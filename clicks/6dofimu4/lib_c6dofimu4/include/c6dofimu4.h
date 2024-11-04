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
 * \brief This file contains API for c6DOF IMU 4 Click driver.
 *
 * \addtogroup c6dofimu4 c6DOF IMU 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C6DOFIMU4_H
#define C6DOFIMU4_H

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
#define C6DOFIMU4_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso    = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi    = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck     = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs      = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.syn     = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define C6DOFIMU4_MASTER_I2C 0
#define C6DOFIMU4_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C6DOFIMU4_RETVAL  uint8_t

#define C6DOFIMU4_OK           0x00
#define C6DOFIMU4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_address  Slave address
 * \{
 */
#define C6DOFIMU4_DEVICE_ADDR                            0x68
/** \} */

/**
 * \defgroup registers  Registers
 * \{
 */
#define C6DOFIMU4_XG_OFFS_TC_REG                         0x04
#define C6DOFIMU4_YG_OFFS_TC_REG                         0x07
#define C6DOFIMU4_ZG_OFFS_TC_REG                         0x0A
#define C6DOFIMU4_SELF_TEST_X_REG                        0x0D
#define C6DOFIMU4_SELF_TEST_Y_REG                        0x0E
#define C6DOFIMU4_SELF_TEST_Z_REG                        0x0F
#define C6DOFIMU4_XG_OFFS_USR_REG                        0x13
#define C6DOFIMU4_YG_OFFS_USR_REG                        0x15
#define C6DOFIMU4_ZG_OFFS_USR_REG                        0x17
#define C6DOFIMU4_SMPLRT_DIV_REG                         0x19
#define C6DOFIMU4_CONFIG_REG                             0x1A
#define C6DOFIMU4_GYRO_CONFIG_REG                        0x1B
#define C6DOFIMU4_ACCEL_CONFIG_REG                       0x1C
#define C6DOFIMU4_ACCEL_CONFIG2_REG                      0x1D
#define C6DOFIMU4_LP_MODE_CFG_REG                        0x1E
#define C6DOFIMU4_ACCEL_WOM_X_THR_REG                    0x20
#define C6DOFIMU4_ACCEL_WOM_Y_THR_REG                    0x21
#define C6DOFIMU4_ACCEL_WOM_Z_THR_REG                    0x22
#define C6DOFIMU4_FIFO_EN_REG                            0x23
#define C6DOFIMU4_FSYNC_INT_REG                          0x36
#define C6DOFIMU4_INT_PIN_CFG_REG                        0x37
#define C6DOFIMU4_INT_ENABLE_REG                         0x38
#define C6DOFIMU4_FIFO_WM_INT_STATUS_REG                 0x39
#define C6DOFIMU4_INT_STATUS_REG                         0x3A
#define C6DOFIMU4_ACCEL_XOUT_REG                         0x3B
#define C6DOFIMU4_ACCEL_YOUT_REG                         0x3D
#define C6DOFIMU4_ACCEL_ZOUT_REG                         0x3F
#define C6DOFIMU4_TEMP_OUT_REG                           0x41
#define C6DOFIMU4_GYRO_XOUT_REG                          0x43
#define C6DOFIMU4_GYRO_YOUT_REG                          0x45
#define C6DOFIMU4_GYRO_ZOUT_REG                          0x47
#define C6DOFIMU4_SELF_TEST_X_GYRO_REG                   0x50
#define C6DOFIMU4_SELF_TEST_Y_GYRO_REG                   0x51
#define C6DOFIMU4_SELF_TEST_Z_GYRO_REG                   0x52
#define C6DOFIMU4_FIFO_WM_TH_REG                         0x60
#define C6DOFIMU4_SIGNAL_PATH_RESET_REG                  0x68
#define C6DOFIMU4_ACCEL_INTEL_CTRL_REG                   0x69
#define C6DOFIMU4_USER_CTRL_REG                          0x6A
#define C6DOFIMU4_PWR_MGMT_1_REG                         0x6B
#define C6DOFIMU4_PWR_MGMT_2_REG                         0x6C
#define C6DOFIMU4_I2C_IF_REG                             0x70
#define C6DOFIMU4_FIFO_COUNT_REG                         0x72
#define C6DOFIMU4_FIFO_R_W_REG                           0x74
#define C6DOFIMU4_WHO_AM_I_REG                           0x75
#define C6DOFIMU4_XA_OFFSET_REG                          0x77
#define C6DOFIMU4_YA_OFFSET_REG                          0x7A
#define C6DOFIMU4_ZA_OFFSET_REG                          0x7D
/** \} */

/**
 * \defgroup commands  Commands
 * \{
 */
#define C6DOFIMU4_FIFO_REPLACING_DIS                     0x40
#define C6DOFIMU4_EXT_SYNC_FUNC_DIS                      0x00
#define C6DOFIMU4_EXT_SYNC_TEMP_OUT_L                    0x08
#define C6DOFIMU4_EXT_SYNC_GYRO_XOUT_L                   0x10
#define C6DOFIMU4_EXT_SYNC_GYRO_YOUT_L                   0x18
#define C6DOFIMU4_EXT_SYNC_GYRO_ZOUT_L                   0x20
#define C6DOFIMU4_EXT_SYNC_ACCEL_XOUT_L                  0x28
#define C6DOFIMU4_EXT_SYNC_ACCEL_YOUT_L                  0x30
#define C6DOFIMU4_EXT_SYNC_ACCEL_ZOUT_L                  0x38
#define C6DOFIMU4_FCHOICE_8173_HZ                        0x01
#define C6DOFIMU4_GYRO_FCHOICE_3281_HZ                   0x02
#define C6DOFIMU4_G_DLPF_CFG_250_HZ                      0x00
#define C6DOFIMU4_G_DLPF_CFG_176_HZ                      0x01
#define C6DOFIMU4_G_DLPF_CFG_92_HZ                       0x02
#define C6DOFIMU4_G_DLPF_CFG_41_HZ                       0x03
#define C6DOFIMU4_G_DLPF_CFG_20_HZ                       0x04
#define C6DOFIMU4_G_DLPF_CFG_10_HZ                       0x05
#define C6DOFIMU4_G_DLPF_CFG_5_HZ                        0x06
#define C6DOFIMU4_G_DLPF_CFG_3281_HZ                     0x07
#define C6DOFIMU4_XG_ST                                  0x80
#define C6DOFIMU4_YG_ST                                  0x40
#define C6DOFIMU4_ZG_ST                                  0x20
#define C6DOFIMU4_GYRO_FS_SEL_250_DPS                    0x00
#define C6DOFIMU4_GYRO_FS_SEL_500_DPS                    0x01
#define C6DOFIMU4_GYRO_FS_SEL_1000_DPS                   0x02
#define C6DOFIMU4_GYRO_FS_SEL_2000_DPS                   0x03
#define C6DOFIMU4_XA_ST                                  0x80
#define C6DOFIMU4_YA_ST                                  0x40
#define C6DOFIMU4_ZA_ST                                  0x20
#define C6DOFIMU4_ACCEL_FS_SEL_2_G                       0x00
#define C6DOFIMU4_ACCEL_FS_SEL_4_G                       0x01
#define C6DOFIMU4_ACCEL_FS_SEL_8_G                       0x02
#define C6DOFIMU4_ACCEL_FS_SEL_16_G                      0x03
#define C6DOFIMU4_ACCEL_AVRG_CFG_4_SAMPLES               0x00
#define C6DOFIMU4_ACCEL_AVRG_CFG_8_SAMPLES               0x10
#define C6DOFIMU4_ACCEL_AVRG_CFG_16_SAMPLES              0x20
#define C6DOFIMU4_ACCEL_AVRG_CFG_32_SAMPLES              0x30
#define C6DOFIMU4_ACCEL_FCHOICE_1046_HZ                  0x08
#define C6DOFIMU4_A_DLPF_CFG_218_HZ                      0x01
#define C6DOFIMU4_A_DLPF_CFG_99_HZ                       0x02
#define C6DOFIMU4_A_DLPF_CFG_44_HZ                       0x03
#define C6DOFIMU4_A_DLPF_CFG_21_HZ                       0x04
#define C6DOFIMU4_A_DLPF_CFG_10_HZ                       0x05
#define C6DOFIMU4_A_DLPF_CFG_5_HZ                        0x06
#define C6DOFIMU4_A_DLPF_CFG_420_HZ                      0x07
#define C6DOFIMU4_GYRO_LP_MODE_EN                        0x80
#define C6DOFIMU4_G_AVGCFG_1X_622HZ                      0x00
#define C6DOFIMU4_G_AVGCFG_2X_391HZ                      0x10
#define C6DOFIMU4_G_AVGCFG_4X_211HZ                      0x20
#define C6DOFIMU4_G_AVGCFG_8X_108HZ                      0x30
#define C6DOFIMU4_G_AVGCFG_16X_54HZ                      0x40
#define C6DOFIMU4_G_AVGCFG_32X_27HZ                      0x50
#define C6DOFIMU4_G_AVGCFG_64X_14HZ                      0x60
#define C6DOFIMU4_G_AVGCFG_128X_7HZ                      0x70
#define C6DOFIMU4_GYRO_FIFO_EN                           0x10
#define C6DOFIMU4_ACCEL_FIFO_EN                          0x08
#define C6DOFIMU4_FSYNC_INT_MASK                         0x80
#define C6DOFIMU4_FSYNC_INT_OCCURED                      0x80
#define C6DOFIMU4_FSYNC_INT_NOT_OCCURED                  0x00
#define C6DOFIMU4_INT_DRDY_PIN_ACT_LOW                   0x80
#define C6DOFIMU4_INT_DRDY_PIN_ACT_HIGH                  0x00
#define C6DOFIMU4_INT_DRDY_PIN_OPEN_DRAIN                0x40
#define C6DOFIMU4_INT_DRDY_PIN_PUSH_PULL                 0x00
#define C6DOFIMU4_INT_DRDY_PIN_STAT_CLEARED              0x20
#define C6DOFIMU4_INT_DRDY_PIN_PULSE                     0x00
#define C6DOFIMU4_INT_STAT_CLEARED_ANY_READ              0x10
#define C6DOFIMU4_INT_STAT_CLEARED_STAT_REG_READ         0x00
#define C6DOFIMU4_FSYNC_PIN_INT_ACT_LOW                  0x08
#define C6DOFIMU4_FSYNC_PIN_INT_ACT_HIGH                 0x00
#define C6DOFIMU4_FSYNC_INT_MODE_EN                      0x04
#define C6DOFIMU4_FIFO_WM_INT_MASK                       0x40
#define C6DOFIMU4_FIFO_WM_INT_OCCURED                    0x40
#define C6DOFIMU4_FIFO_WM_INT_NOT_OCCURED                0x00
#define C6DOFIMU4_WOM_X_INT_MASK                         0x80
#define C6DOFIMU4_WOM_X_INT_OCCURED                      0x80
#define C6DOFIMU4_WOM_Y_INT_MASK                         0x40
#define C6DOFIMU4_WOM_Y_INT_OCCURED                      0x40
#define C6DOFIMU4_WOM_Z_INT_MASK                         0x20
#define C6DOFIMU4_WOM_Z_INT_OCCURED                      0x20
#define C6DOFIMU4_FIFO_OFLOW_INT_MASK                    0x10
#define C6DOFIMU4_FIFO_OFLOW_INT_OCCURED                 0x10
#define C6DOFIMU4_GDRIVE_INT_MASK                        0x04
#define C6DOFIMU4_GDRIVE_INT_OCCURED                     0x04
#define C6DOFIMU4_DATA_RDY_INT_MASK                      0x01
#define C6DOFIMU4_DATA_RDY_INT_OCCURED                   0x01
#define C6DOFIMU4_INT_STATUS_NOT_OCCURED                 0x00
#define C6DOFIMU4_ACCEL_RST                              0x02
#define C6DOFIMU4_TEMP_RST                               0x01
#define C6DOFIMU4_ACCEL_INTEL_WOM_DET_LOGIC_EN           0x80
#define C6DOFIMU4_ACCEL_INTEL_MODE_NOT_USE               0x00
#define C6DOFIMU4_ACCEL_INTEL_MODE_COMPARE               0x40
#define C6DOFIMU4_OUTPUT_LIMIT_EN                        0x02
#define C6DOFIMU4_WOM_TH_MODE_OR                         0x00
#define C6DOFIMU4_WOM_TH_MODE_AND                        0x01
#define C6DOFIMU4_FIFO_EN                                0x40
#define C6DOFIMU4_FIFO_RST                               0x04
#define C6DOFIMU4_ALL_DIG_SIG_PATH_RST                   0x01
#define C6DOFIMU4_DEVICE_RST                             0x80
#define C6DOFIMU4_SLEEP                                  0x40
#define C6DOFIMU4_CYCLE                                  0x20
#define C6DOFIMU4_GYRO_STANDBY                           0x10
#define C6DOFIMU4_TEMP_DIS                               0x08
#define C6DOFIMU4_CLKSEL_AUTO_SELECT                     0x05
#define C6DOFIMU4_CLKSEL_INTERNAL_20_MHZ                 0x06
#define C6DOFIMU4_CLKSEL_STOP_CLOCK                      0x07
#define C6DOFIMU4_STBY_XA                                0x20
#define C6DOFIMU4_STBY_YA                                0x10
#define C6DOFIMU4_STBY_ZA                                0x08
#define C6DOFIMU4_STBY_XG                                0x04
#define C6DOFIMU4_STBY_YG                                0x02
#define C6DOFIMU4_STBY_ZG                                0x01
#define C6DOFIMU4_ALL_AXIS_EN                            0x00
#define C6DOFIMU4_I2C_IF_DIS                             0x40
#define C6DOFIMU4_I2C_IF_EN                              0x00
/** \} */

/**
 * \defgroup state  State
 * \{
 */
#define C6DOFIMU4_OK                                     0x00
#define C6DOFIMU4_INT_OCCURED                            0x01
#define C6DOFIMU4_ADDR_ERROR                             0x02
#define C6DOFIMU4_SENS_RESOLUTION_ERROR                  0x03
/** \} */

/**
 * \defgroup status  Status
 * \{
 */
#define C6DOFIMU4_LOG_HIGH                               0x01
#define C6DOFIMU4_LOG_LOW                                0x00
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
typedef uint8_t  c6dofimu4_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *c6dofimu4_master_io_t )( struct c6dofimu4_s*, uint8_t, uint8_t*, uint8_t );

typedef struct {

    double   x;
    double   y;
    double   z;
    
} c6dofimu4_axis_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct c6dofimu4_s
{
    // Output pins 

    digital_out_t syn;
    digital_out_t cs;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

    uint8_t slave_address;
    pin_name_t chip_select;
    c6dofimu4_master_io_t  write_f;
    c6dofimu4_master_io_t  read_f;
    c6dofimu4_select_t master_sel;

    uint8_t gyro_res;
    uint8_t accel_res;

} c6dofimu4_t;

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

    pin_name_t syn;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;
    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

    c6dofimu4_select_t sel;
   
    uint8_t dev_gyro_res;
    uint8_t dev_accel_res;

} c6dofimu4_cfg_t;

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
void c6dofimu4_cfg_setup ( c6dofimu4_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param ctx          Click object.
 * @param cfg          Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
C6DOFIMU4_RETVAL c6dofimu4_init ( c6dofimu4_t *ctx, c6dofimu4_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 * 
 * @note
 * <pre>
 *       set: C6DOFIMU4_I2C_IF_REG
 *             -C6DOFIMU4_I2C_IF_EN
 *       set: C6DOFIMU4_PWR_MGMT_2_REG
 *             -C6DOFIMU4_ALL_AXIS_EN
 *       set: C6DOFIMU4_PWR_MGMT_1_REG
 *             -C6DOFIMU4_CLKSEL_INTERNAL_20_MHZ
 *       set: C6DOFIMU4_INT_PIN_CFG_REG
 *             -C6DOFIMU4_INT_DRDY_PIN_ACT_HIGH
 *             -C6DOFIMU4_INT_DRDY_PIN_STAT_CLEARED
 *             -C6DOFIMU4_INT_STAT_CLEARED_STAT_REG_READ
 *       set: C6DOFIMU4_GYRO_FS_SEL_2000_DPS
 *             -C6DOFIMU4_ACCEL_FS_SEL_16_G
 * </pre>
 *
 * @description This function executes default configuration for c6DOF IMU 4 Click.
 */
void c6dofimu4_default_cfg ( c6dofimu4_t *ctx );

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
void c6dofimu4_generic_write ( c6dofimu4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 * 
 * @description This function reads data from the desired register.
 */
void c6dofimu4_generic_read ( c6dofimu4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic Single Byte Write function
 *
 * @param ctx       Click object.
 * @param reg_addr  Address where data be written
 * @param data_in   Data to be written
 *
 * @returns 0 - OK, 2 - Wrong address
 *
 * @description Function writes one byte data to the desired register.
 */
uint8_t c6dofimu4_write_byte ( c6dofimu4_t *ctx, uint8_t reg_addr, uint8_t data_in );

/**
 * @brief Generic Single Byte Read function
 *
 * @param ctx       Click object.
 * @param reg_addr  Address which from data be read
 * @param data_out  Memory location where data be stored
 *
 * @returns 0 - OK, 2 - Wrong address
 *
 * @description Function reads one byte data from the desired register.
 */
uint8_t c6dofimu4_read_byte ( c6dofimu4_t *ctx, uint8_t reg_addr, uint8_t *data_out );

/**
 * @brief Generic Word Write function
 *
 * @param ctx       Click object.
 * @param reg_addr  Address of the higher byte of data which will be written
 * @param data_in   Data to be written
 *
 * @returns 0 - OK, 2 - Wrong address
 *
 * @description Function writes 16bit data to the desired register.
 */
uint8_t c6dofimu4_write_word ( c6dofimu4_t *ctx, uint8_t reg_addr, uint16_t data_in );

/**
 * @brief Generic Word Read function
 *
 * @param ctx       Click object.
 * @param reg_addr  Address of the higher byte of data which will be read
 * @param data_out  Memory location where data be stored
 *
 * @returns 0 - OK, 2 - Wrong address
 *
 * @description Function reads 16bit data from the desired register.
 */
uint8_t c6dofimu4_read_word( c6dofimu4_t *ctx, uint8_t reg_addr, uint16_t *data_out );

/**
 * @brief Generic Sequential Write function
 *
 * @param ctx         Click object.
 * @param start_addr  Start address which from data writing be started
 * @param data_in     Data to be written
 * @param n_bytes     Number of bytes to be written
 *
 * @returns 0 - OK, 2 - Wrong address
 *
 * @description Function performs a sequential data writing starting from the desired address.
 */
uint8_t c6dofimu4_write_bytes ( c6dofimu4_t *ctx, uint8_t start_addr, uint8_t *data_in, uint8_t n_bytes );

/**
 * @brief Generic Sequential Read function
 *
 * @param ctx         Click object.
 * @param start_addr  Start address which from data reading be started
 * @param data_out    Memory location where data be stored
 * @param n_bytes     Number of bytes to be read
 *
 * @returns 0 - OK, 2 - Wrong address
 *
 * @description Function performs a sequential data reading starting from the desired address.
 */
uint8_t c6dofimu4_read_bytes ( c6dofimu4_t *ctx, uint8_t start_addr, uint8_t *data_out, uint8_t n_bytes );

/**
 * @brief Device Reset function
 *
 * @param ctx      Click object.
 * 
 * @description Function performs a device reset.
 */
void c6dofimu4_reset ( c6dofimu4_t *ctx );

/**
 * @brief Sync Pin Setting function
 *
 * @param ctx      Click object.
 * @param state    Desired state of the Sync pin
 *
 * @description Function sets the Sync pin on the desired state.
 */
void c6dofimu4_set_sync_pin ( c6dofimu4_t *ctx, uint8_t state );

/**
 * @brief Int Pin Check function
 *
 * @param ctx      Click object.
 * 
 * @returns 0 - Interrupt is not generated, 1 - Interrupt is generated
 *
 * @description Function checks does interrupt generated on the Int pin.
 */
uint8_t c6dofimu4_get_int_pin ( c6dofimu4_t *ctx );

/**
 * @brief Status Check function
 *
 * @param ctx       Click object.
 * @param bit_mask  Selects which interrupt bit of the Status register be checked
 *
 * @returns Masked interrupt status
 *
 * @description Function checks does the desired interrupt generated.
 */
uint8_t c6dofimu4_get_status ( c6dofimu4_t *ctx, uint8_t bit_mask );

/**
 * @brief Data Get function
 *
 * @param ctx        Click object.
 * @param accel_out  Memory location where accelerometer axis data be stored
 * @param gyro_out   Memory location where gyroscope axis data be stored
 * @param temp_out   Memory location where temperature data be stored
 *
 * @description Function performs a data reading and all necessary calculations to get accelerometer, gyroscope and temperature data.
 */
void c6dofimu4_get_data ( c6dofimu4_t *ctx, c6dofimu4_axis_t *accel_out, c6dofimu4_axis_t *gyro_out, int8_t *temp_out );

/**
 * @brief Full Scale Setting function
 *
 * @param ctx          Click object.
 * @param gyro_resol   Selects a full scale for gyroscope measurement [0-3]
 * @param accel_resol  Selects a full scale for accelerometer measurement [0-3]
 *
 * @returns 0 - OK, 3 - Full scale range error
 *
 * @description Function selects a measurement full scale range.
 */
uint8_t c6dofimu4_set_fsr ( c6dofimu4_t *ctx, uint8_t gyro_resol, uint8_t accel_resol );


#ifdef __cplusplus
}
#endif
#endif  // _C6DOFIMU4_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
