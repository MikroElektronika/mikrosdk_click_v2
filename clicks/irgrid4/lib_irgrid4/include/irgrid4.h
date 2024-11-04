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
 * @file irgrid4.h
 * @brief This file contains API for IR Grid 4 Click Driver.
 */

#ifndef IRGRID4_H
#define IRGRID4_H

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
 * @addtogroup irgrid4 IR Grid 4 Click Driver
 * @brief API for configuring and manipulating IR Grid 4 Click driver.
 * @{
 */

/**
 * @defgroup irgrid4_reg IR Grid 4 Registers List
 * @brief List of registers of IR Grid 4 Click driver.
 */

/**
 * @addtogroup irgrid4_reg
 * @{
 */

/**
 * @brief IR Grid 4 memory map.
 * @details Specified memory map of IR Grid 4 Click driver.
 */
#define IRGRID4_ADDR_RAM_START              0x0400
#define IRGRID4_ADDR_RAM_END                0x05BF
#define IRGRID4_ADDR_EEPROM_START           0x2400
#define IRGRID4_ADDR_EEPROM_END             0x273F
#define IRGRID4_ADDR_REG_STATUS             0x8000
#define IRGRID4_ADDR_REG_CONTROL            0x800D
#define IRGRID4_ADDR_REG_I2C_CONFIG         0x800F

/*! @} */ // irgrid4_reg

/**
 * @defgroup irgrid4_set IR Grid 4 Registers Settings
 * @brief Settings for registers of IR Grid 4 Click driver.
 */

/**
 * @addtogroup irgrid4_set
 * @{
 */

/**
 * @brief IR Grid 4 status register setting.
 * @details Specified setting for status register of IR Grid 4 Click driver.
 */
#define IRGRID4_STATUS_SUBPAGE              0x0001
#define IRGRID4_STATUS_DATA_READY           0x0008
#define IRGRID4_STATUS_OVERWRITE_EN         0x0010

/**
 * @brief IR Grid 4 control register setting.
 * @details Specified setting for control register of IR Grid 4 Click driver.
 */
#define IRGRID4_CONTROL_SUBPAGE_EN          0x0001
#define IRGRID4_CONTROL_DATA_HOLD_EN        0x0004
#define IRGRID4_CONTROL_SUBPAGE_REP_EN      0x0008
#define IRGRID4_CONTROL_SUBPAGE_1_SEL       0x0010
#define IRGRID4_CONTROL_REFRESH_RATE_0_5_HZ 0x0000
#define IRGRID4_CONTROL_REFRESH_RATE_1_HZ   0x0080
#define IRGRID4_CONTROL_REFRESH_RATE_2_HZ   0x0100
#define IRGRID4_CONTROL_REFRESH_RATE_4_HZ   0x0180
#define IRGRID4_CONTROL_REFRESH_RATE_8_HZ   0x0200
#define IRGRID4_CONTROL_REFRESH_RATE_16_HZ  0x0280
#define IRGRID4_CONTROL_REFRESH_RATE_32_HZ  0x0300
#define IRGRID4_CONTROL_REFRESH_RATE_64_HZ  0x0380
#define IRGRID4_CONTROL_REFRESH_RATE_MASK   0x0380
#define IRGRID4_CONTROL_RESOLUTION_16_BIT   0x0000
#define IRGRID4_CONTROL_RESOLUTION_17_BIT   0x0400
#define IRGRID4_CONTROL_RESOLUTION_18_BIT   0x0800
#define IRGRID4_CONTROL_RESOLUTION_19_BIT   0x0C00
#define IRGRID4_CONTROL_RESOLUTION_MASK     0x0C00
#define IRGRID4_CONTROL_PATTERN_CHESS       0x1000

/**
 * @brief IR Grid 4 ADC resolution setting.
 * @details Specified setting for ADC resolution of IR Grid 4 Click driver.
 */
#define IRGRID4_RESOLUTION_16_BIT           0
#define IRGRID4_RESOLUTION_17_BIT           1
#define IRGRID4_RESOLUTION_18_BIT           2
#define IRGRID4_RESOLUTION_19_BIT           3

/**
 * @brief IR Grid 4 IR refresh rate setting.
 * @details Specified setting for IR refresh rate of IR Grid 4 Click driver.
 */
#define IRGRID4_REFRESH_RATE_0_5_HZ         0
#define IRGRID4_REFRESH_RATE_1_HZ           1
#define IRGRID4_REFRESH_RATE_2_HZ           2
#define IRGRID4_REFRESH_RATE_4_HZ           3
#define IRGRID4_REFRESH_RATE_8_HZ           4
#define IRGRID4_REFRESH_RATE_16_HZ          5
#define IRGRID4_REFRESH_RATE_32_HZ          6
#define IRGRID4_REFRESH_RATE_64_HZ          7

/**
 * @brief IR Grid 4 object temperature calculation setting.
 * @details Specified setting for object temperature calculation of IR Grid 4 Click driver.
 */
#define IRGRID4_SCALE_ALPHA                 0.000001
#define IRGRID4_EMISSIVITY                  0.95
#define IRGRID4_TA_SHIFT                    5
#define IRGRID4_ABS_ZERO_K                  273.15

/**
 * @brief IR Grid 4 device address setting.
 * @details Specified setting for device slave address selection of
 * IR Grid 4 Click driver.
 */
#define IRGRID4_DEVICE_ADDRESS              0x33

/*! @} */ // irgrid4_set

/**
 * @defgroup irgrid4_map IR Grid 4 MikroBUS Map
 * @brief MikroBUS pin mapping of IR Grid 4 Click driver.
 */

/**
 * @addtogroup irgrid4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of IR Grid 4 Click to the selected MikroBUS.
 */
#define IRGRID4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.led2 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.led1 = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // irgrid4_map
/*! @} */ // irgrid4

/**
 * @brief IR Grid 4 Click parameters object.
 * @details EEPROM calibration parameters object definition of IR Grid 4 Click driver.
 */
typedef struct
{
    int16_t k_vdd;
    int16_t vdd_25;
    float kv_ptat;
    float kt_ptat;
    uint16_t v_ptat_25;
    float alpha_ptat;
    int16_t gain_ee;
    float tgc;
    float cp_kv;
    float cp_kta;
    uint8_t resolution_ee;
    uint8_t calibration_mode_ee;
    float ks_ta;
    float ks_to[ 8 ];
    int16_t ct[ 8 ];
    uint16_t alpha[ 192 ]; 
    uint8_t alpha_scale;   
    int16_t offset[ 2 ][ 192 ];    
    int8_t kta[ 192 ];
    uint8_t kta_scale;    
    int8_t kv[ 192 ];
    uint8_t kv_scale;
    float cp_alpha;
    int16_t cp_offset;
    float emissivity_ee; 
    uint16_t broken_pixel;

} irgrid4_params_t;

/**
 * @brief IR Grid 4 Click context object.
 * @details Context object definition of IR Grid 4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t led2;         /**< LED2 control pin. */
    digital_out_t led1;         /**< LED1 control pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    uint16_t eeprom[ 832 ];     /**< EEPROM RAW data. */

    irgrid4_params_t calib;     /**< Calibration parameters restored from EEPROM. */

} irgrid4_t;

/**
 * @brief IR Grid 4 Click configuration object.
 * @details Configuration object definition of IR Grid 4 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t led2;            /**< LED2 control pin. */
    pin_name_t led1;            /**< LED1 control pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} irgrid4_cfg_t;

/**
 * @brief IR Grid 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    IRGRID4_OK = 0,
    IRGRID4_ERROR = -1

} irgrid4_return_value_t;

/*!
 * @addtogroup irgrid4 IR Grid 4 Click Driver
 * @brief API for configuring and manipulating IR Grid 4 Click driver.
 * @{
 */

/**
 * @brief IR Grid 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #irgrid4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void irgrid4_cfg_setup ( irgrid4_cfg_t *cfg );

/**
 * @brief IR Grid 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #irgrid4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgrid4_init ( irgrid4_t *ctx, irgrid4_cfg_t *cfg );

/**
 * @brief IR Grid 4 default configuration function.
 * @details This function executes a default configuration of IR Grid 4
 * Click board.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t irgrid4_default_cfg ( irgrid4_t *ctx );

/**
 * @brief IR Grid 4 write data function.
 * @details This function writes a desired data word to the selected memory address
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @param[in] addr : 16-bit memory address.
 * @param[in] data_in : 16-bit data word to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgrid4_write_data ( irgrid4_t *ctx, uint16_t addr, uint16_t data_in );

/**
 * @brief IR Grid 4 read data function.
 * @details This function reads a desired number of data words starting from
 * the selected memory address by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @param[in] addr : 16-bit start memory address.
 * @param[out] data_out : Output read data words.
 * @param[in] len : Number of words to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgrid4_read_data ( irgrid4_t *ctx, uint16_t addr, uint16_t *data_out, uint8_t len );

/**
 * @brief IR Grid 4 general reset function.
 * @details This function performs the device general reset.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgrid4_general_reset ( irgrid4_t *ctx );

/**
 * @brief IR Grid 4 enable LED1 function.
 * @details This function enables the LED1.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void irgrid4_enable_led1 ( irgrid4_t *ctx );

/**
 * @brief IR Grid 4 disable LED1 function.
 * @details This function disables the LED1.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void irgrid4_disable_led1 ( irgrid4_t *ctx );

/**
 * @brief IR Grid 4 enable LED2 function.
 * @details This function enables the LED2.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void irgrid4_enable_led2 ( irgrid4_t *ctx );

/**
 * @brief IR Grid 4 disable LED2 function.
 * @details This function disables the LED2.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void irgrid4_disable_led2 ( irgrid4_t *ctx );

/**
 * @brief IR Grid 4 dump EEPROM function.
 * @details This function reads the entire EEPROM memory and stores it in ctx->eeprom.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgrid4_dump_eeprom ( irgrid4_t *ctx );

/**
 * @brief IR Grid 4 sync frame function.
 * @details This function synchronize data frame.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgrid4_sync_frame ( irgrid4_t *ctx );

/**
 * @brief IR Grid 4 trigger measurement function.
 * @details This function triggers data measurement.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgrid4_trigger_measurement ( irgrid4_t *ctx );

/**
 * @brief IR Grid 4 get frame data function.
 * @details This function reads and validates RAM data frame.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @param[out] frame_data : RAM data frame read [242 words in total].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgrid4_get_frame_data ( irgrid4_t *ctx, uint16_t *frame_data );

/**
 * @brief IR Grid 4 get parameters function.
 * @details This function validates EEPROM data and extracts calibration parameters from it.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgrid4_get_parameters ( irgrid4_t *ctx );

/**
 * @brief IR Grid 4 get VDD function.
 * @details This function calculates the VDD system voltage from data frame buffer.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @param[in] frame_data : RAM data frame buffer.
 * @return VDD system voltage.
 * @note None.
 */
float irgrid4_get_vdd ( irgrid4_t *ctx, uint16_t *frame_data );

/**
 * @brief IR Grid 4 get TA function.
 * @details This function calculates the ambient temperature from data frame buffer.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @param[in] frame_data : RAM data frame buffer.
 * @return Ambient temperature in degrees Celsius.
 * @note None.
 */
float irgrid4_get_ta ( irgrid4_t *ctx, uint16_t *frame_data );

/**
 * @brief IR Grid 4 get TO function.
 * @details This function calculates the 16x12 IR grid object temperature from data frame buffer.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @param[in] frame_data : RAM data frame buffer.
 * @param[in] tr_val : Room temperature in degrees Celsius.
 * @param[out] result : Result 16x12 IR Grid object temperature in degrees Celsius.
 * @return None.
 * @note None.
 */
void irgrid4_get_to ( irgrid4_t *ctx, uint16_t *frame_data, float tr_val, float *result );

/**
 * @brief IR Grid 4 set resolution function.
 * @details This function sets the ADC measurement data resolution.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @param[in] resolution : Resolution: @li @c 0 - 16 bit,
 *                                     @li @c 1 - 17 bit,
 *                                     @li @c 2 - 18 bit,
 *                                     @li @c 3 - 19 bit.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgrid4_set_resolution ( irgrid4_t *ctx, uint8_t resolution );

/**
 * @brief IR Grid 4 get resolution function.
 * @details This function gets the ADC measurement data resolution.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @param[out] resolution : Resolution: @li @c 0 - 16 bit,
 *                                      @li @c 1 - 17 bit,
 *                                      @li @c 2 - 18 bit,
 *                                      @li @c 3 - 19 bit.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgrid4_get_resolution ( irgrid4_t *ctx, uint8_t *resolution );

/**
 * @brief IR Grid 4 set refresh rate function.
 * @details This function sets the IR data refresh rate.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @param[in] refresh_rate : Refresh rate: @li @c 0 - 0.5 Hz,
 *                                         @li @c 1 - 1 Hz,
 *                                         @li @c 2 - 2 Hz,
 *                                         @li @c 3 - 4 Hz,
 *                                         @li @c 4 - 8 Hz,
 *                                         @li @c 5 - 16 Hz,
 *                                         @li @c 6 - 32 Hz,
 *                                         @li @c 7 - 64 Hz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgrid4_set_refresh_rate ( irgrid4_t *ctx, uint8_t refresh_rate );

/**
 * @brief IR Grid 4 get refresh rate function.
 * @details This function gets the IR data refresh rate.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @param[out] refresh_rate : Refresh rate: @li @c 0 - 0.5 Hz,
 *                                          @li @c 1 - 1 Hz,
 *                                          @li @c 2 - 2 Hz,
 *                                          @li @c 3 - 4 Hz,
 *                                          @li @c 4 - 8 Hz,
 *                                          @li @c 5 - 16 Hz,
 *                                          @li @c 6 - 32 Hz,
 *                                          @li @c 7 - 64 Hz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgrid4_get_refresh_rate ( irgrid4_t *ctx, uint8_t *refresh_rate );

/**
 * @brief IR Grid 4 get measurement function.
 * @details This function reads the RAM frame data and calculates ambient temperature
 * and a 16x12 IR grid object temperature.
 * @param[in] ctx : Click context object.
 * See #irgrid4_t object definition for detailed explanation.
 * @param[out] t_amb : Ambient temperature in degrees Celsius.
 * @param[out] t_obj : 16x12 IR Grid object temperature in degrees Celsius [array of 192 float].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgrid4_get_measurement ( irgrid4_t *ctx, float *t_amb, float *t_obj );

#ifdef __cplusplus
}
#endif
#endif // IRGRID4_H

/*! @} */ // irgrid4

// ------------------------------------------------------------------------ END
