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
 * \brief This file contains API for Pressure 3 Click driver.
 *
 * \addtogroup pressure3 Pressure 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PRESSURE3_H
#define PRESSURE3_H

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

#define PRESSURE3_MAP_MIKROBUS( cfg, mikrobus ) \
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
#define PRESSURE3_MASTER_I2C 0
#define PRESSURE3_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PRESSURE3_RETVAL  uint8_t

#define PRESSURE3_OK           0x00
#define PRESSURE3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup select  Select
 * \{
 */
#define PRESSURE3_I2C_SELECT                                      0
#define PRESSURE3_SPI_SELECT                                      1
#define PRESSURE3_SPI_CMD_WRITE                                 0x7F
#define PRESSURE3_SPI_CMD_READ                                  0x80
/** \} */

/**
 * \defgroup configuration_register Configuration Registers
 * \{
 */
#define PRESSURE3_I2C_ADDRESS                  0x76
#define PRESSURE3_REG_PSR_B2                   0x00
#define PRESSURE3_REG_PSR_B1                   0x01
#define PRESSURE3_REG_PSR_B0                   0x02
#define PRESSURE3_REG_TMP_B2                   0x03
#define PRESSURE3_REG_TMP_B1                   0x04
#define PRESSURE3_REG_TMP_B0                   0x05
#define PRESSURE3_REG_PRS_CFG                  0x06
#define PRESSURE3_REG_TMP_CFG                  0x07
#define PRESSURE3_REG_MEAS_CFG                 0x08
#define PRESSURE3_REG_CFG_REG                  0x09
#define PRESSURE3_REG_INT_STS                  0x0A
#define PRESSURE3_REG_FIFO_STS                 0x0B
#define PRESSURE3_REG_RESET                    0x0C
#define PRESSURE3_REG_PRODUCT_ID               0x0D
#define PRESSURE3_REG_COEF_C0_MBS              0x10
#define PRESSURE3_REG_COEF_C0_LBS_C1_MBS       0x11
#define PRESSURE3_REG_COEF_C1_LBS              0x12
#define PRESSURE3_REG_COEF_C00_MBS             0x13
#define PRESSURE3_REG_COEF_C00_LSB             0x14
#define PRESSURE3_REG_COEF_C00_XLSB_C10_MSB    0x15
#define PRESSURE3_REG_COEF_C10_LSB             0x16
#define PRESSURE3_REG_COEF_C10_XLSB            0x17
#define PRESSURE3_REG_COEF_C01_MSB             0x18
#define PRESSURE3_REG_COEF_C01_LSB             0x19
#define PRESSURE3_REG_COEF_C11_MSB             0x1A
#define PRESSURE3_REG_COEF_C11_LSB             0x1B
#define PRESSURE3_REG_COEF_C20_MSB             0x1C
#define PRESSURE3_REG_COEF_C20_LSB             0x1D
#define PRESSURE3_REG_COEF_C21_MSB             0x1E
#define PRESSURE3_REG_COEF_C21_LSB             0x1F
#define PRESSURE3_REG_COEF_C30_MSB             0x20
#define PRESSURE3_REG_COEF_C30_LSB             0x21
#define PRESSURE3_REG_COEF_SRCE                0x28
/** \} */

/**
 * \defgroup pressure_configuration   Pressure Configuration
 * \{
 */
#define PRESSURE3_BIT_MASK_PM_RATE_1_PER_SEC                  0x00
#define PRESSURE3_BIT_MASK_PM_RATE_2_PER_SEC                  0x10
#define PRESSURE3_BIT_MASK_PM_RATE_4_PER_SEC                  0x20
#define PRESSURE3_BIT_MASK_PM_RATE_8_PER_SEC                  0x30
#define PRESSURE3_BIT_MASK_PM_RATE_16_PER_SEC                 0x40
#define PRESSURE3_BIT_MASK_PM_RATE_32_PER_SEC                 0x50
#define PRESSURE3_BIT_MASK_PM_RATE_64_PER_SEC                 0x60
#define PRESSURE3_BIT_MASK_PM_RATE_128_PER_SEC                0x70
#define PRESSURE3_BIT_MASK_PM_PRC_1_PER_SEC                   0x00
#define PRESSURE3_BIT_MASK_PM_PRC_2_PER_SEC                   0x01
#define PRESSURE3_BIT_MASK_PM_PRC_4_PER_SEC                   0x02
#define PRESSURE3_BIT_MASK_PM_PRC_8_PER_SEC                   0x03
#define PRESSURE3_BIT_MASK_PM_PRC_16_PER_SEC                  0x04
#define PRESSURE3_BIT_MASK_PM_PRC_32_PER_SEC                  0x05
#define PRESSURE3_BIT_MASK_PM_PRC_64_PER_SEC                  0x06
#define PRESSURE3_BIT_MASK_PM_PRC_128_PER_SEC                 0x07
/** \} */

/**
 * \defgroup Temperature_configuration   Temperature Configuration
 * \{
 */
#define PRESSURE3_BIT_MASK_TMP_EXT_INTERNAL_SENSOR                    0x00
#define PRESSURE3_BIT_MASK_TMP_EXT_EXTERNAL_SENSOR                    0x80
#define PRESSURE3_BIT_MASK_TMP_RATE_1_PER_SEC                         0x00
#define PRESSURE3_BIT_MASK_TMP_RATE_2_PER_SEC                         0x10
#define PRESSURE3_BIT_MASK_TMP_RATE_4_PER_SEC                         0x20
#define PRESSURE3_BIT_MASK_TMP_RATE_8_PER_SEC                         0x30
#define PRESSURE3_BIT_MASK_TMP_RATE_16_PER_SEC                        0x40
#define PRESSURE3_BIT_MASK_TMP_RATE_32_PER_SEC                        0x50
#define PRESSURE3_BIT_MASK_TMP_RATE_64_PER_SEC                        0x60
#define PRESSURE3_BIT_MASK_TMP_RATE_128_PER_SEC                       0x70
#define PRESSURE3_BIT_MASK_TMP_PRC_1_PER_SEC                          0x00
#define PRESSURE3_BIT_MASK_TMP_PRC_2_PER_SEC                          0x01
#define PRESSURE3_BIT_MASK_TMP_PRC_4_PER_SEC                          0x02
#define PRESSURE3_BIT_MASK_TMP_PRC_8_PER_SEC                          0x03
#define PRESSURE3_BIT_MASK_TMP_PRC_16_PER_SEC                         0x04
#define PRESSURE3_BIT_MASK_TMP_PRC_32_PER_SEC                         0x05
#define PRESSURE3_BIT_MASK_TMP_PRC_64_PER_SEC                         0x06
#define PRESSURE3_BIT_MASK_TMP_PRC_128_PER_SEC                        0x07
/** \} */

/**
 * \defgroup senor_operating_mode_and_status    Sensor Operating Mode and Status
 * \{
 */
#define PRESSURE3_BIT_MASK_MEAS_CFG_COEF_RDY_AVB                  0x80
#define PRESSURE3_BIT_MASK_MEAS_CFG_COEF_RDY_NO_AVB               0x00
#define PRESSURE3_BIT_MASK_MEAS_CFG_SENSOR_RDY_CMP                0x40
#define PRESSURE3_BIT_MASK_MEAS_CFG_SENSOR_RDY_NO_CMP             0x00
#define PRESSURE3_BIT_MASK_MEAS_CFG_TMP_RDY                       0x20
#define PRESSURE3_BIT_MASK_MEAS_CFG_PRS_RDY                       0x10
#define PRESSURE3_BIT_MASK_MEAS_CFG_MEAS_CTRL_IDLE                0x00
#define PRESSURE3_BIT_MASK_MEAS_CFG_MEAS_CTRL_PRS                 0x01
#define PRESSURE3_BIT_MASK_MEAS_CFG_MEAS_CTRL_TMP                 0x02
#define PRESSURE3_BIT_MASK_MEAS_CFG_MEAS_CTRL_CNT_PRS             0x05
#define PRESSURE3_BIT_MASK_MEAS_CFG_MEAS_CTRL_CNT_TMP             0x06
#define PRESSURE3_BIT_MASK_MEAS_CFG_MEAS_CTRL_CNT_PRS_TMP         0x07
/** \} */

/**
 * \defgroup interrupt_and_fifo_configuration     Interrupt and FIFO configuration
 * \{
 */
#define PRESSURE3_BIT_MASK_CFG_REG_INT_HL_LOW                     0x00
#define PRESSURE3_BIT_MASK_CFG_REG_INT_HL_HIGH                    0x80
#define PRESSURE3_BIT_MASK_CFG_REG_INT_FIFO_DISABLE               0x00
#define PRESSURE3_BIT_MASK_CFG_REG_INT_FIFO_ENABLE                0x40
#define PRESSURE3_BIT_MASK_CFG_REG_INT_TMP_DISABLE                0x00
#define PRESSURE3_BIT_MASK_CFG_REG_INT_TMP_ENABLE                 0x20
#define PRESSURE3_BIT_MASK_CFG_REG_INT_PRS_DISABLE                0x00
#define PRESSURE3_BIT_MASK_CFG_REG_INT_PRS_ENABLE                 0x10
#define PRESSURE3_BIT_MASK_CFG_REG_T_SHIFT_NO_SHIFT               0x00
#define PRESSURE3_BIT_MASK_CFG_REG_T_SHIFT_SHIFT                  0x08
#define PRESSURE3_BIT_MASK_CFG_REG_P_SHIFT_NO_SHIFT               0x00
#define PRESSURE3_BIT_MASK_CFG_REG_P_SHIFT_SHIFT                  0x04
#define PRESSURE3_BIT_MASK_CFG_REG_FIFO_EN_DISABLE                0x00
#define PRESSURE3_BIT_MASK_CFG_REG_FIFO_EN_ENABLE                 0x02
#define PRESSURE3_BIT_MASK_CFG_REG_SPI_MODE_DISABLE               0x00
#define PRESSURE3_BIT_MASK_CFG_REG_SPI_MODE_ENABLE                0x01
/** \} */

/**
 * \defgroup interrupt_status     Interrupt Status
 * \{
 */
#define PRESSURE3_BIT_MASK_INT_STS_INT_FIFO_FULL_NO_ACTIVE         0x00
#define PRESSURE3_BIT_MASK_INT_STS_INT_FIFO_FULL_ACTIVE            0x04
#define PRESSURE3_BIT_MASK_INT_STS_INT_TMP_NO_ACTIVE               0x00
#define PRESSURE3_BIT_MASK_INT_STS_INT_TMP_ACTIVE                  0x02
#define PRESSURE3_BIT_MASK_INT_STS_INT_PRS_NO_ACTIVE               0x00
#define PRESSURE3_BIT_MASK_INT_STS_INT_PRS_ACTIVE                  0x01
/** \} */

/**
 * \defgroup fifo_status     FIFO Status
 * \{
 */
#define PRESSURE3_BIT_MASK_FIFO_STS_FIFO_FULL_NO                   0x00
#define PRESSURE3_BIT_MASK_FIFO_STS_FIFO_FULL_FULL                 0x02
#define PRESSURE3_BIT_MASK_FIFO_STS_FIFO_EMPTY_NO                  0x00
#define PRESSURE3_BIT_MASK_FIFO_STS_FIFO_EMPTY_EMPTY               0x01
/** \} */

/**
 * \defgroup soft_reset_and_fifo_flus     Soft Reset and FIFO flush
 * \{
 */
#define PRESSURE3_BIT_MASK_RESET_SOFT_RST                          0x09
/** \} */

/**
 * \defgroup coefficients_source     Coefficients Source
 * \{
 */
#define PRESSURE3_BIT_MASK_TMP_COEF_SRCE_INTERNAL_SENSOR           0x00
#define PRESSURE3_BIT_MASK_TMP_COEF_SRCE_EXTERNAL_SENSOR           0x80
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
typedef uint8_t  pressure3_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *pressure3_master_io_t )( struct pressure3_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Coefficients structure.
 */
typedef struct 
{
   int16_t coeff_c0;
   int16_t coeff_c1;
   int32_t coeff_c00;
   int32_t coeff_c10;
   int16_t coeff_c01;
   int16_t coeff_c11;
   int16_t coeff_c20;
   int16_t coeff_c21;
   int16_t coeff_c30;

} pressure3_coeff_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct pressure3_s
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
   pressure3_master_io_t  write_f;
   pressure3_master_io_t  read_f;
   pressure3_select_t master_sel;

} pressure3_t;

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
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

   pressure3_select_t sel;

} pressure3_cfg_t;

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
void pressure3_cfg_setup ( pressure3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
PRESSURE3_RETVAL pressure3_init ( pressure3_t *ctx, pressure3_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Pressure 3 click.
 */
void pressure3_default_cfg ( pressure3_t *ctx );

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
void pressure3_generic_write ( pressure3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void pressure3_generic_read ( pressure3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Get temperature pressure.
 *
 * @param ctx                  Click object.
 * @param temperature          pointer to float temperature value in degrees Celsius [ �C ].
 * @param presure              pointer to float presure value [ mbar ].
 * @param coeff_struct         Structure.
 *
 * @description This function reads data from the desired register.
 */
void pressure3_get_t_p_data ( pressure3_t *ctx, float *temperature, float *presure, pressure3_coeff_t *coeff_struct );

/**
 * @brief Get coefficients.
 *
 * @param ctx                  Click object.
 * @param coeff_struct         Structure.
 *
 * @description This function read the measurement data by read from the
 * three target register address of DPS310 sensor on Pressure 3 click board.
 */
void pressure3_get_coefficients ( pressure3_t *ctx, pressure3_coeff_t *coeff_struct );

/**
 * @brief Read the coefficients value for calculation function.
 *
 * @param ctx                  Click object.
 * @param coeff_struct         Structure.
 *
 * @description This function reads data from the desired register.
 */
int32_t pressure3_get_measurement_data ( pressure3_t *ctx, uint8_t mbs_reg_addr );

/**
 * @brief Set the pressure configuration function.
 *
 * @param ctx               Click object.
 * @param press_config      pressConfig
 * - [ bit7 ]
 *    - Reserved.
 * - [ bit6 : bit4 ] Pressure measurement rate:
 *    - 000 : 1 measurements pr. sec.
 *    - 001 : 2 measurements pr. sec.
 *    - 010 : 4 measurements pr. sec.
 *    - 011 : 8 measurements pr. sec.
 *    - 100 : 16 measurements pr. sec.
 *    - 101 : 32 measurements pr. sec.
 *    - 110 : 64 measurements pr. sec.
 *    - 111 : 128 measurements pr. sec.
 * - [ bit3 : bit0 ] Pressure oversampling rate:
 *    - 0000 : Single. (Low Precision)
 *    - 0001 : 2 times (Low Power).
 *    - 0010 : 4 times.
 *    - 0011 : 8 times.
 *    - 0100 : 16 times (Standard).
 *    - 0101 : 32 times.
 *    - 0110 : 64 times (High Precision).
 *    - 0111 : 128 times.
 *    - 1xxx : Reserved
 *
 * @description This function set the pressure configuration by write pressConfig data to the
 * target _PRESSURE3_REG_PRS_CFG register of DPS310 sensor on Pressure 3 click board.
 */
void pressure3_set_pressure_configuration ( pressure3_t *ctx, uint8_t press_config );

/**
 * @brief Get the pressure configuration function.
 *
 * @param ctx      Click object.
 *
 * @description This function get the pressure configuration by read from the
 * target _PRESSURE3_REG_PRS_CFG register of DPS310 sensor on Pressure 3 click board.
 */
uint8_t pressure3_get_pressure_configuration ( pressure3_t *ctx );

/**
 * @brief Set the temperature configuration function.
 *
 * @param ctx              Click object.
 * @param temp_config      tempConfig
 * - [ bit7 ]
 *    - 0 : Internal sensor (in ASIC)
 *    - 1 : External sensor (in pressure sensor MEMS element)
 * - [ bit6 : bit4 ] Temperature measurement rate:
 *    - 000 : 1 measurements pr. sec.
 *    - 001 : 2 measurements pr. sec.
 *    - 010 : 4 measurements pr. sec.
 *    - 011 : 8 measurements pr. sec.
 *    - 100 : 16 measurements pr. sec.
 *    - 101 : 32 measurements pr. sec.
 *    - 110 : 64 measurements pr. sec.
 *    - 111 : 128 measurements pr. sec.
 * - [ bit3 : bit0 ] Temperature oversampling (precision):
 *    - 0000 :  single. (Default) - Measurement time 3.6 ms.
 *    - 0001 : 2 times (Low Power).
 *    - 0010 : 4 times.
 *    - 0011 : 8 times.
 *    - 0100 : 16 times (Standard).
 *    - 0101 : 32 times.
 *    - 0110 : 64 times (High Precision).
 *    - 0111 : 128 times.
 *    - 1xxx : Reserved
 *
 * @description This function set the temperature configuration by write tempConfig data to the
 * target _PRESSURE3_REG_TMP_CFG register of DPS310 sensor on Pressure 3 click board.
 */
void pressure3_set_temperature_configuration ( pressure3_t *ctx, uint8_t temp_config );

/**
 * @brief Get the temperature configuration function.
 *
 * @param ctx      Click object.
 *
 * @description This function get the temperature configuration by write tempConfig data to the
 * target _PRESSURE3_REG_TMP_CFG register of DPS310 sensor on Pressure 3 click board.
 */
uint8_t pressure3_get_temperature_configuration ( pressure3_t *ctx );

/**
 * @brief Get the sensor operating mode function.
 *
 * @param ctx      Click object.
 *
 * @description This function set the sensor operating mode by write operationMode data to the
 * target _PRESSURE3_REG_MEAS_CFG register of DPS310 sensor on Pressure 3 click board.
 */
void pressure3_set_operating_mode( pressure3_t *ctx, uint8_t operation_mode );

/**
 * @brief Get the sensor operating mode function.
 *
 * @param ctx      Click object.
 *
 * @description This function set the sensor operating mode by write operationMode data to the
 * target _PRESSURE3_REG_MEAS_CFG register of DPS310 sensor on Pressure 3 click board.
 */
uint8_t pressure3_get_operating_mode ( pressure3_t *ctx );

/**
 * @brief Set the configuration function.
 *
 * @param ctx      Click object.
 *
 * @description This function set the configuration by write confgData data to the
 * target _PRESSURE3_REG_CFG_REG register of DPS310 sensor on Pressure 3 click board.
 */
void pressure3_set_configuration ( pressure3_t *ctx,uint8_t confg_data );

/**
 * @brief Get the configuration function.
 *
 * @param ctx      Click object.
 *
 * @description This function get the configuration read the byte of data from the
 * target _PRESSURE3_REG_CFG_REG register of DPS310 sensor on Pressure 3 click board.
 */
uint8_t pressure3_get_configuration ( pressure3_t *ctx );

/**
 * @brief Get the interrupt status function.
 *
 * @param ctx      Click object.
 *
 * @description This function get the interrupt status by read the byte of data from the
 * target _PRESSURE3_REG_INT_STS register of DPS310 sensor on Pressure 3 click board.
 */
uint8_t pressure3_get_interrupt_status ( pressure3_t *ctx );

/**
 * @brief Get the FIFO Status function.
 *
 * @param ctx      Click object.
 *
 * @description This function get the interrupt The FIFO is empty by read the byte of data from the
 * target _PRESSURE3_REG_FIFO_STS register of DPS310 sensor on Pressure 3 click board.
 */
uint8_t pressure3_get_fifo_status ( pressure3_t *ctx );

/**
 * @brief Soft reset function.
 *
 * @param ctx      Click object.
 *
 * @description This function set soft reset by write 0x09 to the
 * target _PRESSURE3_REG_RESET register of DPS310 sensor on Pressure 3 click board..
 */
void pressure3_soft_reset (  pressure3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _PRESSURE3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
