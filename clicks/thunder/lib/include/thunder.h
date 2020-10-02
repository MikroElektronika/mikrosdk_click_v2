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
 * \brief This file contains API for Thunder Click driver.
 *
 * \addtogroup thunder Thunder Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef THUNDER_H
#define THUNDER_H

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

#define THUNDER_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.irq   = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define THUNDER_RETVAL  uint8_t

#define THUNDER_OK                               0x00
#define THUNDER_INIT_ERROR                       0xFF
/** \} */

/**
 * \defgroup device_addresses Possible device addresses
 * \{
 */
#define THUNDER_DEV_ADDR_0                       0x00
#define THUNDER_DEV_ADDR_1                       0x01
#define THUNDER_DEV_ADDR_2                       0x02
#define THUNDER_DEV_ADDR_3                       0x03
/** \} */

/**
 * \defgroup register_addresses Register addresses
 * \{
 */
#define THUNDER_CONFIG_0_REG                     0x00
#define THUNDER_CONFIG_1_REG                     0x01
#define THUNDER_CONFIG_2_REG                     0x02
#define THUNDER_CONFIG_3_INTERR_REG              0x03
#define THUNDER_ENERGY_LIGHTNING_LSBYTE_REG      0x04
#define THUNDER_ENERGY_LIGHTNING_MSBYTE_REG      0x05
#define THUNDER_ENERGY_LIGHTNING_MMSBYTE_REG     0x06
#define THUNDER_DISTANCE_REG                     0x07
#define THUNDER_INTERR_PIN_CONFIG_REG            0x08
#define THUNDER_LDLUT_1_REG                      0x09
#define THUNDER_LDLUT_2_REG                      0x0A
#define THUNDER_LDLUT_3_REG                      0x0B
#define THUNDER_LDLUT_4_REG                      0x0C
#define THUNDER_LDLUT_5_REG                      0x0D
#define THUNDER_LDLUT_6_REG                      0x0E
#define THUNDER_LDLUT_7_REG                      0x0F
#define THUNDER_LDLUT_8_REG                      0x10
#define THUNDER_LDLUT_9_REG                      0x11
#define THUNDER_LDLUT_10_REG                     0x12
#define THUNDER_LDLUT_11_REG                     0x13
#define THUNDER_LDLUT_12_REG                     0x14
#define THUNDER_LDLUT_13_REG                     0x15
#define THUNDER_LDLUT_14_REG                     0x16
#define THUNDER_LDLUT_15_REG                     0x17
#define THUNDER_LDLUT_16_REG                     0x18
#define THUNDER_LDLUT_17_REG                     0x19
#define THUNDER_LDLUT_18_REG                     0x1A
#define THUNDER_LDLUT_19_REG                     0x1B
#define THUNDER_LDLUT_20_REG                     0x1C
#define THUNDER_LDLUT_21_REG                     0x1D
#define THUNDER_LDLUT_22_REG                     0x1E
#define THUNDER_LDLUT_23_REG                     0x1F
#define THUNDER_LDLUT_24_REG                     0x20
#define THUNDER_LDLUT_25_REG                     0x21
#define THUNDER_LDLUT_26_REG                     0x22
#define THUNDER_LDLUT_27_REG                     0x23
#define THUNDER_LDLUT_28_REG                     0x24
#define THUNDER_LDLUT_29_REG                     0x25
#define THUNDER_LDLUT_30_REG                     0x26
#define THUNDER_LDLUT_31_REG                     0x27
#define THUNDER_LDLUT_32_REG                     0x28
#define THUNDER_LDLUT_33_REG                     0x29
#define THUNDER_LDLUT_34_REG                     0x2A
#define THUNDER_LDLUT_35_REG                     0x2B
#define THUNDER_LDLUT_36_REG                     0x2C
#define THUNDER_LDLUT_37_REG                     0x2D
#define THUNDER_LDLUT_38_REG                     0x2E
#define THUNDER_LDLUT_39_REG                     0x2F
#define THUNDER_LDLUT_40_REG                     0x30
#define THUNDER_LDLUT_41_REG                     0x31
#define THUNDER_LDLUT_42_REG                     0x32
#define THUNDER_RESET_REG                        0x3C
#define THUNDER_CALIB_REG                        0x3D
/** \} */

/**
 * \defgroup  options_cfg_0_reg Options for Config 0 register
 * \{
 */
#define THUNDER_INDOOR                           0x24
#define THUNDER_OUTDOOR                          0x1C
#define THUNDER_NORMAL_MODE                      0x00
#define THUNDER_POWER_DOWN                       0x01
/** \} */

/**
 * \defgroup options_cfg_2_reg Options for Config 2 register
 * \{
 */
#define THUNDER_CLEAR_STAT                       0xC0
#define THUNDER_1_LIGHTNING                      0x80
#define THUNDER_5_LIGHTNINGS                     0x90
#define THUNDER_9_LIGHTNINGS                     0xA0
#define THUNDER_16_LIGHTNINGS                    0xB0
/** \} */

/**
 * \defgroup options_cfg_3_reg Options for Config 3 register
 * \{
 */
#define THUNDER_DIV_RATIO_16                     0x00
#define THUNDER_DIV_RATIO_32                     0x40
#define THUNDER_DIV_RATIO_64                     0x80
#define THUNDER_DIV_RATIO_128                    0xC0
#define THUNDER_MASK_DISTURBER                   0x20
#define THUNDER_UNMASK_DISTURBER                 0x00
#define THUNDER_NO_INTERR                        0x00
#define THUNDER_NOISE_LEVEL_INTERR               0x01
#define THUNDER_DISTURBER_INTERR                 0x04
#define THUNDER_LIGHTNING_INTERR                 0x08
/** \} */

/**
 * \defgroup options_irq_cfg_reg Options for Interrupt pin (IRQ) config register
 * \{
 */
#define THUNDER_LCO_ON_IRQ_PIN                   0x80
#define THUNDER_SRCO_ON_IRQ_PIN                  0x40
#define THUNDER_TRCO_ON_IRQ_PIN                  0x20
#define THUNDER_NO_DISPLAY_ON_IRQ_PIN            0x00
/** \} */

/**
 * \defgroup reset_and_rco Reset and RCO calibrate commands
 * \{
 */
#define THUNDER_RESET_COMM                       0x00
#define THUNDER_CALIB_RCO_COMM                   0x01
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

    // Input pins 

    digital_in_t irq;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} thunder_t;

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

    pin_name_t irq;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} thunder_cfg_t;

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
void thunder_cfg_setup ( thunder_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param thunder Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
THUNDER_RETVAL thunder_init ( thunder_t *ctx, thunder_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Thunder click.
 */
void thunder_default_cfg ( thunder_t *ctx );

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
void thunder_generic_transfer 
( 
    thunder_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Generic Write function
 *
 * @param ctx              Click object.
 * @param reg_addr         Address where data be written.
 * @param transfer_data    Data to be written.
 *
 * @returns 0 - OK, 1 - Wrong address parameter
 *
 * @description Function writes one byte to the register.
 */
uint8_t thunder_write_reg ( thunder_t *ctx, uint8_t reg_addr, uint8_t transfer_data );

/**
 * @brief Generic Read function
 *
 * @param ctx              Click object.
 * @param reg_addr         Address which from data be read.
 * @param data_ut          Buffer where data be stored.
 * @param n_bytes          Number of bytes to be read.
 *
 * @returns 0 - OK, 1 - Wrong address parameter, 2 - Too large number of bytes parameter (MAX 51 bytes)
 *
 * @description Function reads the desired number of bytes from the registers.
 */
uint8_t thunder_read_reg ( thunder_t *ctx, uint8_t reg_addr, uint8_t *data_out, uint8_t n_bytes );

/**
 * @brief Command Send function
 * 
 * @param ctx              Click object.
 * @param selCommand       0 - Reset command, Value different from 0 - RCO calibrate command
 *
 * @description Function performs the one of two possible commands.
 */
void thunder_send_command ( thunder_t *ctx, uint8_t command );

/**
 * @brief Interrupt Check function
 * 
 * @param ctx              Click object.
 * @returns 0x00 - No interrupt, 0x01 - Noise level too high, 0x04 - Disturber detected, 0x08 - Lightning interrupt
 *
 * @description Function checks and returns the interrupt value.
 */
uint8_t thunder_check_interr ( thunder_t *ctx );

/**
 * @brief Storm Information Get function
 *
 * @param ctx              Click object.
 * @param energy_out       Energy of the single lightning
 * @param distance_out     Distance estimation for the head of the storm
 *
 * @description Function gets energy of the single lightning and distance estimation for the head of the storm.
 */
void thunder_get_storm_info ( thunder_t *ctx, uint32_t *energy_out, uint8_t *distance_out );

/**
 * @brief IRQ Pin Check function
 * 
 * @param ctx              Click object.
 *
 * @description Function returns the value of the IRQ pin (INT).
 */
uint8_t thunder_check_irq_pin ( thunder_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _THUNDER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
