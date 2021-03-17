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
 * \file altitude.h
 *
 * \brief This file contains API for Altitude Click driver.
 *
 * \addtogroup altitude Altitude Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef _ALTITUDE_H_
#define _ALTITUDE_H_

#include "drv_digital_in.h"
#include "drv_i2c_master.h"


// -------------------------------------------------------------- PUBLIC MACROS
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup dev_addr Device Address
 * \{
 */
#define ALTITUDE_SLAVE_ADDR  0x60
/** \} */

/**
 * \defgroup reg_addr Register Address
 * \{
 */
#define ALTITUDE_REG_STATUS            0x0
#define ALTITUDE_REG_OUT_P_MSB         0x1
#define ALTITUDE_REG_OUT_P_CSB         0x2
#define ALTITUDE_REG_OUT_P_LSB         0x3
#define ALTITUDE_REG_OUT_T_MSB         0x4
#define ALTITUDE_REG_OUT_T_LSB         0x5
#define ALTITUDE_REG_DR_STATUS         0x6
#define ALTITUDE_REG_OUT_P_DELTA_MSB   0x7
#define ALTITUDE_REG_OUT_P_DELTA_CSB   0x8
#define ALTITUDE_REG_OUT_P_DELTA_LSB   0x9
#define ALTITUDE_REG_OUT_T_DELTA_MSB   0xA
#define ALTITUDE_REG_OUT_T_DELTA_LSB   0xB
#define ALTITUDE_REG_WHO_AM_I          0xC
#define ALTITUDE_REG_FIFO_STATUS       0xD
#define ALTITUDE_REG_FIFO_DATA         0xE
#define ALTITUDE_REG_FIFO_SETUP        0xF
#define ALTITUDE_REG_TIME_DLY          0x10
#define ALTITUDE_REG_SYSMOD            0x11
#define ALTITUDE_REG_INT_SOURCE        0x12
#define ALTITUDE_REG_PT_DATA_CFG       0x13
#define ALTITUDE_REG_BAR_IN_MSB        0x14
#define ALTITUDE_REG_BAR_IN_LSB        0x15
#define ALTITUDE_REG_P_TGT_MSB         0x16
#define ALTITUDE_REG_P_TGT_LSB         0x17
#define ALTITUDE_REG_T_TGT             0x18
#define ALTITUDE_REG_P_WND_MSB         0x19
#define ALTITUDE_REG_P_WND_LSB         0x1A
#define ALTITUDE_REG_T_WND             0x1B
#define ALTITUDE_REG_P_MIN_MSB         0x1C
#define ALTITUDE_REG_P_MIN_CSB         0x1D
#define ALTITUDE_REG_P_MIN_LSB         0x1E
#define ALTITUDE_REG_T_MIN_MSB         0x1F
#define ALTITUDE_REG_T_MIN_LSB         0x20
#define ALTITUDE_REG_P_MAX_MSB         0x21
#define ALTITUDE_REG_P_MAX_CSB         0x22
#define ALTITUDE_REG_P_MAX_LSB         0x23
#define ALTITUDE_REG_T_MAX_MSB         0x24
#define ALTITUDE_REG_T_MAX_LSB         0x25
#define ALTITUDE_REG_CTRL1             0x26
#define ALTITUDE_REG_CTRL2             0x27
#define ALTITUDE_REG_CTRL3             0x28
#define ALTITUDE_REG_CTRL4             0x29
#define ALTITUDE_REG_CTRL5             0x2A
#define ALTITUDE_REG_OFF_P             0x2B
#define ALTITUDE_REG_OFF_T             0x2C
#define ALTITUDE_REG_OFF_H             0x2D
/** \} */

/**
 * \defgroup status Status
 * \{
 */
#define ALTITUDE_STATUS_FLAG_TDR   0x2
#define ALTITUDE_STATUS_FLAG_PDR   0x4
#define ALTITUDE_STATUS_FLAG_PTDR  0x8
#define ALTITUDE_STATUS_FLAG_TOW   0x20
#define ALTITUDE_STATUS_FLAG_POW   0x40
#define ALTITUDE_STATUS_FLAG_PTOW  0x80
/** \} */

/**
 * \defgroup int_src Interrupt Source Flag
 * \{
 */
#define ALTITUDE_INT_SOURCE_FLAG_DRDY  0x80
#define ALTITUDE_INT_SOURCE_FLAG_FIFO  0x40
#define ALTITUDE_INT_SOURCE_FLAG_PW    0x20
#define ALTITUDE_INT_SOURCE_FLAG_TW    0x10
#define ALTITUDE_INT_SOURCE_FLAG_PTH   0x8
#define ALTITUDE_INT_SOURCE_FLAG_TTH   0x4
#define ALTITUDE_INT_SOURCE_FLAG_PCHG  0x2
#define ALTITUDE_INT_SOURCE_FLAG_TCHG  0x1
/** \} */

/**
 * \defgroup control Control
 * \{
 */

/**
 * \defgroup mode Mode
 * \{
 */
#define ALTITUDE_CTRL1_SBYB  0x1
#define ALTITUDE_CTRL1_OST   0x2
#define ALTITUDE_CTRL1_CLR   0x3
#define ALTITUDE_CTRL1_RST   0x4
#define ALTITUDE_CTRL1_RAW   0x40
#define ALTITUDE_CTRL1_ALT   0x80
#define ALTITUDE_CTRL1_BAR   0x0
/** \} */

/**
 * \defgroup os_ratio Oversample Ratio
 * \{
 */
#define ALTITUDE_CTRL1_OS1_6MS      0x0
#define ALTITUDE_CTRL1_OS2_10MS     0x8
#define ALTITUDE_CTRL1_OS4_18MS     0x10
#define ALTITUDE_CTRL1_OS8_34MS     0x18
#define ALTITUDE_CTRL1_OS16_66MS    0x20
#define ALTITUDE_CTRL1_OS32_130MS   0x28
#define ALTITUDE_CTRL1_OS64_258MS   0x30
#define ALTITUDE_CTRL1_OS128_512MS  0x38
/** \} */

/**
 * \defgroup int_pol Interrupt Polarity
 * \{
 */
#define ALTITUDE_CTRL3_INT1_POL_HIGH  0x20
#define ALTITUDE_CTRL3_INT1_OD        0x10
#define ALTITUDE_CTRL3_INT2_POL_HIGH  0x2
#define ALTITUDE_CTRL3_INT2_OD        0x1
/** \} */

/**
 * \defgroup int_en Interrupt Enable
 * \{
 */
#define ALTITUDE_CTRL4_INT_EN_DRDY  0x80
#define ALTITUDE_CTRL4_INT_EN_FIFO  0x40
#define ALTITUDE_CTRL4_INT_EN_PW    0x20
#define ALTITUDE_CTRL4_INT_EN_TW    0x10
#define ALTITUDE_CTRL4_INT_EN_PTH   0x8
#define ALTITUDE_CTRL4_INT_EN_TTH   0x4
#define ALTITUDE_CTRL4_INT_EN_PCHG  0x2
#define ALTITUDE_CTRL4_INT_EN_TCHG  0x1
#define ALTITUDE_CTRL4_INT_DIS_ALL  0x0
/** \} */

/**
 * \defgroup int_pin Interrupt Pin
 * \{
 */
#define ALTITUDE_CTRL5_INT1_DRDY  0x80
#define ALTITUDE_CTRL5_INT2_DRDY  0x0
#define ALTITUDE_CTRL5_INT1_FIFO  0x40
#define ALTITUDE_CTRL5_INT2_FIFO  0x0
#define ALTITUDE_CTRL5_INT1_PW    0x20
#define ALTITUDE_CTRL5_INT2_PW    0x0
#define ALTITUDE_CTRL5_INT1_TW    0x10
#define ALTITUDE_CTRL5_INT2_TW    0x0
#define ALTITUDE_CTRL5_INT1_PTH   0x8
#define ALTITUDE_CTRL5_INT2_PTH   0x0
#define ALTITUDE_CTRL5_INT1_TTH   0x4
#define ALTITUDE_CTRL5_INT2_TTH   0x0
#define ALTITUDE_CTRL5_INT1_PCHG  0x2
#define ALTITUDE_CTRL5_INT2_PCHG  0x0
#define ALTITUDE_CTRL5_INT1_TCHG  0x1
#define ALTITUDE_CTRL5_INT2_TCHG  0x0
/** \} */

/**
 * \defgroup fifo FIFO
 * \{
 */
#define ALTITUDE_F_SETUP_FIFO_DISABLE        0x0
#define ALTITUDE_F_SETUP_FIFO_CIRCULAR_BUFF  0x40
#define ALTITUDE_F_SETUP_FIFO_STOP_MODE      0x80
/** \} */

/**
 * \defgroup data_event Data Event
 * \{
 */
#define ALTITUDE_PT_DATA_DR_EVENT_EN     0x4
#define ALTITUDE_PT_DATA_PD_EVENT_EN     0x2
#define ALTITUDE_PT_DATA_TD_EVENT_EN     0x1
#define ALTITUDE_PT_DATA_ALL_EVENTS_DIS  0x0
/** \} */

/** \} */ //  End control group

/**
 * \defgroup id ID
 * \{
 */
#define ALTITUDE_DEVICE_ID  0xC4
/** \} */

/**
 * \defgroup ndata_lim Data Transfer Limit
 * \{
 */
#define ALTITUDE_NDATA_TRANSFER_MIN  1
#define ALTITUDE_NDATA_TRANSFER_MAX  32
/** \} */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define ALTITUDE_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.it1 = MIKROBUS( mikrobus, MIKROBUS_INT ); \
  cfg.it2 = MIKROBUS( mikrobus, MIKROBUS_CS  )
/** \} */

/** \} */ //  End macros group
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click error codes.
 */
typedef enum
{
    ALTITUDE_OK = 0x0,
    ALTITUDE_ERR_INIT_DRV = 0xFD,
    ALTITUDE_ERR_ADDR,
    ALTITUDE_ERR_NDATA

} altitude_err_t;

/**
 * @brief Click system modes.
 */
typedef enum
{
    ALTITUDE_SYSMOD_STANDBY = 0,
    ALTITUDE_SYSMOD_ACTIVE

} altitude_sys_mode_t;

/**
 * @brief Click sensor modes.
 */
typedef enum
{
    ALTITUDE_SENSMOD_BAROMETER = 0,
    ALTITUDE_SENSMOD_ALTIMETER

} altitude_sens_mode_t;

/**
 * @brief Click contex object definition.
 */
typedef struct
{
    //  Interrupt pins.
    digital_in_t  it1;
    digital_in_t  it2;

    //  Module.
    i2c_master_t  i2c;

    //  Module slave address.
    uint8_t  slave_addr;

} altitude_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    //  Communication gpio pins.
    pin_name_t  scl;
    pin_name_t  sda;

    //  Additional gpio pins.
    pin_name_t  it1;
    pin_name_t  it2;

    //  Configuration variables.
    uint32_t  i2c_speed;
    uint8_t  i2c_addr;

} altitude_cfg_t;

/** \} */ //  End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS
/**
 * \defgroup public_function Public Function
 * \{
 */

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Configuration Object Setup function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to initial state.
 * @note All used pins will be set to unconnected state.
 */
void altitude_cfg_setup( altitude_cfg_t *cfg );

/**
 * @brief Click Initialization function.
 *
 * @param ctx  Click object.
 * @param cfg  Click configuration structure.
 *
 * @returns 0x0 - Ok, 0xFD - Driver init error.
 *
 * @description This function initializes all necessary peripherals and pins used for this click.
 */
altitude_err_t altitude_init( altitude_t *ctx, altitude_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes a default configuration for Altitude click.
 * @note This function sets click to active mode, and sensor will measure the altitude by default.
 * All necessary interrupts will be enabled in this function.
 */
void altitude_default_cfg( altitude_t *ctx );

/**
 * @brief Generic Single Write function.
 *
 * @param ctx  Click object.
 * @param reg_addr  Register address.
 * @param data_in  Data to be written.
 *
 * @returns 0x0 - Ok, 0xFE - Invalid register address.
 *
 * @description This function executes a single write operation to the desired register.
 */
altitude_err_t altitude_generic_single_write( altitude_t *ctx, uint8_t reg_addr, uint8_t data_in );

/**
 * @brief Generic Mutiple Write function.
 *
 * @param ctx  Click object.
 * @param reg_addr  Register address.
 * @param data_in  Data to be written.
 * @param n_data  Number of data bytes to be written.
 *
 * @returns 0x0 - Ok, 0xFE - Invalid register address, 0xFF - Number of bytes is out of range.
 *
 * @description This function executes a write operation of multiple data bytes starting from the selected register.
 */
altitude_err_t altitude_generic_multiple_write( altitude_t *ctx, uint8_t reg_addr, uint8_t *data_in, uint8_t n_data );

/**
 * @brief Generic Multiple Read function.
 *
 * @param ctx  Click object.
 * @param reg_addr  Register address.
 * @param data_out  Memory where read data be stored.
 * @param n_data  Number of data bytes to be read.
 *
 * @returns 0x0 - Ok, 0xFE - Invalid register address, 0xFF - Number of bytes is out of range.
 *
 * @description This function executes a read operation of multiple data bytes starting from the selected register.
 */
altitude_err_t altitude_generic_multiple_read( altitude_t *ctx, uint8_t reg_addr, uint8_t *data_out, uint8_t n_data );

/**
 * @brief System Mode Set function.
 *
 * @param ctx  Click object.
 * @param mode  0 - Standby mode, 1 - Active mode.
 *
 * @description This function sets the system mode.
 */
void altitude_set_system_mode( altitude_t *ctx, altitude_sys_mode_t mode );

/**
 * @brief Sensor Mode Set function.
 *
 * @param ctx  Click object.
 * @param mode  0 - Barometer, 1 - Altimeter.
 *
 * @description This function sets the sensor (measurement) mode.
 */
void altitude_set_sensor_mode( altitude_t *ctx, altitude_sens_mode_t mode );

/**
 * @brief Software Reset function.
 *
 * @param ctx  Click object.
 *
 * @description This function sets the all registers to default configuration state.
 */
void altitude_sw_reset( altitude_t *ctx );

/**
 * @brief Data Ready Status Get function.
 *
 * @param ctx  Click object.
 * @param flag_mask  Selects a bits which will be compared.
 *
 * @returns Status byte.
 *
 * @description This function reads Status register and allows comparison of the selected data ready flags.
 */
uint8_t altitude_get_drdy_status( altitude_t *ctx, uint8_t flag_mask );

/**
 * @brief Interrupt Status Get function.
 *
 * @param ctx  Click object.
 * @param flag_mask  Selects a bits which will be compared.
 *
 * @returns Status byte.
 *
 * @description This function reads Interrupt Source register and allows comparison of the selected interrupt flags.
 */
uint8_t altitude_get_int_status( altitude_t *ctx, uint8_t flag_mask );

/**
 * @brief INT1 Pin Get function.
 *
 * @param ctx  Click object.
 *
 * @returns Pin state [bool].
 *
 * @description This function returns a true value if high voltage level was detected on the pin,
 * or returns a false value if low voltage level was detected on the pin.
 */
uint8_t altitude_get_int1_pin( altitude_t *ctx );

/**
 * @brief INT2 Pin Get function.
 *
 * @param ctx  Click object.
 *
 * @returns Pin state [bool].
 *
 * @description This function returns a true value if high voltage level was detected on the pin,
 * or returns a false value if low voltage level was detected on the pin.
 */
uint8_t altitude_get_int2_pin( altitude_t *ctx );

/**
 * @brief Altitude Get function.
 *
 * @param ctx  Click object.
 *
 * @returns Altitude value in meters [m].
 *
 * @description This function reads the altitude and converts this value to meters.
 */
float altitude_get_altitude( altitude_t *ctx );

/**
 * @brief Pressure Get function.
 *
 * @param ctx  Click object.
 *
 * @returns Pressure value in millibars [mbar].
 *
 * @description This function reads the pressure and converts this value to millibars.
 */
float altitude_get_pressure( altitude_t *ctx );

/**
 * @brief Temperature Get function.
 *
 * @param ctx  Click object.
 *
 * @returns Temeprature value in Celsius degrees [deg C].
 *
 * @description This function reads the temperature and converts this value to Celsius degrees.
 */
float altitude_get_temperature( altitude_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  //  _ALTITUDE_H_

/** \} */ //  End public_function group
/// \}    //  End altitude group
/*! @} */
// ------------------------------------------------------------------------ END
