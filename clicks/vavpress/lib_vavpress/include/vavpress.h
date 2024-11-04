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
 * @file vavpress.h
 * @brief This file contains API for VAV Press Click Driver.
 */

#ifndef VAVPRESS_H
#define VAVPRESS_H

#ifdef __cplusplus
extern "C"{
#endif

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
    #if MikroCCoreVersion >= 1
        #include "delays.h"
    #endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup vavpress VAV Press Click Driver
 * @brief API for configuring and manipulating VAV Press Click driver.
 * @{
 */

/**
 * @defgroup vavpress_set VAV Press Registers Settings
 * @brief Settings for registers of VAV Press Click driver.
 */

/**
 * @addtogroup vavpress_set
 * @{
 */

/**
 * @brief VAV Press description command set.
 * @details Specified command set for description of VAV Press Click driver.
 */
#define VAVPRESS_SET_CMD_RESET_FIRMWARE                   0x11
#define VAVPRESS_SET_CMD_START_PRESSURE_CONVERSION        0x21
#define VAVPRESS_SET_CMD_RETRIEVE_ELECTRONIC_SIGNATURE    0x23

/**
 * @brief VAV Press device address setting.
 * @details Specified setting for device slave address selection of
 * VAV Press Click driver.
 */
#define VAVPRESS_SET_DEV_ADDR_0                           0x5C
#define VAVPRESS_SET_DEV_ADDR_1                           0x5D
#define VAVPRESS_SET_DEV_ADDR_2                           0x5E
#define VAVPRESS_SET_DEV_ADDR_3                           0x5F

/*! @} */ // vavpress_set

/**
 * @defgroup vavpress_map VAV Press MikroBUS Map
 * @brief MikroBUS pin mapping of VAV Press Click driver.
 */

/**
 * @addtogroup vavpress_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of VAV Press Click to the selected MikroBUS.
 */
#define VAVPRESS_MAP_MIKROBUS( cfg, mikrobus )    \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // vavpress_map
/*! @} */ // vavpress

/**
 * @brief VAV Press Click context object.
 * @details Context object definition of VAV Press Click driver.
 */
typedef struct
{
    // Modules

    i2c_master_t i2c;         /**< I2C driver object. */
                              
    // I2C slave address      
                              
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} vavpress_t;

/**
 * @brief VAV Press Click configuration object.
 * @details Configuration object definition of VAV Press Click driver.
 */
typedef struct
{
    pin_name_t  scl;          /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;          /**< Bidirectional data pin descriptor for I2C driver. */
    
    uint32_t  i2c_speed;      /**< I2C serial speed. */
    uint8_t   i2c_address;    /**< I2C slave address. */

} vavpress_cfg_t;

/**
 * @brief VAV Press Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   VAVPRESS_OK = 0,
   VAVPRESS_ERROR = -1

} vavpress_return_value_t;

/**
 * @brief VAV Press Click electronic signature.
 * @details Electronic signature of VAV Press Click driver.
 */
typedef struct
{
   float firmware_version;
   char part_number[ 12 ];
   char lot_number[ 7 ];
   uint16_t pressure_range;
   char output_type;
   uint16_t scale_factor;
   char calibration_id[ 2 ];
   uint8_t week_number;
   uint8_t year_number;
   uint16_t sequence_number;

} vavpress_el_signature_data_t;

/**
 * @brief VAV Press Click sensor parameter data.
 * @details Sensor parameter data of VAV Press Click driver.
 */
typedef struct
{
   uint16_t scale_factor_temp;
   uint16_t scale_factor_press;
   uint16_t readout_at_known_temperature;
   float known_temperature_c;

} vavpress_sensor_param_data_t;

/*!
 * @addtogroup vavpress VAV Press Click Driver
 * @brief API for configuring and manipulating VAV Press Click driver.
 * @{
 */

/**
 * @brief VAV Press configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #vavpress_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @endcode
 */
void vavpress_cfg_setup ( vavpress_cfg_t *cfg );

/**
 * @brief VAV Press initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #vavpress_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #vavpress_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t vavpress_init ( vavpress_t *ctx, vavpress_cfg_t *cfg );

/**
 * @brief VAV Press default configuration function.
 * @details This function executes a default configuration of VAV Press
 * Click board.
 * @param[in] ctx : Click context object.
 * See #vavpress_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 *
 * @endcode
 */
err_t vavpress_default_cfg ( vavpress_t *ctx );

/**
 * @brief VAV Press set command function.
 * @details This function set a desire command 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vavpress_t object definition for detailed explanation.
 * @param[in] cmd : 
 *         @li @c 0x11 - Reset firmware ( W ),
 *         @li @c 0x21 - Start pressure conversion ( W/R ).
 *         @li @c 0x23 - Retrieve electronic signature ( W/R ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t vavpress_set_command ( vavpress_t *ctx, uint8_t cmd );

/**
 * @brief VAV Press I2C writing function.
 * @details This function writes a desired number of data bytes 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vavpress_t object definition for detailed explanation.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t vavpress_generic_write ( vavpress_t *ctx, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief VAV Press I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vavpress_t object definition for detailed explanation.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t vavpress_generic_read ( vavpress_t *ctx, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief VAV Press set default sensor parameter function.
 * @details This function set default sensor parameter data of the 
 * LMIS025BB3, digital low differential pressure sensors on the 
 * Vav Press Click board™.
 * @param[in] ctx : Click context object.
 * See #vavpress_t object definition for detailed explanation.
 * @param[in] vavpress_sensor_param_data_t : Pointer to the memory location of the structure where data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t vavpress_set_default_sensor_param ( vavpress_t *ctx, vavpress_sensor_param_data_t *param_data );

/**
 * @brief VAV Press get data readout function.
 * @details This function get differential pressure and temperature data of the 
 * LMIS025BB3, digital low differential pressure sensors on the 
 * Vav Press Click board™.
 * @param[in] ctx : Click context object.
 * See #vavpress_t object definition for detailed explanation.
 * @param[out] press_data : Pressure signed 15-bit value.
 * @param[out] temp_data : Temperature signed 16-bit value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t vavpress_get_readout_data ( vavpress_t *ctx, int16_t *press_data, int16_t *temp_data );

/**
 * @brief VAV Press get differential pressure and temperature function.
 * @details This function get differential pressure [ Pa ] and temperature [ degree Celsius ] data of the 
 * LMIS025BB3, digital low differential pressure sensors on the 
 * Vav Press Click board™.
 * @param[in] ctx : Click context object.
 * See #vavpress_t object definition for detailed explanation.
 * @param[in] param_data : Pointer to the memory location of the structure where data be stored.
 * @param[out] diff_press : Pressure [ Pa ].
 * @param[out] temperature : Temperature [ degree Celsius ].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t vavpress_get_dif_press_and_temp ( vavpress_t *ctx, vavpress_sensor_param_data_t *param_data, float *diff_press, float *temperature );

/**
 * @brief VAV Press retrieve electronic signature function.
 * @details This function retrieve the electronic signature data of the 
 * LMIS025BB3, digital low differential pressure sensors on the 
 * Vav Press Click board™.
 * @param[in] ctx : Click context object.
 * See #vavpress_t object definition for detailed explanation.
 * @param[out] vavpress_el_signature_data_t : Pointer to the memory location of the structure where data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t vavpress_retrieve_electronic_signature ( vavpress_t *ctx, vavpress_el_signature_data_t *el_signature_data );


#ifdef __cplusplus
}
#endif
#endif // VAVPRESS_H

/*! @} */ // vavpress

// ------------------------------------------------------------------------ END
