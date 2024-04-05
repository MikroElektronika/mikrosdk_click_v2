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
 * @file compass5.h
 * @brief This file contains API for Compass 5 Click Driver.
 */

#ifndef COMPASS5_H
#define COMPASS5_H

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
 * @addtogroup compass5 Compass 5 Click Driver
 * @brief API for configuring and manipulating Compass 5 Click driver.
 * @{
 */

/**
 * @defgroup compass5_reg Compass 5 Registers List
 * @brief List of registers of Compass 5 Click driver.
 */

/**
 * @addtogroup compass5_reg
 * @{
 */

/**
 * @brief Compass 5 description register.
 * @details Specified register for description of Compass 5 Click driver.
 */

/**
 * @brief Compass 5 Who I am register.
 * @details Specified Who I am register of Compass 5 Click driver.
 */
#define COMPASS5_DEVICE_ID_NUM                  0X0C
#define COMPASS5_COMPANI_ID_NUM                 0X48
#define COMPASS5_COMPANI_ID                     0x00
#define COMPASS5_DEVICE_ID                      0x01

/**
 * @brief Compass 5 register map for status.
 * @details Specified register map for status of Compass 5 Click driver.
 */
#define COMPASS5_DATA_STATUS_1                  0x10
                                    
/**
 * @brief Compass 5 register map for X, Y, Z axis.
 * @details Specified register map for X, Y, Z axis of Compass 5 Click driver.
 */
#define COMPASS5_X_AXIS_DATA_L                  0x11
#define COMPASS5_X_AXIS_DATA_H                  0x12
#define COMPASS5_Y_AXIS_DATA_L                  0x13
#define COMPASS5_Y_AXIS_DATA_H                  0x14
#define COMPASS5_Z_AXIS_DATA_L                  0x15
#define COMPASS5_Z_AXIS_DATA_H                  0x16
  
/**
 * @brief Compass 5 register map for DUMMY and STATUS.
 * @details Specified register map for DUMMY and STATUS of Compass 5 Click driver.
 */
#define COMPASS5_DUMMY_TMPS                     0x17
#define COMPASS5_DATA_STATUS_2                  0x18

  /**
 * @brief Compass 5 register map for DUMMY and CONTROL SETTINGS.
 * @details Specified register map for DUMMY and CONTROL SETTINGS of Compass 5 Click driver.
 */
#define COMPASS5_DUMMY_CNTL1                    0x30
#define COMPASS5_CONTROL_2_SETTINGS             0x31
#define COMPASS5_CONTROL_3_SETTINGS             0x32
#define COMPASS5_TEST_TS1                       0x33
#define COMPASS5_TEST_TS2                       0x34

/*! @} */ // compass5_reg

/**
 * @defgroup compass5_set Compass 5 Registers Settings
 * @brief Settings for registers of Compass 5 Click driver.
 */

/**
 * @addtogroup compass5_set
 * @{
 */

/**
 * @brief Compass 5 description setting operation mode.
 * @details Specified setting operation mode for description of Compass 5 Click driver.
 */
#define COMPASS5_MODE_POWER_DOWN                0x00
#define COMPASS5_MODE_SINGLE_MEASUREMENT        0x01
#define COMPASS5_MODE_CON_MEASUREMENT_10HZ      0x02
#define COMPASS5_MODE_CON_MEASUREMENT_20HZ      0x04
#define COMPASS5_MODE_CON_MEASUREMENT_50HZ      0x06
#define COMPASS5_MODE_CON_MEASUREMENT_100HZ     0x08
#define COMPASS5_MODE_SELF_TEST                 0x10

/**
 * @brief Compass 5 registers for setting.
 * @details Specified registers for setting of Compass 5 Click driver.
 */
#define COMPASS5_SRST_BIT                       0x01
#define COMPASS5_HOFL_BIT                       0x08
#define COMPASS5_DOR_BIT                        0x02
#define COMPASS5_DRDY_BIT                       0x01

/**
 * @brief Compass 5 registers settings for data status.
 * @details Specified registers settings for data status of Compass 5 Click driver.
 */
#define COMPASS5_DATA_NO_READY                  0x00
#define COMPASS5_DATA_READY                     0x01

/**
 * @brief Compass 5 registers settings bit mask.
 * @details Specified registers settings for bit mask of Compass 5 Click driver.
 */
#define COMPASS5_BIT_MASK_BIT0                  0x01

/**
 * @brief Compass 5 device address setting.
 * @details Specified setting for device slave address selection of
 * Compass 5 Click driver.
 */
#define COMPASS5_SET_DEV_ADDR  0x0C

/*! @} */ // compass5_set

/**
 * @defgroup compass5_map Compass 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Compass 5 Click driver.
 */

/**
 * @addtogroup compass5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Compass 5 Click to the selected MikroBUS.
 */
#define COMPASS5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \

/*! @} */ // compass5_map
/*! @} */ // compass5

/**
 * @brief Compass 5 Click context object.
 * @details Context object definition of Compass 5 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;                 /**< I2C driver object. */
                                   
    // I2C slave address           
    uint8_t slave_address;            /**< Device slave address (used for I2C driver). */

} compass5_t;

/**
 * @brief Compass 5 Click configuration object.
 * @details Configuration object definition of Compass 5 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                  /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                  /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;              /**< I2C serial speed. */
    uint8_t   i2c_address;            /**< I2C slave address. */

} compass5_cfg_t;

/**
 * @brief Compass 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   COMPASS5_OK = 0,
   COMPASS5_ERROR = -1

} compass5_return_value_t;

/*!
 * @addtogroup compass5 Compass 5 Click Driver
 * @brief API for configuring and manipulating Compass 5 Click driver.
 * @{
 */

/**
 * @brief Compass 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #compass5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 * 
 */
void compass5_cfg_setup ( compass5_cfg_t *cfg );

/**
 * @brief Compass 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #compass5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #compass5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 */
err_t compass5_init ( compass5_t *ctx, compass5_cfg_t *cfg );

/**
 * @brief Compass 5 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #compass5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 */
err_t compass5_generic_write ( compass5_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Compass 5 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #compass5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 */
err_t compass5_generic_read ( compass5_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Compass 5 write byte function.
 * @details This function write byte.
 * @param[out] ctx : Click configuration structure.
 * See #compass5_t object definition for detailed explanation.
 * @param[in] reg : 8-bit register address.
 * @param[in] tx_data : 8-bit write data.
 * @return Nothing.
 * @note None.
 *
 */
void compass5_write_byte ( compass5_t *ctx, uint8_t reg, uint8_t tx_data );

/**
 * @brief Compass 5 read 1 byte function.
 * @details This function read 1 byte.
 * @param[out] ctx : Click configuration structure.
 * See #compass5_t object definition for detailed explanation.
 * @param[out] reg : 8-bit register address.
 * @return Returns the read data.
 * @note None.
 *
 */
uint8_t compass5_read_byte ( compass5_t *ctx, uint8_t reg );

/**
 * @brief Compass 5 software reset function.
 * @details This function for software reset.
 * @param[out] ctx : Click configuration structure.
 * See #compass5_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 *
 */
void compass5_sw_reset ( compass5_t *ctx );

/**
 * @brief Compass 5 get ID function.
 * @details This function for get ID.
 * @param[out] ctx : Click configuration structure.
 * See #compass5_t object definition for detailed explanation.
 * @param[out] company_id : Company ID - WIA1.
 * @param[out] device_id : Device ID - WIA2.
 * @return Nothing.
 * @note None.
 * 
 */
void compass5_get_id ( compass5_t *ctx, uint8_t *company_id, uint8_t *device_id );

/**
 * @brief Compass 5 check data ready function.
 * @details This function for check data ready.
 * @param[out] ctx : Click configuration structure.
 * See #compass5_t object definition for detailed explanation.
 * @return Error data.
 * @note None.
 *
 */
uint8_t compass5_check_data_ready ( compass5_t *ctx );

/**
 * @brief Compass 5 check data overrun function.
 * @details This function for check data overrun.
 * @param[out] ctx : Click configuration structure.
 * See #compass5_t object definition for detailed explanation.
 * @return dor data.
 * @note None.
 *
 */
uint8_t compass5_check_data_overrun ( compass5_t *ctx );

/**
 * @brief Compass 5 set operation mode function.
 * @details This function for set operation mode.
 * @param[out] ctx : Click configuration structure.
 * See #compass5_t object definition for detailed explanation.
 * @param[in] op_mode  : Operation mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 *
 */
uint8_t compass5_set_operation_mode ( compass5_t *ctx, uint8_t op_mode );

/**
 * @brief Compass 5 get operation mode function.
 * @details This function for get operation mode.
 * @param[out] ctx : Click configuration structure.
 * See #compass5_t object definition for detailed explanation.
 * @return Operation mode.
 * @note None.
 *
 */
uint8_t compass5_get_operation_mode ( compass5_t *ctx );

/**
 * @brief Compass 5 full measurement axis function.
 * @details This function for full measurement axis.
 * @param[out] ctx : Click configuration structure.
 * See #compass5_t object definition for detailed explanation.
 * @param[out] axis_x : x-axis.
 * @param[out] axis_y : y-axis.
 * @param[out] axis_z : z-axis.
 * @return Nothing.
 * @note None.
 *
 */
void compass5_measurement_axis ( compass5_t *ctx, int16_t *axis_x, int16_t *axis_y, int16_t *axis_z );

/**
 * @brief Compass 5 full measurement axis function.
 * @details This function for full measurement axis.
 * @param[out] ctx : Click configuration structure.
 * See #compass5_t object definition for detailed explanation.
 * @param[out] axis_x : x-axis.
 * @param[out] axis_y : y-axis.
 * @param[out] axis_z : z-axis.
 * @return Nothing.
 * @note None.
 *
 */
void compass5_get_mag_data ( compass5_t *ctx, int16_t *axis_x, int16_t *axis_y, int16_t *axis_z );
#ifdef __cplusplus
}
#endif
#endif // COMPASS5_H

/*! @} */ // compass5

// ------------------------------------------------------------------------ END
