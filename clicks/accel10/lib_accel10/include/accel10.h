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
 * \brief This file contains API for Accel 10 Click driver.
 *
 * \addtogroup accel10 Accel 10 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ACCEL10_H
#define ACCEL10_H

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
#define ACCEL10_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.it1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.it2 = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define ACCEL10_MASTER_I2C 0
#define ACCEL10_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ACCEL10_RETVAL  uint8_t

#define ACCEL10_OK           0x00
#define ACCEL10_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup i2c_address I2C slave address
 * \{
 */
#define ACCEL10_SLAVE_ADDRESS_GND                            0x18
#define ACCEL10_SLAVE_ADDRESS_VCC                            0x19
/** \} */

/**
 * \defgroup reg Register address
 * \{
 */
#define ACCEL10_REG_OUT_T_L                                  0x0D
#define ACCEL10_REG_OUT_T_H                                  0x0E
#define ACCEL10_REG_WHO_AM_I                                 0x0F
#define ACCEL10_REG_CTRL1                                    0x20
#define ACCEL10_REG_CTRL2                                    0x21
#define ACCEL10_REG_CTRL3                                    0x22
#define ACCEL10_REG_CTRL4_INT1_PAD_CTRL                      0x23
#define ACCEL10_REG_CTRL5_INT2_PAD_CTRL                      0x24
#define ACCEL10_REG_CTRL6                                    0x25
#define ACCEL10_REG_OUT_T                                    0x26
#define ACCEL10_REG_STATUS                                   0x27
#define ACCEL10_REG_OUT_X_L                                  0x28
#define ACCEL10_REG_OUT_X_H                                  0x29
#define ACCEL10_REG_OUT_Y_L                                  0x2A
#define ACCEL10_REG_OUT_Y_H                                  0x2B
#define ACCEL10_REG_OUT_Z_L                                  0x2C
#define ACCEL10_REG_OUT_Z_H                                  0x2D
#define ACCEL10_REG_FIFO_CTRL                                0x2E
#define ACCEL10_REG_FIFO_SAMPLES                             0x2F
#define ACCEL10_REG_TAP_THS_X                                0x30
#define ACCEL10_REG_TAP_THS_Y                                0x31
#define ACCEL10_REG_TAP_THS_Z                                0x32
#define ACCEL10_REG_INT_DUR                                  0x33
#define ACCEL10_REG_WAKE_UP_THS                              0x34
#define ACCEL10_REG_WAKE_UP_DUR                              0x35
#define ACCEL10_REG_FREE_FALL                                0x36
#define ACCEL10_REG_STATUS_DUP                               0x37
#define ACCEL10_REG_WAKE_UP_SRC                              0x38
#define ACCEL10_REG_TAP_SRC                                  0x39
#define ACCEL10_REG_SIXD_SRC                                 0x3A
#define ACCEL10_REG_ALL_INT_SRC                              0x3B
#define ACCEL10_REG_X_OFS_USR                                0x3C
#define ACCEL10_REG_Y_OFS_USR                                0x3D
#define ACCEL10_REG_Z_OFS_USR                                0x3E
#define ACCEL10_REG_CTRL_REG7                                0x3F
/** \} */
 
/**
 * \defgroup who_am_i ACCEL10_WHO_AM_I
 * \{
 */
#define ACCEL10_WHO_AM_I_DEFAULT_VALUE                       0x44
/** \} */

/**
 * \defgroup config_reg Configuration ACCEL10_CTRL1 register
 * \{
 */

/**
 * \defgroup config LP_MODE
 * \{
 */
#define ACCEL10_LP_MODE_1                                    0x00
#define ACCEL10_LP_MODE_2                                    0x01
#define ACCEL10_LP_MODE_3                                    0x02
#define ACCEL10_LP_MODE_4                                    0x03
/** \} */

/**
 * \defgroup config MODE
 * \{
 */
#define ACCEL10_MODE_LOW_POWER                               0x00
#define ACCEL10_MODE_HIGH_PERF                               0x04
#define ACCEL10_MODE_SINGLE_CONV                             0x08
/** \} */

/**
 * \defgroup config ODR
 * \{
 */
#define ACCEL10_ODR_POWER_DOWN                               0x00
#define ACCEL10_ODR_12_5_1_6HZ                               0x10
#define ACCEL10_ODR_12_5Hz                                   0x20
#define ACCEL10_ODR_25Hz                                     0x30
#define ACCEL10_ODR_50Hz                                     0x40
#define ACCEL10_ODR_100Hz                                    0x50
#define ACCEL10_ODR_200Hz                                    0x60
#define ACCEL10_ODR_400_200Hz                                0x70
#define ACCEL10_ODR_800_200Hz                                0x80
#define ACCEL10_ODR_1600_200Hz                               0x90
/** \} */

/** \} */

/**
 * \defgroup config_reg_ctrl2 Configuration ACCEL10_CTRL2 register
 * \{
 */

/**
 * \defgroup config SIM
 * \{
 */
#define ACCEL10_SIM_4_WIRE                                   0x00
#define ACCEL10_SIM_3_WIRE                                   0x01
/** \} */

/**
 * \defgroup config I2C_DISABLE
 * \{
 */
#define ACCEL10_I2C_ENABLE_I2C_AND_SPI                       0x00
#define ACCEL10_I2C_ENABLE_SPI_ONLY                          0x02
/** \} */

/**
 * \defgroup config IF_ADD_INC
 * \{
 */
#define ACCEL10_IF_ADD_INC_DISABLE                           0x00
#define ACCEL10_IF_ADD_INC_ENABLE                            0x04
/** \} */
 
/**
 * \defgroup config BDU
 * \{
 */
#define ACCEL10_BDU_CONTINUOUS_UPDATE                        0x00
#define ACCEL10_BDU_NOT_UPDATE_MSB_LSB                       0x08
/** \} */

/**
 * \defgroup config CS_PU_DISC
 * \{
 */
#define ACCEL10_CS_PU_DISC_CONNECT                           0x00
#define ACCEL10_CS_PU_DISC_DISCONNECT                        0x10
/** \} */

/**
 * \defgroup config SOFT_RESET
 * \{
 */
#define  ACCEL10_SOFT_RESET_DISABLE                          0x00
#define  ACCEL10_SOFT_RESET_ENABLE                           0x40
/** \} */

/**
 * \defgroup config BOOT
 * \{
 */
#define ACCEL10_BOOT_DISABLE                                 0x00
#define ACCEL10_BOOT_ENABLE                                  0x80
/** \} */

/** \} */

/**
 * \defgroup config_reg_ctrl3 Configuration ACCEL10_CTRL3 register
 * \{
 */

/**
 * \defgroup config SLP_MODE_1
 * \{
 */
#define ACCEL10_SLP_MODE_1_CONV_START                        0x01
/** \} */

/**
 * \defgroup config SLP_MODE_SEL
 * \{
 */
#define ACCEL10_SLP_MODE_SEL_EN_INT2                         0x00
#define ACCEL10_SLP_MODE_SEL_EN_MODE1                        0x02
/** \} */
 
/**
 * \defgroup config H_LACTIVE
 * \{
 */
#define ACCEL10_H_LACTIVE_HIGH                               0x00
#define ACCEL10_H_LACTIVE_LOW                                0x08
/** \} */

/**
 * \defgroup config LIR
 * \{
 */
#define ACCEL10_LIR_NOT_LATCHED                              0x00
#define ACCEL10_LIR_LATCHED                                  0x10
/** \} */

/**
 * \defgroup config PP_OD
 * \{
 */
#define ACCEL10_PP_OD_PUSH_PULL                              0x00
#define ACCEL10_PP_OD_OPEN_DRAIN                             0x20
/** \} */

/**
 * \defgroup config ST
 * \{
 */
#define ACCEL10_ST_NORMAL                                    0x00
#define ACCEL10_ST_POSITIVE                                  0x40
#define ACCEL10_ST_NEGATIVE                                  0x80
/** \} */

/** \} */
 
/**
 * \defgroup config_reg_ctrl4 Configuration ACCEL10_CTRL4_INT1_PAD_CTRL register
 * \{
 */
/**
 * \defgroup config INT1_DRDY
 * \{
 */
#define ACCEL10_INT1_DRDY_DISABLE                            0x00
#define ACCEL10_INT1_DRDY_ENABLE                             0x01
/** \} */

/**
 * \defgroup config INT1_FTH
 * \{
 */
#define ACCEL10_INT1_FTH_DISABLE                             0x00
#define ACCEL10_INT1_FTH_ENABLE                              0x02
/** \} */

/**
 * \defgroup config INT1_DIFF5
 * \{
 */
#define ACCEL10_INT1_DIFF5_DISABLE                           0x00
#define ACCEL10_INT1_DIFF5_ENABLE                            0x04
/** \} */

/**
 * \defgroup config INT1_TAP
 * \{
 */
#define ACCEL10_INT1_TAP_DISABLE                             0x00
#define ACCEL10_INT1_TAP_ENABLE                              0x08
/** \} */

/**
 * \defgroup config INT1_FF
 * \{
 */
#define ACCEL10_INT1_FF_DISABLE                              0x00
#define ACCEL10_INT1_FF_ENABLE                               0x10
/** \} */

/**
 * \defgroup config INT1_WU
 * \{
 */
#define ACCEL10_INT1_WU_DISABLE                              0x00
#define ACCEL10_INT1_WU_ENABLE                               0x20
/** \} */

/**
 * \defgroup config INT1_SINGLE_TAP
 * \{
 */
#define ACCEL10_INT1_SINGLE_TAP_DISABLE                      0x00
#define ACCEL10_INT1_SINGLE_TAP_ENABLE                       0x40
/** \} */

/**
 * \defgroup config INT1_6D
 * \{
 */
#define ACCEL10_INT1_6D_DISABLE                              0x00
#define ACCEL10_INT1_6D_ENABLE                               0x80
/** \} */
/** \} */

/**
 * \defgroup config_reg_ctrl5 Configuration ACCEL10_CTRL5_INT2_PAD_CTRL register
 * \{
 */
/**
 * \defgroup config INT2_DRDY
 * \{
 */
#define ACCEL10_INT2_DRDY_DISABLE                            0x00
#define ACCEL10_INT2_DRDY_ENABLE                             0x01
/** \} */
 
/**
 * \defgroup config INT2_FTH
 * \{
 */
#define ACCEL10_INT2_FTH_DISABLE                             0x00
#define ACCEL10_INT2_FTH_ENABLE                              0x02
/** \} */

/**
 * \defgroup config INT2_DIFF5
 * \{
 */
#define ACCEL10_INT2_DIFF5_DISABLE                           0x00
#define ACCEL10_INT2_DIFF5_ENABLE                            0x04
/** \} */

/**
 * \defgroup config INT2_OVR
 * \{
 */
#define ACCEL10_INT2_OVR_DISABLE                             0x00
#define ACCEL10_INT2_OVR_ENABLE                              0x08
/** \} */

/**
 * \defgroup config INT2_DRDY_T
 * \{
 */
#define ACCEL10_INT2_DRDY_T_DISABLE                          0x00
#define ACCEL10_INT2_DRDY_T_ENABLE                           0x10
/** \} */

/**
 * \defgroup config INT2_BOOT
 * \{
 */
#define ACCEL10_INT2_BOOT_DISABLE                            0x00
#define ACCEL10_INT2_BOOT_ENABLE                             0x20
/** \} */

/**
 * \defgroup config INT2_SLEEP_CHG
 * \{
 */
#define ACCEL10_INT2_SLEEP_CHG_DISABLE                       0x00
#define ACCEL10_INT2_SLEEP_CHG_ENABLE                        0x40
/** \} */

/**
 * \defgroup config INT2_SLEEP_STATE
 * \{
 */
#define ACCEL10_INT2_SLEEP_STATE_DISABLE                     0x00
#define ACCEL10_INT2_SLEEP_STATE_ENABLE                      0x80
/** \} */
/** \} */

/**
 * \defgroup config_reg_ctrl6 Configuration ACCEL10_CTRL6 register
 * \{
 */
/**
 * \defgroup config LOW_NOISE
 * \{
 */
#define ACCEL10_LOW_NOISE_DISABLE                            0x00
#define ACCEL10_LOW_NOISE_ENABLE                             0x04
/** \} */

/**
 * \defgroup config FSD
 * \{
 */
#define ACCEL10_FSD_LOW_PASS                                 0x00
#define ACCEL10_FSD_HIGH_PASS                                0x08
/** \} */

/**
 * \defgroup config FS
 * \{
 */
#define ACCEL10_FS_2G                                        0x00
#define ACCEL10_FS_4G                                        0x10
#define ACCEL10_FS_8G                                        0x20
#define ACCEL10_FS_16G                                       0x30
/** \} */

/**
 * \defgroup config BW_FILT
 * \{
 */
#define ACCEL10_BW_FILT_ODR2                                 0x00
#define ACCEL10_BW_FILT_ODR4                                 0x40
#define ACCEL10_BW_FILT_ODR10                                0x80
#define ACCEL10_BW_FILT_ODR20                                0xC0
/** \} */
/** \} */

/**
 * \defgroup status Status
 * \{
 */
#define ACCEL10_STATUS_DATA_READY                            0x01
/** \} */
 
/**
 * \defgroup error_status Check error
 * \{
 */
#define ACCEL10_ERROR                                        0x00
#define ACCEL10_SUCCESS                                      0x01
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
typedef uint8_t  accel10_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *accel10_master_io_t )( struct accel10_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct accel10_s
{
    // Input pins 

    digital_out_t cs;
    digital_in_t it1;
    digital_in_t it2;
    
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

    uint8_t slave_address;
    pin_name_t chip_select;
    accel10_master_io_t  write_f;
    accel10_master_io_t  read_f;
    accel10_select_t master_sel;

} accel10_t;

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

    pin_name_t it1;
    pin_name_t it2;

    // static variable 

   uint32_t i2c_speed;
   uint8_t  i2c_address;

   uint32_t spi_speed;
   spi_master_mode_t  spi_mode;
   spi_master_chip_select_polarity_t cs_polarity;

   accel10_select_t sel;

} accel10_cfg_t;

/**
 * @brief Accel data structure definition.
 */
typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;
}
accel10_data_t;

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
void accel10_cfg_setup ( accel10_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
ACCEL10_RETVAL accel10_init ( accel10_t *ctx, accel10_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Accel 10 Click.
 * @note
 *    Click default configuration:
 * -------------------------------------------------
 * 
 * <pre>
 * - Set Low-power mode selection           : Low-Power Mode 2 (14-bit resolution);
 * - Set Mode selection                     : Low-Power Mode (12/14-bit resolution);
 * - Set Data rate configuration            : Low-Power mode 100 Hz;
 * </pre>
 * 
 * <pre>
 *    reg     : ACCEL10_REG_CTRL1
 * -------------------------------------------------
 *    tx_data : ACCEL10_LP_MODE_2 
 *            | ACCEL10_MODE_LOW_POWER 
 *            | ACCEL10_ODR_100Hz
 * </pre>
 * 
 * <pre>
 * - Set Low-noise configuration            : Disable;
 * - Set Filtered data type selection       : Low-pass filter path selected;
 * - Set Full-scale selection               : ±2 g;
 * - Set Digital filtering cutoff selection : ODR/2;
 * </pre>
 * 
 * <pre>
 *    reg     : ACCEL10_REG_CTRL6
 * -------------------------------------------------
 *    tx_data : ACCEL10_LOW_NOISE_DISABLE 
 *            | ACCEL10_FSD_LOW_PASS
              | ACCEL10_FS_2G 
              | ACCEL10_BW_FILT_ODR2
 * </pre>
 */
void accel10_default_cfg ( accel10_t *ctx );

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
void accel10_generic_write ( accel10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx        Click object.
 * @param reg        Register address.
 * @param data_buf   Data buf to be written.
 * @param len        Number of the bytes in data buf.
 *
 * @description This function reads data from the desired register.
 */
void accel10_generic_read ( accel10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Check ID function.
 *
 * @param ctx  Click object.
 * 
 * @return ID status:
 * - 0 ( ACCEL10_ERROR )   : Check ID Error;
 * - 1 ( ACCEL10_SUCCESS ) : Check ID Success;
 *
 * @description This function check device ID by read ID value 
 * from the sensor ACCEL10_WHO_AM_I register address
 * of LIS2DW12 3-axis MEMS acceleromete on Accel 10 Click board.
 */
ACCEL10_RETVAL accel10_check_id ( accel10_t *ctx );

/**
 * @brief Check data ready function.
 *
 * @param ctx  Click object.
 * 
 * @return Data ready:
 * - 0 : Not ready;
 * - 1 : X-, Y- and Z-axis new data available;
 *
 * @description This function check accel data ready
 * of LIS2DW12 3-axis MEMS acceleromete on Accel 10 Click board.
 */
uint8_t accel10_check_data_ready ( accel10_t *ctx );

/**
 * @brief Soft reset function.
 *
 * @param ctx  Click object.
 *
 * @description This function soft reset acts as reset for all control registers
 * of LIS2DW12 3-axis MEMS acceleromete on Accel 10 Click board.
 */
void accel10_soft_reset ( accel10_t *ctx );

/**
 * @brief Read Accel data function.
 *
 * @param ctx            Click object.
 * @param p_accel_data   Pointer to memory location where Accel data be stored.
 *
 * @description This function read Accel data X-axis, Y-axis data and Z-axis data 
 * from the 6 targeted starts from ACCEL10_OUT_X_L register address
 * of LIS2DW12 3-axis MEMS acceleromete on Accel 10 Click board.
 */
void accel10_get_data ( accel10_t *ctx, accel10_data_t *p_accel_data );

/**
 * @brief Read temperature function.
 *
 * @param ctx  Click object.
 * 
 * @return temperature ( degrees Celsius )
 *
 * @description This function read temperature data in degrees Celsius
 * of LIS2DW12 3-axis MEMS acceleromete on Accel 10 Click board.
 */
int8_t accel10_read_temperature ( accel10_t *ctx );

/**
 * @brief Get interrupt 1 ststus function.
 *
 * @param ctx  Click object.
 * 
 * @return
 * Interrupt 1 state:
 * - 0 : No active;
 * - 1 : Active;
 *
 * @description This function check interrupt 1 state by return state
 * of the PWM pin of Accel 10 Click board.
 */
uint8_t accel10_check_it1 ( accel10_t *ctx );

/**
 * @brief Get interrupt 2 ststus function.
 *
 * @param ctx  Click object.
 * 
 * @return
 * Interrupt 2 state:
 * - 0 : No active;
 * - 1 : Active;
 *
 * @description This function check interrupt 1 state by return state
 * of the INT pin of Accel 10 Click board.
 */
uint8_t accel10_check_it2 ( accel10_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _ACCEL10_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
