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
 * \brief This file contains API for GRID EYE Click driver.
 *
 * \addtogroup grideye GRID EYE Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef GRIDEYE_H
#define GRIDEYE_H

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
#define GRIDEYE_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define GRIDEYE_RETVAL  uint8_t

#define GRIDEYE_OK           0x00
#define GRIDEYE_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup I2C Slave Address
 * \{
 */
#define GRIDEYE_I2C_ADDR     0x68
/** \} */

/**
 * \defgroup Register Addresses
 * \{
 */
#define GRIDEYE_PCLT                 0x00
#define GRIDEYE_RST                  0x01
#define GRIDEYE_FPSC                 0x02
#define GRIDEYE_INTC                 0x03
#define GRIDEYE_STAT                 0x04
#define GRIDEYE_SCLR                 0x05
#define GRIDEYE_AVE                  0x07

#define GRIDEYE_INTHL                0x08
#define GRIDEYE_INTHH                0x09
#define GRIDEYE_INTLL                0x0A
#define GRIDEYE_INTLH                0x0B
#define GRIDEYE_IHYSL                0x0C
#define GRIDEYE_IHYSH                0x0D
#define GRIDEYE_TTHL                 0x0E
#define GRIDEYE_TTHH                 0x0F
/** \} */

/**
 * \defgroup Interrupt Table Register
 * \{
 */
#define GRIDEYE_INT0                 0x10
#define GRIDEYE_INT1                 0x11
#define GRIDEYE_INT2                 0x12
#define GRIDEYE_INT3                 0x13
#define GRIDEYE_INT4                 0x14
#define GRIDEYE_INT5                 0x15
#define GRIDEYE_INT6                 0x16
#define GRIDEYE_INT7                 0x17
/** \} */

/**
 * \defgroup Power Control Register Commands
 * \{
 */
#define GRIDEYE_PCLT_NORMAL          0x00
#define GRIDEYE_PCLT_SLEEP           0x10
#define GRIDEYE_PCLT_STANDBY_60      0x20
#define GRIDEYE_PCLT_STANDBY_10      0x21
/** \} */

/**
 * \defgroup Reset Register Commands
 * \{
 */
#define GRIDEYE_RST_FLAG             0x30
#define GRIDEYE_RST_INIT             0x3F
/** \} */

/**
 * \defgroup Frame Rate Register commands
 * \{
 */
#define GRIDEYE_FPSC_1FPS            0x01
#define GRIDEYE_FPSC_10FPS           0x00
/** \} */

/**
 * \defgroup Status Clear Register commands
 * \{
 */
#define GRIDEYE_INTC_INTEN_ACTIVE            0x01
#define GRIDEYE_INTC_INTEN_INACTIVE          0x00
#define GRIDEYE_INTC_INTMOD_ABSO             0x10
#define GRIDEYE_INTC_INTMOD_DIFE             0x00
/** \} */

/**
 * \defgroup Status Clear Register commands
 * \{
 */
#define GRIDEYE_SCLR_INTCLR                  0x02
#define GRIDEYE_SCLR_OVS_CLR                 0x04
#define GRIDEYE_SCLR_OVT_CLR                 0x08
/** \} */

/**
 * \defgroup Average Register Commands
 * \{
 */
#define GRIDEYE_AVE_MAMOD_ACTIVE             0x20
#define GRIDEYE_AVE_MAMOD_INACTIVE           0x00
/** \} */

/**
 * \defgroup Grid-eye Pixels Array
 * \{
 */
#define GRIDEYE_PIXELS                       0x80
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

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} grideye_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} grideye_cfg_t;

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
void grideye_cfg_setup ( grideye_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
GRIDEYE_RETVAL grideye_init ( grideye_t *ctx, grideye_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Grideye click.
 */
void grideye_default_cfg ( grideye_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 *
 * @description This function writes data to the desired register.
 */
void grideye_generic_write ( grideye_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void grideye_generic_read ( grideye_t *ctx,  uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Write data function
 *
 * @param ctx Click object.
 * @param wr_addr  8-bit register address
 * @param wr_data  16-bit data to be written into registers
 *
 * @returns What function returns
 *
 * @description Function writes two bytes of data into two consecutive registers.
**/
void grideye_write_data ( grideye_t *ctx, uint8_t wr_addr, uint16_t wr_data );

/**
 * @brief Data read function
 *
 * @param ctx Click object.
 * @param rd_addr  8-bit register address
 *
 * @returns result 16-bit data from two consecutive registers.
 *
 * @description Function reads two bytes of data from two consecutive registers.
**/
uint16_t grideye_read_data ( grideye_t *ctx, uint8_t rd_addr );

/**
 * @brief Read whole grid function
 *
 * @param ctx Click object.
 * @param buffer data array used to store data from each of 128 registers of the grid
 *
 * @description Function is used to reada data from the whole sensor grid.
**/
void grideye_read_grid ( grideye_t *ctx, uint16_t *buffer );

/**
 * @brief Get Interrupt state function
 *
 * @param ctx Click object.
 * 
 * @return
 * - 1 : Interrupt has occured
 * - 0 : Interrupt has not occured
 *
 * @description Function is used to check if an interrupt has occured.
**/
uint8_t grideye_check_interrupt ( grideye_t *ctx );

/**
 * @brief Set Power Control function
 *
 * @param ctx Click object.
 * @param pow_cnt  8-bit data representing operating mode of device
 *
 * @description Function is used to set operating mode of device.
 * @note Consult datasheet or use predefined values.
**/
void grideye_set_power_control ( grideye_t *ctx, uint8_t pow_cnt );

/**
 * @brief Read Power Control function
 *
 * @param ctx Click object.
 * 
 * @returns result 8-bit data representing operating mode of device
 *
 * @description Function is used to read Power Control register.
 * @note Consult datasheet in order to discern what value represents.
**/
uint8_t grideye_read_power_control ( grideye_t *ctx );

/**
 * @brief Flag reset function
 *
 *@param ctx Click object.
 * 
 * @description Function is used to reset flags.
 * @note Flag reset function clears the Status Register, Interrupt Flag and Interrupt Table.
**/
void grideye_flag_reset ( grideye_t *ctx );

/**
 * @brief Initial reset function
 *
 @param ctx Click object.
 * 
 * @description Function is used to perform initial reset.
 * @note Initial Reset brings Flag reset and returns to initial setting.
**/
void grideye_initial_reset ( grideye_t *ctx );

/**
 * @brief Set FPS 1 function
 *
 * @param ctx Click object.
 * 
 *  @description Function is used for setting Frame Rate to 1FPS.
**/
void grideye_set_fps1 ( grideye_t *ctx );

/**
 * @brief Set FPS 10 function
 *
 * @param ctx Click object. 
 * 
 *  @description Function is used for setting Frame Rate to 10FPS.
**/
void grideye_set_fps10 ( grideye_t *ctx );

/**
 * @brief Check FPS function
 *
 * 
 * @param ctx Click object.
 * 
 * @returns result 8-bit data representing FPS
 *
 *  @description Function is used to check what fps setting is applied.
 * @note Consult datasheet in order to discern what value represents.
**/
uint8_t grideye_check_fps ( grideye_t *ctx );

/**
 * @brief Set Interrupt Control Register function
 *
 * @param ctx Click object.
 * @param int_cnt  8-bit data representing interrupt control settings
 *
 *  @description Function is used to apply interrupt control settings.
 * @note Consult datasheet or use predefined values.
**/
void grideye_set_int_ctl_reg ( grideye_t *ctx, uint8_t int_cnt );

/**
 * @brief Read Interrupt Control Register function
 *
 * @param ctx Click object.
 * 
 * @returns result 8-bit data representing interrupt control settings
 *
 *  @description Function is used to check interrupt control settings.
 * @note Consult datasheet in order to discern what value represents.
**/
uint8_t grideye_read_int_ctl_reg ( grideye_t *ctx );

/**
 * @brief Read Status Register function
 *
 * @param ctx Click object.
 * 
 * @returns result 8-bit data representing contents of status register
 *
 *  @description Function is used to read status register.
 * @note Consult datasheet in order to discern what value represents.
**/
uint8_t grideye_read_stat_reg ( grideye_t *ctx );

/**
 * @brief Set Status Clear Register function
 *
 * @param ctx Click object.
 * @param int_cnt  8-bit data representing status clear settings
 *
 *  @description Function is used to clear the Overflow Flags and Interrupt Flag.
 * @note Consult datasheet or use predefined values.
**/
void grideye_set_stat_clr_reg ( grideye_t *ctx, uint8_t int_cnt );

/**
 * @brief Set Average Register function
 *
 * 
 * @param ctx Click object.
 * @param mamod 8-bit data representing average output mode

 *  @description Function is used to set average output mode.
 * @note Consult datasheet or use predefined values.
**/
void grideye_set_ave_reg ( grideye_t *ctx, uint8_t mamod );

/**
 * @brief Read Average Register function
 *
 * @param ctx Click object.
 * 
 * @returns result 8-bit data representing average output mode
 *
 *  @description Function is used to check average output mode.
 * @note Consult datasheet in order to discern what value represents.
**/
uint8_t grideye_read_ave_reg ( grideye_t *ctx );

/**
 * @brief Set interrupt level high function
 *
 * @param ctx Click object.
 * @param wr_data  16-bit data representing interrupt level upper limit setting
 *
 *  @description Funkction is used to set interrupt level upper limit.
**/
void grideye_write_int_lvl_high ( grideye_t *ctx, uint16_t wr_data );

/**
 * @brief Set interrupt level low function
 *
 * @param wr_data  16-bit data representing interrupt level lower limit setting
 *
 *  @description Funkction is used to set interrupt level lower limit.
**/
void grideye_write_int_lvl_low( grideye_t *ctx, uint16_t wr_data );

/**
 * @brief Read interrupt level high function
 *
 * @param ctx Click object.
 * 
 * @returns result 16-bit data representing interrupt level upper limit setting
 *
 *  @description Funkction is used to check interrupt level upper limit.
**/
uint16_t grideye_read_int_lvl_high ( grideye_t *ctx );

/**
 * @brief Read interrupt level low function
 *
 * @param ctx Click object.
 * 
 * @returns result 16-bit data representing interrupt level lower limit setting
 *
 *  @description Funkction is used to check interrupt level lower limit.
**/
uint16_t grideye_read_int_lvl_low ( grideye_t *ctx );

/**
 * @brief Set interrupt hysteresis level function
 *
 * @param ctx Click object.
 * @param wr_data  16-bit data representing interrupt hysteresis level limit setting
 *
 *  @description Funkction is used to set interrupt hysteresis level limit.
**/
void grideye_write_int_hyst_lvl ( grideye_t *ctx, uint16_t wr_data );

/**
 * @brief Read interrupt hysteresis level function
 *
 * @param ctx Click object.
 * 
 * @returns result 16-bit data representing interrupt hysteresis level setting
 *
 *  @description Funkction is used to check interrupt hysteresis level limit.
**/
uint16_t grideye_read_int_hyst_lvl ( grideye_t *ctx );

/**
 * @brief Read Thermistor Temperature Register function
 *
 * @param ctx Click object.
 * 
 * @returns result float value representing temperature in centigrade
 *
 *  @description Function is used to read register which indicate thermistor temperature data.
**/
float grideye_read_therm_temp_reg ( grideye_t *ctx );

/**
 * @brief Read Interrupt Table Register 0 function
 *
 * @param ctx Click object.
 * 
 * @returns result 8-bit data representing pixels which temperature outputs are over the threshold.
 *
 *  @description Function is used to check pixels with temperature outputs are over the threshold.
**/
uint8_t grideye_read_int0 ( grideye_t *ctx );

/**
 * @brief Read Interrupt Table Register 1 function
 *
 * @param ctx Click object.
 * 
 * @returns result 8-bit data representing pixels which temperature outputs are over the threshold.
 *
 *  @description Function is used to check pixels with temperature outputs are over the threshold.
**/
uint8_t grideye_read_int1 ( grideye_t *ctx );
/**
 * @brief Read Interrupt Table Register 2 function
 *
 * @param ctx Click object.
 * 
 * @returns result 8-bit data representing pixels which temperature outputs are over the threshold.
 *
 *  @description Function is used to check pixels with temperature outputs are over the threshold.
**/
uint8_t grideye_read_int2 ( grideye_t *ctx );

/**
 * @brief Read Interrupt Table Register 3 function
 *
 * @param ctx Click object.
 * 
 * @returns result 8-bit data representing pixels which temperature outputs are over the threshold.
 *
 *  @description Function is used to check pixels with temperature outputs are over the threshold.
**/
uint8_t grideye_read_int3 ( grideye_t *ctx );

/**
 * @brief Read Interrupt Table Register 4 function
 *
 * @param ctx Click object.
 * 
 * @returns result 8-bit data representing pixels which temperature outputs are over the threshold.
 *
 *  @description Function is used to check pixels with temperature outputs are over the threshold.
**/
uint8_t grideye_read_int4 ( grideye_t *ctx );

/**
 * @brief Read Interrupt Table Register 5 function
 *
 * @param ctx Click object.
 * 
 * @returns result 8-bit data representing pixels which temperature outputs are over the threshold.
 *
 *  @description Function is used to check pixels with temperature outputs are over the threshold.
**/
uint8_t grideye_read_int5 ( grideye_t *ctx );

/**
 * @brief Read Interrupt Table Register 6 function
 *
 * @param ctx Click object.
 * 
 * @returns result 8-bit data representing pixels which temperature outputs are over the threshold.
 *
 *  @description Function is used to check pixels with temperature outputs are over the threshold.
**/
uint8_t grideye_read_int6 ( grideye_t *ctx );

/**
 * @brief Read Interrupt Table Register 7 function
 *
 * @param ctx Click object.
 * 
 * @returns result 8-bit data representing pixels which temperature outputs are over the threshold.
 *
 *  @description Function is used to check pixels with temperature outputs are over the threshold.
**/
uint8_t grideye_read_int7 ( grideye_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _GRIDEYE_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
