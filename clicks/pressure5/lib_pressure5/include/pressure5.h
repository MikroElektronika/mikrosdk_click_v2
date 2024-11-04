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
 * \brief This file contains API for Pressure 5 Click driver.
 *
 * \addtogroup pressure5 Pressure 5 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PRESSURE5_H
#define PRESSURE5_H

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

#define PRESSURE5_MAP_MIKROBUS( cfg, mikrobus ) \
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
#define PRESSURE5_MASTER_I2C 0
#define PRESSURE5_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PRESSURE5_RETVAL  uint8_t

#define PRESSURE5_OK                                  0x00
#define PRESSURE5_INIT_ERROR                          0xFF
/** \} */

/**
 * \defgroup general_registers General Registers
 * \{
 */
#define PRESSURE5_REG_DEVICE_ID                       0x00
#define PRESSURE5_REG_ERROR                           0x02
#define PRESSURE5_REG_PRESSURE_DATA_0                 0x04
#define PRESSURE5_REG_PRESSURE_DATA_1                 0x05
#define PRESSURE5_REG_PRESSURE_DATA_2                 0x06
#define PRESSURE5_REG_TEMPERATURE_DATA_0              0x07
#define PRESSURE5_REG_TEMPERATURE_DATA_1              0x08
#define PRESSURE5_REG_TEMPERATURE_DATA_2              0x09
#define PRESSURE5_REG_SENSOR_TIME_0                   0x0C
#define PRESSURE5_REG_SENSOR_TIME_1                   0x0D
#define PRESSURE5_REG_SENSOR_TIME_2                   0x0E
#define PRESSURE5_REG_EVENT                           0x10
#define PRESSURE5_REG_INT_STATUS                      0x11
#define PRESSURE5_REG_FIFO_LENGTH                     0x13
#define PRESSURE5_REG_FIFO_DATA                       0x14
#define PRESSURE5_REG_FIFO_WATERMARK_0                0x15
#define PRESSURE5_REG_FIFO_WATERMARK_1                0x16
#define PRESSURE5_REG_FIFO_CONFIG_1                   0x17
#define PRESSURE5_REG_FIFO_CONFIG_2                   0x18
#define PRESSURE5_REG_INT_CTRL                        0x19
#define PRESSURE5_REG_IF_CONFIG                       0x1A
#define PRESSURE5_REG_POWER_CTRL                      0x1B
#define PRESSURE5_REG_OSR                             0x1C
#define PRESSURE5_REG_ODR                             0x1D
#define PRESSURE5_REG_CONFIGURATION                   0x1F
#define PRESSURE5_REG_COMMAND                         0x7E
/** \} */

/**
 * \defgroup fifo_config FIFO Config 
 * \{
 */
#define PRESSURE5_FCFG_FIFO_ENABLE                    0x01
#define PRESSURE5_FCFG_FIFO_DISABLE                   0x00
#define PRESSURE5_FCFG_FIFO_STOP_ON_FULL_ENABLE       0x02
#define PRESSURE5_FCFG_FIFO_STOP_ON_FULL_DISABLE      0x00
#define PRESSURE5_FCFG_FIFO_TIME_ENABLE               0x04
#define PRESSURE5_FCFG_FIFO_TIME_DISABLE              0x00
#define PRESSURE5_FCFG_FIFO_PRESSURE_STORE_ENABLE     0x08
#define PRESSURE5_FCFG_FIFO_PRESSURE_STORE_DISABLE    0x00
#define PRESSURE5_FCFG_FIFO_TEMP_STORE_ENABLE         0x10
#define PRESSURE5_FCFG_FIFO_TEMP_STORE_DISABLE        0x00
/** \} */

/**
 * \defgroup int_config Int config 
 * \{
 */
#define PRESSURE5_INTCFG_INT_OUTPUT_PUSH_PULL         0x00
#define PRESSURE5_INTCFG_INT_OUTPUT_OPEN_DRAIN        0x01
#define PRESSURE5_INTCFG_INT_LEVEL_ACTIVE_HIGH        0x02
#define PRESSURE5_INTCFG_INT_LEVEL_ACTIVE_LOW         0x00
#define PRESSURE5_INTCFG_INT_LATCH_ENABLE             0x04
#define PRESSURE5_INTCFG_INT_LATCH_DISABLE            0x00
#define PRESSURE5_INTCFG_FIFO_WTM_ENABLE              0x08
#define PRESSURE5_INTCFG_FIFO_WTM_DISABLE             0x00
#define PRESSURE5_INTCFG_FIFO_FULL_ENABLE             0x10
#define PRESSURE5_INTCFG_FIFO_FULL_DISABLE            0x00
#define PRESSURE5_INTCFG_DATA_READY_ENABLE            0x20
#define PRESSURE5_INTCFG_DATA_READY_DISABLE           0x00
/** \} */

/**
 * \defgroup if_config IF config 
 * \{
 */
#define PRESSURE5_IFCFG_SPI_4_WIRE                    0x00
#define PRESSURE5_IFCFG_SPI_3_WIRE                    0x01
#define PRESSURE5_IFCFG_I2C_WATCHDOG_ENABLE           0x02
#define PRESSURE5_IFCFG_I2C_WATCHDOG_DISABLE          0x00
#define PRESSURE5_IFCFG_I2C_WATCHDOG_SHORT_1p25ms     0x00
#define PRESSURE5_IFCFG_I2C_WATCHDOG_LONG_40ms        0x04
/** \} */

/**
 * \defgroup power_ctrl Power control registers
 * \{
 */
#define PRESSURE5_PCTRL_PRESSURE_SENSOR_DISABLE       0x00
#define PRESSURE5_PCTRL_PRESSURE_SENSOR_ENABLE        0x01
#define PRESSURE5_PCTRL_TEMP_SENSOR_DISABLE           0x00
#define PRESSURE5_PCTRL_TEMP_SENSOR_ENABLE            0x02
#define PRESSURE5_PCTRL_MODE_SLEEP                    0x00
#define PRESSURE5_PCTRL_MODE_FORCED                   0x10
#define PRESSURE5_PCTRL_MODE_NORMAL                   0x30
/** \} */

/**
 * \defgroup osr_registers OSR Registers 
 * \{
 */
#define PRESSURE5_OSR_PRESSURE_x1                     0x00
#define PRESSURE5_OSR_PRESSURE_x2                     0x01
#define PRESSURE5_OSR_PRESSURE_x4                     0x02
#define PRESSURE5_OSR_PRESSURE_x8                     0x03
#define PRESSURE5_OSR_PRESSURE_x16                    0x04
#define PRESSURE5_OSR_PRESSURE_x32                    0x05
#define PRESSURE5_OSR_TEMP_x1                         0x00 >> 1
#define PRESSURE5_OSR_TEMP_x2                         0x10 >> 1
#define PRESSURE5_OSR_TEMP_x4                         0x20 >> 1
#define PRESSURE5_OSR_TEMP_x8                         0x30 >> 1
#define PRESSURE5_OSR_TEMP_x16                        0x40 >> 1
#define PRESSURE5_OSR_TEMP_x32                        0x50 >> 1
/** \} */

/**
 * \defgroup odr_registers ODR registers 
 * \{
 */
#define PRESSURE5_ODR_200                             0x00
#define PRESSURE5_ODR_100                             0x01
#define PRESSURE5_ODR_50                              0x02
#define PRESSURE5_ODR_25                              0x03
#define PRESSURE5_ODR_12p5                            0x04
#define PRESSURE5_ODR_6p25                            0x05
#define PRESSURE5_ODR_3p1                             0x06
#define PRESSURE5_ODR_1p5                             0x07
#define PRESSURE5_ODR_0p75                            0x08
#define PRESSURE5_ODR_0p39                            0x09
#define PRESSURE5_ODR_0p2                             0x0A
#define PRESSURE5_ODR_0p1                             0x0B
#define PRESSURE5_ODR_0p05                            0x0C
#define PRESSURE5_ODR_0p02                            0x0D
#define PRESSURE5_ODR_0p01                            0x0E
#define PRESSURE5_ODR_0p006                           0x0F
#define PRESSURE5_ODR_0p003                           0x10
#define PRESSURE5_ODR_0p0015                          0x11
/** \} */

/**
 * \defgroup config_registers CONFIG Registers 
 * \{
 */
#define PRESSURE5_CFG_FILTER_COEFF_0                  0x00
#define PRESSURE5_CFG_FILTER_COEFF_1                  0x01 << 1
#define PRESSURE5_CFG_FILTER_COEFF_3                  0x02 << 1
#define PRESSURE5_CFG_FILTER_COEFF_7                  0x03 << 1
#define PRESSURE5_CFG_FILTER_COEFF_15                 0x04 << 1
#define PRESSURE5_CFG_FILTER_COEFF_31                 0x05 << 1
#define PRESSURE5_CFG_FILTER_COEFF_63                 0x06 << 1
#define PRESSURE5_CFG_FILTER_COEFF_127                0x07 << 1
/** \} */

/**
 * \defgroup cmd_registers CMD registers 
 * \{
 */
#define PRESSURE5_CMD_EXTMODE_EN_MIDDLE               0x34
#define PRESSURE5_CMD_FIFO_FLUSH                      0xB0
#define PRESSURE5_CMD_SOFTWARE_RESET                  0xB6
/** \} */

/**
 * \defgroup slave_address Slave Address 
 * \{
 */
#define PRESSURE5_DEVICE_SLAVE_ADDR_GND               0x76
#define PRESSURE5_DEVICE_SLAVE_ADDR_VCC               0x77
/** \} */

/**
 * \defgroup data_raw Data Raw 
 * \{
 */
#define PRESSURE5_TEMPERATURE_RAW_DATA                0x07
#define PRESSURE5_PRESSURE_RAW_DATA                   0x04
/** \} */

/**
 * \defgroup other_macros Other Macros 
 * \{
 */
#define PRESSURE5_DEVICE_ID                           0x50
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
typedef uint8_t  pressure5_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *pressure5_master_io_t )( struct pressure5_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct pressure5_s
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
   pressure5_master_io_t  write_f;
   pressure5_master_io_t  read_f;
   pressure5_select_t master_sel;

} pressure5_t;

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

   pressure5_select_t sel;

} pressure5_cfg_t;

typedef struct
{
    uint16_t t1;
    uint16_t t2;
    int8_t   t3;

    int16_t  p1;
    int16_t  p2;
    int8_t   p3;
    int8_t   p4;
    uint16_t p5;
    uint16_t p6;
    int8_t   p7;
    int8_t   p8;
    int16_t  p9;
    int8_t   p10;
    int8_t   p11;

} pressure5_nvm_par_t;


typedef struct
{
    float t1;
    float t2;
    float t3;

    float p1;
    float p2;
    float p3;
    float p4;
    float p5;
    float p6;
    float p7;
    float p8;
    float p9;
    float p10;
    float p11;

} pressure5_par_coeff_t;

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
void pressure5_cfg_setup ( pressure5_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param pressure5 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
PRESSURE5_RETVAL pressure5_init ( pressure5_t *ctx, pressure5_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Pressure 5 Click.
 */
void pressure5_default_cfg ( pressure5_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx        Click object.
 * @param reg        Register address.
 * @param reg_data   Output data buf
 *
 * @description This function writes data to the desired register.
 */
void pressure5_generic_write ( pressure5_t *ctx, uint8_t reg, uint8_t reg_data);

/**
 * @brief Generic read function.
 *
 * @param ctx      Click object.
 * @param reg          Register address.
 *
 * @description This function reads data from the desired register.
 */
uint8_t pressure5_generic_read ( pressure5_t *ctx, uint8_t reg );
/**
 * @brief Function for read more bytes from register
 *
 * @param ctx      Click object.
 * @param reg          Register address.
 * @param data_buf  Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function reads data from the desired register.
 */

void pressure5_read ( pressure5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
/**
 * @brief Get Interrupt pin state
 *
 * @param ctx              Click object.
 *
 * @returns                 Interrupt state on the INT pin.
 */
uint8_t pressure5_get_interrupt_state ( pressure5_t *ctx );
/**
 * @brief Software Reset
 *
 * @param ctx             Click object.
 *
 * @description This function performs software reset of Click ctx
 */
void pressure5_software_reset ( pressure5_t *ctx );
/**
 * @brief Get (Temperature or Pressure) Raw data
 *
 * @param ctx             Click object.
 * @param data_addr       Pressure(PRESSURE_RAW_DATA) or Temperature(TEMPERATURE_RAW_DATA) raw data.
 * @returns               24bit raw data.
 * 
 * @description This function reads raw data from Click ctx. 
 */
uint32_t pressure5_get_raw_data ( pressure5_t *ctx, uint8_t data_addr );
/**
 * @brief Update calibration coefficients
 *
 * @param ctx             Click object.
 *
 *
 * @description  This function allows you to update the calibration coefficient.
 * Coefficients must be updated on the start program.
 */
void pressure5_update_coefficient ( pressure5_t *ctx );
/**
 * @brief Get Temperature data in C
 *
 * @param ctx             Click object.
 *
 * @return Temperature data
 *
 * @description This function gets temperature in Celsius.
 */
float pressure5_get_temperature_data ( pressure5_t *ctx );
/**
 * @brief Get Pressure data in mBar
 *
 * @param ctx             Click object.
 *
 * @return Pressure data
 *
 * @description This function gets pressure in mBar.
 */
float pressure5_get_pressure_data ( pressure5_t *ctx );




#ifdef __cplusplus
}
#endif
#endif  // _PRESSURE5_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
