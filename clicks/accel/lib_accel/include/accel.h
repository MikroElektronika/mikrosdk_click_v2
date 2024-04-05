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
 * \brief This file contains API for Accel Click driver.
 *
 * \addtogroup accel Accel Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ACCEL_H
#define ACCEL_H

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

#include "drv_digital_in.h"
#include "drv_i2c_master.h"
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

#define ACCEL_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define ACCEL_MASTER_I2C                    0
#define ACCEL_MASTER_SPI                    1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ACCEL_OK                            0
#define ACCEL_ERROR                        -1
/** \} */

/**
 * \defgroup slave_address Slave addresses 
 * \{
 */   
#define ACCEL_I2C_ADR_VCC                   0x1D
#define ACCEL_I2C_ADR_GND                   0x53
/** \} */

/**
 * \defgroup registers Registers 
 * \{
 */ 
#define ACCEL_REG_DEVID                     0x00
#define ACCEL_REG_THRESH_TAP                0x1D
#define ACCEL_REG_OFSX                      0x1E
#define ACCEL_REG_OFSY                      0x1F
#define ACCEL_REG_OFSZ                      0x20
#define ACCEL_REG_DUR                       0x21
#define ACCEL_REG_LATENT                    0x22
#define ACCEL_REG_WINDOW                    0x23
#define ACCEL_REG_THRESH_ACT                0x24
#define ACCEL_REG_THRESH_INACT              0x25
#define ACCEL_REG_TIME_INACT                0x26
#define ACCEL_REG_ACT_INACT_CTL             0x27
#define ACCEL_REG_THRESH_FF                 0x28
#define ACCEL_REG_TIME_FF                   0x29
#define ACCEL_REG_TAP_AXES                  0x2A
#define ACCEL_REG_ACT_TAP_STATUS            0x2B
#define ACCEL_REG_BW_RATE                   0x2C
#define ACCEL_REG_POWER_CTL                 0x2D
#define ACCEL_REG_INT_ENABLE                0x2E
#define ACCEL_REG_INT_MAP                   0x2F
#define ACCEL_REG_INT_SOURCE                0x30
#define ACCEL_REG_DATA_FORMAT               0x31
#define ACCEL_REG_DATA_X_LSB                0x32
#define ACCEL_REG_DATA_X_MSB                0x33
#define ACCEL_REG_DATA_Y_LSB                0x34
#define ACCEL_REG_DATA_Y_MSB                0x35
#define ACCEL_REG_DATA_Z_LSB                0x36
#define ACCEL_REG_DATA_Z_MSB                0x37
#define ACCEL_REG_FIFO_CTL                  0x38
#define ACCEL_REG_FIFO_STATUS               0x39
/** \} */

/**
 * \defgroup device_id Device ID 
 * \{
 */ 
#define ACCEL_DEVID                         0xE5
/** \} */

/**
 * \defgroup power_ctrl Power control 
 * \{
 */ 
#define ACCEL_POWER_CTL_LINK                0x20
#define ACCEL_POWER_CTL_AUTO_SLEEP          0x10
#define ACCEL_POWER_CTL_MEASURE             0x08
#define ACCEL_POWER_CTL_SLEEP               0x04
#define ACCEL_POWER_CTL_WAKEUP_8            0x03
#define ACCEL_POWER_CTL_WAKEUP_4            0x02
#define ACCEL_POWER_CTL_WAKEUP_2            0x01
#define ACCEL_POWER_CTL_WAKEUP_1            0x00
/** \} */

/**
 * \defgroup data_format Data format 
 * \{
 */ 
#define ACCEL_DATA_FORMAT_SELF_TEST         0x80
#define ACCEL_DATA_FORMAT_SPI               0x40
#define ACCEL_DATA_FORMAT_INT_INVERT        0x20
#define ACCEL_DATA_FORMAT_FULL_RES          0x08
#define ACCEL_DATA_FORMAT_JUSTIFY           0x04
#define ACCEL_DATA_FORMAT_RANGE_16          0x03
#define ACCEL_DATA_FORMAT_RANGE_8           0x02
#define ACCEL_DATA_FORMAT_RANGE_4           0x01
#define ACCEL_DATA_FORMAT_RANGE_2           0x00
/** \} */

/**
 * \defgroup bandwidth Bandwidth register 
 * \{
 */ 
#define ACCEL_BW_RATE_LOW_POWER             0x10
#define ACCEL_BW_RATE_1600                  0x0F
#define ACCEL_BW_RATE_800                   0x0E
#define ACCEL_BW_RATE_400                   0x0D
#define ACCEL_BW_RATE_200                   0x0C
#define ACCEL_BW_RATE_100                   0x0B
#define ACCEL_BW_RATE_50                    0x0A
#define ACCEL_BW_RATE_25                    0x09
#define ACCEL_BW_RATE_12_5                  0x08
#define ACCEL_BW_RATE_6_25                  0x07
#define ACCEL_BW_RATE_3_13                  0x06
#define ACCEL_BW_RATE_1_56                  0x05
#define ACCEL_BW_RATE_0_78                  0x04
#define ACCEL_BW_RATE_0_39                  0x03
#define ACCEL_BW_RATE_0_2                   0x02
#define ACCEL_BW_RATE_0_1                   0x01
#define ACCEL_BW_RATE_0_05                  0x00
/** \} */

/**
 * \defgroup fifo FIFO control
 * \{
 */ 
#define ACCEL_FIFO_CTL_FIFO_MODE_BYPASS     0x00
#define ACCEL_FIFO_CTL_FIFO_MODE_ENABLE     0x40
#define ACCEL_FIFO_CTL_FIFO_MODE_STREAM     0x80
#define ACCEL_FIFO_CTL_FIFO_MODE_TRIGGER    0x60
#define ACCEL_FIFO_CTL_TRIGGER_INT2         0x20
/** \} */

/**
 * \defgroup resolution Data resolution
 * \{
 */ 
#define ACCEL_DATA_RES_LSB_PER_G            256.0f
/** \} */

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b accel_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ACCEL_SET_DATA_SAMPLE_EDGE          SET_SPI_DATA_SAMPLE_EDGE
#define ACCEL_SET_DATA_SAMPLE_MIDDLE        SET_SPI_DATA_SAMPLE_MIDDLE


/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Communication type.
 */
typedef uint8_t  accel_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *accel_master_io_t )( struct accel_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct accel_s
{
    digital_out_t cs;

    // Input pins 
    digital_in_t int_pin;
    
    // Modules 
    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 
    uint8_t slave_address;
    pin_name_t chip_select;
    accel_master_io_t  write_f;
    accel_master_io_t  read_f;
    accel_select_t master_sel;

} accel_t;

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
    pin_name_t int_pin;

    // static variable 
    uint32_t i2c_speed;
    uint8_t  i2c_address;
    uint32_t spi_speed;
    spi_master_mode_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

    accel_select_t sel;

} accel_cfg_t;

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
void accel_cfg_setup ( accel_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param accel Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
err_t accel_init ( accel_t *ctx, accel_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Accel click.
 * <pre>
 *   ACCEL_REG_POWER_CTL
 * -------------------------------------------
 *   ACCEL_POWER_CTL_WAKEUP_1
 * </pre>
 * 
 * <pre>
 *   ACCEL_REG_DATA_FORMAT
 * -------------------------------------------
 *   ACCEL_DATA_FORMAT_FULL_RES
 *   ACCEL_DATA_FORMAT_RANGE_16
 * </pre>
 * 
 * <pre>
 *   ACCEL_REG_BW_RATE
 * -------------------------------------------
 *   ACCEL_BW_RATE_RATE_50
 * </pre>
 *
 * <pre>
 *   ACCEL_REG_FIFO_CTL
 * -------------------------------------------
 *   ACCEL_FIFO_CTL_FIFO_MODE_STREAM
 * </pre>
 *
 * <pre>
 *   ACCEL_REG_POWER_CTL
 * -------------------------------------------
 *   ACCEL_POWER_CTL_MEASURE
 * </pre>
 */
void accel_default_cfg ( accel_t *ctx );

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
void accel_generic_write ( accel_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void accel_generic_read ( accel_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Function raw read X axis
 *
 * @param ctx      Click object.
 *
 * @return         Value X axis.
 *
 * @description Function reads X axis value from Accel.
 */
int16_t accel_read_x_axis ( accel_t *ctx );

/**
 * @brief Function raw read Y axis
 *
 * @param ctx      Click object.
 * 
 * @return         Value Y axis.
 *
 * @description Function reads Y axis value from Accel.
 */
int16_t accel_read_y_axis ( accel_t *ctx );

/**
 * @brief Function raw read Z axis
 *
 * @param ctx      Click object.
 * 
 * @return         Value Z axis.
 *
 * @description Function reads Z axis value from Accel.
 */
int16_t accel_read_z_axis ( accel_t *ctx );

/**
 * @brief INT Pin Get function.
 *
 * @param ctx  Click object.
 *
 * @returns Pin state [bool].
 *
 * @description This function returns true if the high voltage level detected on the INT pin,
 * or returns false if the low voltage level detected on the INT pin.
 */
uint8_t accel_check_int_pin ( accel_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _ACCEL_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
