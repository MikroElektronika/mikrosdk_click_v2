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
 * \brief This file contains API for Geomagnetic Click driver.
 *
 * \addtogroup geomagnetic Geomagnetic Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef GEOMAGNETIC_H
#define GEOMAGNETIC_H

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

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define GEOMAGNETIC_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define GEOMAGNETIC_MASTER_I2C 0
#define GEOMAGNETIC_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define GEOMAGNETIC_RETVAL  uint8_t

#define GEOMAGNETIC_OK           0x00
#define GEOMAGNETIC_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup geomagnetic_macros Geomagnetic Macros
 * \{
 */
#define GEOMAG_DUMMY                                          0x00 
#define GEOMAG_SPI_INTERFACE                                  0x00 
#define GEOMAG_I2C_INTERFACE                                  0x01 
#define GEOMAG_READ_CMD                                       0x80 
#define GEOMAG_DEV_ADDR                                       0x10 
#define GEOMAG_ID_REG                                         0x40 
#define GEOMAG_RESERVED1_REG                                  0x41 
#define GEOMAG_DATAX_LSB_REG                                  0x42 
#define GEOMAG_DATAX_MSB_REG                                  0x43 
#define GEOMAG_DATAY_LSB_REG                                  0x44 
#define GEOMAG_DATAY_MSB_REG                                  0x45 
#define GEOMAG_DATAZ_LSB_REG                                  0x46 
#define GEOMAG_DATAZ_MSB_REG                                  0x47 
#define GEOMAG_RHALL_LSB_REG                                  0x48 
#define GEOMAG_RHALL_MSB_REG                                  0x49 
#define GEOMAG_INTERRUPT_STATUS_REG                           0x4A 
#define GEOMAG_POWER_AND_RESET_CON_REG                        0x4B 
#define GEOMAG_DATARATE_AND_OPMODE_CON_REG                    0x4C 
#define GEOMAG_INTERR_AND_AXIS_EN_REG                         0x4D 
#define GEOMAG_INTERR_AND_CHANNEL_EN_REG                      0x4E 
#define GEOMAG_LOW_THRESHOLD_REG                              0x4F 
#define GEOMAG_HIGH_THRESHOLD_REG                             0x50 
#define GEOMAG_REPETITION_XY_CON_REG                          0x51 
#define GEOMAG_REPETITION_Z_CON_REG                           0x52 
#define GEOMAG_RESERVED2_REG                                  0x53 
#define GEOMAG_RESERVED3_REG                                  0x54 
#define GEOMAG_RESERVED4_REG                                  0x55 
#define GEOMAG_RESERVED5_REG                                  0x56 
#define GEOMAG_RESERVED6_REG                                  0x57 
#define GEOMAG_RESERVED7_REG                                  0x58 
#define GEOMAG_RESERVED8_REG                                  0x59 
#define GEOMAG_RESERVED9_REG                                  0x5A 
#define GEOMAG_RESERVED10_REG                                 0x5B 
#define GEOMAG_RESERVED11_REG                                 0x5C 
#define GEOMAG_RESERVED12_REG                                 0x5D 
#define GEOMAG_RESERVED13_REG                                 0x5E 
#define GEOMAG_RESERVED14_REG                                 0x5F 
#define GEOMAG_RESERVED15_REG                                 0x60 
#define GEOMAG_RESERVED16_REG                                 0x61 
#define GEOMAG_RESERVED17_REG                                 0x62 
#define GEOMAG_RESERVED18_REG                                 0x63 
#define GEOMAG_RESERVED19_REG                                 0x64 
#define GEOMAG_RESERVED20_REG                                 0x65 
#define GEOMAG_RESERVED21_REG                                 0x66 
#define GEOMAG_RESERVED22_REG                                 0x67 
#define GEOMAG_RESERVED23_REG                                 0x68 
#define GEOMAG_RESERVED24_REG                                 0x69 
#define GEOMAG_RESERVED25_REG                                 0x6A 
#define GEOMAG_RESERVED26_REG                                 0x6B 
#define GEOMAG_RESERVED27_REG                                 0x6C 
#define GEOMAG_RESERVED28_REG                                 0x6D 
#define GEOMAG_RESERVED29_REG                                 0x6E 
#define GEOMAG_RESERVED30_REG                                 0x6F 
#define GEOMAG_RESERVED31_REG                                 0x70 
#define GEOMAG_RESERVED32_REG                                 0x71 
#define GEOMAG_OK                                             0x00 
#define GEOMAG_ADDR_ERR                                       0x01 
#define GEOMAG_INTERRUPT_OCCURED                              0x02 
#define GEOMAG_NBYTES_ERR                                     0x03 
#define GEOMAG_DATA_READY                                     0x01 
#define GEOMAG_DATA_NOT_READY                                 0x00 
#define GEOMAG_SUSPEND_MODE_SPI4_EN                           0x00 
#define GEOMAG_SLEEP_MODE                                     0x01 
#define GEOMAG_SOFT_RESET_EN                                  0x82 
#define GEOMAG_SPI3_EN                                        0x04 
#define GEOMAG_NORMAL_OPMODE_DR_10HZ                          0x00 
#define GEOMAG_FORCED_OPMODE                                  0x02 
#define GEOMAG_SLEEP_OPMODE                                   0x06 
#define GEOMAG_DR_2HZ                                         0x08 
#define GEOMAG_DR_6HZ                                         0x10 
#define GEOMAG_DR_8HZ                                         0x18 
#define GEOMAG_DR_15HZ                                        0x20 
#define GEOMAG_DR_20HZ                                        0x28 
#define GEOMAG_DR_25HZ                                        0x30 
#define GEOMAG_DR_30HZ                                        0x38 
#define GEOMAG_INTERR_DISABLED_THRESHOLDS_ENABLED             0x00 
#define GEOMAG_LOWTHRESHOLD_X_DISABLED                        0x01 
#define GEOMAG_LOWTHRESHOLD_Y_DISABLED                        0x02 
#define GEOMAG_LOWTHRESHOLD_Z_DISABLED                        0x04 
#define GEOMAG_HIGHTHRESHOLD_X_DISABLED                       0x08 
#define GEOMAG_HIGHTHRESHOLD_Y_DISABLED                       0x10 
#define GEOMAG_HIGHTHRESHOLD_Z_DISABLED                       0x20 
#define GEOMAG_OVERFLOW_PIN_IND_EN                            0x40 
#define GEOMAG_DATAOVERRUN_IND_EN                             0x80 
#define GEOMAG_CHANNELS_ENABLED_INTERR_DATAREADY_ACTIVE_LOW   0x00 
#define GEOMAG_INTERR_PIN_ACTIVE_HIGH                         0x01 
#define GEOMAG_INTERR_LATCHED                                 0x02 
#define GEOMAG_DATAREADY_ACTIVE_HIGH                          0x04 
#define GEOMAG_CHANNEL_X_DISABLED                             0x08 
#define GEOMAG_CHANNEL_Y_DISABLED                             0x10 
#define GEOMAG_CHANNEL_Z_DISABLED                             0x20 
#define GEOMAG_INTERR_PIN_EN                                  0x40 
#define GEOMAG_DATAREADY_PIN_EN                               0x80 
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
typedef uint8_t  geomagnetic_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *geomagnetic_master_io_t )( struct geomagnetic_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief GeoMagnetic axis structure.
 */
typedef struct 
{
    int16_t x_axis;
    int16_t y_axis;
    int16_t z_axis;

} geomagnetic_axis_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct geomagnetic_s
{
    // Output pins 
   
    digital_out_t cs;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

    uint8_t slave_address;
    pin_name_t chip_select;
    geomagnetic_master_io_t  write_f;
    geomagnetic_master_io_t  read_f;
    geomagnetic_select_t master_sel;

} geomagnetic_t;

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
    spi_master_mode_t  spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

   geomagnetic_select_t sel;

} geomagnetic_cfg_t;

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
void geomagnetic_cfg_setup ( geomagnetic_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
GEOMAGNETIC_RETVAL geomagnetic_init ( geomagnetic_t *ctx, geomagnetic_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for geomagnetic click.
 */
void geomagnetic_default_cfg ( geomagnetic_t *ctx );

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
void geomagnetic_generic_write ( geomagnetic_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void geomagnetic_generic_read ( geomagnetic_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Write byte function.
 *
 * @param ctx           Click object.
 * @param input_data    Input data variable.
 * @param address       Address variable.
 *
 * @description This function writes one byte of data to the specified address.
 */
GEOMAGNETIC_RETVAL geomagnetic_write_byte ( geomagnetic_t *ctx, uint8_t input_data, uint8_t address );

/**
 * @brief Read data function.
 *
 * @param ctx           Click object.
 * @param out_buf       Output buffer.
 * @param address       Address variable.
 * @param len           Size of the output buffer.
 *
 * @description This function reads n bytes of data from the specified address.
 */
GEOMAGNETIC_RETVAL geomagnetic_read_data ( geomagnetic_t *ctx, uint8_t *out_buf, uint8_t address, uint8_t len );

/**
 * @brief Check ready function.
 *
 * @param ctx           Click object.
 * 
 * @description This function gives feedback on whether the device is ready to measure or not.
 */
uint8_t geomagnetic_check_ready ( geomagnetic_t *ctx );

/**
 * @brief Read axis data function.
 *
 * @param ctx                Click object.
 * @param geomag_axis        Axis structures pointer.
 * @param resolution_hall    Hall effect digital resolution value.
 *
 * @description This function sets the x/y/z axis and hall resolution value.
 */
void geomagnetic_read_axis_data ( geomagnetic_t *ctx, geomagnetic_axis_t 
*geomag_axis, uint16_t *resolution_hall );

/**
 * @brief Check interrupt function.
 *
 * @param ctx    Click object.
 *
 * @description This function returns 1/0 depeinding on the input from the INT pin.
 */
GEOMAGNETIC_RETVAL geomagnetic_check_interrupt ( geomagnetic_t *ctx );

/**
 * @brief Get interrupt function.
 *
 * @param ctx    Click object.
 *
 * @description This function returns the input value from the INT pin.
 */
uint8_t get_interrupt ( geomagnetic_t *ctx );

/**
 * @brief Software reset function.
 *
 * @param ctx    Click object.
 *
 * @description This function resets the click module.
 */
void geomagnetic_software_reset ( geomagnetic_t *ctx );

/**
 * @brief Power ON reset function.
 *
 * @param ctx    Click object.
 *
 * @description This function configures some click module registers after the device has
 *              been reset.
 */
void geomagnetic_power_on_reset ( geomagnetic_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _GEOMAGNETIC_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
