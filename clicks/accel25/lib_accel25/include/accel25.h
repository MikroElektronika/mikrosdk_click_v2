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
 * @file accel25.h
 * @brief This file contains API for Accel 25 Click Driver.
 */

#ifndef ACCEL25_H
#define ACCEL25_H

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
 * @addtogroup accel25 Accel 25 Click Driver
 * @brief API for configuring and manipulating Accel 25 Click driver.
 * @{
 */

/**
 * @defgroup accel25_reg Accel 25 Registers List
 * @brief List of registers of Accel 25 Click driver.
 */

/**
 * @addtogroup accel25_reg
 * @{
 */

/**
 * @brief Accel 25 description register.
 * @details Specified register for description of Accel 25 Click driver.
 */
#define ACCEL25_REG_INT_SRC0            0x00
#define ACCEL25_REG_INT_CLR0            0x00
#define ACCEL25_REG_INT_SRC1            0x01
#define ACCEL25_REG_INT_CLR1            0x01
#define ACCEL25_REG_STATUS              0x02
#define ACCEL25_REG_XOUT_MSB            0x03
#define ACCEL25_REG_XOUT_LSB            0x04
#define ACCEL25_REG_YOUT_MSB            0x05
#define ACCEL25_REG_YOUT_LSB            0x06
#define ACCEL25_REG_ZOUT_MSB            0x07
#define ACCEL25_REG_ZOUT_LSB            0x08
#define ACCEL25_REG_TOUT                0x09
#define ACCEL25_REG_INT_MASK0           0x0A
#define ACCEL25_REG_INT_MASK1           0x0B
#define ACCEL25_REG_DETECTION           0x0C
#define ACCEL25_REG_CONTROL             0x0D
#define ACCEL25_REG_DEVICE_ID           0x0E
#define ACCEL25_REG_WHO_AM_I            0x0F

/*! @} */ // accel25_reg

/**
 * @defgroup accel25_set Accel 25 Registers Settings
 * @brief Settings for registers of Accel 25 Click driver.
 */

/**
 * @addtogroup accel25_set
 * @{
 */

/**
 * @brief Accel 25 description setting.
 * @details Specified setting for description of Accel 25 Click driver.
 */
/**
 * @brief Accel 25 INT_SRC0 register settings.
 * @details Specified settings for INT_SRC0 register of Accel 25 Click driver.
 */
#define ACCEL25_INT_SRC0_CHORZ          0x80
#define ACCEL25_INT_SRC0_CHORXY         0x40
#define ACCEL25_INT_SRC0_SHYM           0x08
#define ACCEL25_INT_SRC0_SHYP           0x04
#define ACCEL25_INT_SRC0_SHXM           0x02
#define ACCEL25_INT_SRC0_SHXP           0x01

/**
 * @brief Accel 25 INT_CLR0 register settings.
 * @details Specified settings for INT_CLR0 register of Accel 25 Click driver.
 */
#define ACCEL25_INT_CLR0_ORZC           0x80
#define ACCEL25_INT_CLR0_ORXYC          0x40
#define ACCEL25_INT_CLR0_SHYMC          0x08
#define ACCEL25_INT_CLR0_SHYPC          0x04
#define ACCEL25_INT_CLR0_SHXMC          0x02
#define ACCEL25_INT_CLR0_SHXPC          0x01
#define ACCEL25_INT_CLR0_ALL            0xCF

/**
 * @brief Accel 25 INT_SRC1 register settings.
 * @details Specified settings for INT_SRC1 register of Accel 25 Click driver.
 */
#define ACCEL25_INT_SRC1_TILT           0x80
#define ACCEL25_INT_SRC1_ORZ            0x40
#define ACCEL25_INT_SRC1_ORXY_X_PLUS    0x00
#define ACCEL25_INT_SRC1_ORXY_Y_PLUS    0x10
#define ACCEL25_INT_SRC1_ORXY_X_MINUS   0x20
#define ACCEL25_INT_SRC1_ORXY_Y_MINUS   0x30
#define ACCEL25_INT_SRC1_ORXY_MASK      0x30
#define ACCEL25_INT_SRC1_DRDY           0x01

/**
 * @brief Accel 25 INT_CLR1 register settings.
 * @details Specified settings for INT_CLR1 register of Accel 25 Click driver.
 */
#define ACCEL25_INT_CLR1_SW_RST         0x10
#define ACCEL25_INT_CLR1_DRDYC          0x01

/**
 * @brief Accel 25 STATUS register settings.
 * @details Specified settings for STATUS register of Accel 25 Click driver.
 */
#define ACCEL25_STATUS_ORD              0x10
#define ACCEL25_STATUS_ORIZ_MSB         0x08
#define ACCEL25_STATUS_ORIZ_LSB         0x04
#define ACCEL25_STATUS_ORIXY_MSB        0x02
#define ACCEL25_STATUS_ORIXY_LSB        0x01

/**
 * @brief Accel 25 INT_MASK0 register settings.
 * @details Specified settings for INT_MASK0 register of Accel 25 Click driver.
 */
#define ACCEL25_INT_MASK0_ORZE          0x80
#define ACCEL25_INT_MASK0_ORXYE         0x40
#define ACCEL25_INT_MASK0_SHYME         0x08
#define ACCEL25_INT_MASK0_SHYPE         0x04
#define ACCEL25_INT_MASK0_SHXME         0x02
#define ACCEL25_INT_MASK0_SHXPE         0x01
#define ACCEL25_INT_MASK0_NONE          0x00
#define ACCEL25_INT_MASK0_ALL           0xCF

/**
 * @brief Accel 25 INT_MASK1 register settings.
 * @details Specified settings for INT_MASK1 register of Accel 25 Click driver.
 */
#define ACCEL25_INT_MASK1_DRDYE         0x01

/**
 * @brief Accel 25 DETECTION register settings.
 * @details Specified settings for DETECTION register of Accel 25 Click driver.
 */
#define ACCEL25_DETECTION_SHM           0x80
#define ACCEL25_DETECTION_SHTH_0p25G    0x00
#define ACCEL25_DETECTION_SHTH_0p5G     0x10
#define ACCEL25_DETECTION_SHTH_0p75G    0x20
#define ACCEL25_DETECTION_SHTH_1G       0x30
#define ACCEL25_DETECTION_SHTH_1p25G    0x40
#define ACCEL25_DETECTION_SHTH_1p5G     0x50
#define ACCEL25_DETECTION_SHTH_1p75G    0x60
#define ACCEL25_DETECTION_SHTH_2G       0x70
#define ACCEL25_DETECTION_SHTH_MASK     0x70
#define ACCEL25_DETECTION_SHC_8         0x00
#define ACCEL25_DETECTION_SHC_16        0x04
#define ACCEL25_DETECTION_SHC_32        0x08
#define ACCEL25_DETECTION_SHC_64        0x0C
#define ACCEL25_DETECTION_SHC_MASK      0x0C
#define ACCEL25_DETECTION_ORC_16        0x00
#define ACCEL25_DETECTION_ORC_32        0x01
#define ACCEL25_DETECTION_ORC_64        0x02
#define ACCEL25_DETECTION_ORC_128       0x03
#define ACCEL25_DETECTION_ORC_MASK      0x03
#define ACCEL25_DETECTION_NONE          0x00

/**
 * @brief Accel 25 CONTROL register settings.
 * @details Specified settings for CONTROL register of Accel 25 Click driver.
 */
#define ACCEL25_CONTROL_FSR_2G          0x00
#define ACCEL25_CONTROL_FSR_4G          0x20
#define ACCEL25_CONTROL_FSR_8G          0x40
#define ACCEL25_CONTROL_FSR_UNDEFINED   0x60
#define ACCEL25_CONTROL_FSR_MASK        0x60
#define ACCEL25_CONTROL_PD              0x01

/**
 * @brief Accel 25 measurement calculation settings.
 * @details Specified settings for measurement calculation of Accel 25 Click driver.
 */
#define ACCEL25_ACCEL_RESOLUTION        2048.0f
#define ACCEL25_TEMP_SENSITIVITY        0.586f
#define ACCEL25_TEMP_NOMINAL            25.0f

/**
 * @brief Accel 25 FSR settings.
 * @details Specified settings for FSR of Accel 25 Click driver.
 */
#define ACCEL25_FSR_2G                  0
#define ACCEL25_FSR_4G                  1
#define ACCEL25_FSR_8G                  2

/**
 * @brief Accel 25 Device ID register value.
 * @details Specified Device ID register value of Accel 25 Click driver.
 */
#define ACCEL25_DEVICE_ID               0x02

/**
 * @brief Accel 25 pin state value.
 * @details Specified pin state value of Accel 25 Click driver.
 */
#define ACCEL25_PIN_STATE_LOW           0x00
#define ACCEL25_PIN_STATE_HIGH          0x01

/**
 * @brief Accel 25 device address setting.
 * @details Specified setting for device slave address selection of
 * Accel 25 Click driver.
 */
#define ACCEL25_DEVICE_ADDRESS          0x15

/*! @} */ // accel25_set

/**
 * @defgroup accel25_map Accel 25 MikroBUS Map
 * @brief MikroBUS pin mapping of Accel 25 Click driver.
 */

/**
 * @addtogroup accel25_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Accel 25 Click to the selected MikroBUS.
 */
#define ACCEL25_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // accel25_map
/*! @} */ // accel25

/**
 * @brief Accel 25 Click context object.
 * @details Context object definition of Accel 25 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin. Reflects the state of the INT bit in the STATUS register. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */
    
    uint8_t fsr_sens;             /**< FSR sensitivity LSB/g. */

} accel25_t;

/**
 * @brief Accel 25 Click configuration object.
 * @details Configuration object definition of Accel 25 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;         /**< Interrupt pin. Reflects the state of the INT bit in the STATUS register. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} accel25_cfg_t;

/**
 * @brief Accel 25 Click data structure.
 * @details Data object definition of Accel 25 Click driver.
 */
typedef struct
{
    float x;            /**< X axis. */
    float y;            /**< Y axis. */
    float z;            /**< Z axis. */
    float temperature;  /**< Temperature. */

} accel25_data_t;

/**
 * @brief Accel 25 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ACCEL25_OK = 0,
    ACCEL25_ERROR = -1

} accel25_return_value_t;

/*!
 * @addtogroup accel25 Accel 25 Click Driver
 * @brief API for configuring and manipulating Accel 25 Click driver.
 * @{
 */

/**
 * @brief Accel 25 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #accel25_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void accel25_cfg_setup ( accel25_cfg_t *cfg );

/**
 * @brief Accel 25 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #accel25_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #accel25_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel25_init ( accel25_t *ctx, accel25_cfg_t *cfg );

/**
 * @brief Accel 25 default configuration function.
 * @details This function executes a default configuration of Accel 25
 * Click board.
 * @param[in] ctx : Click context object.
 * See #accel25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t accel25_default_cfg ( accel25_t *ctx );

/**
 * @brief Accel 25 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel25_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel25_generic_write ( accel25_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 25 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel25_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel25_generic_read ( accel25_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 25 write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel25_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel25_write_register ( accel25_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Accel 25 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel25_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel25_read_register ( accel25_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Accel 25 check communication function.
 * @details This function checks the communication by reading and verifying the who am I register.
 * @param[in] ctx : Click context object.
 * See #accel25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel25_check_communication ( accel25_t *ctx );

/**
 * @brief Accel 25 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #accel25_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t accel25_get_int_pin ( accel25_t *ctx );

/**
 * @brief Accel 25 soft reset function.
 * @details This function performs the software reset by setting the SW RST bit.
 * @param[in] ctx : Click context object.
 * See #accel25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel25_soft_reset ( accel25_t *ctx );

/**
 * @brief Accel 25 set full scale range function.
 * @details This function sets the full scale range resolution.
 * @param[in] ctx : Click context object.
 * See #accel25_t object definition for detailed explanation.
 * @param[in] fsr : Full-scale range @li @c 0 - 2G,
 *                                   @li @c 1 - 4G,
 *                                   @li @c 2 - 8G.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel25_set_full_scale_range ( accel25_t *ctx, uint8_t fsr );

/**
 * @brief Accel 25 read data function.
 * @details This function checks the data ready bit, clears it, and then reads the accel
 * (X, Y, Z) and temperature measurements.
 * @param[in] ctx : Click context object.
 * See #accel25_t object definition for detailed explanation.
 * @param[out] data_out : Output data read.
 * See #accel25_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel25_read_data ( accel25_t *ctx, accel25_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // ACCEL25_H

/*! @} */ // accel25

// ------------------------------------------------------------------------ END
