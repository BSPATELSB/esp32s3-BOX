/**
 * @file tt21100.h
 * @brief 
 * @version 0.1
 * @date 2021-09-06
 * 
 * @copyright Copyright 2021 Espressif Systems (Shanghai) Co. Ltd.
 *
 *      Licensed under the Apache License, Version 2.0 (the "License");
 *      you may not use this file except in compliance with the License.
 *      You may obtain a copy of the License at
 *
 *               http://www.apache.org/licenses/LICENSE-2.0
 *
 *      Unless required by applicable law or agreed to in writing, software
 *      distributed under the License is distributed on an "AS IS" BASIS,
 *      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *      See the License for the specific language governing permissions and
 *      limitations under the License.
 */

#pragma once

#include <stdint.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Init TT21100 touch panel
 * 
 * @return 
 *    - ESP_OK: Success
 *    - Others: Fail
 */
esp_err_t tt21100_tp_init(void);

/**
 * @brief Read touch point from TT21100
 * 
 * @param tp_num Touch point number
 * @param x X coordinate
 * @param y Y coordinate
 * @return 
 *    - ESP_OK: Success
 *    - Others: Fail
 */
esp_err_t tt21100_tp_read(uint8_t *tp_num, uint16_t *x, uint16_t *y);

#ifdef __cplusplus
}
#endif

