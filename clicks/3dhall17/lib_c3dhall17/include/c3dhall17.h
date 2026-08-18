/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file c3dhall17.h
 * @brief This file contains API for 3D Hall 17 Click Driver.
 */

#ifndef C3DHALL17_H
#define C3DHALL17_H

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
 * @addtogroup c3dhall17 3D Hall 17 Click Driver
 * @brief API for configuring and manipulating 3D Hall 17 Click driver.
 * @{
 */

/**
 * @defgroup c3dhall17_reg 3D Hall 17 Registers List
 * @brief List of registers of 3D Hall 17 Click driver.
 */

/**
 * @addtogroup c3dhall17_reg
 * @{
 */

/**
 * @brief 3D Hall 17 register list.
 * @details Specified register list of 3D Hall 17 Click driver.
 */
#define C3DHALL17_REG_BX                    0x00
#define C3DHALL17_REG_BY                    0x01
#define C3DHALL17_REG_BZ                    0x02
#define C3DHALL17_REG_TEMP                  0x03
#define C3DHALL17_REG_BX2Y2                 0x04
#define C3DHALL17_REG_BZ2                   0x05
#define C3DHALL17_REG_TEMP2                 0x06
#define C3DHALL17_REG_RSVD0                 0x00
#define C3DHALL17_REG_MOD1                  0x01
#define C3DHALL17_REG_RSVD2                 0x02
#define C3DHALL17_REG_MOD2                  0x03

/*! @} */ // c3dhall17_reg

/**
 * @defgroup c3dhall17_set 3D Hall 17 Registers Settings
 * @brief Settings for registers of 3D Hall 17 Click driver.
 */

/**
 * @addtogroup c3dhall17_set
 * @{
 */

/**
 * @brief 3D Hall 17 MOD1 register setting.
 * @details Specified setting for MOD1 register of 3D Hall 17 Click driver.
 */
#define C3DHALL17_MOD1_LOW                  0x01
#define C3DHALL17_MOD1_FAST                 0x02
#define C3DHALL17_MOD1_INT                  0x04
#define C3DHALL17_MOD1_WUE                  0x08
#define C3DHALL17_MOD1_IICADDR_MASK         0x30
#define C3DHALL17_MOD1_IICADDR_0            0x00
#define C3DHALL17_MOD1_IICADDR_1            0x10
#define C3DHALL17_MOD1_IICADDR_2            0x20
#define C3DHALL17_MOD1_IICADDR_3            0x30

/**
 * @brief 3D Hall 17 MOD2 register setting.
 * @details Specified setting for MOD2 register of 3D Hall 17 Click driver.
 */
#define C3DHALL17_MOD2_CA                   0x10
#define C3DHALL17_MOD2_LP                   0x40

/**
 * @brief 3D Hall 17 BZ2 register setting.
 * @details Specified setting for BZ2 register of 3D Hall 17 Click driver.
 */
#define C3DHALL17_BZ2_PD_FLAG               0x10

/**
 * @brief 3D Hall 17 operating mode setting.
 * @details Specified setting for operating mode of 3D Hall 17 Click driver.
 */
#define C3DHALL17_OP_MODE1_POWER_DOWN       0x00
#define C3DHALL17_OP_MODE1_ULTRA_LP         0x01
#define C3DHALL17_OP_MODE1_LOW_POWER        0x01
#define C3DHALL17_OP_MODE1_MASTER_CTRL      0x03
#define C3DHALL17_OP_MODE2_DEFAULT          0x00

/**
 * @brief 3D Hall 17 magnetic sensitivity and resolution setting.
 * @details Specified setting for magnetic sensitivity and resolution of 3D Hall 17 Click driver.
 */
#define C3DHALL17_SENS_LSB_PER_GAUSS        1.0f
#define C3DHALL17_TEMP_RES_DEG_PER_LSB      1.0f

/**
 * @brief 3D Hall 17 timeout in milliseconds setting.
 * @details Specified setting for timeout in milliseconds of 3D Hall 17 Click driver.
 */
#define C3DHALL17_TIMEOUT_MS                1000

/**
 * @brief 3D Hall 17 sign extend values setting.
 * @details Specified setting for sign extend values of 3D Hall 17 Click driver.
 */
#define C3DHALL17_BIT_11_MASK               0x0800
#define C3DHALL17_4TH_BYTE_MASK             0xF000

/**
 * @brief 3D Hall 17 write and read length setting.
 * @details Specified setting for write and read length of 3D Hall 17 Click driver.
 */
#define C3DHALL17_WRITE_LEN                 4
#define C3DHALL17_READ_LEN                  7
/**
 * @brief 3D Hall 17 reserved register data setting.
 * @details Specified setting for reserved register data of 3D Hall 17 Click driver.
 */
#define C3DHALL17_RSVD_REG_DATA             0x00

/**
 * @brief 3D Hall 17 device address setting.
 * @details Specified setting for device slave address selection of
 * 3D Hall 17 Click driver.
 */
#define C3DHALL17_DEVICE_ADDRESS            0x5E

/*! @} */ // c3dhall17_set

/**
 * @defgroup c3dhall17_map 3D Hall 17 MikroBUS Map
 * @brief MikroBUS pin mapping of 3D Hall 17 Click driver.
 */

/**
 * @addtogroup c3dhall17_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 3D Hall 17 Click to the selected MikroBUS.
 */
#define C3DHALL17_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en  = MIKROBUS( mikrobus, MIKROBUS_RST ); \

/*! @} */ // c3dhall17_map
/*! @} */ // c3dhall17

/**
 * @brief 3D Hall 17 Click context object.
 * @details Context object definition of 3D Hall 17 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;                           /**< Enable pin. */

    // Modules
    i2c_master_t i2c;                           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                      /**< Device slave address (used for I2C driver). */

} c3dhall17_t;

/**
 * @brief 3D Hall 17 Click configuration object.
 * @details Configuration object definition of 3D Hall 17 Click driver.
 */
typedef struct
{
    pin_name_t scl;                             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;                              /**< Enable pin descriptor. */

    uint32_t   i2c_speed;                       /**< I2C serial speed. */
    uint8_t    i2c_address;                     /**< I2C slave address. */

} c3dhall17_cfg_t;

/**
 * @brief 3D Hall 17 Click measurement data object.
 * @details Measurement data object definition of 3D Hall 17 Click driver.
 */
typedef struct
{
    float x_val;                                /**< Magnetic flux density X-axis [Gauss]. */
    float y_val;                                /**< Magnetic flux density Y-axis [Gauss]. */
    float z_val;                                /**< Magnetic flux density Z-axis [Gauss]. */
    float temp_val;                             /**< Die temperature [degC]. */

} c3dhall17_data_t;

/**
 * @brief 3D Hall 17 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C3DHALL17_OK = 0,
    C3DHALL17_ERROR = -1

} c3dhall17_return_value_t;

/*!
 * @addtogroup c3dhall17 3D Hall 17 Click Driver
 * @brief API for configuring and manipulating 3D Hall 17 Click driver.
 * @{
 */

/**
 * @brief 3D Hall 17 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c3dhall17_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c3dhall17_cfg_setup ( c3dhall17_cfg_t *cfg );

/**
 * @brief 3D Hall 17 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #c3dhall17_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c3dhall17_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall17_init ( c3dhall17_t *ctx, c3dhall17_cfg_t *cfg );

/**
 * @brief 3D Hall 17 default configuration function.
 * @details This function executes a default configuration of 3D Hall 17
 * Click board.
 * @param[in] ctx : Click context object.
 * See #c3dhall17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c3dhall17_default_cfg ( c3dhall17_t *ctx );

/**
 * @brief 3D Hall 17 write registers function.
 * @details This function writes data to all 4 write registers of the device.
 * @param[in] ctx : Click context object.
 * See #c3dhall17_t object definition for detailed explanation.
 * @param[in] data_in : Pointer to the input data buffer.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall17_write_regs ( c3dhall17_t *ctx, uint8_t *data_in );

/**
 * @brief 3D Hall 17 read registers function.
 * @details This function reads all 7 read registers of the device.
 * @param[in] ctx : Click context object.
 * See #c3dhall17_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to the output data buffer.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall17_read_regs ( c3dhall17_t *ctx, uint8_t *data_out );

/**
 * @brief 3D Hall 17 enable device function.
 * @details This function enables the sensor by setting the EN pin high.
 * @param[in] ctx : Click context object.
 * See #c3dhall17_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void c3dhall17_enable_device ( c3dhall17_t *ctx );

/**
 * @brief 3D Hall 17 disable device function.
 * @details This function disables the sensor by setting the EN pin low.
 * @param[in] ctx : Click context object.
 * See #c3dhall17_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void c3dhall17_disable_device ( c3dhall17_t *ctx );

/**
 * @brief 3D Hall 17 set operating mode function.
 * @details This function sets the operating mode of the device by writing
 * all four write registers in a single I2C transaction, as required by the AH4931Q.
 * @param[in] ctx : Click context object.
 * See #c3dhall17_t object definition for detailed explanation.
 * @param[in] mod1 : Value for MOD1 register.
 * See #C3DHALL17_OP_MODE_x macros for detailed explanation.
 * @param[in] mod2 : Value for MOD2 register.
 * See #C3DHALL17_OP_MODE_x macros for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall17_set_op_mode ( c3dhall17_t *ctx, uint8_t mod1, uint8_t mod2 );

/**
 * @brief 3D Hall 17 get data function.
 * @details This function reads and converts the magnetic flux
 * density on all three axes and the die temperature.
 * @param[in] ctx : Click context object.
 * See #c3dhall17_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to the output measurement data structure.
 * See #c3dhall17_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall17_get_data ( c3dhall17_t *ctx, c3dhall17_data_t *data_out );

/**
 * @brief 3D Hall 17 hardware reset function.
 * @details This function performs a hardware reset of the device.
 * @param[in] ctx : Click context object.
 * See #c3dhall17_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void c3dhall17_hw_reset ( c3dhall17_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // C3DHALL17_H

/*! @} */ // c3dhall17

// ------------------------------------------------------------------------ END
