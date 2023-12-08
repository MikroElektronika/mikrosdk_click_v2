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
 * \brief This file contains API for Compass 4 Click driver.
 *
 * \addtogroup compass4 Compass 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef COMPASS4_H
#define COMPASS4_H

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

#define COMPASS4_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define COMPASS4_MASTER_I2C 0
#define COMPASS4_MASTER_SPI 1
/** \} */
 
/**
 * \defgroup error_code Error Code
 * \{
 */
#define COMPASS4_RETVAL  uint8_t

#define COMPASS4_OK           0x00
#define COMPASS4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers  Registers
 * \{
 */
#define COMPASS4_REG_COMPANY_ID            0x00 // Read only
#define COMPASS4_REG_DEVICE_ID             0x01 // Read only 
#define COMPASS4_REG_INFO                  0x03 // Read only
#define COMPASS4_REG_STATUS_1              0x10 // Read only
#define COMPASS4_REG_X_AXIS_LSB            0x11 // Read only
#define COMPASS4_REG_X_AXIS_MSB            0x12 // Read only
#define COMPASS4_REG_Y_AXIS_LSB            0x13 // Read only
#define COMPASS4_REG_Y_AXIS_MSB            0x14 // Read only
#define COMPASS4_REG_Z_AXIS_LSB            0x15 // Read only
#define COMPASS4_REG_Z_AXIS_MSB            0x16 // Read only
#define COMPASS4_REG_TMPS                  0x17 // Read only
#define COMPASS4_REG_STATUS_2              0x18 // Read only
#define COMPASS4_REG_CONTROL_1             0x30 // Read and write
#define COMPASS4_REG_CONTROL_2             0x31 // Read and write
#define COMPASS4_REG_CONTROL_3             0x32 // Read and write
#define COMPASS4_REG_TS_1                  0x33 // Read and write
#define COMPASS4_REG_TS_2                  0x34 // Read and write
#define COMPASS4_REG_TS_3                  0x35 // Read and write
#define COMPASS4_REG_I2C_DISABLE           0x36 // Read and write
#define COMPASS4_REG_TS_4                  0x37 // Read and write
#define COMPASS4_REG_ASAX                  0x60 // Read only
#define COMPASS4_REG_ASAY                  0x61 // Read only
#define COMPASS4_REG_ASAZ                  0x62 // Read only
#define COMPASS4_REG_TPH_1                 0xC0 // Read and write
#define COMPASS4_REG_TPH_2                 0xC1 // Read and write
#define COMPASS4_REG_RR                    0xC2 // Read and write
#define COMPASS4_REG_SYT                   0xC3 // Read and write
#define COMPASS4_REG_DT                    0xC4 // Read and write
/** \} */
 
/**
 * \defgroup default_value   Default value
 * \{
 */
#define COMPASS4_DEF_COMPANY_ID            0x48
#define COMPASS4_DEF_DEVICE_ID             0x10
/** \} */
 
/**
 * \defgroup contol_1_register  Control 1 register
 * \{
 */
#define COMPASS4_CTRL1_WM_STEP_1           0x00
#define COMPASS4_CTRL1_WM_STEPS_2          0x01
#define COMPASS4_CTRL1_WM_STEPS_3          0x02
#define COMPASS4_CTRL1_WM_STEPS_4          0x03
#define COMPASS4_CTRL1_WM_STEPS_5          0x04
#define COMPASS4_CTRL1_WM_STEPS_6          0x05
#define COMPASS4_CTRL1_WM_STEPS_7          0x06
#define COMPASS4_CTRL1_WM_STEPS_8          0x07
#define COMPASS4_CTRL1_WM_STEPS_9          0x08
#define COMPASS4_CTRL1_WM_STEPS_10         0x09
#define COMPASS4_CTRL1_WM_STEPS_11         0x0A
#define COMPASS4_CTRL1_WM_STEPS_12         0x0B
#define COMPASS4_CTRL1_WM_STEPS_13         0x0C
#define COMPASS4_CTRL1_WM_STEPS_14         0x0D
#define COMPASS4_CTRL1_WM_STEPS_15         0x0E
#define COMPASS4_CTRL1_WM_STEPS_16         0x0F
#define COMPASS4_CTRL1_WM_STEPS_17         0x10
#define COMPASS4_CTRL1_WM_STEPS_18         0x11
#define COMPASS4_CTRL1_WM_STEPS_19         0x12
#define COMPASS4_CTRL1_WM_STEPS_20         0x13
#define COMPASS4_CTRL1_WM_STEPS_21         0x14
#define COMPASS4_CTRL1_WM_STEPS_22         0x15
#define COMPASS4_CTRL1_WM_STEPS_23         0x16
#define COMPASS4_CTRL1_WM_STEPS_24         0x17
#define COMPASS4_CTRL1_WM_STEPS_25         0x18
#define COMPASS4_CTRL1_WM_STEPS_26         0x19
#define COMPASS4_CTRL1_WM_STEPS_27         0x1A
#define COMPASS4_CTRL1_WM_STEPS_28         0x1B
#define COMPASS4_CTRL1_WM_STEPS_29         0x1C
#define COMPASS4_CTRL1_WM_STEPS_30         0x1D
#define COMPASS4_CTRL1_WM_STEPS_31         0x1E
#define COMPASS4_CTRL1_WM_STEPS_32         0x1F
#define COMPASS4_CTRL1_NOISE_DISABLE       0x00
#define COMPASS4_CTRL1_NOISE_ENABLE        0x20
/** \} */
 
/**
 * \defgroup contol_2_register  Control 2 register
 * \{
 */
#define COMPASS4_CTRL2_MODE_POWER_DOWN     0x00
#define COMPASS4_CTRL2_MODE_SINGLE         0x01
#define COMPASS4_CTRL2_MODE_CONT_1         0x02
#define COMPASS4_CTRL2_MODE_CONT_2         0x04
#define COMPASS4_CTRL2_MODE_CONT_3         0x06
#define COMPASS4_CTRL2_MODE_CONT_4         0x08
#define COMPASS4_CTRL2_MODE_CONT_5         0x0A
#define COMPASS4_CTRL2_MODE_CONT_6         0x0C
#define COMPASS4_CTRL2_MODE_SELF_TEST      0x10
#define COMPASS4_CTRL2_SDR_LOW_POWER       0x00
#define COMPASS4_CTRL2_SDR_LOW_NOISE       0x40
#define COMPASS4_CTRL2_FIFO_ENABLE         0x80
#define COMPASS4_CTRL2_FIFO_DISABLE        0x00
/** \} */
 
/**
 * \defgroup contol_3_register  Control 3 register
 * \{
 */
#define COMPASS4_CTRL3_SOFT_RESET          0x01
/** \} */
 
/**
 * \defgroup device_slave_address  Device Slave address
 * \{
 */
#define COMPASS4_SLAVE_ADDRESS_GND_GND     0x0C
#define COMPASS4_SLAVE_ADDRESS_GND_VCC     0x0D
#define COMPASS4_SLAVE_ADDRESS_VCC_GND     0x0E
#define COMPASS4_SLAVE_ADDRESS_VCC_VCC     0x0F
/** \} */
 
/**
 * \defgroup function_get_data  Function get data
 * \{
 */
#define COMPASS4_GET_STATUS_1              0x01
#define COMPASS4_GET_STATUS_2              0x02
/** \} */
 
/**
 * \defgroup axis_data  Axis data
 * \{
 */
#define COMPASS4_X_AXIS_DATA               0x11
#define COMPASS4_Y_AXIS_DATA               0x13
#define COMPASS4_Z_AXIS_DATA               0x15
/** \} */
 
/**
 * \defgroup flux_const  Flux const
 * \{
 */
#define FLUX_CONSTANT 0.15
/** \} */
 

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

typedef struct 
{
    int16_t x;
    int16_t y;
    int16_t z;

} compass4_axis_t;

typedef struct 
{
    float x;
    float y;
    float z;

} compass4_flux_t;

/**
 * @brief Communication type.
 */
typedef uint8_t  compass4_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *compass4_master_io_t )( struct compass4_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct compass4_s
{
   // Output pins 
   digital_out_t cs;

    digital_out_t rst;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

    uint8_t slave_address;
    pin_name_t chip_select;
    compass4_master_io_t  write_f;
    compass4_master_io_t  read_f;
    compass4_select_t master_sel;

} compass4_t;

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

    pin_name_t rst;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t  i2c_address;

    uint32_t spi_speed;
    spi_master_mode_t  spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

    compass4_select_t sel;

} compass4_cfg_t;

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
void compass4_cfg_setup ( compass4_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param compass4 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
COMPASS4_RETVAL compass4_init ( compass4_t *ctx, compass4_cfg_t *cfg );

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
void compass4_generic_write ( compass4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void compass4_generic_read ( compass4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Hardware reset function
 *
 * @param ctx      Click object.
 * 
 * @description Used this function for start hardware reset module
 */
void compass4_hardware_reset ( compass4_t *ctx );

/**
 * @brief Sets RST pin state
 *
 * @param ctx      Click object.
 * @param state New pin state
 * @description Used this function for set RST pin state
 */
void compass4_set_rst_pin_state ( compass4_t *ctx, uint8_t state );

/**
 * @brief Software reset function
 *
 * @param ctx      Click object.
 * 
 * @description Used this function for start software reset module
 */
void compass4_software_reset ( compass4_t *ctx );

/**
 * @brief Configuration function
 *
 * @param ctx      Click object.
 * @param cfg1 Config data for configuration register 1
 * @param cfg2 Config data for configuration register 2
 *
 * @description Used this function for configuration module
 */
void compass4_configuration ( compass4_t *ctx, uint8_t cfg1, uint8_t cfg2 );

/**
 * @brief Get status 
 *
 * @param ctx      Click object.
 * @param cfg1 Config data for configuration register 1
 * @param cfg2 Config data for configuration register 2
 *
 * @description Used this function for configuration module
 */
uint8_t compass4_get_status( compass4_t *ctx, uint8_t status );

/**
 * @brief Check device function
 *
 * @param ctx      Click object.
 * 
 * @return device state ( 1 - Device ERROR // 0 - Device OK )
 *
 * @description This function reads device and company id, 
 *              because tests communication
 */
uint8_t compass4_check_device ( compass4_t *ctx );

/**
 * @brief Gets INT pin state (DRDY pin)
 *
 * @param ctx      Click object.
 * 
 * @return INT pin state 
 *
 * @description Used this function for getting current interrupt pin state
 */
uint8_t compass4_get_interrupt ( compass4_t *ctx );

/**
 * @brief Gets X\Y\Z Axis value
 *
 * @param ctx      Click object.
 * @param axis Raw axis data object
 * @return device state ( 1 - Device ERROR // 0 - Device OK )
 *
 * @description Used this function for reads current axis data
 */
uint8_t compass4_get_axis ( compass4_t *ctx, compass4_axis_t *axis );

/**
 * @brief Gets single axis value
 *
 * @param ctx      Click object.
 * @param axis_reg Axis register ( LSB )
 * @param axis_data axis data that reads from the register
 * @return device state ( 1 - Device ERROR // 0 - Device OK )
 *
 * @description Used this function for reads current single axis data
 */
uint8_t compass4_get_single_axis ( compass4_t *ctx, uint8_t axis_reg, int16_t *axis_data );

/**
 * @brief Gets magnetic flux of X\Y\Z axis value
 *
 * @param ctx      Click object.
 * @param flux   Magnetic flux of axis data
 * @return device state ( 1 - Device ERROR // 0 - Device OK )
 *
 * @description Used this function for reads magnetic flux of axis data
 */
uint8_t compass4_get_magnetic_flux ( compass4_t *ctx, compass4_flux_t *flux );

/**
 * @brief Gets single axis flux value
 *
 * @param ctx      Click object.
 * @param axis Axis register ( LSB )
 * @param flux_data Flux data that reads and calculate
 * @return device state ( 1 - Device ERROR // 0 - Device OK )
 *
 * @description Used this function for reads current single flux or axis data
 */
uint8_t compass4_get_single_magnetic_flux ( compass4_t *ctx, uint8_t axis, float *flux_data );

#ifdef __cplusplus
}
#endif
#endif  // _COMPASS4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
