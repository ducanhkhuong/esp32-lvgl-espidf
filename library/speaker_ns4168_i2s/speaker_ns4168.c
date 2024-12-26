#include "esp_log.h"
#include "esp_check.h"
#include "audio_player.h"
#include "driver/gpio.h"
#include "freertos/semphr.h"
#include "esp_spiffs.h"

static const char *TAG = "AUDIO PLAYER";

#define CONFIG_BSP_I2S_NUM 1

/* Audio */
#define BSP_I2S_SCLK (GPIO_NUM_36)
#define BSP_I2S_MCLK (GPIO_NUM_2)
#define BSP_I2S_LCLK (GPIO_NUM_35)
#define BSP_I2S_DOUT (GPIO_NUM_37) // To Codec ES8311
#define BSP_I2S_DSIN (GPIO_NUM_NC) // From ADC ES7210
#define BSP_POWER_AMP_IO (GPIO_NUM_3)

#define BSP_I2S_GPIO_CFG       \
    {                          \
        .mclk = BSP_I2S_MCLK,  \
        .bclk = BSP_I2S_SCLK,  \
        .ws = BSP_I2S_LCLK,    \
        .dout = BSP_I2S_DOUT,  \
        .din = BSP_I2S_DSIN,   \
        .invert_flags = {      \
            .mclk_inv = false, \
            .bclk_inv = false, \
            .ws_inv = false,   \
        },                     \
    }

#define BSP_I2S_DUPLEX_MONO_CFG(_sample_rate)                                                         \
    {                                                                                                 \
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(_sample_rate),                                          \
        .slot_cfg = I2S_STD_PHILIP_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_MONO), \
        .gpio_cfg = BSP_I2S_GPIO_CFG,                                                                 \
    }

static i2s_chan_handle_t i2s_tx_chan;
static i2s_chan_handle_t i2s_rx_chan;

static esp_err_t bsp_i2s_write(void *audio_buffer, size_t len, size_t *bytes_written, uint32_t timeout_ms)
{
    // Giảm âm lượng
    int16_t *pcm_buffer = (int16_t *)audio_buffer; // Giả sử dữ liệu là PCM 16-bit
    size_t sample_count = len / sizeof(int16_t);
    const float volume_scale = 0.3; // Giảm âm lượng xuống 50%

    for (size_t i = 0; i < sample_count; i++)
    {
        pcm_buffer[i] = (int16_t)(pcm_buffer[i] * volume_scale);
    }

    return i2s_channel_write(i2s_tx_chan, (char *)audio_buffer, len, bytes_written, timeout_ms);
}

static esp_err_t bsp_i2s_reconfig_clk(uint32_t rate, uint32_t bits_cfg, i2s_slot_mode_t ch)
{
    esp_err_t ret = ESP_OK;
    i2s_std_config_t std_cfg = {
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(rate),
        .slot_cfg = I2S_STD_PHILIP_SLOT_DEFAULT_CONFIG((i2s_data_bit_width_t)bits_cfg, (i2s_slot_mode_t)ch),
        .gpio_cfg = BSP_I2S_GPIO_CFG,
    };

    ret |= i2s_channel_disable(i2s_tx_chan);
    ret |= i2s_channel_reconfig_std_clock(i2s_tx_chan, &std_cfg.clk_cfg);
    ret |= i2s_channel_reconfig_std_slot(i2s_tx_chan, &std_cfg.slot_cfg);
    ret |= i2s_channel_enable(i2s_tx_chan);
    return ret;
}

static esp_err_t audio_mute_function(AUDIO_PLAYER_MUTE_SETTING setting)
{
    ESP_LOGI(TAG, "Mute setting: %d", setting);
    return ESP_OK;
}

static esp_err_t bsp_audio_init(const i2s_std_config_t *i2s_config, i2s_chan_handle_t *tx_channel, i2s_chan_handle_t *rx_channel)
{
    /* Setup I2S peripheral */
    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(CONFIG_BSP_I2S_NUM, I2S_ROLE_MASTER);
    chan_cfg.auto_clear = true; // Auto clear the legacy data in the DMA buffer
    ESP_ERROR_CHECK(i2s_new_channel(&chan_cfg, tx_channel, rx_channel));

    /* Setup I2S channels */
    const i2s_std_config_t std_cfg_default = BSP_I2S_DUPLEX_MONO_CFG(22050);
    const i2s_std_config_t *p_i2s_cfg = &std_cfg_default;
    if (i2s_config != NULL)
    {
        p_i2s_cfg = i2s_config;
    }

    if (tx_channel != NULL)
    {
        ESP_ERROR_CHECK(i2s_channel_init_std_mode(*tx_channel, p_i2s_cfg));
        ESP_ERROR_CHECK(i2s_channel_enable(*tx_channel));
    }
    if (rx_channel != NULL)
    {
        ESP_ERROR_CHECK(i2s_channel_init_std_mode(*rx_channel, p_i2s_cfg));
        ESP_ERROR_CHECK(i2s_channel_enable(*rx_channel));
    }

    /* Setup power amplifier pin */
    const gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = BIT64(BSP_POWER_AMP_IO),
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLDOWN_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&io_conf));

    return ESP_OK;
}

void speaker_config(void)
{

    ESP_LOGI(TAG, "Initializing audio system");

    /* Configure I2S peripheral and Power Amplifier */
    i2s_std_config_t std_cfg = {
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(44100),
        .slot_cfg = I2S_STD_PHILIP_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_STEREO),
        .gpio_cfg = BSP_I2S_GPIO_CFG,
    };

    esp_err_t ret = bsp_audio_init(&std_cfg, &i2s_tx_chan, &i2s_rx_chan);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to initialize audio system");
        return;
    }

    audio_player_config_t config = {
        .mute_fn = audio_mute_function,
        .write_fn = bsp_i2s_write,
        .clk_set_fn = bsp_i2s_reconfig_clk,
        .priority = 0,
        .coreID = 0};

    ret = audio_player_new(config);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to initialize audio player");
    }
}

void init_sound_spiffs(void)
{
    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/sound",         // Điểm gắn kết SPIFFS
        .partition_label = NULL,       // Tên phân vùng trong partitions.csv
        .max_files = 3,                // Số lượng tệp mở tối đa
        .format_if_mount_failed = true // Định dạng lại nếu gắn kết thất bại
    };

    esp_err_t ret = esp_vfs_spiffs_register(&conf);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        return;
    }

    size_t total = 0, used = 0;
    ret = esp_spiffs_info(NULL, &total, &used);
    if (ret == ESP_OK)
    {
        ESP_LOGI(TAG, "SPIFFS total: %d, used: %d", total, used);
    }
    else
    {
        ESP_LOGE(TAG, "Failed to get SPIFFS info (%s)", esp_err_to_name(ret));
    }
}

void read_and_play_mp3_file(const char *filename)
{
    esp_err_t ret;
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        ESP_LOGE(TAG, "Failed to open file: %s", filename);
        return;
    }

    ESP_LOGI(TAG, "Reading MP3 file: %s", filename);
    ret = audio_player_play(file);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to play audio");
        fclose(file);
        return;
    }

    ESP_LOGI(TAG, "Playing audio...");

    // // Delay for playback duration (adjust as necessary)
    vTaskDelay(pdMS_TO_TICKS(4500)); // Example: 16 seconds

    ESP_LOGI(TAG, "Playback finished");

    ESP_LOGI(TAG, "File closed");
}

void sap_toi_bien_toc_do_gioi_han_40()
{
    read_and_play_mp3_file("/sound/tdgh40.mp3");
}

void sap_toi_bien_toc_do_gioi_han_50()
{
    read_and_play_mp3_file("/sound/tdgh50.mp3");
}

void sap_toi_bien_toc_do_gioi_han_60()
{
    read_and_play_mp3_file("/sound/tdgh60.mp3");
}

void sap_toi_bien_toc_do_gioi_han_70()
{
    read_and_play_mp3_file("/sound/tdgh70.mp3");
}

void sap_toi_bien_toc_do_gioi_han_80()
{
    read_and_play_mp3_file("/sound/tdgh80.mp3");
}

void sap_toi_bien_toc_do_gioi_han_90()
{
    read_and_play_mp3_file("/sound/tdgh90.mp3");
}

void sap_toi_bien_toc_do_gioi_han_100()
{
    read_and_play_mp3_file("/sound/tdgh100.mp3");
}

void sap_toi_bien_toc_do_gioi_han_120()
{
    read_and_play_mp3_file("/sound/tdgh120.mp3");
}

void sap_vao_khu_dan_cu()
{
    read_and_play_mp3_file("/sound/svaokhudancu.mp3");
}

void sap_thoat_khoi_khu_dan_cu()
{
    read_and_play_mp3_file("/sound/sapthoatkhudancu.mp3");
}

void sap_toi_tram_thu_phi()
{
    read_and_play_mp3_file("/sound/saptoitramthuphi.mp3");
}

void qua_toc_do_cho_phep()
{
    read_and_play_mp3_file("/sound/Over_limit_speed.mp3");
}

void het_duong_cam_vuot()
{
    read_and_play_mp3_file("/sound/hetduongcamvuot.mp3");
}

void vao_duong_cam_vuot()
{
    read_and_play_mp3_file("/sound/duongcamvuot.mp3");
}

void giam_toc_do_gioi_han()
{
    read_and_play_mp3_file("/sound/giamtocdogioihan.mp3");
}

void co_camera_giao_thong()
{
    read_and_play_mp3_file("/sound/cocameragiaothong.mp3");
}

void beep()
{
    read_and_play_mp3_file("/sound/censor-beep-01.mp3");
}

void camera_theo_doi_toc_do()
{
    read_and_play_mp3_file("/sound/cameratheodoitd.mp3");
}
