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
 * \brief This file contains API for ADAC Click driver.
 *
 * \addtogroup adac ADAC Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ADAC_H
#define ADAC_H

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
#define ADAC_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ADAC_RETVAL  uint8_t

#define ADAC_OK           0x00
#define ADAC_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup configuration Configuration
 * \{
 */
#define ADAC_I2C_SLAVE_ADDR    0X10
#define ADAC_SOFT_RESET_CMD    0x0DAC
#define ADAC_NO_OP             0X00
#define ADAC_ADC_SEQUENCE      0X02
#define ADAC_GP_CONTROL        0X03
#define ADAC_ADC_CONFIG        0X04
#define ADAC_DAC_CONFIG        0X05
#define ADAC_PULL_DOWN         0X06
#define ADAC_LDAC_MODE         0X07
#define ADAC_GPIO_WR_CONFIG    0X08
#define ADAC_GPIO_WR_DATA      0X09
#define ADAC_GPIO_RD_CONFIG    0X0A
#define ADAC_POWER_REF_CTRL    0X0B
#define ADAC_OPEN_DRAIN_CFG    0X0C
#define ADAC_THREE_STATE       0X0D
#define ADAC_SOFT_RESET        0X0F
/** \} */

/**
 * \defgroup w_r_pointer_mod W/R Pointer Mod
 * \{
 */
#define ADAC_CONFIG_MOD    0X00
#define ADAC_DAC_WRITE     0X10
#define ADAC_ADC_READ      0X40
#define ADAC_DAC_READ      0X50
#define ADAC_GPIO_READ     0X60
#define ADAC_REG_READ      0X70
/** \} */

/**
 * \defgroup vref_sequence VREF & Sequence
 * \{
 */
#define ADAC_VREF_ON        0X02
#define ADAC_SEQUENCE_ON    0X02
/** \} */

/**
 * \defgroup pin_command_relation Pin - Command relation
 * \{
 */
#define ADAC_IO0    0X01
#define ADAC_IO1    0X02
#define ADAC_IO2    0X04
#define ADAC_IO3    0X08
#define ADAC_IO4    0X10
#define ADAC_IO5    0X20
#define ADAC_IO6    0X40
#define ADAC_IO7    0X80
/** \} */

/**
 * \defgroup pointer_byte_pin_selection Pointer Byte Pin Selection
 * \{
 */
#define ADAC_PB_PIN0    0X00
#define ADAC_PB_PIN1    0X01
#define ADAC_PB_PIN2    0X02
#define ADAC_PB_PIN3    0X03
#define ADAC_PB_PIN4    0X04
#define ADAC_PB_PIN5    0X05
#define ADAC_PB_PIN6    0X06
#define ADAC_PB_PIN7    0X07
/** \} */

/**
 * \defgroup pointer_byte_address Pointer Byte Address
 * \{
 */
#define ADAC_PB_DAC0    0X10
#define ADAC_PB_DAC1    0X11
#define ADAC_PB_DAC2    0X12
#define ADAC_PB_DAC3    0X13
#define ADAC_PB_DAC4    0X14
#define ADAC_PB_DAC5    0X15
#define ADAC_PB_DAC6    0X16
#define ADAC_PB_DAC7    0X17
/** \} */

/**
 * \defgroup general_purpose_register_commands General Purpose Register CMDs
 * \{
 */
#define ADAC_DAC_RANGE_SEL        0X0010
#define ADAC_ADC_RANGE_SEL        0X0020
#define ADAC_WRITE_ALL_DACS       0X0040
#define ADAC_LOCK_CONFIG          0X0080
#define ADAC_ADC_BUFF_ENABLE      0X0100
#define ADAC_ADC_BUFF_PRE_CHAR    0X0200
/** \} */

/**
 * \defgroup power_down_commands Power Down CMDs
 * \{
 */
#define ADAC_PD_CHAN_0          0X0001
#define ADAC_PD_CHAN_1          0X0002
#define ADAC_PD_CHAN_2          0X0004
#define ADAC_PD_CHAN_3          0X0008
#define ADAC_PD_CHAN_4          0X0010
#define ADAC_PD_CHAN_5          0X0020
#define ADAC_PD_CHAN_6          0X0040
#define ADAC_PD_CHAN_7          0x0080
#define ADAC_REF_BUFF_POW_UP    0x0200
#define ADAC_PD_ALL             0x0400
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
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} adac_t;

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

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} adac_cfg_t;

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
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void adac_cfg_setup ( adac_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param adac Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ADAC_RETVAL adac_init ( adac_t *ctx, adac_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void adac_generic_write ( adac_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void adac_generic_read ( adac_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Hardware reset function.
 *
 * @param ctx          Click object.
 *
 * @description This function does a hardware reset of the click module.
 */
void adac_hardware_reset ( adac_t *ctx );

/**
 * @brief Software reset function.
 *
 * @param ctx          Click object.
 * @param cmd          Command.
 *
 * @description This function does a software reset of the click module.
 */
void adac_software_reset ( adac_t *ctx, uint16_t cmd );

/**
 * @brief Power down function.
 *
 * @param ctx          Click object.
 * @param settings     Settings.
 *
 * @description This function configures power down settings of the click module.
 */
void adac_power_down_settings ( adac_t *ctx, uint16_t settings );

/**
 * @brief General purpose function.
 *
 * @param ctx          Click object.
 * @param settings     Settings.
 *
 * @description This function configures general purpose register settings of the click module.
 */
void adac_general_purpose_settings ( adac_t *ctx, uint16_t settings );

/**
 * @brief Read configuration function.
 *
 * @param ctx          Click object.
 *
 * @description This function acquires the current settings data of the click module.
 */
uint16_t adac_read_config( adac_t *ctx );

/**
 * @brief Write GPIO function.
 *
 * @param ctx          Click object.
 * @param w_data       Write data.
 *
 * @description This function writes GPIO data using the I2C serial interface.
 */
void adac_write_gpio ( adac_t *ctx, uint8_t w_data );

/**
 * @brief Read GPIO function.
 *
 * @param ctx          Click object.
 *
 * @description This function reads GPIO data using the I2C serial interface.
 */
uint8_t adac_read_gpio ( adac_t *ctx );

/**
 * @brief Read DAC function.
 *
 * @param ctx          Click object.
 * @param chan         DAC channel.
 *
 * @description This function reads DAC data using the I2C serial interface.
 */
uint16_t adac_read_dac ( adac_t *ctx, uint8_t *chan );

/**
 * @brief Read ADC function.
 *
 * @param ctx          Click object.
 * @param chan         ADC channel.
 * 
 * @description This function reads ADC data using the I2C serial interface.
 */
uint16_t adac_read_adc( adac_t *ctx, uint8_t *chan );

/**
 * @brief Write DAC data function.
 *
 * @param ctx          Click object.
 * @param chan         ADC channel.
 * @param w_data       Write data.
 * 
 * @description This function writes DAC data using the I2C serial interface.
 */
void adac_write_dac_data ( adac_t *ctx, uint8_t chan, uint16_t w_data );

/**
 * @brief Write DAC function.
 *
 * @param ctx          Click object.
 * @param chan         ADC channel.
 * @param msb          Most significant byte.
 * @param lsb          Least significant byte.
 * 
 * @description This function writes DAC using the I2C serial interface.
 */
void adac_write_dac ( adac_t *ctx, uint8_t chan, uint8_t msb, uint8_t lsb );

/**
 * @brief Set configuration function.
 *
 * @param ctx          Click object.
 * @param ptr          Pointer.
 * @param msb          Most significant byte.
 * @param lsb          Least significant byte.
 * 
 * @description This function sets the configuration for the click module.
 */
void adac_set_configuration ( adac_t *ctx, uint8_t ptr, uint8_t msb, uint8_t lsb );

/**
 * @brief Read data function.
 *
 * @param ctx          Click object.
 * @param addr         Register address.
 * 
 * @description This function reads 2 bytes of data from the specified register address using
 *              the I2C serial interface.
 */
uint16_t adac_read_data ( adac_t *ctx, uint8_t addr );

/**
 * @brief Write data function.
 *
 * @param ctx          Click object.
 * @param addr         Register address.
 * 
 * @description This function writes 2 bytes of data to the specified register address using 
 *              the I2C serial interface.
 */
void adac_write_data ( adac_t *ctx, uint8_t addr, uint16_t w_data );

#ifdef __cplusplus
}
#endif
#endif  // _ADAC_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
