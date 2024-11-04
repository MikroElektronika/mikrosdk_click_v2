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
 * @file ambient14.h
 * @brief This file contains API for Ambient 14 Click Driver.
 */

#ifndef AMBIENT14_H
#define AMBIENT14_H

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
 * @addtogroup ambient14 Ambient 14 Click Driver
 * @brief API for configuring and manipulating Ambient 14 Click driver.
 * @{
 */

/**
 * @defgroup ambient14_reg Ambient 14 Registers List
 * @brief List of registers of Ambient 14 Click driver.
 */

/**
 * @addtogroup ambient14_reg
 * @{
 */

/**
 * @brief Ambient 14 register list.
 * @details Specified register list of Ambient 14 Click driver.
 */
#define AMBIENT14_REG_ENABLE                        0x80
#define AMBIENT14_REG_ATIME                         0x81
#define AMBIENT14_REG_PRATE                         0x82
#define AMBIENT14_REG_AWTIME                        0x83
#define AMBIENT14_REG_AILTL                         0x84
#define AMBIENT14_REG_AILTH                         0x85
#define AMBIENT14_REG_AIHTL                         0x86
#define AMBIENT14_REG_AIHTH                         0x87
#define AMBIENT14_REG_PILTL                         0x88
#define AMBIENT14_REG_PILTH                         0x89
#define AMBIENT14_REG_PIHTL                         0x8A
#define AMBIENT14_REG_PIHTH                         0x8B
#define AMBIENT14_REG_PERS                          0x8C
#define AMBIENT14_REG_CFG0                          0x8D
#define AMBIENT14_REG_PCFG0                         0x8E
#define AMBIENT14_REG_PCFG1                         0x8F
#define AMBIENT14_REG_PCFG2                         0x90
#define AMBIENT14_REG_CFG1                          0x91
#define AMBIENT14_REG_REVID                         0x92
#define AMBIENT14_REG_ID                            0x93
#define AMBIENT14_REG_STATUS                        0x94
#define AMBIENT14_REG_ALSL                          0x95
#define AMBIENT14_REG_ALSH                          0x96
#define AMBIENT14_REG_IRL                           0x97
#define AMBIENT14_REG_IRH                           0x98
#define AMBIENT14_REG_PDATAL                        0x99
#define AMBIENT14_REG_PDATAH                        0x9A
#define AMBIENT14_REG_REVID2                        0xA6
#define AMBIENT14_REG_SOFTRST                       0xA8
#define AMBIENT14_REG_PWTIME                        0xA9
#define AMBIENT14_REG_CFG8                          0xAA
#define AMBIENT14_REG_CFG3                          0xAB
#define AMBIENT14_REG_CFG6                          0xAE
#define AMBIENT14_REG_POFFSETL                      0xC0
#define AMBIENT14_REG_POFFSETH                      0xC1
#define AMBIENT14_REG_CALIB                         0xD7
#define AMBIENT14_REG_CALIB_OFFSET                  0xD8
#define AMBIENT14_REG_CALIBCFG                      0xD9
#define AMBIENT14_REG_CALIBSTAT                     0xDC
#define AMBIENT14_REG_INTENAB                       0xDD
#define AMBIENT14_REG_FAC_L                         0xE6
#define AMBIENT14_REG_FAC_H                         0xE7
#define AMBIENT14_REG_TEST9                         0xF9

/*! @} */ // ambient14_reg

/**
 * @defgroup ambient14_set Ambient 14 Registers Settings
 * @brief Settings for registers of Ambient 14 Click driver.
 */

/**
 * @addtogroup ambient14_set
 * @{
 */

/**
 * @brief Ambient 14 ENABLE register setting.
 * @details Specified setting for ENABLE register of Ambient 14 Click driver.
 */
#define AMBIENT14_ENABLE_PWEN                       0x10
#define AMBIENT14_ENABLE_AWEN                       0x08
#define AMBIENT14_ENABLE_PEN                        0x04
#define AMBIENT14_ENABLE_AEN                        0x02
#define AMBIENT14_ENABLE_PON                        0x01

/**
 * @brief Ambient 14 SOFTRST register setting.
 * @details Specified setting for SOFTRST register of Ambient 14 Click driver.
 */
#define AMBIENT14_SOFT_RESET                        0x01

/**
 * @brief Ambient 14 PCFG0 register setting.
 * @details Specified setting for PCFG0 register of Ambient 14 Click driver.
 */
#define AMBIENT14_PCFG0_PGAIN1_1X                   0x00
#define AMBIENT14_PCFG0_PGAIN1_2X                   0x40
#define AMBIENT14_PCFG0_PGAIN1_4X                   0x80
#define AMBIENT14_PCFG0_PGAIN1_8X                   0xC0
#define AMBIENT14_PCFG0_PGAIN1_MASK                 0xC0
#define AMBIENT14_PCFG0_PPULSE_MIN                  0x00
#define AMBIENT14_PCFG0_PPULSE_DEFAULT              0x01
#define AMBIENT14_PCFG0_PPULSE_MAX                  0x3F
#define AMBIENT14_PCFG0_PPULSE_MASK                 0x3F

/**
 * @brief Ambient 14 PCFG1 register setting.
 * @details Specified setting for PCFG1 register of Ambient 14 Click driver.
 */
#define AMBIENT14_PCFG1_PPULSE_LENH_DEFAULT         0x00
#define AMBIENT14_PCFG1_PPULSE_LENH_MASK            0xC0
#define AMBIENT14_PCFG1_RESERVED                    0x30
#define AMBIENT14_PCFG1_PLDRIVE_7_MA                0x05
#define AMBIENT14_PCFG1_PLDRIVE_8_MA                0x06
#define AMBIENT14_PCFG1_PLDRIVE_9_MA                0x07
#define AMBIENT14_PCFG1_PLDRIVE_10_MA               0x08
#define AMBIENT14_PCFG1_PLDRIVE_MASK                0x0F

/**
 * @brief Ambient 14 PCFG2 register setting.
 * @details Specified setting for PCFG2 register of Ambient 14 Click driver.
 */
#define AMBIENT14_PCFG2_PPULSE_LENL_DEFAULT         0x20
#define AMBIENT14_PCFG2_PPULSE_LENL_MASK            0xFF

/**
 * @brief Ambient 14 CFG1 register setting.
 * @details Specified setting for CFG1 register of Ambient 14 Click driver.
 */
#define AMBIENT14_CFG1_PGAIN2_2_5X                  0x00
#define AMBIENT14_CFG1_PGAIN2_5X                    0x20
#define AMBIENT14_CFG1_PGAIN2_10X                   0x60
#define AMBIENT14_CFG1_PGAIN2_MASK                  0x60
#define AMBIENT14_CFG1_AGAIN_16X                    0x05
#define AMBIENT14_CFG1_AGAIN_128X                   0x08
#define AMBIENT14_CFG1_AGAIN_1024X                  0x0B
#define AMBIENT14_CFG1_AGAIN_MASK                   0x1F

/**
 * @brief Ambient 14 CFG8 register setting.
 * @details Specified setting for CFG8 register of Ambient 14 Click driver.
 */
#define AMBIENT14_CFG8_RESERVED                     0x29

/**
 * @brief Ambient 14 CFG6 register setting.
 * @details Specified setting for CFG6 register of Ambient 14 Click driver.
 */
#define AMBIENT14_CFG6_APC_ENABLE                   0x00
#define AMBIENT14_CFG6_APC_DISABLE                  0x40
#define AMBIENT14_CFG6_RESERVED                     0x3F

/**
 * @brief Ambient 14 STATUS register setting.
 * @details Specified setting for STATUS register of Ambient 14 Click driver.
 */
#define AMBIENT14_STATUS_ASAT                       0x80
#define AMBIENT14_STATUS_PSAT                       0x40
#define AMBIENT14_STATUS_PINT                       0x20
#define AMBIENT14_STATUS_AINT                       0x10
#define AMBIENT14_STATUS_CINT                       0x08
#define AMBIENT14_STATUS_ZINT                       0x04
#define AMBIENT14_STATUS_PSAT_REFLECTIVE            0x02
#define AMBIENT14_STATUS_PSAT_AMBIENT               0x01
#define AMBIENT14_STATUS_CLEAR_ALL                  0xFF

/**
 * @brief Ambient 14 INTENAB register setting.
 * @details Specified setting for INTENAB register of Ambient 14 Click driver.
 */
#define AMBIENT14_INTENAB_ASIEN                     0x80
#define AMBIENT14_INTENAB_PSIEN                     0x40
#define AMBIENT14_INTENAB_PIEN                      0x20
#define AMBIENT14_INTENAB_AIEN                      0x10
#define AMBIENT14_INTENAB_CIEN                      0x08
#define AMBIENT14_INTENAB_ZIEN                      0x04
#define AMBIENT14_INTENAB_DISABLE                   0x00

/**
 * @brief Ambient 14 CALIB register setting.
 * @details Specified setting for CALIB register of Ambient 14 Click driver.
 */
#define AMBIENT14_CALIB_CALAVG                      0x80
#define AMBIENT14_CALIB_ELECTRICAL_CALIB            0x20
#define AMBIENT14_CALIB_CALPRATE                    0x10
#define AMBIENT14_CALIB_START_OFFSET_CAL            0x01

/**
 * @brief Ambient 14 CALIBCFG register setting.
 * @details Specified setting for CALIBCFG register of Ambient 14 Click driver.
 */
#define AMBIENT14_CALIBCFG_BINSRCH_TARGET_3         0x00
#define AMBIENT14_CALIBCFG_BINSRCH_TARGET_7         0x20
#define AMBIENT14_CALIBCFG_BINSRCH_TARGET_15        0x40
#define AMBIENT14_CALIBCFG_BINSRCH_TARGET_31        0x60
#define AMBIENT14_CALIBCFG_BINSRCH_TARGET_63        0x80
#define AMBIENT14_CALIBCFG_BINSRCH_TARGET_127       0xA0
#define AMBIENT14_CALIBCFG_BINSRCH_TARGET_255       0xC0
#define AMBIENT14_CALIBCFG_BINSRCH_TARGET_511       0xE0
#define AMBIENT14_CALIBCFG_BINSRCH_TARGET_MASK      0xE0
#define AMBIENT14_CALIBCFG_RESERVED                 0x10
#define AMBIENT14_CALIBCFG_AUTO_OFFSET_ADJ          0x08
#define AMBIENT14_CALIBCFG_PROX_AVG_DISABLE         0x00
#define AMBIENT14_CALIBCFG_PROX_AVG_2               0x01
#define AMBIENT14_CALIBCFG_PROX_AVG_4               0x02
#define AMBIENT14_CALIBCFG_PROX_AVG_8               0x03
#define AMBIENT14_CALIBCFG_PROX_AVG_16              0x04
#define AMBIENT14_CALIBCFG_PROX_AVG_MASK            0x07

/**
 * @brief Ambient 14 CALIBSTAT register setting.
 * @details Specified setting for CALIBSTAT register of Ambient 14 Click driver.
 */
#define AMBIENT14_CALIBSTAT_OFFSET_ADJUSTED         0x04
#define AMBIENT14_CALIBSTAT_CALIB_FINISHED          0x01

/**
 * @brief Ambient 14 integration time setting.
 * @details Specified setting for integration time of Ambient 14 Click driver.
 */
#define AMBIENT14_SINGLE_STEP_MS                    2.78f
#define AMBIENT14_ATIME_MAX                         ( 256 * AMBIENT14_SINGLE_STEP_MS )
#define AMBIENT14_ATIME_MIN                         AMBIENT14_SINGLE_STEP_MS
#define AMBIENT14_ATIME_DEFAULT                     100.0f
#define AMBIENT14_AWTIME_MAX                        ( 256 * AMBIENT14_SINGLE_STEP_MS )
#define AMBIENT14_AWTIME_MIN                        AMBIENT14_SINGLE_STEP_MS
#define AMBIENT14_AWTIME_DEFAULT                    50.0f
#define AMBIENT14_PWTIME_MAX                        ( 256 * AMBIENT14_SINGLE_STEP_MS )
#define AMBIENT14_PWTIME_MIN                        AMBIENT14_SINGLE_STEP_MS
#define AMBIENT14_PWTIME_DEFAULT                    500.0f
#define AMBIENT14_ROUND_TO_INT                      0.5f

/**
 * @brief Ambient 14 illuminance conversion setting.
 * @details Specified setting for illuminance conversion (Figure 13 from datasheet) of Ambient 14 Click driver.
 */
#define AMBIENT14_ILLUMINANCE_GAIN_16_TO_128        0.125f
#define AMBIENT14_ILLUMINANCE_ATIME_100_GAIN_128    0.0095f
#define AMBIENT14_ILLUMINANCE_GAIN_1024_TO_128      8.2f

/**
 * @brief Ambient 14 ID value.
 * @details Specified ID value of Ambient 14 Click driver.
 */
#define AMBIENT14_DEVICE_ID                         0x50

/**
 * @brief Ambient 14 device address setting.
 * @details Specified setting for device slave address selection of
 * Ambient 14 Click driver.
 */
#define AMBIENT14_DEVICE_ADDRESS                    0x39

/*! @} */ // ambient14_set

/**
 * @defgroup ambient14_map Ambient 14 MikroBUS Map
 * @brief MikroBUS pin mapping of Ambient 14 Click driver.
 */

/**
 * @addtogroup ambient14_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Ambient 14 Click to the selected MikroBUS.
 */
#define AMBIENT14_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.sby = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ambient14_map
/*! @} */ // ambient14

/**
 * @brief Ambient 14 Click context object.
 * @details Context object definition of Ambient 14 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t sby;          /**< Standby pin (active low). */

    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin (Active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} ambient14_t;

/**
 * @brief Ambient 14 Click configuration object.
 * @details Configuration object definition of Ambient 14 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t sby;             /**< Standby pin (active low). */
    pin_name_t int_pin;         /**< Interrupt pin (Active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} ambient14_cfg_t;

/**
 * @brief Ambient 14 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AMBIENT14_OK = 0,
    AMBIENT14_ERROR = -1

} ambient14_return_value_t;

/*!
 * @addtogroup ambient14 Ambient 14 Click Driver
 * @brief API for configuring and manipulating Ambient 14 Click driver.
 * @{
 */

/**
 * @brief Ambient 14 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ambient14_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ambient14_cfg_setup ( ambient14_cfg_t *cfg );

/**
 * @brief Ambient 14 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ambient14_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ambient14_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient14_init ( ambient14_t *ctx, ambient14_cfg_t *cfg );

/**
 * @brief Ambient 14 default configuration function.
 * @details This function executes a default configuration of Ambient 14
 * Click board.
 * @param[in] ctx : Click context object.
 * See #ambient14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ambient14_default_cfg ( ambient14_t *ctx );

/**
 * @brief Ambient 14 write regs function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient14_write_regs ( ambient14_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Ambient 14 read regs function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient14_read_regs ( ambient14_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Ambient 14 write reg function.
 * @details This function writes data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient14_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient14_write_reg ( ambient14_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Ambient 14 read reg function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient14_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient14_read_reg ( ambient14_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Ambient 14 enable device function.
 * @details This function enables the device by setting the SBY pin to HIGH logic state.
 * @param[in] ctx : Click context object.
 * See #ambient14_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ambient14_enable_device ( ambient14_t *ctx );

/**
 * @brief Ambient 14 disable device function.
 * @details This function enables the device by setting the SBY pin to LOW logic state.
 * @param[in] ctx : Click context object.
 * See #ambient14_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ambient14_disable_device ( ambient14_t *ctx );

/**
 * @brief Ambient 14 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #ambient14_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ambient14_get_int_pin ( ambient14_t *ctx );

/**
 * @brief Ambient 14 check communication function.
 * @details This function checks the communication by reading and verifying the device ID 
 * on up to 10 tries.
 * @param[in] ctx : Click context object.
 * See #ambient14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient14_check_communication ( ambient14_t *ctx );

/**
 * @brief Ambient 14 soft reset function.
 * @details This function executes the defice software reset command.
 * @param[in] ctx : Click context object.
 * See #ambient14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient14_soft_reset ( ambient14_t *ctx );

/**
 * @brief Ambient 14 clear interrupts function.
 * @details This function clears all interrupts status.
 * @param[in] ctx : Click context object.
 * See #ambient14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient14_clear_interrupts ( ambient14_t *ctx );

/**
 * @brief Ambient 14 set atime function.
 * @details This function sets the ADC integration time in milliseconds by setting
 * the ATIME register.
 * @param[in] ctx : Click context object.
 * See #ambient14_t object definition for detailed explanation.
 * @param[in] atime_ms : ADC integration time in milliseconds.
 * [from AMBIENT14_ATIME_MIN to AMBIENT14_ATIME_MAX].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient14_set_atime ( ambient14_t *ctx, float atime_ms );

/**
 * @brief Ambient 14 set awtime function.
 * @details This function sets the ALS wait time in milliseconds by setting the AWTIME register.
 * @param[in] ctx : Click context object.
 * See #ambient14_t object definition for detailed explanation.
 * @param[in] awtime_ms : ALS wait time in milliseconds.
 * [from AMBIENT14_AWTIME_MIN to AMBIENT14_AWTIME_MAX].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient14_set_awtime ( ambient14_t *ctx, float awtime_ms );

/**
 * @brief Ambient 14 set pwtime function.
 * @details This function sets the PROX wait time in milliseconds by setting the PWTIME register.
 * @param[in] ctx : Click context object.
 * See #ambient14_t object definition for detailed explanation.
 * @param[in] pwtime_ms : PROX wait time in milliseconds.
 * [from AMBIENT14_PWTIME_MIN to AMBIENT14_PWTIME_MAX].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient14_set_pwtime ( ambient14_t *ctx, float pwtime_ms );

/**
 * @brief Ambient 14 read proximity function.
 * @details This function reads the raw proximity data. The higher the value, the closer the detected object is.
 * @param[in] ctx : Click context object.
 * See #ambient14_t object definition for detailed explanation.
 * @param[out] prox_data : Proximity data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient14_read_proximity ( ambient14_t *ctx, uint16_t *prox_data );

/**
 * @brief Ambient 14 read als ir function.
 * @details This function reads the raw ALS and IR data.
 * @param[in] ctx : Click context object.
 * See #ambient14_t object definition for detailed explanation.
 * @param[out] als_data : ALS data.
 * @param[out] ir_data : IR data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient14_read_als_ir ( ambient14_t *ctx, uint16_t *als_data, uint16_t *ir_data );

/**
 * @brief Ambient 14 get illuminance function.
 * @details This function calculates the illuminance level (Lux) from ALS data counts input.
 * @param[in] ctx : Click context object.
 * See #ambient14_t object definition for detailed explanation.
 * @param[in] als_data : ALS data.
 * @param[out] illuminance : Illuminance in Lux.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient14_get_illuminance ( ambient14_t *ctx, uint16_t als_data, float *illuminance );

#ifdef __cplusplus
}
#endif
#endif // AMBIENT14_H

/*! @} */ // ambient14

// ------------------------------------------------------------------------ END
