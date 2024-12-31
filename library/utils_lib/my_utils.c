#include "my_utils.h"
#include "stdbool.h"
#include "esp_log.h"

#define TAG "Parse BLE data: "
sign_data_t sign_handle(uint8_t *data, uint16_t len)
{

    // priority
    // 1 - limit speed (current speed -> next speed)
    // 2 - enter or exit urban
    // 3 - camera
    // 4 - other
    sign_data_t sign_data = {0}; // Initialize the structure to zero
    uint8_t offset = 0;
    if (data == NULL)
    {
        ESP_LOGE(TAG, "Received null data");
        return sign_data;
    }

    ESP_LOGI(TAG, "Data received:");
    for (uint16_t i = 0; i < len; i++)
    {
        ESP_LOGI(TAG, "Byte[%d]: 0x%02X", i, data[i]);
    }

    // Parse the data
    while (offset < len)
    {
        uint8_t header = data[offset];
        switch (header)
        {
        case HEADER_CURRENT_SPEED:
            sign_data.current_speed.current_speed = data[offset + 1];
            ESP_LOGI(TAG, "Current Speed: %d", sign_data.current_speed.current_speed);
            offset += 2; // Move to the next header
            break;

        case HEADER_NEXT_SPEED:
            memcpy(sign_data.next_speed.unique_id, &data[offset + 1], 3);
            sign_data.next_speed.next_speed = data[offset + 4];
            memcpy(sign_data.next_speed.distance, &data[offset + 5], 2);
            ESP_LOGI(TAG, "Next Speed Unique ID: 0x%02X%02X%02X",
                     sign_data.next_speed.unique_id[0],
                     sign_data.next_speed.unique_id[1],
                     sign_data.next_speed.unique_id[2]);
            ESP_LOGI(TAG, "Next Speed: %d, Distance: 0x%02X%02X",
                     sign_data.next_speed.next_speed,
                     sign_data.next_speed.distance[0],
                     sign_data.next_speed.distance[1]);
            offset += 7;
            break;

        case HEADER_CAMERA:
            sign_data.camera_sign.number_of_sign = data[offset + 1];
            if (sign_data.camera_sign.number_of_sign == 0)
            {
                ESP_LOGI(TAG, "Dont have camera");
                offset += 2;
            }
            offset += 2;
            for (int i = 0; i < sign_data.camera_sign.number_of_sign; i++)
            {
                memcpy(sign_data.camera_sign.unique_id[i], &data[offset], 3);
                sign_data.camera_sign.traffic_id_sign[i] = data[offset + 3];
                memcpy(sign_data.camera_sign.distance[i], &data[offset + 4], 2);
                offset += 6;
                ESP_LOGI(TAG, "Camera Sign[%d]: Unique ID: 0x%02X%02X%02X, Traffic ID: 0x%02X, Distance: 0x%02X%02X",
                         i + 1,
                         sign_data.camera_sign.unique_id[i][0],
                         sign_data.camera_sign.unique_id[i][1],
                         sign_data.camera_sign.unique_id[i][2],
                         sign_data.camera_sign.traffic_id_sign[i],
                         sign_data.camera_sign.distance[i][0],
                         sign_data.camera_sign.distance[i][1]);
            }
            break;

        case HEADER_TRAFFIC:
            sign_data.traffic_sign.number_of_sign = data[offset + 1];
            if (sign_data.traffic_sign.number_of_sign == 0)
            {
                ESP_LOGI(TAG, "Don't have traffic sign");
                offset += 2;
            }
            else
            {
                offset += 2;
                for (int i = 0; i < sign_data.traffic_sign.number_of_sign; i++)
                {
                    memcpy(sign_data.traffic_sign.unique_id[i], &data[offset], 3);
                    sign_data.traffic_sign.traffic_id_sign[i] = data[offset + 3];
                    memcpy(sign_data.traffic_sign.distance[i], &data[offset + 4], 2);
                    offset += 6;

                    ESP_LOGI(TAG, "Traffic Sign[%d]: Unique ID: 0x%02X%02X%02X, Traffic ID: 0x%02X, Distance: 0x%02X%02X",
                             i + 1,
                             sign_data.traffic_sign.unique_id[i][0],
                             sign_data.traffic_sign.unique_id[i][1],
                             sign_data.traffic_sign.unique_id[i][2],
                             sign_data.traffic_sign.traffic_id_sign[i],
                             sign_data.traffic_sign.distance[i][0],
                             sign_data.traffic_sign.distance[i][1]);
                }
            }
            break;

        case HEADER_OTHER:
            sign_data.other_sign.number_of_sign = data[offset + 1];
            if (sign_data.other_sign.number_of_sign == 0)
            {
                ESP_LOGI(TAG, "Don't have other traffic sign");
                offset += 2;
            }
            else
            {
                offset += 2;
                for (int i = 0; i < sign_data.other_sign.number_of_sign; i++)
                {
                    memcpy(sign_data.other_sign.unique_id[i], &data[offset], 3);
                    sign_data.other_sign.traffic_id_sign[i] = data[offset + 3];
                    memcpy(sign_data.other_sign.distance[i], &data[offset + 4], 2);
                    offset += 6;

                    ESP_LOGI(TAG, "Other Sign[%d]: Unique ID: 0x%02X%02X%02X, Traffic ID: 0x%02X, Distance: 0x%02X%02X",
                             i + 1,
                             sign_data.other_sign.unique_id[i][0],
                             sign_data.other_sign.unique_id[i][1],
                             sign_data.other_sign.unique_id[i][2],
                             sign_data.other_sign.traffic_id_sign[i],
                             sign_data.other_sign.distance[i][0],
                             sign_data.other_sign.distance[i][1]);
                }
            }
            break;

        default:
            // ESP_LOGW(TAG, "Unknown header: 0x%02X at offset %d", header, offset);
            offset++;
            break;
        }
    }
    return sign_data;
}