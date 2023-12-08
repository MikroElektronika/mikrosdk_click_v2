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
 * @file lightmixsens.h
 * @brief This file contains API for Light mix sens Click Driver.
 */

#ifndef LIGHTMIXSENS_H
#define LIGHTMIXSENS_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup lightmixsens Light mix sens Click Driver
 * @brief API for configuring and manipulating Light mix sens Click driver.
 * @{
 */

/**
 * @defgroup lightmixsens_reg Light mix sens Registers List
 * @brief List of registers of Light mix sens Click driver.
 */

/**
 * @addtogroup lightmixsens_reg
 * @{
 */

/**
 * @brief Light mix sens description register.
 * @details Specified register for description of Light mix sens Click driver.
 */
#define LIGHTMIXSENS_REG_ENABLE                  0x80
#define LIGHTMIXSENS_REG_ATIME                   0x81
#define LIGHTMIXSENS_REG_PTIME                   0x82
#define LIGHTMIXSENS_REG_WTIME                   0x83
#define LIGHTMIXSENS_REG_AILT                    0x84
#define LIGHTMIXSENS_REG_AIHT                    0x86
#define LIGHTMIXSENS_REG_PILT                    0x88
#define LIGHTMIXSENS_REG_PIHT                    0x8A
#define LIGHTMIXSENS_REG_PERS                    0x8C
#define LIGHTMIXSENS_REG_CFG0                    0x8D
#define LIGHTMIXSENS_REG_PCFG0                   0x8E
#define LIGHTMIXSENS_REG_PCFG1                   0x8F
#define LIGHTMIXSENS_REG_CFG1                    0x90
#define LIGHTMIXSENS_REG_REVID                   0x91
#define LIGHTMIXSENS_REG_ID                      0x92
#define LIGHTMIXSENS_REG_STATUS                  0x93
#define LIGHTMIXSENS_REG_CDATA                   0x94
#define LIGHTMIXSENS_REG_RDATA                   0x96
#define LIGHTMIXSENS_REG_GDATA_IRDATA            0x98
#define LIGHTMIXSENS_REG_BDATA                   0x9A
#define LIGHTMIXSENS_REG_PDATA                   0x9C
#define LIGHTMIXSENS_REG_REVID2                  0x9E
#define LIGHTMIXSENS_REG_CFG2                    0x9F
#define LIGHTMIXSENS_REG_CFG3                    0xAB
#define LIGHTMIXSENS_REG_POFFSET                 0xC0
#define LIGHTMIXSENS_REG_AZCFG                   0xD6
#define LIGHTMIXSENS_REG_CALIB                   0xD7
#define LIGHTMIXSENS_REG_CALIBCFG                0xD9
#define LIGHTMIXSENS_REG_CALIBSTAT               0xDC
#define LIGHTMIXSENS_REG_INTENAB                 0xDD

/*! @} */ // lightmixsens_reg

/**
 * @defgroup lightmixsens_set Light mix sens Registers Settings
 * @brief Settings for registers of Light mix sens Click driver.
 */

/**
 * @addtogroup lightmixsens_set
 * @{
 */

/**
 * @brief Light mix sens description setting.
 * @details Specified setting for description of Light mix sens Click driver.
 */
#define LIGHTMIXSENS_ATIME_WTIME_CONST           2.8
#define LIGHTMIXSENS_PTIME_CONST                 88
#define LIGHTMIXSENS_WTIME_INCR_FACTOR           12

#define LIGHTMIXSENS_ENABLE_WAIT                 0x08
#define LIGHTMIXSENS_ENABLE_PROX                 0x04
#define LIGHTMIXSENS_ENABLE_ALS                  0x02
#define LIGHTMIXSENS_ENABLE_OSC                  0x01
#define LIGHTMIXSENS_DISABLE_ALL                 0x00

#define LIGHTMIXSENS_PCFG1_GAIN_1x               0x00
#define LIGHTMIXSENS_PCFG1_GAIN_2x               0x40
#define LIGHTMIXSENS_PCFG1_GAIN_4x               0x80
#define LIGHTMIXSENS_PCFG1_GAIN_8x               0xC0
#define LIGHTMIXSENS_PCFG1_DRIVE_6mA             0x00
#define LIGHTMIXSENS_PCFG1_DRIVE_12mA            0x01
#define LIGHTMIXSENS_PCFG1_DRIVE_18mA            0x02
#define LIGHTMIXSENS_PCFG1_DRIVE_192mA           0x1F

#define LIGHTMIXSENS_CFG0_WLONG                  0x04

#define LIGHTMIXSENS_CFG1_IR_TO_GREEN            0x08
#define LIGHTMIXSENS_CFG1_AGAIN_1x               0x00
#define LIGHTMIXSENS_CFG1_AGAIN_4x               0x01
#define LIGHTMIXSENS_CFG1_AGAIN_16x              0x02
#define LIGHTMIXSENS_CFG1_AGAIN_64x              0x03

#define LIGHTMIXSENS_CFG2_AGAINMAX               0x10
#define LIGHTMIXSENS_CFG2_AGAINL                 0x04

#define LIGHTMIXSENS_CFG3_INT_READ_CLEAR         0x80
#define LIGHTMIXSENS_CFG3_SAI                    0x10

/**
 * @brief Light mix sens flag bits.
 * @details Specified flag bits values of Light mix sens Click driver.
 */
#define LIGHTMIXSENS_FLAG_ASAT                   0x80
#define LIGHTMIXSENS_FLAG_PSAT                   0x40
#define LIGHTMIXSENS_FLAG_PINT                   0x20
#define LIGHTMIXSENS_FLAG_AINT                   0x10
#define LIGHTMIXSENS_FLAG_CINT                   0x08
#define LIGHTMIXSENS_FLAG_PSAT_REFL              0x02
#define LIGHTMIXSENS_FLAG_PSAT_AMB               0x01

/**
 * @brief Light mix sens calibration settings.
 * @details Specified calibration settings of Light mix sens Click driver.
 */
#define LIGHTMIXSENS_CALIB_ELECTRICAL            0x20
#define LIGHTMIXSENS_CALIB_OFFSET_START          0x01

#define LIGHTMIXSENS_CALIBCFG_PROX_TARGET_0      0x00
#define LIGHTMIXSENS_CALIBCFG_PROX_TARGET_1      0x20
#define LIGHTMIXSENS_CALIBCFG_PROX_TARGET_3      0x40
#define LIGHTMIXSENS_CALIBCFG_PROX_TARGET_7      0x60
#define LIGHTMIXSENS_CALIBCFG_PROX_TARGET_15     0x80
#define LIGHTMIXSENS_CALIBCFG_PROX_TARGET_31     0xA0
#define LIGHTMIXSENS_CALIBCFG_PROX_TARGET_63     0xC0
#define LIGHTMIXSENS_CALIBCFG_PROX_TARGET_127    0xE0
#define LIGHTMIXSENS_CALIBCFG_AUTO_OFFSET_ADJ    0x08
#define LIGHTMIXSENS_CALIBCFG_PROX_AVG_DIS       0x00
#define LIGHTMIXSENS_CALIBCFG_PROX_AVG_2         0x01
#define LIGHTMIXSENS_CALIBCFG_PROX_AVG_4         0x02
#define LIGHTMIXSENS_CALIBCFG_PROX_AVG_8         0x03
#define LIGHTMIXSENS_CALIBCFG_PROX_AVG_16        0x04
#define LIGHTMIXSENS_CALIBCFG_PROX_AVG_32        0x05
#define LIGHTMIXSENS_CALIBCFG_PROX_AVG_64        0x06
#define LIGHTMIXSENS_CALIBCFG_PROX_AVG_128       0x07

#define LIGHTMIXSENS_CALIBSTAT_FINISHED          0x01
#define LIGHTMIXSENS_DUMMY_DATA                  0x00

/**
 * @brief Light mix sens device address setting.
 * @details Specified setting for device slave address selection of
 * Light mix sens Click driver.
 */
#define LIGHTMIXSENS_SET_DEV_ADDR  0x39

/*! @} */ // lightmixsens_set

/**
 * @defgroup lightmixsens_map Light mix sens MikroBUS Map
 * @brief MikroBUS pin mapping of Light mix sens Click driver.
 */

/**
 * @addtogroup lightmixsens_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Light mix sens Click to the selected MikroBUS.
 */
#define LIGHTMIXSENS_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // lightmixsens_map
/*! @} */ // lightmixsens

/**
 * @brief Light mix sens Click context object.
 * @details Context object definition of Light mix sens Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  int_pin;              /**< Interrupt. */

    // Modules
    i2c_master_t i2c;                   /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;              /**< Device slave address (used for I2C driver). */

} lightmixsens_t;

/**
 * @brief Light mix sens Click configuration object.
 * @details Configuration object definition of Light mix sens Click driver.
 */
typedef struct
{
    pin_name_t  scl;                    /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                    /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  int_pin;                /**< Interrupt. */

    uint32_t  i2c_speed;                /**< I2C serial speed. */
    uint8_t   i2c_address;              /**< I2C slave address. */

} lightmixsens_cfg_t;

/**
 * @brief Light mix sens Click data object.
 * @details Data object definition of Light mix sens Click driver.
 */
typedef struct
{
    uint16_t lightmixsens_cdata;
    uint16_t lightmixsens_rdata;
    uint16_t lightmixsens_gdata;
    uint16_t lightmixsens_bdata;
    uint8_t lightmixsens_pdata;
} lightmixsens_data_obj;

/**
 * @brief Light mix sens Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   LIGHTMIXSENS_OK = 0,
   LIGHTMIXSENS_ERROR = -1

} lightmixsens_return_value_t;

/*!
 * @addtogroup lightmixsens Light mix sens Click Driver
 * @brief API for configuring and manipulating Light mix sens Click driver.
 * @{
 */

/**
 * @brief Light mix sens configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lightmixsens_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lightmixsens_cfg_setup ( lightmixsens_cfg_t *cfg );

/**
 * @brief Light mix sens initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #lightmixsens_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lightmixsens_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t lightmixsens_init ( lightmixsens_t *ctx, lightmixsens_cfg_t *cfg );

/**
 * @brief Light mix sens default configuration function.
 * @details This function executes a default configuration of Light mix sens
 * click board.
 * @param[in] ctx : Click context object.
 * See #lightmixsens_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void lightmixsens_default_cfg ( lightmixsens_t *ctx );

/**
 * @brief Light mix sens I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightmixsens_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t lightmixsens_generic_write ( lightmixsens_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Light mix sens I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightmixsens_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t lightmixsens_generic_read ( lightmixsens_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );


/**
 * @brief Generic Write Byte function.
 * @details This function writes data byte to the selected register.
 * @param[in] ctx : Click context object.
 * See #lightmixsens_t object definition for detailed explanation.
 * @param[in] reg_addr : Address where data be written.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * 
 * See #err_t definition for detailed explanation.
 */
err_t lightmixsens_write_byte ( lightmixsens_t *ctx, uint8_t reg_addr, uint8_t data_in );

/**
 * @brief Generic Write Word function.
 * @details This function writes 16-bit data starting from the selected 
 * register to the next one.
 * @param[in] ctx : Click context object.
 * See #lightmixsens_t object definition for detailed explanation. 
 * @param[in] reg_addr : Start address where data be written.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * 
 * See #err_t definition for detailed explanation.
 */
err_t lightmixsens_write_word ( lightmixsens_t *ctx, uint8_t reg_addr, uint16_t data_in );

/**
 * @brief Generic Read Byte function.
 * @details This function reads data byte from the selected register.
 * @param[in] ctx : Click context object.
 * See #lightmixsens_t object definition for detailed explanation. 
 * @param[in] reg_addr : Address which from data be read.
 * @param[out] data_out : Buffer where data be placed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * 
 * See #err_t definition for detailed explanation.
 */
err_t lightmixsens_read_byte ( lightmixsens_t *ctx, uint8_t reg_addr, uint8_t *data_out );

/**
 * @brief Generic Read Word function.
 * @details This function reads 16-bit data starting from the selected 
 * register to the next one.
 * @param[in] ctx : Click context object.
 * See #lightmixsens_t object definition for detailed explanation. 
 * @param[in] reg_addr : Start address which from data be read.
 * @param[out] data_out : Buffer where data be placed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * 
 * See #err_t definition for detailed explanation.
 */
err_t lightmixsens_read_word ( lightmixsens_t *ctx, uint8_t reg_addr, uint16_t *data_out );

/**
 * @brief Get Status function.
 * @details This function allows the desired bit flags to be checked from 
 * the STATUS register.
 * @param[in] ctx : Click context object.
 * See #lightmixsens_t object definition for detailed explanation. 
 * @param[in] flag_mask : Bit flag selection to include/mask the desired bits.
 * @param[in] status : Buffer where masked status byte be placed.
 * @return Nothing.
 */
void lightmixsens_get_status ( lightmixsens_t *ctx, uint8_t flag_mask, uint8_t *status );

/**
 * @brief Switch IR To Green Channel function.
 * @details This function switches the IR light to be measured in the Green
 * channel (GDATA) register.
 * @param[out] ctx : Click context object.
 * See #lightmixsens_t object definition for detailed explanation.
 * @return Nothing.
 */
void lightmixsens_switch_ir_to_green ( lightmixsens_t *ctx );

/**
 * @brief Switch IR To Proximity function.
 * @details This function switches the IR light to measure proximity in the
 * PDATA register.
 * @param[out] ctx : Click context object.
 * See #lightmixsens_t object definition for detailed explanation.
 * @return Nothing.
 */
void lightmixsens_switch_ir_to_prox ( lightmixsens_t *ctx );

/**
 * @brief Wait ALS/Color Intregration Time Done function.
 * @details This function performs a delay time determined by the ALS/Color 
 * integration time (ATIME) register.
 * @param[in] ctx : Click context object.
 * See #lightmixsens_t object definition for detailed explanation.
 * @return Nothing.
 */
void lightmixsens_wait_atime ( lightmixsens_t *ctx );

/**
 * @brief Wait Proximity Sample Time Done function.
 * @details This function performs a delay time determined by the 
 * Proximity sample time (PTIME) register.
 * @param[in] ctx : Click context object.
 * See #lightmixsens_t object definition for detailed explanation.
 * @return Nothing.
 */
void lightmixsens_wait_ptime ( lightmixsens_t *ctx );

/**
 * @brief Wait WTIME + WLONG Done function.
 * @details This function performs a delay time determined by the 
 * WTIME and WLONG registers.
 * @param[in] ctx : Click context object.
 * See #lightmixsens_t object definition for detailed explanation.
 * @return Nothing.
 */
void lightmixsens_wait_wtime ( lightmixsens_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // LIGHTMIXSENS_H

/*! @} */ // lightmixsens

// ------------------------------------------------------------------------ END
