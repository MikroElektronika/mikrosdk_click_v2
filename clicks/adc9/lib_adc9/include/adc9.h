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
 * \brief This file contains API for ADC 9 Click driver.
 *
 * \addtogroup adc9 ADC 9 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ADC9_H
#define ADC9_H

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

#define ADC9_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso    = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi    = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck     = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs      = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.mck     = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ADC9_RETVAL  uint8_t

#define ADC9_OK           0x00
#define ADC9_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup device_address Device address
 * \{
 */
#define ADC9_DEVICE_ADR                   0x01
/** \} */

/**
 * \defgroup command_bits Command bits
 * \{
 */
#define ADC9_CMD_DONT_CARE                0x00
#define ADC9_CMD_STAT_READ                0x01
#define ADC9_CMD_INC_WRITE                0x02
#define ADC9_CMD_INC_READ                 0x03
/** \} */

/**
 * \defgroup internal_registers Internal Registers
 * \{
 */
#define ADC9_REG_ADC_DATA                 0x00
#define ADC9_REG_CFG_0                    0x01
#define ADC9_REG_CFG_1                    0x02
#define ADC9_REG_CFG_2                    0x03
#define ADC9_REG_CFG_3                    0x04
#define ADC9_REG_IRQ                      0x05
#define ADC9_REG_MUX                      0x06
#define ADC9_REG_SCAN                     0x07
#define ADC9_REG_TIMER                    0x08
#define ADC9_REG_OFFSET_CAL               0x09
#define ADC9_REG_GAIN_CAL                 0x0A
#define ADC9_RSV_REG_W_A                  0x0B
#define ADC9_REG_LOCK                     0x0D
#define ADC9_RSV_REG                      0x0E
#define ADC9_REG_CRC_CFG                  0x0F
/** \} */

/**
 * \defgroup config0_register CONFIG0 Register
 * \{
 */
#define ADC9_CFG_0_VREF_SEL_0             0x00
#define ADC9_CFG_0_VREF_SEL_1             0x40
#define ADC9_CFG_0_VREF_SEL_2             0x80
#define ADC9_CFG_0_VREF_SEL_3             0xC0

#define ADC9_CFG_0_CLK_SEL_0              0x00
#define ADC9_CFG_0_CLK_SEL_1              0x10
#define ADC9_CFG_0_CLK_SEL_2              0x20
#define ADC9_CFG_0_CLK_SEL_3              0x30

#define ADC9_CFG_0_CS_SEL_0               0x00
#define ADC9_CFG_0_CS_SEL_1               0x04
#define ADC9_CFG_0_CS_SEL_2               0x08
#define ADC9_CFG_0_CS_SEL_3               0x0C

#define ADC9_CFG_0_MODE_SHD_DEF           0x00
#define ADC9_CFG_0_MODE_SHD               0x01
#define ADC9_CFG_0_MODE_STANDBY           0x02
#define ADC9_CFG_0_MODE_CONV              0x03
/** \} */

/**
 * \defgroup config1_register CONFIG1 Register
 * \{
 */
#define ADC9_CFG_1_PRE_1                  0x00
#define ADC9_CFG_1_PRE_2                  0x40
#define ADC9_CFG_1_PRE_4                  0x80
#define ADC9_CFG_1_PRE_8                  0xC0
/** \} */

/**
 * \defgroup oversampling_ratio Oversampling Ratio for Delta-Sigma A/D Conversion
 * \{
 */
#define ADC9_CFG_1_OSR_98304              0x3C
#define ADC9_CFG_1_OSR_81920              0x38
#define ADC9_CFG_1_OSR_49152              0x34
#define ADC9_CFG_1_OSR_40960              0x30
#define ADC9_CFG_1_OSR_24576              0x2C
#define ADC9_CFG_1_OSR_20480              0x28
#define ADC9_CFG_1_OSR_16384              0x24
#define ADC9_CFG_1_OSR_8192               0x20
#define ADC9_CFG_1_OSR_4096               0x1C
#define ADC9_CFG_1_OSR_2048               0x18
#define ADC9_CFG_1_OSR_1024               0x14
#define ADC9_CFG_1_OSR_512                0x10
#define ADC9_CFG_1_OSR_256                0x0C
#define ADC9_CFG_1_OSR_128                0x08
#define ADC9_CFG_1_OSR_64                 0x04
#define ADC9_CFG_1_OSR_32                 0x00

#define ADC9_CFG_1_DITHER_MAX             0x03
#define ADC9_CFG_1_DITHER_MED             0x02
#define ADC9_CFG_1_DITHER_MIN             0x01
#define ADC9_CFG_1_DITHER_DEF             0x00
/** \} */

/**
 * \defgroup config2_register CONFIG2 Register
 * \{
 */
#define ADC9_CFG_2_BOOST_X_2              0xC0
#define ADC9_CFG_2_BOOST_X_1              0x80
#define ADC9_CFG_2_BOOST_X_066            0x40
#define ADC9_CFG_2_BOOST_X_05             0x00

#define ADC9_CFG_2_GAIN_X_64              0x38
#define ADC9_CFG_2_GAIN_X_32              0x30
#define ADC9_CFG_2_GAIN_X_16              0x28
#define ADC9_CFG_2_GAIN_X_8               0x20
#define ADC9_CFG_2_GAIN_X_4               0x18
#define ADC9_CFG_2_GAIN_X_2               0x10
#define ADC9_CFG_2_GAIN_X_1               0x08
#define ADC9_CFG_2_GAIN_X_033             0x00

#define ADC9_CFG_2_AZ_MUX_EN              0x04
#define ADC9_CFG_2_AZ_MUX_DIS             0x00
#define ADC9_CFG_2_AZ_VREF_EN             0x02
#define ADC9_CFG_2_AZ_VREF_DIS            0x00

#define ADC9_CFG_2_AZ_FREQ_HIGH           0x01
#define ADC9_CFG_2_AZ_FREQ_LOW            0x00
/** \} */

/**
 * \defgroup config3_register CONFIG3 Register
 * \{
 */
#define ADC9_CFG_3_CONV_MODE_CONT         0xC0
#define ADC9_CFG_3_CONV_MODE_STANDBY      0x80
#define ADC9_CFG_3_CONV_MODE_SHD          0x40
#define ADC9_CFG_3_CONV_MODE_SHD0         0x00

#define ADC9_CFG_3_DATA_FORMAT_CH_ADC     0x30
#define ADC9_CFG_3_DATA_FORMAT_SIGN_ADC   0x20
#define ADC9_CFG_3_DATA_FORMAT_LEFT_JUST  0x10
#define ADC9_CFG_3_DATA_FORMAT_DEF        0x00

#define ADC9_CFG_3_CRC_FORMAT_32          0x08
#define ADC9_CFG_3_CRC_FORMAT_16          0x00

#define ADC9_CFG_3_CRC_COM_EN             0x04
#define ADC9_CFG_3_CRC_COM_DIS            0x00

#define ADC9_CFG_3_CRC_OFF_CAL_EN         0x02
#define ADC9_CFG_3_CRC_OFF_CAL_DIS        0x00
#define ADC9_CFG_3_CRC_GAIN_CAL_EN        0x01
#define ADC9_CFG_3_CRC_GAIN_CAL_DIS       0x00
/** \} */ 

/**
 * \defgroup irq_egister IRQ Register
 * \{
 */
#define ADC9_IRQ_MODE_MDAT                0x08
#define ADC9_IRQ_MODE_IRQ                 0x00
#define ADC9_IRQ_MODE_LOGIC_HIGH          0x04
#define ADC9_IRQ_MODE_HIGH_Z              0x00
#define ADC9_IRQ_FASTCMD_EN               0x02
#define ADC9_IRQ_FASTCMD_DIS              0x00
#define ADC9_IRQ_STP_EN                   0x01
#define ADC9_IRQ_STP_DIS                  0x00
/** \} */ 

/**
 * \defgroup mux_vin_plus_input_selection MUX_VIN+ Input Selection
 * \{
 */
#define ADC9_MUX_VIN_POS_NO_IN            0xF0
#define ADC9_MUX_VIN_POS_VCM              0xE0
#define ADC9_MUX_VIN_POS_TEMP             0xD0
#define ADC9_MUX_VIN_POS_VREF_EXT_MINUS   0xC0
#define ADC9_MUX_VIN_POS_VREF_EXT_PLUS    0xB0
#define ADC9_MUX_VIN_POS_VREF_INT         0xA0
#define ADC9_MUX_VIN_POS_AVDD             0x90
#define ADC9_MUX_VIN_POS_VSS              0x80
#define ADC9_MUX_VIN_POS_CH7              0x70
#define ADC9_MUX_VIN_POS_CH6              0x60
#define ADC9_MUX_VIN_POS_CH5              0x50
#define ADC9_MUX_VIN_POS_CH4              0x40
#define ADC9_MUX_VIN_POS_CH3              0x30
#define ADC9_MUX_VIN_POS_CH2              0x20
#define ADC9_MUX_VIN_POS_CH1              0x10
#define ADC9_MUX_VIN_POS_CH0              0x00
/** \} */ 

/**
 * \defgroup mux_vin_minus_input_selection MUX_VIN- Input Selection
 * \{
 */
#define ADC9_MUX_VIN_NEG_NO_IN            0x0F
#define ADC9_MUX_VIN_NEG_VCM              0x0E
#define ADC9_MUX_VIN_NEG_TEMP             0x0D
#define ADC9_MUX_VIN_NEG_VREF_EXT_MINUS   0x0C
#define ADC9_MUX_VIN_NEG_VREF_EXT_PLUS    0x0B
#define ADC9_MUX_VIN_NEG_VREF_INT         0x0A
#define ADC9_MUX_VIN_NEG_AVDD             0x09
#define ADC9_MUX_VIN_NEG_VSS              0x08
#define ADC9_MUX_VIN_NEG_CH7              0x07
#define ADC9_MUX_VIN_NEG_CH6              0x06
#define ADC9_MUX_VIN_NEG_CH5              0x05
#define ADC9_MUX_VIN_NEG_CH4              0x04
#define ADC9_MUX_VIN_NEG_CH3              0x03
#define ADC9_MUX_VIN_NEG_CH2              0x02
#define ADC9_MUX_VIN_NEG_CH1              0x01
#define ADC9_MUX_VIN_NEG_CH0              0x00
/** \} */ 

/**
 * \defgroup scan_register SCAN Register
 * \{
 */
#define ADC9_SCAN_DLY_DM_CLK_X_512        0x00E00000
#define ADC9_SCAN_DLY_DM_CLK_X_256        0x00C00000
#define ADC9_SCAN_DLY_DM_CLK_X_128        0x00A00000
#define ADC9_SCAN_DLY_DM_CLK_X_64         0x00800000
#define ADC9_SCAN_DLY_DM_CLK_X_32         0x00600000
#define ADC9_SCAN_DLY_DM_CLK_X_16         0x00400000
#define ADC9_SCAN_DLY_DM_CLK_X_8          0x00200000
#define ADC9_SCAN_DLY_NO_DELAY            0x00000000

#define ADC9_SCAN_PSAV_VREF_OFF           0x00100000
#define ADC9_SCAN_PSAV_VREF_ON            0x00000000

#define ADC9_SCAN_OFFSET                  0x00008000
#define ADC9_SCAN_VREF                    0x00004000
#define ADC9_SCAN_AVDD                    0x00002000
#define ADC9_SCAN_TEMP                    0x00001000
#define ADC9_SCAN_DIFF_D                  0x00000800
#define ADC9_SCAN_DIFF_C                  0x00000400
#define ADC9_SCAN_DIFF_B                  0x00000200
#define ADC9_SCAN_DIFF_A                  0x00000100
#define ADC9_SCAN_CH7                     0x00000080
#define ADC9_SCAN_CH6                     0x00000040
#define ADC9_SCAN_CH5                     0x00000020
#define ADC9_SCAN_CH4                     0x00000010
#define ADC9_SCAN_CH3                     0x00000008
#define ADC9_SCAN_CH2                     0x00000004
#define ADC9_SCAN_CH1                     0x00000002
#define ADC9_SCAN_CH0                     0x00000001
/** \} */ 

/**
 * \defgroup timer_register Timer Register
 * \{
 */
#define ADC9_TIMER_DLY_DMCLK_X_16777215   0x00FFFFFF
#define ADC9_TIMER_DLY_DMCLK_X_8388607    0x007FFFFF
#define ADC9_TIMER_DLY_DMCLK_X_4194303    0x003FFFFF
#define ADC9_TIMER_DLY_DMCLK_X_2097151    0x001FFFFF
#define ADC9_TIMER_DLY_DMCLK_X_1048575    0x000FFFFF
#define ADC9_TIMER_DLY_DMCLK_X_524287     0x0007FFFF
#define ADC9_TIMER_DLY_DMCLK_X_262143     0x0003FFFF
#define ADC9_TIMER_DLY_DMCLK_X_131071     0x0001FFFF
#define ADC9_TIMER_DLY_DMCLK_X_65535      0x0000FFFF
#define ADC9_TIMER_DLY_DMCLK_X_32767      0x00007FFF
#define ADC9_TIMER_DLY_DMCLK_X_16383      0x00003FFF
#define ADC9_TIMER_DLY_DMCLK_X_8191       0x00001FFF
#define ADC9_TIMER_DLY_DMCLK_X_4095       0x00000FFF
#define ADC9_TIMER_DLY_DMCLK_X_2047       0x000007FF
#define ADC9_TIMER_DLY_DMCLK_X_1023       0x000003FF
#define ADC9_TIMER_DLY_DMCLK_X_511        0x000001FF
#define ADC9_TIMER_DLY_DMCLK_X_255        0x000000FF
#define ADC9_TIMER_DLY_DMCLK_X_127        0x0000007F
#define ADC9_TIMER_DLY_DMCLK_X_63         0x0000003F
#define ADC9_TIMER_DLY_DMCLK_X_31         0x0000001F
#define ADC9_TIMER_DLY_DMCLK_X_15         0x0000000F
#define ADC9_TIMER_DLY_DMCLK_X_2          0x00000002
#define ADC9_TIMER_DLY_DMCLK_X_1          0x00000001
#define ADC9_TIMER_DLY_NO_DELAY           0x00000000
/** \} */ 

/**
 * \defgroup fast_commands Fast commands
 * \{
 */
#define ADC9_FAST_CMD_ADC_CONV_START      0x28
#define ADC9_FAST_CMD_ADC_STANDBY_MODE    0x2C
#define ADC9_FAST_CMD_ADC_SHUTDOWN_MODE   0x30
#define ADC9_FAST_CMD_FULL_SHUTDOWN_MODE  0x34
#define ADC9_FAST_CMD_DEV_FULL_RESET      0x38
/** \} */ 

/**
 * \defgroup calculation_coefitient Calculation coefitient
 * \{
 */
#define ADC9_CALC_COEF                    8388608
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

    digital_out_t mck;
    digital_out_t cs;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} adc9_t;

/**
 * @brief Click wr object definition.
 */
typedef struct
{
    // static variable 
    uint8_t dev_adr; 
    uint8_t reg;
    uint8_t cmd; 

} adc9_rw_t;

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

    pin_name_t mck;
    pin_name_t int_pin;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} adc9_cfg_t;

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
void adc9_cfg_setup ( adc9_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
ADC9_RETVAL adc9_init ( adc9_t *ctx, adc9_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 * @param rw   Read/write object.
 *
 * @description This function executes default configuration for ADC 9 Click.
 */
void adc9_default_cfg ( adc9_t *ctx, adc9_rw_t *rw );

/**
 * @brief Generic transfer function.
 *
 * @param ctx          Click object.
 * @param wr_buf       Write data buffer
 * @param wr_len       Number of byte in write data buffer
 * @param rd_buf       Read data buffer
 * @param rd_len       Number of byte in read data buffer
 *
 * @description Generic SPI transfer, for sending and receiving packages
 */
void adc9_generic_transfer 
( 
    adc9_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Write fast commands function
 *
 * @param ctx  Click object.
 * @param rw   Read/write object. 
 * <pre>
 * Struct Arguments:
 *      dev_adr     8-bit value that defines the dvice
 *      cmd         8-bit value that defines the command
 * </pre> 
 *
 * @returns stat_byte 8-bit value that represents the device's status.
 *
 * @description Function is used to execute fast command.
**/
uint8_t adc9_write_fast_cmd ( adc9_t *ctx, adc9_rw_t *rw );

/**
 * @brief Write byte function
 *
 * @param ctx  Click object.
 * @param rw   Read/write object. 
 * <pre>
 * Struct Arguments: 
 *      dev_adr     8-bit value that defines the dvice
 *      reg         8-bit value that defines the register
 * </pre> 
 * @param wr_data  8-bit value that defines the input data
 *
 * @returns stat_byte 8-bit value that represents the device's status.
 *
 * @description Function is used to write single byte of data into user defined register.
**/
uint8_t adc9_write_u8 (  adc9_t *ctx, adc9_rw_t *rw, uint8_t wr_data );

/**
 * @brief Read byte function
 *
 * @param ctx  Click object.
 * @param rw   Read/write object. 
 * <pre>
 * Struct Arguments: 
 *      dev_adr     8-bit value that defines the dvice
 *      reg         8-bit value that defines the register
 *      cmd         8-bit value that defines the command( static or incremental read )
 * </pre> 
 * @param rd_data  8-bit value that defines the output data
 *
 * @returns stat_byte 8-bit value that represents the device's status.
 *
 * @description Function is used to read single byte of data from user defined register.
**/
uint8_t adc9_read_u8 (  adc9_t *ctx, adc9_rw_t *rw, uint8_t *rd_data );

/**
 * @brief Write word function
 *
 * @param ctx  Click object.
 * @param rw   Read/write object. 
 * <pre>
 * Struct Arguments: 
 *      dev_adr     8-bit value that defines the dvice
 *      reg         8-bit value that defines the register
 * </pre>  
 * @param wr_data  16-bit value that defines the input data
 *
 * @returns stat_byte 8-bit value that represents the device's status.
 *
 * @description Function is used to write two bytes of data into user defined register.
**/
uint8_t adc9_write_u16 ( adc9_t *ctx, adc9_rw_t *rw, uint16_t wr_data );

/**
 * @brief Read word function
 *
 * @param ctx  Click object.
 * @param rw   Read/write object. 
 * <pre>
 * Struct Arguments: 
 *      dev_adr     8-bit value that defines the dvice
 *      reg         8-bit value that defines the register
 *      cmd         8-bit value that defines the command( static or incremental read )
 * </pre>  
 * @param rd_data  16-bit value that defines the output data
 *
 * @returns stat_byte 8-bit value that represents the device's status.
 *
 * @description Function is used to read two bytes of data from user defined register.
**/
uint8_t adc9_read_u16 ( adc9_t *ctx, adc9_rw_t *rw, uint16_t *rd_data );

/**
 * @brief Write 24-bit function
 *
 * @param ctx  Click object.
 * @param rw   Read/write object. 
 * <pre>
 * Struct Arguments: 
 *      dev_adr     8-bit value that defines the dvice
 *      reg         8-bit value that defines the register
 * </pre>  
 * @param wr_data  24-bit value that defines the input data
 *
 * @returns stat_byte 8-bit value that represents the device's status.
 *
 * @description Function is used to write three bytes of data into user defined register.
**/
uint8_t adc9_write_u24 ( adc9_t *ctx, adc9_rw_t *rw, uint32_t wr_data );

/**
 * @brief Read 24-bit function
 *
 * @param ctx  Click object.
 * @param rw   Read/write object. 
 * <pre>
 * Struct Arguments: 
 *      dev_adr     8-bit value that defines the dvice
 *      reg         8-bit value that defines the register
 *      cmd         8-bit value that defines the command( static or incremental read )
 * </pre>  
 * @param rd_data  24-bit value that defines the output data
 *
 * @returns stat_byte 8-bit value that represents the device's status.
 *
 * @description Function is used to read three bytes of data from user defined register.
**/
uint8_t adc9_read_u24 (  adc9_t *ctx, adc9_rw_t *rw, uint32_t *rd_data );

/**
 * @brief Read 32-bit function
 *
 * @param ctx  Click object.
 * @param rw   Read/write object. 
 * <pre>
 * Struct Arguments: 
 *      dev_adr     8-bit value that defines the dvice
 *      reg         8-bit value that defines the register
 *      cmd         8-bit value that defines the command( static or incremental read )
 * </pre>  
 * @param rd_data  32-bit value that defines the output data
 *
 * @returns stat_byte 8-bit value that represents the device's status.
 *
 * @description Function is used to read four bytes of data from user defined register.
**/
uint8_t adc9_read_u32 (  adc9_t *ctx, adc9_rw_t *rw, uint32_t *rd_data );

/**
 * @brief Get IRQ pin state function
 *
 * @param ctx  Click object. 
 *
 * @returns    1 : Interrupt has not occured , 0 : Interrupt has occured
 *
 * @description Function is used to check if an interrupt has occured.
**/
uint8_t adc9_irq_pin_state ( adc9_t *ctx );

/**
 * @brief Read default adc format value function
 *
 * @param ctx  Click object.
 * @param rw   Read/write object. 
 * <pre>
 * Struct Argument: 
 *      dev_adr     8-bit value that defines the dvice.
 * </pre>  
 * @param rd_data     32-bit value that defines the ADC output data.
 *
 * @returns stat_byte 8-bit value that represents the device's status.
 *
 * @description Function is used to read ADC value when the default fata format is applied.
**/
uint8_t adc9_read_def_adc ( adc9_t *ctx, adc9_rw_t *rw, int32_t *rd_data );

/**
 * @brief Read left justified adc value function
 *
 * @param ctx  Click object.
 * @param rw   Read/write object. 
 * <pre>
 * Struct Argument: 
 *      dev_adr     8-bit value that defines the dvice.
 * </pre> 
 * @param rd_data     32-bit value that defines the ADC output data. 
 *
 * @returns stat_byte 8-bit value that represents the device's status.
 *
 * @description Function is used to read ADC value when the left-justified fata format is applied.
**/
uint8_t adc9_read_24_left_adc ( adc9_t *ctx, adc9_rw_t *rw, int32_t *rd_data );

/**
 * @brief Read Sign and ADC value function
 *
 * @param ctx  Click object.
 * @param rw   Read/write object. 
 * <pre>
 * Struct Argument: 
 *      dev_adr     8-bit value that defines the dvice.
 * </pre>  
 * @param rd_data  32-bit value that defines the ADC output data.
 *
 * @returns stat_byte 8-bit value that represents the device's status.
 *
 * @description Function is used to read ADC value when the read sign and ADC fata format is applied.
**/
uint8_t adc9_read_sign_adc ( adc9_t *ctx, adc9_rw_t *rw, int32_t *adc_val );

/**
 * @brief Read Channel and ADC value function
 *
 * @param ctx  Click object.
 * @param rw   Read/write object. 
 * <pre>
 * Struct Arguments: 
 *      dev_adr     8-bit value that defines the dvice.
 * </pre> 
 * @param rd_data  32-bit value that defines the ADC output data.
 * @param chan  8-bit value that defines the ADC output channel.
 *
 * @returns stat_byte 8-bit value that represents the device's status.
 *
 * @description Function is used to read ADC value when the read channel and ADC fata format is applied.
**/
uint8_t adc9_read_chan_adc ( adc9_t *ctx, adc9_rw_t *rw, int32_t *adc_val, uint8_t *chan );

/**
 * @brief Calculate Voltage function
 *
 * @param ctx  Click object. 
 * @param adc_val  32-bit value that defines the ADC input data.
 * @param v_ref    16-bit data that defines reference voltage.
 * @param gain     8-bit data that defines gain applied.
 *
 * @returns volt float  calculation value that represents voltage in millivolts.
 *
 * @description Function is used to calculate voltage based on ADC values.
**/
float adc9_volt_calc ( adc9_t *ctx, int32_t adc_val, uint16_t v_ref, uint8_t gain );

#ifdef __cplusplus
}
#endif
#endif  // _ADC9_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
