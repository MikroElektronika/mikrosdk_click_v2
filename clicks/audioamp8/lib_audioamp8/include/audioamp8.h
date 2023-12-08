/****************************************************************************
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file audioamp8.h
 * @brief This file contains API for AudioAmp 8 Click Driver.
 */

#ifndef AUDIOAMP8_H
#define AUDIOAMP8_H

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
 * @addtogroup audioamp8 AudioAmp 8 Click Driver
 * @brief API for configuring and manipulating AudioAmp 8 Click driver.
 * @{
 */

/**
 * @defgroup audioamp8_reg AudioAmp 8 Registers List
 * @brief List of registers of AudioAmp 8 Click driver.
 */

/**
 * @addtogroup audioamp8_reg
 * @{
 */

/**
 * @brief AudioAmp 8 description register.
 * @details Specified register for description of AudioAmp 8 Click driver.
 */
#define AUDIOAMP8_REG_PWR_MODE_CTRL              0x00
#define AUDIOAMP8_REG_THSH_PWR_MODE_PM12         0x01
#define AUDIOAMP8_REG_THSH_PWR_MODE_PM21         0x02
#define AUDIOAMP8_REG_THSH_PWR_MODE_PM23         0x03
#define AUDIOAMP8_REG_THSH_PWR_MODE_PM32         0x04
#define AUDIOAMP8_REG_SOFT_CLP_OVC_PROT_LAT      0x0A
#define AUDIOAMP8_REG_SEL_PWR_MODE_PROFILE       0x1D
#define AUDIOAMP8_REG_PWR_MODE_PROFILE_CFG       0x1E
#define AUDIOAMP8_REG_OVC_PROT_LAT_CLR           0x20
#define AUDIOAMP8_REG_AUDIO_IN_MODE              0x25
#define AUDIOAMP8_REG_DC_PROTECTION              0x26
#define AUDIOAMP8_REG_AUDIO_IN_MODE_OVERWRITE    0x27
#define AUDIOAMP8_REG_ERROR_HANDLER_CLEAR        0x2D

#define AUDIOAMP8_REG_MON_CH_0_FREQ_PWR_MODE     0x60
#define AUDIOAMP8_REG_MON_CH_0                   0x61
#define AUDIOAMP8_REG_MON_CH_0_MODUL_INDEX       0x62
#define AUDIOAMP8_REG_MON_CH_1_FREQ_PWR_MODE     0x64
#define AUDIOAMP8_REG_MON_CH_1                   0x65
#define AUDIOAMP8_REG_MON_CH_1_MODUL_INDEX       0x66
#define AUDIOAMP8_REG_ERROR_ACCUMULATED          0x6D
#define AUDIOAMP8_REG_MONITOR_MSEL               0x75
#define AUDIOAMP8_REG_ERROR                      0x7C

/*! @} */ // audioamp8_reg

/**
 * @defgroup audioamp8_set AudioAmp 8 Registers Settings
 * @brief Settings for registers of AudioAmp 8 Click driver.
 */

/**
 * @addtogroup audioamp8_set
 * @{
 */

/**
 * @brief AudioAmp 8 description setting.
 * @details Specified setting for description of AudioAmp 8 Click driver.
 */
#define AUDIOAMP8_SET_MON_CH_0                   0x00
#define AUDIOAMP8_SET_MON_CH_1                   0x01
#define AUDIOAMP8_SET_AUTO_PWR_MODE              0x00
#define AUDIOAMP8_SET_MANUAL_PWR_MODE            0x01
#define AUDIOAMP8_SET_MTHR_1TO2_DEFAULT          0x3C
#define AUDIOAMP8_SET_MTHR_2TO1_DEFAULT          0x32
#define AUDIOAMP8_SET_MTHR_2TO3_DEFAULT          0x5A
#define AUDIOAMP8_SET_MTHR_3TO2_DEFAULT          0x50
#define AUDIOAMP8_SET_DISABLE                    0x00
#define AUDIOAMP8_SET_ENABLE                     0x01


/**
 * @brief AudioAmp 8 device address setting.
 * @details Specified setting for device slave address selection of
 * AudioAmp 8 Click driver.
 */
#define AUDIOAMP8_SET_DEV_ADDR_0                 0x20
#define AUDIOAMP8_SET_DEV_ADDR_1                 0x21
#define AUDIOAMP8_SET_DEV_ADDR_2                 0x22
#define AUDIOAMP8_SET_DEV_ADDR_3                 0x23

/*! @} */ // audioamp8_set

/**
 * @defgroup audioamp8_map AudioAmp 8 MikroBUS Map
 * @brief MikroBUS pin mapping of AudioAmp 8 Click driver.
 */

/**
 * @addtogroup audioamp8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of AudioAmp 8 Click to the selected MikroBUS.
 */
#define AUDIOAMP8_MAP_MIKROBUS( cfg, mikrobus )   \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.mut = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.ms0 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.ms1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // audioamp8_map
/*! @} */ // audioamp8

/**
 * @brief AudioAmp 8 Click context object.
 * @details Context object definition of AudioAmp 8 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  en;      /**< Enable pin. */
    digital_out_t  mut;     /**< Mute pin. */
    digital_out_t  ms0;     /**< SE/BTL/PBTL configuration select 0 pin. */
    digital_out_t  ms1;     /**< SE/BTL/PBTL configuration select 1 pin. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

} audioamp8_t;

/**
 * @brief AudioAmp 8 Click configuration object.
 * @details Configuration object definition of AudioAmp 8 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  en;         /**< Enable pin. */
    pin_name_t  mut;        /**< Mute pin. */
    pin_name_t  ms0;        /**< SE/BTL/PBTL configuration select 0 pin. */
    pin_name_t  ms1;        /**< SE/BTL/PBTL configuration select 1 pin. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} audioamp8_cfg_t;

/**
 * @brief AudioAmp 8 Click power mode configuration object.
 * @details Power mode configuration object definition of AudioAmp 8 Click driver.
 */
typedef struct
{
    uint8_t   manual_pm;
    uint8_t   pm_man;
    uint8_t   mthr_1to2;
    uint8_t   mthr_2to1;
    uint8_t   mthr_2to3;
    uint8_t   mthr_3to2;

} audioamp8_pwr_mon_cfg_t;

/**
 * @brief AudioAmp 8 Click power mode profile configuration object.
 * @details Power mode profile configuration object definition of AudioAmp 8 Click driver.
 */
typedef struct
{
    uint8_t   pm_profile;
    uint8_t   pm3_man_sh;
    uint8_t   pm2_man_sh;
    uint8_t   pm1_man_sh;

} audioamp8_pwr_mod_profile_cfg_t;

/**
 * @brief AudioAmp 8 Click monitor channel object.
 * @details Monitor channel object definition of AudioAmp 8 Click driver.
 */
typedef struct
{
    uint8_t   freq_mode;
    uint8_t   pwr_mode;
    uint8_t   mute_mon;
    uint8_t   vdd_mon;
    uint8_t   pvdd_mon;
    uint8_t   cfly2_mon;
    uint8_t   cfly1_mon;
    uint8_t   ovc_prot;
    uint8_t   modul_index_mon;

} audioamp8_monitor_channel_t;

/**
 * @brief AudioAmp 8 Click monitor channel object.
 * @details Monitor channel object definition of AudioAmp 8 Click driver.
 */
typedef struct
{
    uint8_t   fly_cap_ov_vtg;
    uint8_t   ov_curr_prot;
    uint8_t   pll_err;
    uint8_t   pvdd_un_vtg_prot;
    uint8_t   ov_temp_wrg;
    uint8_t   ov_temp_err;
    uint8_t   imped_prot;
    uint8_t   dc_prot;

} audioamp8_error_status_t;

/**
 * @brief AudioAmp 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   AUDIOAMP8_OK = 0,
   AUDIOAMP8_ERROR = -1

} audioamp8_return_value_t;

/**
 * @brief AudioAmp 8 Click manual selected power mode value data.
 * @details Manual selected power mode enum values for driver return values.
 */
typedef enum
{
   AUDIOAMP8_PM_MAN_1 = 1,
   AUDIOAMP8_PM_MAN_2,
   AUDIOAMP8_PM_MAN_3

} audioamp8_manual_pm_value_t;

/**
 * @brief AudioAmp 8 Click select power mode profile value data.
 * @details Select power mode profile enum values for driver return values.
 */
typedef enum
{
   AUDIOAMP8_PM_PROFILE_0 = 0,
   AUDIOAMP8_PM_PROFILE_1,
   AUDIOAMP8_PM_PROFILE_2,
   AUDIOAMP8_PM_PROFILE_3,
   AUDIOAMP8_PM_PROFILE_4

} audioamp8_pm_profile_value_t;

/**
 * @brief AudioAmp 8 Click profile assign scheme value data.
 * @details Profile assign scheme enum values for driver return values.
 */
typedef enum
{
   AUDIOAMP8_SCHEME_A = 0,
   AUDIOAMP8_SCHEME_B,
   AUDIOAMP8_SCHEME_C,
   AUDIOAMP8_SCHEME_D

} audioamp8_pm_man_sh_value_t;

/**
 * @brief AudioAmp 8 Click audio input mode value data.
 * @details Audio input mode enum values for driver return values.
 */
typedef enum
{
   AUDIOAMP8_AUDIO_IN_MODE_0_20dB = 0,
   AUDIOAMP8_AUDIO_IN_MODE_0_26dB

} audioamp8_audio_in_mode_value_t;

/**
 * @brief AudioAmp 8 Click audio input mode value data.
 * @details Audio input mode enum values for driver return values.
 */
typedef enum
{
   AUDIOAMP8_AUDIO_IN_MODE_EXT_DISABLE = 0,
   AUDIOAMP8_AUDIO_IN_MODE_EXT_ENABLE

} audioamp8_audio_in_mode_ext_value_t;

/*!
 * @addtogroup audioamp8 AudioAmp 8 Click Driver
 * @brief API for configuring and manipulating AudioAmp 8 Click driver.
 * @{
 */

/**
 * @brief AudioAmp 8 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #audioamp8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void audioamp8_cfg_setup ( audioamp8_cfg_t *cfg );

/**
 * @brief AudioAmp 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #audioamp8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #audioamp8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp8_init ( audioamp8_t *ctx, audioamp8_cfg_t *cfg );

/**
 * @brief AudioAmp 8 default configuration function.
 * @details This function executes a default configuration of AudioAmp 8
 * click board.
 * @param[in] ctx : Click context object.
 * See #audioamp8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t audioamp8_default_cfg ( audioamp8_t *ctx );

/**
 * @brief AudioAmp 8 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #audioamp8_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp8_generic_write ( audioamp8_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief AudioAmp 8 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #audioamp8_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp8_generic_read ( audioamp8_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief AudioAmp 8 start-up procedure function.
 * @details This function performs a start-up procedure 
 * of the MA12070 Filterless and High-Efficiency +4V to +26V Audio Amplifier with Analog Input
 * on the AudioAmp 8 click board™.
 * @param[in] ctx : Click context object.
 * See #audioamp8_t object definition for detailed explanation.
 * @return @li @c  0 - Success.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp8_start_up ( audioamp8_t *ctx );

/**
 * @brief AudioAmp 8 shut-down procedure function.
 * @details This function performs a power-down procedure 
 * of the MA12070 Filterless and High-Efficiency +4V to +26V Audio Amplifier with Analog Input
 * on the AudioAmp 8 click board™.
 * @param[in] ctx : Click context object.
 * See #audioamp8_t object definition for detailed explanation.
 * @return @li @c  0 - Success.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp8_shut_down ( audioamp8_t *ctx );

/**
 * @brief AudioAmp 8 mute function.
 * @details This function performs a mute 
 * of the MA12070 Filterless and High-Efficiency +4V to +26V Audio Amplifier with Analog Input
 * on the AudioAmp 8 click board™.
 * @param[in] ctx : Click context object.
 * See #audioamp8_t object definition for detailed explanation.
 * @return @li @c  0 - Success.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp8_set_mute ( audioamp8_t *ctx, uint8_t en_mute );

/**
 * @brief AudioAmp 8 enable function.
 * @details This function performs a enable 
 * of the MA12070 Filterless and High-Efficiency +4V to +26V Audio Amplifier with Analog Input
 * on the AudioAmp 8 click board™.
 * @param[in] ctx : Click context object.
 * See #audioamp8_t object definition for detailed explanation.
 * @return @li @c  0 - Success.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp8_set_enable ( audioamp8_t *ctx, uint8_t dev_en );

/**
 * @brief AudioAmp 8 BTL configuration function.
 * @details This function performs a BTL signal configuration, 
 * two input- and output terminals are used per channel 
 * of the MA12070 Filterless and High-Efficiency +4V to +26V Audio Amplifier with Analog Input
 * on the AudioAmp 8 click board™.
 * @param[in] ctx : Click context object.
 * See #audioamp8_t object definition for detailed explanation.
 * @return @li @c  0 - Success.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp8_btl_cfg ( audioamp8_t *ctx );

/**
 * @brief AudioAmp 8 set power mode configuration function.
 * @details This function configure power mode
 * of the MA12070 Filterless and High-Efficiency +4V to +26V Audio Amplifier with Analog Input
 * on the AudioAmp 8 click board™.
 * @param[in] ctx : Click context object.
 * See #audioamp8_t object definition for detailed explanation.
 * @param[in] pwr_mode : Power mode configuration object object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp8_set_cfg_pmode ( audioamp8_t *ctx, audioamp8_pwr_mon_cfg_t pwr_mode );

/**
 * @brief AudioAmp 8 get power mode configuration function.
 * @details This function get power mode configuration
 * of the MA12070 Filterless and High-Efficiency +4V to +26V Audio Amplifier with Analog Input
 * on the AudioAmp 8 click board™.
 * @param[in] ctx : Click context object.
 * See #audioamp8_t object definition for detailed explanation.
 * @param[out] pwr_mode : Power mode configuration object object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp8_get_cfg_pmode ( audioamp8_t *ctx, audioamp8_pwr_mon_cfg_t *pwr_mode );

/**
 * @brief AudioAmp 8 set soft-clipping and overcurrent protection latching function.
 * @details This function configure oft-clipping and overcurrent protection latching 
 * of the MA12070 Filterless and High-Efficiency +4V to +26V Audio Amplifier with Analog Input
 * on the AudioAmp 8 click board™.
 * @param[in] ctx : Click context object.
 * See #audioamp8_t object definition for detailed explanation.
 * @param[in] lf_clamp_en : Enables soft-clipping: 
 *         @li @c  0 - Disable,
 *         @li @c  1 - Enable. 
 * @param[in] ocp_latch_en : Enables soft-clipping: 
 *         @li @c  0 - Disable,
 *         @li @c  1 - Use permanently latching OCP. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp8_set_soft_copl ( audioamp8_t *ctx, uint8_t lf_clamp_en, uint8_t ocp_latch_en );

/**
 * @brief AudioAmp 8 set power mode profile configuration function.
 * @details This function configure power mode profile
 * of the MA12070 Filterless and High-Efficiency +4V to +26V Audio Amplifier with Analog Input
 * on the AudioAmp 8 click board™.
 * @param[in] ctx : Click context object.
 * See #audioamp8_t object definition for detailed explanation.
 * @param[in] pm_profile : Power mode profile configuration object object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp8_set_cfg_pmode_p ( audioamp8_t *ctx, audioamp8_pwr_mod_profile_cfg_t pm_profile );

/**
 * @brief AudioAmp 8 get power mode configuration function.
 * @details This function get power mode profile configuration
 * of the MA12070 Filterless and High-Efficiency +4V to +26V Audio Amplifier with Analog Input
 * on the AudioAmp 8 click board™.
 * @param[in] ctx : Click context object.
 * See #audioamp8_t object definition for detailed explanation.
 * @param[out] pm_profile : Power mode profile configuration object object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp8_get_cfg_pmode_p ( audioamp8_t *ctx, audioamp8_pwr_mod_profile_cfg_t *pm_profile );

/**
 * @brief AudioAmp 8 over-current protection latch clear function.
 * @details This function clears over current protection latch
 * of the MA12070 Filterless and High-Efficiency +4V to +26V Audio Amplifier with Analog Input
 * on the AudioAmp 8 click board™.
 * @param[in] ctx : Click context object.
 * See #audioamp8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp8_clr_opl ( audioamp8_t *ctx );

/**
 * @brief AudioAmp 8 set audio IN mode function.
 * @details This function set audio IN mode
 * of the MA12070 Filterless and High-Efficiency +4V to +26V Audio Amplifier with Analog Input
 * on the AudioAmp 8 click board™.
 * @param[in] ctx : Click context object.
 * See #audioamp8_t object definition for detailed explanation.
 * @param[in] audio_in_mode : Audio IN:
 *         @li @c  0 - Mode 0: 20dB gain,
 *         @li @c  1 - Mode 1: 26dB gain.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp8_set_audio_imode ( audioamp8_t *ctx, uint8_t audio_in_mode );

/**
 * @brief AudioAmp 8 set DC protection function.
 * @details This function set DC protection
 * of the MA12070 Filterless and High-Efficiency +4V to +26V Audio Amplifier with Analog Input
 * on the AudioAmp 8 click board™.
 * @param[in] ctx : Click context object.
 * See #audioamp8_t object definition for detailed explanation.
 * @param[in] eh_dcshdn : DC protection:
 *         @li @c  0 - Disable,
 *         @li @c  1 - Enable. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp8_set_dc_protection ( audioamp8_t *ctx, uint8_t eh_dcshdn );

/**
 * @brief AudioAmp 8 set audio IN mode overwrite function.
 * @details This function set audio IN mode overwrite
 * of the MA12070 Filterless and High-Efficiency +4V to +26V Audio Amplifier with Analog Input
 * on the AudioAmp 8 click board™.
 * @param[in] ctx : Click context object.
 * See #audioamp8_t object definition for detailed explanation.
 * @param[in] audio_in_mode_ext : Audio IN mode overwrite:
 *         @li @c  0 - Disable,
 *         @li @c  1 - Enable. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note . Should enabled audio IN mode function.
 */
err_t audioamp8_set_audio_imode_ow ( audioamp8_t *ctx, uint8_t audio_in_mode_ext );

/**
 * @brief AudioAmp 8 error handler clear function.
 * @details This function clears error handler 
 * of the MA12070 Filterless and High-Efficiency +4V to +26V Audio Amplifier with Analog Input
 * on the AudioAmp 8 click board™.
 * @param[in] ctx : Click context object.
 * See #audioamp8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp8_clr_err_handler ( audioamp8_t *ctx );

/**
 * @brief AudioAmp 8 monitors the status of the channel's function.
 * @details This function performs monitoring of the channel 0 or channel 1
 * of the MA12070 Filterless and High-Efficiency +4V to +26V Audio Amplifier with Analog Input
 * on the AudioAmp 8 click board™.
 * @param[in] ctx : Click context object.
 * See #audioamp8_t object definition for detailed explanation.
 * @param[in] mon_ch : Select monitor channel:
 *         @li @c  0 - Channel 0,
 *         @li @c  1 - Channel 1.
 * @param[out] ch_mon : Monitor Channel object object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp8_channel_monitoring ( audioamp8_t *ctx, uint8_t mon_ch, audioamp8_monitor_channel_t *ch_mon );

/**
 * @brief AudioAmp 8 monitor msel function.
 * @details This function performs monitoring of the signal configuration PBTL, SE/BTL, BTL, SE
 * of the MA12070 Filterless and High-Efficiency +4V to +26V Audio Amplifier with Analog Input
 * on the AudioAmp 8 click board™.
 * @param[in] ctx : Click context object.
 * See #audioamp8_t object definition for detailed explanation.
 * @param[out] msel : signal configuration: 
 *         @li @c  0 - PBTL,
 *         @li @c  1 - SE/BTL,
 *         @li @c  2 - BTL,
 *         @li @c  3 - SE.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp8_monitor_msel ( audioamp8_t *ctx, uint8_t *msel );

/**
 * @brief AudioAmp 8 get error status function.
 * @details This function read error status
 * of the MA12070 Filterless and High-Efficiency +4V to +26V Audio Amplifier with Analog Input
 * on the AudioAmp 8 click board™.
 * @param[in] ctx : Click context object.
 * See #audioamp8_t object definition for detailed explanation.
 * @param[out] error_status : Gives the live status of every potential error source. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp8_err_status ( audioamp8_t *ctx, audioamp8_error_status_t *error_status );

#ifdef __cplusplus
}
#endif
#endif // AUDIOAMP8_H

/*! @} */ // audioamp8

// ------------------------------------------------------------------------ END
