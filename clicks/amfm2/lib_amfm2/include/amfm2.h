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
 * @file amfm2.h
 * @brief This file contains API for AM/FM 2 Click Driver.
 */

#ifndef AMFM2_H
#define AMFM2_H

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
 * @addtogroup amfm2 AM/FM 2 Click Driver
 * @brief API for configuring and manipulating AM/FM 2 Click driver.
 * @{
 */

/**
 * @defgroup amfm2_reg AM/FM 2 Registers List
 * @brief List of registers of AM/FM 2 Click driver.
 */

/**
 * @addtogroup amfm2_cmd
 * @{
 */

/**
 * @brief AM/FM 2 description command.
 * @details Specified command for description of AM/FM 2 Click driver.
 */
/**
 * @brief AM/FM 2 description FM/RDS Transmitter commands.
 * @details Specified FM/RDS Transmitter Command of AM/FM 2 Click driver.
 */
#define AMFM2_CMD_POWER_UP                    0x01
#define AMFM2_CMD_GET_REV                     0x10
#define AMFM2_CMD_POWER_DOWN                  0x11
#define AMFM2_CMD_SET_PROPERTY                0x12
#define AMFM2_CMD_GET_PROPERTY                0x13
#define AMFM2_CMD_GET_INT_STATUS              0x14
#define AMFM2_CMD_PATCH_ARGS                  0x15
#define AMFM2_CMD_PATCH_DATA                  0x16
#define AMFM2_CMD_TX_TUNE_FREQ                0x30
#define AMFM2_CMD_TX_TUNE_POWER               0x31
#define AMFM2_CMD_TX_TUNE_MEASURE             0x32
#define AMFM2_CMD_TX_TUNE_STATUS              0x33
#define AMFM2_CMD_TX_ASQ_STATUS               0x34
#define AMFM2_CMD_TX_RDS_BUFF                 0x35
#define AMFM2_CMD_TX_TX_RDS_PS                0x36
#define AMFM2_CMD_GPIO_CTL                    0x80
#define AMFM2_CMD_GPIO_SET                    0x81

/**
 * @brief AM/FM 2 description AM/LW/SW Receiver commands.
 * @details Specified AM/LW/SW Receiver Command commands of AM/FM 2 Click driver.
 */
#define AMFM2_CMD_AM_TUNE_FREQ                0x40
#define AMFM2_CMD_AM_SEEK_START               0x41
#define AMFM2_CMD_AM_TUNE_STATUS              0x42
#define AMFM2_CMD_AM_RSQ_STATUS               0x43
#define AMFM2_CMD_AM_AGC_STATUS               0x47
#define AMFM2_CMD_AM_AGC_OVERRIDE             0x48

/**
 * @brief AM/FM 2 description FM/RDS Receiver commands.
 * @details Specified FM/RDS Receiver commands of AM/FM 2 Click driver.
 */
#define AMFM2_CMD_FM_TUNE_FREQ                0x20
#define AMFM2_CMD_FM_SEEK_START               0x21
#define AMFM2_CMD_FM_TUNE_STATUS              0x22
#define AMFM2_CMD_FM_RSQ_STATUS               0x23
#define AMFM2_CMD_FM_RDS_STATUS               0x24
#define AMFM2_CMD_FM_AGC_STATUS               0x27
#define AMFM2_CMD_FM_AGC_OVERRIDE             0x28

/*! @} */ // amfm2_cmd

/**
 * @defgroup amfm2_set AM/FM 2 Registers Settings
 * @brief Settings for registers of AM/FM 2 Click driver.
 */

/**
 * @addtogroup amfm2_set
 * @{
 */

/**
 * @brief AM/FM 2 description respond status.
 * @details Specified setting for description of AM FM 2 Click driver.
 */
#define AMFM2_RSP_STATUS_CTS                  0x80
#define AMFM2_RSP_STATUS_ERROR                0x40
#define AMFM2_RSP_STATUS_RDSINT               0x04
#define AMFM2_RSP_STATUS_ASQINT               0x02
#define AMFM2_RSP_STATUS_STCINT               0x01

/**
 * @brief AM/FM 2 description arguments data value.
 * @details Specified arguments data value of AM/FM 2 Click driver.
 */
#define AMFM2_PWRUP_ARG_CTSIEN                0x80
#define AMFM2_PWRUP_ARG_GPO2OEN               0x40
#define AMFM2_PWRUP_ARG_PATCH                 0x20
#define AMFM2_PWRUP_ARG_XOSCEN                0x10
#define AMFM2_PWRUP_ARG_FUNC_FMRECEIVE        0x00
#define AMFM2_PWRUP_ARG_FUNC_QUERYLIBID       0x0F
#define AMFM2_PWRUP_ARG_OPMODE_ANALOGOUT      0x05
#define AMFM2_PWRUP_ARG_OPMODE_DIGITALOUT     0x0B
#define AMFM2_PWRUP_ARG_OPMODE_DIGITALOUTS    0xB0
#define AMFM2_FMTUNEFREQ_ARG_FREEZE           0x02
#define AMFM2_FMTUNEFREQ_ARG_FAST             0x01
#define AMFM2_FMSEEKSTART_ARG_SEEKUP          0x08
#define AMFM2_FMSEEKSTART_ARG_WRAP            0x04
#define AMFM2_FMTUNESTATUS_ARG_CANCEL         0x02
#define AMFM2_FMTUNESTATUS_ARG_INTACK         0x01
#define AMFM2_FMRSQSTATUS_ARG_INTACK          0x01
#define AMFM2_FMRDSSTATUS_ARG_STATUSONLY      0x04
#define AMFM2_FMRDSSTATUS_ARG_MTFIFO          0x02
#define AMFM2_FMRDSSTATUS_ARG_INTACK          0x01
#define AMFM2_FMAGCOVERRIDE_ARG_RFAGCDIS      0x01
#define AMFM2_GPIOCTL_ARG_GPO3OEN             0x08
#define AMFM2_GPIOCTL_ARG_GPO2OEN             0x04
#define AMFM2_GPIOCTL_ARG_GPO1OEN             0x02
#define AMFM2_GPIOSET_ARG_GPO3LEVEL           0x08
#define AMFM2_GPIOSET_ARG_GPO2LEVEL           0x04
#define AMFM2_GPIOSET_ARG_GPO1LEVEL           0x02

/**
 * @brief AM/FM 2 description volume data value.
 * @details Specified volume data value of AM/FM 2 Click driver.
 */
#define AMFM2_SET_VOLUME_MUTE                 0
#define AMFM2_SET_VOLUME_MAX                  63

/**
 * @brief AM/FM 2 description properties AMFM data value.
 * @details Specified properties AMFM data value of AM/FM 2 Click driver.
 */
#define AMFM2_PROP_GPOIEN_H                   0x00
#define AMFM2_PROP_GPOIEN_L                   0x01
#define AMFM2_PROP_DIGITALOUTFORMAT_H         0x01
#define AMFM2_PROP_DIGITALOUTFORMAT_L         0x02
#define AMFM2_PROP_DIGITALOUTSAMPLERATE_H     0x01
#define AMFM2_PROP_DIGITALOUTSAMPLERATE_L     0x04
#define AMFM2_PROP_REFCLKFREQ_H               0x02
#define AMFM2_PROP_REFCLKFREQ_L               0x01
#define AMFM2_PROP_REFCLKPRESCALE_H           0x02
#define AMFM2_PROP_REFCLKPRESCALE_L           0x02
#define AMFM2_PROP_RXVOLUME_H                 0x40
#define AMFM2_PROP_RXVOLUME_L                 0x00
#define AMFM2_PROP_RXHMUTE_H                  0x40
#define AMFM2_PROP_RXHMUTE_L                  0x01

/**
 * @brief AM/FM 2 description properties AM data value.
 * @details Specified properties AM data value of AM/FM 2 Click driver.
 */
#define AMFM2_PROP_FMDEEMPHASIS_H             0x11
#define AMFM2_PROP_FMDEEMPHASIS_L             0x00
#define AMFM2_PROP_AMDEEMPHASIS_H             0x31
#define AMFM2_PROP_AMDEEMPHASIS_L             0x00
#define AMFM2_PROP_FMCHANFILTER_H             0x11
#define AMFM2_PROP_FMCHANFILTER_L             0x02
#define AMFM2_PROP_AMCHANFILTER_H             0x31
#define AMFM2_PROP_AMCHANFILTER_L             0x02
#define AMFM2_PROP_AMRSQINTS_H                0x32
#define AMFM2_PROP_AMRSQINTS_L                0x00
#define AMFM2_PROP_AMNBRATE_H                 0x39
#define AMFM2_PROP_AMNBRATE_L                 0x02
#define AMFM2_PROP_AMNBIIRFILTER_H            0x39
#define AMFM2_PROP_AMNBIIRFILTER_L            0x03
#define AMFM2_PROP_AMNBDELAY_H                0x39
#define AMFM2_PROP_AMNBDELAY_L                0x04

/**
 * @brief AM/FM 2 description properties FM data value.
 * @details Specified properties FM data value of AM/FM 2 Click driver.
 */
#define AMFM2_PROP_FMBLENDSTEREOTHS_H         0x11
#define AMFM2_PROP_FMBLENDSTEREOTHS_L         0x05
#define AMFM2_PROP_FMBLENDMONOTHS_H           0x11
#define AMFM2_PROP_FMBLENDMONOTHS_L           0x06
#define AMFM2_PROP_FMNBDETECTTHS_H            0x19
#define AMFM2_PROP_FMNBDETECTTHS_L            0x00
#define AMFM2_PROP_FMNBINTERVAL_H             0x19
#define AMFM2_PROP_FMNBINTERVAL_L             0x01
#define AMFM2_PROP_FMNBRATE_H                 0x19
#define AMFM2_PROP_FMNBRATE_L                 0x02
#define AMFM2_PROP_FMNBIIRFILTER_H            0x19
#define AMFM2_PROP_FMNBIIRFILTER_L            0x03
#define AMFM2_PROP_FMNBDELAY_H                0x19
#define AMFM2_PROP_FMNBDELAY_L                0x04

/**
 * @brief AM/FM 2 description properties data value.
 * @details Specified properties data value of AM/FM 2 Click driver.
 */
#define AMFM2_PROPVALH_RSQREP                 0x08
#define AMFM2_PROPVALH_RDSREP                 0x04
#define AMFM2_PROPVALH_STCREP                 0x01
#define AMFM2_PROPVALL_CTSIEN                 0x80
#define AMFM2_PROPVALL_ERRIEN                 0x40
#define AMFM2_PROPVALL_RSQIEN                 0x08
#define AMFM2_PROPVALL_RDSIEN                 0x04
#define AMFM2_PROPVALL_STCIEN                 0x01
#define AMFM2_PROPVALL_OFALL                  0x80
#define AMFM2_PROPVALL_LMUTE                  0x02
#define AMFM2_PROPVALL_RMUTE                  0x01

/**
 * @brief AM/FM 2 device address setting.
 * @details Specified setting for device slave address selection of
 * AM/FM 2 Click driver.
 */
#define AMFM2_DEVICE_ADDRESS_GND              0x11
#define AMFM2_DEVICE_ADDRESS_VCC              0x63

/*! @} */ // amfm2_set

/**
 * @defgroup amfm2_map AM/FM 2 MikroBUS Map
 * @brief MikroBUS pin mapping of AM/FM 2 Click driver.
 */

/**
 * @addtogroup amfm2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of AM/FM 2 Click to the selected MikroBUS.
 */
#define AMFM2_MAP_MIKROBUS( cfg, mikrobus )       \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.ema = MIKROBUS( mikrobus, MIKROBUS_AN );  \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.gp1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.gp2 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // amfm2_map
/*! @} */ // amfm2

/**
 * @brief AM/FM 2 Click context object.
 * @details Context object definition of AM/FM 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t ema;    /**< Enable Headphone Amplifier pin. */
    digital_out_t rst;    /**< Reset pin. */

    // Input pins
    digital_in_t gp1;    /**< GP1 input pin. */
    digital_in_t gp2;    /**< GP2 input pin. */

    // Modules
    i2c_master_t i2c;    /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} amfm2_t;

/**
 * @brief AM/FM 2 Click configuration object.
 * @details Configuration object definition of AM/FM 2 Click driver.
 */
typedef struct
{
    pin_name_t scl;    /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;    /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t ema;    /**< Enable Headphone Amplifier pin. */
    pin_name_t rst;    /**< Reset pin. */
    pin_name_t gp1;    /**< GP1 input pin. */
    pin_name_t gp2;    /**< GP2 input pin. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

} amfm2_cfg_t;

/**
 * @brief AM/FM 2 Click device information object.
 * @details Device information object definition of AM/FM 2 Click driver.
 */
typedef struct
{
    uint8_t  pn;          /**< Part Number. */
    uint8_t  fwmajor;     /**< Major Revision. */
    uint8_t  fwminor;     /**< Firmware Minor Revision. */
    uint16_t patch;       /**< Patch ID. */
    uint8_t  cmpmajor;    /**< Component Major Revision. */
    uint8_t  cmpminor;    /**< Component Minor Revision. */
    uint8_t  chiprev;     /**< Chip Revision. */

} amfm2_device_info_t;

/**
 * @brief AM/FM 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AMFM2_OK = 0,
    AMFM2_ERROR = -1

} amfm2_return_value_t;

/*!
 * @addtogroup amfm2 AM/FM 2 Click Driver
 * @brief API for configuring and manipulating AM/FM 2 Click driver.
 * @{
 */

/**
 * @brief AM/FM 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #amfm2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void amfm2_cfg_setup ( amfm2_cfg_t *cfg );

/**
 * @brief AM/FM 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #amfm2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #amfm2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t amfm2_init ( amfm2_t *ctx, amfm2_cfg_t *cfg );

/**
 * @brief AM/FM 2 default configuration function.
 * @details This function executes a default configuration of AM/FM 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #amfm2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t amfm2_default_cfg ( amfm2_t *ctx );

/**
 * @brief AM/FM 2 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #amfm2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t amfm2_write_data ( amfm2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief AM/FM 2 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #amfm2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t amfm2_generic_read ( amfm2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief AM/FM 2 hardware reset function.
 * @details This function perform a hardware reset
 * of the Si4732-A10, Broadcast AM/FM/SW/LW/RDS Radio Receiver
 * on the AM/FM 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #amfm2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void amfm2_hw_reset ( amfm2_t *ctx );

/**
 * @brief AM/FM 2 enable headphone amp function.
 * @details This function enable the headphone amplifier
 * of the LM4910, Output Capacitor-less Stereo 35mW Headphone Amplifier
 * on the AM/FM 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #amfm2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void amfm2_headphone_amp_enable ( amfm2_t *ctx );

/**
 * @brief AM/FM 2 disable headphone amp function.
 * @details This function disables the headphone amplifier
 * of the LM4910, Output Capacitor-less Stereo 35mW Headphone Amplifier
 * on the AM/FM 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #amfm2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void amfm2_headphone_amp_disable ( amfm2_t *ctx );

/**
 * @brief AM/FM 2 get state of GP1 pin function.
 * @details This function gets states of the GP1 ( PWM ) pin
 * of the Si4732-A10, Broadcast AM/FM/SW/LW/RDS Radio Receiver
 * on the AM/FM 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #amfm2_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t amfm2_get_gp1 ( amfm2_t *ctx );

/**
 * @brief AM/FM 2 get state of GP2 pin function.
 * @details This function gets states of the GP2 ( INT ) pin
 * of the Si4732-A10, Broadcast AM/FM/SW/LW/RDS Radio Receiver
 * on the AM/FM 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #amfm2_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t amfm2_get_gp2 ( amfm2_t *ctx );

/**
 * @brief AM/FM 2 set state of RST pin function.
 * @details This function sets states of the RST pin
 * of the Si4732-A10, Broadcast AM/FM/SW/LW/RDS Radio Receiver
 * on the AM/FM 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #amfm2_t object definition for detailed explanation.
 * @param[in] pin_state : RST pin state.
 * @return Nothing.
 * @note None.
 */
void amfm2_set_rst ( amfm2_t *ctx, uint8_t pin_state );

/**
 * @brief AM/FM 2 wait response function.
 * @details This function wait for an response 
 * of the Si4732-A10, Broadcast AM/FM/SW/LW/RDS Radio Receiver
 * on the AM/FM 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #amfm2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t amfm2_wait_rsp ( amfm2_t *ctx );

/**
 * @brief AM/FM 2 set command function.
 * @details This function set the desired command and accompanying arguments
 * of the Si4732-A10, Broadcast AM/FM/SW/LW/RDS Radio Receiver
 * on the AM/FM 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #amfm2_t object definition for detailed explanation.
 * @param[in] cmd : Desired command.
 * @param[in] arg : Desired argument.
 * @param[in] arg_len : Number of bytes of argument.
 * @param[out] rsp : Response.
 * @param[in] rsp_len : Number of bytes of response.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t amfm2_set_command ( amfm2_t *ctx, uint8_t cmd, uint8_t *arg, 
                          uint8_t arg_len, uint8_t *rsp, uint8_t rsp_len );

/**
 * @brief AM/FM 2 get response function.
 * @details This function set the desired command and accompanying arguments
 * of the Si4732-A10, Broadcast AM/FM/SW/LW/RDS Radio Receiver
 * on the AM/FM 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #amfm2_t object definition for detailed explanation.
 * @param[out] rsp : Response.
 * @param[in] rsp_len : Number of bytes of response.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t amfm2_get_response ( amfm2_t *ctx, uint8_t *rsp, uint8_t rsp_len );

/**
 * @brief AM/FM 2 get revision information function.
 * @details This function reads the revision information 
 * of the Si4732-A10, Broadcast AM/FM/SW/LW/RDS Radio Receiver
 * on the AM/FM 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #amfm2_t object definition for detailed explanation.
 * @param[out] rev : Revision information object.
 * See amfm2_device_info_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t amfm2_get_rev ( amfm2_t *ctx, amfm2_device_info_t *rev );

/**
 * @brief AM/FM 2 seek station function.
 * @details This function searching for a valid radio frequency
 * of the Si4732-A10, Broadcast AM/FM/SW/LW/RDS Radio Receiver
 * on the AM/FM 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #amfm2_t object definition for detailed explanation.
 * @param[out] rsp : Response.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t amfm2_seek_station ( amfm2_t *ctx, uint8_t *rsp );

/**
 * @brief AM/FM 2 set volume function.
 * @details This function sets the desired volume
 * of the Si4732-A10, Broadcast AM/FM/SW/LW/RDS Radio Receiver
 * on the AM/FM 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #amfm2_t object definition for detailed explanation.
 * @param[out] volume : Volume [0-63].
 * @param[out] rsp : Response.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t amfm2_set_volume ( amfm2_t *ctx, uint8_t volume, uint8_t *rsp );

/**
 * @brief AM/FM 2 sound off function.
 * @details This function turns off the sound
 * of the Si4732-A10, Broadcast AM/FM/SW/LW/RDS Radio Receiver
 * on the AM/FM 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #amfm2_t object definition for detailed explanation.
 * @param[out] rsp : Response.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t amfm2_sound_off ( amfm2_t *ctx, uint8_t *rsp );

/**
 * @brief AM/FM 2 sound on function.
 * @details This function turns on the sound
 * of the Si4732-A10, Broadcast AM/FM/SW/LW/RDS Radio Receiver
 * on the AM/FM 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #amfm2_t object definition for detailed explanation.
 * @param[out] rsp : Response.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t amfm2_sound_on ( amfm2_t *ctx, uint8_t *rsp );

/**
 * @brief AM/FM 2 tuning frequency up function.
 * @details This function queries about the status of previous 
 * and selects the FM tuning frequency up
 * of the Si4732-A10, Broadcast AM/FM/SW/LW/RDS Radio Receiver
 * on the AM/FM 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #amfm2_t object definition for detailed explanation.
 * @param[out] rsp : Response.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t amfm2_tuning_freq_up ( amfm2_t *ctx, uint8_t *rsp );

/**
 * @brief AM/FM 2 tuning frequency down function.
 * @details This function queries about the status of previous 
 * and selects the FM tuning frequency down
 * of the Si4732-A10, Broadcast AM/FM/SW/LW/RDS Radio Receiver
 * on the AM/FM 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #amfm2_t object definition for detailed explanation.
 * @param[out] rsp : Response.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t amfm2_tuning_freq_down ( amfm2_t *ctx, uint8_t *rsp );

/**
 * @brief AM/FM 2 tuning frequency function.
 * @details This function selects the FM tuning frequency
 * of the Si4732-A10, Broadcast AM/FM/SW/LW/RDS Radio Receiver
 * on the AM/FM 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #amfm2_t object definition for detailed explanation.
 * @param[in] frequency : Desired radio frequency [64MHz–108MHz].
 * @param[out] rsp : Response.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t amfm2_tuning_freq ( amfm2_t *ctx, float frequency, uint8_t *rsp );

/**
 * @brief AM/FM 2 get tuning frequency function.
 * @details This function gets the FM tuning frequency
 * of the Si4732-A10, Broadcast AM/FM/SW/LW/RDS Radio Receiver
 * on the AM/FM 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #amfm2_t object definition for detailed explanation.
 * @param[out] frequency : Radio frequency [MHz].
 * @param[out] rsp : Response.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t amfm2_get_tuning_freq ( amfm2_t *ctx, float *frequency );

/**
 * @brief AM/FM 2 check CTS function.
 * @details his function checks the status of the clear to send
 * of the Si4732-A10, Broadcast AM/FM/SW/LW/RDS Radio Receiver
 * on the AM/FM 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #amfm2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t amfm2_check_clear_to_send ( amfm2_t *ctx );

/**
 * @brief AM/FM 2 check CTS function.
 * @details This function checks the status of the clear to send
 * of the Si4732-A10, Broadcast AM/FM/SW/LW/RDS Radio Receiver
 * on the AM/FM 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #amfm2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t amfm2_check_seek_tune_complete ( amfm2_t *ctx );

/**
 * @brief AM/FM 2 check status error function.
 * @details This function checks the status of the error
 * of the Si4732-A10, Broadcast AM/FM/SW/LW/RDS Radio Receiver
 * on the AM/FM 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #amfm2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t amfm2_check_status_error ( amfm2_t *ctx );

/**
 * @brief AM/FM 2 check RDS interrupt function.
 * @details This function checks the status of the RDS interrupt
 * of the Si4732-A10, Broadcast AM/FM/SW/LW/RDS Radio Receiver
 * on the AM/FM 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #amfm2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t amfm2_check_rds_interrupt ( amfm2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // AMFM2_H

/*! @} */ // amfm2

// ------------------------------------------------------------------------ END
