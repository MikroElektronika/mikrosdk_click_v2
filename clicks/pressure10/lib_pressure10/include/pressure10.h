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
 * \brief This file contains API for Pressure 10 Click driver.
 *
 * \addtogroup pressure10 Pressure 10 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PRESSURE10_H
#define PRESSURE10_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
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

#define PRESSURE10_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.rdy = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define PRESSURE10_MASTER_I2C 0
#define PRESSURE10_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PRESSURE10_RETVAL  uint8_t

#define PRESSURE10_OK           0x00
#define PRESSURE10_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup return_error     RETURN ERROR
 * \{
 */
#define DEVICE_OK 0
#define DEVICE_ERROR 1
/** \} */

/**
 * \defgroup communication    COMMUNICATION
 * \{
 */
#define I2C_COMMUNICATION 1
#define SPI_COMMUNICATION 0
/** \} */

/**
 * \defgroup device_slave_addr    DEVICE SLAVE ADDR
 * \{
 */
#define PRESSURE10_DEVICE_SLAVE_ADDR_0        0x48
#define PRESSURE10_DEVICE_SLAVE_ADDR_1        0x49
/** \} */

/**
 * \defgroup register_and_command    REGISTER AND COMMAND
 * \{
 */
#define PRESSURE10_REG_WHO_I_AM               0x00
#define PRESSURE10_REG_INFORMATION            0x01
#define PRESSURE10_REG_FIFO_STATUS            0x02
#define PRESSURE10_REG_STATUS                 0x03
#define PRESSURE10_REG_PRESSURE_OUT_LOW       0x04
#define PRESSURE10_REG_PRESSURE_OUT_MID       0x05
#define PRESSURE10_REG_PRESSURE_OUT_HIGH      0x06
#define PRESSURE10_REG_TEMP_OUT_LOW           0x09
#define PRESSURE10_REG_TEMP_OUT_HIGH          0x0A
#define PRESSURE10_REG_DRDY_PIN_CRTL          0x0D
#define PRESSURE10_REG_CONTROL_1              0x0E
#define PRESSURE10_REG_CONTROL_2              0x0F
#define PRESSURE10_REG_ACTION_CONTROL_1       0x10
#define PRESSURE10_REG_ACTION_CONTROL_2       0x11
#define PRESSURE10_REG_FIFO_CONTROL           0x12
#define PRESSURE10_REG_AVERAGE_CONTROL        0x13
#define PRESSURE10_REG_I2C_DISABLE            0x15
#define PRESSURE10_REG_PRODUCT_NUMBER         0x1C
#define PRESSURE10_CMD_PRESS_DETECTION        0x20
#define PRESSURE10_CMD_TEMP_DETECTION         0x22
#define PRESSURE10_CMD_SW_RESET               0x26
#define PRESSURE10_CMD_PT_DETECTION           0x29
/** \} */

/**
 * \defgroup default_value   DEFAULT VALUE
 * \{
 */
#define PRESSURE10_DEF_WHO_I_AM               0x49
#define PRESSURE10_DEF_INFO                   0x31
#define PRESSURE10_DEF_PRODUCT_NUM            0x40
/** \} */

/**
 * \defgroup drdy_ctrl_register   DRDY CTRL REGISTER
 * \{
 */
#define PRESSURE10_CTRLDRDY_AFEV_ENABLE       0x80
#define PRESSURE10_CTRLDRDY_AFEV_DISABLE      0x00
#define PRESSURE10_CTRLDRDY_ATDR_ENABLE       0x10
#define PRESSURE10_CTRLDRDY_ATDR_DISABLE      0x00
#define PRESSURE10_CTRLDRDY_APOR_ENABLE       0x04
#define PRESSURE10_CTRLDRDY_APOR_DISABLE      0x00
#define PRESSURE10_CTRLDRDY_APDY_ENABLE       0x01
#define PRESSURE10_CTRLDRDY_APDY_DISABLE      0x00
/** \} */

/**
 * \defgroup control_1_register   CONTROL 1 REGISTER
 * \{
 */
#define PRESSURE10_CTRL1_PDRP_LOW_ACTIVE      0x00
#define PRESSURE10_CTRL1_PDRP_HIGH_ACTIVE     0x10
#define PRESSURE10_CTRL1_PTAP_ULTRA_LOW_PWR   0x00
#define PRESSURE10_CTRL1_PTAP_LOW_PWR         0x01
#define PRESSURE10_CTRL1_PTAP_HIGH_ACCURACY   0x02
#define PRESSURE10_CTRL1_PTAP_ULTRA_ACCURACY  0x03
/** \} */

/**
 * \defgroup control_2_register   CONTROL 2 REGISTER
 * \{
 */
#define PRESSURE10_CTRL2_TMES_DISABLE         0x00
#define PRESSURE10_CTRL2_TMES_ENABLE          0x80
#define PRESSURE10_CTRL2_PMES_DISABLE         0x00
#define PRESSURE10_CTRL2_PMES_ENABLE          0x20
#define PRESSURE10_CTRL2_ODR_1HZ              0x00
#define PRESSURE10_CTRL2_ODR_10HZ             0x04
#define PRESSURE10_CTRL2_ODR_100HZ            0x08
#define PRESSURE10_CTRL2_ODR_200HZ            0x0C
#define PRESSURE10_CTRL2_MODE_REG_ACTION      0x00
#define PRESSURE10_CTRL2_MODE_CONT_MEAS       0x01
#define PRESSURE10_CTRL2_MODE_CMD_ACTION      0x02
/** \} */

/**
 * \defgroup action_ctrl_1_register   ACTION CTRL 1 REGISTER
 * \{
 */
#define PRESSURE10_ACTRL1_TEMP_NO_MEAS        0x00
#define PRESSURE10_ACTRL1_TEMP_MEAS           0x08
#define PRESSURE10_ACTRL1_PRESS_NO_MEAS       0x00
#define PRESSURE10_ACTRL1_PRESS_MEAS          0x02
/** \} */

/**
 * \defgroup action_ctrl_2_register    ACTION CTRL 2 REGISTER
 * \{
 */
#define PRESSURE10_ACTRL2_SW_RESET_NONE       0x00
#define PRESSURE10_ACTRL2_SW_RESET_EXECUTE    0x80
/** \} */

/**
 * \defgroup average_ctrl     AVERAGE CTRL
 * \{
 */
#define PRESSURE10_AVCTRL_TFRQ_ONLY_FIRST_TIME        0x00
#define PRESSURE10_AVCTRL_TFRQ_ONLY_EVERY_64_TIMES    0x08
#define PRESSURE10_AVCTRL_TFRQ_ONLY_EVERY_32_TIMES    0x10
#define PRESSURE10_AVCTRL_TFRQ_ONLY_EVERY_16_TIMES    0x18
#define PRESSURE10_AVCTRL_TFRQ_ONLY_EVERY_8_TIMES     0x20
#define PRESSURE10_AVCTRL_TFRQ_ONLY_EVERY_4_TIMES     0x28
#define PRESSURE10_AVCTRL_TFRQ_ONLY_EVERY_2_TIMES     0x30
#define PRESSURE10_AVCTRL_TFRQ_EVERY_TIME             0x38
#define PRESSURE10_AVCTRL_AVG_NONE                    0x00
#define PRESSURE10_AVCTRL_AVG_X2                      0x01
#define PRESSURE10_AVCTRL_AVG_X4                      0x02
#define PRESSURE10_AVCTRL_AVG_X8                      0x03
#define PRESSURE10_AVCTRL_AVG_X16                     0x04
#define PRESSURE10_AVCTRL_AVG_X32                     0x05
#define PRESSURE10_AVCTRL_AVG_X64                     0x06
#define PRESSURE10_AVCTRL_AVG_X128                    0x07
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

typedef struct
{
    uint8_t busy;
    uint8_t temp_meas;
    uint8_t data_over;
    uint8_t press_meas;
} pressure10_status_t;


/**
 * @brief Communication type.
 */
typedef uint8_t  pressure10_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *pressure10_master_io_t )( struct pressure10_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct pressure10_s
{
    // Output pins 
    
    digital_out_t cs;

    // Input pins 

    digital_in_t rdy;
    
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

   uint8_t slave_address;
   pin_name_t chip_select;
   pressure10_master_io_t  write_f;
   pressure10_master_io_t  read_f;
   pressure10_select_t master_sel;

} pressure10_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;
    
    // Additional gpio pins 

    pin_name_t rdy;

    // static variable 

    uint32_t i2c_speed;
    uint8_t  i2c_address;

    uint32_t spi_speed;
    spi_master_mode_t  spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

   pressure10_select_t sel;

} pressure10_cfg_t;

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
void pressure10_cfg_setup ( pressure10_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param pressure10 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
PRESSURE10_RETVAL pressure10_init ( pressure10_t *ctx, pressure10_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Pressure 10 click.
 */
void pressure10_default_cfg ( pressure10_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx        Click object.
 * @param reg        Register address.
 * @param data_buf   Output data buf
 * @param len        Number of the bytes to be read
 *
 * @description This function writes data to the desired register.
 */
void pressure10_generic_write ( pressure10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx      Click object.
 * @param reg          Register address.
 * @param data_buf  Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function reads data from the desired register.
 */
void pressure10_generic_read ( pressure10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Send command.
 *
 * @param cmd        Command
 */
void pressure10_send_cmd ( pressure10_t *ctx, uint8_t cmd );

/**
 * @brief Check communication.
 *
 * @param ctx      Click object.
 * 
 * @return  if device communication ok return [0], else return [1]
 */
uint8_t pressure10_check_communication ( pressure10_t *ctx );

/**
 * @brief Get status function.
 *
 * @param ctx      Click object.
 * @param status_obj  Status structure to be filled
 */
void pressure10_get_status( pressure10_t *ctx, pressure10_status_t *status_obj );

/**
 * @brief Get Temperature data in C.
 *
 * @param ctx      Click object.
 * @return temperature data
 */
float pressure10_get_temperature ( pressure10_t *ctx );

/**
 * @brief Get Pressure data in mBar.
 *
 * @param ctx      Click object.
 * @return pressure data
 */
float pressure10_get_pressure ( pressure10_t *ctx );

/**
 * @brief Set the configuration in the control registers
 *
 * @param ctx      Click object.
 * @param ctrl_reg Control register address
 * @param wr_data  Configuration data
 */
void pressure10_control_cfg ( pressure10_t *ctx, uint8_t ctrl_reg, uint8_t wr_data );

/**
 * @brief Get DRDY pin state
 *
 * @param ctx      Click object.
 * 
 * @return drdy pin state
 */
uint8_t pressure10_get_drdy_pin ( pressure10_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _PRESSURE10_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
