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
 * \brief This file contains API for Accel 14 Click driver.
 *
 * \addtogroup accel14 Accel 14 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ACCEL14_H
#define ACCEL14_H

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

#define ACCEL14_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.i2    = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.i1    = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ACCEL14_RETVAL  uint8_t

#define ACCEL14_OK           0x00
#define ACCEL14_INIT_ERROR   0xFF
/** \} */
 
/**
 * \defgroup register_map  Register map
 * \{
 */
#define ACCEL14_REG_PIN_CTRL                      0x02
#define ACCEL14_REG_FIFO_CTRL1                    0x07
#define ACCEL14_REG_FIFO_CTRL2                    0x08
#define ACCEL14_REG_FIFO_CTRL3                    0x09
#define ACCEL14_REG_FIFO_CTRL4                    0x0A
#define ACCEL14_REG_COUNTER_BDR_REG1              0x0B
#define ACCEL14_REG_COUNTER_BDR_REG2              0x0C
#define ACCEL14_REG_INT1_CTRL                     0x0D
#define ACCEL14_REG_INT2_CTRL                     0x0E
#define ACCEL14_REG_WHO_AM_I                      0x0F
#define ACCEL14_REG_CTRL1_XL                      0x10
#define ACCEL14_REG_CTRL3_C                       0x12
#define ACCEL14_REG_CTRL4_C                       0x13
#define ACCEL14_REG_CTRL5_C                       0x14
#define ACCEL14_REG_CTRL6_C                       0x15
#define ACCEL14_REG_CTRL7_C                       0x16
#define ACCEL14_REG_CTRL8_XL                      0x17
#define ACCEL14_REG_CTRL10_C                      0x19
#define ACCEL14_REG_ALL_INT_SRC                   0x1A
#define ACCEL14_REG_WAKE_UP_SRC                   0x1B
#define ACCEL14_REG_STATUS_REG                    0x1E
#define ACCEL14_REG_OUT_TEMP_L                    0x20
#define ACCEL14_REG_OUT_TEMP_H                    0x21
#define ACCEL14_REG_OUTX_L_A                      0x28
#define ACCEL14_REG_OUTX_H_A                      0x29
#define ACCEL14_REG_OUTY_L_A                      0x2A
#define ACCEL14_REG_OUTY_H_A                      0x2B
#define ACCEL14_REG_OUTZ_L_A                      0x2C
#define ACCEL14_REG_OUTZ_H_A                      0x2D
#define ACCEL14_REG_FIFO_STATUS1                  0x3A
#define ACCEL14_REG_FIFO_STATUS2                  0x3B
#define ACCEL14_REG_TIMESTAMP0                    0x40
#define ACCEL14_REG_TIMESTAMP1                    0x41
#define ACCEL14_REG_TIMESTAMP2                    0x42
#define ACCEL14_REG_TIMESTAMP3                    0x43
#define ACCEL14_REG_SLOPE_EN                      0x56
#define ACCEL14_REG_INTERRUPTS_EN                 0x58
#define ACCEL14_REG_WAKE_UP_THS                   0x5B
#define ACCEL14_REG_WAKE_UP_DUR                   0x5C
#define ACCEL14_REG_MD1_CFG                       0x5E
#define ACCEL14_REG_MD2_CFG                       0x5F
#define ACCEL14_REG_INTERNAL_FREQ_FINE            0x63
#define ACCEL14_REG_X_OFS_USR                     0x73
#define ACCEL14_REG_Y_OFS_USR                     0x74
#define ACCEL14_REG_Z_OFS_USR                     0x75
#define ACCEL14_REG_FIFO_DATA_OUT_TAG             0x78
#define ACCEL14_REG_FIFO_DATA_OUT_X_L             0x79
#define ACCEL14_REG_FIFO_DATA_OUT_X_H             0x7A
#define ACCEL14_REG_FIFO_DATA_OUT_Y_L             0x7B
#define ACCEL14_REG_FIFO_DATA_OUT_Y_H             0x7C
#define ACCEL14_REG_FIFO_DATA_OUT_Z_L             0x7D
#define ACCEL14_REG_FIFO_DATA_OUT_Z_H             0x7E
/** \} */
 
/**
 * \defgroup id_value  ID value
 * \{
 */
#define ACCEL14_ID_VALUE                          0x7B
/** \} */
 
/**
 * \defgroup ctrl1_xl  Ctrl1 xl
 * \{
 */
#define ACCEL14_CTRL1_XL_POWER_BIT_MASK           0xE0
#define ACCEL14_CTRL1_XL_POWER_DOWN               0x00
#define ACCEL14_CTRL1_XL_POWER_UP                 0xA0

#define ACCEL14_CTRL1_XL_HIGH_RES_BIT_MASK        0x02
#define ACCEL14_CTRL1_XL_HIGH_RES_FS              0x00
#define ACCEL14_CTRL1_XL_HIGH_RES_SS              0x02

#define ACCEL14_CTRL1_XL_GSEL_BIT_MASK            0x0C
#define ACCEL14_CTRL1_XL_GSEL_2G                  0x00
#define ACCEL14_CTRL1_XL_GSEL_16G                 0x04
#define ACCEL14_CTRL1_XL_GSEL_4G                  0x08
#define ACCEL14_CTRL1_XL_GSEL_8G                  0x0C

#define ACCEL14_COEF_RES_2G                       0.061
#define ACCEL14_COEF_RES_4G                       0.122
#define ACCEL14_COEF_RES_8G                       0.244
#define ACCEL14_COEF_RES_16G                      0.488
/** \} */
 
/**
 * \defgroup ctrl3_c  Ctrl3 c
 * \{
 */
#define ACCEL14_CTRL3_C_BOOT_NORMAL               0x00
#define ACCEL14_CTRL3_C_BOOT_REBOOT               0x80
#define ACCEL14_CTRL3_C_BDU_CONTINUOUS            0x00
#define ACCEL14_CTRL3_C_BDU_READ_UPDATE           0x40
#define ACCEL14_CTRL3_C_INT_ACTIVE_HIGH           0x00
#define ACCEL14_CTRL3_C_INT_ACTIVE_LOW            0x20
#define ACCEL14_CTRL3_C_PP_OD_PUSH_PULL           0x00
#define ACCEL14_CTRL3_C_PP_OD_OPEN_DRAIN          0x10
#define ACCEL14_CTRL3_C_SIM_SPI_4_WIRE            0x00
#define ACCEL14_CTRL3_C_SIM_SPI_3_WIRE            0x08
#define ACCEL14_CTRL3_C_IF_INC_DISABLE            0x00
#define ACCEL14_CTRL3_C_IF_INC_ENABLE             0x04
#define ACCEL14_CTRL3_C_SW_RESET_DIS              0x00
#define ACCEL14_CTRL3_C_SW_RESET_EN               0x01
/** \} */
 
/**
 * \defgroup ctrl4_c  Ctrl4 c
 * \{
 */
#define ACCEL14_CTRL4_C_INT1_2_DIV                0x00
#define ACCEL14_CTRL4_C_INT1_2_LOGIC_INT1         0x20
#define ACCEL14_CTRL4_C_DRDY_MASK_DIS             0x00
#define ACCEL14_CTRL4_C_DRDY_MASK_EN              0x10
#define ACCEL14_CTRL4_C_SPI_I2C_EN                0x00
#define ACCEL14_CTRL4_C_I2C_DISABLE               0x04
#define ACCEL14_CTRL4_C_3REGOUT_EN                0x00
#define ACCEL14_CTRL4_C_1AX_EN                    0x01
/** \} */
 
/**
 * \defgroup ctrl5_c  Ctrl5 c
 * \{
 */
#define ACCEL14_CTRL5_C_ROUNDING_NO               0x00
#define ACCEL14_CTRL5_C_ROUNDING_EN               0x20
#define ACCEL14_CTRL5_C_ST_NORMAL                 0x00
#define ACCEL14_CTRL5_C_ST_POSITIVE               0x01
#define ACCEL14_CTRL5_C_ST_NEGATIVE               0x02
/** \} */
 
/**
 * \defgroup ctrl6_c  Ctrl6 c
 * \{
 */
#define ACCEL14_CTRL6_C_USR_OFF_W_10              0x00
#define ACCEL14_CTRL6_C_USR_OFF_W_2               0x08
#define ACCEL14_CTRL6_C_SEL_3_AXES                0x00
#define ACCEL14_CTRL6_C_SEL_X_AXES                0x01
#define ACCEL14_CTRL6_C_SEL_Y_AXES                0x02
#define ACCEL14_CTRL6_C_SEL_Z_AXES                0x03
/** \} */
 
/**
 * \defgroup ctrl7_c  Ctrl7 c
 * \{
 */
#define ACCEL14_CTRL7_C_USR_OFF_OUT               0x00
#define ACCEL14_CTRL7_C_USR_ON_OUT                0x02
/** \} */
 
/**
 * \defgroup ctrl8_xl  Ctrl8 xl
 * \{
 */
#define ACCEL14_CTRL8_ODR_4                       0x00
#define ACCEL14_CTRL8_ODR_10                      0x20
#define ACCEL14_CTRL8_ODR_20                      0x40
#define ACCEL14_CTRL8_ODR_45                      0x60
#define ACCEL14_CTRL8_ODR_100                     0x80
#define ACCEL14_CTRL8_ODR_200                     0xA0
#define ACCEL14_CTRL8_ODR_400                     0xC0
#define ACCEL14_CTRL8_ODR_800                     0xE0
#define ACCEL14_CTRL8_HIGH_PASS_DIS               0x00
#define ACCEL14_CTRL8_HIGH_PASS_EN                0x10
#define ACCEL14_CTRL8_LPF2_HPF_DIS                0x00
#define ACCEL14_CTRL8_LPF2_HPF_EN                 0x08
/** \} */
 
/**
 * \defgroup ctrl10_c  Ctrl10 c
 * \{
 */
#define ACCEL14_CTRL10_TIMESTAMP_DIS              0x00
#define ACCEL14_CTRL10_TIMESTAMP_EN               0x20
/** \} */
 
/**
 * \defgroup check_id Check id
 * \{
 */
#define ACCEL14_CHECK_ID_ERROR                    0x00
#define ACCEL14_CHECK_ID_SUCCESS                  0x01
/** \} */
 
/**
 * \defgroup check_new_data Check new data
 * \{
 */
#define ACCEL14_STATUS_DATA_READY                 0x05
#define ACCEL14_STATUS_TEMP_READY                 0x04
#define ACCEL14_STATUS_ACCEL_READY                0x01
#define ACCEL14_NEW_DATA_NO_DATA                  0x00
#define ACCEL14_NEW_DATA_AVAILABLE                0x01
/** \} */
 
/**
 * \defgroup communication  Communication
 * \{
 */
#define ACCEL14_SPI_WRITE                         0x00
#define ACCEL14_SPI_READ                          0x80
/** \} */
 
/**
 * \defgroup dummy  Dummy
 * \{
 */
#define ACCEL14_DUMMY                             0x00
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

} accel14_accel_t;

typedef struct 
{
    float accel_x;
    float accel_y;
    float accel_z;

} accel14_accel_fs_xl_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Input pins 

    digital_in_t i1;
    digital_in_t i2;

    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} accel14_t;

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

    // Additional gpio pins 

    pin_name_t i2;
    pin_name_t i1;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} accel14_cfg_t;

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
void accel14_cfg_setup ( accel14_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param accel14 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ACCEL14_RETVAL accel14_init ( accel14_t *ctx, accel14_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Accel 14 click.
 */
void accel14_default_cfg ( accel14_t *ctx );

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
void accel14_generic_transfer 
( 
    accel14_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Generic write function.
 *
 * @param ctx  Click object.
 * @param reg                8-bit register address.
 * @param tx_data            Byte of data to write.
 *
 * @description The function write the byte of data
 * to the target 8-bit register address of 
 * IIS3DWB Ultra-wide bandwidth, low-noise, 3-axis digital vibration sensor
 * on Accel 14 Click board.
 */
void accel14_generic_write ( accel14_t *ctx, uint8_t reg, uint8_t tx_data );

/**
 * @brief Generic read function.
 *
 * @param ctx  Click object.
 * @param reg                8-bit register address.
 *
 * @return
 * 8-bit read data
 *
 * @description The function read the the byte of data
 * from the target 8-bit register address of
 * IIS3DWB Ultra-wide bandwidth, low-noise, 3-axis digital vibration sensor
 * on Accel 14 Click board.
 */
uint8_t accel14_generic_read ( accel14_t *ctx, uint8_t reg );

/**
 * @brief Generic read sequence function.
 *
 * @param ctx  Click object.
 * @param reg               8-bit register address.
 * @param p_tx_data         pointer to the memory location where data be stored.
 * @param n_bytes           number of bytes to be written.
 *
 * @description The function read a sequential data starting
 * from the targeted 8-bit register address of
 * IIS3DWB Ultra-wide bandwidth, low-noise, 3-axis digital vibration sensor
 * on Accel 14 Click board.
 */
void accel14_multi_read ( accel14_t *ctx, uint8_t reg, uint8_t *p_rx_data, uint8_t n_bytes );

/**
 * @brief Check communication function.
 *
 * @param ctx  Click object.
 * 
 * @retval
 * - 0x00 : Error.
 * - 0x01 : Success.
 *
 * @description The function check device ID
 * of IIS3DWB Ultra-wide bandwidth, low-noise, 3-axis digital vibration sensor
 * on Accel 14 Click board.
 */
uint8_t accel14_check_communication ( accel14_t *ctx );

/**
 * @brief Check accel data ready function.
 *
 * @param ctx  Click object.
 * 
 * @retval
 * - 0x00 : No set of data is available at temperature sensor output;.
 * - 0x01 : New set of data is available at temperature sensor output.
 *
 * @description The function check new set of data is available 
 * at accelerometer output
 * of IIS3DWB Ultra-wide bandwidth, low-noise, 3-axis digital vibration sensor
 * on Accel 14 Click board.
 */
uint8_t accel14_check_accel_data_ready ( accel14_t *ctx );

/**
 * @brief Check temperature data ready function.
 *
 * @param ctx  Click object.
 * 
 * @retval
 * - 0x00 : No set of data is available at temperature sensor output.
 * - 0x01 : New set of data is available at temperature sensor output.
 *
 * @description The function check new set of data is available
 * at temperature output
 * of IIS3DWB Ultra-wide bandwidth, low-noise, 3-axis digital vibration sensor
 * on Accel 14 Click board.
 */
uint8_t accel14_check_temp_data_ready ( accel14_t *ctx );

/**
 * @brief Get Accel data function.
 *
 * @param ctx  Click object.
 * @param accel_data
 * pointer to memory location where Accel data be stored
 *
 * @description Function read Accel, Gyro and Mag
 * X-axis, Y-axis data and Z-axis data from
 * of IIS3DWB Ultra-wide bandwidth, low-noise, 3-axis digital vibration sensor
 * on Accel 14 Click board.
 */
void accel14_get_data ( accel14_t *ctx, accel14_accel_t *accel_data );

/**
 * @brief Get temperature function.
 *
 * @param ctx  Click object.
 * 
 * @return
 * float temperature ( degrees Celsius )
 *
 * @description Function get temperature data in degrees Celsius
 * of IIS3DWB Ultra-wide bandwidth, low-noise, 3-axis digital vibration sensor
 * on Accel 14 Click board.
 */
float accel14_get_temperature ( accel14_t *ctx );

/**
 * @brief Read Accel data function
 *
 * @param ctx  Click object.
 * @param accel_fs
 * pointer to memory location where Accel data be stored
 *
 * @description Function read Accel data X-axis, Y-axis data and Z-axis
 * data from the 6 targeted starts from ACCEL10_OUT_X_L register address
 * of IIS3DWB Ultra-wide bandwidth, low-noise, 3-axis digital vibration sensor
 * on Accel 14 Click board.
 */
void accel14_read_accel ( accel14_t *ctx, accel14_accel_fs_xl_t *accel_fs );

/**
 * @brief Get interrupt 1 ststus function
 *
 * @param ctx  Click object.
 * 
 * @return
 * Interrupt 1 state:
 * - 0 : No active;
 * - 1 : Active;
 *
 * @description Function check interrupt 1 state by return state of the INT pin
 * of IIS3DWB Ultra-wide bandwidth, low-noise, 3-axis digital vibration sensor
 * on Accel 14 Click board.
*/
uint8_t accel14_check_int1 ( accel14_t *ctx );

/**
 * @brief Get interrupt 2 ststus function
 *
 * @param ctx  Click object.
 * 
 * @return
 * Interrupt 1 state:
 * - 0 : No active;
 * - 1 : Active;
 *
 * @description Function check interrupt 2 state by return state of the RST pin
 * of IIS3DWB Ultra-wide bandwidth, low-noise, 3-axis digital vibration sensor
 * on Accel 14 Click board.
*/
uint8_t accel14_check_int2 ( accel14_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _ACCEL14_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
