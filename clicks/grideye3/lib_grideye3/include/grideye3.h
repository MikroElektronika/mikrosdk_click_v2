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
 * @file grideye3.h
 * @brief This file contains API for Grid-EYE 3 Click Driver.
 */

#ifndef GRIDEYE3_H
#define GRIDEYE3_H

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
 * @addtogroup grideye3 Grid-EYE 3 Click Driver
 * @brief API for configuring and manipulating Grid-EYE 3 Click driver.
 * @{
 */

/**
 * @defgroup grideye3_reg Grid-EYE 3 Registers List
 * @brief List of registers of Grid-EYE 3 Click driver.
 */

/**
 * @addtogroup grideye3_reg
 * @{
 */

/**
 * @brief Grid-EYE 3 register list.
 * @details Specified register list of Grid-EYE 3 Click driver.
 */
#define GRIDEYE3_REG_PCLT               0x00
#define GRIDEYE3_REG_RST                0x01
#define GRIDEYE3_REG_FPSC               0x02
#define GRIDEYE3_REG_INTC               0x03
#define GRIDEYE3_REG_STAT               0x04
#define GRIDEYE3_REG_SCLR               0x05
#define GRIDEYE3_REG_AVE                0x07
#define GRIDEYE3_REG_INTHL              0x08
#define GRIDEYE3_REG_INTHH              0x09
#define GRIDEYE3_REG_INTLL              0x0A
#define GRIDEYE3_REG_INTLH              0x0B
#define GRIDEYE3_REG_IHYSL              0x0C
#define GRIDEYE3_REG_IHYSH              0x0D
#define GRIDEYE3_REG_TTHL               0x0E
#define GRIDEYE3_REG_TTHH               0x0F
#define GRIDEYE3_REG_INT0               0x10
#define GRIDEYE3_REG_INT1               0x11
#define GRIDEYE3_REG_INT2               0x12
#define GRIDEYE3_REG_INT3               0x13
#define GRIDEYE3_REG_INT4               0x14
#define GRIDEYE3_REG_INT5               0x15
#define GRIDEYE3_REG_INT6               0x16
#define GRIDEYE3_REG_INT7               0x17
#define GRIDEYE3_REG_AVE_SET            0x1F
#define GRIDEYE3_REG_TO1L               0x80
#define GRIDEYE3_REG_TO1H               0x81

/*! @} */ // grideye3_reg

/**
 * @defgroup grideye3_set Grid-EYE 3 Registers Settings
 * @brief Settings for registers of Grid-EYE 3 Click driver.
 */

/**
 * @addtogroup grideye3_set
 * @{
 */

/**
 * @brief Grid-EYE 3 PCLT register setting.
 * @details Specified setting for PCLT register of Grid-EYE 3 Click driver.
 */
#define GRIDEYE3_PCLT_NORMAL_MODE       0x00
#define GRIDEYE3_PCLT_SLEEP_MODE        0x10

/**
 * @brief Grid-EYE 3 RST register setting.
 * @details Specified setting for RST register of Grid-EYE 3 Click driver.
 */
#define GRIDEYE3_RST_FLAG               0x30
#define GRIDEYE3_RST_INITIAL            0x3F

/**
 * @brief Grid-EYE 3 FPSC register setting.
 * @details Specified setting for FPSC register of Grid-EYE 3 Click driver.
 */
#define GRIDEYE3_FPSC_10FPS             0x00
#define GRIDEYE3_FPSC_1FPS              0x01

/**
 * @brief Grid-EYE 3 INTC register setting.
 * @details Specified setting for INTC register of Grid-EYE 3 Click driver.
 */
#define GRIDEYE3_INTC_INTMOD_DIFF       0x00
#define GRIDEYE3_INTC_INTMOD_ABS        0x02
#define GRIDEYE3_INTC_INTMOD_MASK       0x02
#define GRIDEYE3_INTC_INTEN_INACTIVE    0x00
#define GRIDEYE3_INTC_INTEN_ACTIVE      0x01
#define GRIDEYE3_INTC_INTEN_MASK        0x01

/**
 * @brief Grid-EYE 3 STAT register setting.
 * @details Specified setting for STAT register of Grid-EYE 3 Click driver.
 */
#define GRIDEYE3_STAT_OVF_IRS           0x04
#define GRIDEYE3_STAT_INTF              0x02

/**
 * @brief Grid-EYE 3 AVE register setting.
 * @details Specified setting for AVE register of Grid-EYE 3 Click driver.
 * @note Changing AVE mode is done by setting AVE_SET registers to 0-2 values,
 * then writing to AVE register, and ending with a value 3 write to AVE_SET register. 
 */
#define GRIDEYE3_AVE_MAMOD_OFF          0x00
#define GRIDEYE3_AVE_MAMOD_ON           0x20
#define GRIDEYE3_AVE_SET_0              0x50
#define GRIDEYE3_AVE_SET_1              0x45
#define GRIDEYE3_AVE_SET_2              0x57
#define GRIDEYE3_AVE_SET_3              0x00

/**
 * @brief Grid-EYE 3 data calculation setting.
 * @details Specified setting for data calculation of Grid-EYE 3 Click driver.
 */
#define GRIDEYE3_DATA_SIGN_BIT          0x0800
#define GRIDEYE3_DATA_FILL_SIGN         0xF000
#define GRIDEYE3_DATA_LSB               0.25f
#define GRIDEYE3_NUM_PIXELS             64

/**
 * @brief Grid-EYE 3 device address setting.
 * @details Specified setting for device slave address selection of
 * Grid-EYE 3 Click driver.
 */
#define GRIDEYE3_DEVICE_ADDRESS_0       0x68
#define GRIDEYE3_DEVICE_ADDRESS_1       0x69

/*! @} */ // grideye3_set

/**
 * @defgroup grideye3_map Grid-EYE 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Grid-EYE 3 Click driver.
 */

/**
 * @addtogroup grideye3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Grid-EYE 3 Click to the selected MikroBUS.
 */
#define GRIDEYE3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // grideye3_map
/*! @} */ // grideye3

/**
 * @brief Grid-EYE 3 Click context object.
 * @details Context object definition of Grid-EYE 3 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */
    
    float grid_temp[ GRIDEYE3_NUM_PIXELS ]; /**< 8x8 pixels grid temperature in Celsius. */

} grideye3_t;

/**
 * @brief Grid-EYE 3 Click configuration object.
 * @details Configuration object definition of Grid-EYE 3 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} grideye3_cfg_t;

/**
 * @brief Grid-EYE 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GRIDEYE3_OK = 0,
    GRIDEYE3_ERROR = -1

} grideye3_return_value_t;

/*!
 * @addtogroup grideye3 Grid-EYE 3 Click Driver
 * @brief API for configuring and manipulating Grid-EYE 3 Click driver.
 * @{
 */

/**
 * @brief Grid-EYE 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #grideye3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void grideye3_cfg_setup ( grideye3_cfg_t *cfg );

/**
 * @brief Grid-EYE 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #grideye3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #grideye3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t grideye3_init ( grideye3_t *ctx, grideye3_cfg_t *cfg );

/**
 * @brief Grid-EYE 3 default configuration function.
 * @details This function executes a default configuration of Grid-EYE 3
 * Click board.
 * @param[in] ctx : Click context object.
 * See #grideye3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t grideye3_default_cfg ( grideye3_t *ctx );

/**
 * @brief Grid-EYE 3 write reg bytes function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #grideye3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t grideye3_write_reg_bytes ( grideye3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Grid-EYE 3 write reg byte function.
 * @details This function writes a data byte to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #grideye3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t grideye3_write_reg_byte ( grideye3_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Grid-EYE 3 write reg word function.
 * @details This function writes a data word (LSB first) starting from the selected 
 * register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #grideye3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data word to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t grideye3_write_reg_word ( grideye3_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Grid-EYE 3 read reg bytes function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #grideye3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t grideye3_read_reg_bytes ( grideye3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Grid-EYE 3 read reg byte function.
 * @details This function reads a data byte from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #grideye3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t grideye3_read_reg_byte ( grideye3_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Grid-EYE 3 read reg word function.
 * @details This function reads a data word (LSB first) starting from the selected
 * register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #grideye3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t grideye3_read_reg_word ( grideye3_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Grid-EYE 3 get INT pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #grideye3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t grideye3_get_int_pin ( grideye3_t *ctx );

/**
 * @brief Grid-EYE 3 read grid function.
 * @details This function reads the temperature measurement of an 8x8 pixels grid and stores
 * it in the ctx->grid_temp array.
 * @param[in] ctx : Click context object.
 * See #grideye3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t grideye3_read_grid ( grideye3_t *ctx );

/**
 * @brief Grid-EYE 3 clear status function.
 * @details This function clears the interrupt status flags.
 * @param[in] ctx : Click context object.
 * See #grideye3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t grideye3_clear_status ( grideye3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // GRIDEYE3_H

/*! @} */ // grideye3

// ------------------------------------------------------------------------ END
