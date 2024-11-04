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
 * \brief This file contains API for ADC 6 Click driver.
 *
 * \addtogroup adc6 ADC 6 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ADC6_H
#define ADC6_H

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
#include "drv_spi_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */


/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define ADC6_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.syn = MIKROBUS( mikrobus, MIKROBUS_RST )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ADC6_OK                             0
#define ADC6_ERROR                         -1
/** \} */

/**
 * \defgroup general_register General Registers
 * \{
 */
#define ADC6_COMMUNICATION_AND_STATUS_REG   0x00
#define ADC6_CONTROL_REG                    0x01
#define ADC6_DATA_REG                       0x02
#define ADC6_IO_CONTROL_1_REG               0x03
#define ADC6_IO_CONTROL_2_REG               0x04
#define ADC6_ID_REG                         0x05
#define ADC6_ERROR_STATUS_REG               0x06
#define ADC6_ERROR_ENABLE_REG               0x07
#define ADC6_MASTER_CLOCK_COUNTER_REG       0x08
#define ADC6_CHANNEL_0_REG                  0x09
#define ADC6_CHANNEL_1_REG                  0x0A
#define ADC6_CHANNEL_2_REG                  0x0B
#define ADC6_CHANNEL_3_REG                  0x0C
#define ADC6_CHANNEL_4_REG                  0x0D
#define ADC6_CHANNEL_5_REG                  0x0E
#define ADC6_CHANNEL_6_REG                  0x0F
#define ADC6_CHANNEL_7_REG                  0x10
#define ADC6_CHANNEL_8_REG                  0x11
#define ADC6_CHANNEL_9_REG                  0x12
#define ADC6_CHANNEL_10_REG                 0x13
#define ADC6_CHANNEL_11_REG                 0x14
#define ADC6_CHANNEL_12_REG                 0x15
#define ADC6_CHANNEL_13_REG                 0x16
#define ADC6_CHANNEL_14_REG                 0x17
#define ADC6_CHANNEL_15_REG                 0x18
#define ADC6_CONFIG_0_REG                   0x19
#define ADC6_CONFIG_1_REG                   0x1A
#define ADC6_CONFIG_2_REG                   0x1B
#define ADC6_CONFIG_3_REG                   0x1C
#define ADC6_CONFIG_4_REG                   0x1D
#define ADC6_CONFIG_5_REG                   0x1E
#define ADC6_CONFIG_6_REG                   0x1F
#define ADC6_CONFIG_7_REG                   0x20
#define ADC6_FILTER_0_REG                   0x21
#define ADC6_FILTER_1_REG                   0x22
#define ADC6_FILTER_2_REG                   0x23
#define ADC6_FILTER_3_REG                   0x24
#define ADC6_FILTER_4_REG                   0x25
#define ADC6_FILTER_5_REG                   0x26
#define ADC6_FILTER_6_REG                   0x27
#define ADC6_FILTER_7_REG                   0x28
#define ADC6_OFFSET_0_REG                   0x29
#define ADC6_OFFSET_1_REG                   0x2A
#define ADC6_OFFSET_2_REG                   0x2B
#define ADC6_OFFSET_3_REG                   0x2C
#define ADC6_OFFSET_4_REG                   0x2D
#define ADC6_OFFSET_5_REG                   0x2E
#define ADC6_OFFSET_6_REG                   0x2F
#define ADC6_OFFSET_7_REG                   0x30
#define ADC6_GAIN_0_REG                     0x31
#define ADC6_GAIN_1_REG                     0x32
#define ADC6_GAIN_2_REG                     0x33
#define ADC6_GAIN_3_REG                     0x34
#define ADC6_GAIN_4_REG                     0x35
#define ADC6_GAIN_5_REG                     0x36
#define ADC6_GAIN_6_REG                     0x37
#define ADC6_GAIN_7_REG                     0x38
/** \} */

/**
 * \defgroup adc_commands Adc Commands
 * \{
 */
#define ADC6_COMMUN_WRITE_COMMAND                                        0x00
#define ADC6_COMMUN_READ_COMMAND                                         0x40
#define ADC6_COMMUN_WRITE_DISABLE                                        0x80
 /** \} */

/**
 * \defgroup control_registers Control Registers
 * \{
 */
#define ADC6_CONTROL_RDY_DELAY_10NS_LOW_POWER_MODE_RDY_PIN_ENABLE      0x0000
#define ADC6_CONTROL_RDY_DELAY_100NS                                   0x1000
#define ADC6_CONTROL_CONTINUOUS_CONVERSION_MODE                        0x0800
#define ADC6_CONTROL_DATA_STATUS_ENABLE                                0x0400
#define ADC6_CONTROL_DOUT_PIN_ENABLE                                   0x0200
#define ADC6_CONTROL_INTERNAL_REFERENCE_VOLTAGE_ENABLE                 0x0100
#define ADC6_CONTROL_MID_POWER_MODE                                    0x0040
#define ADC6_CONTROL_FULL_POWER_MODE                                   0x0080
#define ADC6_CONTROL_SINGLE_CONVERSION_MODE                            0x0004
#define ADC6_CONTROL_STANDBY_MODE                                      0x0008
#define ADC6_CONTROL_SINGLE_POWER_DOWN_MODE                            0x000C
#define ADC6_CONTROL_IDLE_MODE                                         0x0010
#define ADC6_CONTROL_MODE_MASK                                         0x003C
#define ADC6_CONTROL_INTERNAL_ZERO_SCALE_OFFSET_CALIBRATION            0x0014
#define ADC6_CONTROL_INTERNAL_FULL_SCALE_GAIN_CALIBRATION              0x0018
#define ADC6_CONTROL_SYSTEM_ZERO_SCALE_OFFSET_CALIBRATION              0x001C
#define ADC6_CONTROL_SYSTEM_FULL_SCALE_GAIN_CALIBRATION                0x0020
 /** \} */

/**
 * \defgroup configure1_values Configure1 values
 * \{
 */
#define ADC6_IO_CON1_DIGITAL_OUTPUT_PINS_DISABLE_CURRENT_DISABLE   0x00000000
#define ADC6_IO_CON1_SET_DIGITAL_OUTPUT_PIN_P4                     0x00800000
#define ADC6_IO_CON1_SET_DIGITAL_OUTPUT_PIN_P3                     0x00400000
#define ADC6_IO_CON1_SET_DIGITAL_OUTPUT_PIN_P2                     0x00200000
#define ADC6_IO_CON1_SET_DIGITAL_OUTPUT_PIN_P1                     0x00100000
#define ADC6_IO_CON1_ENABLE_DIGITAL_OUTPUT_PIN_P4                  0x00080000
#define ADC6_IO_CON1_ENABLE_DIGITAL_OUTPUT_PIN_P3                  0x00040000
#define ADC6_IO_CON1_ENABLE_DIGITAL_OUTPUT_PIN_P2                  0x00020000
#define ADC6_IO_CON1_ENABLE_DIGITAL_OUTPUT_PIN_P1                  0x00010000
#define ADC6_IO_CON1_ENABLE_BRIGDE_POWER_DOWN                      0x00008000
#define ADC6_IO_CON1_IOUT1_CURRENT_50_MIKRO_A                      0x00000800
#define ADC6_IO_CON1_IOUT1_CURRENT_100_MIKRO_A                     0x00001000
#define ADC6_IO_CON1_IOUT1_CURRENT_250_MIKRO_A                     0x00001800
#define ADC6_IO_CON1_IOUT1_CURRENT_500_MIKRO_A                     0x00002000
#define ADC6_IO_CON1_IOUT1_CURRENT_750_MIKRO_A                     0x00002800
#define ADC6_IO_CON1_IOUT1_CURRENT_1000_MIKRO_A                    0x00003000
#define ADC6_IO_CON1_IOUT0_CURRENT_50_MIKRO_A                      0x00000100
#define ADC6_IO_CON1_IOUT0_CURRENT_100_MIKRO_A                     0x00000200
#define ADC6_IO_CON1_IOUT0_CURRENT_250_MIKRO_A                     0x00000300
#define ADC6_IO_CON1_IOUT0_CURRENT_500_MIKRO_A                     0x00000400
#define ADC6_IO_CON1_IOUT0_CURRENT_750_MIKRO_A                     0x00000500
#define ADC6_IO_CON1_IOUT0_CURRENT_1000_MIKRO_A                    0x00000600
#define ADC6_IO_CON1_IOUT1_ON_AIN0_PIN                             0x00000000
#define ADC6_IO_CON1_IOUT1_ON_AIN1_PIN                             0x00000010
#define ADC6_IO_CON1_IOUT1_ON_AIN2_PIN                             0x00000020
#define ADC6_IO_CON1_IOUT1_ON_AIN3_PIN                             0x00000030
#define ADC6_IO_CON1_IOUT1_ON_AIN4_PIN                             0x00000040
#define ADC6_IO_CON1_IOUT1_ON_AIN5_PIN                             0x00000050
#define ADC6_IO_CON1_IOUT1_ON_AIN6_PIN                             0x00000060
#define ADC6_IO_CON1_IOUT1_ON_AIN7_PIN                             0x00000070
#define ADC6_IO_CON1_IOUT1_ON_AIN8_PIN                             0x00000080
#define ADC6_IO_CON1_IOUT1_ON_AIN9_PIN                             0x00000090
#define ADC6_IO_CON1_IOUT1_ON_AIN10_PIN                            0x000000A0
#define ADC6_IO_CON1_IOUT1_ON_AIN11_PIN                            0x000000B0
#define ADC6_IO_CON1_IOUT1_ON_AIN12_PIN                            0x000000C0
#define ADC6_IO_CON1_IOUT1_ON_AIN13_PIN                            0x000000D0
#define ADC6_IO_CON1_IOUT1_ON_AIN14_PIN                            0x000000E0
#define ADC6_IO_CON1_IOUT1_ON_AIN15_PIN                            0x000000F0
#define ADC6_IO_CON1_IOUT0_ON_AIN0_PIN                             0x00000000
#define ADC6_IO_CON1_IOUT0_ON_AIN1_PIN                             0x00000001
#define ADC6_IO_CON1_IOUT0_ON_AIN2_PIN                             0x00000002
#define ADC6_IO_CON1_IOUT0_ON_AIN3_PIN                             0x00000003
#define ADC6_IO_CON1_IOUT0_ON_AIN4_PIN                             0x00000004
#define ADC6_IO_CON1_IOUT0_ON_AIN5_PIN                             0x00000005
#define ADC6_IO_CON1_IOUT0_ON_AIN6_PIN                             0x00000006
#define ADC6_IO_CON1_IOUT0_ON_AIN7_PIN                             0x00000007
#define ADC6_IO_CON1_IOUT0_ON_AIN8_PIN                             0x00000008
#define ADC6_IO_CON1_IOUT0_ON_AIN9_PIN                             0x00000009
#define ADC6_IO_CON1_IOUT0_ON_AIN10_PIN                            0x0000000A
#define ADC6_IO_CON1_IOUT0_ON_AIN11_PIN                            0x0000000B
#define ADC6_IO_CON1_IOUT0_ON_AIN12_PIN                            0x0000000C
#define ADC6_IO_CON1_IOUT0_ON_AIN13_PIN                            0x0000000D
#define ADC6_IO_CON1_IOUT0_ON_AIN14_PIN                            0x0000000E
#define ADC6_IO_CON1_IOUT0_ON_AIN15_PIN                            0x0000000F
/** \} */

/**
* \defgroup configure2_values Configure2 values
* \{
*/
#define ADC6_IO_CON2_VBIAS_DISABLE                   0x0000
#define ADC6_IO_CON2_VBIAS_ENABLE_ON_AIN0_CHANNEL    0x0001
#define ADC6_IO_CON2_VBIAS_ENABLE_ON_AIN1_CHANNEL    0x0002
#define ADC6_IO_CON2_VBIAS_ENABLE_ON_AIN2_CHANNEL    0x0004
#define ADC6_IO_CON2_VBIAS_ENABLE_ON_AIN3_CHANNEL    0x0008
#define ADC6_IO_CON2_VBIAS_ENABLE_ON_AIN4_CHANNEL    0x0010
#define ADC6_IO_CON2_VBIAS_ENABLE_ON_AIN5_CHANNEL    0x0020
#define ADC6_IO_CON2_VBIAS_ENABLE_ON_AIN6_CHANNEL    0x0040
#define ADC6_IO_CON2_VBIAS_ENABLE_ON_AIN7_CHANNEL    0x0080
#define ADC6_IO_CON2_VBIAS_ENABLE_ON_AIN8_CHANNEL    0x0100
#define ADC6_IO_CON2_VBIAS_ENABLE_ON_AIN9_CHANNEL    0x0200
#define ADC6_IO_CON2_VBIAS_ENABLE_ON_AIN10_CHANNEL   0x0400
#define ADC6_IO_CON2_VBIAS_ENABLE_ON_AIN11_CHANNEL   0x0800
#define ADC6_IO_CON2_VBIAS_ENABLE_ON_AIN12_CHANNEL   0x1000
#define ADC6_IO_CON2_VBIAS_ENABLE_ON_AIN13_CHANNEL   0x2000
#define ADC6_IO_CON2_VBIAS_ENABLE_ON_AIN14_CHANNEL   0x4000
#define ADC6_IO_CON2_VBIAS_ENABLE_ON_AIN15_CHANNEL   0x8000
/** \} */

/**
* \defgroup  monitoring_commands Monitoring commands
* \{
*/
#define ADC6_DISABLE_ALL_ERROR_FLAG                           0x00000000
#define ADC6_ENABLE_MASTER_CLOCK_COUNTER                      0x00400000
#define ADC6_ENABLE_LDO_CAPACITOR_TEST_CHECK                  0x00200000
#define ADC6_ENABLE_ANALOG_LDO_CALIBRATION_CHECK              0x00080000
#define ADC6_ENABLE_DIGITAL_LDO_CALIBRATION_CHECK             0x00100000
#define ADC6_DISABLE_LDO_CHECK                                0x00180000
#define ADC6_ENABLE_CALIBRATION_FAIL_CHECK                    0x00040000
#define ADC6_ENABLE_CONVERSION_FAIL_CHECK                     0x00020000
#define ADC6_ENABLE_SATURATION_CHECK                          0x00010000
#define ADC6_ENABLE_OVERVOLTAGE_MONITOR_ON_AINP_CHANNELS      0x00008000
#define ADC6_ENABLE_UNDERVOLTAGE_MONITOR_ON_AINP_CHANNELS     0x00004000
#define ADC6_ENABLE_OVERVOLTAGE_MONITOR_ON_AINM_CHANNELS      0x00002000
#define ADC6_ENABLE_UNDERVOLTAGE_MONITOR_ON_AINM_CHANNELS     0x00001000
#define ADC6_ENABLE_EXT_REFERENCE_DETECT_ERROR                0x00000800
#define ADC6_ENABLE_DIG_LDO_TEST_MECHANISM_CHECK              0x00000400
#define ADC6_ENABLE_DIG_LDO_VOLTAGE_MONITORING                0x00000200
#define ADC6_ENABLE_AN_LDO_TEST_MECHANISM_CHECK               0x00000100
#define ADC6_ENABLE_AN_LDO_VOLTAGE_MONITORING                 0x00000080
#define ADC6_ENABLE_SPI_IGNORE_ERROR                          0x00000040
#define ADC6_ENABLE_SPI_SCLK_COUNTER_ERROR_CHECK              0x00000020
#define ADC6_ENABLE_SPI_READ_ERROR_CHECK                      0x00000010
#define ADC6_ENABLE_SPI_WRITE_ERROR_CHECK                     0x00000008
#define ADC6_ENABLE_SPI_CRC_CHECK                             0x00000004
#define ADC6_ENABLE_SPI_CRC_CALCULATION_PERFORMING_ON_MEMORY  0x00000002
/** \} */

/**
* \defgroup  adc_channels ADC Channels
* \{
*/
#define ADC6_DISABLE_CHANNEL                       0x0000
#define ADC6_ENABLE_CHANNEL                        0x8000
#define ADC6_CHANNEL_POSITIVE_ANALOG_INPUT_AIN0    0x0000
#define ADC6_CHANNEL_POSITIVE_ANALOG_INPUT_AIN1    0x0020
#define ADC6_CHANNEL_POSITIVE_ANALOG_INPUT_AIN2    0x0040
#define ADC6_CHANNEL_POSITIVE_ANALOG_INPUT_AIN3    0x0060
#define ADC6_CHANNEL_POSITIVE_ANALOG_INPUT_AIN4    0x0080
#define ADC6_CHANNEL_POSITIVE_ANALOG_INPUT_AIN5    0x00A0
#define ADC6_CHANNEL_POSITIVE_ANALOG_INPUT_AIN6    0x00C0
#define ADC6_CHANNEL_POSITIVE_ANALOG_INPUT_AIN7    0x00E0
#define ADC6_CHANNEL_POSITIVE_ANALOG_INPUT_AIN8    0x0100
#define ADC6_CHANNEL_POSITIVE_ANALOG_INPUT_AIN9    0x0120
#define ADC6_CHANNEL_POSITIVE_ANALOG_INPUT_AIN10   0x0140
#define ADC6_CHANNEL_POSITIVE_ANALOG_INPUT_AIN11   0x0160
#define ADC6_CHANNEL_POSITIVE_ANALOG_INPUT_AIN12   0x0180
#define ADC6_CHANNEL_POSITIVE_ANALOG_INPUT_AIN13   0x01A0
#define ADC6_CHANNEL_POSITIVE_ANALOG_INPUT_AIN14   0x01C0
#define ADC6_CHANNEL_POSITIVE_ANALOG_INPUT_AIN15   0x01E0
#define ADC6_POSITIVE_CHANNEL_TEMPERATURE_SENSOR   0x0200
#define ADC6_POSITIVE_CHANNEL_AVSS                 0x0220
#define ADC6_POSITIVE_CHANNEL_INTERNAL_REFERENCE   0x0240
#define ADC6_POSITIVE_CHANNEL_DGND                 0x0260
#define ADC6_CHANNEL_NEGATIVE_ANALOG_INPUT_AIN0    0x0000
#define ADC6_CHANNEL_NEGATIVE_ANALOG_INPUT_AIN1    0x0001
#define ADC6_CHANNEL_NEGATIVE_ANALOG_INPUT_AIN2    0x0002
#define ADC6_CHANNEL_NEGATIVE_ANALOG_INPUT_AIN3    0x0003
#define ADC6_CHANNEL_NEGATIVE_ANALOG_INPUT_AIN4    0x0004
#define ADC6_CHANNEL_NEGATIVE_ANALOG_INPUT_AIN5    0x0005
#define ADC6_CHANNEL_NEGATIVE_ANALOG_INPUT_AIN6    0x0006
#define ADC6_CHANNEL_NEGATIVE_ANALOG_INPUT_AIN7    0x0007
#define ADC6_CHANNEL_NEGATIVE_ANALOG_INPUT_AIN8    0x0008
#define ADC6_CHANNEL_NEGATIVE_ANALOG_INPUT_AIN9    0x0009
#define ADC6_CHANNEL_NEGATIVE_ANALOG_INPUT_AIN10   0x000A
#define ADC6_CHANNEL_NEGATIVE_ANALOG_INPUT_AIN11   0x000B
#define ADC6_CHANNEL_NEGATIVE_ANALOG_INPUT_AIN12   0x000C
#define ADC6_CHANNEL_NEGATIVE_ANALOG_INPUT_AIN13   0x000D
#define ADC6_CHANNEL_NEGATIVE_ANALOG_INPUT_AIN14   0x000E
#define ADC6_CHANNEL_NEGATIVE_ANALOG_INPUT_AIN15   0x000F
#define ADC6_NEGATIVE_CHANNEL_TEMPERATURE_SENSOR   0x0010
#define ADC6_NEGATIVE_CHANNEL_AVSS                 0x0011
#define ADC6_NEGATIVE_CHANNEL_INTERNAL_REFERENCE   0x0012
#define ADC6_NEGATIVE_CHANNEL_DGND                 0x0013
/** \} */

/**
* \defgroup  configuration3_values Configuration3 values
* \{
*/
#define ADC6_CONFIG_UNIPOLAR_OP_BUFFER_DISABLE_BURNOUT_CURRENT_OFF   0x0000
#define ADC6_CONFIG_ENABLE_BIPOLAR_OP                                0x0800
#define ADC6_CONFIG_ENABLE_BURNOUT_CURRENT_ON_500_NANO_A             0x0200
#define ADC6_CONFIG_ENABLE_BURNOUT_CURRENT_ON_2_MIKRO_A              0x0400
#define ADC6_CONFIG_ENABLE_BURNOUT_CURRENT_ON_4_MIKRO_A              0x0600
#define ADC6_CONFIG_ENABLE_BUFFER_ON_REFIN_POSITIVE                  0x0100
#define ADC6_CONFIG_ENABLE_BUFFER_ON_REFIN_NEGATIVE                  0x0080
#define ADC6_CONFIG_ENABLE_BUFFER_ON_AINP                            0x0040
#define ADC6_CONFIG_ENABLE_BUFFER_ON_AINM                            0x0020
#define ADC6_CONFIG_SELECT_REFIN1                                    0x0000
#define ADC6_CONFIG_SELECT_REFIN2                                    0x0008
#define ADC6_CONFIG_SELECT_INTERNAL_REFERENCE                        0x0010
#define ADC6_CONFIG_SELECT_AVDD_FOR_REFERENCE                        0x0018
#define ADC6_CONFIG_SET_GAIN_1                                       0x0000
#define ADC6_CONFIG_SET_GAIN_2                                       0x0001
#define ADC6_CONFIG_SET_GAIN_4                                       0x0002
#define ADC6_CONFIG_SET_GAIN_8                                       0x0003
#define ADC6_CONFIG_SET_GAIN_16                                      0x0004
#define ADC6_CONFIG_SET_GAIN_32                                      0x0005
#define ADC6_CONFIG_SET_GAIN_64                                      0x0006
#define ADC6_CONFIG_SET_GAIN_128                                     0x0007
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
    digital_out_t cs;

    // Output pins 

    digital_out_t  syn;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} adc6_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;

    // Additional gpio pins 

    pin_name_t syn;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t  spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} adc6_cfg_t;

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
void adc6_cfg_setup ( adc6_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
err_t adc6_init ( adc6_t *ctx, adc6_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for ADC6 Click.
 */
void adc6_default_cfg ( adc6_t* ctx );

/**
 * @brief Reset device
 *
 * @param ctx Click object.
 *
 * @description This function resets device and puts device back to normal 
 * operation mode.
 */
void adc6_reset_device ( adc6_t* ctx );

/**
 * @brief Get data function
 *
 * @param ctx           Click object.
 *
 * @returns              Data from Data register.
 *
 * @description This function gets data from Data register in single read mode first starts conversion,
 * then checks ready bit, and when conversion is done (data is ready) reads data from register.
 */
uint32_t adc6_get_adc_data ( adc6_t* ctx );

/**
 * @brief Generic read function
 *
 * @param ctx                Click object.
 * @param register_address    Register address.
 *
 * @returns              Data from determined register.
 *
 * @description This function reads data from determined register.
 */
uint32_t adc6_read_reg ( adc6_t* ctx, uint8_t register_address );

/**
 * @brief Generic write function
 *
 * @param ctx                  Click object.
 * @param register_address      Register address.
 *
 *
 * @description This function writes data to determined register.
 */
void adc6_write_reg ( adc6_t* ctx, uint8_t register_address, uint32_t transfer_data );


#ifdef __cplusplus
}
#endif
#endif  // _ADC6_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
