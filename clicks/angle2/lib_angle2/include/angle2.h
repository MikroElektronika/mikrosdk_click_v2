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
 * \brief This file contains API for Angle 2 Click driver.
 *
 * \addtogroup angle2 Angle 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ANGLE2_H
#define ANGLE2_H

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

#define ANGLE2_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ANGLE2_RETVAL  uint8_t

#define ANGLE2_OK           0x00
#define ANGLE2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup constants Constants
 * \{
 */
#define ANGLE2_WRITE_CMD                        0x20
#define ANGLE2_READ_CMD                         0x10
#define ANGLE2_DUMMY_BYTE                       0x00
#define ANGLE2_REG_ADDR_MASK                    0x0F

#define ANGLE2_BIAS_CURR_TRIMM_REG_3            0x03
#define ANGLE2_ZERO_POS_MSB_REG_4               0x04
#define ANGLE2_AXIS_TRIMM_AND_ZERO_LSB_REG_5    0x05
#define ANGLE2_FLASH_N_REG_9                    0x09

#define ANGLE2_X_AXIS_TRIMM_EN                  0x10
#define ANGLE2_Y_AXIS_TRIMM_EN                  0x20
#define ANGLE2_AXIS_TRIMM_DIS                   0x00

#define ANGLE2_FLASH_REG_3                      0x08
#define ANGLE2_FLASH_REG_4                      0x10
#define ANGLE2_FLASH_REG_5                      0x20
#define ANGLE2_NO_FLASH                         0x00

#define ANGLE2_DEG_LSB                 0.08789
#define ANGLE2_MAX_SCALE_359_91_DEG    359.91211
#define ANGLE2_MIN_SCALE_0_DEG         0
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

    digital_out_t cs;

    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} angle2_t;

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
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} angle2_cfg_t;

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
void angle2_cfg_setup ( angle2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ANGLE2_RETVAL angle2_init ( angle2_t *ctx, angle2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Angle 2 click.
 */
void angle2_default_cfg ( angle2_t *ctx );

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
void angle2_generic_transfer ( angle2_t *ctx,  uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf,  uint16_t rd_len );

/**
 * @brief Register write function.
 *
 * @param ctx          Click object.
 * @param addr         Register address.
 * @param input        Data to be written.
 *
 * @description This function writes 1 byte of data to the specified register address.
 */
double angle2_write_reg ( angle2_t *ctx, uint8_t addr, uint8_t input );

/**
 * @brief Register read function.
 *
 * @param ctx          Click object.
 * @param addr         Register address.
 * @param output       Variable in which the read data is stored.
 *
 * @description This function reads 1 byte of data from the specified register address.
 */
double angle2_read_reg ( angle2_t *ctx, uint8_t addr, uint8_t *output );

/**
 * @brief Angle read function.
 *
 * @param ctx          Click object.
 *
 * @description This function reads angle data from the click module.
 */
double angle2_get_angle ( angle2_t *ctx );

/**
 * @brief Angle with time index read function.
 *
 * @param ctx          Click object.
 *
 * @description This function reads angle and time index data from the click module.
 */
double angle2_get_angle_with_time_index ( angle2_t *ctx, uint8_t *time_index );

/**
 * @brief Set zero scale function.
 *
 * @param ctx          Click object.
 * @param zero_deg     Zero degree value.
 *
 * @description This function sets the zero scale value.
 */
void angle2_set_zero_scale ( angle2_t *ctx, double zero_deg );

/**
 * @brief Enable trimming function.
 *
 * @param ctx          Click object.
 * @param state        Trimming state.
 *
 * @description This function sets the trimming state.
 */
void angle2_enable_trimming ( angle2_t *ctx, uint8_t state );

/**
 * @brief Flash register function.
 *
 * @param ctx          Click object.
 * @param reg_sel      Register select.
 *
 * @description This function flashes the specified register.
 */
void angle2_flash_reg ( angle2_t *ctx, uint8_t reg_sel );

#ifdef __cplusplus
}
#endif
#endif  // _ANGLE2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
