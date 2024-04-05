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
 * \brief This file contains API for Angle 4 Click driver.
 *
 * \addtogroup angle4 Angle 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ANGLE4_H
#define ANGLE4_H

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

#define ANGLE4_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ANGLE4_RETVAL  uint8_t

#define ANGLE4_OK           0x00
#define ANGLE4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define ANGLE4_REG_CUSTOMER_CFG_0                     0x04
#define ANGLE4_REG_CUSTOMER_CFG_1                     0x05
#define ANGLE4_REG_CUSTOMER_CFG_2                     0x06
#define ANGLE4_REG_OPERATING_VOLTAGE                  0x0A
#define ANGLE4_REG_UNLOCK_REGISTER                    0x10
#define ANGLE4_REG_CUSTOMER_RESERVED_OTP              0x11
#define ANGLE4_REG_ST_ZERO_RESET_OTP                  0x12
#define ANGLE4_REG_CUSTOMER_CONFIG_OTP                0x13
#define ANGLE4_REG_PROGRAM_OPERATING_VOLTAGE          0x14
#define ANGLE4_REG_CONFIG_OF_FULL_CALIBRATION_OTP     0x1B
/** \} */

/**
 * \defgroup customer_configuration_0 Customer Configuration 0
 * \{
 */
#define ANGLE4_CCFG0_SELECT_UVW_MODE                  0x80
#define ANGLE4_CCFG0_SELECT_PWM_MODE                  0x00
#define ANGLE4_CCFG0_PWM_PERIOD_8193us                0x60
#define ANGLE4_CCFG0_PWM_PERIOD_4097us                0x40
#define ANGLE4_CCFG0_PWM_PERIOD_2049us                0x20
#define ANGLE4_CCFG0_PWM_PERIOD_1025us                0x00
#define ANGLE4_CCFG0_ABI_360edeg                      0x18
#define ANGLE4_CCFG0_ABI_270edeg                      0x10
#define ANGLE4_CCFG0_ABI_180edeg                      0x08
#define ANGLE4_CCFG0_ABI_90edeg                       0x00
#define ANGLE4_CCFG0_UVW_POLE_PAIRS_8                 0x07
#define ANGLE4_CCFG0_UVW_POLE_PAIRS_7                 0x06
#define ANGLE4_CCFG0_UVW_POLE_PAIRS_6                 0x05
#define ANGLE4_CCFG0_UVW_POLE_PAIRS_5                 0x04
#define ANGLE4_CCFG0_UVW_POLE_PAIRS_4                 0x03
#define ANGLE4_CCFG0_UVW_POLE_PAIRS_3                 0x02
#define ANGLE4_CCFG0_UVW_POLE_PAIRS_2                 0x01
#define ANGLE4_CCFG0_UVW_POLE_PAIRS_1                 0x00
/** \} */

/**
 * \defgroup customer_configuration_1 Customer Configuration 1
 * \{
 */
#define ANGLE4_CCFG1_ABI_CPR_4096                     0x70
#define ANGLE4_CCFG1_ABI_CPR_2048                     0x60
#define ANGLE4_CCFG1_ABI_CPR_1024                     0x50
#define ANGLE4_CCFG1_ABI_CPR_512                      0x40
#define ANGLE4_CCFG1_ABI_CPR_256                      0x30
#define ANGLE4_CCFG1_ABI_CPR_128                      0x20
#define ANGLE4_CCFG1_ABI_CPR_64                       0x10
#define ANGLE4_CCFG1_ABI_CPR_32                       0x00
#define ANGLE4_CCFG1_HYSTERESIS_1_4mdeg               0x09
#define ANGLE4_CCFG1_HYSTERESIS_0_7mdeg               0x08
#define ANGLE4_CCFG1_HYSTERESIS_0_35mdeg              0x07
#define ANGLE4_CCFG1_HYSTERESIS_0_17mdeg              0x06
#define ANGLE4_CCFG1_HYSTERESIS_0_08mdeg              0x05
#define ANGLE4_CCFG1_HYSTERESIS_0_04mdeg              0x04
#define ANGLE4_CCFG1_HYSTERESIS_0_02mdeg              0x03
#define ANGLE4_CCFG1_HYSTERESIS_0_01mdeg              0x02
#define ANGLE4_CCFG1_HYSTERESIS_0_005mdeg             0x01
#define ANGLE4_CCFG1_NO_HYSTERESIS                    0x00
/** \} */

/**
 * \defgroup customer_configuration_2 Customer Configuration 2
 * \{
 */
#define ANGLE4_CCFG2_DIR_COUNTER_CLOCKWISE_ROTATION   0x80
#define ANGLE4_CCFG2_DIR_CLOCKWISE_ROTATION           0x00
#define ANGLE4_CCFG2_ZERO_LATENCY_MODE_ON             0x40
#define ANGLE4_CCFG2_ZERO_LATENCY_MODE_OFF            0x00
#define ANGLE4_CCFG2_ABS_RESOLUTION_10bit             0x30
#define ANGLE4_CCFG2_ABS_RESOLUTION_12bit             0x20
#define ANGLE4_CCFG2_ABS_RESOLUTION_14bit             0x10
#define ANGLE4_CCFG2_ABS_RESOLUTION_16bit             0x00
#define ANGLE4_CCFG2_SETTINGS_CPR_4096                0x06
#define ANGLE4_CCFG2_SETTINGS_CPR_2048                0x06
#define ANGLE4_CCFG2_SETTINGS_CPR_1024                0x04
#define ANGLE4_CCFG2_SETTINGS_CPR_512                 0x04
#define ANGLE4_CCFG2_SETTINGS_CPR_256                 0x03
#define ANGLE4_CCFG2_SETTINGS_CPR_128                 0x02
#define ANGLE4_CCFG2_SETTINGS_CPR_64                  0x02
#define ANGLE4_CCFG2_SETTINGS_CPR_32                  0x02
#define ANGLE4_CCFG2_CPR_ABS_RESOLUTION               0x04
/** \} */

/**
 * \defgroup operating_voltage Operating Voltage
 * \{
 */
#define ANGLE4_OPERATING_VOLTAGE_3300mV               0x00
#define ANGLE4_OPERATING_VOLTAGE_5000mV               0x02
/** \} */

/**
 * \defgroup absolute_resolution Absolute Resolution
 * \{
 */
#define ANGLE4_DATA_RESOLUTION_14bit                  0x10
#define ANGLE4_DATA_RESOLUTION_16bit                  0x00
#define ANGLE4_DATA_RESOLUTION_12bit                  0x30
#define ANGLE4_DATA_RESOLUTION_10bit                  0x30
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

    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

    uint8_t resolution;
    uint16_t new_angle;

} angle4_t;

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

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t  spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

    uint8_t cfg_resolution;
    uint16_t cfg_new_angle;

} angle4_cfg_t;

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
void angle4_cfg_setup ( angle4_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ANGLE4_RETVAL angle4_init ( angle4_t *ctx, angle4_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx                Click object.
 * @param dir                Direction definition (counter-clockwise rotation or clockwise rotation)
 * @param data_resolution    Absolute Resolution ( 10bit, 12bit, 14bit or 16bit)
 *
 * @description This function executes default configuration for Angle 4 click.
 */
void angle4_default_cfg ( angle4_t *ctx, uint8_t dir, uint8_t data_resolution );

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
void angle4_generic_transfer ( angle4_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );
/**
 * @brief One byte write function.
 *
 * @param ctx          Click object.
 * @param addr         Address in which the data will be written
 * @param w_data       Data which be written in the address
 * 
 * @description This function is used to write single byte of Data on the desired address.
 */
void angle4_write_byte ( angle4_t *ctx, uint8_t addr, uint8_t w_data );

/**
 * @brief One byte read function.
 *
 * @param ctx          Click object.
 * @param addr         Address from which data will be read.
 * @retval one byte of data that was read from the desired address.
 * 
 * @description This function is used to read single byte of Data on the desired address.
 */
uint8_t angle4_read_byte ( angle4_t *ctx, uint8_t addr );

/**
 * @brief Start meaasurement function.
 * 
 * @param ctx          Click object.
 * 
 * @description function used to start measurement mode.
 */
void angle4_start_mesuremenet ( angle4_t *ctx );

/**
 * @brief Functions for reading Angle
 *
 * @param ctx          Click object.
 * @param data_out     Buffer in which angle data will be stored.
 * @retval status
 *
 * Status :
 * <pre>
 *    3-bit Ready (chip is ready)
 *    2-bit Magnet High ( This indicates that the magnet strength detected by the chip is too strong. When this is flagged
 *    high consistently, change the weaker magnet or increase the distance between the chip and the magnet.)
 *    1-bit Magnet Low (This indicates that the magnet strength detected by the chip is too weak. When this is flagged high
 *    consistently, change the stronger magnet or decrease the distance between the chip and the magnet )
 *    0-bit Parity
 * </pre>
 * 
 * @description 
 */
uint8_t angle4_get_new_angle ( angle4_t *ctx, uint16_t *data_out );

#ifdef __cplusplus
}
#endif
#endif  // _ANGLE4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
