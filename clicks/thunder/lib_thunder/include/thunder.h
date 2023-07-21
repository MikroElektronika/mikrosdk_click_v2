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
#include "spi_specifics.h"

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
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b thunder_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define THUNDER_SET_DATA_SAMPLE_EDGE            SET_SPI_DATA_SAMPLE_EDGE
#define THUNDER_SET_DATA_SAMPLE_MIDDLE          SET_SPI_DATA_SAMPLE_MIDDLE

/**
 * \defgroup error_code Error Code
 * \{
 */
#define THUNDER_OK                              0x00
#define THUNDER_ERROR                           0xFF
/** \} */

/**
 * \defgroup device_addresses Possible device addresses
 * \{
 */
#define THUNDER_DEV_ADDR_0                      0x00
#define THUNDER_DEV_ADDR_1                      0x01
#define THUNDER_DEV_ADDR_2                      0x02
#define THUNDER_DEV_ADDR_3                      0x03
/** \} */

/**
 * \defgroup register_addresses Register addresses
 * \{
 */
#define THUNDER_REG_CONFIG_0                    0x00
#define THUNDER_REG_CONFIG_1                    0x01
#define THUNDER_REG_CONFIG_2                    0x02
#define THUNDER_REG_CONFIG_3_INTERR             0x03
#define THUNDER_REG_ENERGY_LIGHTNING_LSBYTE     0x04
#define THUNDER_REG_ENERGY_LIGHTNING_MSBYTE     0x05
#define THUNDER_REG_ENERGY_LIGHTNING_MMSBYTE    0x06
#define THUNDER_REG_DISTANCE                    0x07
#define THUNDER_REG_INTERR_PIN_CONFIG           0x08
#define THUNDER_REG_LDLUT_1                     0x09
#define THUNDER_REG_LDLUT_2                     0x0A
#define THUNDER_REG_LDLUT_3                     0x0B
#define THUNDER_REG_LDLUT_4                     0x0C
#define THUNDER_REG_LDLUT_5                     0x0D
#define THUNDER_REG_LDLUT_6                     0x0E
#define THUNDER_REG_LDLUT_7                     0x0F
#define THUNDER_REG_LDLUT_8                     0x10
#define THUNDER_REG_LDLUT_9                     0x11
#define THUNDER_REG_LDLUT_10                    0x12
#define THUNDER_REG_LDLUT_11                    0x13
#define THUNDER_REG_LDLUT_12                    0x14
#define THUNDER_REG_LDLUT_13                    0x15
#define THUNDER_REG_LDLUT_14                    0x16
#define THUNDER_REG_LDLUT_15                    0x17
#define THUNDER_REG_LDLUT_16                    0x18
#define THUNDER_REG_LDLUT_17                    0x19
#define THUNDER_REG_LDLUT_18                    0x1A
#define THUNDER_REG_LDLUT_19                    0x1B
#define THUNDER_REG_LDLUT_20                    0x1C
#define THUNDER_REG_LDLUT_21                    0x1D
#define THUNDER_REG_LDLUT_22                    0x1E
#define THUNDER_REG_LDLUT_23                    0x1F
#define THUNDER_REG_LDLUT_24                    0x20
#define THUNDER_REG_LDLUT_25                    0x21
#define THUNDER_REG_LDLUT_26                    0x22
#define THUNDER_REG_LDLUT_27                    0x23
#define THUNDER_REG_LDLUT_28                    0x24
#define THUNDER_REG_LDLUT_29                    0x25
#define THUNDER_REG_LDLUT_30                    0x26
#define THUNDER_REG_LDLUT_31                    0x27
#define THUNDER_REG_LDLUT_32                    0x28
#define THUNDER_REG_LDLUT_33                    0x29
#define THUNDER_REG_LDLUT_34                    0x2A
#define THUNDER_REG_LDLUT_35                    0x2B
#define THUNDER_REG_LDLUT_36                    0x2C
#define THUNDER_REG_LDLUT_37                    0x2D
#define THUNDER_REG_LDLUT_38                    0x2E
#define THUNDER_REG_LDLUT_39                    0x2F
#define THUNDER_REG_LDLUT_40                    0x30
#define THUNDER_REG_LDLUT_41                    0x31
#define THUNDER_REG_LDLUT_42                    0x32
#define THUNDER_REG_RESET                       0x3C
#define THUNDER_REG_CALIB                       0x3D
/** \} */

/**
 * \defgroup options_cfg_0_reg Options for Config 0 register
 * \{
 */
#define THUNDER_INDOOR                          0x24
#define THUNDER_OUTDOOR                         0x1C
#define THUNDER_NORMAL_MODE                     0x00
#define THUNDER_POWER_DOWN                      0x01
/** \} */

/**
 * \defgroup options_cfg_1_reg Options for Config 1 register
 * \{
 */
#define THUNDER_DEFAULT_NOISE_FLOOR_LVL         0x20
#define THUNDER_DEFAULT_WDG_THRESHOLD           0x02
/** \} */

/**
 * \defgroup options_cfg_2_reg Options for Config 2 register
 * \{
 */
#define THUNDER_CLEAR_STAT                      0xC0
#define THUNDER_1_LIGHTNING                     0x80
#define THUNDER_5_LIGHTNINGS                    0x90
#define THUNDER_9_LIGHTNINGS                    0xA0
#define THUNDER_16_LIGHTNINGS                   0xB0
#define THUNDER_DEFAULT_SREJ                    0x82
/** \} */

/**
 * \defgroup options_cfg_3_reg Options for Config 3 register
 * \{
 */
#define THUNDER_DIV_RATIO_16                    0x00
#define THUNDER_DIV_RATIO_32                    0x40
#define THUNDER_DIV_RATIO_64                    0x80
#define THUNDER_DIV_RATIO_128                   0xC0
#define THUNDER_MASK_DISTURBER                  0x20
#define THUNDER_UNMASK_DISTURBER                0x00
#define THUNDER_NO_INTERR                       0x00
#define THUNDER_NOISE_LEVEL_INTERR              0x01
#define THUNDER_DISTURBER_INTERR                0x04
#define THUNDER_LIGHTNING_INTERR                0x08
/** \} */

/**
 * \defgroup options_irq_cfg_reg Options for Interrupt pin (IRQ) config register
 * \{
 */
#define THUNDER_LCO_ON_IRQ_PIN                  0x80
#define THUNDER_SRCO_ON_IRQ_PIN                 0x40
#define THUNDER_TRCO_ON_IRQ_PIN                 0x20
#define THUNDER_NO_DISPLAY_ON_IRQ_PIN           0x00
#define THUNDER_DEFAULT_TUNE_CAP                0x03
/** \} */

/**
 * \defgroup reset_and_rco Reset and RCO calibrate commands
 * \{
 */
#define THUNDER_RESET_COMM                      0x00
#define THUNDER_CALIB_RCO_COMM                  0x01
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
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
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
 * @details This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void thunder_cfg_setup ( thunder_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param thunder Click object.
 * @param cfg Click configuration structure.
 * 
 * @return 0 - OK, -1 - ERROR
 * 
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t thunder_init ( thunder_t *ctx, thunder_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @details This function executes default configuration for Thunder click.
 */
void thunder_default_cfg ( thunder_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address
 * @param data_in      Write data buffer
 * @param len          Number of byte in write data buffer
 * 
 * @return 0 - OK, -1 - ERROR
 *
 * @details Generic SPI write, for sending packages
 */
err_t thunder_generic_write ( thunder_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address
 * @param data_out     Read data buffer
 * @param len          Number of byte in read data buffer
 * 
 * @return 0 - OK, -1 - ERROR
 *
 * @details Generic SPI read, for receiving packages
 */
err_t thunder_generic_read ( thunder_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Write reg function
 *
 * @param ctx              Click object.
 * @param reg              Address where data be written.
 * @param data_in          Data to be written.
 *
 * @return 0 - OK, -1 - ERROR
 *
 * @details Function writes one byte to the register.
 */
err_t thunder_write_reg ( thunder_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Read reg function
 *
 * @param ctx              Click object.
 * @param reg              Address which from data be read.
 * @param data_out         Buffer where data be stored.
 *
 * @return 0 - OK, -1 - ERROR
 *
 * @details Function reads a data byte from the registers.
 */
err_t thunder_read_reg ( thunder_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Command Send function
 * 
 * @param ctx              Click object.
 * @param command          0 - Reset command, Value different from 0 - RCO calibrate command
 *
 * @details Function performs the one of two possible commands.
 */
void thunder_send_command ( thunder_t *ctx, uint8_t command );

/**
 * @brief Interrupt Check function
 * 
 * @param ctx              Click object.
 * 
 * @return 0x00 - No interrupt, 0x01 - Noise level too high, 0x04 - Disturber detected, 0x08 - Lightning interrupt
 *
 * @details Function checks and returns the interrupt value.
 */
uint8_t thunder_check_int ( thunder_t *ctx );

/**
 * @brief Storm Information Get function
 *
 * @param ctx              Click object.
 * @param energy_out       Energy of the single lightning
 * @param distance_out     Distance estimation for the head of the storm
 *
 * @details Function gets energy of the single lightning and distance estimation for the head of the storm.
 */
void thunder_get_storm_info ( thunder_t *ctx, uint32_t *energy_out, uint8_t *distance_out );

/**
 * @brief IRQ Pin Check function
 * 
 * @param ctx              Click object.
 * 
 * @return Value of the IRQ pin (INT)
 *
 * @details Function returns the value of the IRQ pin (INT).
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
