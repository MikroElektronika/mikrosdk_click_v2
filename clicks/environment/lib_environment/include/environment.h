/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright (c) 2019, MikroElektronika - www.mikroe.com
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*!
 * \file
 *
 * \brief This file contains API for Environment Click driver.
 *
 * \addtogroup environment  Environment Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

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

#define ENVIRONMENT_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define ENVIRONMENT_MASTER_I2C 0
#define ENVIRONMENT_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ENVIRONMENT_RETVAL  uint8_t

#define ENVIRONMENT_OK           0x00
#define ENVIRONMENT_INIT_ERROR   0xFF
/** \} */

#define ENVIRONMENT_POLL_PERIOD_MS                                        10

/**
 * \defgroup bme_i2c_registers BME680 I2C addresses
 * \{
 */
#define ENVIRONMENT_DEVICE_SLAVE_ADDR_0                                   0x76
#define ENVIRONMENT_DEVICE_SLAVE_ADDR_1                                   0x77
#define ENVIRONMENT_CHIP_ID                                               0x61
#define ENVIRONMENT_COEFF_SIZE                                            41
#define ENVIRONMENT_COEFF_ADDR1_LEN                                       25
#define ENVIRONMENT_COEFF_ADDR2_LEN                                       16
#define ENVIRONMENT_FIELD_LENGTH                                          15
#define ENVIRONMENT_FIELD_ADDR_OFFSET                                     17
#define ENVIRONMENT_SOFT_RESET_CMD                                        0xB6
#define ENVIRONMENT_DEVICE_OK                                             0
#define ENVIRONMENT_DEVICE_ERROR                                          1
#define ENVIRONMENT_E_NULL_PTR                                           -1
#define ENVIRONMENT_E_COM_FAIL                                           -2
#define ENVIRONMENT_E_DEV_NOT_FOUND                                      -3
#define ENVIRONMENT_E_INVALID_LENGTH                                     -4
#define ENVIRONMENT_W_DEFINE_PWR_MODE                                     1
#define ENVIRONMENT_W_NO_NEW_DATA                                         2
#define ENVIRONMENT_I_MIN_CORRECTION                                      1
#define ENVIRONMENT_I_MAX_CORRECTION                                      2
/** \} */

/**
 * \defgroup bme680_address_registers BME680 Addresses
 * \{
 */
#define ENVIRONMENT_ADDR_RES_HEAT_VAL_ADDR                                0x00
#define ENVIRONMENT_ADDR_RES_HEAT_RANGE_ADDR                              0x02
#define ENVIRONMENT_ADDR_RANGE_SW_ERR_ADDR                                0x04
#define ENVIRONMENT_ADDR_SENS_CONF_START                                  0x5A
#define ENVIRONMENT_ADDR_GAS_CONF_START                                   0x64
#define ENVIRONMENT_FIELD0_ADDR                                           0x1d
#define ENVIRONMENT_RES_HEAT0_ADDR                                        0x5a
#define ENVIRONMENT_GAS_WAIT0_ADDR                                        0x64
#define ENVIRONMENT_CONF_HEAT_CTRL_ADDR                                   0x70
#define ENVIRONMENT_CONF_ODR_RUN_GAS_NBC_ADDR                             0x71
#define ENVIRONMENT_CONF_OS_H_ADDR                                        0x72
#define ENVIRONMENT_MEM_PAGE_ADDR                                         0xf3
#define ENVIRONMENT_CONF_T_P_MODE_ADDR                                    0x74
#define ENVIRONMENT_CONF_ODR_FILT_ADDR                                    0x75
#define ENVIRONMENT_COEFF_ADDR1                                           0x89
#define ENVIRONMENT_COEFF_ADDR2                                           0xe1
#define ENVIRONMENT_CHIP_ID_ADDR                                          0xd0
#define ENVIRONMENT_SOFT_RESET_ADDR                                       0xe0
/** \} */

/**
 * \defgroup bme680_various_registers BME680 Various Addresses
 * \{
 */
#define ENVIRONMENT_ENABLE_HEATER                                         0x00
#define ENVIRONMENT_DISABLE_HEATER                                        0x08
#define ENVIRONMENT_DISABLE_GAS_MEAS                                      0x00
#define ENVIRONMENT_ENABLE_GAS_MEAS                                       0x01
#define ENVIRONMENT_OS_NONE                                               0
#define ENVIRONMENT_OS_1X                                                 1
#define ENVIRONMENT_OS_2X                                                 2
#define ENVIRONMENT_OS_4X                                                 3
#define ENVIRONMENT_OS_8X                                                 4
#define ENVIRONMENT_OS_16X                                                5
#define ENVIRONMENT_FILTER_SIZE_0                                         0
#define ENVIRONMENT_FILTER_SIZE_1                                         1
#define ENVIRONMENT_FILTER_SIZE_3                                         2
#define ENVIRONMENT_FILTER_SIZE_7                                         3
#define ENVIRONMENT_FILTER_SIZE_15                                        4
#define ENVIRONMENT_FILTER_SIZE_31                                        5
#define ENVIRONMENT_FILTER_SIZE_63                                        6
#define ENVIRONMENT_FILTER_SIZE_127                                       7
#define ENVIRONMENT_SLEEP_MODE                                            0
#define ENVIRONMENT_FORCED_MODE                                           1
#define ENVIRONMENT_RESET_PERIOD                                          10
#define ENVIRONMENT_MEM_PAGE0                                             0x10
#define ENVIRONMENT_MEM_PAGE1                                             0x00
#define ENVIRONMENT_HUM_REG_SHIFT_VAL                                     4
#define ENVIRONMENT_RUN_GAS_DISABLE                                       0
#define ENVIRONMENT_RUN_GAS_ENABLE                                        1
#define ENVIRONMENT_TMP_BUFFER_LENGTH                                     40
#define ENVIRONMENT_REG_BUFFER_LENGTH                                     6 
#define ENVIRONMENT_FIELD_DATA_LENGTH                                     3 
#define ENVIRONMENT_GAS_REG_BUF_LENGTH                                    20
#define ENVIRONMENT_OST_SEL                                               1
#define ENVIRONMENT_OSP_SEL                                               2
#define ENVIRONMENT_OSH_SEL                                               4
#define ENVIRONMENT_GAS_MEAS_SEL                                          8
#define ENVIRONMENT_FILTER_SEL                                            16
#define ENVIRONMENT_HCNTRL_SEL                                            32
#define ENVIRONMENT_RUN_GAS_SEL                                           64
#define ENVIRONMENT_NBCONV_SEL                                            128
#define ENVIRONMENT_GAS_SENSOR_SEL                                       ( ENVIRONMENT_GAS_MEAS_SEL | \
                                                                           ENVIRONMENT_RUN_GAS_SEL | \
                                                                           ENVIRONMENT_NBCONV_SEL )
#define ENVIRONMENT_NBCONV_MIN                                            0 
#define ENVIRONMENT_NBCONV_MAX                                            10
#define ENVIRONMENT_GAS_MEAS_MSK                                          0x30
#define ENVIRONMENT_NBCONV_MSK                                            0X0F
#define ENVIRONMENT_FILTER_MSK                                            0X1C
#define ENVIRONMENT_OST_MSK                                               0XE0
#define ENVIRONMENT_OSP_MSK                                               0X1C
#define ENVIRONMENT_OSH_MSK                                               0X07
#define ENVIRONMENT_HCTRL_MSK                                             0x08
#define ENVIRONMENT_RUN_GAS_MSK                                           0x10
#define ENVIRONMENT_MODE_MSK                                              0x03
#define ENVIRONMENT_RHRANGE_MSK                                           0x30
#define ENVIRONMENT_RSERROR_MSK                                           0xf0
#define ENVIRONMENT_NEW_DATA_MSK                                          0x80
#define ENVIRONMENT_GAS_INDEX_MSK                                         0x0f
#define ENVIRONMENT_GAS_RANGE_MSK                                         0x0f
#define ENVIRONMENT_GASM_VALID_MSK                                        0x20
#define ENVIRONMENT_HEAT_STAB_MSK                                         0x10
#define ENVIRONMENT_MEM_PAGE_MSK                                          0x10
#define ENVIRONMENT_SPI_RD_MSK                                            0x80
#define ENVIRONMENT_SPI_WR_MSK                                            0x7f
#define ENVIRONMENT_BIT_H1_DATA_MSK                                       0x0F
#define ENVIRONMENT_GAS_MEAS_POS                                          4
#define ENVIRONMENT_FILTER_POS                                            2
#define ENVIRONMENT_OST_POS                                               5
#define ENVIRONMENT_OSP_POS                                               2
#define ENVIRONMENT_RUN_GAS_POS                                           4
#define ENVIRONMENT_T2_LSB_REG                                            1
#define ENVIRONMENT_T2_MSB_REG                                            2
#define ENVIRONMENT_T3_REG                                                3
#define ENVIRONMENT_P1_LSB_REG                                            5
#define ENVIRONMENT_P1_MSB_REG                                            6
#define ENVIRONMENT_P2_LSB_REG                                            7
#define ENVIRONMENT_P2_MSB_REG                                            8
#define ENVIRONMENT_P3_REG                                                9
#define ENVIRONMENT_P4_LSB_REG                                            11
#define ENVIRONMENT_P4_MSB_REG                                            12
#define ENVIRONMENT_P5_LSB_REG                                            13
#define ENVIRONMENT_P5_MSB_REG                                            14
#define ENVIRONMENT_P7_REG                                                15
#define ENVIRONMENT_P6_REG                                                16
#define ENVIRONMENT_P8_LSB_REG                                            19
#define ENVIRONMENT_P8_MSB_REG                                            20
#define ENVIRONMENT_P9_LSB_REG                                            21
#define ENVIRONMENT_P9_MSB_REG                                            22
#define ENVIRONMENT_P10_REG                                               23
#define ENVIRONMENT_H2_MSB_REG                                            25
#define ENVIRONMENT_H2_LSB_REG                                            26
#define ENVIRONMENT_H1_LSB_REG                                            26
#define ENVIRONMENT_H1_MSB_REG                                            27
#define ENVIRONMENT_H3_REG                                                28
#define ENVIRONMENT_H4_REG                                                29
#define ENVIRONMENT_H5_REG                                                30
#define ENVIRONMENT_H6_REG                                                31
#define ENVIRONMENT_H7_REG                                                32
#define ENVIRONMENT_T1_LSB_REG                                            33
#define ENVIRONMENT_T1_MSB_REG                                            34
#define ENVIRONMENT_GH2_LSB_REG                                           35
#define ENVIRONMENT_GH2_MSB_REG                                           36
#define ENVIRONMENT_GH1_REG                                               37
#define ENVIRONMENT_GH3_REG                                               38
#define ENVIRONMENT_REG_FILTER_INDEX                                      5
#define ENVIRONMENT_REG_TEMP_INDEX                                        4
#define ENVIRONMENT_REG_PRES_INDEX                                        4
#define ENVIRONMENT_REG_HUM_INDEX                                         2
#define ENVIRONMENT_REG_NBCONV_INDEX                                      1
#define ENVIRONMENT_REG_RUN_GAS_INDEX                                     1
#define ENVIRONMENT_REG_HCTRL_INDEX                                       0
#define ENVIRONMENT_MAX_OVERFLOW_VAL                                      0x40000000
#define ENVIRONMENT_DATA_TEMPERATURE                                      0x01
#define ENVIRONMENT_DATA_PRESSURE                                         0x02
#define ENVIRONMENT_DATA_HUMIDITY                                         0x03
#define BME680_CONCAT_BYTES(msb, lsb)        (((uint16_t)msb << 8) | (uint16_t)lsb)
#define BME680_SET_BITS(reg_data, bitname, data) \
                ((reg_data & ~(bitname##_MSK)) | \
                ((data << bitname##_POS) & bitname##_MSK))
#define BME680_SET_BITS_POS_0(reg_data, bitname, data) \
                                ((reg_data & ~(bitname##_MSK)) | \
                                (data & bitname##_MSK))

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

typedef struct
{
    uint8_t status;
    uint8_t gas_index;
    uint8_t meas_index;
    int16_t temperature;
    float pressure;
    uint32_t humidity;
    uint32_t gas_resistance;

}T_ENVIRONMENT_BME680_FIELD_DATA;

typedef struct
{
    uint16_t par_h1;
    uint16_t par_h2;
    int8_t par_h3;
    int8_t par_h4;
    int8_t par_h5;
    uint8_t par_h6;
    int8_t par_h7;
    int8_t par_gh1;
    int16_t par_gh2;
    int8_t par_gh3;
    uint16_t par_t1;
    int16_t par_t2;
    int8_t par_t3;
    uint16_t par_p1;
    int16_t par_p2;
    int8_t par_p3;
    int16_t par_p4;
    int16_t par_p5;
    int8_t par_p6;
    int8_t par_p7;
    int16_t par_p8;
    int16_t par_p9;
    uint8_t par_p10;
    int32_t t_fine;
    uint8_t res_heat_range;
    int8_t res_heat_val;
    int8_t range_sw_err;

} T_ENVIRONMENT_BME680_CALIB_DATA;

typedef struct
{
    uint8_t os_hum;
    uint8_t os_temp;
    uint8_t os_pres;
    uint8_t filter;

}T_ENVIRONMENT_BME680_TPH_SETTINGS;


typedef struct
{
    uint8_t nb_conv;
    uint8_t heatr_ctrl;
    uint8_t run_gas;
    uint16_t heatr_temp;
    uint16_t heatr_dur;

}T_ENVIRONMENT_BME680_GAS_SETTINGS;

/**
 * @brief Communication type.
 */
typedef uint8_t  environment_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *environment_master_io_t )( struct environment_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct environment_s
{    
    digital_out_t cs;

   // Modules 

   i2c_master_t i2c;
   spi_master_t spi;

   // ctx variable 

    uint8_t slave_address;
    pin_name_t chip_select;
   environment_master_io_t  write_f;
   environment_master_io_t  read_f;
   environment_select_t master_sel;

   T_ENVIRONMENT_BME680_FIELD_DATA d_data;
   T_ENVIRONMENT_BME680_CALIB_DATA calib;
   T_ENVIRONMENT_BME680_TPH_SETTINGS tph_sett;
   T_ENVIRONMENT_BME680_GAS_SETTINGS gas_sett;

   uint8_t device_mem_page;
   uint8_t device_power_mode;

} environment_t;

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

    // static variable 

   uint32_t i2c_speed;
   uint8_t  i2c_address;

   uint32_t spi_speed;
   spi_master_mode_t  spi_mode;
   spi_master_chip_select_polarity_t cs_polarity;

   environment_select_t sel;

} environment_cfg_t;

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
void environment_cfg_setup ( environment_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param environment  Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ENVIRONMENT_RETVAL environment_init ( environment_t *ctx, environment_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 * 
 *
 * @description This function executes default configuration for Environment click.
 */
void environment_default_cfg ( environment_t *ctx );

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
void environment_generic_write ( environment_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void environment_generic_read ( environment_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic the write byte of data function
 *
 * @param ctx      Click object.
 *
 * @param reg_address                8-bit register address
 *
 * @param write_data                 Byte of data to write
 *
 * @description Function write the 8-bit of data to the
 * target 8-bit register address of BME680 chip on Environment Click board.
 */
void environment_write_byte ( environment_t *ctx, uint8_t reg_address, uint8_t write_data );

/**
 * @brief Generic the read byte of data function
 *
 *
 * @param ctx                        Click object.
 *
 * @param reg_address                Register address
 *
 * @returnss                          8-bit read data
 *
 * @description Function read the 8-bit of data from the
 * target 8-bit register address of BME680 chip on Environment Click board.
 */
uint8_t environment_read_byte ( environment_t *ctx, uint8_t reg_address );

/**
 * @brief Check device ID function
 *
 *
 * @param ctx      Click object.
 *
 * @returns
 * - 0 : ERROR;
 * - 1 : OK;
 *
 * @description Function check device ID by read ID value from the
 * sensor ID register address of BME680 chip on Environment Click board.
 */
uint8_t environment_check_id ( environment_t *ctx );

/**
 * @brief Get device ID function
 *
 *
 * @param ctx      Click object.
 *
 * @returns         8-bit device ID value
 *
 * @description Function read device ID from the
 * sensor ID register address of BME680 chip on Environment Click board.
 *
 * @note
 * Default device: ID = 0x61.
 */
uint8_t environment_get_device_id ( environment_t *ctx );

/**
 * @brief Software reset function
 *
 *
 * @param ctx      Click object.
 *
 * @description Function software reset by write value of 0xB6 to the
 * sensor reset register address of BME680 chip on Environment Click board.
 */
void environment_soft_reset ( environment_t *ctx );

/**
 * @brief Get factory calibration parameters function
 *
 *
 * @param ctx      Click object.
 *
 * @description Function read factory calibration parameters value from the
 * sensor calibration registers address of BME680 chip on Environment Click board.
 *
 * @note
 * This function must be called at least once at the beginning of the program
 * to read and store the calibration parameters in the memory.
 */
void environment_get_calibration_data ( environment_t *ctx );

/**
 * @brief Set default configuration for the BMP680 sensor function
 *
 *
 * @param ctx      Click object.
 *
 * @description Function set default configuration to the
 * sensor configuration register address of BME680 chip on Environment Click board.
 *
 * @note
 * This function must be called at least once at the beginning of the program
 * so that the sensor can be successfully configured for measurement.
 */
void environment_default_config ( environment_t *ctx );

/**
 * @brief Get ambient data function
 *
 *
 * @param ctx      Click object.
 *
 * @param dataIn    Data for reading:
 *
 * @returns 
 * float ambient ( temperature, pressure or humidity ) data
 *
 * @description Function get ambient data by sets device force mode and read data from the
 * sensor temperature,  pressure or humidity register address
 * of BME680 chip on Environment Click board.
 */
float environment_get_ambient_data ( environment_t *ctx, uint8_t data_in );

/**
 * @brief Gets temperature in degrees Celsius function
 *
 *
 * @param ctx      Click object.
 *
 * @returns
 * float value of temperature in degrees Celsius
 *
 * @description Function get temperature value in degrees Celsius [ �C ] from the
 * sensor temperature register address of BME680 chip on Environment Click board.
 */
float environment_get_temperature ( environment_t *ctx );

/**
 * @brief Gets humidity in percentage [ % ] function
 *
 *
 * @param ctx      Click object.
 *
 * @returns
 * float value of humidity in percentage [ % ]
 *
 * @description Function get humidity value in percentage [ % ] from the
 * sensor humidity register address of BME680 chip on Environment Click board.
 */
float environment_get_humidity ( environment_t *ctx );

/**
 * @brief Gets pressure in degrees Celsius function
 *
 *
 * @param ctx      Click object.
 *
 * @returns        float value of pressure in [ mbar ]
 *
 * @description Function get pressure value in [ mbar ] from the
 * sensor pressure register address of BME680 chip on Environment Click board.
 */
float environment_get_pressure ( environment_t *ctx );

/**
 * @brief Gets gas resistance data function
 *
 *
 * @param ctx      Click object.
 *
 * @returnss 32-bite gas resistance data
 *
 * @description Function get gas resistance value from the
 * sensor gas resistance register address of BME680 chip on Environment Click board.
 */
uint32_t environment_get_gas_resistance ( environment_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _ENVIRONMENT_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
