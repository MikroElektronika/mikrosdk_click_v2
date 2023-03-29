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
 * @file lightranger5.h
 * @brief This file contains API for LightRanger 5 Click Driver.
 */

#ifndef LIGHTRANGER5_H
#define LIGHTRANGER5_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
    
/*!
 * @addtogroup lightranger5 LightRanger 5 Click Driver
 * @brief API for configuring and manipulating LightRanger 5 Click driver.
 * @{
 */

/**
 * @defgroup lightranger5_reg LightRanger 5 Registers List
 * @brief List of registers of LightRanger 5 Click driver.
 */

/**
 * @addtogroup lightranger5_reg
 * @{
 */

/**
 * @brief LightRanger 5 description register.
 * @details Specified register for description of LightRanger 5 Click driver.
 */
#define LIGHTRANGER5_REG_APPID                                          0x00
#define LIGHTRANGER5_REG_APPREQID                                       0x02
#define LIGHTRANGER5_REG_APPREV_MAJOR                                   0x01
#define LIGHTRANGER5_REG_APPREV_MINOR                                   0x12
#define LIGHTRANGER5_REG_APPREV_PATCH                                   0x13
#define LIGHTRANGER5_REG_CMD_DATA9                                      0x06
#define LIGHTRANGER5_REG_CMD_DATA8                                      0x07
#define LIGHTRANGER5_REG_CMD_DATA7                                      0x08
#define LIGHTRANGER5_REG_CMD_DATA6                                      0x09
#define LIGHTRANGER5_REG_CMD_DATA5                                      0x0A
#define LIGHTRANGER5_REG_CMD_DATA4                                      0x0B
#define LIGHTRANGER5_REG_CMD_DATA3                                      0x0C
#define LIGHTRANGER5_REG_CMD_DATA2                                      0x0D
#define LIGHTRANGER5_REG_CMD_DATA1                                      0x0E
#define LIGHTRANGER5_REG_CMD_DATA0                                      0x0F
#define LIGHTRANGER5_REG_COMMAND                                        0x10
#define LIGHTRANGER5_REG_PREVIOUS                                       0x11
#define LIGHTRANGER5_REG_STATUS                                         0x1D
#define LIGHTRANGER5_REG_REGISTER_CONTENTS                              0x1E
#define LIGHTRANGER5_REG_TID                                            0x1F
#define LIGHTRANGER5_REG_RESULT_NUMBER                                  0x20
#define LIGHTRANGER5_REG_RESULT_INFO                                    0x21
#define LIGHTRANGER5_REG_DISTANCE_PEAK_0                                0x22
#define LIGHTRANGER5_REG_DISTANCE_PEAK_1                                0x23
#define LIGHTRANGER5_REG_SYS_CLOCK_0                                    0x24
#define LIGHTRANGER5_REG_SYS_CLOCK_1                                    0x25
#define LIGHTRANGER5_REG_SYS_CLOCK_2                                    0x26
#define LIGHTRANGER5_REG_SYS_CLOCK_3                                    0x27
#define LIGHTRANGER5_REG_STATE_DATA_0                                   0x28
#define LIGHTRANGER5_REG_STATE_DATA_1                                   0x29
#define LIGHTRANGER5_REG_STATE_DATA_2                                   0x2A
#define LIGHTRANGER5_REG_STATE_DATA_3                                   0x2B
#define LIGHTRANGER5_REG_STATE_DATA_4                                   0x2C
#define LIGHTRANGER5_REG_STATE_DATA_5                                   0x2D
#define LIGHTRANGER5_REG_STATE_DATA_6                                   0x2E
#define LIGHTRANGER5_REG_STATE_DATA_7                                   0x2F
#define LIGHTRANGER5_REG_STATE_DATA_8_XTALK_MSB                         0x30
#define LIGHTRANGER5_REG_STATE_DATA_9_XTALK_LSB                         0x31
#define LIGHTRANGER5_REG_STATE_DATA_10_TJ                               0x32
#define LIGHTRANGER5_REG_REFERENCE_HITS_0                               0x33
#define LIGHTRANGER5_REG_REFERENCE_HITS_1                               0x34
#define LIGHTRANGER5_REG_REFERENCE_HITS_2                               0x35
#define LIGHTRANGER5_REG_REFERENCE_HITS_3                               0x36
#define LIGHTRANGER5_REG_OBJECT_HITS_0                                  0x37
#define LIGHTRANGER5_REG_OBJECT_HITS_1                                  0x38
#define LIGHTRANGER5_REG_OBJECT_HITS_2                                  0x39
#define LIGHTRANGER5_REG_OBJECT_HITS_3                                  0x3A
#define LIGHTRANGER5_REG_FACTORY_CALIB_0                                0x20
#define LIGHTRANGER5_REG_STATE_DATA_WR_0                                0x2E
#define LIGHTRANGER5_REG_ENABLE                                         0xE0
#define LIGHTRANGER5_REG_INT_STATUS                                     0xE1
#define LIGHTRANGER5_REG_INT_ENAB                                       0xE2
#define LIGHTRANGER5_REG_DEVICE_ID                                      0xE3
#define LIGHTRANGER5_REG_REVID                                          0xE4

/*! @} */ // lightranger5_reg

/**
 * @defgroup lightranger5_set LightRanger 5 Registers Settings
 * @brief Settings for registers of LightRanger 5 Click driver.
 */

/**
 * @addtogroup lightranger5_set
 * @{
 */

/**
 * @brief LightRanger 5 description setting.
 * @details Specified setting for description of LightRanger 5 Click driver.
 */

/**
 * @brief LightRanger 5 device command setting.
 * @details Specified setting for device command selection of
 * LightRanger 5 Click driver.
 */
#define LIGHTRANGER5_CMD_NO_COMMAND                                     0x00
#define LIGHTRANGER5_CMD_DISTANCE_MEASURE_MODE_1                        0x02
#define LIGHTRANGER5_CMD_FACTORY_CALIB                                  0x0A
#define LIGHTRANGER5_CMD_DL_CALIB_AND_STATE                             0x0B
#define LIGHTRANGER5_CMD_RESULT                                         0x55

/**
 * @brief LightRanger 5 device app mode setting.
 * @details Specified setting for device app mode selection of
 * LightRanger 5 Click driver.
 */
#define LIGHTRANGER5_APPID_MEASUREMENT                                  0xC0
#define LIGHTRANGER5_APPID_BOOTLOADER                                   0x80
#define LIGHTRANGER5_EXPECTED_ID                                        0x07
#define LIGHTRANGER5_CALIB_DATA                                         0x0A
#define LIGHTRANGER5_SERIAL_NUMBER                                      0x47
#define LIGHTRANGER5_BIT_CPU_RDY                                        0x40
#define LIGHTRANGER5_ENABLE_RESET                                       0x80

/**
 * @brief LightRanger 5 device address setting.
 * @details Specified setting for device slave address selection of
 * LightRanger 5 Click driver.
 */
#define LIGHTRANGER5_SET_DEV_ADDR                                       0x41

/*! @} */ // lightranger5_set

/**
 * @addtogroup lightranger5_get
 * @{
 */

/**
 * @brief LightRanger 5 status data.
 * @details Specified status data for description of LightRanger 5 Click driver.
 */ 
#define LIGHTRANGER5_STATUS_IDLE                                        0x00
#define LIGHTRANGER5_STATUS_DIAGNOSTIC                                  0x01
#define LIGHTRANGER5_STATUS_START                                       0x02
#define LIGHTRANGER5_STATUS_CALIBRATION                                 0x03
#define LIGHTRANGER5_STATUS_LIGHTCOL                                    0x04
#define LIGHTRANGER5_STATUS_ALGORITHM                                   0x05
#define LIGHTRANGER5_STATUS_STARTUP                                     0x06
#define LIGHTRANGER5_STATUS_OK                                          0x0F
#define LIGHTRANGER5_STATUS_VCSEL_PWR_FAIL                              0x10
#define LIGHTRANGER5_STATUS_VCSEL_LED_A_FAIL                            0x11
#define LIGHTRANGER5_STATUS_VCSEL_LED_K_FAIL                            0x12
#define LIGHTRANGER5_STATUS_INVALID_PARAM                               0x18
#define LIGHTRANGER5_STATUS_INVALID_DEVICE                              0x19
#define LIGHTRANGER5_STATUS_CALIB_ERROR                                 0x1B
#define LIGHTRANGER5_STATUS_INVALID_COMMAND                             0x1C
#define LIGHTRANGER5_STATUS_INVALID_STATE                               0x1D
#define LIGHTRANGER5_STATUS_ERR_ALGORITHM                               0x1F


/*! @} */ // lightranger5_get

/**
 * @defgroup lightranger5_map LightRanger 5 MikroBUS Map
 * @brief MikroBUS pin mapping of LightRanger 5 Click driver.
 */

/**
 * @addtogroup lightranger5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LightRanger 5 Click to the selected MikroBUS.
 */
#define LIGHTRANGER5_MAP_MIKROBUS( cfg, mikrobus )  \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL );   \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );   \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS );     \
    cfg.io0 = MIKROBUS( mikrobus, MIKROBUS_RST );   \
    cfg.io1 = MIKROBUS( mikrobus, MIKROBUS_PWM );   \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // lightranger5_map
/*! @} */ // lightranger5

/**
 * @brief LightRanger 5 Click context object.
 * @details Context object definition of LightRanger 5 Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t  en;        /**< Enable pin. */
    digital_out_t  io0;       /**< General purpose pin. */
    digital_out_t  io1;       /**< General purpose pin. */
    
    // Input pins

    digital_in_t  int_pin;    /**< Interrupt pin. */

    // Modules

    i2c_master_t i2c;         /**< I2C driver object. */
                              
    // I2C slave address      
                              
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} lightranger5_t;

/**
 * @brief LightRanger 5 Click configuration object.
 * @details Configuration object definition of LightRanger 5 Click driver.
 */
typedef struct
{
    pin_name_t  scl;          /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;          /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  en;           /**< Enable pin. */
    pin_name_t  io0;          /**< General purpose pin. */
    pin_name_t  io1;          /**< General purpose pin. */
    pin_name_t  int_pin;      /**< Interrupt pin. */

    uint32_t  i2c_speed;      /**< I2C serial speed. */
    uint8_t   i2c_address;    /**< I2C slave address. */

} lightranger5_cfg_t;

/**
 * @brief LightRanger 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   LIGHTRANGER5_OK = 0,
   LIGHTRANGER5_ERROR = -1

} lightranger5_return_value_t;

/**
 * @brief LightRanger 5 Click return data ready.
 * @details Predefined enum values for driver return data ready values.
 */
typedef enum
{
   LIGHTRANGER5_DATA_NOT_READY = 0,
   LIGHTRANGER5_DATA_IS_READY = 1

} lightranger5_return_data_ready_t;

/*!
 * @addtogroup lightranger5 LightRanger 5 Click Driver
 * @brief API for configuring and manipulating LightRanger 5 Click driver.
 * @{
 */

/**
 * @brief LightRanger 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lightranger5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @endcode
 */
void lightranger5_cfg_setup ( lightranger5_cfg_t *cfg );

/**
 * @brief LightRanger 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #lightranger5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lightranger5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t lightranger5_init ( lightranger5_t *ctx, lightranger5_cfg_t *cfg );

/**
 * @brief LightRanger 5 default configuration function.
 * @details This function executes a default configuration of LightRanger 5
 * click board.
 * @param[in] ctx : Click context object.
 * See #lightranger5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 *
 * @endcode
 */
err_t lightranger5_default_cfg ( lightranger5_t *ctx );

/**
 * @brief LightRanger 5 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t lightranger5_generic_write ( lightranger5_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief LightRanger 5 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t lightranger5_generic_read ( lightranger5_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );


/**
 * @brief LightRanger 5 enable device function.
 * @details This function enables the device by sets EN ( CS ) pin to high state of the 
 * TMF8801, Time-of-Flight Sensor on the LightRanger 5 click board™.
 * @param[in] ctx : Click context object.
 * See #lightranger5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t lightranger5_enable_device ( lightranger5_t *ctx );

/**
 * @brief LightRanger 5 disable device function.
 * @details This function disables the device by sets EN ( CS ) pin to low state of the 
 * TMF8801, Time-of-Flight Sensor on the LightRanger 5 click board™.
 * @param[in] ctx : Click context object.
 * See #lightranger5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t lightranger5_disable_device ( lightranger5_t *ctx );

/**
 * @brief LightRanger 5 set IO0 pin state function.
 * @details This function sets the state of the IO0 ( RST ) pin of the 
 * TMF8801, Time-of-Flight Sensor on the LightRanger 5 click board™.
 * @param[in] ctx : Click context object.
 * See #lightranger5_t object definition for detailed explanation.
 * @param[in] io0_state :
 *         @li @c  0 - Low pin state,
 *         @li @c  1 - High pin state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t lightranger5_set_pin_state_io0 ( lightranger5_t *ctx, uint8_t io0_state );

/**
 * @brief LightRanger 5 set IO1 pin state function.
 * @details This function sets the state of the IO1 ( PWM ) pin of the 
 * TMF8801, Time-of-Flight Sensor on the LightRanger 5 click board™.
 * @param[in] ctx : Click context object.
 * See #lightranger5_t object definition for detailed explanation.
 * @param[in] io1_state :
 *         @li @c  0 - Low pin state,
 *         @li @c  1 - High pin state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t lightranger5_set_pin_state_io1 ( lightranger5_t *ctx, uint8_t io1_state );

/**
 * @brief LightRanger 5 device reset function.
 * @details This function performs a software reset device and 
 * fully resetting CPU and all CPU registers of the 
 * TMF8801, Time-of-Flight Sensor on the LightRanger 5 click board™.
 * @param[in] ctx : Click context object.
 * See #lightranger5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t lightranger5_device_reset ( lightranger5_t *ctx );

/**
 * @brief LightRanger 5 load app function.
 * @details This function set application that shall be started, 
 * set this to measurement app mode of the
 * TMF8801, Time-of-Flight Sensor on the LightRanger 5 click board™.
 * @param[in] ctx : Click context object.
 * See #lightranger5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t lightranger5_load_app ( lightranger5_t *ctx );

/**
 * @brief LightRanger 5 start calibration function.
 * @details This function start the calibration of the
 * TMF8801, Time-of-Flight Sensor on the LightRanger 5 click board™.
 * @param[in] ctx : Click context object.
 * See #lightranger5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t lightranger5_start_calib_cmd ( lightranger5_t *ctx );

/**
 * @brief LightRanger 5 check factory calibration function.
 * @details This function check the factory calibration, check device ID and
 * currently running application status of the
 * TMF8801, Time-of-Flight Sensor on the LightRanger 5 click board™.
 * @param[in] ctx : Click context object.
 * See #lightranger5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t lightranger5_check_factory_calibration ( lightranger5_t *ctx );

/**
 * @brief LightRanger 5 get status function.
 * @details This function get status data of the
 * TMF8801, Time-of-Flight Sensor on the LightRanger 5 click board™.
 * @param[in] ctx : Click context object.
 * See #lightranger5_t object definition for detailed explanation.
 * @param[out] status : Status data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t lightranger5_get_status ( lightranger5_t *ctx, uint8_t *status );

/**
 * @brief LightRanger 5 set command function.
 * @details This function set the command of the
 * TMF8801, Time-of-Flight Sensor on the LightRanger 5 click board™.
 * @param[in] ctx : Click context object.
 * See #lightranger5_t object definition for detailed explanation.
 * @param[in] cmd : Command data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t lightranger5_set_command ( lightranger5_t *ctx, uint8_t cmd );

/**
 * @brief LightRanger 5 set factory calib data function.
 * @details This function set the factory calibration data of the
 * TMF8801, Time-of-Flight Sensor on the LightRanger 5 click board™.
 * @param[in] ctx : Click context object.
 * See #lightranger5_t object definition for detailed explanation.
 * @param[in] factory_calib_data : Pointer to the memory location where factory calibration data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function shall be pre-loaded by the host before command 
 * LIGHTRANGER5_CMD_DISTANCE_MEASURE_MODE_1 or LIGHTRANGER5_CMD_DL_CALIB_AND_STATE.
 *
 * @endcode
 */
err_t lightranger5_set_factory_calib_data ( lightranger5_t *ctx, uint8_t *factory_calib_data );

/**
 * @brief LightRanger 5 get factory calib data function.
 * @details This function get the factory calibration data of the
 * TMF8801, Time-of-Flight Sensor on the LightRanger 5 click board™.
 * @param[in] ctx : Click context object.
 * See #lightranger5_t object definition for detailed explanation.
 * @param[out] factory_calib_data : Pointer to the memory location where factory calibration data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function shall be pre-loaded by the host before command 
 * LIGHTRANGER5_CMD_DISTANCE_MEASURE_MODE_1 or LIGHTRANGER5_CMD_DL_CALIB_AND_STATE.
 *
 * @endcode
 */
err_t lightranger5_get_factory_calib_data ( lightranger5_t *ctx, uint8_t *factory_calib_data );

/**
 * @brief LightRanger 5 set algorithm state data function.
 * @details This function set algorithm state data array of the
 * TMF8801, Time-of-Flight Sensor on the LightRanger 5 click board™.
 * @param[in] ctx : Click context object.
 * See #lightranger5_t object definition for detailed explanation.
 * @param[in] alg_state_data : Pointer to the memory location where factory algorithm state data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note If only algorithm state data and no calibration data is sent to TMF8801, 
 * pre-load algorithm state data starting from address 
 * LIGHTRANGER5_REG_FACTORY_CALIB_0 instead of LIGHTRANGER5_REG_STATE_DATA_WR_0.
 *
 * @endcode
 */
err_t lightranger5_set_algorithm_state_data ( lightranger5_t *ctx, uint8_t *alg_state_data );

/**
 * @brief LightRanger 5 set command data function.
 * @details This function set command data array of the
 * TMF8801, Time-of-Flight Sensor on the LightRanger 5 click board™.
 * @param[in] ctx : Click context object.
 * See #lightranger5_t object definition for detailed explanation.
 * @param[in] cmd_data : Pointer to the memory location where command data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Only available if appid measurement mode ( LIGHTRANGER5_APPID_MEASUREMENT ).
 *
 * @endcode
 */
err_t lightranger5_set_command_data ( lightranger5_t *ctx, uint8_t *cmd_data );

/**
 * @brief LightRanger 5 check previous command function.
 * @details This function check the previous command that was executed
 * or current if continues mode is selected of the
 * TMF8801, Time-of-Flight Sensor on the LightRanger 5 click board™.
 * @param[in] ctx : Click context object.
 * See #lightranger5_t object definition for detailed explanation.
 * @param[out] previous_cmd : 
 *         @li @c  0 - Command that was executed,
 *         @li @c  1 - Current if continues mode is selected. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t lightranger5_check_previous_command ( lightranger5_t *ctx, uint8_t *previous_cmd );

/**
 * @brief LightRanger 5 get currently running application function.
 * @details This function get currently running application mode of the
 * TMF8801, Time-of-Flight Sensor on the LightRanger 5 click board™.
 * @param[in] ctx : Click context object.
 * See #lightranger5_t object definition for detailed explanation.
 * @param[out] appid_data : 
 *         @li @c 0xC0 ( LIGHTRANGER5_APPID_MEASUREMENT ) - Measurement application running,
 *         @li @c 0x80 ( LIGHTRANGER5_APPID_BOOTLOADER )  - Bootloader running. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t lightranger5_get_currently_run_app ( lightranger5_t *ctx, uint8_t *appid_data );

/**
 * @brief LightRanger 5 check data ready function.
 * @details This function check is new data ready of the
 * TMF8801, Time-of-Flight Sensor on the LightRanger 5 click board™.
 * @param[in] ctx : Click context object.
 * See #lightranger5_t object definition for detailed explanation.
 * @return @li @c 0x00 ( LIGHTRANGER5_DATA_NOT_READY ) - Data not ready,
 *         @li @c 0x01 ( LIGHTRANGER5_DATA_IS_READY )  - Data is ready.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
lightranger5_return_data_ready_t lightranger5_check_data_ready ( lightranger5_t *ctx );

/**
 * @brief LightRanger 5 measure distance function.
 * @details This function measure the distance of the
 * TMF8801, Time-of-Flight Sensor on the LightRanger 5 click board™.
 * @param[in] ctx : Click context object.
 * See #lightranger5_t object definition for detailed explanation.
 * @return Distance in mm.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
uint16_t lightranger5_measure_distance ( lightranger5_t *ctx );

/**
 * @brief LightRanger 5 check interrupt state function.
 * @details This function check the interrupt state of the
 * TMF8801, Time-of-Flight Sensor on the LightRanger 5 click board™.
 * @param[in] ctx : Click context object.
 * See #lightranger5_t object definition for detailed explanation.
 * @return @li @c 0 - INT pin state low,
 *         @li @c 1 - INT pin state high.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
uint8_t lightranger5_check_int ( lightranger5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // LIGHTRANGER5_H

/*! @} */ // lightranger5

// ------------------------------------------------------------------------ END
