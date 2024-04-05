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
 * \brief This file contains API for Accel 8 Click driver.
 *
 * \addtogroup accel8 Accel 8 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ACCEL8_H
#define ACCEL8_H

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

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define ACCEL8_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.da = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.cl = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ACCEL8_RETVAL  uint8_t

#define ACCEL8_OK           0x00
#define ACCEL8_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define ACCEL8_REG_SELF_TEST_X           0x0D
#define ACCEL8_REG_SELF_TEST_Y           0x0E
#define ACCEL8_REG_SELF_TEST_Z           0x0F
#define ACCEL8_REG_SELF_TEST_A           0x10
#define ACCEL8_REG_SMPLRT_DIV            0x19
#define ACCEL8_REG_CONFIG                0x1A
#define ACCEL8_REG_GYRO_CONFIG           0x1B
#define ACCEL8_REG_ACCEL_CONFIG          0x1C
#define ACCEL8_REG_FIFO_EN               0x23
#define ACCEL8_REG_I2C_MST_CTRL          0x24
#define ACCEL8_REG_I2C_SLV0_ADDR         0x25
#define ACCEL8_REG_I2C_SLV0_REG          0x26
#define ACCEL8_REG_I2C_SLV0_CTRL         0x27
#define ACCEL8_REG_I2C_SLV1_ADDR         0x28
#define ACCEL8_REG_I2C_SLV1_REG          0x29
#define ACCEL8_REG_I2C_SLV1_CTRL         0x2A
#define ACCEL8_REG_I2C_SLV2_ADDR         0x2B
#define ACCEL8_REG_I2C_SLV2_REG          0x2C
#define ACCEL8_REG_I2C_SLV2_CTRL         0x2D
#define ACCEL8_REG_I2C_SLV3_ADDR         0x2E
#define ACCEL8_REG_I2C_SLV3_REG          0x2F
#define ACCEL8_REG_I2C_SLV3_CTRL         0x30
#define ACCEL8_REG_I2C_SLV4_ADDR         0x31
#define ACCEL8_REG_I2C_SLV4_REG          0x32
#define ACCEL8_REG_I2C_SLV4_DO           0x33
#define ACCEL8_REG_I2C_SLV4_CTRL         0x34
#define ACCEL8_REG_I2C_SLV4_DI           0x35
#define ACCEL8_REG_I2C_MST_STATUS        0x36
#define ACCEL8_REG_INT_PIN_CFG           0x37
#define ACCEL8_REG_INT_ENABLE            0x38
#define ACCEL8_REG_INT_STATUS            0x3A
#define ACCEL8_REG_ACCEL_XOUT_H          0x3B
#define ACCEL8_REG_ACCEL_XOUT_L          0x3C
#define ACCEL8_REG_ACCEL_YOUT_H          0x3D
#define ACCEL8_REG_ACCEL_YOUT_L          0x3E
#define ACCEL8_REG_ACCEL_ZOUT_H          0x3F
#define ACCEL8_REG_ACCEL_ZOUT_L          0x40
#define ACCEL8_REG_TEMP_OUT_H            0x41
#define ACCEL8_REG_TEMP_OUT_L            0x42
#define ACCEL8_REG_GYRO_XOUT_H           0x43
#define ACCEL8_REG_GYRO_XOUT_L           0x44
#define ACCEL8_REG_GYRO_YOUT_H           0x45
#define ACCEL8_REG_GYRO_YOUT_L           0x46
#define ACCEL8_REG_GYRO_ZOUT_H           0x47
#define ACCEL8_REG_GYRO_ZOUT_L           0x48
#define ACCEL8_REG_EXT_SENS_DATA_00      0x49
#define ACCEL8_REG_EXT_SENS_DATA_01      0x4A
#define ACCEL8_REG_EXT_SENS_DATA_02      0x4B
#define ACCEL8_REG_EXT_SENS_DATA_03      0x4C
#define ACCEL8_REG_EXT_SENS_DATA_04      0x4D
#define ACCEL8_REG_EXT_SENS_DATA_05      0x4E
#define ACCEL8_REG_EXT_SENS_DATA_06      0x4F
#define ACCEL8_REG_EXT_SENS_DATA_07      0x50
#define ACCEL8_REG_EXT_SENS_DATA_08      0x51
#define ACCEL8_REG_EXT_SENS_DATA_09      0x52
#define ACCEL8_REG_EXT_SENS_DATA_10      0x53
#define ACCEL8_REG_EXT_SENS_DATA_11      0x54
#define ACCEL8_REG_EXT_SENS_DATA_12      0x55
#define ACCEL8_REG_EXT_SENS_DATA_13      0x56
#define ACCEL8_REG_EXT_SENS_DATA_14      0x57
#define ACCEL8_REG_EXT_SENS_DATA_15      0x58
#define ACCEL8_REG_EXT_SENS_DATA_16      0x59
#define ACCEL8_REG_EXT_SENS_DATA_17      0x5A
#define ACCEL8_REG_EXT_SENS_DATA_18      0x5B
#define ACCEL8_REG_EXT_SENS_DATA_19      0x5C
#define ACCEL8_REG_EXT_SENS_DATA_20      0x5D
#define ACCEL8_REG_EXT_SENS_DATA_21      0x5E
#define ACCEL8_REG_EXT_SENS_DATA_22      0x5F
#define ACCEL8_REG_EXT_SENS_DATA_23      0x60
#define ACCEL8_REG_I2C_SLV0_DO           0x63
#define ACCEL8_REG_I2C_SLV1_DO           0x64
#define ACCEL8_REG_I2C_SLV2_DO           0x65
#define ACCEL8_REG_I2C_SLV3_DO           0x66
#define ACCEL8_REG_I2C_MST_DELAY_CTRL    0x67
#define ACCEL8_REG_SIGNAL_PATH_RESET     0x68
#define ACCEL8_REG_USER_CTRL             0x6A
#define ACCEL8_REG_PWR_MGMT_1            0x6B
#define ACCEL8_REG_PWR_MGMT_2            0x6C
#define ACCEL8_REG_FIFO_COUNTH           0x72
#define ACCEL8_REG_FIFO_COUNTL           0x73
#define ACCEL8_REG_FIFO_R_W              0x74
#define ACCEL8_REG_WHO_AM_I              0x75
/** \} */

/**
 * \defgroup configuration Configuration
 * \{
 */
#define ACCEL8_CFG_EXT_SYNC_INPUT_DISABLED    0x00 << 3
#define ACCEL8_CFG_EXT_SYNC_TEMP_OUTPUT       0x01 << 3
#define ACCEL8_CFG_EXT_SYNC_GYRO_X_OUTPUT     0x02 << 3
#define ACCEL8_CFG_EXT_SYNC_GYRO_Y_OUTPUT     0x03 << 3
#define ACCEL8_CFG_EXT_SYNC_GYRO_Z_OUTPUT     0x04 << 3
#define ACCEL8_CFG_EXT_SYNC_ACCEL_X_OUTPUT    0x05 << 3
#define ACCEL8_CFG_EXT_SYNC_ACCEL_Y_OUTPUT    0x06 << 3
#define ACCEL8_CFG_EXT_SYNC_ACCEL_Z_OUTPUT    0x07 << 3
#define ACCEL8_CFG_DLPF_CFG_BW_A260_G256      0x00
#define ACCEL8_CFG_DLPF_CFG_BW_A184_G188      0x01
#define ACCEL8_CFG_DLPF_CFG_BW_A94_G98        0x02
#define ACCEL8_CFG_DLPF_CFG_BW_A44_G42        0x03
#define ACCEL8_CFG_DLPF_CFG_BW_A21_G20        0x04
#define ACCEL8_CFG_DLPF_CFG_BW_A10_G10        0x05
#define ACCEL8_CFG_DLPF_CFG_BW_A5_G5          0x06
/** \} */

/**
 * \defgroup gyroscope_configuration Gyroscope Configuration
 * \{
 */
#define ACCEL8_GYRO_CFG_X_SELF_TEST                 0x80
#define ACCEL8_GYRO_CFG_Y_SELF_TEST                 0x40
#define ACCEL8_GYRO_CFG_Z_SELF_TEST                 0x20
#define ACCEL8_GYRO_CFG_FULL_SCALE_RANGE_250dbs     0x00
#define ACCEL8_GYRO_CFG_FULL_SCALE_RANGE_500dbs     0x08
#define ACCEL8_GYRO_CFG_FULL_SCALE_RANGE_1000dbs    0x10
#define ACCEL8_GYRO_CFG_FULL_SCALE_RANGE_2000dbs    0x18
/** \} */

/**
 * \defgroup accelerometer_configuration Accelerometer Configuration
 * \{
 */
#define ACCEL8_ACCEL_CFG_X_SELF_TEST             0x80
#define ACCEL8_ACCEL_CFG_Y_SELF_TEST             0x40
#define ACCEL8_ACCEL_CFG_Z_SELF_TEST             0x20
#define ACCEL8_ACCEL_CFG_FULL_SCALE_RANGE_2g     0x00
#define ACCEL8_ACCEL_CFG_FULL_SCALE_RANGE_4g     0x08
#define ACCEL8_ACCEL_CFG_FULL_SCALE_RANGE_8g     0x10
#define ACCEL8_ACCEL_CFG_FULL_SCALE_RANGE_16g    0x18
/** \} */

/**
 * \defgroup fifo_enable FIFO Enable
 * \{
 */
#define ACCEL8_FIFO_ENABLE_TEMP                  0x80
#define ACCEL8_FIFO_ENABLE_X_AXIS_GYRO           0x40
#define ACCEL8_FIFO_ENABLE_Y_AXIS_GYRO           0x20
#define ACCEL8_FIFO_ENABLE_Z_AXIS_GYRO           0x10
#define ACCEL8_FIFO_ENABLE_ACCEL                 0x08
#define ACCEL8_FIFO_ENABLE_EXT_SENS_DATA_SLV2    0x04
#define ACCEL8_FIFO_ENABLE_EXT_SENS_DATA_SLV1    0x02
#define ACCEL8_FIFO_ENABLE_EXT_SENS_DATA_SLV0    0x01
/** \} */

/**
 * \defgroup i2c_master_control I2C Master Control
 * \{
 */
#define ACCEL8_I2C_MST_CTRL_MUL_MST_ENABLE               0x80
#define ACCEL8_I2C_MST_CTRL_WAIT_FOR_ES                  0x40
#define ACCEL8_I2C_MST_CTRL_EXT_SENS_DATA_SLV3           0x20
#define ACCEL8_I2C_MST_CTRL_I2C_RESTART_BETWEEN_READS    0x00
#define ACCEL8_I2C_MST_CTRL_I2C_STOP_AND_START           0x10
#define ACCEL8_I2C_MST_CTRL_I2C_CLOCK_348kHz             0x00
#define ACCEL8_I2C_MST_CTRL_I2C_CLOCK_333kHz             0x01
#define ACCEL8_I2C_MST_CTRL_I2C_CLOCK_320kHz             0x02
#define ACCEL8_I2C_MST_CTRL_I2C_CLOCK_308kHz             0x03
#define ACCEL8_I2C_MST_CTRL_I2C_CLOCK_296kHz             0x04
#define ACCEL8_I2C_MST_CTRL_I2C_CLOCK_286kHz             0x05
#define ACCEL8_I2C_MST_CTRL_I2C_CLOCK_276kHz             0x06
#define ACCEL8_I2C_MST_CTRL_I2C_CLOCK_367kHz             0x07
#define ACCEL8_I2C_MST_CTRL_I2C_CLOCK_358kHz             0x08
#define ACCEL8_I2C_MST_CTRL_I2C_CLOCK_500kHz             0x09
#define ACCEL8_I2C_MST_CTRL_I2C_CLOCK_471kHz             0x0A
#define ACCEL8_I2C_MST_CTRL_I2C_CLOCK_444kHz             0x0B
#define ACCEL8_I2C_MST_CTRL_I2C_CLOCK_421kHz             0x0C
#define ACCEL8_I2C_MST_CTRL_I2C_CLOCK_400kHz             0x0D
#define ACCEL8_I2C_MST_CTRL_I2C_CLOCK_381kHz             0x0E
#define ACCEL8_I2C_MST_CTRL_I2C_CLOCK_364kHz             0x0F
/** \} */

/**
 * \defgroup int_pin_bypass_enable_cfg INT Pin / Bypass Enable Configuration
 * \{
 */
#define ACCEL8_INTC_INT_PIN_IS_ACTIVE_HIGH                 0x00
#define ACCEL8_INTC_INT_PIN_IS_ACTIVE_LOW                  0x80
#define ACCEL8_INTC_INT_PIN_IS_CONFIGURED_AS_PUSH_PULL     0x00
#define ACCEL8_INTC_INT_PIN_IS_CONFIGURED_AS_OPEN_DRAIN    0x40
#define ACCEL8_INTC_LATCH_INT_ENABLE                       0x20
#define ACCEL8_INTC_INT_READ_CLEAR                         0x10
#define ACCEL8_INTC_FSYNC_INT_LEVEL_ACTIVE_HIGH            0x00
#define ACCEL8_INTC_FSYNC_INT_LEVEL_ACTIVE_LOW             0x08
#define ACCEL8_INTC_FSYNC_INT_ENABLE                       0x04
#define ACCEL8_INTC_I2C_BYPASS_ENABLE                      0x02
#define ACCEL8_INTC_I2C_BYPASS_DISABLE                     0x00
/** \} */

/**
 * \defgroup int_enable Interrupt Enable
 * \{
 */
#define ACCEL8_INTE_FIFO_OFLOW_ENABLE     0x10
#define ACCEL8_INTE_I2C_MST_INT_ENABLE    0x08
#define ACCEL8_INTE_DATA_RDY_ENABLE       0x01
/** \} */

/**
 * \defgroup int_status Interrupt Status
 * \{
 */
#define ACCEL8_INTS_FIFO_OFLOW     0x10
#define ACCEL8_INTS_I2C_MST_INT    0x08
#define ACCEL8_INTS_DATA_RDY       0x01
/** \} */

/**
 * \defgroup data_output Data Output
 * \{
 */
#define ACCEL8_ACCEL_X_AXIS_DATA    0x3B
#define ACCEL8_ACCEL_Y_AXIS_DATA    0x3D
#define ACCEL8_ACCEL_Z_AXIS_DATA    0x3F
#define ACCEL8_TEMP_DATA            0x41
#define ACCEL8_GYRO_X_AXIS_DATA     0x43
#define ACCEL8_GYRO_Y_AXIS_DATA     0x45
#define ACCEL8_GYRO_Z_AXIS_DATA     0x47
/** \} */

/**
 * \defgroup reset Reset
 * \{
 */
#define ACCEL8_GYRO_RESET     0x04
#define ACCEL8_ACCEL_RESET    0x02
#define ACCEL8_TEMP_RESET     0x01
/** \} */

/**
 * \defgroup user_control User Control
 * \{
 */
#define ACCEL8_UC_FIFO_ENABLE         0x40
#define ACCEL8_UC_I2C_MASTER_MODE     0x20
#define ACCEL8_UC_FIFO_RESET          0x04
#define ACCEL8_UC_I2C_MASTER_RESET    0x02
#define ACCEL8_UC_SIG_COND_RESET      0x01
/** \} */

/**
 * \defgroup power_management_1 Power Management 1
 * \{
 */
#define ACCEL8_PM1_DEVICE_RESET                          0x80
#define ACCEL8_PM1_GO_TO_SLEEP                           0x40
#define ACCEL8_PM1_CYCLE                                 0x20
#define ACCEL8_PM1_TEMP_DISABLE                          0x08
#define ACCEL8_PM1_CLKSEL_INTERNAL_8MHZ_OSCILLATOR       0x00
#define ACCEL8_PM1_CLKSEL_PLL_WITH_X_AXIS_GYROSCOPE      0x01
#define ACCEL8_PM1_CLKSEL_PLL_WITH_Y_AXIS_GYROSCOPE      0x02
#define ACCEL8_PM1_CLKSEL_PLL_WITH_Z_AXIS_GYROSCOPE      0x03
#define ACCEL8_PM1_CLKSEL_PLL_WITH_EXTERNAL_32_768kHz    0x04
#define ACCEL8_PM1_CLKSEL_PLL_WITH_EXTERNAL_19_2kHz      0x05
#define ACCEL8_PM1_CLKSEL_STOPS_THE_CLOCK                0x07
/** \} */

/**
 * \defgroup power_management_2 Power Management 2
 * \{
 */
#define ACCEL8_PM2_LP_WAKE_CTRL_WAKE_UP_FREQ_1_25Hz          0x00
#define ACCEL8_PM2_LP_WAKE_CTRL_WAKE_UP_FREQ_5Hz             0x40
#define ACCEL8_PM2_LP_WAKE_CTRL_WAKE_UP_FREQ_20Hz            0x80
#define ACCEL8_PM2_LP_WAKE_CTRL_WAKE_UP_FREQ_40Hz            0xC0
#define ACCEL8_PM2_LP_WAKE_CTRL_X_AXIS_ACCEL_STANDBY_MODE    0x20
#define ACCEL8_PM2_LP_WAKE_CTRL_Y_AXIS_ACCEL_STANDBY_MODE    0x10
#define ACCEL8_PM2_LP_WAKE_CTRL_Z_AXIS_ACCEL_STANDBY_MODE    0x08
#define ACCEL8_PM2_LP_WAKE_CTRL_X_AXIS_GYRO_STANDBY_MODE     0x04
#define ACCEL8_PM2_LP_WAKE_CTRL_Y_AXIS_GYRO_STANDBY_MODE     0x02
#define ACCEL8_PM2_LP_WAKE_CTRL_Z_AXIS_GYRO_STANDBY_MODE     0x01
/** \} */

/**
 * \defgroup slave_addresses Slave ADdresses
 * \{
 */
#define ACCEL8_DEVICE_SLAVE_ADDRESS_ADD    0x69
#define ACCEL8_DEVICE_SLAVE_ADDRESS_SEL    0x68
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Input pins 

    digital_in_t da;
    digital_in_t cl;
    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} accel8_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t da;
    pin_name_t cl;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} accel8_cfg_t;

/**
 * @brief Click range structure definition.
 */
typedef struct
{
  //ranges

  uint8_t accel_range;
  uint16_t gyro_range;

} range_retval_t;

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
void accel8_cfg_setup ( accel8_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ACCEL8_RETVAL accel8_init ( accel8_t *ctx, accel8_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx           Click object.
 * @param accel_cfg     Accel configutarion.
 * @param accel_range   Accel range output value.
 * @param rng           Range value object.
 *
 * @description This function executes default configuration and gets values for range for Accel8 click.
 */
void accel8_default_cfg ( accel8_t *ctx, uint8_t accel_cfg, uint8_t gyro_cfg, range_retval_t *rng );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void accel8_generic_write ( accel8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void accel8_generic_read ( accel8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * 
 * @retval One word read from the register.
 *
 * @description This function reads 1 word from the desired register.
 */
uint16_t accel8_read_data ( accel8_t *ctx, uint8_t reg );

/**
 * @brief Functions for read Temperature data in C
 *
 * @param ctx          Click object.
 * 
 * @retval Temperature data
 *
 * @Note
 *   Formule :
 *  <pre>
 *    Temperature = Temp_OUT / 340 + 36.53
 *    Temp_OUT = 16bit Temp data
 *  </pre>
 */
float accel8_get_temperature ( accel8_t *ctx );

/**
 * @brief Functions for read Accel axis data
 *
 * @param ctx          Click object.
 * @param x_axis       Accel X axis data.
 * @param y_axis       Accel Y axis data.
 * @param z_axis       Accel Z axis data.
 *
 * @description This function reads Accel axis data.
 */
void accel8_get_accel_axis ( accel8_t *ctx, int16_t *x_axis, int16_t *y_axis, int16_t *z_axis );

/**
 * @brief Functions for read Gyro axis data
 *
 * @param ctx          Click object.
 * @param x_axis       Gyro X axis data.
 * @param y_axis       Gyro Y axis data.
 * @param z_axis       Gyro Z axis data.
 *
 * @description This function reads Gyro axis data.
 */
void accel8_get_gyro_axis ( accel8_t *ctx, int16_t *x_axis, int16_t *y_axis, int16_t *z_axis );

/**
 * @brief Functions for read INT pin state
 *
 * @param ctx          Click object.
 * 
 * @retval Interrupt state.
 * 
 * @description This function returns Interupt state.
 */
uint8_t accel8_get_interrupt ( accel8_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _ACCEL8_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
