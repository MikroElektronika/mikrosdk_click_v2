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
 * \brief This file contains API for Barometer 3 Click driver.
 *
 * \addtogroup barometer3 Barometer 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BAROMETER3_H
#define BAROMETER3_H

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

#define BAROMETER3_MAP_MIKROBUS( cfg, mikrobus ) \
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
#define BAROMETER3_MASTER_I2C 0
#define BAROMETER3_MASTER_SPI 1
/** \} */
 
/**
 * \defgroup error_code Error Code
 * \{
 */
#define BAROMETER3_RETVAL  uint8_t

#define BAROMETER3_OK           0x00
#define BAROMETER3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup i2c_address i2c address
 * \{
 */
#define BAROMETER3_I2C_SLV_ADR_GND          0x76
#define BAROMETER3_I2C_SLV_ADR_VCC          0x77
/** \} */
 
/**
 * \defgroup spi_mask  Spi Mask
 * \{
 */
#define BAROMETER3_READ_BIT_MASK            0x80
#define BAROMETER3_WRITE_BIT_MASK           0x7F
/** \} */
 
/**
 * \defgroup reg_map  Reg map
 * \{
 */
#define BAROMETER3_PSR_B2                   0x00
#define BAROMETER3_PSR_B1                   0x01
#define BAROMETER3_PSR_B0                   0x02
#define BAROMETER3_TMP_B2                   0x03
#define BAROMETER3_TMP_B1                   0x04
#define BAROMETER3_TMP_B0                   0x05
#define BAROMETER3_PRS_CFG                  0x06
#define BAROMETER3_TMP_CFG                  0x07
#define BAROMETER3_MEAS_CFG                 0x08
#define BAROMETER3_CFG_REG                  0x09
#define BAROMETER3_INT_STS                  0x0A
#define BAROMETER3_FIFO_STS                 0x0B
#define BAROMETER3_RESET                    0x0C
#define BAROMETER3_PROD_ID                  0x0D
#define BAROMETER3_COEF_C0                  0x10
#define BAROMETER3_COEF_C0_C1               0x11
#define BAROMETER3_COEF_C1                  0x12
#define BAROMETER3_COEF_C00_MSB             0x13
#define BAROMETER3_COEF_C00_LSB             0x14
#define BAROMETER3_COEF_C00_C10             0x15
#define BAROMETER3_COEF_C10_MSB             0x16
#define BAROMETER3_COEF_C10_LSB             0x17
#define BAROMETER3_COEF_C01_MSB             0x18
#define BAROMETER3_COEF_C01_LSB             0x19
#define BAROMETER3_COEF_C11_MSB             0x1A
#define BAROMETER3_COEF_C11_LSB             0x1B
#define BAROMETER3_COEF_C20_MSB             0x1C
#define BAROMETER3_COEF_C20_LSB             0x1D
#define BAROMETER3_COEF_C21_MSB             0x1E
#define BAROMETER3_COEF_C21_LSB             0x1F
#define BAROMETER3_COEF_C30_MSB             0x20
#define BAROMETER3_COEF_C30_LSB             0x21
#define BAROMETER3_COEF_SRCE                0x28
/** \} */
 
/**
 * \defgroup pressure_config  Pressure config
 * \{
 */
#define BAROMETER3_PM_RATE_1                0x00
#define BAROMETER3_PM_RATE_2                0x10
#define BAROMETER3_PM_RATE_4                0x20
#define BAROMETER3_PM_RATE_8                0x30
#define BAROMETER3_PM_RATE_16               0x40
#define BAROMETER3_PM_RATE_32               0x50
#define BAROMETER3_PM_RATE_64               0x60
#define BAROMETER3_PM_RATE_128              0x70
#define BAROMETER3_PM_PRC_1                 0x00
#define BAROMETER3_PM_PRC_2                 0x01
#define BAROMETER3_PM_PRC_4                 0x02
#define BAROMETER3_PM_PRC_8                 0x03
#define BAROMETER3_PM_PRC_16                0x04
#define BAROMETER3_PM_PRC_32                0x05
#define BAROMETER3_PM_PRC_64                0x06
#define BAROMETER3_PM_PRC_128               0x07
/** \} */
 
/**
 * \defgroup temp_config  Temp config
 * \{
 */
#define BAROMETER3_TMP_INT                  0x00
#define BAROMETER3_TMP_EXT                  0x80
#define BAROMETER3_TMP_RATE_1               0x00
#define BAROMETER3_TMP_RATE_2               0x10
#define BAROMETER3_TMP_RATE_4               0x20
#define BAROMETER3_TMP_RATE_8               0x30
#define BAROMETER3_TMP_RATE_16              0x40
#define BAROMETER3_TMP_RATE_32              0x50
#define BAROMETER3_TMP_RATE_64              0x60
#define BAROMETER3_TMP_RATE_128             0x70
#define BAROMETER3_TMP_PRC_1                0x00
#define BAROMETER3_TMP_PRC_2                0x01
#define BAROMETER3_TMP_PRC_4                0x02
#define BAROMETER3_TMP_PRC_8                0x03
#define BAROMETER3_TMP_PRC_16               0x04
#define BAROMETER3_TMP_PRC_32               0x05
#define BAROMETER3_TMP_PRC_64               0x06
#define BAROMETER3_TMP_PRC_128              0x07
/** \} */
 
/**
 * \defgroup sensor_mode_and_status  Sensor mode and status
 * \{
 */
#define BAROMETER3_COEF_RDY                 0x80
#define BAROMETER3_SENSOR_RDY               0x40
#define BAROMETER3_TMP_RDY                  0x20
#define BAROMETER3_PRS_RDY                  0x10
#define BAROMETER3_MEAS_CTRL_IDLE           0x00
#define BAROMETER3_MEAS_CTRL_CMD_PM         0x01
#define BAROMETER3_MEAS_CTRL_CMD_TM         0x02
#define BAROMETER3_MEAS_CTRL_CONT_PM        0x05
#define BAROMETER3_MEAS_CTRL_CONT_TM        0x06
#define BAROMETER3_MEAS_CTRL_CONT_MEAS      0x07
/** \} */
 
/**
 * \defgroup operating_mode  Operating mode
 * \{
 */
#define BAROMETER3_INT_HL_ACT_L             0x00
#define BAROMETER3_INT_HL_ACT_H             0x80
#define BAROMETER3_INT_FIFO                 0x40
#define BAROMETER3_INT_TMP                  0x20
#define BAROMETER3_INT_PRS                  0x10
#define BAROMETER3_T_SHIFT                  0x08
#define BAROMETER3_P_SHIFT                  0x04
#define BAROMETER3_FIFO_EN                  0x02
#define BAROMETER3_SPI_MODE_4_WIRE          0x00
#define BAROMETER3_SPI_MODE_3_WIRE          0x01
/** \} */
 
/**
 * \defgroup interrupt_status  interrupt status  
 * \{
 */
#define BAROMETER3_INT_FIFO_FULL            0x04
#define BAROMETER3_INT_TMP_FLG              0x02
#define BAROMETER3_INT_PRS_FLG              0x01
/** \} */
 
/**
 * \defgroup fifo_status  Fifo status
 * \{
 */
#define BAROMETER3_FIFO_FULL                0x02
#define BAROMETER3_FIFO_EMPTY               0x01
#define BAROMETER3_FIFO_SIZE                  32
/** \} */
 
/**
 * \defgroup soft_res_fifo_status  soft res and fifo status
 * \{
 */
#define BAROMETER3_FIFO_FLUSH               0x80
#define BAROMETER3_SOFT_RST                 0x09
/** \} */
 
/**
 * \defgroup coef_source  Coef source
 * \{
 */
#define BAROMETER3_TMP_COEF_SRCE            0x80
/** \} */
 
/**
 * \defgroup scale_factors  Scale Factors
 * \{
 */
#define BAROMETER3_SCALE_FCTR_OSR_1         524288
#define BAROMETER3_SCALE_FCTR_OSR_2         1572864
#define BAROMETER3_SCALE_FCTR_OSR_4         3670016
#define BAROMETER3_SCALE_FCTR_OSR_8         7864320
#define BAROMETER3_SCALE_FCTR_OSR_16        253952
#define BAROMETER3_SCALE_FCTR_OSR_32        516096
#define BAROMETER3_SCALE_FCTR_OSR_64        1040384
#define BAROMETER3_SCALE_FCTR_OSR_128       2088960
/** \} */
 
/**
 * \defgroup fails  Fails
 * \{
 */
#define BAROMETER3_SUCCESS                  0
#define BAROMETER3_BUSY                     1
#define BAROMETER3_MAX_BUSYTIME             990
#define BAROMETER3_FAIL                     2
#define BAROMETER3_UNFIN                    3
/** \} */
 
/**
 * \defgroup dummy  Dummy
 * \{
 */
#define BAROMETER3_SPI_DUMMY                0x00
/** \} */
 
/**
 * \defgroup communication  Communication
 * \{
 */
#define SPI_COMMUNICATION                   1
#define I2C_COMMUNICATION                   2
/** \} */

/**
 * \defgroup product_id  Product ID value
 * \{
 */
#define BAROMETER3_PRODUCT_ID               0x10
/** \} */

/**
 * \defgroup pascal_to_mbar  Pascal to mBar relation
 * \{
 */
#define BAROMETER3_PASCAL_TO_MBAR           100
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
typedef uint8_t  barometer3_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *barometer3_master_io_t )( struct barometer3_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct barometer3_s
{
    // Input pins 

    digital_in_t int_pin;

    // Output pins 
    
    digital_out_t cs;
    
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

    uint8_t slave_address;
    pin_name_t chip_select;
    barometer3_master_io_t  write_f;
    barometer3_master_io_t  read_f;
    barometer3_select_t master_sel;

    int32_t coef_c0_half;
    int32_t coef_c1;
    int32_t coef_c00;
    int32_t coef_c10;
    int32_t coef_c01;
    int32_t coef_c11;
    int32_t coef_c20;
    int32_t coef_c21;
    int32_t coef_c30;
    float coef_temp_scal;
    uint8_t cfg_temp_mr;
    uint8_t cfg_temp_osr;
    uint8_t cfg_prs_mr;
    uint8_t cfg_prs_osr;
    uint8_t cfg_temp_sens;
    uint8_t cfg_op_mode;

    uint8_t communication_interface;

} barometer3_t;

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

   barometer3_select_t sel;

} barometer3_cfg_t;

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
void barometer3_cfg_setup ( barometer3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param barometer3 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BAROMETER3_RETVAL barometer3_init ( barometer3_t *ctx, barometer3_cfg_t *cfg );

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
void barometer3_generic_write ( barometer3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void barometer3_generic_read ( barometer3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Read byte function
 *
 * @param ctx        Click object.
 * @param reg_adr    8-bit value that defines the register
 *
 * @return rx_buf    8-bit value that defines the output data
 *
 * @description Function is used to read single byte of data 
 * from user defined register.
**/
uint8_t barometer3_read_byte ( barometer3_t *ctx, uint8_t reg_adr );

/**
 * @brief Read Calculation Coefficients function
 *
 * @param ctx        Click object.
 * 
 * @description Function read calculation coefficients.
**/
void  barometer3_read_coeffs ( barometer3_t *ctx );

/**
 * @brief Set mode of operation function
 *
 * @param ctx        Click object.
 * @param op_mode    8-bit register address
 *
 * @description Function set mode of operation.
**/
void barometer3_set_op_mode ( barometer3_t *ctx, uint8_t op_mode );

/**
 * @brief Flush FIFO function
 *
 * @param ctx        Click object.
 * 
 * @description Function flush FIFO.
**/
void barometer3_flush_fifo ( barometer3_t *ctx );

/**
 * @brief Disable FIFO function
 *
 * @param ctx        Click object.
 * 
 * @description Function disable FIFO.
**/
void barometer3_disable_fifo ( barometer3_t *ctx );

/**
 * @brief Standby function
 *
 * @param ctx        Click object.
 * 
 * @description Function standby.
**/
void barometer3_standby ( barometer3_t *ctx );

/**
 * @brief Temperature Measurement Configuration function
 *
 * @param ctx        Click object.
 * @param temp_mr    8-bit measuremetns temperature rate
 * @param temp_osr   8-bit temperature oversampling rate
 *
 * @description Function set configuration for temperature measurement.
**/
void barometer3_cfg_temp ( barometer3_t *ctx, uint8_t temp_mr, uint8_t temp_osr );

/**
 * @brief Pressure Measurement Configuration function
 *
 * @param ctx        Click object.
 * @param prs_mr    8-bit measuremetns pressure rate
 * @param prs_osr   8-bit pressure oversampling rate
 *
 * @description Function set configuration for pressure measurement.
**/
void  barometer3_cfg_pres ( barometer3_t *ctx, uint8_t prs_mr, uint8_t prs_osr );

/**
 * @brief Start Measure Temperature Once function
 *
 * @param ctx        Click object.
 * @param temp_osr   8-bit temperature oversampling rate
 *
 * @return Measure temperature status:
 * - 0x00 ( BAROMETER3_SUCCESS ) : Success.
 * - 0x01 ( BAROMETER3_BUSY )    : Busy.
 * - 0x02 ( BAROMETER3_FAIL )    : Fail.
 * - 0x03 ( BAROMETER3_UNFIN )   : Unfin.
 *
 * @description Function start measure temperature once.
**/
uint8_t barometer3_st_meas_temp_once ( barometer3_t *ctx, uint8_t temp_osr );

/**
 * @brief Start Measure Pressure Once function
 *
 * @param ctx        Click object.
 * @param temp_osr   8-bit pressure oversampling rate
 *
 * @return Measure pressure status:
 * - 0x00 ( BAROMETER3_SUCCESS ) : Success.
 * - 0x01 ( BAROMETER3_BUSY )    : Busy.
 * - 0x02 ( BAROMETER3_FAIL )    : Fail.
 * - 0x03 ( BAROMETER3_UNFIN )   : Unfin.
 *
 * @description Function start measure pressure once.
**/
uint8_t barometer3_st_meas_pres_once ( barometer3_t *ctx, uint8_t prs_osr );

/**
 * @brief Get Raw Measurement results
 *
 * @param ctx        Click object.
 * @param reg    8-bit register address
 * @param raw    pointer to the memory location where data be stored.
 *
 * @description Function get raw measurement results.
**/
void  barometer3_get_raw_res ( barometer3_t *ctx, uint8_t reg_adr, int32_t *raw );

/**
 * @brief Temperature Calculation function
 *
 * @param ctx        Click object.
 * @param raw    raw result.
 *
 * @return float temperature data [ degree Celsius ].
 *
 * @description Function calculate the temperature.
**/
float barometer3_calc_temp ( barometer3_t *ctx, int32_t raw );

/**
 * @brief Pressure Calculation function
 *
 * @param ctx        Click object.
 * @param raw    raw result.
 *
 * @return float pressure data [ Pa ].
 *
 * @description Function calculate the pressure.
**/
float barometer3_calc_pres ( barometer3_t *ctx, int32_t raw );

/**
 * @brief Get Single measurement function
 *
 * @param ctx        Click object.
 * @param result    float result data.
 *
 * @return Measure result status:
 * - 0x00 ( BAROMETER3_SUCCESS ) : Success.
 * - 0x01 ( BAROMETER3_BUSY )    : Busy.
 * - 0x02 ( BAROMETER3_FAIL )    : Fail.
 * - 0x03 ( BAROMETER3_UNFIN )   : Unfin.
 *
 * @description Function get single measurement.
**/
uint8_t barometer3_get_single_res ( barometer3_t *ctx, float *result );

/**
 * @brief Get Temperature Measurement Once function
 *
 * @param ctx        Click object.
 * @param result    
 * pointer to the memory location where temperature data be stored.
 * @param temp_osr   8-bit temperature oversampling rat
 *
 * @return Measure temperature status:
 * - 0x00 ( BAROMETER3_SUCCESS ) : Success.
 * - 0x01 ( BAROMETER3_BUSY )    : Busy.
 * - 0x02 ( BAROMETER3_FAIL )    : Fail.
 * - 0x03 ( BAROMETER3_UNFIN )   : Unfin.
 *
 * @description Function perform temperature measurement once.
**/
uint8_t barometer3_meas_temp_once ( barometer3_t *ctx, float *result, uint8_t temp_osr );

/**
 * @brief Get Pressure Measurement Once function
 *
 * @param ctx        Click object.
 * @param result
 * pointer to the memory location where pressure data be stored.
 * @param prs_osr   8-bit pressure oversampling rat
 *
 * @return Measure pressure status:
 * - 0x00 ( BAROMETER3_SUCCESS ) : Success.
 * - 0x01 ( BAROMETER3_BUSY )    : Busy.
 * - 0x02 ( BAROMETER3_FAIL )    : Fail.
 * - 0x03 ( BAROMETER3_UNFIN )   : Unfin.
 *
 * @description Function perform pressure measurement once.
**/
uint8_t barometer3_meas_prs_once ( barometer3_t *ctx, float *result, uint8_t prs_osr );

/**
 * @brief Apply Default Configuration function
 *
 * @param ctx        Click object.
 * 
 * @description Function apply default configuration.
**/
void barometer3_def_cfg ( barometer3_t *ctx );

/**
 * @brief Get FIFO Value function
 *
 * @param ctx        Click object.
 * @param value    pointer to the memory location where data be stored.
 *
 * @return Measure pressure status:
 * - 0x00 ( BAROMETER3_SUCCESS ) : Success.
 * - 0x01 ( BAROMETER3_BUSY )    : Busy.
 * - 0x02 ( BAROMETER3_FAIL )    : Fail.
 * - 0x03 ( BAROMETER3_UNFIN )   : Unfin.
 *
 * @description Function perform pressure measurement once.
**/
uint8_t barometer3_get_fifo_val ( barometer3_t *ctx, int32_t *value );

/**
 * @brief Get Continuous results function
 *
 * @param ctx        Click object.
 * @param result
 * pointer to the memory location where temperature data be stored.
 * @param result
 * pointer to the memory location where pressure data be stored.
 *
 * @return Measure pressure status:
 * - 0x00 ( BAROMETER3_SUCCESS ) : Success.
 * - 0x01 ( BAROMETER3_BUSY )    : Busy.
 * - 0x02 ( BAROMETER3_FAIL )    : Fail.
 * - 0x03 ( BAROMETER3_UNFIN )   : Unfin.
 *
 * @description Function get continuous results.
**/
uint8_t barometer3_get_cont_res ( barometer3_t *ctx, float *temp_buf, float *prs_buf );

/**
 * @brief Check interrupt ststus function.
 *
 * @param ctx        Click object.
 * 
 * @return
 * Interrupt state:
 * - 0 : No active.
 * - 1 : Active.
 *
 * @description Function check interrupt state by return state.
 */
uint8_t barometer3_check_int ( barometer3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _BAROMETER3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
