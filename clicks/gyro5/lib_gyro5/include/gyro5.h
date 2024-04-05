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
 * \brief This file contains API for Gyro 5 Click driver.
 *
 * \addtogroup gyro5 Gyro 5 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef GYRO5_H
#define GYRO5_H

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

#define GYRO5_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.int_pin    = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define GYRO5_MASTER_I2C            0
#define GYRO5_MASTER_SPI            1
#define GYRO5_COM_I2C               0x01
#define GYRO5_COM_SPI               0x02
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define GYRO5_RETVAL  uint8_t

#define GYRO5_OK                    0x00
#define GYRO5_INIT_ERROR            0xFF
/** \} */

/**
 * \defgroup device_addresses Device addresses
 * \{
 */
#define GYRO5_I2C_DEV_ADR_GND      0x68
#define GYRO5_I2C_DEV_ADR_VCC      0x69
/** \} */

/**
 * \defgroup sleep_mode Sleep mode
 * \{
 */
#define GYRO5_SLEEP_DISABLE        0x00
#define GYRO5_SLEEP_ENABLE         0x01
/** \} */

/**
 * \defgroup interrupt_types Interrupt types
 * \{
 */
#define GYRO5_INT_DATA_RDY         0x00
#define GYRO5_INT_FSYNC            0x01
#define GYRO5_INT_FIFO_OVF         0x02
/** \} */

/**
 * \defgroup reg_address Register addresses
 * \{
 */
#define GYRO5_REG_XG_OFFS_TC_H     0x04
#define GYRO5_REG_XG_OFFS_TC_L     0x05
#define GYRO5_REG_YG_OFFS_TC_H     0x07
#define GYRO5_REG_YG_OFFS_TC_L     0x08
#define GYRO5_REG_ZG_OFFS_TC_H     0x0A
#define GYRO5_REG_ZG_OFFS_TC_L     0x0B
#define GYRO5_REG_XG_OFFS_USRH     0x13
#define GYRO5_REG_XG_OFFS_USRL     0x14
#define GYRO5_REG_YG_OFFS_USRH     0x15
#define GYRO5_REG_YG_OFFS_USRL     0x16
#define GYRO5_REG_ZG_OFFS_USRH     0x17
#define GYRO5_REG_G_OFFS_USRL      0x18
#define GYRO5_REG_SMPLRT_DIV       0x19
#define GYRO5_REG_CONFIG           0x1A
#define GYRO5_REG_GYRO_CONFIG      0x1B
#define GYRO5_REG_FIFO_EN          0x23
#define GYRO5_REG_INT_PIN_CFG      0x37
#define GYRO5_REG_INT_ENABLE       0x38
#define GYRO5_REG_INT_STATUS       0x3A
#define GYRO5_REG_TEMP_OUT_H       0x41
#define GYRO5_REG_TEMP_OUT_L       0x42
#define GYRO5_REG_GYRO_XOUT_H      0x43
#define GYRO5_REG_GYRO_XOUT_L      0x44
#define GYRO5_REG_GYRO_YOUT_H      0x45
#define GYRO5_REG_GYRO_YOUT_L      0x46
#define GYRO5_REG_GYRO_ZOUT_H      0x47
#define GYRO5_REG_GYRO_ZOUT_L      0x48
#define GYRO5_REG_USER_CTRL        0x6A
#define GYRO5_REG_PWR_MGMT_1       0x6B
#define GYRO5_REG_PWR_MGMT_2       0x6C
#define GYRO5_REG_FIFO_COUNTH      0x72
#define GYRO5_REG_FIFO_COUNTL      0x73
#define GYRO5_REG_FIFO_R_W         0x74
#define GYRO5_REG_WHO_AM_I         0x75
/** \} */

/**
 * \defgroup power_manage_1_cfg Power manage 1 configuration
 * \{
 */
#define GYRO5_CFG_PWR_MGMT_1_DEV_RST          0x80
#define GYRO5_CFG_PWR_MGMT_1_SLEEP            0x40
#define GYRO5_CFG_PWR_MGMT_1_TEMP_DIS         0x10
#define GYRO5_CFG_PWR_MGMT_1_CLKSEL_EXT_OSC   0x06
#define GYRO5_CFG_PWR_MGMT_1_CLKSEL_PLL       0x01
#define GYRO5_CFG_PWR_MGMT_1_CLKSEL_INT_OSC   0x00
/** \} */

/**
 * \defgroup power_manage_2_cfg Power manage 2 configuration
 * \{
 */
#define GYRO5_CFG_PWR_MGMT_2_STBY_XG          0x04
#define GYRO5_CFG_PWR_MGMT_2_STBY_YG          0x02
#define GYRO5_CFG_PWR_MGMT_2_STBY_ZG          0x01
#define GYRO5_CFG_PWR_MGMT_2_DIS_ALL          0x00
/** \} */

/**
 * \defgroup user_ctrl_cfg User control configuration
 * \{
 */
#define GYRO5_CFG_USER_CTRL_FIFO_EN          0x40
#define GYRO5_CFG_USER_CTRL_I2C_IF_DIS       0x10
#define GYRO5_CFG_USER_CTRL_FIFO_RESET       0x08
#define GYRO5_CFG_USER_CTRL_SIG_COND_RST     0x01
/** \} */

/**
 * \defgroup internal_clock_src Internal clock source
 * \{
 */
#define GYRO5_CFG_SMPLRT_DIV_DEF             0x00
/** \} */

/**
 * \defgroup register_cfg Register configuration
 * \{
 */
#define GYRO5_CFG_CONFIG_EXT_SYNC_SET_GYRO_ZOUT_L   0x20 
#define GYRO5_CFG_CONFIG_EXT_SYNC_SET_GYRO_YOUT_L   0x18 
#define GYRO5_CFG_CONFIG_EXT_SYNC_SET_GYRO_XOUT_L   0x10
#define GYRO5_CFG_CONFIG_EXT_SYNC_SET_TEMP_OUT_L    0x08
#define GYRO5_CFG_CONFIG_EXT_SYNC_SET_IN_DIS        0x00
#define GYRO5_CFG_CONFIG_DEF                        0x00
/** \} */

/**
 * \defgroup register_gyro_cfg Register gyroscope configuration
 * \{
 */
#define GYRO5_CFG_GYRO_CONFIG_FS_SEL_4000           0x18
#define GYRO5_CFG_GYRO_CONFIG_FS_SEL_2000           0x10
#define GYRO5_CFG_GYRO_CONFIG_FS_SEL_1000           0x08
#define GYRO5_CFG_GYRO_CONFIG_FS_SEL_500            0x00
/** \} */

/**
 * \defgroup fifo_en_cfg Fifo enable configuration
 * \{
 */
#define GYRO5_CFG_FIFO_EN_TEMP                      0x80
#define GYRO5_CFG_FIFO_EN_GYRO_X                    0x40
#define GYRO5_CFG_FIFO_EN_GYRO_Y                    0x20
#define GYRO5_CFG_FIFO_EN_GYRO_Z                    0x10
#define GYRO5_CFG_FIFO_EN_DIS_ALL                   0x00
/** \} */

/**
 * \defgroup int_cfg Interrupt configuration
 * \{
 */
#define GYRO5_CFG_INT_PIN_CFG_INT_LEVEL             0x80
#define GYRO5_CFG_INT_PIN_CFG_INT_OPEN              0x40
#define GYRO5_CFG_INT_PIN_CFG_LATCH_INT_EN          0x20
#define GYRO5_CFG_INT_PIN_CFG_INT_RD_CLEAR          0x10
#define GYRO5_CFG_INT_PIN_CFG_FSYNC_INT_LEVEL       0x08
#define GYRO5_CFG_INT_PIN_CFG_FSYNC_INT_MODE_EN     0x04
#define GYRO5_CFG_INT_PIN_CFG_DIS_ALL               0x00
/** \} */

/**
 * \defgroup int_en Interrupt enable
 * \{
 */
#define GYRO5_CFG_INT_ENABLE_FIFO_OFLOW_EN          0x10
#define GYRO5_CFG_INT_ENABLE_FSYNC_INT_EN           0x08
#define GYRO5_CFG_INT_ENABLE_DATA_RDY_EN            0x01
/** \} */

/**
 * \defgroup int_status Interrupt status
 * \{
 */
#define GYRO5_STATUS_INT_FIFO_OFLOW                 0x10
#define GYRO5_STATUS_INT_FSYNC                      0x08
#define GYRO5_STATUS_INT_DATA_RDY                   0x01
#define GYRO5_STATUS_INT_NOT_DATA_RDY               0x00
/** \} */

/**
 * \defgroup int_type Interrupt type
 * \{
 */
#define GYRO5_STATUS_INT_TYPES_SEL_FIFO_OFLOW       0x02
#define GYRO5_STATUS_INT_TYPES_INT_FSYNC            0x01
#define GYRO5_STATUS_INT_TYPES_INT_DATA_RDY         0x00
/** \} */

/**
 * \defgroup sleep_status Sleep status
 * \{
 */
#define GYRO5_SLEEP_STATUS_EN                       0x01
#define GYRO5_SLEEP_STATUS_DIS                      0x00
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
typedef uint8_t  gyro5_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *gyro5_master_io_t )( struct gyro5_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct gyro5_s
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
   gyro5_master_io_t  write_f;
   gyro5_master_io_t  read_f;
   gyro5_select_t master_sel;

} gyro5_t;

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

    pin_name_t int_pin;

    // static variable 

   uint32_t i2c_speed;
   uint8_t  i2c_address;

   uint32_t spi_speed;
   spi_master_mode_t  spi_mode;
   spi_master_chip_select_polarity_t cs_polarity;

   gyro5_select_t sel;

} gyro5_cfg_t;

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
void gyro5_cfg_setup ( gyro5_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
GYRO5_RETVAL gyro5_init ( gyro5_t *ctx, gyro5_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Gyro 5 click.
 */
void gyro5_default_cfg ( gyro5_t *ctx );

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
void gyro5_generic_write ( gyro5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void gyro5_generic_read ( gyro5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Getting INT pin state
 *
 * @param ctx      Click object.
 *
 * @returns 
 * - 0 : if INT pin state is LOW
 * - 1 : if INT pin state is HIGH
 *
 * @description This function returns INT pin state
 */
uint8_t gyro5_get_int ( gyro5_t *ctx );

/**
 * @brief Getting interrupt status
 *
 * @param ctx      Click object.
 * @param int_type uint8_t interrupt_type - interrupt type (data ready, fsync or fifo overflow)
 *
 * @returns 
 * - 0 : for successful operations
 * - 1 : for unsuccessful operations
 *
 * @description This function returns state of specified interrupt bit
 */
uint8_t gyro5_int_status ( gyro5_t *ctx, uint8_t int_type );

/**
 * @brief Getting temperature value
 *
 * @param ctx          Click object.
 * @param temperature  pointer to memory location where float temperature data be stored
 *
 * @description This function reads temperature measurement registers.
 * This function converts raw temperature data to get die temperature in [deg C]
 */
void gyro5_get_temperature ( gyro5_t *ctx, float *temperature );

/**
 * @brief Getting gyroscope axes values
 *
 * @param ctx          Click object.
 * @param x_axis       pointer to memory location where float x axis value be stored
 * @param y_axis       pointer to memory location where float y axis value be stored
 * @param z_axis       pointer to memory location where float z axis value be stored
 *
 * @description This function reads axes measurement registers.
 * This function converts raw axes measurement data to get gyroscope data in [deg/s]
 */
void gyro5_get_axes ( gyro5_t *ctx, float *x_axis, float *y_axis, float *z_axis );

/**
 * @brief Set sleep mode
 *
 * @param ctx          Click object.
 * @param en_sleep     
 * - 0 : disable sleep mode
 * - 1 : enable sleep mode
 *
 * @description This function set sleep mode
 */
void gyro5_sleep ( gyro5_t *ctx, uint8_t en_sleep );

#ifdef __cplusplus
}
#endif
#endif  // _GYRO5_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
