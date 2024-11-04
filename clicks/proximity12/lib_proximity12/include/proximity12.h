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
 * @file proximity12.h
 * @brief This file contains API for Proximity 12 Click Driver.
 */

#ifndef PROXIMITY12_H
#define PROXIMITY12_H

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
 * @addtogroup proximity12 Proximity 12 Click Driver
 * @brief API for configuring and manipulating Proximity 12 Click driver.
 * @{
 */

/**
 * @defgroup proximity12_reg Proximity 12 Registers List
 * @brief List of registers of Proximity 12 Click driver.
 */

/**
 * @addtogroup proximity12_reg
 * @{
 */

/**
 * @brief Proximity 12 registers map.
 * @details Specified register map of Proximity 12 Click driver.
 */
#define PROXIMITY12_REG_AILT                        0x2E
#define PROXIMITY12_REG_AIHT                        0x31
#define PROXIMITY12_REG_PILT0                       0x34
#define PROXIMITY12_REG_PIHT0                       0x36
#define PROXIMITY12_REG_PILT1                       0x38
#define PROXIMITY12_REG_PIHT1                       0x3A
#define PROXIMITY12_REG_PILTR                       0x3C
#define PROXIMITY12_REG_PIHTR                       0x3E
#define PROXIMITY12_REG_FD_CFG0                     0x40
#define PROXIMITY12_REG_FD_CFG1                     0x41
#define PROXIMITY12_REG_FD_CFG2                     0x42
#define PROXIMITY12_REG_FD_CFG3                     0x43
#define PROXIMITY12_REG_FD_CFG4                     0x44
#define PROXIMITY12_REG_FD_CFG5                     0x45
#define PROXIMITY12_REG_FD_CFG6                     0x46
#define PROXIMITY12_REG_FD_CFG7                     0x47
#define PROXIMITY12_REG_FD_CFG8                     0x48
#define PROXIMITY12_REG_SYNC_DELAY                  0x4F
#define PROXIMITY12_REG_VSYNC_CFG0                  0x53
#define PROXIMITY12_REG_VSYNC_CFG1                  0x54
#define PROXIMITY12_REG_VSYNC_CFG2                  0x56
#define PROXIMITY12_REG_VSYNC_CFG3                  0x57
#define PROXIMITY12_REG_CALIB                       0x69
#define PROXIMITY12_REG_CALIBCFG0                   0x6A
#define PROXIMITY12_REG_CALIBCFG1                   0x6B
#define PROXIMITY12_REG_CALIBCFG2                   0x6C
#define PROXIMITY12_REG_CALIBSTAT                   0x6D
#define PROXIMITY12_REG_ENABLE                      0x80
#define PROXIMITY12_REG_MEAS_MODE0                  0x81
#define PROXIMITY12_REG_MEAS_MODE1                  0x82
#define PROXIMITY12_REG_TRIGGER_MODE                0x83
#define PROXIMITY12_REG_ATIME                       0x84
#define PROXIMITY12_REG_ASTEP                       0x85
#define PROXIMITY12_REG_PTIME                       0x87
#define PROXIMITY12_REG_WTIPE                       0x88
#define PROXIMITY12_REG_MOD_GAIN_0_1                0x89
#define PROXIMITY12_REG_MOD_GAIN_2_3                0x8A
#define PROXIMITY12_REG_MOD_GAIN_4_5                0x8B
#define PROXIMITY12_REG_MOD_GAIN_6_7                0x8C
#define PROXIMITY12_REG_AGC_ENABLE                  0x8D
#define PROXIMITY12_REG_AUXID                       0x90
#define PROXIMITY12_REG_REVID                       0x91
#define PROXIMITY12_REG_ID                          0x92
#define PROXIMITY12_REG_CFG0                        0x93
#define PROXIMITY12_REG_CFG3                        0x96
#define PROXIMITY12_REG_CFG4                        0x97
#define PROXIMITY12_REG_PERS                        0x9A
#define PROXIMITY12_REG_CFG8                        0x9B
#define PROXIMITY12_REG_CFG9                        0x9C
#define PROXIMITY12_REG_CFG10                       0x9D
#define PROXIMITY12_REG_CFG11                       0x9E
#define PROXIMITY12_REG_CFG12                       0x9F
#define PROXIMITY12_REG_AZ_CONFIG                   0xA4
#define PROXIMITY12_REG_CFG20                       0xA7
#define PROXIMITY12_REG_PCFG1                       0xAA
#define PROXIMITY12_REG_PCFG2                       0xAB
#define PROXIMITY12_REG_PCFG3                       0xAC
#define PROXIMITY12_REG_PCFG4                       0xAD
#define PROXIMITY12_REG_PCFG5                       0xAE
#define PROXIMITY12_REG_PCFG6                       0xAF
#define PROXIMITY12_REG_PCFG7                       0xB0
#define PROXIMITY12_REG_POFFSET0                    0xB1
#define PROXIMITY12_REG_PXAVG                       0xB3
#define PROXIMITY12_REG_PBSLN                       0xB5
#define PROXIMITY12_REG_STATUS                      0xB7
#define PROXIMITY12_REG_STATUS2                     0xB8
#define PROXIMITY12_REG_STATUS3                     0xB9
#define PROXIMITY12_REG_STATUS4                     0xBA
#define PROXIMITY12_REG_STATUS5                     0xBB
#define PROXIMITY12_REG_STATUS7                     0xBD
#define PROXIMITY12_REG_STATUS8                     0xBE
#define PROXIMITY12_REG_STATUS9                     0xBF
#define PROXIMITY12_REG_ASTATUS                     0xC0
#define PROXIMITY12_REG_ADATA0                      0xC1
#define PROXIMITY12_REG_ADATA1                      0xC4
#define PROXIMITY12_REG_ADATA2                      0xC7
#define PROXIMITY12_REG_ADATA3                      0xCA
#define PROXIMITY12_REG_ADATA4                      0xCD
#define PROXIMITY12_REG_ADATA5                      0xD0
#define PROXIMITY12_REG_ADATA6                      0xD3
#define PROXIMITY12_REG_ADATA7                      0xD6
#define PROXIMITY12_REG_PSTATUS                     0xD9
#define PROXIMITY12_REG_PDATA0                      0xDA
#define PROXIMITY12_REG_PDATA1                      0xDC
#define PROXIMITY12_REG_PDATAR                      0xDE
#define PROXIMITY12_REG_GPIO                        0xF2
#define PROXIMITY12_REG_AGC_GAIN_MAX                0xF4
#define PROXIMITY12_REG_INTENAB                     0xF5
#define PROXIMITY12_REG_CONTROL                     0xF6
#define PROXIMITY12_REG_POFFSET1                    0xF7
#define PROXIMITY12_REG_FIFO_MAP                    0xF9
#define PROXIMITY12_REG_FIFO_MAP2                   0xFA
#define PROXIMITY12_REG_FIFO_STATUS                 0xFB
#define PROXIMITY12_REG_FDATA                       0xFC

/*! @} */ // proximity12_reg

/**
 * @defgroup proximity12_set Proximity 12 Registers Settings
 * @brief Settings for registers of Proximity 12 Click driver.
 */

/**
 * @addtogroup proximity12_set
 * @{
 */

/**
 * @brief Proximity 12 ENABLE register setting.
 * @details Specified setting for ENABLE register of Proximity 12 Click driver.
 */
#define PROXIMITY12_ENABLE_FLICKER                  0x40
#define PROXIMITY12_ENABLE_ALS                      0x10
#define PROXIMITY12_ENABLE_PROX                     0x08
#define PROXIMITY12_ENABLE_POWER                    0x01

/**
 * @brief Proximity 12 MEAS_MODE0 register setting.
 * @details Specified setting for MEAS_MODE0 register of Proximity 12 Click driver.
 */
#define PROXIMITY12_MEAS_MODE0_CL_APF_VSYNC         0x40
#define PROXIMITY12_MEAS_MODE0_EN_PROX_DIODE        0x0C
#define PROXIMITY12_MEAS_MODE0_ALS_SET_A_DIODE      0x00
#define PROXIMITY12_MEAS_MODE0_ALS_SET_B_DIODE      0x02
#define PROXIMITY12_MEAS_MODE0_EN_ALS_DIODE         0x01

/**
 * @brief Proximity 12 modulator gain setting.
 * @details Specified setting for modulator gain of Proximity 12 Click driver.
 */
#define PROXIMITY12_AGC_DISABLE_ALL_MOD             0x00
#define PROXIMITY12_AGC_ENABLE_ALL_MOD              0xFF
#define PROXIMITY12_AGC_ENABLE_MOD_7                0x80
#define PROXIMITY12_AGC_ENABLE_MOD_6                0x40
#define PROXIMITY12_AGC_ENABLE_MOD_5                0x20
#define PROXIMITY12_AGC_ENABLE_MOD_4                0x10
#define PROXIMITY12_AGC_ENABLE_MOD_3                0x08
#define PROXIMITY12_AGC_ENABLE_MOD_2                0x04
#define PROXIMITY12_AGC_ENABLE_MOD_1                0x02
#define PROXIMITY12_AGC_ENABLE_MOD_0                0x01
#define PROXIMITY12_MOD_GAIN_2X                     0x00
#define PROXIMITY12_MOD_GAIN_4X                     0x01
#define PROXIMITY12_MOD_GAIN_8X                     0x02
#define PROXIMITY12_MOD_GAIN_16X                    0x03
#define PROXIMITY12_MOD_GAIN_32X                    0x04
#define PROXIMITY12_MOD_GAIN_64X                    0x05
#define PROXIMITY12_MOD_GAIN_128X                   0x06
#define PROXIMITY12_MOD_GAIN_256X                   0x07
#define PROXIMITY12_MOD_GAIN_512X                   0x08
#define PROXIMITY12_MOD_GAIN_1024X                  0x09
#define PROXIMITY12_MOD_GAIN_2048X                  0x0A
#define PROXIMITY12_MOD_GAIN_4096X                  0x0B

/**
 * @brief Proximity 12 proximity filter setting.
 * @details Specified setting for proximity filter of Proximity 12 Click driver.
 */
#define PROXIMITY12_PROX_FILTER_ENABLE              0x08
#define PROXIMITY12_PROX_FILTER_1                   0x00
#define PROXIMITY12_PROX_FILTER_2                   0x01
#define PROXIMITY12_PROX_FILTER_3                   0x02
#define PROXIMITY12_PROX_FILTER_4                   0x03
#define PROXIMITY12_PROX_FILTER_5                   0x04
#define PROXIMITY12_PROX_FILTER_6                   0x05
#define PROXIMITY12_PROX_FILTER_7                   0x06
#define PROXIMITY12_PROX_FILTER_8                   0x07

/**
 * @brief Proximity 12 LED sink setting.
 * @details Specified setting for LED sink of Proximity 12 Click driver.
 */
#define PROXIMITY12_ISINK_SCALER_0p5                0x00
#define PROXIMITY12_ISINK_SCALER_1                  0x01
#define PROXIMITY12_ISINK_SCALER_1p5                0x02
#define PROXIMITY12_ISINK_SCALER_2                  0x03
#define PROXIMITY12_ISINK_CURRENT_0mA               0x00
#define PROXIMITY12_ISINK_CURRENT_1mA               0x01
#define PROXIMITY12_ISINK_CURRENT_2mA               0x02
#define PROXIMITY12_ISINK_CURRENT_3mA               0x03
#define PROXIMITY12_ISINK_CURRENT_4mA               0x04
#define PROXIMITY12_ISINK_CURRENT_5mA               0x05
#define PROXIMITY12_ISINK_CURRENT_6mA               0x06
#define PROXIMITY12_ISINK_CURRENT_7mA               0x07

/**
 * @brief Proximity 12 proximity gain setting.
 * @details Specified setting for proximity gain of Proximity 12 Click driver.
 */
#define PROXIMITY12_PROX_GAIN_1X                    0x00
#define PROXIMITY12_PROX_GAIN_2X                    0x01
#define PROXIMITY12_PROX_GAIN_4X                    0x02
#define PROXIMITY12_PROX_GAIN_8X                    0x03

/**
 * @brief Proximity 12 ID registers values.
 * @details Specified values of ID registers of Proximity 12 Click driver.
 */
#define PROXIMITY12_AUXID                           0x03
#define PROXIMITY12_REVID                           0x13
#define PROXIMITY12_ID                              0x40

/**
 * @brief Proximity 12 device address setting.
 * @details Specified setting for device slave address selection of
 * Proximity 12 Click driver.
 */
#define PROXIMITY12_SET_DEV_ADDR                    0x39

/*! @} */ // proximity12_set

/**
 * @defgroup proximity12_map Proximity 12 MikroBUS Map
 * @brief MikroBUS pin mapping of Proximity 12 Click driver.
 */

/**
 * @addtogroup proximity12_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Proximity 12 Click to the selected MikroBUS.
 */
#define PROXIMITY12_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.syn = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.gp1 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.gp2 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // proximity12_map
/*! @} */ // proximity12

/**
 * @brief Proximity 12 Click context object.
 * @details Context object definition of Proximity 12 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  syn;       /**< VSYNC pin. */
    digital_out_t  gp1;       /**< GPIO 1 pin. */
    digital_out_t  gp2;       /**< GPIO 2 pin. */

    // Input pins
    digital_in_t  int_pin;    /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} proximity12_t;

/**
 * @brief Proximity 12 Click configuration object.
 * @details Configuration object definition of Proximity 12 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  syn;        /**< VSYNC pin. */
    pin_name_t  gp1;        /**< GPIO 1 pin. */
    pin_name_t  gp2;        /**< GPIO 2 pin. */
    pin_name_t  int_pin;    /**< Interrupt pin. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} proximity12_cfg_t;

/**
 * @brief Proximity 12 ALS data object.
 * @details ALS data object definition of Proximity 12 Click driver.
 */
typedef struct
{
    uint32_t clear;
    uint32_t red;
    uint32_t green;
    uint32_t blue;
    uint32_t leakage;
    uint32_t wideband;
    uint32_t ir1;
    uint32_t ir2;

} proximity12_als_data_t;

/**
 * @brief Proximity 12 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PROXIMITY12_OK = 0,
    PROXIMITY12_ERROR = -1

} proximity12_return_value_t;

/*!
 * @addtogroup proximity12 Proximity 12 Click Driver
 * @brief API for configuring and manipulating Proximity 12 Click driver.
 * @{
 */

/**
 * @brief Proximity 12 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #proximity12_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void proximity12_cfg_setup ( proximity12_cfg_t *cfg );

/**
 * @brief Proximity 12 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #proximity12_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #proximity12_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity12_init ( proximity12_t *ctx, proximity12_cfg_t *cfg );

/**
 * @brief Proximity 12 default configuration function.
 * @details This function executes a default configuration of Proximity 12
 * Click board.
 * @param[in] ctx : Click context object.
 * See #proximity12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t proximity12_default_cfg ( proximity12_t *ctx );

/**
 * @brief Proximity 12 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity12_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity12_generic_write ( proximity12_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Proximity 12 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity12_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity12_generic_read ( proximity12_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Proximity 12 check device ID function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #proximity12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity12_check_device_id ( proximity12_t *ctx );

/**
 * @brief Proximity 12 read proximity function.
 * @details This function reads the raw proximity value measured by the Click board.
 * @param[in] ctx : Click context object.
 * See #proximity12_t object definition for detailed explanation.
 * @param[out] prox_data : Proximity value read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity12_read_proximity ( proximity12_t *ctx, uint16_t *prox_data );

/**
 * @brief Proximity 12 read als data function.
 * @details This function reads all als data measured by the Click board.
 * @param[in] ctx : Click context object.
 * See #proximity12_t object definition for detailed explanation.
 * @param[out] als : Als data structure.
 * See #proximity12_als_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity12_read_als ( proximity12_t *ctx, proximity12_als_data_t *als );

/**
 * @brief Proximity 12 wait atime function.
 * @details This function waits for als integration time which is set in the proper registers.
 * @param[in] ctx : Click context object.
 * See #proximity12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity12_wait_atime ( proximity12_t *ctx );

/**
 * @brief Proximity 12 wait ptime function.
 * @details This function waits for proximity sample time which is set in the proper registers.
 * @param[in] ctx : Click context object.
 * See #proximity12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity12_wait_ptime ( proximity12_t *ctx );

/**
 * @brief Proximity 12 enable function.
 * @details This function enables desired sensors.
 * @param[in] ctx : Click context object.
 * See #proximity12_t object definition for detailed explanation.
 * @param[in] en_mask : Enable mask, refer to ENABLE register settings for more information.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity12_enable ( proximity12_t *ctx, uint8_t en_mask );

/**
 * @brief Proximity 12 enable measurement function.
 * @details This function enables desired diodes for a measurement.
 * @param[in] ctx : Click context object.
 * See #proximity12_t object definition for detailed explanation.
 * @param[in] en_mask : Enable mask, refer to MEAS_MODE0 register settings for more information.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity12_enable_measurement ( proximity12_t *ctx, uint8_t en_mask );

/**
 * @brief Proximity 12 proximity calibration function.
 * @details This function performs a proximity calibration and waits until the calibration is finished.
 * @param[in] ctx : Click context object.
 * See #proximity12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity12_proximity_calibration ( proximity12_t *ctx );

/**
 * @brief Proximity 12 set proximity filter function.
 * @details This function sets the proximity filter by setting the PCFG1 register.
 * @param[in] ctx : Click context object.
 * See #proximity12_t object definition for detailed explanation.
 * @param[in] filter : Filter mask [0-15].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity12_set_proximity_filter ( proximity12_t *ctx, uint8_t filter );

/**
 * @brief Proximity 12 set led isink function.
 * @details This function sets the LEDs sink scaler and current values.
 * @param[in] ctx : Click context object.
 * See #proximity12_t object definition for detailed explanation.
 * @param[in] scaler : Scaler mask [0-3].
 * @param[in] current : Current mask [0-7].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This functions affects both PCFG2 and PCFG3 registers.
 */
err_t proximity12_set_led_isink ( proximity12_t *ctx, uint8_t scaler, uint8_t current );

/**
 * @brief Proximity 12 set proximity gain function.
 * @details This function sets the proximity gain by setting the PCFG4 register.
 * @param[in] ctx : Click context object.
 * See #proximity12_t object definition for detailed explanation.
 * @param[in] gain : Gain mask [0-3].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This functions affects both PGAINs in PCFG4 register.
 */
err_t proximity12_set_proximity_gain ( proximity12_t *ctx, uint8_t gain );

/**
 * @brief Proximity 12 set agc modulator gain function.
 * @details This function sets the agc modulator gains.
 * @param[in] ctx : Click context object.
 * See #proximity12_t object definition for detailed explanation.
 * @param[in] en_mask : Enable mask, refer to AGC_ENABLE register settings for more information.
 * @param[in] gain : Gain mask [0-11].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This functions affects all modulator gain registers.
 */
err_t proximity12_set_agc_mod_gain ( proximity12_t *ctx, uint8_t en_mask, uint8_t gain );

/**
 * @brief Proximity 12 set syn pin state function.
 * @details This function sets the syn pin state.
 * @param[in] ctx : Click context object.
 * See #proximity12_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void proximity12_set_syn_pin ( proximity12_t *ctx, uint8_t state );

/**
 * @brief Proximity 12 set gp1 pin state function.
 * @details This function sets the gp1 pin state.
 * @param[in] ctx : Click context object.
 * See #proximity12_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void proximity12_set_gp1_pin ( proximity12_t *ctx, uint8_t state );

/**
 * @brief Proximity 12 set gp2 pin state function.
 * @details This function sets the gp2 pin state.
 * @param[in] ctx : Click context object.
 * See #proximity12_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void proximity12_set_gp2_pin ( proximity12_t *ctx, uint8_t state );

/**
 * @brief Proximity 12 get int pin state function.
 * @details This function returns the int pin logic state.
 * @param[in] ctx : Click context object.
 * See #proximity12_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t proximity12_get_int_pin ( proximity12_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // PROXIMITY12_H

/*! @} */ // proximity12

// ------------------------------------------------------------------------ END
