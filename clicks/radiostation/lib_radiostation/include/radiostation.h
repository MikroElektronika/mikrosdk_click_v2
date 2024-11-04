/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 * \brief This file contains API for RadioStation Click driver.
 *
 * \addtogroup radiostation RadioStation Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RADIOSTATION_H
#define RADIOSTATION_H

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

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define RADIOSTATION_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst     = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.sen     = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RADIOSTATION_RETVAL  uint8_t

#define RADIOSTATION_OK           0x00
#define RADIOSTATION_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_address Slave address
 * \{
 */
#define RADIOSTATION_SLAVE_ADDR0                          0x11              // If SEN = 0
#define RADIOSTATION_SLAVE_ADDR1                          0x63              // If SEN = 1
/** \} */

/**
 * \defgroup return_value_masks Return Value Masks
 * \{
 */
#define RADIOSTATION_CTS                                  0x80
#define RADIOSTATION_ERR                                  0x40
#define RADIOSTATION_RDSINT                               0x04
#define RADIOSTATION_ASQINT                               0x02
#define RADIOSTATION_STCINT                               0x01
/** \} */

/**
 * \defgroup command_arguments_values Command Arguments Values
 * \{
 */

// Power Up Settings
#define RADIOSTATION_CTS_INTERRUPT_ENABLE                 0x04
#define RADIOSTATION_GPO2_OUTPUT_ENABLE                   0x02
#define RADIOSTATION_PATCH_ENABLE                         0x01

// Set Tune Frequency Possible Arguments
#define RADIOSTATION_MIN_TUNE_FREQ                        7600
#define RADIOSTATION_MAX_TUNE_FREQ                        10800
#define RADIOSTATION_MIN_STEP                             5
/** \} */

/**
 * \defgroup property_ids_and_their_values Property IDs and Their Values
 * \{
 */
#define  RADIOSTATION_PROP_GPO_IEN                        0x0001
#define  RADIOSTATION_GPO_IEN_ASQREP                      0x0200
#define  RADIOSTATION_GPO_IEN_STCREP                      0x0100
#define  RADIOSTATION_GPO_IEN_CTSIEN                      0x0080
#define  RADIOSTATION_GPO_IEN_ERRIEN                      0x0040
#define  RADIOSTATION_GPO_IEN_RDSIEN                      0x0004
#define  RADIOSTATION_GPO_IEN_ASQIEN                      0x0002
#define  RADIOSTATION_GPO_IEN_STCIENP                     0x0001

#define RADIOSTATION_PROP_REFCLK_FREQ                     0x0201    // Value Range: 31130 to 34406

#define RADIOSTATION_PROP_REFCLK_PRESCALE                 0x0202    // Value Range: 1 to 4095
#define RADIOSTATION_REFCLK_PRESCALE_RCLK                 0x0000 & 0x1000
#define RADIOSTATION_REFCLK_PRESCALE_DCLK                 0x1000 & 0x1000

#define RADIOSTATION_PROP_TX_COMPONENT_ENABLE             0x2100
#define RADIOSTATION_TX_COMPONENT_ENABLE_RDS              0x0004
#define RADIOSTATION_TX_COMPONENT_ENABLE_LEFT_MINUS_RIGHT 0x0002
#define RADIOSTATION_TX_COMPONENT_ENABLE_PILOT_TONE       0x0001

#define RADIOSTATION_PROP_TX_AUDIO_DEVIATION              0x2101    // Value Range: 0 to 9000

#define RADIOSTATION_PROP_TX_PILOT_DEVIATION              0x2102    // Value Range: 0 to 9000

#define RADIOSTATION_PROP_TX_LINE_INPUT_LEVEL             0x2104
#define RADIOSTATION_TX_LINE_INPUT_LEVEL_LIATTEN_1        0x0000 & 0x3000
#define RADIOSTATION_TX_LINE_INPUT_LEVEL_LIATTEN_2        0x1000 & 0x3000
#define RADIOSTATION_TX_LINE_INPUT_LEVEL_LIATTEN_3        0x2000 & 0x3000
#define RADIOSTATION_TX_LINE_INPUT_LEVEL_LIATTEN_4        0x3000 & 0x3000
#define RADIOSTATION_TX_LINE_INPUT_LEVEL_MAX_LILEVEL      636 & 0x03FF

#define RADIOSTATION_PROP_TX_LINE_INPUT_MUTE              0x2105
#define RADIOSTATION_TX_LINE_INPUT_MUTE_R                 0x0001
#define RADIOSTATION_TX_LINE_INPUT_MUTE_L                 0x0002

#define RADIOSTATION_PROP_TX_PREEMPHASIS                  0x2106
#define RADIOSTATION_TX_PREEMPHASIS_75                    0x0000
#define RADIOSTATION_TX_PREEMPHASIS_50                    0x0001
#define RADIOSTATION_TX_PREEMPHASIS_DISABLED              0x0002

#define RADIOSTATION_PROP_TX_PILOT_FREQUENCY              0x2107    // Value Range: 0 to 19000

#define RADIOSTATION_PROP_TX_ACOMP_ENABLE                 0x2200
#define RADIOSTATION_TX_ACOMP_ENABLE_LIMITEN              0x0002
#define RADIOSTATION_TX_ACOMP_ENABLE_ACEN                 0x0001

#define RADIOSTATION_PROP_TX_ACOMP_THRESHOLD              0x2201    // Value Range: �40 to 0

#define RADIOSTATION_PROP_TX_ACOMP_ATTACK_TIME            0x2202
#define RADIOSTATION_TX_ACOMP_ATTACK_TIME_0_5_MS          0x0000
#define RADIOSTATION_TX_ACOMP_ATTACK_TIME_1_0_MS          0x0001
#define RADIOSTATION_TX_ACOMP_ATTACK_TIME_1_5_MS          0x0002
#define RADIOSTATION_TX_ACOMP_ATTACK_TIME_2_0_MS          0x0003
#define RADIOSTATION_TX_ACOMP_ATTACK_TIME_2_5_MS          0x0004
#define RADIOSTATION_TX_ACOMP_ATTACK_TIME_3_0_MS          0x0005
#define RADIOSTATION_TX_ACOMP_ATTACK_TIME_3_5_MS          0x0006
#define RADIOSTATION_TX_ACOMP_ATTACK_TIME_4_0_MS          0x0007
#define RADIOSTATION_TX_ACOMP_ATTACK_TIME_4_5_MS          0x0008
#define RADIOSTATION_TX_ACOMP_ATTACK_TIME_5_0_MS          0x0009

#define RADIOSTATION_PROP_TX_ACOMP_RELEASE_TIME           0x2203
#define RADIOSTATION_TX_ACOMP_RELEASE_TIME_100_MS         0x0000
#define RADIOSTATION_TX_ACOMP_RELEASE_TIME_200_MS         0x0001
#define RADIOSTATION_TX_ACOMP_RELEASE_TIME_350_MS         0x0002
#define RADIOSTATION_TX_ACOMP_RELEASE_TIME_525_MS         0x0003
#define RADIOSTATION_TX_ACOMP_RELEASE_TIME_1000_MS        0x0004

#define RADIOSTATION_PROP_TX_ACOMP_GAIN                   0x2204    // Value Range: 0 to 20

#define RADIOSTATION_PROP_TX_LIMITER_RELEASE_TIME         0x2205    // Value Range: 5 to 2000

#define RADIOSTATION_PROP_TX_ASQ_INTERRUPT_SELECT         0x2300
#define RADIOSTATION_TX_ASQ_INTERRUPT_OVERMODIEN          0x0004
#define RADIOSTATION_TX_ASQ_INTERRUPT_IALHIEN             0x0002
#define RADIOSTATION_TX_ASQ_INTERRUPT_IALLIEN             0x0001

#define RADIOSTATION_PROP_TX_ASQ_LEVEL_LOW                0x2301    // Value Range: -70 to 0

#define RADIOSTATION_PROP_TX_ASQ_LEVEL_HIGH               0x2303    // Value Range: -70 to 0

#define RADIOSTATION_PROP_TX_ASQ_DURATION_LOW             0x2302

#define RADIOSTATION_PROP_TX_ASQ_DURATION_HIGH            0x2304
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t rst;
    digital_out_t sen;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

    uint16_t transmit_frequency;   // Frequency is represented in following way xxx.yy MHz 
    uint8_t status;

} radiostation_t;

/**
 * @brief Click send command object definition
 */
typedef struct
{
    // Static variable

    uint8_t *params;
    uint8_t params_count;
    uint8_t *ret_vals;
    uint8_t ret_vals_count;

} radiostation_cmd_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t rst;
    pin_name_t sen;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    bool slave_select;

} radiostation_cfg_t;

/** \} */ // End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */
 
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void radiostation_cfg_setup ( radiostation_cfg_t *cfg, bool slave_select );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
RADIOSTATION_RETVAL radiostation_init ( radiostation_t *ctx, radiostation_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 * @param cmd  Command Click object.
 *
 * @description This function executes default configuration for RadioStation Click.
 */
void radiostation_default_cfg ( radiostation_t *ctx, radiostation_cmd_t *cmd );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data.
 */
void radiostation_write ( radiostation_t *ctx, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data.
 */
void radiostation_read ( radiostation_t *ctx, uint8_t *data_buf, uint8_t len );

 /**
 * @brief Radio Station Click Power Up Advanced
 *
 * @param ctx               Click object.
 * @param cmd               Command Click object.
 * @param config            Power Up settings.
 *
 * @description Powers up the chip with custom settings. This function (or radiostation_power_up ) 
 * should be executed before sending any commands to the chip.
 */
uint8_t radiostation_power_up_advanced ( radiostation_t *ctx, radiostation_cmd_t *cmd, uint8_t config );

/**
 * @brief Radio Station Click Power Up
 *
 * @param ctx  Click object.
 * @param cmd  Command Click object.
 *
 * @description Powers up the chip with default settings. This function should be executed 
 * before sending any commands to the chip.
 */
uint8_t radiostation_power_up ( radiostation_t *ctx, radiostation_cmd_t *cmd );

/**
 * @brief Radio Station Click Power Down
 *
 * @param ctx  Click object.
 * @param cmd  Command Click object.
 * 
 * @description Powers down the chip. Any command sent after this will not return correct result.
 */
uint8_t radiostation_power_down ( radiostation_t *ctx, radiostation_cmd_t *cmd );

/**
 * @brief Radio Station Click Get Revision
 *
 * @param ctx                  Click object.
 * @param cmd                  Command Click object. 
 * @param ret_vals             Pointer to a buffer that receives revision information.
 *
 * @description Gets the revision information about the chip.
 * 1 byte for status (same as return value) and 8 bytes for revision info.
 */
uint8_t radiostation_get_revision ( radiostation_t *ctx, radiostation_cmd_t *cmd, uint8_t *ret_vals );

/**
 * @brief Radio Station Click Set Tune Frequency
 *
 * @param ctx              Click object.
 * @param cmd              Command Click object. 
 * @param freq             Desired carrier frequency (between 7600 and 10800).
 *
 * @description Sets carrier frequency to specified value. 
 * @note Value specified represents units of 10 kHz, and has to be multiple of 5 (50 kHz).
 *       Example: Value 10300 sets carrier frequency to 10300 * 10 kHz = 103 MHz.
 */
uint8_t radiostation_get_revision1 ( radiostation_t *ctx, uint8_t *ret_vals );

/**
 * @brief Radio Station Click Set Tune Frequency
 *
 * @param ctx              Click object.
 * @param cmd              Command Click object. 
 * @param freq             Desired carrier frequency (between 7600 and 10800).
 *
 * @description Sets carrier frequency to specified value.
 * @note Value specified represents units of 10 kHz, and has to be multiple of 5 (50 kHz).
 *       Example: Value 10300 sets carrier frequency to 10300 * 10 kHz = 103 MHz.
 */
uint8_t radiostation_set_tune_frequency ( radiostation_t *ctx, radiostation_cmd_t *cmd, uint16_t freq );

/**
 * @brief Radio Station Click Get Revision
 *
 * @param ctx                 Click object.
 * @param cmd                 Command Click object. 
 * @param voltage             Tune power (between 0 and 115/120 dB�V).
 * @param capacitance         Tuning capacitor capacitance (between 0 and 191).
 *
 * @description Sets power of transmitted signal. Also sets tuning capacitor capacitance
 *              (gets multiplied by 0x25 pF), 0 indicates automatic setting of capacitance.
 */
uint8_t radiostation_set_tune_power ( radiostation_t *ctx,  radiostation_cmd_t *cmd, uint8_t voltage, uint8_t capacitance );

/**
 * @brief Radio Station Click Get Tuning Measurements
 *
 * @param ctx                 Click object.
 * @param cmd                 Command Click object. 
 * @param freq                Frequency at which measurement is performed.
 * @param capacitance         Tuning capacitor capacitance (between 0 and 191).
 *
 * @description Measures Received Noise Level (RNL) at specified frequency and capacitance.
 */
uint8_t radiostation_get_tune_measure ( radiostation_t *ctx, radiostation_cmd_t *cmd, uint16_t freq, uint8_t capacitance );

/**
 * @brief Getting int pin status
 *
 * @param ctx  Click object.
 * @param cmd  Command Click object.
 * 
 * @description This function get int status.
 */
uint8_t radiostation_get_int_status ( radiostation_t *ctx, radiostation_cmd_t *cmd ); 

/**
 * @brief Radio Station Click Busy Wait for STCINT
 *
 * @param ctx  Click object.
 * @param cmd  Command Click object.
 * 
 * @description Should be called after a command that sets STCINT bit if interrupts are not used.
 * Busy waits for the bit to become 1.
 */
void radiostation_busy_wait_for_stcint ( radiostation_t *ctx, radiostation_cmd_t *cmd );

/**
 * @brief Radio Station Click Busy Wait for ASQINT
 *
 * @param ctx  Click object.
 * @param cmd  Command Click object.
 * 
 * @description Should be called after a command that sets ASQINT bit if interrupts are not used.
 * Busy waits for the bit to become 1.
 */
void radiostation_busy_wait_for_asqint ( radiostation_t *ctx, radiostation_cmd_t *cmd );

/**
 * @brief Radio Station Click Busy Wait for RDSINT
 *
 * @param ctx  Click object.
 * @param cmd  Command Click object.
 *
 * @description Should be called after a command that sets RDSINT bit if interrupts are not used.
 * Busy waits for the bit to become 1.
 */
void radiostation_busy_wait_for_rdsint ( radiostation_t *ctx, radiostation_cmd_t *cmd );

/**
 * @brief Radio Station Click Get Tune Status
 *
 * @param ctx                    Click object.
 * @param cmd                    Command Click object. 
 * @param clear_stc_status_bit   Clear STC bit.
 * @param ret_vals               Pointer to a buffer that receives tune status.
 *
 * @description Returns status information which is set by radiostation_get_tune_measure,
 * radiostation_set_tune_frequency or radiostation_set_tune_power.
 * 1 byte for return status (same as return value) and 7 bytes for tune status.
 */
uint8_t radiostation_get_tune_status ( radiostation_t *ctx, radiostation_cmd_t *cmd, uint8_t clear_stc_status_bit, uint8_t *ret_vals );

/**
 * @brief Radio Station Click ASQ Status
 *
 * @param ctx                    Click object.
 * @param cmd                    Command Click object.  
 * @param ret_vals               Pointer to a buffer that receives ASQ status.
 *
 * @description Returns status information about the Audio Signal Quality and current FM 
 * transmit frequency. 1 byte for return status (same as return value) and 4 bytes for ASQ status.
 */
uint8_t radiostation_get_asq_status ( radiostation_t *ctx, radiostation_cmd_t *cmd, uint8_t *ret_vals ) ;

/**
 * @brief Radio Station Click Set Property
 *
 * @param ctx                     Click object.
 * @param cmd                     Command Click object.  
 * @param property_id             ID of the property.
 * @param property_value          Value of the property being set.
 *
 * @description Sets specified property to the specified value.
 */
uint8_t radiostation_set_property ( radiostation_t *ctx, radiostation_cmd_t *cmd, uint16_t property_id, uint16_t property_value );

/**
 * @brief Radio Station Click Get Property
 *
 * @param ctx                    Click object.
 * @param cmd                    Command Click object.   
 * @param property_id            ID of the property.
 *
 * @description Gets specified property. Returns the property value (16 bits).
 */
uint16_t radiostation_get_property ( radiostation_t *ctx, radiostation_cmd_t *cmd, uint16_t property_id );


#ifdef __cplusplus
}
#endif
#endif  // _RADIOSTATION_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
