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
 * @file compass8.h
 * @brief This file contains API for Compass 8 Click Driver.
 */

#ifndef COMPASS8_H
#define COMPASS8_H

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
 * @addtogroup compass8 Compass 8 Click Driver
 * @brief API for configuring and manipulating Compass 8 Click driver.
 * @{
 */

/**
 * @defgroup compass8_reg Compass 8 Registers List
 * @brief List of registers of Compass 8 Click driver.
 */

/**
 * @addtogroup compass8_reg
 * @{
 */

/**
 * @brief Compass 8 description register.
 * @details Specified register for description of Compass 8 Click driver.
 */
#define COMPASS8_REG_WIA1              0x00
#define COMPASS8_REG_WIA2              0x01
#define COMPASS8_REG_RSV1              0x02
#define COMPASS8_REG_RSV2              0x03
#define COMPASS8_REG_ST1               0x10
#define COMPASS8_REG_HXH               0x11
#define COMPASS8_REG_HXL               0x12
#define COMPASS8_REG_HYH               0x13
#define COMPASS8_REG_HYL               0x14
#define COMPASS8_REG_HZH               0x15
#define COMPASS8_REG_HZL               0x16
#define COMPASS8_REG_TMPS              0x17
#define COMPASS8_REG_ST2               0x18
#define COMPASS8_REG_CNTL1             0x30
#define COMPASS8_REG_CNTL2             0x31
#define COMPASS8_REG_CNTL3             0x32
#define COMPASS8_REG_TS1               0x33
#define COMPASS8_REG_TS2               0x34

/*! @} */ // compass8_reg

/**
 * @defgroup compass8_set Compass 8 Registers Settings
 * @brief Settings for registers of Compass 8 Click driver.
 */

/**
 * @addtogroup compass8_set
 * @{
 */

/**
 * @brief Compass 8 status 1 register bitmask.
 * @details Status 1 register setting for description of Compass 8 Click driver.
 */
#define COMPASS8_ST1_DATA_NORMAL       0x00
#define COMPASS8_ST1_DATA_READY        0x01
#define COMPASS8_ST1_DOR_NORMAL        0x00
#define COMPASS8_ST1_DOR_OVR           0x02

/**
 * @brief Compass 8 control 1 register bitmask.
 * @details Control 1 register setting for description of Compass 8 Click driver.
 */
#define COMPASS8_CNTL1_WM_STEP_1       0x00
#define COMPASS8_CNTL1_WM_STEP_2       0x01
#define COMPASS8_CNTL1_WM_STEP_3       0x02
#define COMPASS8_CNTL1_ITS_OFF         0x00
#define COMPASS8_CNTL1_ITS_LOW         0x20
#define COMPASS8_CNTL1_ITS_HIGH        0x40
#define COMPASS8_CNTL1_ITS_HIGH1       0x60

/**
 * @brief Compass 8 control 2 register bitmask.
 * @details Control 2 register setting for description of Compass 8 Click driver.
 */
#define COMPASS8_CNTL2_MODE_PD         0x00
#define COMPASS8_CNTL2_MODE_SNGL       0x01
#define COMPASS8_CNTL2_MODE_CONT1      0x02
#define COMPASS8_CNTL2_MODE_CONT2      0x04
#define COMPASS8_CNTL2_MODE_CONT3      0x05
#define COMPASS8_CNTL2_MODE_CONT4      0x08
#define COMPASS8_CNTL2_MODE_CONT5      0x0E
#define COMPASS8_CNTL2_MODE_BITMASK    0x0F
#define COMPASS8_CNTL2_MODE_ST         0x10
#define COMPASS8_CNTL2_IBIP_DIS        0x00
#define COMPASS8_CNTL2_IBIP_EN         0x20
#define COMPASS8_CNTL2_SDR_DIS         0x00
#define COMPASS8_CNTL2_SDR_EN          0x40
#define COMPASS8_CNTL2_FIFO_DIS        0x00
#define COMPASS8_CNTL2_FIFO_EN         0x80

/**
 * @brief Compass 8 control 3 register bitmask.
 * @details Control 3 register setting for description of Compass 8 Click driver.
 */
#define COMPASS8_CNTL3_SRST_NORMAL     0x00
#define COMPASS8_CNTL3_SRST_RESET      0x01

/**
 * @brief Compass 8 device information data.
 * @details Device information data for description of Compass 8 Click driver.
 */
#define COMPASS8_COMPANY_ID            0x48
#define COMPASS8_DEVICE_ID             0x0E

/**
 * @brief Compass 8 magnetic flux density calculation data.
 * @details Magnetic flux density data of Compass 8 Click driver.
 */
#define COMPASS8_MAG_AXIS_SENS         0.125f

/**
 * @brief Compass 8 device address setting.
 * @details Specified setting for device slave address selection of
 * Compass 8 Click driver.
 */
#define COMPASS8_DEVICE_ADDRESS        0x0E

/*! @} */ // compass8_set

/**
 * @defgroup compass8_map Compass 8 MikroBUS Map
 * @brief MikroBUS pin mapping of Compass 8 Click driver.
 */

/**
 * @addtogroup compass8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Compass 8 Click to the selected MikroBUS.
 */
#define COMPASS8_MAP_MIKROBUS( cfg, mikrobus )    \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en  = MIKROBUS( mikrobus, MIKROBUS_RST )

/*! @} */ // compass8_map
/*! @} */ // compass8

/**
 * @brief Compass 8 Click context object.
 * @details Context object definition of Compass 8 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;       /**< Enable pin. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

} compass8_t;

/**
 * @brief Compass 8 Click configuration object.
 * @details Configuration object definition of Compass 8 Click driver.
 */
typedef struct
{
    pin_name_t scl;    /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;    /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;     /**< Enable pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} compass8_cfg_t;

/**
 * @brief Compass 8 Click axes magnetic flux density data.
 * @details Axes data object definition of Compass 8 Click driver.
 */
typedef struct
{
    float x;    /**< X-axis. */
    float y;    /**< Y-axis. */
    float z;    /**< Z-axis. */

} compass8_axes_t;

/**
 * @brief Compass 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    COMPASS8_OK = 0,
    COMPASS8_ERROR = -1

} compass8_return_value_t;

/*!
 * @addtogroup compass8 Compass 8 Click Driver
 * @brief API for configuring and manipulating Compass 8 Click driver.
 * @{
 */

/**
 * @brief Compass 8 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #compass8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void compass8_cfg_setup ( compass8_cfg_t *cfg );

/**
 * @brief Compass 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #compass8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #compass8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass8_init ( compass8_t *ctx, compass8_cfg_t *cfg );

/**
 * @brief Compass 8 default configuration function.
 * @details This function executes a default configuration of Compass 8
 * Click board.
 * @param[in] ctx : Click context object.
 * See #compass8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t compass8_default_cfg ( compass8_t *ctx );

/**
 * @brief Compass 8 device enable function.
 * @details This function enabled the device.
 * @param[in] ctx : Click context object.
 * See #compass8_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void compass8_device_enable ( compass8_t *ctx );

/**
 * @brief Compass 8 device disable function.
 * @details This function disable the device.
 * @param[in] ctx : Click context object.
 * See #compass8_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void compass8_device_disable ( compass8_t *ctx );

/**
 * @brief Compass 8 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #compass8_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass8_generic_write ( compass8_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Compass 8 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #compass8_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass8_generic_read ( compass8_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Compass 8 get company ID function.
 * @details This function reads company ID register by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #compass8_t object definition for detailed explanation.
 * @param[out] company_id : Company ID [0x48].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass8_get_company_id ( compass8_t *ctx, uint8_t *company_id );

/**
 * @brief Compass 8 get device ID function.
 * @details This function reads device ID register by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #compass8_t object definition for detailed explanation.
 * @param[out] device_id : Device ID [0x0E].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass8_get_device_id ( compass8_t *ctx, uint8_t *device_id );

/**
 * @brief Compass 8 wait data ready function.
 * @details This function waits until data is ready by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #compass8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass8_wait_data_ready ( compass8_t *ctx );

/**
 * @brief Compass 8 get mag raw data function.
 * @details This function reads the magnetic measurement raw data 
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #compass8_t object definition for detailed explanation.
 * @param[out] axis_x : Measurement data of magnetic sensor X-axis.
 * @param[out] axis_y : Measurement data of magnetic sensor Y-axis.
 * @param[out] axis_z : Measurement data of magnetic sensor Z-axis.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass8_get_raw_data ( compass8_t *ctx, int16_t *axis_x, int16_t *axis_y, int16_t *axis_z );

/**
 * @brief Compass 8 get magnetic data function.
 * @details This function reads the raw magnetic sensor measurement data 
 * and calculates magnetic flux density [microTesla] using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #compass8_t object definition for detailed explanation.
 * @param[out] axis : Magnetic flux density [microTesla].
 * See #compass8_axes_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass8_get_magnetic_data ( compass8_t *ctx, compass8_axes_t *axis );

/**
 * @brief Compass 8 set operation mode function.
 * @details This function sets the desired sensor operation mode
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #compass8_t object definition for detailed explanation.
 * @param[in] op_mode : Operation mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass8_set_operation_mode ( compass8_t *ctx, uint8_t op_mode );

/**
 * @brief Compass 8 get operation mode function.
 * @details This function reads the current operation mode
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #compass8_t object definition for detailed explanation.
 * @param[out] op_mode : Operation mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass8_get_operation_mode ( compass8_t *ctx, uint8_t *op_mode );

/**
 * @brief Compass 8 set control function.
 * @details This function sets the data of the desired control register data
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #compass8_t object definition for detailed explanation.
 * @param[in] ctrl_reg : Control register selector.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass8_set_control ( compass8_t *ctx, uint8_t ctrl_reg, uint8_t data_in );

/**
 * @brief Compass 8 soft reset function.
 * @details This function performs software reset
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #compass8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass8_sw_reset ( compass8_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // COMPASS8_H

/*! @} */ // compass8

// ------------------------------------------------------------------------ END
