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
 * \brief This file contains API for SPI ISLOATOR Click driver.
 *
 * \addtogroup spiisolator SPI ISLOATOR Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef SPIISOLATOR_H
#define SPIISOLATOR_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
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

#define SPIISOLATOR_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define SPIISOLATOR_RETVAL  uint8_t

#define SPIISOLATOR_OK           0x00
#define SPIISOLATOR_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup Write & Read Command - Pressure 3 click
 * \{
 */
#define SPIISOLATOR_PRESSURE3_SPI_CMD_WRITE                               0x7F
#define SPIISOLATOR_PRESSURE3_SPI_CMD_READ                                0x80
/** \} */

/**
 * \defgroup Register Map - Pressure 3 click
 * \{
 */
#define SPIISOLATOR_PRESSURE3_REG_PSR_B2                                  0x00
#define SPIISOLATOR_PRESSURE3_REG_PSR_B1                                  0x01
#define SPIISOLATOR_PRESSURE3_REG_PSR_B0                                  0x02
#define SPIISOLATOR_PRESSURE3_REG_TMP_B2                                  0x03
#define SPIISOLATOR_PRESSURE3_REG_TMP_B1                                  0x04
#define SPIISOLATOR_PRESSURE3_REG_TMP_B0                                  0x05
#define SPIISOLATOR_PRESSURE3_REG_PRS_CFG                                 0x06
#define SPIISOLATOR_PRESSURE3_REG_TMP_CFG                                 0x07
#define SPIISOLATOR_PRESSURE3_REG_MEAS_CFG                                0x08
#define SPIISOLATOR_PRESSURE3_REG_CFG_REG                                 0x09
#define SPIISOLATOR_PRESSURE3_REG_INT_STS                                 0x0A
#define SPIISOLATOR_PRESSURE3_REG_FIFO_STS                                0x0B
#define SPIISOLATOR_PRESSURE3_REG_RESET                                   0x0C
#define SPIISOLATOR_PRESSURE3_REG_PRODUCT_ID                              0x0D
#define SPIISOLATOR_PRESSURE3_REG_COEF_C0_MBS                             0x10
#define SPIISOLATOR_PRESSURE3_REG_COEF_C0_LBS_C1_MBS                      0x11
#define SPIISOLATOR_PRESSURE3_REG_COEF_C1_LBS                             0x12
#define SPIISOLATOR_PRESSURE3_REG_COEF_C00_MBS                            0x13
#define SPIISOLATOR_PRESSURE3_REG_COEF_C00_LSB                            0x14
#define SPIISOLATOR_PRESSURE3_REG_COEF_C00_XLSB_C10_MSB                   0x15
#define SPIISOLATOR_PRESSURE3_REG_COEF_C10_LSB                            0x16
#define SPIISOLATOR_PRESSURE3_REG_COEF_C10_XLSB                           0x17
#define SPIISOLATOR_PRESSURE3_REG_COEF_C01_MSB                            0x18
#define SPIISOLATOR_PRESSURE3_REG_COEF_C01_LSB                            0x19
#define SPIISOLATOR_PRESSURE3_REG_COEF_C11_MSB                            0x1A
#define SPIISOLATOR_PRESSURE3_REG_COEF_C11_LSB                            0x1B
#define SPIISOLATOR_PRESSURE3_REG_COEF_C20_MSB                            0x1C
#define SPIISOLATOR_PRESSURE3_REG_COEF_C20_LSB                            0x1D
#define SPIISOLATOR_PRESSURE3_REG_COEF_C21_MSB                            0x1E
#define SPIISOLATOR_PRESSURE3_REG_COEF_C21_LSB                            0x1F
#define SPIISOLATOR_PRESSURE3_REG_COEF_C30_MSB                            0x20
#define SPIISOLATOR_PRESSURE3_REG_COEF_C30_LSB                            0x21
#define SPIISOLATOR_PRESSURE3_REG_COEF_SRCE                               0x28
/** \} */

/**
 * \defgroup BIT MASK - Pressure Configuration
 * \{
 */
#define SPIISOLATOR_PRESSURE3_BIT_MASK_PM_RATE_1_PER_SEC                  0x00
#define SPIISOLATOR_PRESSURE3_BIT_MASK_PM_RATE_2_PER_SEC                  0x10
#define SPIISOLATOR_PRESSURE3_BIT_MASK_PM_RATE_4_PER_SEC                  0x20
#define SPIISOLATOR_PRESSURE3_BIT_MASK_PM_RATE_8_PER_SEC                  0x30
#define SPIISOLATOR_PRESSURE3_BIT_MASK_PM_RATE_16_PER_SEC                 0x40
#define SPIISOLATOR_PRESSURE3_BIT_MASK_PM_RATE_32_PER_SEC                 0x50
#define SPIISOLATOR_PRESSURE3_BIT_MASK_PM_RATE_64_PER_SEC                 0x60
#define SPIISOLATOR_PRESSURE3_BIT_MASK_PM_RATE_128_PER_SEC                0x70
#define SPIISOLATOR_PRESSURE3_BIT_MASK_PM_PRC_1_PER_SEC                   0x00
#define SPIISOLATOR_PRESSURE3_BIT_MASK_PM_PRC_2_PER_SEC                   0x01
#define SPIISOLATOR_PRESSURE3_BIT_MASK_PM_PRC_4_PER_SEC                   0x02
#define SPIISOLATOR_PRESSURE3_BIT_MASK_PM_PRC_8_PER_SEC                   0x03
#define SPIISOLATOR_PRESSURE3_BIT_MASK_PM_PRC_16_PER_SEC                  0x04
#define SPIISOLATOR_PRESSURE3_BIT_MASK_PM_PRC_32_PER_SEC                  0x05
#define SPIISOLATOR_PRESSURE3_BIT_MASK_PM_PRC_64_PER_SEC                  0x06
#define SPIISOLATOR_PRESSURE3_BIT_MASK_PM_PRC_128_PER_SEC                 0x07
/** \} */

/**
 * \defgroup BIT MASK - Temperature Configuration
 * \{
 */
#define SPIISOLATOR_PRESSURE3_BIT_MASK_TMP_EXT_INTERNAL_SENSOR            0x00
#define SPIISOLATOR_PRESSURE3_BIT_MASK_TMP_EXT_EXTERNAL_SENSOR            0x80
#define SPIISOLATOR_PRESSURE3_BIT_MASK_TMP_RATE_1_PER_SEC                 0x00
#define SPIISOLATOR_PRESSURE3_BIT_MASK_TMP_RATE_2_PER_SEC                 0x10
#define SPIISOLATOR_PRESSURE3_BIT_MASK_TMP_RATE_4_PER_SEC                 0x20
#define SPIISOLATOR_PRESSURE3_BIT_MASK_TMP_RATE_8_PER_SEC                 0x30
#define SPIISOLATOR_PRESSURE3_BIT_MASK_TMP_RATE_16_PER_SEC                0x40
#define SPIISOLATOR_PRESSURE3_BIT_MASK_TMP_RATE_32_PER_SEC                0x50
#define SPIISOLATOR_PRESSURE3_BIT_MASK_TMP_RATE_64_PER_SEC                0x60
#define SPIISOLATOR_PRESSURE3_BIT_MASK_TMP_RATE_128_PER_SEC               0x70
#define SPIISOLATOR_PRESSURE3_BIT_MASK_TMP_PRC_1_PER_SEC                  0x00
#define SPIISOLATOR_PRESSURE3_BIT_MASK_TMP_PRC_2_PER_SEC                  0x01
#define SPIISOLATOR_PRESSURE3_BIT_MASK_TMP_PRC_4_PER_SEC                  0x02
#define SPIISOLATOR_PRESSURE3_BIT_MASK_TMP_PRC_8_PER_SEC                  0x03
#define SPIISOLATOR_PRESSURE3_BIT_MASK_TMP_PRC_16_PER_SEC                 0x04
#define SPIISOLATOR_PRESSURE3_BIT_MASK_TMP_PRC_32_PER_SEC                 0x05
#define SPIISOLATOR_PRESSURE3_BIT_MASK_TMP_PRC_64_PER_SEC                 0x06
#define SPIISOLATOR_PRESSURE3_BIT_MASK_TMP_PRC_128_PER_SEC                0x07
/** \} */

/**
 * \defgroup BIT MASK - Sensor Operating Mode and Status
 * \{
 */
#define SPIISOLATOR_PRESSURE3_BIT_MASK_MEAS_CFG_COEF_RDY_AVB                      0x80
#define SPIISOLATOR_PRESSURE3_BIT_MASK_MEAS_CFG_COEF_RDY_NO_AVB                   0x00
#define SPIISOLATOR_PRESSURE3_BIT_MASK_MEAS_CFG_SENSOR_RDY_CMP                    0x40
#define SPIISOLATOR_PRESSURE3_BIT_MASK_MEAS_CFG_SENSOR_RDY_NO_CMP                 0x00
#define SPIISOLATOR_PRESSURE3_BIT_MASK_MEAS_CFG_TMP_RDY                           0x20
#define SPIISOLATOR_PRESSURE3_BIT_MASK_MEAS_CFG_PRS_RDY                           0x10
#define SPIISOLATOR_PRESSURE3_BIT_MASK_MEAS_CFG_MEAS_CTRL_IDLE                    0x00
#define SPIISOLATOR_PRESSURE3_BIT_MASK_MEAS_CFG_MEAS_CTRL_PRS                     0x01
#define SPIISOLATOR_PRESSURE3_BIT_MASK_MEAS_CFG_MEAS_CTRL_TMP                     0x02
#define SPIISOLATOR_PRESSURE3_BIT_MASK_MEAS_CFG_MEAS_CTRL_CNT_PRS                 0x05
#define SPIISOLATOR_PRESSURE3_BIT_MASK_MEAS_CFG_MEAS_CTRL_CNT_TMP                 0x06
#define SPIISOLATOR_PRESSURE3_BIT_MASK_MEAS_CFG_MEAS_CTRL_CNT_PRS_TMP             0x07
/** \} */

/**
 * \defgroup BIT MASK -  Interrupt and FIFO configuration
 * \{
 */
#define SPIISOLATOR_PRESSURE3_BIT_MASK_CFG_REG_INT_HL_LOW                         0x00
#define SPIISOLATOR_PRESSURE3_BIT_MASK_CFG_REG_INT_HL_HIGH                        0x80
#define SPIISOLATOR_PRESSURE3_BIT_MASK_CFG_REG_INT_FIFO_DISABLE                   0x00
#define SPIISOLATOR_PRESSURE3_BIT_MASK_CFG_REG_INT_FIFO_ENABLE                    0x40
#define SPIISOLATOR_PRESSURE3_BIT_MASK_CFG_REG_INT_TMP_DISABLE                    0x00
#define SPIISOLATOR_PRESSURE3_BIT_MASK_CFG_REG_INT_TMP_ENABLE                     0x20
#define SPIISOLATOR_PRESSURE3_BIT_MASK_CFG_REG_INT_PRS_DISABLE                    0x00
#define SPIISOLATOR_PRESSURE3_BIT_MASK_CFG_REG_INT_PRS_ENABLE                     0x10
#define SPIISOLATOR_PRESSURE3_BIT_MASK_CFG_REG_T_SHIFT_NO_SHIFT                   0x00
#define SPIISOLATOR_PRESSURE3_BIT_MASK_CFG_REG_T_SHIFT_SHIFT                      0x08
#define SPIISOLATOR_PRESSURE3_BIT_MASK_CFG_REG_P_SHIFT_NO_SHIFT                   0x00
#define SPIISOLATOR_PRESSURE3_BIT_MASK_CFG_REG_P_SHIFT_SHIFT                      0x04
#define SPIISOLATOR_PRESSURE3_BIT_MASK_CFG_REG_FIFO_EN_DISABLE                    0x00
#define SPIISOLATOR_PRESSURE3_BIT_MASK_CFG_REG_FIFO_EN_ENABLE                     0x02
#define SPIISOLATOR_PRESSURE3_BIT_MASK_CFG_REG_SPI_MODE_DISABLE                   0x00
#define SPIISOLATOR_PRESSURE3_BIT_MASK_CFG_REG_SPI_MODE_ENABLE                    0x01
/** \} */

/**
 * \defgroup BIT MASK -  Interrupt Status
 * \{
 */
#define SPIISOLATOR_PRESSURE3_BIT_MASK_INT_STS_INT_FIFO_FULL_NO_ACTIVE            0x00
#define SPIISOLATOR_PRESSURE3_BIT_MASK_INT_STS_INT_FIFO_FULL_ACTIVE               0x04
#define SPIISOLATOR_PRESSURE3_BIT_MASK_INT_STS_INT_TMP_NO_ACTIVE                  0x00
#define SPIISOLATOR_PRESSURE3_BIT_MASK_INT_STS_INT_TMP_ACTIVE                     0x02
#define SPIISOLATOR_PRESSURE3_BIT_MASK_INT_STS_INT_PRS_NO_ACTIVE                  0x00
#define SPIISOLATOR_PRESSURE3_BIT_MASK_INT_STS_INT_PRS_ACTIVE                     0x01
/** \} */

/**
 * \defgroup BIT MASK -  FIFO Status
 * \{
 */
#define SPIISOLATOR_PRESSURE3_BIT_MASK_FIFO_STS_FIFO_FULL_NO                      0x00
#define SPIISOLATOR_PRESSURE3_BIT_MASK_FIFO_STS_FIFO_FULL_FULL                    0x02
#define SPIISOLATOR_PRESSURE3_BIT_MASK_FIFO_STS_FIFO_EMPTY_NO                     0x00
#define SPIISOLATOR_PRESSURE3_BIT_MASK_FIFO_STS_FIFO_EMPTY_EMPTY                  0x01
/** \} */

/**
 * \defgroup BIT MASK - Soft Reset and FIFO flush
 * \{
 */
#define SPIISOLATOR_PRESSURE3_BIT_MASK_RESET_SOFT_RST                             0x09
/** \} */

/**
 * \defgroup BIT MASK - Coefficients Source
 * \{
 */
#define SPIISOLATOR_PRESSURE3_BIT_MASK_TMP_COEF_SRCE_INTERNAL_SENSOR                      0x00
#define SPIISOLATOR_PRESSURE3_BIT_MASK_TMP_COEF_SRCE_EXTERNAL_SENSOR                      0x80
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief 
 */
typedef struct
{   

    uint8_t reg_address;
    uint8_t cmd;

} addr_cmd_t;


/**
 * @brief Click ctx object definition.
 */
typedef struct
{   
    digital_out_t cs;

    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} spiisolator_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} spiisolator_cfg_t;

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
void spiisolator_cfg_setup ( spiisolator_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param spiisolator Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
SPIISOLATOR_RETVAL spiisolator_init ( spiisolator_t *ctx, spiisolator_cfg_t *cfg );

/**
 * @brief Generic transfer function.
 *
 * @param ctx          Click object.
 * @param wr_buf       Write data buffer
 * @param wr_len       Number of byte in write data buffer
 * @param rd_buf       Read data buffer
 * @param rd_len       Number of byte in read data buffer
 *
 * @description Generic SPI transfer, for sending and receiving packages
 */
void spiisolator_generic_transfer 
( 
    spiisolator_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);


void spiisolator_write_cmd ( spiisolator_t *ctx, uint8_t cmd, uint8_t tx_data );

/**
 * @brief Write the byte of data function
 *
 * @param ctx                        Click object.
 * @param reg_address                8-bit register address
 * @param write_cmd                  write comman
 * @param write_data                 Byte of data to write
 *
 * @description Function writes the byte of data to the
 * targeted 8-bit register address of connected random I2C click
 * which is wired to the SPI Isolator Click board
 */
void spiisolator_write_byte ( spiisolator_t *ctx, uint8_t reg_address, uint8_t write_cmd, uint8_t write_data );

/**
 * @brief Read the byte of data function
 *
 * @param ctx                        Click object.
 * @param reg_address                8-bit register address
 * @param read_cmd                   read command
 *
 * @return  8-bit read data
 *
 * @description Function reads the byte of data from the
 * targeted 8-bit register address of connected random I2C click
 * which is wired to the SPI Isolator Click board
 */
uint8_t spiisolator_read_byte ( spiisolator_t *ctx, uint8_t reg_address, uint8_t read_cmd );

/**
 * @brief Write 16-bit data function
 *
 * @param reg_address                8-bit register address
 * @param write_cmd                  write command
 * @param write_data                 16-bit data to write
 *
 * @description Function writes the 16-bit data to the
 * targeted 8-bit register address of connected random I2C click
 * which is wired to the SPI Isolator Click board
 */
void spiisolator_write_data ( spiisolator_t *ctx, uint8_t reg_address, uint8_t write_cmd, uint16_t write_data );

/**
 * @brief Read 16-bit data function
 * @param reg_address                8-bit register address
 * @param read_cmd                   read command
 * 
 * @return 16-bit read data
 *
 * @description Function reads the 16-bit data from the
 * targeted 8-bit register address of connected random I2C click
 * which is wired to the SPI Isolator Click board
 */
uint16_t spiisolator_read_data ( spiisolator_t *ctx, uint8_t reg_address, uint8_t read_cmd );

/**
 * @brief Sequential write function
 *
 * @param reg_address                8-bit register address
 * @param write_cmd                  write command
 * @param write_data                 pointer to the data to be written
 * @param n_bytes                    number of bytes to be written
 *
 * @description function writes a sequential data starting from the
 * targeted 8-bit register address of connected random I2C click
 * which is wired to the SPI Isolator Click board
 */
void spiisolator_write_bytes ( spiisolator_t *ctx, uint8_t reg_address, uint8_t write_cmd, uint8_t *write_data, uint16_t n_bytes );

/**
 * @brief Sequential read function
 *
 * @param reg_address                8-bit register address
 * @param read_cmd                   read command
 * @param read_data                  pointer to the memory location where data be stored
 * @param n_bytes                    number of bytes to be written
 *
 * @description Function read a sequential data starting from the
 * targeted 8-bit register address of connected random I2C click
 * which is wired to the SPI Isolator Click board
 */
void spiisolator_read_bytes ( spiisolator_t *ctx,uint8_t reg_address, uint8_t read_cmd, uint8_t *read_data, uint16_t n_bytes );

#ifdef __cplusplus
}
#endif
#endif  // _SPIISOLATOR_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
