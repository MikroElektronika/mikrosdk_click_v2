/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 * \brief This file contains API for Fingerprint 3 Click driver.
 *
 * \addtogroup fingerprint3 Fingerprint 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef FINGERPRINT3_H
#define FINGERPRINT3_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define FINGERPRINT3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define FINGERPRINT3_RETVAL  uint8_t

#define FINGERPRINT3_OK           0x00
#define FINGERPRINT3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup instruction_code  Instruction code
 * \{
 */

#define FINGERPRINT3_CMD_GET_IMAGE                                  0x01
#define FINGERPRINT3_CMD_IMAGE_2_TZ                                 0x02
#define FINGERPRINT3_CMD_MATCH                                      0x03
#define FINGERPRINT3_CMD_SEARCH                                     0x04
#define FINGERPRINT3_CMD_REG_MODEL                                  0x05
#define FINGERPRINT3_CMD_STORE                                      0x06
#define FINGERPRINT3_CMD_LOAD_CHAR                                  0x07
#define FINGERPRINT3_CMD_UPLOAD_CHAR                                0x08
#define FINGERPRINT3_CMD_DOWNLOAD_CHAR                              0x09
#define FINGERPRINT3_CMD_UPLOAD_IMAGE                               0x0A
#define FINGERPRINT3_CMD_DOWNLOAD_IMAGE                             0x0B
#define FINGERPRINT3_CMD_DELETE_CHAR                                0x0C
#define FINGERPRINT3_CMD_EMPTY                                      0x0D
#define FINGERPRINT3_CMD_SET_SYS_PARAM                              0x0E
#define FINGERPRINT3_CMD_READ_SYS_PARAM                             0x0F
#define FINGERPRINT3_CMD_SET_PASSWORD                               0x12
#define FINGERPRINT3_CMD_VERIFY_PASSWORD                            0x13
#define FINGERPRINT3_CMD_GET_RANDOM_CODE                            0x14
#define FINGERPRINT3_CMD_SET_ADDRESS                                0x15
#define FINGERPRINT3_CMD_READ_INFO_PAGE                             0x16
#define FINGERPRINT3_CMD_PORT_CONTROL                               0x17
#define FINGERPRINT3_CMD_WRITE_NOTEPAD                              0x18
#define FINGERPRINT3_CMD_READ_NOTEPAD                               0x19
#define FINGERPRINT3_CMD_TEMPLATE_NUM                               0x1D
#define FINGERPRINT3_CMD_READ_INDEX_TEMPLATE                        0x1F
#define FINGERPRINT3_CMD_GET_IMAGE_EXT                              0x28
#define FINGERPRINT3_CMD_CANCEL                                     0x30
#define FINGERPRINT3_CMD_AURA_CONTROL                               0x35
#define FINGERPRINT3_CMD_CHECK_SENSOR                               0x36
#define FINGERPRINT3_CMD_GET_ALG_VERSION                            0x39
#define FINGERPRINT3_CMD_GET_FW_VERSION                             0x3A
#define FINGERPRINT3_CMD_READ_PRODUCT_INFO                          0x3C
#define FINGERPRINT3_CMD_SOFT_RESET                                 0x3D
#define FINGERPRINT3_CMD_HAND_SHAKE                                 0x40
/** \} */

/**
 * \defgroup confirmation_code  Confirmation code
 * \{
 */
#define FINGERPRINT3_CONF_CMD_OK                                    0x00
#define FINGERPRINT3_CONF_PACKET_RECEIVE_ERROR                      0x01
#define FINGERPRINT3_CONF_NO_FINGER                                 0x02
#define FINGERPRINT3_CONF_ENROLL_FAIL                               0x03
#define FINGERPRINT3_CONF_OVER_DISORDERLY_FAIL                      0x06
#define FINGERPRINT3_CONF_OVER_SMALLNESS_FAIL                       0x07
#define FINGERPRINT3_CONF_NO_MATCH                                  0x08
#define FINGERPRINT3_CONF_NOT_FOUND                                 0x09
#define FINGERPRINT3_CONF_FAIL_TO_COMBINE                           0x0A
#define FINGERPRINT3_CONF_BAD_LOCATION                              0x0B
#define FINGERPRINT3_CONF_READ_TEMPLATE_FAIL                        0x0C
#define FINGERPRINT3_CONF_UPLOAD_TEMPLATE_FAIL                      0x0D
#define FINGERPRINT3_CONF_PACKET_RECEIVE_FAIL                       0x0E
#define FINGERPRINT3_CONF_UPLOAD_IMAGE_FAIL                         0x0F
#define FINGERPRINT3_CONF_DELETE_TEMPLATE_FAIL                      0x10
#define FINGERPRINT3_CONF_LIBRARY_CLEAR_FAIL                        0x11
#define FINGERPRINT3_CONF_WRONG_PASSWORD                            0x13
#define FINGERPRINT3_CONF_GENERATE_IMAGE_FAIL                       0x15
#define FINGERPRINT3_CONF_FLASH_WRITE_ERROR                         0x18
#define FINGERPRINT3_CONF_NO_DEFINITION_ERROR                       0x19
#define FINGERPRINT3_CONF_INVALID_REG_NUM                           0x1A
#define FINGERPRINT3_CONF_INCORRECT_REG_CONFIG                      0x1B
#define FINGERPRINT3_CONF_WRONG_PAGE_NUM                            0x1C
#define FINGERPRINT3_CONF_COM_PORT_FAIL                             0x1D
/** \} */

/**
 * \defgroup header_bytes Header bytes
 * \{
 */
#define FINGERPRINT3_HEADER                                         0xEF01
#define FINGERPRINT3_HEADER_MSB                                     0xEF
#define FINGERPRINT3_HEADER_LSB                                     0x01
/** \} */

/**
 * \defgroup default_address_password Default address and password
 * \{
 */
#define FINGERPRINT3_DEFAULT_ADDRESS                                0xFFFFFFFFul
#define FINGERPRINT3_DEFAULT_PASSWORD                               0x00000000ul
/** \} */

/**
 * \defgroup pid Package identifier ( PID )
 * \{
 */
#define FINGERPRINT3_COMMAND_PACKET                                 0x01
#define FINGERPRINT3_DATA_PACKET                                    0x02
#define FINGERPRINT3_ACK_PACKET                                     0x07
#define FINGERPRINT3_END_DATA_PACKET                                0x08
/** \} */

/**
 * \defgroup finger_detection  Finger detection
 * \{
 */
#define FINGERPRINT3_DETECT_FINGER                                  0x00
#define FINGERPRINT3_DETECT_NO_FINGER                               0x01
/** \} */

/**
 * \defgroup error_flags  Error flags
 * \{
 */
#define FINGERPRINT3_ERR_TIMEOUT                                    0xFB
#define FINGERPRINT3_ERR_PACKAGE_LEN                                0xFC
#define FINGERPRINT3_ERR_CHKSUM                                     0xFD
#define FINGERPRINT3_ERR_RESPONSE                                   0xFE
#define FINGERPRINT3_ERR_HEADER                                     0xFF
/** \} */

/**
 * \defgroup aura_led_config  Aura LED config
 * \{
 */
#define FINGERPRINT3_AURA_LED_RED                                    0x01
#define FINGERPRINT3_AURA_LED_BLUE                                   0x02
#define FINGERPRINT3_AURA_LED_PURPLE                                 0x03

#define FINGERPRINT3_AURA_CTRL_BREATH                                0x01
#define FINGERPRINT3_AURA_CTRL_FLASH                                 0x02
#define FINGERPRINT3_AURA_CTRL_ON                                    0x03
#define FINGERPRINT3_AURA_CTRL_OFF                                   0x04
#define FINGERPRINT3_AURA_CTRL_GRADUAL_ON                            0x05
#define FINGERPRINT3_AURA_CTRL_GRADUAL_OFF                           0x06

#define FINGERPRINT3_AURA_TIME_INFINITE                              0x00
/** \} */

/**
 * \defgroup max_pkg_len  MAX package length
 * \{
 */
#define FINGERPRINT3_MAX_PACKAGE_LENGTH                              256
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define FINGERPRINT3_DRV_TX_BUFFER_SIZE                              500
#define FINGERPRINT3_DRV_RX_BUFFER_SIZE                              500
/** \} */

/**
 * \defgroup timeout Timeout
 * \{
 */
#define FINGERPRINT3_TIMEOUT                                         500
/** \} */


/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Package structure.
 */

typedef struct
{
    uint16_t header;
    uint32_t addr;
    uint8_t pkg_id;
    uint16_t pkg_len;
    uint8_t pkg_content[ FINGERPRINT3_MAX_PACKAGE_LENGTH ];
    uint16_t checksum;
    
} fingerprint3_pkg_t;

/**
 * @brief Product Info structure.
 */
typedef struct
{
    uint8_t module_type[ 16 ];
    uint8_t module_batch_number[ 4 ];
    uint8_t module_serial_number[ 8 ];
    uint8_t hardware_version[ 2 ];
    uint8_t sensor_type[ 8 ];
    uint16_t sensor_width;
    uint16_t sensor_height;
    uint16_t template_size;
    uint16_t database_size;
    
} fingerprint3_product_info_t;

/**
 * @brief System Parameters structure.
 */
typedef struct
{
    uint16_t status_register;
    uint16_t system_identifier_code;
    uint16_t finger_library_size;
    uint16_t security_level;
    uint32_t device_address;
    uint16_t data_package_size;
    uint32_t baudrate;
    
} fingerprint3_sys_parameter_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 
    digital_out_t rst;

    // Input pins 
    digital_in_t int_pin;
    
    // Modules 
    uart_t uart;

    uint8_t uart_rx_buffer[ FINGERPRINT3_DRV_RX_BUFFER_SIZE ];
    uint8_t uart_tx_buffer[ FINGERPRINT3_DRV_TX_BUFFER_SIZE ];
    
    fingerprint3_pkg_t rsp;
    fingerprint3_product_info_t product_info;
    fingerprint3_sys_parameter_t system_parameters;
    uint32_t address;
    uint32_t password;

} fingerprint3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 
    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 
    pin_name_t rst;
    pin_name_t int_pin;

    // static variable 
    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.     

} fingerprint3_cfg_t;

/**
 * @brief Error type 
 */

/** \} */ // End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */
 
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @details This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void fingerprint3_cfg_setup ( fingerprint3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t fingerprint3_init ( fingerprint3_t *ctx, fingerprint3_cfg_t *cfg );

/**
 * @brief Set config function.
 *
 * @param ctx Click object.
 * @param addr Address.
 * @param pass Password.
 *
 * @returns 0 - OK, Other - error.
 * 
 * @details This function verifies password and sets the address, also stores product info and system parameters
 * in the click object structure. 
 */
uint8_t fingerprint3_set_config ( fingerprint3_t *ctx, uint32_t addr, uint32_t pass );

/**
 * @brief Set RST pin state function.
 *
 * @param ctx Click object.
 * @param pin_state
 * - 0 : Inactive.
 * - 1 : Active.
 *
 * @details This function sets state of the RST pin 
 * of the Fingerprint 3 Click board.
 */
void fingerprint3_set_rst_pin ( fingerprint3_t *ctx, uint8_t rst_pin );

/**
 * @brief Generic write function.
 * 
 * @param ctx Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void fingerprint3_generic_write ( fingerprint3_t *ctx, uint8_t *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * 
 * @param ctx Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * 
 * @return Number of reads data.
 */
int32_t fingerprint3_generic_read ( fingerprint3_t *ctx, uint8_t *data_buf, uint16_t max_len );

/**
 * @brief Send package function
 *
 * @param ctx         Click object. 
 * @param pkg_id      Package Identifier.
 * @param pkg_content Package Content.
 * @param pkg_len     Package Length ( without checksum bytes ).
 *
 * @returns Confirmation code or Read errors.
 *
 * @details This function sends package and reads response to that package which will be stored
 * in the click object structure. It also checks checksum and header bytes.
 */
uint8_t fingerprint3_send_package ( fingerprint3_t *ctx, uint8_t pkg_id, uint8_t *pkg_content, uint16_t pkg_len );

/**
 * @brief Finger indicator function.
 *
 * @param ctx Click object.
 * 
 * @return Logic state of INT pin.
 */
uint8_t fingerprint3_finger_indicator ( fingerprint3_t *ctx );

/**
 * @brief Aura LED control function.
 *
 * @param ctx         Click object. 
 * @param control     FINGERPRINT3_AURA_CTRL_ON, FINGERPRINT3_AURA_CTRL_OFF, 
 *                    FINGERPRINT3_AURA_CTRL_BREATH, FINGERPRINT3_AURA_CTRL_FLASH, 
 *                    FINGERPRINT3_AURA_CTRL_GRADUAL_ON or FINGERPRINT3_AURA_CTRL_GRADUAL_OFF
 * @param speed       effective for FINGERPRINT3_AURA_CTRL_BREATH, FINGERPRINT3_AURA_CTRL_FLASH, 
 *                                  FINGERPRINT3_AURA_CTRL_GRADUAL_ON, FINGERPRINT3_AURA_CTRL_GRADUAL_OFF
 *                    0 to 255, 0 means 5 seconds per cycle
 * @param color       FINGERPRINT3_AURA_LED_RED, FINGERPRINT3_AURA_LED_BLUE or FINGERPRINT3_AURA_LED_PURPLE
 * @param times       effective for FINGERPRINT3_AURA_CTRL_BREATH, FINGERPRINT3_AURA_CTRL_FLASH
 *                    number of cycles: 0 means infinite or 1 to 255
 *
 * @returns Confirmation code or Read errors.
 *
 * @details This function controls the LED ring of the sensor.
 */
uint8_t fingerprint3_aura_control ( fingerprint3_t *ctx, uint8_t control, uint8_t speed,
                                                         uint8_t color, uint8_t times );

/**
 * @brief Verify password function.
 *
 * @param ctx         Click object. 
 * @param pass        Password.
 *
 * @returns Confirmation code or Read errors.
 *
 * @details This function verifies the password.
 */
uint8_t fingerprint3_verify_password ( fingerprint3_t *ctx, uint32_t pass );

/**
 * @brief Read product info function.
 *
 * @param ctx         Click object. 
 *
 * @returns Confirmation code or Read errors.
 *
 * @details This function reads product info and stores data in the click object product_info structure.
 */
uint8_t fingerprint3_read_product_info ( fingerprint3_t *ctx );

/**
 * @brief Read system parameter function.
 *
 * @param ctx         Click object. 
 *
 * @returns Confirmation code or Read errors.
 *
 * @details This function reads system parameter and stores data in the click object system_parameter structure.
 */
uint8_t fingerprint3_read_sys_param ( fingerprint3_t *ctx );

/**
 * @brief Set security level function.
 *
 * @param ctx         Click object. 
 * @param lvl         Security level - a number between 1 (inclusive) and 5 (inclusive).
 *                    level 1: false acceptance rate is lowest and false rejection rate is highest
 *                    level 5: false acceptance rate is highest and false rejection rate is lowest
 *
 * @returns Confirmation code or Read errors.
 *
 * @details This function sets the security level.
 */
uint8_t fingerprint3_set_security_lvl ( fingerprint3_t *ctx, uint8_t lvl );

/**
 * @brief Hand shake function.
 *
 * @param ctx         Click object. 
 *
 * @returns Confirmation code or Read errors.
 *
 * @details This function checks if module is okay.
 */
uint8_t fingerprint3_hand_shake ( fingerprint3_t *ctx );

/**
 * @brief Check sensor function.
 *
 * @param ctx         Click object. 
 *
 * @returns Confirmation code or Read errors.
 *
 * @details This function checks if sensor is okay.
 */
uint8_t fingerprint3_check_sensor ( fingerprint3_t *ctx );

/**
 * @brief Soft reset function.
 *
 * @param ctx         Click object. 
 *
 * @returns Confirmation code or Read errors.
 *
 * @details This function resets sensor and waits until it is ready.
 */
uint8_t fingerprint3_soft_reset ( fingerprint3_t *ctx );

/**
 * @brief Read index table function.
 *
 * @param ctx         Click object.
 * @param table       A pointer to a memory block of at least 32 bytes.
 * @param page        the index page, a number between 0 (inclusive) and 3 (inclusive)
 *                    index page 0: location 0 to 255
 *                    index page 1: location 256 to 511
 *                    index page 2: location 512 to 767
 *                    index page 3: location 768 to 1023
 *
 * @returns Confirmation code or Read errors.
 *
 * @details This function reads the index table a bitfield indicating at which location a template is stored.
 * 
 * @note
 * The bit index corresponds to the location
 * bit equal 1 means template is stored at that location 
 * bit equal 0 means no template is stored at that location
 * e.g. for page 0: template at location k <=> table[k / 8] >> k % 8 & 0x01
 */
uint8_t fingerprint3_read_index_table ( fingerprint3_t *ctx, uint8_t *table, uint8_t page );

/**
 * @brief Take image function.
 *
 * @param ctx         Click object. 
 *
 * @returns Confirmation code or Read errors ( FINGERPRINT3_CONF_NO_FINGER if no finger is on the sensor ).
 *
 * @details This function detects finger on the sensor, takes image and writes it into the image buffer.
 */
uint8_t fingerprint3_take_image ( fingerprint3_t *ctx );

/**
 * @brief Extract features function.
 *
 * @param ctx         Click object. 
 * @param char_buffer Character buffer - number in the range 1 to 6.
 *
 * @returns Confirmation code or Read errors.
 *
 * @details This function extracts the features from the finger image in the image buffer
 * and writes them into the character buffer indentified by char_buffer
 */
uint8_t fingerprint3_extract_features ( fingerprint3_t *ctx, uint8_t char_buffer );

/**
 * @brief Create template function.
 *
 * @param ctx         Click object. 
 *
 * @returns Confirmation code or Read errors.
 *
 * @details This function combines the features from char_buffer 1 to k into a template
 * k is the char_buffer where the most recent feature extraction was written to
 * the template is written back to char_buffer 1 and 2
 */
uint8_t fingerprint3_create_template ( fingerprint3_t *ctx );

/**
 * @brief Create template function.
 *
 * @param ctx         Click object. 
 * @param char_buffer Character buffer - number in the range 1 to 6.
 * @param location    Location in flash.
 *
 * @returns Confirmation code or Read errors.
 *
 * @details This function stores template located in char_buffer and char_buffer+1 to flash at location.
 */
uint8_t fingerprint3_store_template ( fingerprint3_t *ctx, uint8_t char_buffer, uint16_t location );

/**
 * @brief Delete template function.
 *
 * @param ctx         Click object. 
 * @param location    Location in flash.
 *
 * @returns Confirmation code or Read errors.
 *
 * @details This function deletes template located at the desired location.
 */
uint8_t fingerprint3_delete_template ( fingerprint3_t *ctx, uint16_t location );

/**
 * @brief Empty the library function.
 *
 * @param ctx         Click object. 
 *
 * @returns Confirmation code or Read errors.
 *
 * @details This function deletes all the templates.
 */
uint8_t fingerprint3_empty_library ( fingerprint3_t *ctx );

/**
 * @brief Create template function.
 *
 * @param ctx         Click object. 
 * @param char_buffer Character buffer - number in the range 1 to 6.
 * @param location    Location in flash.
 *
 * @returns Confirmation code or Read errors.
 *
 * @details This function loads template from flash in location to char_buffer and char_buffer+1.
 */
uint8_t fingerprint3_load_template ( fingerprint3_t *ctx, uint8_t char_buffer, uint16_t location );

/**
 * @brief Empty the library function.
 *
 * @param ctx         Click object. 
 * @param score       Reference to write the matching score to.
 * 
 * @returns Confirmation code or Read errors ( FINGERPRINT3_CONF_NO_MATCH if features do not match ).
 *
 * @details This function compares the recently extracted features with the template in character buffer 1 and 2.
 */
uint8_t fingerprint3_match_finger ( fingerprint3_t *ctx, uint16_t *score );

/**
 * @brief Empty the library function.
 *
 * @param ctx         Click object. 
 * @param char_buffer Character buffer - number in the range 1 to 6.
 * @param location    Reference to write the matching location to.
 * @param score       Reference to write the matching score to.
 * 
 * @returns Confirmation code or Read errors ( FINGERPRINT3_CONF_NO_MATCH if features do not match ).
 *
 * @details This function searches the fingerprint library for a template matching the features in char_buffer.
 */
uint8_t fingerprint3_search_finger ( fingerprint3_t *ctx, uint8_t char_buffer, uint16_t *location, uint16_t *score );

#ifdef __cplusplus
}
#endif
#endif  // _FINGERPRINT3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
