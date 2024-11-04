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
 * @file solarenergy2.h
 * @brief This file contains API for Solar Energy 2 Click Driver.
 */

#ifndef SOLARENERGY2_H
#define SOLARENERGY2_H

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
 * @addtogroup solarenergy2 Solar Energy 2 Click Driver
 * @brief API for configuring and manipulating Solar Energy 2 Click driver.
 * @{
 */

/**
 * @defgroup solarenergy2_reg Solar Energy 2 Registers List
 * @brief List of registers of Solar Energy 2 Click driver.
 */

/**
 * @addtogroup solarenergy2_reg
 * @{
 */

/**
 * @brief Solar Energy 2 description register.
 * @details Specified register for description of Solar Energy 2 Click driver.
 */
#define SOLARENERGY2_REG_T_HRV_PERIOD              0x00
#define SOLARENERGY2_REG_T_HRV_MEAS                0x01
#define SOLARENERGY2_REG_T_STS_PERIOD              0x02
#define SOLARENERGY2_REG_T_LTS_PERIOD              0x03
#define SOLARENERGY2_REG_V_HRV_CFG                 0x04
#define SOLARENERGY2_REG_HRV_CHECK_LVL             0x05
#define SOLARENERGY2_REG_LTS_CFG                   0x06
#define SOLARENERGY2_REG_V_BAT_MAX_HI              0x07
#define SOLARENERGY2_REG_V_BAT_MAX_LO              0x08
#define SOLARENERGY2_REG_V_BAT_MIN_HI_DIS          0x09
#define SOLARENERGY2_REG_V_BAT_MIN_HI_CON          0x0A
#define SOLARENERGY2_REG_V_BAT_MIN_LO              0x0B
#define SOLARENERGY2_REG_V_APL_MAX_HI              0x0C
#define SOLARENERGY2_REG_V_APL_MAX_LO              0x0D
#define SOLARENERGY2_REG_LDO_CFG                   0x0E
#define SOLARENERGY2_REG_PWR_CFG                   0x0F
#define SOLARENERGY2_REG_VAUX_CFG                  0x10
#define SOLARENERGY2_REG_VAUX_GND_CFG              0x11
#define SOLARENERGY2_REG_MPPT_RATIO                0x12
#define SOLARENERGY2_REG_EXT_CFG                   0x13
#define SOLARENERGY2_REG_T_SLEEP_VSUP_LO           0x14
#define SOLARENERGY2_REG_T_SLEEP_VSUP_MID          0x15
#define SOLARENERGY2_REG_T_SLEEP_VSUP_HI           0x16
#define SOLARENERGY2_REG_T_HRV_LOW_CFG             0x17
#define SOLARENERGY2_REG_SPI_I2C_CFG               0x18
#define SOLARENERGY2_REG_PWR_MGT                   0x19

#define SOLARENERGY2_REG_SOFT_RES_WORD             0x1A
#define SOLARENERGY2_REG_PROTECT_KEY               0x1B
#define SOLARENERGY2_REG_LUX_METER_CFG             0x1C
#define SOLARENERGY2_REG_LUX_METER_RESULT          0x1D
#define SOLARENERGY2_REG_STATUS                    0x22
#define SOLARENERGY2_REG_VLD_STATUS                0x23

#define SOLARENERGY2_REG_EEPROM_0                  0x40

/*! @} */ // solarenergy2_reg

/**
 * @defgroup solarenergy2_set Solar Energy 2 Registers Settings
 * @brief Settings for registers of Solar Energy 2 Click driver.
 */

/**
 * @addtogroup solarenergy2_set
 * @{
 */

/**
 * @brief Solar Energy 2 description setting.
 * @details Specified setting for description of Solar Energy 2 Click driver.
 */
#define SOLARENERGY2_SET_T_HRV_PERIOD_256ms        0x00
#define SOLARENERGY2_SET_T_HRV_PERIOD_512ms        0x01
#define SOLARENERGY2_SET_T_HRV_PERIOD_1sec         0x02
#define SOLARENERGY2_SET_T_HRV_PERIOD_2sec         0x03
#define SOLARENERGY2_SET_T_HRV_PERIOD_4sec         0x04
#define SOLARENERGY2_SET_T_HRV_PERIOD_8sec         0x05
#define SOLARENERGY2_SET_T_HRV_PERIOD_16sec        0x06
#define SOLARENERGY2_SET_T_HRV_PERIOD_32sec        0x07

#define SOLARENERGY2_SET_T_HRV_MEAS_16ms           0x00
#define SOLARENERGY2_SET_T_HRV_MEAS_32ms           0x01
#define SOLARENERGY2_SET_T_HRV_MEAS_64ms           0x02
#define SOLARENERGY2_SET_T_HRV_MEAS_128ms          0x03
#define SOLARENERGY2_SET_T_HRV_MEAS_256ms          0x04
#define SOLARENERGY2_SET_T_HRV_MEAS_512ms          0x05
#define SOLARENERGY2_SET_T_HRV_MEAS_1sec           0x06
#define SOLARENERGY2_SET_T_HRV_MEAS_2sec           0x07

#define SOLARENERGY2_SET_T_STS_PERIOD_1ms          0x00
#define SOLARENERGY2_SET_T_STS_PERIOD_2ms          0x01
#define SOLARENERGY2_SET_T_STS_PERIOD_8ms          0x02
#define SOLARENERGY2_SET_T_STS_PERIOD_16ms         0x03
#define SOLARENERGY2_SET_T_STS_PERIOD_32ms         0x04
#define SOLARENERGY2_SET_T_STS_PERIOD_64ms         0x05
#define SOLARENERGY2_SET_T_STS_PERIOD_128ms        0x06
#define SOLARENERGY2_SET_T_STS_PERIOD_256ms        0x07

#define SOLARENERGY2_SET_T_LTS_PERIOD_1ms          0x00
#define SOLARENERGY2_SET_T_LTS_PERIOD_4ms          0x01
#define SOLARENERGY2_SET_T_LTS_PERIOD_16ms         0x02
#define SOLARENERGY2_SET_T_LTS_PERIOD_64ms         0x03
#define SOLARENERGY2_SET_T_LTS_PERIOD_256ms        0x04
#define SOLARENERGY2_SET_T_LTS_PERIOD_1sec         0x05
#define SOLARENERGY2_SET_T_LTS_PERIOD_4sec         0x06
#define SOLARENERGY2_SET_T_LTS_PERIOD_16sec        0x07

#define SOLARENERGY2_SET_T_HRV_LOW_PERIOD_256ms    0x00
#define SOLARENERGY2_SET_T_HRV_LOW_PERIOD_512ms    0x01
#define SOLARENERGY2_SET_T_HRV_LOW_PERIOD_1sec     0x02
#define SOLARENERGY2_SET_T_HRV_LOW_PERIOD_2sec     0x03
#define SOLARENERGY2_SET_T_HRV_LOW_PERIOD_4sec     0x04
#define SOLARENERGY2_SET_T_HRV_LOW_PERIOD_8sec     0x05
#define SOLARENERGY2_SET_T_HRV_LOW_PERIOD_16sec    0x06
#define SOLARENERGY2_SET_T_HRV_LOW_PERIOD_32sec    0x07

#define SOLARENERGY2_SET_T_LTS_LOW_PERIOD_2ms      0x00
#define SOLARENERGY2_SET_T_LTS_LOW_PERIOD_8ms      0x01
#define SOLARENERGY2_SET_T_LTS_LOW_PERIOD_32ms     0x02
#define SOLARENERGY2_SET_T_LTS_LOW_PERIOD_128ms    0x03
#define SOLARENERGY2_SET_T_LTS_LOW_PERIOD_512ms    0x04
#define SOLARENERGY2_SET_T_LTS_LOW_PERIOD_2sec     0x05
#define SOLARENERGY2_SET_T_LTS_LOW_PERIOD_8sec     0x06
#define SOLARENERGY2_SET_T_LTS_LOW_PERIOD_32sec    0x07

#define SOLARENERGY2_PROTECT_KEY_SOFT_RESET        0xE2
#define SOLARENERGY2_PROTECT_KEY_PROTECTED_REG     0x4B
#define SOLARENERGY2_PROTECT_KEY_EEPROM            0xA5

#define SOLARENERGY2_SET_VAUX_LDO_CFG_1_2V         0x00
#define SOLARENERGY2_SET_VAUX_LDO_CFG_1_55V        0x10
#define SOLARENERGY2_SET_VAUX_LDO_CFG_1_65V        0x20
#define SOLARENERGY2_SET_VAUX_LDO_CFG_1_8V         0x30
#define SOLARENERGY2_SET_VAUX_LDO_CFG_2_0V         0x40
#define SOLARENERGY2_SET_VAUX_LDO_CFG_2_2V         0x50
#define SOLARENERGY2_SET_VAUX_LDO_CFG_2_4V         0x60
#define SOLARENERGY2_SET_VAUX_LDO_CFG_2_6V         0x70
#define SOLARENERGY2_SET_VAUX_LDO_CFG_BIT_MASK     0x70

#define SOLARENERGY2_SET_ULP_LDO_CFG_1_2V          0x00
#define SOLARENERGY2_SET_ULP_LDO_CFG_1_55V         0x01
#define SOLARENERGY2_SET_ULP_LDO_CFG_1_65V         0x02
#define SOLARENERGY2_SET_ULP_LDO_CFG_1_8V          0x03
#define SOLARENERGY2_SET_ULP_LDO_CFG_2_0V          0x04
#define SOLARENERGY2_SET_ULP_LDO_CFG_2_2V          0x05
#define SOLARENERGY2_SET_ULP_LDO_CFG_2_4V          0x06
#define SOLARENERGY2_SET_ULP_LDO_CFG_2_6V          0x07
#define SOLARENERGY2_SET_ULP_LDO_CFG_BIT_MASK      0x07

#define SOLARENERGY2_SET_MPPT_RATIO_50             0x00
#define SOLARENERGY2_SET_MPPT_RATIO_60             0x01
#define SOLARENERGY2_SET_MPPT_RATIO_67             0x02
#define SOLARENERGY2_SET_MPPT_RATIO_71             0x03
#define SOLARENERGY2_SET_MPPT_RATIO_75             0x04
#define SOLARENERGY2_SET_MPPT_RATIO_78             0x05
#define SOLARENERGY2_SET_MPPT_RATIO_80             0x06
#define SOLARENERGY2_SET_MPPT_RATIO_82             0x07
#define SOLARENERGY2_SET_MPPT_RATIO_83             0x08
#define SOLARENERGY2_SET_MPPT_RATIO_85             0x09
#define SOLARENERGY2_SET_MPPT_RATIO_86             0x0A
#define SOLARENERGY2_SET_MPPT_RATIO_87             0x0B
#define SOLARENERGY2_SET_MPPT_RATIO_88             0x0C
#define SOLARENERGY2_SET_MPPT_BIT_MASK             0x0F

#define SOLARENERGY2_SET_HRV_CHECK_VLD_VTG         0x00
#define SOLARENERGY2_SET_HRV_CHECK_VLD_CUR         0x40
#define SOLARENERGY2_SET_HRV_MIN_VTG_GEN           0x01

#define SOLARENERGY2_SET_CRT_SRC_SEL_0mA           0x00
#define SOLARENERGY2_SET_CRT_SRC_SEL_5mA           0x01
#define SOLARENERGY2_SET_CRT_SRC_SEL_10mA          0x02
#define SOLARENERGY2_SET_CRT_SRC_SEL_15mA          0x03
#define SOLARENERGY2_CRT_SRC_SEL_BIT_MASK          0x03

#define SOLARENERGY2_V_BATT_APP_VTG_BIT_MASK       0x3F

#define SOLARENERGY2_SET_LTS_CFG_CONN_LTS_STS      0x04
#define SOLARENERGY2_SET_LTS_CFG_NORMAL_MODE       0x00
#define SOLARENERGY2_SET_LTS_CFG_NEVER_CHARGE      0x02
#define SOLARENERGY2_SET_LTS_CFG_RECHARGEABLE      0x00
#define SOLARENERGY2_SET_LTS_CFG_BATT_PROT_DIS     0x01
#define SOLARENERGY2_SET_LTS_CFG_BATT_PROT_EN      0x00

#define SOLARENERGY2_SET_VAUX0_CFG_STS             0x00
#define SOLARENERGY2_SET_VAUX0_CFG_LDO             0x01
#define SOLARENERGY2_SET_VAUX0_CFG_AUTO_FLT        0x02
#define SOLARENERGY2_SET_VAUX0_CFG_AUTO_GND        0x03
#define SOLARENERGY2_SET_VAUX1_CFG_STS             0x00
#define SOLARENERGY2_SET_VAUX1_CFG_LDO             0x04
#define SOLARENERGY2_SET_VAUX1_CFG_AUTO_FLT        0x08
#define SOLARENERGY2_SET_VAUX1_CFG_AUTO_GND        0x0C
#define SOLARENERGY2_SET_VAUX2_CFG_STS             0x00
#define SOLARENERGY2_SET_VAUX2_CFG_LDO             0x10
#define SOLARENERGY2_SET_VAUX2_CFG_AUTO_FLT        0x20
#define SOLARENERGY2_SET_VAUX2_CFG_AUTO_GND        0x30
#define SOLARENERGY2_SET_LDO_CFG_ULP_BIT_MASK      0x08
#define SOLARENERGY2_SET_LDO_CFG_VSUP_BIT_MASK     0x80

#define SOLARENERGY2_LUX_METER_BUSY_BIT_MASK       0x10
#define SOLARENERGY2_LUX_METER_BIT_MASK            0x0F

#define SOLARENERGY2_SET_HRV_CURRENT_LVL_15uA      0x0E


/**
 * @brief Solar Energy 2 device address setting.
 * @details Specified setting for device slave address selection of
 * Solar Energy 2 Click driver.
 */
#define SOLARENERGY2_DEVICE_ADDRESS                0x77

/*! @} */ // solarenergy2_set

/**
 * @defgroup solarenergy2_map Solar Energy 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Solar Energy 2 Click driver.
 */

/**
 * @addtogroup solarenergy2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Solar Energy 2 Click to the selected MikroBUS.
 */
#define SOLARENERGY2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS );    \
    cfg.wup = MIKROBUS( mikrobus, MIKROBUS_AN );   \
    cfg.blv = MIKROBUS( mikrobus, MIKROBUS_PWM );  \
    cfg.hlv = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // solarenergy2_map
/*! @} */ // solarenergy2

/**
 * @brief Solar Energy 2 Click context object.
 * @details Context object definition of Solar Energy 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t cs;         /**< Chip select pin. */
    digital_out_t wup;        /**< Wake-up pin. */

    // Input pins
    digital_in_t blv;         /**< Battery low indicator pin. */
    digital_in_t hlv;         /**< Energy harvester cell low indicator pin. */

    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} solarenergy2_t;

/**
 * @brief Solar Energy 2 Click configuration object.
 * @details Configuration object definition of Solar Energy 2 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t cs;              /**< Chip select pin. */
    pin_name_t wup;             /**< Wake-up pin. */
    pin_name_t blv;             /**< Battery low indicator pin. */
    pin_name_t hlv;             /**< Energy harvester cell low indicator pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} solarenergy2_cfg_t;

/**
 * @brief Solar Energy 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SOLARENERGY2_OK = 0,
    SOLARENERGY2_ERROR = -1

} solarenergy2_return_value_t;

/**
 * @brief Solar Energy 2 Click status information object.
 * @details Status information object definition of Solar Energy 2 Click driver.
 */
typedef struct
{
    uint8_t    eeprom_data_busy;     /**< EEPROM busy status. */
    uint8_t    hrv_lux_busy;         /**< HRV current status. */
    uint8_t    hrv_low;              /**< HRV energy level low status. */
    uint8_t    bat_low;              /**< LTS voltage low status. */
    uint8_t    sw_vdcdc_lts_nsts;    /**< DCDC charging status. */
    uint8_t    sw_lts_sts;           /**< LTS and STS connection status. */
    uint8_t    usb_on;               /**< USB power status. */
    uint8_t    lts_protect;          /**< LTS protection mode status. */

} solarenergy2_status_t;

/**
 * @brief Solar Energy 2 Click storage element voltage and state object.
 * @details Storage element voltage and staten object definition of Solar Energy 2 Click driver.
 */
typedef struct
{
    uint8_t    lts_bat_min_hi;    /**< Battery MIN High status. */
    uint8_t    lts_bat_min_lo;    /**< Battery MIN Low status. */
    uint8_t    sts_bat_max_hi;    /**< Battery MAX High status. */
    uint8_t    sts_bat_max_lo;    /**< Battery MAX Low status. */
    uint8_t    sts_apl_max_hi;    /**< Application MAX High status. */
    uint8_t    sts_apl_max_lo;    /**< Application MAX Low status. */
    uint8_t    sts_bat_min_hi;    /**< STS Battery MIN High status. */
    uint8_t    sts_bat_min_lo;    /**< STS Battery MIN Low status. */

} solarenergy2_bat_vtg_status_t;

/**
 * @brief Solar Energy 2 Click operation battery voltage values object.
 * @details Operation battery voltage values object definition of Solar Energy 2 Click driver.
 */
typedef struct
{
    float    v_bat_max_hi;        /**< Maximum battery voltage. High level of hysteresis. */
    float    v_bat_max_lo;        /**< Maximum battery voltage. Low level of hysteresis. */
    float    v_bat_min_hi_dis;    /**< Minimum STS maintenance voltage – acts as v_bat_min_hi when STS and LTS are disconnected. */
    float    v_bat_min_hi_con;    /**< Minimum battery maintenance voltage – acts as v_bat_min_hi when STS and LTS are connected. */
    float    v_bat_min_lo;        /**< Minimum battery voltage. Low level of hysteresis. */
    float    v_apl_max_hi;        /**< Maximum application voltage. High level of hysteresis. */
    float    v_apl_max_lo;        /**< Maximum application voltage. Low level of hysteresis. */

} solarenergy2_abs_vtg_v_t;

/*!
 * @addtogroup solarenergy2 Solar Energy 2 Click Driver
 * @brief API for configuring and manipulating Solar Energy 2 Click driver.
 * @{
 */

/**
 * @brief Solar Energy 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #solarenergy2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void solarenergy2_cfg_setup ( solarenergy2_cfg_t *cfg );

/**
 * @brief Solar Energy 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #solarenergy2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #solarenergy2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solarenergy2_init ( solarenergy2_t *ctx, solarenergy2_cfg_t *cfg );

/**
 * @brief Solar Energy 2 default configuration function.
 * @details This function executes a default configuration of Solar Energy 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #solarenergy2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t solarenergy2_default_cfg ( solarenergy2_t *ctx );

/**
 * @brief Solar Energy 2 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #solarenergy2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solarenergy2_generic_write ( solarenergy2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Solar Energy 2 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #solarenergy2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solarenergy2_generic_read ( solarenergy2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Solar Energy 2 write register function.
 * @details This function writes a desired register by using I2C serial interface
 * of the EM8500 Power Management Controller with Energy Harvesting Interface
 * on the Solar Energy 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #solarenergy2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solarenergy2_write_reg ( solarenergy2_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Solar Energy 2 write EEPROM function.
 * @details This function writes a desired EEPROM register by using I2C serial interface
 * of the EM8500 Power Management Controller with Energy Harvesting Interface
 * on the Solar Energy 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #solarenergy2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solarenergy2_write_eeprom ( solarenergy2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Solar Energy 2 soft reset function.
 * @details This function perform a software reset
 * of the EM8500 Power Management Controller with Energy Harvesting Interface
 * on the Solar Energy 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #solarenergy2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solarenergy2_soft_reset ( solarenergy2_t *ctx );

/**
 * @brief Solar Energy 2 get status function.
 * @details This function reads the status data
 * of the EM8500 Power Management Controller with Energy Harvesting Interface
 * on the Solar Energy 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #solarenergy2_t object definition for detailed explanation.
 * @param[out] status : Status data object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solarenergy2_get_status ( solarenergy2_t *ctx, solarenergy2_status_t *status );

/**
 * @brief Solar Energy 2 get storage element status function.
 * @details This function reads the storage element voltage and state data
 * of the EM8500 Power Management Controller with Energy Harvesting Interface
 * on the Solar Energy 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #solarenergy2_t object definition for detailed explanation.
 * @param[out] bat_vtg_status : Storage element status data object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solarenergy2_get_bat_vtg_status ( solarenergy2_t *ctx, solarenergy2_bat_vtg_status_t *bat_vtg_status );

/**
 * @brief Solar Energy 2 set sleep VSUP function.
 * @details This function sets the sleep state
 * of the EM8500 Power Management Controller with Energy Harvesting Interface
 * on the Solar Energy 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #solarenergy2_t object definition for detailed explanation.
 * @param[out] sleep_vsup_sec : VSUP sleep time in seconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note VSUP supply can be interrupted for up to 4 hours.
 */
err_t solarenergy2_set_sleep_vsup ( solarenergy2_t *ctx, float sleep_vsup_sec );

/**
 * @brief Solar Energy 2 set MPPT ratio function.
 * @details This function sets the Maximum Power Point Tracking
 * of the EM8500 Power Management Controller with Energy Harvesting Interface
 * on the Solar Energy 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #solarenergy2_t object definition for detailed explanation.
 * @param[out] mppt_ratio : 
 *            @li @c  0x00 (SOLARENERGY2_SET_MPPT_RATIO_50) - MPPT ratio 50%,
 *            @li @c  0x01 (SOLARENERGY2_SET_MPPT_RATIO_60) - MPPT ratio 60%,
 *            @li @c  0x02 (SOLARENERGY2_SET_MPPT_RATIO_67) - MPPT ratio 67%,
 *            @li @c  0x03 (SOLARENERGY2_SET_MPPT_RATIO_71) - MPPT ratio 71%,
 *            @li @c  0x04 (SOLARENERGY2_SET_MPPT_RATIO_75) - MPPT ratio 75%,
 *            @li @c  0x05 (SOLARENERGY2_SET_MPPT_RATIO_78) - MPPT ratio 78%,
 *            @li @c  0x06 (SOLARENERGY2_SET_MPPT_RATIO_80) - MPPT ratio 80%,
 *            @li @c  0x07 (SOLARENERGY2_SET_MPPT_RATIO_82) - MPPT ratio 82%,
 *            @li @c  0x08 (SOLARENERGY2_SET_MPPT_RATIO_83) - MPPT ratio 83%,
 *            @li @c  0x09 (SOLARENERGY2_SET_MPPT_RATIO_85) - MPPT ratio 85%,
 *            @li @c  0x0A (SOLARENERGY2_SET_MPPT_RATIO_86) - MPPT ratio 86%,
 *            @li @c  0x0B (SOLARENERGY2_SET_MPPT_RATIO_87) - MPPT ratio 87%,
 *            @li @c  0x0C (SOLARENERGY2_SET_MPPT_RATIO_88) - MPPT ratio 88%.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note VSUP supply can be interrupted for up to 4 hours.
 */
err_t solarenergy2_set_mppt_ratio ( solarenergy2_t *ctx, uint8_t mppt_ratio );

/**
 * @brief Solar Energy 2 set LDO config function.
 * @details This function sets configuration of the LDO regulator
 * of the EM8500 Power Management Controller with Energy Harvesting Interface
 * on the Solar Energy 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #solarenergy2_t object definition for detailed explanation.
 * @param[in] vaux_ldo : VAUX LDO regulated voltage selection
 *         @li @c 0x00 (SOLARENERGY2_SET_VAUX_LDO_CFG_1_2V)  - 1.2 V,
 *         @li @c 0x10 (SOLARENERGY2_SET_VAUX_LDO_CFG_1_55V) - 1.55 V,
 *         @li @c 0x20 (SOLARENERGY2_SET_VAUX_LDO_CFG_1_65V) - 1.65 V,
 *         @li @c 0x30 (SOLARENERGY2_SET_VAUX_LDO_CFG_1_8V)  - 1.8 V,
 *         @li @c 0x40 (SOLARENERGY2_SET_VAUX_LDO_CFG_2_0V)  - 2.0 V,
 *         @li @c 0x50 (SOLARENERGY2_SET_VAUX_LDO_CFG_2_2V)  - 2.2 V,
 *         @li @c 0x60 (SOLARENERGY2_SET_VAUX_LDO_CFG_2_4V)  - 2.4 V,
 *         @li @c 0x70 (SOLARENERGY2_SET_VAUX_LDO_CFG_2_6V)  - 2.6 V.
 * @param[in] ulp_ldo : VAUX LDO regulated voltage selection
 *         @li @c 0x00 (SOLARENERGY2_SET_ULP_LDO_CFG_1_2V)  - 1.2 V,
 *         @li @c 0x10 (SOLARENERGY2_SET_ULP_LDO_CFG_1_55V) - 1.55 V,
 *         @li @c 0x20 (SOLARENERGY2_SET_ULP_LDO_CFG_1_65V) - 1.65 V,
 *         @li @c 0x30 (SOLARENERGY2_SET_ULP_LDO_CFG_1_8V)  - 1.8 V,
 *         @li @c 0x40 (SOLARENERGY2_SET_ULP_LDO_CFG_2_0V)  - 2.0 V,
 *         @li @c 0x50 (SOLARENERGY2_SET_ULP_LDO_CFG_2_2V)  - 2.2 V,
 *         @li @c 0x60 (SOLARENERGY2_SET_ULP_LDO_CFG_2_4V)  - 2.4 V,
 *         @li @c 0x70 (SOLARENERGY2_SET_ULP_LDO_CFG_2_6V)  - 2.6 V.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note VSUP supply can be interrupted for up to 4 hours.
 */
err_t solarenergy2_set_ldo_cfg ( solarenergy2_t *ctx, uint8_t vaux_ldo, uint8_t ulp_ldo );

/**
 * @brief Solar Energy 2 config absolute voltage function.
 * @details This function sets the configuration of the absolute voltage values
 * of the EM8500 Power Management Controller with Energy Harvesting Interface
 * on the Solar Energy 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #solarenergy2_t object definition for detailed explanation.
 * @param[in] abs_vtg : Absolute voltage data object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solarenergy2_config_abs_voltage ( solarenergy2_t *ctx, solarenergy2_abs_vtg_v_t abs_vtg );

/**
 * @brief Solar Energy 2 power source selection function.
 * @details This function sets the power current source selection
 * of the EM8500 Power Management Controller with Energy Harvesting Interface
 * on the Solar Energy 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #solarenergy2_t object definition for detailed explanation.
 * @param[in] crt_src_sel :
 *         @li @c  0x00 (SOLARENERGY2_SET_CRT_SRC_SEL_0mA)  - Current 0 mA (do not charge),
 *         @li @c  0x00 (SOLARENERGY2_SET_CRT_SRC_SEL_5mA)  - Current 5 mA,
 *         @li @c  0x00 (SOLARENERGY2_SET_CRT_SRC_SEL_10mA) - Current 10 mA,
 *         @li @c  0x00 (SOLARENERGY2_SET_CRT_SRC_SEL_15mA) - Current 15 mA.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solarenergy2_set_pwr_current_source ( solarenergy2_t *ctx, uint8_t crt_src_sel );

/**
 * @brief Solar Energy 2 store config function.
 * @details This function stores the configuration of the device in the EEPROM memory
 * of the EM8500 Power Management Controller with Energy Harvesting Interface
 * on the Solar Energy 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #solarenergy2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solarenergy2_store_config ( solarenergy2_t *ctx );

/**
 * @brief Solar Energy 2 set WUP pin function.
 * @details This function sets the Wake-up pin logic state
 * of the EM8500 Power Management Controller with Energy Harvesting Interface
 * on the Solar Energy 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #solarenergy2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return Nothing.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void solarenergy2_set_wup_pin ( solarenergy2_t *ctx, uint8_t state );

/**
 * @brief Solar Energy 2 get HLV state function.
 * @details This function gets energy harvester cell low indicator state
 * of the EM8500 Power Management Controller with Energy Harvesting Interface
 * on the Solar Energy 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #solarenergy2_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t solarenergy2_get_en_hv_cell_low_state ( solarenergy2_t *ctx );

/**
 * @brief Solar Energy 2 get BLV state function.
 * @details This function gets battery low indicator state
 * of the EM8500 Power Management Controller with Energy Harvesting Interface
 * on the Solar Energy 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #solarenergy2_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t solarenergy2_get_battery_low_state ( solarenergy2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // SOLARENERGY2_H

/*! @} */ // solarenergy2

// ------------------------------------------------------------------------ END
