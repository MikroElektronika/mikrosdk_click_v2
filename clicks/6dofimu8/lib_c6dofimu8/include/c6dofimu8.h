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
 * \brief This file contains API for c6DOF IMU 8 Click driver.
 *
 * \addtogroup c6dofimu8 c6DOF IMU 8 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C6DOFIMU8_H
#define C6DOFIMU8_H

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

#define C6DOFIMU8_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.it2 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.it1 = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define C6DOFIMU8_MASTER_I2C 0
#define C6DOFIMU8_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C6DOFIMU8_RETVAL  uint8_t

#define C6DOFIMU8_OK           0x00
#define C6DOFIMU8_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup device_addr Device Addr
 * \{
 */
#define C6DOFIMU8_DEVICE_ADDR_LSB_LOW                    0x6A
#define C6DOFIMU8_DEVICE_ADDR_LSB_HIGH                   0x6B
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define C6DOFIMU8_FUNC_CFG_ACCESS_REG                    0x01
#define C6DOFIMU8_SENS_SYNC_TIME_FRAME_REG               0x04
#define C6DOFIMU8_SENS_SYNC_RES_RATIO_REG                0x05
#define C6DOFIMU8_FIFO_CTRL1_REG                         0x06
#define C6DOFIMU8_FIFO_CTRL2_REG                         0x07
#define C6DOFIMU8_FIFO_CTRL3_REG                         0x08
#define C6DOFIMU8_FIFO_CTRL4_REG                         0x09
#define C6DOFIMU8_FIFO_CTRL5_REG                         0x0A
#define C6DOFIMU8_DRDY_PULSE_CFG_REG                     0x0B
#define C6DOFIMU8_INT1_CTRL_REG                          0x0D
#define C6DOFIMU8_INT2_CTRL_REG                          0x0E
#define C6DOFIMU8_WHO_AM_I_REG                           0x0F
#define C6DOFIMU8_CTRL1_XL_REG                           0x10
#define C6DOFIMU8_CTRL2_G_REG                            0x11
#define C6DOFIMU8_CTRL3_C_REG                            0x12
#define C6DOFIMU8_CTRL4_C_REG                            0x13
#define C6DOFIMU8_CTRL5_C_REG                            0x14
#define C6DOFIMU8_CTRL6_C_REG                            0x15
#define C6DOFIMU8_CTRL7_G_REG                            0x16
#define C6DOFIMU8_CTRL8_XL_REG                           0x17
#define C6DOFIMU8_CTRL9_XL_REG                           0x18
#define C6DOFIMU8_CTRL10_C_REG                           0x19
#define C6DOFIMU8_MASTER_CFG_REG                         0x1A
#define C6DOFIMU8_WAKE_UP_SRC_REG                        0x1B
#define C6DOFIMU8_TAP_SRC_REG                            0x1C
#define C6DOFIMU8_D6D_SRC_REG                            0x1D
#define C6DOFIMU8_STATUS_REG                             0x1E
#define C6DOFIMU8_OUT_TEMP_REG                           0x20
#define C6DOFIMU8_OUTX_G_REG                             0x22
#define C6DOFIMU8_OUTY_G_REG                             0x24
#define C6DOFIMU8_OUTZ_G_REG                             0x26
#define C6DOFIMU8_OUTX_XL_REG                            0x28
#define C6DOFIMU8_OUTY_XL_REG                            0x2A
#define C6DOFIMU8_OUTZ_XL_REG                            0x2C
#define C6DOFIMU8_SENS_HUB1_REG                          0x2E
#define C6DOFIMU8_SENS_HUB2_REG                          0x2F
#define C6DOFIMU8_SENS_HUB3_REG                          0x30
#define C6DOFIMU8_SENS_HUB4_REG                          0x31
#define C6DOFIMU8_SENS_HUB5_REG                          0x32
#define C6DOFIMU8_SENS_HUB6_REG                          0x33
#define C6DOFIMU8_SENS_HUB7_REG                          0x34
#define C6DOFIMU8_SENS_HUB8_REG                          0x35
#define C6DOFIMU8_SENS_HUB9_REG                          0x36
#define C6DOFIMU8_SENS_HUB10_REG                         0x37
#define C6DOFIMU8_SENS_HUB11_REG                         0x38
#define C6DOFIMU8_SENS_HUB12_REG                         0x39
#define C6DOFIMU8_FIFO_STATUS1_REG                       0x3A
#define C6DOFIMU8_FIFO_STATUS2_REG                       0x3B
#define C6DOFIMU8_FIFO_STATUS3_REG                       0x3C
#define C6DOFIMU8_FIFO_STATUS4_REG                       0x3D
#define C6DOFIMU8_FIFO_DATA_OUT_REG                      0x3E
#define C6DOFIMU8_TIMESTAMP0_REG                         0x40
#define C6DOFIMU8_TIMESTAMP1_REG                         0x41
#define C6DOFIMU8_TIMESTAMP2_REG                         0x42
#define C6DOFIMU8_SENS_HUB13_REG                         0x4D
#define C6DOFIMU8_SENS_HUB14_REG                         0x4E
#define C6DOFIMU8_SENS_HUB15_REG                         0x4F
#define C6DOFIMU8_SENS_HUB16_REG                         0x50
#define C6DOFIMU8_SENS_HUB17_REG                         0x51
#define C6DOFIMU8_SENS_HUB18_REG                         0x52
#define C6DOFIMU8_FUNC_SRC1_REG                          0x53
#define C6DOFIMU8_FUNC_SRC2_REG                          0x54
#define C6DOFIMU8_TAP_CFG_REG                            0x58
#define C6DOFIMU8_TAP_THS_6D_REG                         0x59
#define C6DOFIMU8_INT_DUR2_REG                           0x5A
#define C6DOFIMU8_WAKE_UP_THS_REG                        0x5B
#define C6DOFIMU8_WAKE_UP_DUR_REG                        0x5C
#define C6DOFIMU8_FREE_FALL_REG                          0x5D
#define C6DOFIMU8_MD1_CFG_REG                            0x5E
#define C6DOFIMU8_MD2_CFG_REG                            0x5F
#define C6DOFIMU8_MASTER_CMD_CODE_REG                    0x60
#define C6DOFIMU8_SENS_SYNC_SPI_ERR_CODE_REG             0x61
#define C6DOFIMU8_OUT_MAG_RAW_X_REG                      0x66
#define C6DOFIMU8_OUT_MAG_RAW_Y_REG                      0x68
#define C6DOFIMU8_OUT_MAG_RAW_Z_REG                      0x6A
#define C6DOFIMU8_INT_OIS_REG                            0x6F
#define C6DOFIMU8_CTRL1_OIS_REG                          0x70
#define C6DOFIMU8_CTRL2_OIS_REG                          0x71
#define C6DOFIMU8_CTRL3_OIS_REG                          0x72
#define C6DOFIMU8_X_OFS_USR_REG                          0x73
#define C6DOFIMU8_Y_OFS_USR_REG                          0x74
#define C6DOFIMU8_Z_OFS_USR_REG                          0x75
/** \} */

/**
 * \defgroup reg_access Reg Access
 * \{
 */
#define C6DOFIMU8_REG_ACCESS_EN                          0x80
/** \} */

/**
 * \defgroup dec_fifo Dec Fifo
 * \{
 */
#define C6DOFIMU8_DEC_FIFO_XL_SENS_NOT_IN_FIFO           0x00
#define C6DOFIMU8_DEC_FIFO_XL_NO_DEC                     0x01
#define C6DOFIMU8_DEC_FIFO_XL_FACTOR2                    0x02
#define C6DOFIMU8_DEC_FIFO_XL_FACTOR3                    0x03
#define C6DOFIMU8_DEC_FIFO_XL_FACTOR4                    0x04
#define C6DOFIMU8_DEC_FIFO_XL_FACTOR8                    0x05
#define C6DOFIMU8_DEC_FIFO_XL_FACTOR16                   0x06
#define C6DOFIMU8_DEC_FIFO_XL_FACTOR32                   0x07
#define C6DOFIMU8_DEC_FIFO_G_SENS_NOT_IN_FIFO            0x00
#define C6DOFIMU8_DEC_FIFO_G_NO_DEC                      0x08
#define C6DOFIMU8_DEC_FIFO_G_FACTOR2                     0x10
#define C6DOFIMU8_DEC_FIFO_G_FACTOR3                     0x18
#define C6DOFIMU8_DEC_FIFO_G_FACTOR4                     0x20
#define C6DOFIMU8_DEC_FIFO_G_FACTOR8                     0x28
#define C6DOFIMU8_DEC_FIFO_G_FACTOR16                    0x30
#define C6DOFIMU8_DEC_FIFO_G_FACTOR32                    0x38
/** \} */

/**
 * \defgroup fifo_odr Fifo Odr
 * \{
 */
#define C6DOFIMU8_FIFO_ODR_DIS                           0x00
#define C6DOFIMU8_FIFO_ODR_12_5_HZ                       0x08
#define C6DOFIMU8_FIFO_ODR_26_HZ                         0x10
#define C6DOFIMU8_FIFO_ODR_52_HZ                         0x18
#define C6DOFIMU8_FIFO_ODR_104_HZ                        0x20
#define C6DOFIMU8_FIFO_ODR_208_HZ                        0x28
#define C6DOFIMU8_FIFO_ODR_416_HZ                        0x30
#define C6DOFIMU8_FIFO_ODR_833_HZ                        0x38
#define C6DOFIMU8_FIFO_ODR_1660_HZ                       0x40
#define C6DOFIMU8_FIFO_ODR_3330_HZ                       0x48
#define C6DOFIMU8_FIFO_ODR_6660_HZ                       0x50
#define C6DOFIMU8_FIFO_BYPASS1_MODE                      0x00
#define C6DOFIMU8_FIFO_FIFO_MODE                         0x01
#define C6DOFIMU8_FIFO_CONT1_MODE                        0x03
#define C6DOFIMU8_FIFO_BYPASS2_MODE                      0x04
#define C6DOFIMU8_FIFO_CONT2_MODE                        0x06
/** \} */

/**
 * \defgroup drdy_mode Drdy Mode
 * \{
 */
#define C6DOFIMU8_DRDY_LATCHED_MODE                      0x00
#define C6DOFIMU8_DRDY_PULSED_MODE                       0x80
/** \} */

/**
 * \defgroup int_pin Int Pin
 * \{
 */
#define C6DOFIMU8_INT_PIN_FIFO_FULL_FLAG_EN              0x20
#define C6DOFIMU8_INT_PIN_FIFO_OVERRUN_FLAG_EN           0x10
#define C6DOFIMU8_INT_PIN_FIFO_THRESH_FLAG_EN            0x08
#define C6DOFIMU8_INT1_PIN_BOOT_STATUS_FLAG_EN           0x04
#define C6DOFIMU8_INT2_PIN_TEMP_DRDY_FLAG_EN             0x04
#define C6DOFIMU8_INT_PIN_G_DRDY_FLAG_EN                 0x02
#define C6DOFIMU8_INT_PIN_XL_DRDY_FLAG_EN                0x01
/** \} */

/**
 * \defgroup odr Odr
 * \{
 */
#define C6DOFIMU8_ODR_POWER_DOWN                         0x00
#define C6DOFIMU8_ODR_1_6_HZ                             0x0B
#define C6DOFIMU8_ODR_12_5_HZ                            0x01
#define C6DOFIMU8_ODR_26_HZ                              0x02
#define C6DOFIMU8_ODR_52_HZ                              0x03
#define C6DOFIMU8_ODR_104_HZ                             0x04
#define C6DOFIMU8_ODR_208_HZ                             0x05
#define C6DOFIMU8_ODR_416_HZ                             0x06
#define C6DOFIMU8_ODR_833_HZ                             0x07
#define C6DOFIMU8_ODR_1660_HZ                            0x08
#define C6DOFIMU8_ODR_3330_HZ                            0x09
#define C6DOFIMU8_ODR_6660_HZ                            0x0A
#define C6DOFIMU8_FS_XL_2G                               0x00
#define C6DOFIMU8_FS_XL_16G                              0x01
#define C6DOFIMU8_FS_XL_4G                               0x02
#define C6DOFIMU8_FS_XL_8G                               0x03
#define C6DOFIMU8_FS_G_250DPS                            0x00
#define C6DOFIMU8_FS_G_500DPS                            0x01
#define C6DOFIMU8_FS_G_1000DPS                           0x02
#define C6DOFIMU8_FS_G_2000DPS                           0x03
#define C6DOFIMU8_FS_G_125DPS                            0x04
#define C6DOFIMU8_BW_XL_1500_HZ                          0x00
#define C6DOFIMU8_BW_XL_400_HZ                           0x01
/** \} */

/**
 * \defgroup mode Mode
 * \{
 */
#define C6DOFIMU8_NORMAL_MODE                            0x00
#define C6DOFIMU8_REBOOT_MEM_CONTENT                     0x80
#define C6DOFIMU8_CONT_UPDATE                            0x00
#define C6DOFIMU8_READ_UPDATE                            0x40
#define C6DOFIMU8_INT_OUT_PADS_ACT_HIGH                  0x00
#define C6DOFIMU8_INT_OUT_PADS_ACT_LOW                   0x20
#define C6DOFIMU8_PADS_PUSH_PULL_MODE                    0x00
#define C6DOFIMU8_PADS_OPEN_DRAIN_MODE                   0x10
#define C6DOFIMU8_SPI_4_WIRE_INTER                       0x00
#define C6DOFIMU8_SPI_3_WIRE_INTER                       0x08
#define C6DOFIMU8_REG_ADDR_AUTO_INC_EN                   0x04
#define C6DOFIMU8_DATA_LSB                               0x00
#define C6DOFIMU8_DATA_MSB                               0x02
#define C6DOFIMU8_SW_RESET_CMD                           0x01
/** \} */

/**
 * \defgroup enable Enable
 * \{
 */
#define C6DOFIMU8_DEN_XL_EN                              0x80
#define C6DOFIMU8_G_SLEEP_MODE_EN                        0x40
#define C6DOFIMU8_INT1_PAD_ONLY_EN                       0x20
#define C6DOFIMU8_DEN_DRDY_INT1_EN                       0x10
#define C6DOFIMU8_DA_TIMER_EN                            0x08
#define C6DOFIMU8_I2C_INTER_DIS                          0x04
#define C6DOFIMU8_LPF1_SEL_G_EN                          0x02
/** \} */

/**
 * \defgroup round Round
 * \{
 */
#define C6DOFIMU8_NO_ROUNDING                            0x00
#define C6DOFIMU8_ROUND_XL_ONLY                          0x20
#define C6DOFIMU8_ROUND_G_ONLY                           0x40
#define C6DOFIMU8_ROUND_G_AND_XL                         0x60
#define C6DOFIMU8_DEN_ACT_LOW                            0x00
#define C6DOFIMU8_DEN_ACT_HIGH                           0x10
#define C6DOFIMU8_ST_G_NORMAL_MODE                       0x00
#define C6DOFIMU8_ST_G_POS_SIGN                          0x04
#define C6DOFIMU8_ST_G_NEG_SIGN                          0x0C
#define C6DOFIMU8_ST_XL_NORMAL_MODE                      0x00
#define C6DOFIMU8_ST_XL_POS_SIGN                         0x01
#define C6DOFIMU8_ST_XL_NEG_SIGN                         0x02
/** \} */

/**
 * \defgroup hpf Hpf
 * \{
 */
#define C6DOFIMU8_G_HP_OP_MODE_DIS                       0x80
#define C6DOFIMU8_G_HPF_EN                               0x40
#define C6DOFIMU8_G_HPF_16_MILLI_HZ                      0x00
#define C6DOFIMU8_G_HPF_65_MILLI_HZ                      0x10
#define C6DOFIMU8_G_HPF_260_MILLI_HZ                     0x20
#define C6DOFIMU8_G_HPF_1040_MILLI_HZ                    0x30
#define C6DOFIMU8_ROUNDING_EN                            0x04
/** \} */

/**
 * \defgroup den_stored Den Stored
 * \{
 */
#define C6DOFIMU8_DEN_X_LSB_STORED                       0x80
#define C6DOFIMU8_DEN_Y_LSB_STORED                       0x40
#define C6DOFIMU8_DEN_Z_LSB_STORED                       0x20
#define C6DOFIMU8_DEN_G_STAMPED                          0x00
#define C6DOFIMU8_DEN_XL_STAMPED                         0x10
#define C6DOFIMU8_SOFT_IRON_CORR_ALGO_EN                 0x04
/** \} */

/**
 * \defgroup event_mask Event Mask
 * \{
 */
#define C6DOFIMU8_FREE_FALL_EVENT_MASK                   0x20
#define C6DOFIMU8_SLEEP_EVENT_MASK                       0x10
#define C6DOFIMU8_WAKE_UP_EVENT_MASK                     0x08
#define C6DOFIMU8_X_WAKEUP_EVENT_MASK                    0x04
#define C6DOFIMU8_Y_WAKEUP_EVENT_MASK                    0x02
#define C6DOFIMU8_Z_WAKEUP_EVENT_MASK                    0x01

#define C6DOFIMU8_TAP_EVENT_MASK                         0x40
#define C6DOFIMU8_SINGLE_TAP_EVENT_MASK                  0x20
#define C6DOFIMU8_DOUBLE_TAP_EVENT_MASK                  0x10
#define C6DOFIMU8_TAP_SIGN_EVENT_MASK                    0x08
#define C6DOFIMU8_X_TAP_EVENT_MASK                       0x04
#define C6DOFIMU8_Y_TAP_EVENT_MASK                       0x02
#define C6DOFIMU8_Z_TAP_EVENT_MASK                       0x01
/** \} */

/**
 * \defgroup drdy_mask Drdy Mask
 * \{
 */
#define C6DOFIMU8_TEMP_DRDY_MASK                         0x04
#define C6DOFIMU8_G_DRDY_MASK                            0x02
#define C6DOFIMU8_XL_DRDY_MASK                           0x01
/** \} */

/**
 * \defgroup fifo_status_mask Fifo Status Mask
 * \{
 */
#define C6DOFIMU8_FIFO_WATERMARK_STATUS_MASK             0x80
#define C6DOFIMU8_FIFO_OVERRUN_STATUS_MASK               0x40
#define C6DOFIMU8_FIFO_FULL_SMART_STATUS_MASK            0x20
#define C6DOFIMU8_FIFO_EMPTY_STATUS_MASK                 0x10
/** \} */

/**
 * \defgroup enable Enable
 * \{
 */
#define C6DOFIMU8_BASIC_INTERR_EN                        0x80
#define C6DOFIMU8_SLOPE_FILTER_APPLIED                   0x00
#define C6DOFIMU8_HPF_APPLIED                            0x10
#define C6DOFIMU8_TAP_X_EN                               0x08
#define C6DOFIMU8_TAP_Y_EN                               0x04
#define C6DOFIMU8_TAP_Z_EN                               0x02
#define C6DOFIMU8_INTERR_REQ_LATCHED                     0x01
/** \} */

/**
 * \defgroup event_detected Event Detected
 * \{
 */
#define C6DOFIMU8_EVENT_NOT_DETECTED                     0x00
#define C6DOFIMU8_EVENT_DETECTED                         0x01
/** \} */

/**
 * \defgroup error Error
 * \{
 */
#define C6DOFIMU8_INT_OCCURED                            0x01
#define C6DOFIMU8_ADDR_ERROR                             0x02
#define C6DOFIMU8_FULL_SCALE_ERROR                       0x03
#define C6DOFIMU8_DATA_RATE_ERROR                        0x04
/** \} */

/**
 * \defgroup log Log
 * \{
 */
#define C6DOFIMU8_LOG_HIGH                               0x01
#define C6DOFIMU8_LOG_LOW                                0x00
/** \} */

/**
 * \defgroup log Log
 * \{
 */
#define SPI_DRIVER                                       0
#define I2C_DRIVER                                       1
#define DUMMY_BYTE                                       0
#define SPI_RD_CMD                                       0x80
#define TEMP_LSB_RES                                     326.8
#define TEMP_OFFSET                                      25
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
typedef uint8_t  c6dofimu8_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *c6dofimu8_master_io_t )( struct c6dofimu8_s*, uint8_t, uint8_t*, uint8_t );

typedef struct {

    double   x;
    double   y;
    double   z;

} t_c6dofimu8_axis;

/**
 * @brief Click ctx object definition.
 */
typedef struct c6dofimu8_s
{
    // Input pins 

    digital_in_t it2;
    digital_in_t it1;
    digital_out_t cs;
    
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

   uint8_t slave_address;
   pin_name_t chip_select;
   c6dofimu8_master_io_t  write_f;
   c6dofimu8_master_io_t  read_f;
   c6dofimu8_select_t master_sel;

   uint8_t driver_sel;
   uint8_t gyro_res;
   uint8_t accel_res;

   t_c6dofimu8_axis dev_axis;

} c6dofimu8_t;

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

    pin_name_t it2;
    pin_name_t it1;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;
    uint32_t spi_speed;
    spi_master_mode_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

   c6dofimu8_select_t sel;

} c6dofimu8_cfg_t;

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
void c6dofimu8_cfg_setup ( c6dofimu8_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param c6dofimu8 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
C6DOFIMU8_RETVAL c6dofimu8_init ( c6dofimu8_t *ctx, c6dofimu8_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for c6DOF IMU 8 Click.
 */
void c6dofimu8_default_cfg ( c6dofimu8_t *ctx );

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
void c6dofimu8_generic_write ( c6dofimu8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void c6dofimu8_generic_read ( c6dofimu8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Single Byte Write functions.
 *
 * @param ctx        Click object.
 * @param reg_addr   Address where data be written.
 * @param data_in    Data to be written.
 *
 * @description This function writes one byte data to the desired register.
 */
uint8_t c6dofimu8_write_byte ( c6dofimu8_t *ctx, uint8_t reg_addr, uint8_t data_in );

/**
 * @brief Single Byte Read function.
 *
 * @param ctx        Click object.
 * @param reg_addr   Address which from data be read.
 * @param data_out   Memory location where data be stored.
 *
 * @description This function reads one byte data from the desired register.
 */
uint8_t c6dofimu8_read_byte ( c6dofimu8_t *ctx, uint8_t reg_addr, uint8_t *data_out );

/**
 * @brief Word Write function.
 *
 * @param ctx        Click object.
 * @param reg_addr   Address of the lower byte of data which will be written.
 * @param data_in    Data to be written.
 *
 * @description This function writes 16bit data to the desired register.
 */
uint8_t c6dofimu8_write_word ( c6dofimu8_t *ctx, uint8_t reg_addr, uint16_t data_in );

/**
 * @brief Word Read function.
 *
 * @param ctx        Click object.
 * @param reg_addr   Address of the lower byte of data which will be read.
 * @param data_out   Memory location where data be stored.
 *
 * @description This function reads 16bit data from the desired register.
 */
uint8_t c6dofimu8_read_word ( c6dofimu8_t *ctx, uint8_t reg_addr, uint16_t *data_out );

/**
 * @brief Sequential Write function.
 *
 * @param ctx           Click object.
 * @param start_addr    Start address which from data writing be started.
 * @param data_in       Data to be written.
 * @param n_bytes       Number of bytes to be written.
 *
 * @description This function performs a sequential data writing starting from the desired address.
 */
uint8_t c6dofimu8_write_bytes ( c6dofimu8_t *ctx, uint8_t start_addr, uint8_t *data_in, uint8_t n_bytes );

/**
 * @brief equential Read function.
 *
 * @param ctx           Click object.
 * @param start_addr    Start address which from data reading be started.
 * @param data_out      Memory location where data be stored.
 * @param n_bytes       Number of bytes to be read.
 *
 * @description This function performs a sequential data reading starting from the desired address.
 */
uint8_t c6dofimu8_read_bytes ( c6dofimu8_t *ctx, uint8_t start_addr, uint8_t *data_out, uint8_t n_bytes );

/**
 * @brief Device SW Reset function.
 *
 * @param ctx           Click object.
 *
 * @description This function performs a device software reset.
 */
void c6dofimu8_reset ( c6dofimu8_t *ctx );

/**
 * @brief INT1 Pin Check function.
 *
 * @param ctx           Click object.
 *
 * @description This function checks does interrupt generated on the INT1 pin.
 */
uint8_t c6dofimu8_get_int_1_pin ( c6dofimu8_t *ctx );

/**
 * @brief INT2 Pin Check function.
 *
 * @param ctx           Click object.
 *
 * @description This function checks does interrupt generated on the INT2 pin.
 */
uint8_t c6dofimu8_get_int_2_pin ( c6dofimu8_t *ctx );

/**
 * @brief Status Check function.
 *
 * @param ctx           Click object.
 * @param bit_mask      Selects which status flag bit of the Status register be checked.
 *
 * @description This function checks a data ready status for all measurements.
 */
uint8_t c6dofimu8_get_drdy_status ( c6dofimu8_t *ctx, uint8_t bit_mask );

/**
 * @brief Data Get function.
 *
 * @param ctx           Click object.
 * @param accel_out     Memory location where accelerometer axis data be stored.
 * @param gyro_out      Memory location where gyroscope axis data be stored.
 * @param temp_out      Memory location where temperature data be stored.
 *
 * @description This function performs a data reading and all necessary calculations to get accelerometer, gyroscope and temperature data.
 */
void c6dofimu8_get_data ( c6dofimu8_t *ctx, t_c6dofimu8_axis *accel_out, t_c6dofimu8_axis *gyro_out, int8_t *temp_out );

/**
 * @brief Full Scale Setting function.
 *
 * @param ctx           Click object.
 * @param gyro_fsr      Selects a full scale for gyroscope measurement [0-4].
 * @param accel_fsr     Selects a full scale for accelerometer measurement [0-3].
 *
 * @description This function selects a measurement full scale range.
 */
uint8_t c6dofimu8_set_fsr ( c6dofimu8_t *ctx, uint8_t gyro_fsr, uint8_t accel_fsr );

/**
 * @brief Data Rate Setting function.
 *
 * @param ctx           Click object.
 * @param gyro_odr      Selects a data rate for gyroscope measurement [0x00-0x0B].
 * @param accel_odr     Selects a data rate for accelerometer measurement [0x00-0x0B].
 *
 * @description This function selects a measurement output data rate.
 */
uint8_t c6dofimu8_set_odr ( c6dofimu8_t *ctx, uint8_t gyro_odr, uint8_t accel_odr );

/**
 * @brief Magnetometer Data Get function.
 *
 * @param ctx           Click object.
 * @param gyro_odr      Memory location where magnetometer axis data be stored.
 *
 * @description This function performs a magnetometer data reading.
 */
void c6dofimu8_get_magnetometer_data ( c6dofimu8_t *ctx, t_c6dofimu8_axis *magneto_out );

#ifdef __cplusplus
}
#endif
#endif  // _C6DOFIMU8_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
