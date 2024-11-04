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
 * \brief This file contains API for 3D Hall 5 Click driver.
 *
 * \addtogroup c3dhall5 3D Hall 5 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C3DHALL5_H
#define C3DHALL5_H

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

#define C3DHALL5_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.css = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define C3DHALL5_MASTER_I2C 0
#define C3DHALL5_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C3DHALL5_RETVAL  uint8_t

#define C3DHALL5_OK           0x00
#define C3DHALL5_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup def_macro Default macro
 * \{
 */
#define C3DHALL5_I_AM 0x40;
/** \} */

/**
 * \defgroup axis Axis
 * \{
 */
#define C3DHALL5_AXIS_X 0x68
#define C3DHALL5_AXIS_Y 0x6A
#define C3DHALL5_AXIS_Z 0x6C
/** \} */

/**
 * \defgroup offset_axis Offset axis
 * \{
 */
#define C3DHALL5_OFFSET_AXIS_X 0x45
#define C3DHALL5_OFFSET_AXIS_Y 0x47
#define C3DHALL5_OFFSET_AXIS_Z 0x49
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define C3DHALL5_REG_OFFSET_X_LSB 0x45
#define C3DHALL5_REG_OFFSET_X_MSB 0x46
#define C3DHALL5_REG_OFFSET_Y_LSB 0x47
#define C3DHALL5_REG_OFFSET_Y_MSB 0x48
#define C3DHALL5_REG_OFFSET_Z_LSB 0x49
#define C3DHALL5_REG_OFFSET_Z_MSB 0x4A
#define C3DHALL5_REG_WHO_AM_I     0x4F
#define C3DHALL5_REG_CONFIG_A     0x60
#define C3DHALL5_REG_CONFIG_B     0x61
#define C3DHALL5_REG_CONFIG_C     0x62
#define C3DHALL5_REG_INT_CTRL     0x63
#define C3DHALL5_REG_INT_SOURCE   0x64
#define C3DHALL5_REG_INT_THS_LSB  0x65
#define C3DHALL5_REG_INT_THS_MSB  0x66
#define C3DHALL5_REG_STATUS       0x67
#define C3DHALL5_REG_X_AXIS_LSB   0x68
#define C3DHALL5_REG_X_AXIS_MSB   0x69
#define C3DHALL5_REG_Y_AXIS_LSB   0x6A
#define C3DHALL5_REG_Y_AXIS_MSB   0x6B
#define C3DHALL5_REG_Z_AXIS_LSB   0x6C
#define C3DHALL5_REG_Z_AXIS_MSB   0x6D
#define C3DHALL5_REG_TEMP_LSB     0x6E
#define C3DHALL5_REG_TEMP_MSB     0x6F
/** \} */

/**
 * \defgroup cfg_reg_a Config register A
 * \{
 */
#define C3DHALL5_CFG_A_COMP_TEMP_ENABLE     0x80
#define C3DHALL5_CFG_A_COMP_TEMP_DISABLE    0x00
#define C3DHALL5_CFG_A_REBOOT_MEM_CONTENT   0x40
#define C3DHALL5_CFG_A_NORMAL_MODE          0x00
#define C3DHALL5_CFG_A_SOFTRESET            0x20
#define C3DHALL5_CFG_A_HIGH_RESOLUTION_MODE 0x00
#define C3DHALL5_CFG_A_LOW_POWER_MODE       0x10
#define C3DHALL5_CFG_A_ODR_10Hz             0x00
#define C3DHALL5_CFG_A_ODR_20Hz             0x04
#define C3DHALL5_CFG_A_ODR_50Hz             0x08
#define C3DHALL5_CFG_A_ODR_100Hz            0x0C
#define C3DHALL5_CFG_A_MODE_CONTINUOUS      0x00
#define C3DHALL5_CFG_A_MODE_SINGLE          0x01
#define C3DHALL5_CFG_A_MODE_IDLE            0x02
/** \} */

/**
 * \defgroup cfg_reg_b Config register B
 * \{
 */
#define C3DHALL5_CFG_B_OFFSET_IN_SINGLE_MODE_ENABLE  0x10
#define C3DHALL5_CFG_B_OFFSET_IN_SINGLE_MODE_DISABLE 0x00
#define C3DHALL5_CFG_B_INT_ON_DATA_OFF               0x08
#define C3DHALL5_CFG_B_SET_PULSE_63_ODR              0x00
#define C3DHALL5_CFG_B_SET_PULSE_PD_CONDITION        0x04
#define C3DHALL5_CFG_B_OFFSET_ENABLE                 0x02
#define C3DHALL5_CFG_B_OFFSET_DISABLE                0x00
#define C3DHALL5_CFG_B_LPF_DISABLE_ODR_2             0x00
#define C3DHALL5_CFG_B_LPF_ENABLE_ODR_4              0x01
/** \} */

/**
 * \defgroup cfg_reg_c Config register C
 * \{
 */
#define C3DHALL5_CFG_C_INT_ON_PIN         0x40
#define C3DHALL5_CFG_C_INT_ON_PIN_DISABLE 0x00
#define C3DHALL5_CFG_C_I2C_DISABLE        0x20
#define C3DHALL5_CFG_C_BLE_ENABLE         0x08
#define C3DHALL5_CFG_C_SELF_TEST          0x02
#define C3DHALL5_CFG_C_DRDY_ON_PIN        0x01
/** \} */

/**
 * \defgroup int_ctrl INT control register
 * \{
 */
#define C3DHALL5_INT_CTRL_X_AXIS_ENABLE        0x80
#define C3DHALL5_INT_CTRL_Y_AXIS_ENABLE        0x40
#define C3DHALL5_INT_CTRL_Z_AXIS_ENABLE        0x20
#define C3DHALL5_INT_CTRL_IEA_0_SIGNALS_AN_INT 0x00
#define C3DHALL5_INT_CTRL_IEA_1_SIGNALS_AN_INT 0x04
#define C3DHALL5_INT_CTRL_IEL_INT_IS_PILSED    0x00
#define C3DHALL5_INT_CTRL_IEL_INT_IS_LATCHED   0x02
#define C3DHALL5_INT_CTRL_IEN_INT_ENABLE       0x01
#define C3DHALL5_INT_CTRL_IEN_INT_DISABLE      0x00
/** \} */

/**
 * \defgroup int_source INT source register
 * \{
 */
#define C3DHALL5_INT_SOURCE_POS_TH_X 0x80
#define C3DHALL5_INT_SOURCE_POS_TH_Y 0x40
#define C3DHALL5_INT_SOURCE_POS_TH_Z 0x20
#define C3DHALL5_INT_SOURCE_NEG_TH_X 0x10
#define C3DHALL5_INT_SOURCE_NEG_TH_Y 0x08
#define C3DHALL5_INT_SOURCE_NEG_TH_N 0x04
/** \} */

/**
 * \defgroup status Status register
 * \{
 */
#define C3DHALL5_STATUS_XYZ_DATA_OVERRUN  0x80
#define C3DHALL5_STATUS_Z_DATA_OVERRUN    0x40
#define C3DHALL5_STATUS_Y_DATA_OVERRUN    0x20
#define C3DHALL5_STATUS_X_DATA_OVERRUN    0x10
#define C3DHALL5_STATUS_XYZ_NEW_DATA      0x08
#define C3DHALL5_STATUS_Z_NEW_DATA        0x04
#define C3DHALL5_STATUS_Y_NEW_DATA        0x02
#define C3DHALL5_STATUS_X_NEW_DATA        0x01
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Communication type.
 */
typedef uint8_t  c3dhall5_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *c3dhall5_master_io_t )( struct c3dhall5_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct c3dhall5_s
{
    // Output pins 
    digital_out_t css;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

    uint8_t slave_address;
    pin_name_t chip_select;
    c3dhall5_master_io_t  write_f;
    c3dhall5_master_io_t  read_f;
    c3dhall5_select_t master_sel;

} c3dhall5_t;

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

    pin_name_t css;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;
    
    uint32_t spi_speed;
    spi_master_mode_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

   c3dhall5_select_t sel;

} c3dhall5_cfg_t;

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
void c3dhall5_cfg_setup ( c3dhall5_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param c3dhall5 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
C3DHALL5_RETVAL c3dhall5_init ( c3dhall5_t *ctx, c3dhall5_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for 3DHall5 Click.
 * @note
 *    Default configuration of the chip contains the settings :
 *      Config A:
 *         - C3DHALL5_CFG_A_COMP_TEMP_ENABLE
 *      Config C:
 *          - C3DHALL5_CFG_C_DRDY_ON_PIN
 *
 */
void c3dhall5_default_cfg ( c3dhall5_t *ctx );

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
void c3dhall5_generic_write ( c3dhall5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void c3dhall5_generic_read ( c3dhall5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Device ID.
 *
 * @param ctx      Click object.
 * @return Device ID ( C3DHALL5_I_AM )
 *
 * @description You can use this function as a check to communicate a Click with your MCU.
 */
uint8_t c3dhall5_get_device_id ( c3dhall5_t *ctx );

/**
 * @brief Temperature data
 *
 * @param ctx      Click object.
 * @return Temperature data in C
 *
 * @description Function for checking and reading temperature.
 */
float c3dhall5_get_temperature_data ( c3dhall5_t *ctx );

/**
 * @brief Interrupt state
 *
 * @param ctx      Click object.
 * @return Interrupt state on INT pin
 */
uint8_t c3dhall5_get_interrupt_state ( c3dhall5_t *ctx );

/**
 * @brief Set offest
 *
 * @param ctx              Click object.
 * @param offset_axis      The axis for which you set off
 * @param offset           Offset data to be set
 */
void c3dhall5_set_offset ( c3dhall5_t *ctx, uint8_t offset_axis, int16_t offset );

/**
 * @brief Axis data
 *
 * @param ctx       Click object.
 * @param axis      The axis to be read
 * @return Axis data
 */
int16_t c3dhall5_get_axis_data ( c3dhall5_t *ctx, uint8_t axis );

#ifdef __cplusplus
}
#endif
#endif  // _C3DHALL5_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
