/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file irgrid2.h
 * @brief This file contains API for IR Grid 2 Click Driver.
 */

#ifndef IRGRID2_H
#define IRGRID2_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup irgrid2 IR Grid 2 Click Driver
 * @brief API for configuring and manipulating IR Grid 2 Click driver.
 * @{
 */

/**
 * @defgroup irgrid2_error_code IR Grid 2 Registers List
 * @brief List of registers of IR Grid 2 Click driver.
 */

/**
 * @defgroup irgrid2_set IR Grid 2 Registers Settings
 * @brief Settings for registers of IR Grid 2 Click driver.
 */

/**
 * @addtogroup irgrid2_set
 * @{
 */

/**
 * @brief IR Grid 2 device address setting.
 * @details Specified setting for device slave address selection of
 * IR Grid 2 Click driver.
 */
#define IRGRID2_SET_DEV_ADDR  0x33

/*! @} */ // irgrid2_set

/**
 * @defgroup irgrid2_map IR Grid 2 MikroBUS Map
 * @brief MikroBUS pin mapping of IR Grid 2 Click driver.
 */

/**
 * @addtogroup irgrid2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of IR Grid 2 Click to the selected MikroBUS.
 */
#define IRGRID2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // irgrid2_map
/*! @} */ // irgrid2

/**
 * @brief IR Grid 2 Click params definition.
 * @details Context object definition of IR Grid 2 Click driver.
 */
typedef struct 
{
    int16_t k_vdd;
    int16_t vdd_25;
    float kv_ptat;
    float kt_ptat;
    uint16_t v_ptat_25;
    float alpha_ptat;
    int16_t gain_eeprom;
    float tgc;
    float cp_kv;
    float cp_kta;
    uint8_t resolution_eeprom;
    uint8_t calibration_mode_eeprom;
    float ks_ta;
    float ks_to[ 4 ];
    int16_t ct[ 4 ];
    float alpha[ 768 ];
    int16_t offset[ 768 ];
    float kta[ 768 ];
    float kv[ 768 ];
    float cp_alpha[ 2 ];
    int16_t cp_offset[ 2 ];
    float il_chess_c[ 3 ];
    uint16_t broken_pixels[ 5 ];
    uint16_t outlier_pixels[ 5 ];
} irgrid2_params_t;

/**
 * @brief IR Grid 2 Click context object.
 * @details Context object definition of IR Grid 2 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;                                /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                           /**< Device slave address (used for I2C driver). */
    irgrid2_params_t params;
    
} irgrid2_t;

/**
 * @brief IR Grid 2 Click configuration object.
 * @details Configuration object definition of IR Grid 2 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

} irgrid2_cfg_t;

/**
 * @brief IR Grid 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   IRGRID2_OK = 0,
   IRGRID2_ERROR = -1,
   IRGRID2_INIT_ERROR = 0xFF,
   IRGRID2_EEPROM_OK = 0x00,
   IRGRID2_EEPROM_ERROR = 0xF0,
   IRGRID2_ADJ_PIXELS_ERROR = 0xF1,
   IRGRID2_ADJ_PIXELS_OK  = 0x00,
   IRGRID2_BROKEN_PIX_ERROR = 0xF2,
   IRGRID2_OUTLIER_PIX_ERROR = 0xF3,
   IRGRID2_2_PIX_ERROR = 0xF4

} irgrid2_return_value_t;

/*!
 * @addtogroup irgrid2 IR Grid 2 Click Driver
 * @brief API for configuring and manipulating IR Grid 2 Click driver.
 * @{
 */

/**
 * @brief IR Grid 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #irgrid2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 */
void irgrid2_cfg_setup ( irgrid2_cfg_t *cfg );

/**
 * @brief IR Grid 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #irgrid2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #irgrid2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 */
err_t irgrid2_init ( irgrid2_t *ctx, irgrid2_cfg_t *cfg );

/**
 * @brief IR Grid 2 default configuration function.
 * @details This function executes a default configuration of IR Grid 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #irgrid2_t object definition for detailed explanation.
 * @return Nothing.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 *
 */
void irgrid2_default_cfg ( irgrid2_t *ctx );

/**
 * @brief IR Grid 2 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #irgrid2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return Nothing.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 */
void irgrid2_generic_write ( irgrid2_t *ctx, uint16_t reg, uint8_t *data_buf, uint16_t len );

/**
 * @brief IR Grid 2 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #irgrid2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return Nothing.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *

 */
void irgrid2_generic_read ( irgrid2_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Function for reading EEPROM.
 * @details This function reads data from the EEPROM.
 * @param[in] ctx : Click context object.
 * See #irgrid2_t object definition for detailed explanation.
 * @param[out] eeprom_data : Buffer in which the data will be stored.
 * @return Nothing.
 * 
 */
void irgrid2_read_eeprom ( irgrid2_t *ctx, uint16_t *eeprom_data );

/**
 * @brief Parameters storage function.
 * @details This function stpores data from the EEPROM.
 * @param[in] ctx : Click context object.
 * See #irgrid2_t object definition for detailed explanation.
 * @param[out] eeprom_data : EEPROM buffer.
 * @return Nothing.
 * 
 */
uint8_t irgrid2_extract_parameters ( irgrid2_t *ctx, uint16_t *eeprom_data );

/**
 * @brief Function for setting refresh rate.
 * @details This function sets settings for refresh rate.
 * @param[in] ctx : Click context object.
 * See #irgrid2_t object definition for detailed explanation.
 * @param[in] refresh_rate : the refresh Rate data that will be set.
 * @return Nothing.
 * 
 */
void irgrid2_set_refresh_rate ( irgrid2_t *ctx, uint8_t refresh_rate );

/**
 * @brief Function for getting frame data.
 * @details This function is used for getting frame data.
 * @param[in] ctx : Click context object.
 * See #irgrid2_t object definition for detailed explanation.
 * @param[out] frame_data : Buffer in which the data will be stored
 * @return Nothing.
 * 
 */
uint16_t irgrid2_get_frame_data ( irgrid2_t *ctx, uint16_t *frame_data );

/**
 * @brief Function for setting resolution.
 * @details This function is used for setting resolution.
 * @param[in] ctx : Click context object.
 * See #irgrid2_t object definition for detailed explanation.
 * @param[in] resolution : The resolution that will be set.
 * @return Nothing.
 * 
 */
void irgrid2_set_resolution ( irgrid2_t *ctx, uint8_t resolution );

/**
 * @brief Function for getting current resolution.
 * @details This function is used for getting current resolution.
 * @param[in] ctx : Click context object.
 * See #irgrid2_t object definition for detailed explanation.
 * @return current resolution
 */
uint16_t irgrid2_get_current_res ( irgrid2_t *ctx );

/**
 * @brief Function for getting current refresh Rate.
 * @details This function is used for getting current refresh Rate.
 * @param[in] ctx : Click context object.
 * See #irgrid2_t object definition for detailed explanation.
 * @return current refresh Rate
 */
uint16_t irgrid2_get_refresh_rate ( irgrid2_t *ctx );

/**
 * @brief Function for setting interleaved mode.
 * @details This function is used for interleaved mode.
 * @param[in] ctx : Click context object.
 * See #irgrid2_t object definition for detailed explanation.
 * @return Nothing.
 *
 */
void irgrid2_set_interleaved_mode ( irgrid2_t *ctx );

/**
 * @brief Function for setting chess mode.
 * @details This function is used for setting chess mode.
 * @param[in] ctx : Click context object.
 * See #irgrid2_t object definition for detailed explanation.
 * @return Nothing.
 * 
 */
void irgrid2_set_chess_mode ( irgrid2_t *ctx );

/**
 * @brief Function for getting current mode.
 * @details This function is used for getting current mode.
 * @param[in] ctx : Click context object.
 * See #irgrid2_t object definition for detailed explanation.
 * @return Current mode.
 * 
 */
uint16_t irgrid2_get_current_mode ( irgrid2_t *ctx );

/**
 * @brief Function for getting pixels temperature
 * @details This function is used for getting pixels temperature.
 * @param[in] ctx : Click context object.
 * See #irgrid2_t object definition for detailed explanation.
 * @param[in] temp_ambient : Ambient temperature data.
 * @param[out] pixel_temp : Output matrix pixels.
 * @return Nothing.
 * 
 */
void irgrid2_get_pixel_temperature ( irgrid2_t *ctx, float *temp_ambient, float *pixel_temp );

/**
 * @brief Function for getting Ambient temperature
 * @details This function is used for getting ambient temperature.
 * @param[in] ctx : Click context object.
 * See #irgrid2_t object definition for detailed explanation.
 * @param[in] frame_data : Frame Data
 * @return Ambient temperature.
 * 
 */
float irgrid2_get_temp_ambient ( irgrid2_t *ctx, uint16_t *frame_data );

/**
 * @brief Function for getting sub page number
 * @details This function is used for getting sub page number.
 * @param[in] ctx : Click context object.
 * See #irgrid2_t object definition for detailed explanation.
 * @param[in] frame_data : Frame Data.
 * @return  Sub page number.
 * 
 */
uint16_t irgrid2_get_subpage_number ( uint16_t *frame_data );

/**
 * @brief Function for getting Vdd.
 * @details This function is used for getting Vdd.
 * @param[in] ctx : Click context object.
 * See #irgrid2_t object definition for detailed explanation.
 * @param[in] frame_data : Frame Data
 */
float irgrid2_get_vdd ( irgrid2_t *ctx, uint16_t *frame_data );

/**
 * @brief Function for calculating temperature objects.
 * @details This function is used for calculating temperature objects.
 * @param[in] ctx : Click context object.
 * See #irgrid2_t object definition for detailed explanation.
 * @param[in] frame_data : Frame Data
 * @param[in] tr_data : Real temperature
 * @param[out] px_matrix : Buffer in which the result of the calculation will be stored
 * @return Nothing.
 * 
 */
void irgrid2_calculate_temp_obj ( irgrid2_t *ctx, uint16_t *frame_data, float tr_data, float *px_matrix );

/**
 * @brief Function for getting Image.
 * @details This function is used for getting Image.
 * @param[in] ctx : Click context object.
 * See #irgrid2_t object definition for detailed explanation.
 * @param[in] frame_data : Frame Data
 * @param[out] px_matrix : Buffer in which the result of the calculation will be stored
 * @return Nothing.
 * 
 */
void irgrid2_get_image ( irgrid2_t *ctx, uint16_t *frame_data, float *px_matrix );
#ifdef __cplusplus
}
#endif
#endif // IRGRID2_H

/*! @} */ // irgrid2

// ------------------------------------------------------------------------ END
