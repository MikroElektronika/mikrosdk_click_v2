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
 * \brief This file contains API for 3D Hall 7 Click driver.
 *
 * \addtogroup c3dhall7 3D Hall 7 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C3DHALL7_H
#define C3DHALL7_H

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

#define C3DHALL7_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.it2   = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.rst   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.it1   = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup communication   Select communication
 * \{
 */
#define C3DHALL7_MASTER_I2C 0
#define C3DHALL7_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code   Error Code
 * \{
 */
#define C3DHALL7_RETVAL  uint8_t

#define C3DHALL7_OK           0x00
#define C3DHALL7_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup register   Register
 * \{
 */
#define C3DHALL7_REG_DEVICE_ID                  0x00
#define C3DHALL7_REG_STATUS                     0x10
#define C3DHALL7_REG_ST_AXIS_X                  0x11
#define C3DHALL7_REG_ST_AXIS_Y                  0x12
#define C3DHALL7_REG_ST_AXIS_X_Y                0x13
#define C3DHALL7_REG_ST_AXIS_Z                  0x14
#define C3DHALL7_REG_ST_AXIS_X_Z                0x15
#define C3DHALL7_REG_ST_AXIS_Y_Z                0x16
#define C3DHALL7_REG_ST_AXIS_X_Y_Z              0x17
#define C3DHALL7_REG_STATUS_UP8                 0x18
#define C3DHALL7_REG_STUP8_AXIS_X               0x19
#define C3DHALL7_REG_STUP8_AXIS_Y               0x1A
#define C3DHALL7_REG_STUP8_AXIS_X_Y             0x1B
#define C3DHALL7_REG_ST8UP_AXIS_Z               0x1C
#define C3DHALL7_REG_STUP8_AXIS_X_Z             0x1D
#define C3DHALL7_REG_STUP8_AXIS_Y_Z             0x1E
#define C3DHALL7_REG_STUP8_AXIS_X_Y_Z           0x1F
#define C3DHALL7_REG_INTERRUPT_SETTINGS         0x20
#define C3DHALL7_REG_SENSOR_SETTINGS            0x21
#define C3DHALL7_REG_THRESHOLD_1_AXIS_X         0x22
#define C3DHALL7_REG_THRESHOLD_2_AXIS_X         0x23
#define C3DHALL7_REG_THRESHOLD_1_AXIS_Y         0x24
#define C3DHALL7_REG_THRESHOLD_2_AXIS_Y         0x25
#define C3DHALL7_REG_THRESHOLD_1_AXIS_Z         0x26
#define C3DHALL7_REG_THRESHOLD_2_AXIS_Z         0x27
#define C3DHALL7_REG_SOFTWARE_RESET             0x30
#define C3DHALL7_REG_I2C_DISABLE                0x31
/** \} */
 
/**
 * \defgroup interrupt_settings   Interrupt settings
 * \{
 */
#define C3DHALL7_INT_DRDY_ENBALE              0x0001
#define C3DHALL7_INT_DRDY_DISABLE             0x0000
#define C3DHALL7_INT_SW_X1_ENABLE             0x0002
#define C3DHALL7_INT_SW_X1_DISABLE            0x0000
#define C3DHALL7_INT_SW_X2_ENABLE             0x0004
#define C3DHALL7_INT_SW_X2_DISABLE            0x0000
#define C3DHALL7_INT_SW_Y1_ENABLE             0x0008
#define C3DHALL7_INT_SW_Y1_DISABLE            0x0000
#define C3DHALL7_INT_SW_Y2_ENABLE             0x0010
#define C3DHALL7_INT_SW_Y2_DISABLE            0x0000
#define C3DHALL7_INT_SW_Z1_ENABLE             0x0020
#define C3DHALL7_INT_SW_Z1_DISABLE            0x0000
#define C3DHALL7_INT_SW_Z2_ENABLE             0x0040
#define C3DHALL7_INT_SW_Z2_DISABLE            0x0000
#define C3DHALL7_INT_ERROR_X_Y_ENABLE         0x0080
#define C3DHALL7_INT_ERROR_X_Y_DISABLE        0x0000
#define C3DHALL7_INT_ERROR_ADC_ENABLE         0x0100
#define C3DHALL7_INT_ERROR_ADC_DISABLE        0x0000
#define C3DHALL7_INT_INTERRUPT_ENABLE         0x0200
#define C3DHALL7_INT_INTERRUPT_DISABLE        0x0000
#define C3DHALL7_INT_ODINT_ENABLE             0x0400
#define C3DHALL7_INT_ODINT_DISABLE            0x0000
/** \} */
 
/**
 * \defgroup sensor_control_settings   Sensor control settings
 * \{
 */
#define C3DHALL7_CTRL_MODE_POWER_DOWN         0x0000
#define C3DHALL7_CTRL_MODE_SINGLE             0x0001
#define C3DHALL7_CTRL_MODE_CONTINUOUS_0p25Hz  0x0002
#define C3DHALL7_CTRL_MODE_CONTINUOUS_0p5Hz   0x0004
#define C3DHALL7_CTRL_MODE_CONTINUOUS_1Hz     0x0006
#define C3DHALL7_CTRL_MODE_CONTINUOUS_10Hz    0x0008
#define C3DHALL7_CTRL_MODE_CONTINUOUS_20Hz    0x000A
#define C3DHALL7_CTRL_MODE_CONTINUOUS_50Hz    0x000C
#define C3DHALL7_CTRL_MODE_CONTINUOUS_100Hz   0x000E
#define C3DHALL7_CTRL_SDR_LOW_NOISE_DRIVE     0x0000
#define C3DHALL7_CTRL_SDR_LOW_POWER_DRIVE     0x0010
#define C3DHALL7_CTRL_SMR_HIGH_SENSITIVITY    0x0000
#define C3DHALL7_CTRL_SMR_WIDE_MEASUREMENT    0x0020
/** \} */
 
/**
 * \defgroup device_info Device Info
 * \{
 */
#define C3DHALL7_DEVICE_ID                      0xC0
#define C3DHALL7_COMPANY_ID                     0x48
/** \} */
 
/**
 * \defgroup device_slave_address   Device slave address
 * \{
 */
#define C3DHALL7_DEVICE_SLAVE_ADDR_VCC          0x0D
#define C3DHALL7_DEVICE_SLAVE_ADDR_GND          0x0C
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
typedef uint8_t  c3dhall7_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *c3dhall7_master_io_t )( struct c3dhall7_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct c3dhall7_s
{
    // Output pins 

    digital_out_t rst;
    digital_out_t cs;

    // Input pins 

    digital_in_t it2;
    digital_in_t it1;
    
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

    uint8_t slave_address;
    pin_name_t chip_select;
   c3dhall7_master_io_t  write_f;
   c3dhall7_master_io_t  read_f;
   c3dhall7_select_t master_sel;

} c3dhall7_t;

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

    pin_name_t it2;
    pin_name_t rst;
    pin_name_t it1;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;
    uint32_t spi_speed;
    uint8_t spi_mode;

    c3dhall7_select_t sel;
    spi_master_chip_select_polarity_t cs_polarity;

} c3dhall7_cfg_t;

typedef struct
{
    uint8_t data_overrun;
    uint8_t err_adc;
    uint8_t err_axis_xy;
    uint8_t sw_axis_z2;
    uint8_t sw_axis_z1;
    uint8_t sw_axis_y2;
    uint8_t sw_axis_y1;
    uint8_t sw_axis_x2;
    uint8_t sw_axis_x1;
    uint8_t drdy;

} c3dhall7_status_t;

typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;
    c3dhall7_status_t status;

} c3dhall7_axis_t;

typedef struct
{
    uint8_t company_id;
    uint8_t device_id;

}c3dhall7_dev_info_t;

typedef struct
{
    uint8_t interrupt_1;
    uint8_t interrupt_2;

} c3dhall7_int_state_t;

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
void c3dhall7_cfg_setup ( c3dhall7_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param c3dhall7 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
C3DHALL7_RETVAL c3dhall7_init ( c3dhall7_t *ctx, c3dhall7_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for 3D Hall 7 Click.
 */
void c3dhall7_default_cfg ( c3dhall7_t *ctx );

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
void c3dhall7_generic_write ( c3dhall7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function reads data from the desired register.
 */
void c3dhall7_generic_read ( c3dhall7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Hardware device reset.
 *
 * @param ctx      Click object.
 *
 * @description This function reads data from the desired register.
 */
void c3dhall7_device_reset ( c3dhall7_t *ctx );

/**
 * @brief Get Axis data function.
 *
 * @param ctx      Click object.
 * @param T_C3DHALL7_AXIS axis    structure of axis data 
 *
 * @description This function reads data from the desired register.
 */
void c3dhall7_get_axis_data( c3dhall7_t *ctx, c3dhall7_axis_t *axis);

/**
 * @brief Software device reset.
 *
 * @param ctx      Click object.
 *
 * @description This function reads data from the desired register.
 */
void c3dhall7_software_reset ( c3dhall7_t *ctx );

/**
 * @brief Configuration function (for ctrl register).
 *
 * @param ctx          Click object.
 * @param reg          Address where data be written.
 * @param data_in      Config data
 *
 * @description This function reads data from the desired register.
 */
void c3dhall7_configuration ( c3dhall7_t *ctx, uint8_t reg, uint16_t data_in);

/**
 * @brief Device info function.
 *
 * @param ctx                    Click object.
 * @param T_C3DHALL7_DEV_INFO    Tructure of device information 
 *
 * @description This function reads data from the desired register.
 */
void c3dhall7_device_info ( c3dhall7_t *ctx, c3dhall7_dev_info_t *info );

/**
 * @brief Measurement status function.
 *
 * @param ctx               Click object.
 * @param T_C3DHALL7_STATUS Structure of measurement status
 *
 * @description This function reads data from the desired register.
 */
void c3dhall7_get_status ( c3dhall7_t *ctx, c3dhall7_status_t  *status );

/**
 * @brief Interrupt state function
 *
 * @param ctx      Click object.
 * @param T_C3DHALL7_INT_STATE     structure of Interrupt pin state
 *
 * @description This function reads data from the desired register.
 */
void c3dhall7_get_interrupt_state ( c3dhall7_t *ctx, c3dhall7_int_state_t *state );


#ifdef __cplusplus
}
#endif
#endif  // _C3DHALL7_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
