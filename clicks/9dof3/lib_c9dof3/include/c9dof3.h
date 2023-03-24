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
 * \brief This file contains API for 9DOF 3  Click driver.
 *
 * \addtogroup c9dof3 9DOF 3  Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C9DOF3_H
#define C9DOF3_H

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

#define C9DOF3_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso    = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi    = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck     = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs1     = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.cs2     = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.cs3     = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define C9DOF3_MASTER_I2C 0
#define C9DOF3_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C9DOF3_RETVAL  uint8_t
/** \} */

/**
 * \defgroup i2c_slave_address I2C Slave Address
 * \{
 */
#define C9DOF3_ACC_I2C_SLAVE_ADDRESS                                0x18
#define C9DOF3_GYRO_I2C_SLAVE_ADDRESS                               0x68
#define C9DOF3_MAG_I2C_SLAVE_ADDRESS                                0x10
/** \} */

/**
 * \defgroup device_check_register Device check register
 * \{
 */
#define C9DOF3_ACC_DEVICE                                           0xFA
#define C9DOF3_GYRO_DEVICE                                          0x0F
#define C9DOF3_MAG_DEVICE                                           0x32
/** \} */

/**
 * \defgroup soft_reset_parameter Soft reset parameter
 * \{
 */
#define C9DOF3_INITIATED_SOFT_RESET                                 0xB6
/** \} */

/**
 * \defgroup accel_register Accel Register
 * \{
 */
#define C9DOF3_REG_ACC_WHO_AM_I                                     0x00
#define C9DOF3_REG_ACC_DATA_START                                   0x02
#define C9DOF3_REG_ACC_D_X_LSB                                      0x02
#define C9DOF3_REG_ACC_D_X_MSB                                      0x03
#define C9DOF3_REG_ACC_D_Y_LSB                                      0x04
#define C9DOF3_REG_ACC_D_Y_MSB                                      0x05
#define C9DOF3_REG_ACC_D_Z_LSB                                      0x06
#define C9DOF3_REG_ACC_D_Z_MSB                                      0x07
#define C9DOF3_REG_ACC_D_TEMP                                       0x08
#define C9DOF3_REG_ACC_INT_STATUS_0                                 0x09
#define C9DOF3_REG_ACC_INT_STATUS_1                                 0x0A
#define C9DOF3_REG_ACC_INT_STATUS_2                                 0x0B
#define C9DOF3_REG_ACC_INT_STATUS_3                                 0x0C
#define C9DOF3_REG_ACC_FIFO_STATUS                                  0x0E
#define C9DOF3_REG_ACC_PMU_RANGE                                    0x0F
#define C9DOF3_REG_ACC_PMU_BW                                       0x10
#define C9DOF3_REG_ACC_PMU_LPW                                      0x11
#define C9DOF3_REG_ACC_PMU_LOW_POWER                                0x12
#define C9DOF3_REG_ACC_D_HBW                                        0x13
#define C9DOF3_REG_ACC_BGW_SOFTRESET                                0x14
#define C9DOF3_REG_ACC_INT_EN_0                                     0x16
#define C9DOF3_REG_ACC_INT_EN_1                                     0x17
#define C9DOF3_REG_ACC_INT_EN_2                                     0x18
#define C9DOF3_REG_ACC_INT_MAP_0                                    0x19
#define C9DOF3_REG_ACC_INT_MAP_1                                    0x1A
#define C9DOF3_REG_ACC_INT_MAP_2                                    0x1B
#define C9DOF3_REG_ACC_INT_SRC                                      0x1E
#define C9DOF3_REG_ACC_INT_OUT_CTRL                                 0x20
#define C9DOF3_REG_ACC_INT_RST_LATCH                                0x21
#define C9DOF3_REG_ACC_INT_0                                        0x22
#define C9DOF3_REG_ACC_INT_1                                        0x23
#define C9DOF3_REG_ACC_INT_2                                        0x24
#define C9DOF3_REG_ACC_INT_3                                        0x25
#define C9DOF3_REG_ACC_INT_4                                        0x26
#define C9DOF3_REG_ACC_INT_5                                        0x27
#define C9DOF3_REG_ACC_INT_6                                        0x28
#define C9DOF3_REG_ACC_INT_7                                        0x29
#define C9DOF3_REG_ACC_INT_8                                        0x2A
#define C9DOF3_REG_ACC_INT_9                                        0x2B
#define C9DOF3_REG_ACC_INT_A                                        0x2C
#define C9DOF3_REG_ACC_INT_B                                        0x2D
#define C9DOF3_REG_ACC_INT_C                                        0x2E
#define C9DOF3_REG_ACC_INT_D                                        0x2F
#define C9DOF3_REG_ACC_FIFO_CONFIG_0                                0x30
#define C9DOF3_REG_ACC_PMU_SELF_TEST                                0x32
#define C9DOF3_REG_ACC_TRIM_NVM_CTRL                                0x33
#define C9DOF3_REG_ACC_BGW_SPI3_WDT                                 0x34
#define C9DOF3_REG_ACC_OFC_CTRL                                     0x36
#define C9DOF3_REG_ACC_OFC_SETTING                                  0x37
#define C9DOF3_REG_ACC_OFC_OFFSET_X                                 0x38
#define C9DOF3_REG_ACC_OFC_OFFSET_Y                                 0x39
#define C9DOF3_REG_ACC_OFC_OFFSET_Z                                 0x3A
#define C9DOF3_REG_ACC_TRIM_GPO                                     0x3B
#define C9DOF3_REG_ACC_TRIM_GP1                                     0x3C
#define C9DOF3_REG_ACC_FIFO_CONFIG_1                                0x3E
#define C9DOF3_REG_ACC_FIFO_DATA                                    0x3F
/** \} */

/**
 * \defgroup gyro_register Gyro Register
 * \{
 */
#define C9DOF3_REG_GYRO_WHO_AM_I                                    0x00
#define C9DOF3_REG_GYRO_DATA_START                                  0x02
#define C9DOF3_REG_GYRO_RATE_X_LSB                                  0x02
#define C9DOF3_REG_GYRO_RATE_X_MSB                                  0x03
#define C9DOF3_REG_GYRO_RATE_Y_LSB                                  0x04
#define C9DOF3_REG_GYRO_RATE_Y_MSB                                  0x05
#define C9DOF3_REG_GYRO_RATE_Z_LSB                                  0x06
#define C9DOF3_REG_GYRO_RATE_Z_MSB                                  0x07
#define C9DOF3_REG_GYRO_INT_STATUS_0                                0x09
#define C9DOF3_REG_GYRO_INT_STATUS_1                                0x0A
#define C9DOF3_REG_GYRO_INT_STATUS_2                                0x0B
#define C9DOF3_REG_GYRO_INT_STATUS_3                                0x0C
#define C9DOF3_REG_GYRO_FIFO_STATUS                                 0x0E
#define C9DOF3_REG_GYRO_RANGE                                       0x0F
#define C9DOF3_REG_GYRO_BW                                          0x10
#define C9DOF3_REG_GYRO_LPM1                                        0x11
#define C9DOF3_REG_GYRO_LPM2                                        0x12
#define C9DOF3_REG_GYRO_RATE_HBW                                    0x13
#define C9DOF3_REG_GYRO_BGW_SOFTRESET                               0x14
#define C9DOF3_REG_GYRO_INT_EN_0                                    0x15
#define C9DOF3_REG_GYRO_INT_EN_1                                    0x16
#define C9DOF3_REG_GYRO_INT_MAP_0                                   0x17
#define C9DOF3_REG_GYRO_INT_MAP_1                                   0x18
#define C9DOF3_REG_GYRO_INT_MAP_2                                   0x19
#define C9DOF3_REG_GYRO_INT_SRC_1                                   0x1A
#define C9DOF3_REG_GYRO_INT_SRC_2                                   0x1B
#define C9DOF3_REG_GYRO_INT_SRC_3                                   0x1C
#define C9DOF3_REG_GYRO_FIFO_EN                                     0x1E
#define C9DOF3_REG_GYRO_INT_RST_LATCH                               0x21
#define C9DOF3_REG_GYRO_HIGH_TH_X                                   0x22
#define C9DOF3_REG_GYRO_HIGH_DUR_X                                  0x23
#define C9DOF3_REG_GYRO_HIGH_TH_Y                                   0x24
#define C9DOF3_REG_GYRO_HIGH_DUR_Y                                  0x25
#define C9DOF3_REG_GYRO_HIGH_TH_Z                                   0x26
#define C9DOF3_REG_GYRO_HIGH_DUR_Z                                  0x27
#define C9DOF3_REG_GYRO_SOC                                         0x31
#define C9DOF3_REG_GYRO_A_FOC                                       0x32
#define C9DOF3_REG_GYRO_TRIM_NVM_CTRL                               0x33
#define C9DOF3_REG_GYRO_BGW_SPI3_WDT                                0x34
#define C9DOF3_REG_GYRO_OFC1                                        0x36
#define C9DOF3_REG_GYRO_OFC2                                        0x37
#define C9DOF3_REG_GYRO_OFC3                                        0x38
#define C9DOF3_REG_GYRO_OFC4                                        0x39
#define C9DOF3_REG_GYRO_TRIM_GP0                                    0x3A
#define C9DOF3_REG_GYRO_TRIM_GP1                                    0x3B
#define C9DOF3_REG_GYRO_BIST                                        0x3C
#define C9DOF3_REG_GYRO_FIFO_CONFIG_0                               0x3D
#define C9DOF3_REG_GYRO_FIFO_CONFIG_1                               0x3E
/** \} */

/**
 * \defgroup mag_register Mag Register
 * \{
 */
#define C9DOF3_REG_MAG_WHO_AM_I                                     0x40
#define C9DOF3_REG_MAG_DATA_START                                   0x42
#define C9DOF3_REG_MAG_XOUT_LSB                                     0x42
#define C9DOF3_REG_MAG_XOUT_MSB                                     0x43
#define C9DOF3_REG_MAG_YOUT_LSB                                     0x44
#define C9DOF3_REG_MAG_YOUT_MSB                                     0x45
#define C9DOF3_REG_MAG_ZOUT_LSB                                     0x46
#define C9DOF3_REG_MAG_ZOUT_MSB                                     0x47
#define C9DOF3_REG_MAG_ROUT_LSB                                     0x48
#define C9DOF3_REG_MAG_ROUT_MSB                                     0x49
#define C9DOF3_REG_MAG_INT_STATUS                                   0x4A
#define C9DOF3_REG_MAG_PWR_CNTL1                                    0x4B
#define C9DOF3_REG_MAG_PWR_CNTL2                                    0x4C
#define C9DOF3_REG_MAG_INT_EN_1                                     0x4D
#define C9DOF3_REG_MAG_INT_EN_2                                     0x4E
#define C9DOF3_REG_MAG_LOW_THS                                      0x4F
#define C9DOF3_REG_MAG_HIGH_THS                                     0x50
#define C9DOF3_REG_MAG_REP_XY                                       0x51
#define C9DOF3_REG_MAG_REP_Z                                        0x52
/** \} */

/**
 * \defgroup accel_mpu_range_param Accel MPU Range Parameter
 * \{
 */
#define C9DOF3_ACC_RANGE_2                                          0x03
#define C9DOF3_ACC_RANGE_4                                          0x05
#define C9DOF3_ACC_RANGE_8                                          0x08
#define C9DOF3_ACC_RANGE_16                                         0x0C
/** \} */

/**
 * \defgroup accel_mpu_band_width_param   Accel MPU Band Width Parameter ( Hz )
 * \{
 */
#define C9DOF3_ACC_PMU_BW_7_81                                      0x08
#define C9DOF3_ACC_PMU_BW_15_63                                     0x09
#define C9DOF3_ACC_PMU_BW_31_25                                     0x0A
#define C9DOF3_ACC_PMU_BW_62_5                                      0x0B
#define C9DOF3_ACC_PMU_BW_125                                       0x0C
#define C9DOF3_ACC_PMU_BW_250                                       0x0D
#define C9DOF3_ACC_PMU_BW_500                                       0x0E
#define C9DOF3_ACC_PMU_BW_1000                                      0x0F
/** \} */

/**
 * \defgroup accel_low_power_mode_param  Accel Low Power Mode Parameter
 * \{
 */
#define C9DOF3_ACC_PMU_LPW_MODE_NOMAL                               0x00
#define C9DOF3_ACC_PMU_LPW_MODE_DEEP_SUSPEND                        0x20
#define C9DOF3_ACC_PMU_LPW_MODE_LOW_POWER                           0x40
#define C9DOF3_ACC_PMU_LPW_MODE_SUSPEND                             0x80
/** \} */

/**
 * \defgroup Accel_sleep_phase_duration_param Accel Low Power Mode sleep phase duration Parameter
 * \{
 */
#define C9DOF3_ACC_PMU_LPW_SLEEP_DUR_0_5MS                          0x00
#define C9DOF3_ACC_PMU_LPW_SLEEP_DUR_1MS                            0x0C
#define C9DOF3_ACC_PMU_LPW_SLEEP_DUR_2MS                            0x0E
#define C9DOF3_ACC_PMU_LPW_SLEEP_DUR_4MS                            0x10
#define C9DOF3_ACC_PMU_LPW_SLEEP_DUR_6MS                            0x12
#define C9DOF3_ACC_PMU_LPW_SLEEP_DUR_10MS                           0x14
#define C9DOF3_ACC_PMU_LPW_SLEEP_DUR_25MS                           0x16
#define C9DOF3_ACC_PMU_LPW_SLEEP_DUR_50MS                           0x18
#define C9DOF3_ACC_PMU_LPW_SLEEP_DUR_100MS                          0x1A
#define C9DOF3_ACC_PMU_LPW_SLEEP_DUR_500MS                          0x1C
#define C9DOF3_ACC_PMU_LPW_SLEEP_DUR_1S                             0x1E
/** \} */

/**
 * \defgroup gyro_low_power_mode_param Gyro Low Power Mode Parameter
 * \{
 */
#define C9DOF3_GYRO_LPM1_MODE_NOMAL                                 0x00
#define C9DOF3_GYRO_LPM1_MODE_DEEP_SUSPEND                          0x01
#define C9DOF3_GYRO_LPM1_MODE_SUSPEND                               0x10
/** \} */

/**
 * \defgroup gyro_measur_range_param Gyro Measurement Range Parameter ( Resolution: LSB/�/s )
 * \{
 */
#define C9DOF3_GYRO_RANGE_16_4                                      0x00
#define C9DOF3_GYRO_RANGE_32_8                                      0x01
#define C9DOF3_GYRO_RANGE_65_6                                      0x02
#define C9DOF3_GYRO_RANGE_131_2                                     0x03
#define C9DOF3_GYRO_RANGE_262_4                                     0x04
/** \} */

/**
 * \defgroup gyro_mpu_band_width_param Gyro MPU Band Width Parameter ( Hz )
 * \{
 */
#define C9DOF3_GYRO_BW_32                                           0x07
#define C9DOF3_GYRO_BW_64                                           0x06
#define C9DOF3_GYRO_BW_12                                           0x05
#define C9DOF3_GYRO_BW_23                                           0x04
#define C9DOF3_GYRO_BW_47                                           0x03
#define C9DOF3_GYRO_BW_116                                          0x02
#define C9DOF3_GYRO_BW_230                                          0x01
#define C9DOF3_GYRO_BW_523                                          0x00
/** \} */

/**
 * \defgroup  gyro_sleep_duration_param  Gyro Sleep Duration Parameter ( ms )
 * \{
 */
#define C9DOF3_GYRO_LPM1_SLEEP_DUR_2MS                              0x00
#define C9DOF3_GYRO_LPM1_SLEEP_DUR_4MS                              0x01
#define C9DOF3_GYRO_LPM1_SLEEP_DUR_5MS                              0x02
#define C9DOF3_GYRO_LPM1_SLEEP_DUR_8MS                              0x03
#define C9DOF3_GYRO_LPM1_SLEEP_DUR_10MS                             0x04
#define C9DOF3_GYRO_LPM1_SLEEP_DUR_15MS                             0x05
#define C9DOF3_GYRO_LPM1_SLEEP_DUR_18MS                             0x06
#define C9DOF3_GYRO_LPM1_SLEEP_DUR_20MS                             0x07
/** \} */

/**
 * \defgroup  mag_power_ctrl_param  Mag Power Control Parameter
 * \{
 */
#define C9DOF3_MAG_POW_CTL_SOFT_RESET                               0x82
#define C9DOF3_MAG_POW_CTL_SLEEP_MODE                               0x01
#define C9DOF3_MAG_POW_CTL_SUSPEND_MODE                             0x00
/** \} */

/**
 * \defgroup mag_datarate_ctrl_param  Mag Datarate Control Parameter
 * \{
 */
#define C9DOF3_MAG_DATA_RATE_10                                     0x00
#define C9DOF3_MAG_DATA_RATE_2                                      0x08
#define C9DOF3_MAG_DATA_RATE_6                                      0x10
#define C9DOF3_MAG_DATA_RATE_8                                      0x18
#define C9DOF3_MAG_DATA_RATE_15                                     0x20
#define C9DOF3_MAG_DATA_RATE_20                                     0x28
#define C9DOF3_MAG_DATA_RATE_25                                     0x30
#define C9DOF3_MAG_DATA_RATE_30                                     0x38
/** \} */

/**
 * \defgroup mag_repetitions Mag Repetitions for X-Y-Z Axis
 * \{
 */
#define C9DOF3_MAG_XY_REPET_9                                       0x04
#define C9DOF3_MAG_Z_REPET_15                                       0x0F
/** \} */

/**
 * \defgroup spi SPI
 * \{
 */
#define C9DOF3_BIT_MASK_SPI_CMD_WRITE                               0x7F
#define C9DOF3_BIT_MASK_SPI_CMD_READ                                0x80
#define C9DOF3_SPI_COMMUNICATION_DUMMY                              0x00
/** \} */

/**
 * \defgroup accel_gyro_mag_id Check Accel, Gyro and Mag ID
 * \{
 */
#define C9DOF3_ID_CHECK_ERROR                                       0x00
#define C9DOF3_ID_CHECK_SUCCESS                                     0x01
#define C9DOF3_ACC_COMM_ERROR                                       0x00
#define C9DOF3_ACC_COMM_SUCCESS                                     0x04
#define C9DOF3_GYRO_COMM_ERROR                                      0x00
#define C9DOF3_GYRO_COMM_SUCCESS                                    0x02
#define C9DOF3_MAG_COMM_ERROR                                       0x00
#define C9DOF3_MAG_COMM_SUCCESS                                     0x01
/** \} */

/**
 * \defgroup communication_mode Communication Mode
 * \{
 */
#define COMMUNICATION_MODE_ACCEL                                    0x01
#define COMMUNICATION_MODE_GYRO                                     0x02
#define COMMUNICATION_MODE_MAG                                      0x03
/** \} */

/**
 * \defgroup rst_pin_state RST pin state
 * \{
 */
#define C9DOF3_PIN_STATE_LOW                                        0x00
#define C9DOF3_PIN_STATE_HIGH                                       0x01
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief 9DOF 3 Click driver selector.
 * @details Selects target driver interface of 9DOF 3 Click driver.
 */
typedef enum
{
   C9DOF3_DRV_SEL_SPI,      /**< SPI driver descriptor. */
   C9DOF3_DRV_SEL_I2C       /**< I2C driver descriptor. */
} c9dof3_drv_t;

/**
 * @brief 9DOF 3 Click driver interface.
 * @details Definition of driver interface of 9DOF 3 Click driver.
 */
typedef void ( *c9dof3_master_io_t )( struct c9dof3_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Click ctx object definition.
 */
typedef struct c9dof3_s
{
    // Output pins 

    digital_out_t cs1;
    digital_out_t cs2;
    digital_out_t cs3;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t  i2c;                   /**< I2C driver object. */
    spi_master_t  spi;                   /**< SPI driver object. */

    // ctx variable 

    uint8_t     slave_address;           /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;             /**< Chip select pin descriptor (used for SPI driver). */
    c9dof3_drv_t  drv_sel;               /**< Master driver interface selector. */

    c9dof3_master_io_t  write_f;         /**< Master write function. */
    c9dof3_master_io_t  read_f;          /**< Master read function. */
    
    uint8_t sel_mode;

} c9dof3_t;

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
    pin_name_t cs1;
    pin_name_t cs2;
    pin_name_t cs3;
    
    // Additional gpio pins 

    pin_name_t int_pin;

    // static variable 

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

    c9dof3_drv_t  drv_sel;                              /**< Master driver interface selector. */

} c9dof3_cfg_t;

typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;
}
c9dof3_accel_t;

typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;
}
c9dof3_gyro_t;

typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;
}
c9dof3_mag_t;

/**
 * @brief 9DOF 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   C9DOF3_OK = 0,
   C9DOF3_ERROR = -1

} c9dof3_return_value_t;

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
void c9dof3_cfg_setup ( c9dof3_cfg_t *cfg );

/**
 * @brief 9DOF 3 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #c9dof3_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #c9dof3_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void c9dof3_drv_interface_selection ( c9dof3_cfg_t *cfg, c9dof3_drv_t drv_sel );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
C9DOF3_RETVAL c9dof3_init ( c9dof3_t *ctx, c9dof3_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description The function set default sensor configuration.
 *
 * @note
 * <pre>
 * Accelerometer, Gyroscope and Magnetometer soft reset,
 * Accelerometer default configuration: Select PMU Range( +-2 ), 
 * PMU_BW ( 7.81Hz ), PMU_LPW ( NomalMode, SleepDuration 0.5ms ).
 * Gyroscope default configuration: Set Range( 262.4 LSB/�/s ),
 * BW ( 32Hz ), LPM1 ( NomalMode, SleepDuration 2ms ).
 * Magnetometer default configuration: Set sleep mode,
 * Adv. stg., DataRate, OperationMode, SelfTest ( NomalMode, ODR 10Hz ),
 * Repetitions for X-Y Axis: 0x04 -> ( 1 + 2 ( 2 ^ 2 ) ) = 9,
 * Repetition for Z-Axis: 0x0F -> ( 1 +( 2 ^ 0 + 2 ^ 1 + 2 ^ 2 + 2 ^ 3) = 15.
 * </pre>
 */
void c9dof3_default_cfg ( c9dof3_t *ctx );

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
void c9dof3_generic_write ( c9dof3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void c9dof3_generic_read ( c9dof3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Check communication function.
 *
 * @param ctx      Click object.
 *
 * @returns 3-bit communication status:
 * <pre>
 * - [ Bit 0 ] Accelerometer ID check:
 *    - 0 : Error.
 *    - 1 : Success.
 * - [ Bit 1 ] Gyroscope ID check:
 *    - 0 : Error.
 *    - 1 : Success.
 * - [ Bit 2 ] Magnetometer ID check:
 *    - 0 : Error.
 *    - 1 : Success.
 * </pre>
 *
 * @description The function check device ID for accelerometer, gyroscope and magnetometer.
 */
uint8_t c9dof3_check_communication ( c9dof3_t *ctx );

/**
 * @brief Read Accel data function.
 *
 * @param ctx           Click object. 
 * @param accel_data    Pointer to memory location where Accel data be stored
 *
 * @description Function read 12-bit ( signed ) Accel X-axis, Y-axis data and Z-axis data from 
 *              the 6 targeted starts from C9DOF3_REG_ACC_DATA_START register address.
 */
void c9dof3_read_accel_data ( c9dof3_t *ctx, c9dof3_accel_t *accel_data );

/**
 * @brief Read Gyro data function.
 *
 * @param ctx           Click object. 
 * @param gyro_data     Pointer to memory location where Gyro data be stored
 *
 * @description Function read 16-bit ( signed ) Gyro X-axis, Y-axis data and Z-axis data from 
 * the 6 targeted starts from C9DOF3_REG_GYRO_DATA_START register address.
 */
void c9dof3_read_gyro_data ( c9dof3_t *ctx, c9dof3_gyro_t *gyro_data );

/**
 * @brief Read Mag data function.
 *
 * @param ctx           Click object.  
 * @param accel_data    Pointer to memory location where Mag data be stored
 *
 * @description Function read 13-bit ( signed ) Mag X-axis, Y-axis data and Z-axis data from 
 * the 6 targeted starts from C9DOF3_REG_MAG_DATA_START register address.
 */
void c9dof3_read_mag_data ( c9dof3_t *ctx, c9dof3_mag_t *mag_data );

/**
 * @brief Read Accel, Gyro and Mag data function.
 *
 * @param ctx           Click object.   
 * @param accel_data    Pointer to memory location where Accel data be stored
 * @param gyro_data     Pointer to memory location where Magnetometer data be stored
 * @param mag_data      Pointer to memory location where Magnetometer data be stored
 *
 * @description Function read Accel, Gyro and Mag X-axis, Y-axis data and Z-axis data.
 */
void c9dof3_get_data ( c9dof3_t *ctx, c9dof3_accel_t *accel_data, c9dof3_gyro_t *gyro_data, c9dof3_mag_t *mag_data );

/**
 * @brief Check interrupt status function.
 *
 * @param ctx           Click object.  
 * 
 * @returns Interrupt state:  0 - No active;    1 - Active;
 *
 * @description Function check interrupt state.
*/
uint8_t c9dof3_check_interrupt ( c9dof3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _C9DOF3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
