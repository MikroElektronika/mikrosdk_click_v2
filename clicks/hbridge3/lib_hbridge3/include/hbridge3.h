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
 * \brief This file contains API for H Bridge 3 Click driver.
 *
 * \addtogroup hbridge3 H Bridge 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef HBRIDGE3_H
#define HBRIDGE3_H

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
#include "drv_pwm.h"
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
#define HBRIDGE3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.dir = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.dis = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.cs  = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.sdo = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
  cfg.sdi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
  cfg.sck = MIKROBUS( mikrobus, MIKROBUS_SCK ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define HBRIDGE3_RETVAL  uint8_t

#define HBRIDGE3_OK                   0x00
#define HBRIDGE3_INIT_ERROR           0xFF
/** \} */

/**
 * \defgroup default_freq Default frequency value
 * \{
 */
#define HBRIDGE3_DEF_FREQ             20000
/** \} */

/**
 * \defgroup commands Commands
 * \{
 */
#define HBRIDGE3_CMD_RD_DIA           0x00
#define HBRIDGE3_CMD_RES_DIA          0x80
#define HBRIDGE3_CMD_RD_REV           0x20
#define HBRIDGE3_CMD_RD_CTRL          0x60
#define HBRIDGE3_CMD_WR_CTRL          0xE0
#define HBRIDGE3_CMD_WR_CTRL_RD_DIA   0xC0
/** \} */

/**
 * \defgroup wr_ctrl_command_parameters Wr Ctrl Command Parameters
 * \{
 */
#define HBRIDGE3_CTRL_VIA_PWM_DIR     0x00
#define HBRIDGE3_CTRL_VIA_SPI         0x80
#define HBRIDGE3_SPI_ENA_OUT          0x40
#define HBRIDGE3_SPI_DIS_OUT          0x00
#define HBRIDGE3_SPI_DIR_1            0x00
#define HBRIDGE3_SPI_DIR_2            0x20
#define HBRIDGE3_SPI_PWM_0            0x00
#define HBRIDGE3_SPI_PWM_1            0x01
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

    digital_out_t dir;
    digital_out_t dis;
    digital_out_t cs;

    
    // Modules 
    spi_master_t spi;
    pin_name_t chip_select;
    pwm_t pwm;

    // ctx variable 

    uint16_t pwm_period;
    uint32_t pwm_freq;

} hbridge3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t pwm;
    pin_name_t sdo;
    pin_name_t sdi;
    pin_name_t sck;
    
    // Additional gpio pins 

    pin_name_t dir;
    pin_name_t dis;
    pin_name_t cs;

    // static variable 

    uint32_t dev_pwm_freq;
    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} hbridge3_cfg_t;

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
void hbridge3_cfg_setup ( hbridge3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
HBRIDGE3_RETVAL hbridge3_init ( hbridge3_t *ctx, hbridge3_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for HBridge3 Click.
 */
void hbridge3_default_cfg ( hbridge3_t *ctx, float duty_cycle );

/**
 * @brief Generic sets PWM duty cycle.
 *
 * @param ctx          Click object.
 * @param duty_cycle   Duty cycle.
 *
 * @description This function sets the PWM duty cycle.
 */
void hbridge3_set_duty_cycle ( hbridge3_t *ctx, float duty_cycle );

/**
 * @brief Stop PWM module.
 *
 * @param ctx Click object.
 *
 * @description This function stops PWM module.
 */
void hbridge3_pwm_stop ( hbridge3_t *ctx );

/**
 * @brief Start PWM module.
 *
 * @param ctx  Click object.
 *
 * @description This function starts PWM module.
 */
void hbridge3_pwm_start ( hbridge3_t *ctx );

/** 
 * @brief Setting AN pin state
 * 
 * @param ctx       Click object.
 * @param pin_state State of AN pin to be set (0 for LOW state and 1 for HIGH state)
 * 
 * @description This function sets AN pin state
 */
void hbridge3_dir_set ( hbridge3_t *ctx, uint8_t pin_state );

/**
 * @brief Setting RST pin state
 * 
 * @param ctx       Click object.
 * @param pin_state State of RST pin to be set (0 for LOW state and 1 for HIGH state)
 * 
 * @description This function sets RST pin state
 */
void hbridge3_dis_set ( hbridge3_t *ctx, uint8_t pin_state );

/** 
 * @brief Setting CS pin state
 * 
 * @param ctx       Click object.
 * @param pin_state  State of CS pin to be set (0 for LOW state and 1 for HIGH state)
 * 
 * @description This function sets CS pin state
 */
void hbridge3_cs_set ( hbridge3_t *ctx, uint8_t pin_state );


/**
 * @brief Sending SPI command
 * 
 * @param ctx       Click object.
 * @param spi_command - SPI command
 * 
 * @returns SPI response to command sent
 * 
 * @description This function sends SPI command and receives response to command sent
 */
uint8_t hbridge3_spi ( hbridge3_t *ctx, uint8_t spi_command );


#ifdef __cplusplus
}
#endif
#endif  // _HBRIDGE3_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
