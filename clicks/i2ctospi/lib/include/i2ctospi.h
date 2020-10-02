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
 * \brief This file contains API for I2C to SPI Click driver.
 *
 * \addtogroup i2ctospi I2C to SPI Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef I2CTOSPI_H
#define I2CTOSPI_H

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
#define I2CTOSPI_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define I2CTOSPI_RETVAL  uint8_t

#define I2CTOSPI_OK           0x00
#define I2CTOSPI_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup i2c_slave_addr I2C Slave Address
 * \{
 */
#define I2CTOSPI_I2C_SLAVE_ADDRESS_0                               0x28
#define I2CTOSPI_I2C_SLAVE_ADDRESS_1                               0x29
#define I2CTOSPI_I2C_SLAVE_ADDRESS_2                               0x2A
#define I2CTOSPI_I2C_SLAVE_ADDRESS_3                               0x2B
#define I2CTOSPI_I2C_SLAVE_ADDRESS_4                               0x2C
#define I2CTOSPI_I2C_SLAVE_ADDRESS_5                               0x2D
#define I2CTOSPI_I2C_SLAVE_ADDRESS_6                               0x2E
#define I2CTOSPI_I2C_SLAVE_ADDRESS_7                               0x2F
/** \} */

/**
 * \defgroup function_id Function ID
 * \{
 */
#define I2CTOSPI_CONFIGURE_SPI                                     0xF0
#define I2CTOSPI_CLEAR_INTERRUPT                                   0xF1
#define I2CTOSPI_IDLE_MODE                                         0xF2
#define I2CTOSPI_GPIO_WRITE                                        0xF4
#define I2CTOSPI_GPIO_READ                                         0xF5
#define I2CTOSPI_GPIO_ENABLE                                       0xF6
#define I2CTOSPI_GPIO_CONFIGURATION                                0xF7
/** \} */

/**
 * \defgroup cfg_spi_interface Configure SPI Interface
 * \{
 */
#define I2CTOSPI_CONFIGURE_SPI_ORDER_MSB_FIRST                     0x00
#define I2CTOSPI_CONFIGURE_SPI_ORDER_LSB_FIRST                     0x20
#define I2CTOSPI_CONFIGURE_SPI_MODE_SPICLK_LOW_LEADING_EDGE        0x00
#define I2CTOSPI_CONFIGURE_SPI_MODE_SPICLK_LOW_TRAILING_EDGE       0x04
#define I2CTOSPI_CONFIGURE_SPI_MODE_SPICLK_HIGH_LEADING_EDGE       0x08
#define I2CTOSPI_CONFIGURE_SPI_MODE_SPICLK_HIGH_TRAILING_EDGE      0x0C
#define I2CTOSPI_CONFIGURE_SPI_CLOCK_RATE_1843kHz                  0x00
#define I2CTOSPI_CONFIGURE_SPI_CLOCK_RATE_461kHz                   0x01
#define I2CTOSPI_CONFIGURE_SPI_CLOCK_RATE_115kHz                   0x02
#define I2CTOSPI_CONFIGURE_SPI_CLOCK_RATE_58kHz                    0x03
/** \} */

/**
 * \defgroup  cfg_gpio_write Configure GPIO Write
 * \{
 */
#define I2CTOSPI_CONFIGURE_GPIO_WRITE_PORT_ENABLE_SS0              0x01
#define I2CTOSPI_CONFIGURE_GPIO_WRITE_PORT_ENABLE_SS1              0x02
#define I2CTOSPI_CONFIGURE_GPIO_WRITE_PORT_ENABLE_SS2              0x04
#define I2CTOSPI_CONFIGURE_GPIO_WRITE_PORT_ENABLE_SS3              0x08
/** \} */

/**
 * \defgroup cfg_gpio_read Configure GPIO Read
 * \{
 */
#define I2CTOSPI_CONFIGURE_GPIO_READ_PORT_ENABLE_SS0               0x01
#define I2CTOSPI_CONFIGURE_GPIO_READ_PORT_ENABLE_SS1               0x02
#define I2CTOSPI_CONFIGURE_GPIO_READ_PORT_ENABLE_SS2               0x04
#define I2CTOSPI_CONFIGURE_GPIO_READ_PORT_ENABLE_SS3               0x08
/** \} */

/**
 * \defgroup cfg_gpio_enable Configure GPIO Enable
 * \{
 */
#define I2CTOSPI_CONFIGURE_GPIO_BIDIRECTIONAL_PORT_ENABLE_SS0      0x01
#define I2CTOSPI_CONFIGURE_GPIO_BIDIRECTIONAL_PORT_ENABLE_SS1      0x02
#define I2CTOSPI_CONFIGURE_GPIO_BIDIRECTIONAL_PORT_ENABLE_SS2      0x04
#define I2CTOSPI_CONFIGURE_GPIO_BIDIRECTIONAL_PORT_ENABLE_SS3      0x08
/** \} */

/**
 * \defgroup  gpio_cfg_types  GPIO Configuration Types
 * \{
 */
#define I2CTOSPI_CONFIGURE_GPIO_QUASI_BIDIRECTIONAL_SS0            0x00
#define I2CTOSPI_CONFIGURE_GPIO_PUSH_PULL_SS0                      0x01
#define I2CTOSPI_CONFIGURE_GPIO_INPUT_ONLY_SS0                     0x02
#define I2CTOSPI_CONFIGURE_GPIO_OPEN_DRAIN_SS0                     0x03
#define I2CTOSPI_CONFIGURE_GPIO_QUASI_BIDIRECTIONAL_SS1            0x00
#define I2CTOSPI_CONFIGURE_GPIO_PUSH_PULL_SS1                      0x04
#define I2CTOSPI_CONFIGURE_GPIO_INPUT_ONLY_SS1                     0x08
#define I2CTOSPI_CONFIGURE_GPIO_OPEN_DRAIN_SS1                     0x0C
#define I2CTOSPI_CONFIGURE_GPIO_QUASI_BIDIRECTIONAL_SS2            0x00
#define I2CTOSPI_CONFIGURE_GPIO_PUSH_PULL_SS2                      0x10
#define I2CTOSPI_CONFIGURE_GPIO_INPUT_ONLY_SS2                     0x20
#define I2CTOSPI_CONFIGURE_GPIO_OPEN_DRAIN_SS2                     0x30
#define I2CTOSPI_CONFIGURE_GPIO_QUASI_BIDIRECTIONAL_SS3            0x00
#define I2CTOSPI_CONFIGURE_GPIO_PUSH_PULL_SS3                      0x40
#define I2CTOSPI_CONFIGURE_GPIO_INPUT_ONLY_SS3                     0x80
#define I2CTOSPI_CONFIGURE_GPIO_OPEN_DRAIN_SS3                     0xC0

#define I2CTOSPI_SLAVEDEVICE_SS0                                  0x01
#define I2CTOSPI_SLAVEDEVICE_SS1                                  0x02
#define I2CTOSPI_SLAVEDEVICE_SS2                                  0x04
#define I2CTOSPI_SLAVEDEVICE_SS3                                  0x08

#define I2CTOSPI_RTC5_COMMAND_WRITE                                0x12
#define I2CTOSPI_RTC5_COMMAND_READ                                 0x13

#define I2CTOSPI_RTC5_REG_TIME_HUN_OF_SEC                          0x00
#define I2CTOSPI_RTC5_REG_TIME_SEC                                 0x01
#define I2CTOSPI_RTC5_REG_TIME_MIN                                 0x02
#define I2CTOSPI_RTC5_REG_TIME_HOUR                                0x03
#define I2CTOSPI_RTC5_REG_TIME_DAY_OF_THE_WEEK                     0x04
#define I2CTOSPI_RTC5_REG_TIME_DATE_DAY                            0x05
#define I2CTOSPI_RTC5_REG_TIME_DATE_MONTH                          0x06
#define I2CTOSPI_RTC5_REG_TIME_DATE_YEAR                           0x07
#define I2CTOSPI_RTC5_REG_CONFIG                                   0x08
#define I2CTOSPI_RTC5_REG_CALIBRATION                              0x09

#define I2CTOSPI_RTC5_COMMAND_CLEAR                                0x54
#define I2CTOSPI_RTC5_COMMAND_ENABLE_COUNTING                      0x80
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
    digital_out_t cs;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} i2ctospi_t;

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
    pin_name_t cs;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} i2ctospi_cfg_t;

/**
 * @brief Click spi object definition.
 */
typedef struct
{
    // Variable 
     uint8_t slave_device; 
     uint8_t function_id; 
     uint8_t reg_addr; 
     uint8_t n_bytes;

} i2ctospi_spi_t;

/**
 * @brief Click gpio object definition.
 */
typedef struct
{
    // Variable 
      uint8_t ss3_val; 
      uint8_t ss2_val; 
      uint8_t ss1_val; 
      uint8_t ss0_val;

} i2ctospi_gpio_t;

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
void i2ctospi_cfg_setup ( i2ctospi_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
I2CTOSPI_RETVAL i2ctospi_init ( i2ctospi_t *ctx, i2ctospi_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for I2cToSpi click.
 */
void i2ctospi_default_cfg ( i2ctospi_t *ctx );

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
void i2ctospi_generic_write ( i2ctospi_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void i2ctospi_generic_read ( i2ctospi_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Hardware reset function
 *
 * @param ctx          Click object.
 *
 * @description Function hardware reset I2C to SPI click board by cleared to '0' state of the RST pin,
 * wait the 100 ms, sets to '1' state of the RST pin and wait another the 100 ms.
 *
 * @note
 * Delay is 200 ms.
*/
void i2ctospi_hw_reset ( i2ctospi_t *ctx );

/**
 * @brief Gets state of the interrupt function
 *
 * @param ctx          Click object.
 *
 * @returns interrupt state: 0 - No active; 1 - Active;
 *
 * @description  Function gets state of the INT pin on I2C to SPI click board.
*/
uint8_t i2ctospi_get_interrupt ( i2ctospi_t *ctx );

/**
 * @brief Generic SPI write the byte of data to data buffer function
 *
 * @param ctx          Click object.
 * @param spi          Spi object.
 * <pre>
 * Arguments:
 *  - slave_device               slave device ( SS0, SS1, SS2 or SS3 )
 *  - function_id                8-bit function id data.
 *  - reg_addr                   8-bit register address.
 * </pre>
 * @param write_data   8-bit data to write
 *
 * @description  Function SPI write the byte of data to the targeted 8-bit register address 
 * of the SC18IS602B I2C-bus to SPI bridge on the I2C to SPI click board.
*/
void i2ctospi_spi_write_byte ( i2ctospi_t *ctx, i2ctospi_spi_t *spi, uint8_t write_data );

/**
 * @brief Generic SPI read the byte of data from data buffer function
 *
 * @param ctx          Click object.
 * @param spi          Spi object.
 * <pre>
 * Arguments:
 *  - slave_device               slave device ( SS0, SS1, SS2 or SS3 ).
 *  - function_id                8-bit function id data.
 *  - reg_addr                   8-bit register address.
 * </pre>
 *
 * @returns the byte of data from data buffer
 *
 * @description Function SPI read the byte of data from the targeted 8-bit register address 
 * of the SC18IS602B I2C-bus to SPI bridge on the I2C to SPI click board.
*/
uint8_t i2ctospi_spi_read_byte ( i2ctospi_t *ctx, i2ctospi_spi_t *spi );

/**
 * @brief Generic SPI write - single address burst write function
 *
 * @param ctx          Click object.
 * @param spi          Spi object.
 * <pre>
 * Arguments:
 *  - slave_device               slave device ( SS0, SS1, SS2 or SS3 ).
 *  - function_id                8-bit function id data.
 *  - reg_addr                   8-bit register address.
 *  - n_bytes                    number of bytes to be written.
 * </pre>
 * @param write_data   Pointer to the data to be written
 *
 * @description Function SPI burst write data to the targeted 8-bit register address of the
 * SC18IS602B I2C-bus to SPI bridge on the I2C to SPI click board.
*/
void i2ctospi_spi_burst_write ( i2ctospi_t *ctx, i2ctospi_spi_t *spi, uint8_t *write_data );

/**
 * @brief Generic SPI read - single address burst read function
 *
 * @param ctx          Click object.
 * @param spi          Spi object.
 * <pre>
 * Arguments:
 *  - slave_device               slave device ( SS0, SS1, SS2 or SS3 ).
 *  - function_id                8-bit function id data.
 *  - reg_addr                   8-bit register address.
 *  - n_bytes                    number of bytes to be written.
 * </pre>
 *
 * @param read_data     Pointer to the memory location where data be stored
 *
 * @description Function SPI burst read data from the targeted 8-bit register address of the
 * SC18IS602B I2C-bus to SPI bridge on the I2C to SPI click board.
*/ 
void i2ctospi_spi_burst_read ( i2ctospi_t *ctx, i2ctospi_spi_t *spi, uint8_t *read_data );

/**
 * @brief Generic sequential read from the data buffer function
 *
 * @param ctx          Click object.
 * @param spi          Spi object.
 * <pre>
 * Arguments:
 *  - reg_addr                   8-bit register address.
 *  - n_bytes                    number of bytes to be written.
 * </pre>
 *
 * @param read_data    Pointer to the memory location where data be stored
 *
 * @description Function sequential read data starts from the targeted 8-bit buffer register
 * address of the SC18IS602B I2C-bus to SPI bridge on the I2C to SPI click board.
 */
void i2ctospi_read_buffer_bytes ( i2ctospi_t *ctx, i2ctospi_spi_t *spi, uint8_t *read_data );

/**
 * @brief Generic write command byte of data function
 *
 * @param ctx          Click object.
 * @param spi          Spi object.
 * <pre>
 * Argument:
 *  - function_id                8-bit function id ( from 0xF0 to 0xF7 )
 * </pre>
 *
 * @param command_data  8-bit command data
 *
 * @description  Function write the bytes of data command to the 8-bit register address of the
 * SC18IS602B I2C-bus to SPI bridge on the I2C to SPI click board.
*/
void i2ctospi_write_command ( i2ctospi_t *ctx, i2ctospi_spi_t *spi, uint8_t command_data );

/**
 * @brief SPI EEPROM wite enable function
 *
 * @param ctx          Click object.
 * @param ss_pin_data
 * <pre>
 * - 0x01 : SS0;
 * - 0x02 : SS1;
 * - 0x04 : SS2;
 * - 0x08 : SS3;
 * </pre>
 *
 * @description Function SPI EEPROM wite enable by enable selected SPI port 
 * ( SS0, SS1, SS2 or SS3 ) SC18IS602B I2C-bus to SPI bridge on the I2C to SPI click board.
*/
void i2ctospi_write_enable ( i2ctospi_t *ctx, uint8_t ss_pin_data );

/**
 * @brief Configure SPI Interface function
 *
 * @param ctx          Click object.
 * @param config_data
 * <pre>               
 * 8-bit configuration data:
 * - bit [ 7 : 6 ] : reserved
 * - bit [ 5 ]     : ORDER:
 *                   - 0 : MSB of the data word is transmitted first
 *                   - 1 : LSB of the data word is transmitted first
 * - bit [ 4 ]     : reserved
 * - bit [ 3 : 2 ] : MODE:
 *                   - 0 : SPICLK LOW when idle; data clocked in on leading edge ( CPOL = 0, CPHA = 0 );
 *                   - 1 : SPICLK LOW when idle; data clocked in on trailing edge ( CPOL = 0, CPHA = 1 );
 *                   - 2 : SPICLK HIGH when idle; data clocked in on trailing edge ( CPOL = 1, CPHA = 0 );
 *                   - 3 : SPICLK HIGH when idle; data clocked in on leading edge ( CPOL = 1, CPHA = 1 );
 * - bit [ 1 : 0 ] : SPI clock rate
 *                   - 0 : 1843 kHz;
 *                   - 1 :  461 kHz;
 *                   - 2 :  115 kHz;
 *                   - 3 :   58 kHz;
 * </pre>
 *
 * @description Function configure SPI Interface by write configuration the byte of data
 * to the targeted [ I2CTOSPI_CONFIGURE_SPI ] register address 
 * of the SC18IS602B I2C-bus to SPI bridge on the I2C to SPI click board.
 */
void i2ctospi_config_spi ( i2ctospi_t *ctx, uint8_t config_data );

/**
 * @brief Clear interrupt function
 *
 * @param ctx          Click object.
 *
 * @description Function clear interrupt is generated by the SC18IS602B
 * after any SPI transmission has been completed.
 *
 * @note
 * This interrupt can be cleared ( INT pin HIGH ) by sending a clear interrupt command
 * to the targeted [ I2CTOSPI_CLEAR_INTERRUPT ] register address
 * SC18IS602B I2C-bus to SPI bridge on the I2C to SPI click board.
*/ 
void i2ctospi_clear_interrupt ( i2ctospi_t *ctx );

/**
 * @brief Set Idle mode function
 *
 * @param ctx          Click object.
 *
 * @description Function set Idle mode, a low-power mode may be entered 
 * by sending the Idle Mode command to the targeted [ I2CTOSPI_IDLE_MODE ] register address
 * SC18IS602B I2C-bus to SPI bridge on the I2C to SPI click board.
*/
void i2ctospi_set_idle_mode ( i2ctospi_t *ctx );

/**
 * @brief Set state of the pins defined as GPIO write function
 *
 * @param ctx          Click object.
 * @param gpio_state
 * <pre>  
 *  - 0x01 [ I2CTOSPI_CONFIGURE_GPIO_WRITE_PORT_ENABLE_SS0 ] : SS0;
 *  - 0x02 [ I2CTOSPI_CONFIGURE_GPIO_WRITE_PORT_ENABLE_SS1 ] : SS1;
 *  - 0x04 [ I2CTOSPI_CONFIGURE_GPIO_WRITE_PORT_ENABLE_SS2 ] : SS2;
 *  - 0x08 [ I2CTOSPI_CONFIGURE_GPIO_WRITE_PORT_ENABLE_SS3 ] : SS3;
 * </pre>  
 *
 * @description Function set state of the pins defined as GPIO write
 * determine the state of SS3, SS2, SS1, and SS0, if they are configured as GPIO.
 *
 * @note
 * The Port Enable function will define if these pins are used as SPI Slave Selects or if 
 * they are GPIO of the SC18IS602B I2C-bus to SPI bridge on the I2C to SPI click board.
*/
void i2ctospi_set_write_state_of_gpio ( i2ctospi_t *ctx, uint8_t gpio_state );

/**
 * @brief Set state of the pins defined as GPIO read function
 *
 * @param ctx          Click object.
 * @param gpio_state
 * <pre>  
 *  - 0x01 [ I2CTOSPI_CONFIGURE_GPIO_READ_PORT_ENABLE_SS0 ] : SS0;
 *  - 0x02 [ I2CTOSPI_CONFIGURE_GPIO_READ_PORT_ENABLE_SS1 ] : SS1;
 *  - 0x04 [ I2CTOSPI_CONFIGURE_GPIO_READ_PORT_ENABLE_SS2 ] : SS2;
 *  - 0x08 [ I2CTOSPI_CONFIGURE_GPIO_READ_PORT_ENABLE_SS3 ] : SS3;
 * </pre>  
 *
 * @description Function set the state of the pins defined as GPIO may be read into the 
 * SC18IS602B data buffer using the GPIO read by write 8-bit gpioState data to the after 
 * write targeted [ I2CTOSPI_GPIO_READ ] functio Id
 * to the SC18IS602B I2C-bus to SPI bridge on the I2C to SPI click board.
*/
void i2ctospi_set_read_state_of_gpio ( i2ctospi_t *ctx, uint8_t gpio_state );

/**
 * @brief Enable the pins defined as GPIO function
 *
 * @param ctx          Click object.
 * @param ss_pin_number
 * <pre>  
 * - 0x01 [ I2CTOSPI_CONFIGURE_GPIO_BIDIRECTIONAL_PORT_ENABLE_SS0 ] : SS0;
 * - 0x02 [ I2CTOSPI_CONFIGURE_GPIO_BIDIRECTIONAL_PORT_ENABLE_SS1 ] : SS1;
 * - 0x04 [ I2CTOSPI_CONFIGURE_GPIO_BIDIRECTIONAL_PORT_ENABLE_SS2 ] : SS2;
 * - 0x08 [ I2CTOSPI_CONFIGURE_GPIO_BIDIRECTIONAL_PORT_ENABLE_SS3 ] : SS3;
 * </pre>  
 *
 * @description Function enable the pins defined as GPIO, the Slave Select pins 
 * ( SS0, SS1, SS2 and SS3 ) are configured to be used as slave select outputs
 * by write 8-bit ss_pin_number data after write targeted [ I2CTOSPI_GPIO_ENABLE ] functio Id
 * to the SC18IS602B I2C-bus to SPI bridge on the I2C to SPI click board.
*/
void i2ctospi_enable_gpio ( i2ctospi_t *ctx, uint8_t ss_pin_number );

/**
 * @brief Enable the pins defined as GPIO function
 *
 * @param ctx          Click object.
 * @param gpio         GPIO object.
 * <pre>
 * Arguments:
 * ~ ss3_val 
 *      - 0x00 : quasi-bidirectional;
 *      - 0x01 : push-pull;
 *      - 0x02 : input-only (high-impedance);
 *      - 0x03 : open-drain;
 * ~ ss2_val
 *      - 0x00 : quasi-bidirectional;
 *      - 0x01 : push-pull;
 *      - 0x02 : input-only (high-impedance);
 *      - 0x03 : open-drain;
 * ~ ss1_val
 *      - 0x00 : quasi-bidirectional;
 *      - 0x01 : push-pull;
 *      - 0x02 : input-only (high-impedance);
 *      - 0x03 : open-drain;
 * ~ ss0_val
 *      - 0x00 : quasi-bidirectional;
 *      - 0x01 : push-pull;
 *      - 0x02 : input-only (high-impedance);
 *      - 0x03 : open-drain;
 * </pre>  
 *
 * @description Function enable the pins defined as GPIO configured by software to one of four 
 * types on a pin-by-pin basis by write types on a selected SS pins basis 8-bit data
 * after write targeted [ _I2CTOSPI_GPIO_CONFIGURATION ] functio Id
 * to the SC18IS602B I2C-bus to SPI bridge on the I2C to SPI click board.
 */
void i2ctospi_types_gpio ( i2ctospi_t *ctx, i2ctospi_gpio_t *gpio );

#ifdef __cplusplus
}
#endif
#endif  // _I2CTOSPI_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
