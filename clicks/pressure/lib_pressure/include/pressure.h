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
 * \file pressure.h
 *
 * \brief This file contains API for Pressure Click driver.
 *
 * \addtogroup pressure Pressure Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef _PRESSURE_H_
#define _PRESSURE_H_

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
 * \defgroup registers Registers
 * \{
 */

/**
 * \defgroup address Address
 * \{
 */
#define PRESSURE_REG_REF_P_XLB      0x8        //  Reference pressure (LSB)
#define PRESSURE_REG_REF_P_LSB      0x9        //  Reference pressure (middle)
#define PRESSURE_REG_REF_P_MSB      0xA        //  Reference pressure (MSB)
#define PRESSURE_REG_DEVICE_ID      0xF        //  Device identification
#define PRESSURE_REG_RES_CFG        0x10       //  Pressure resolution
#define PRESSURE_REG_CTRL_REG1      0x20       //  Control register 1
#define PRESSURE_REG_CTRL_REG2      0x21       //  Control register 2
#define PRESSURE_REG_CTRL_REG3      0x22       //  Control register 3
#define PRESSURE_REG_INT_CFG        0x23       //  Interrupt configuration
#define PRESSURE_REG_INT_SOURCE     0x24       //  Interrupt source
#define PRESSURE_REG_THSH_P_LSB     0x25       //  Threshold pressure (LSB)
#define PRESSURE_REG_THSH_P_MSB     0x26       //  Threshold pressure (MSB)
#define PRESSURE_REG_STATUS         0x27       //  Status register
#define PRESSURE_REG_PRESS_OUT_XLB  0x28       //  Pressure data (LSB)
#define PRESSURE_REG_PRESS_OUT_LSB  0x29       //  Pressure data (middle)
#define PRESSURE_REG_PRESS_OUT_MSB  0x2A       //  Pressure data (MSB)
#define PRESSURE_REG_TEMP_OUT_LSB   0x2B       //  Temperature data (LSB)
#define PRESSURE_REG_TEMP_OUT_MSB   0x2C       //  Temperature data (MSB)
#define PRESSURE_REG_AMP_CTRL       0x30       //  Analog front and control
/** \} */

/**
 * \defgroup id ID
 * \{
 */
#define PRESSURE_WHO_AM_I  0xBB
/** \} */

/**
 * \defgroup settings Settings
 * \{
 */

/**
 * \defgroup res_reg RES Register
 * \{
 */
#define PRESSURE_SET_RES_AVG_1    0x0
#define PRESSURE_SET_RES_AVG_2    0x1
#define PRESSURE_SET_RES_AVG_4    0x2
#define PRESSURE_SET_RES_AVG_8    0x3
#define PRESSURE_SET_RES_AVG_16   0x4
#define PRESSURE_SET_RES_AVG_32   0x5
#define PRESSURE_SET_RES_AVG_64   0x6
#define PRESSURE_SET_RES_AVG_128  0x7
#define PRESSURE_SET_RES_AVG_256  0x8
#define PRESSURE_SET_RES_AVG_384  0x9
#define PRESSURE_SET_RES_AVG_512  0xA
/** \} */

/**
 * \defgroup ctrl1_reg CTRL1 Register
 * \{
 */
#define PRESSURE_SET_PWR_UP_DEV          0x80
#define PRESSURE_SET_PWR_UP_INT          0x8
#define PRESSURE_SET_BLOCK_DATA_UPDATE   0x4
#define PRESSURE_SET_PWR_UP_DELTA_PRESS  0x2
#define PRESSURE_SET_SPI_3_WIRE          0x1
/** \} */

/**
 * \defgroup ctrl2_reg CTRL2 Register
 * \{
 */
#define PRESSURE_SET_REBOOT_MEM_CONTENT  0x80
#define PRESSURE_SET_SW_RESET            0x4
#define PRESSURE_SET_AUTOZERO_EN         0x2
#define PRESSURE_SET_ONESHOT_EN          0x1
#define PRESSURE_SET_NORMAL_MODE         0x0
/** \} */

/**
 * \defgroup ctrl3_reg CTRL3 Register
 * \{
 */
#define PRESSURE_SET_INT_ACT_LOW        0x80
#define PRESSURE_SET_INT_OPEN_DRAIN     0x40
#define PRESSURE_SET_INT_GND            0x0
#define PRESSURE_SET_INT_PRESS_HIGH     0x1
#define PRESSURE_SET_INT_PRESS_LOW      0x2
#define PRESSURE_SET_INT_P_LOW_OR_HIGH  0x3
#define PRESSURE_SET_INT_DATA_RDY       0x4
#define PRESSURE_SET_INT_TRI_STATE      0x7
/** \} */

/** \} */ //  End settings group

/**
 * \defgroup status Status
 * \{
 */

/**
 * \defgroup data_stat Data
 * \{
 */
#define PRESSURE_FLAG_MASK_P_DATA_OR   0x20
#define PRESSURE_FLAG_MASK_T_DATA_OR   0x10
#define PRESSURE_FLAG_MASK_P_DATA_RDY  0x2
#define PRESSURE_FLAG_MASK_T_DATA_RDY  0x1
/** \} */

/**
 * \defgroup int_stat Interrupt
 * \{
 */
#define PRESSURE_FLAG_MASK_INT_ACT      0x4
#define PRESSURE_FLAG_MASK_DIFF_P_LOW   0x2
#define PRESSURE_FLAG_MASK_DIFF_P_HIGH  0x1
/** \} */

/** \} */ //  End status group

/**
 * \defgroup trans_limit Transfer Limits
 * \{
 */
#define PRESSURE_DATA_NUMBER_MIN  1
#define PRESSURE_DATA_NUMBER_MAX  49
/** \} */

/** \} */ //  End registers group

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define PRESSURE_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.cs      = MIKROBUS( mikrobus, MIKROBUS_CS   ); \
    cfg.sck     = MIKROBUS( mikrobus, MIKROBUS_SCK  ); \
    cfg.sdo     = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.sdi     = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT  ); \
    cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL  ); \
    cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA  )
/** \} */

/** \} */ //  End macros group
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup types Types
 * \{
 */

/**
 * @brief Click master transfer function definition.
 */
typedef void ( *pressure_master_transfer_t )( struct pressure_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click error code definition.
 */
typedef enum
{
    PRESSURE_OK = 0x0,
    PRESSURE_ERR_INIT_DRV = 0xFD,
    PRESSURE_ERR_ADDR,
    PRESSURE_ERR_NDATA

} pressure_err_t;

/**
 * @brief Click driver selector definition.
 */
typedef enum
{
    PRESSURE_DRV_SEL_I2C = 0,
    PRESSURE_DRV_SEL_SPI

} pressure_drv_select_t;

/**
 * @brief Click output data rate definition.
 */
typedef enum
{
    PRESSURE_ODR_ONE_SHOT = 0,
    PRESSURE_ODR_P1HZ_T1HZ,
    PRESSURE_ODR_P7HZ_T1HZ,
    PRESSURE_ODR_P12HZ_T1HZ,
    PRESSURE_ODR_P25HZ_T1HZ,
    PRESSURE_ODR_P7HZ_T7HZ,
    PRESSURE_ODR_P12HZ_T12HZ,
    PRESSURE_ODR_P25HZ_T25HZ

} pressure_odr_t;

/**
 * @brief Click power control definition.
 */
typedef enum
{
    PRESSURE_PWR_DOWN = 0,
    PRESSURE_PWR_UP

} pressure_pwr_ctrl_t;

/**
 * @brief Click context object definition.
 */
typedef struct pressure_s
{
    // Output pin 
    digital_out_t cs;

    //  Interrupt pin.
    digital_in_t  int_pin;

    //  Modules.
    i2c_master_t  i2c;
    spi_master_t  spi;

    //  Context variables.
    uint8_t slave_addr;
    pin_name_t chip_select;
    pressure_master_transfer_t  write;
    pressure_master_transfer_t  read;

} pressure_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    //  Communication gpio pins.
    pin_name_t  cs;
    pin_name_t  sck;
    pin_name_t  sdo;
    pin_name_t  sdi;
    pin_name_t  scl;
    pin_name_t  sda;

    //  Additional gpio pins.
    pin_name_t  int_pin;

    //  Configuration variables.
    bool                    i2c_addr;
    uint32_t                i2c_speed;
    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

    pressure_drv_select_t   drv_sel;

} pressure_cfg_t;

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
 * @description This function initializes click configuration structure to
 * initial state.
 * @note All used pins will be set to unconnected state.
 */
void
pressure_cfg_setup( pressure_cfg_t *cfg );

/**
 * @brief Click Initialization function.
 *
 * @param ctx  Click object.
 * @param cfg  Click configuration structure.
 *
 * @returns 0x0  - Ok,
 *          0xFD - Driver init error.
 *
 * @description This function initializes all necessary pins and peripherals
 * used for this click.
 * @note All configuration settings will be entered from the configuration
 *       structure.
 */
pressure_err_t
pressure_init( pressure_t *ctx, pressure_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Pressure click.
 * @note Pressure click will be set to work in the default normal mode.
 */
void
pressure_default_cfg( pressure_t *ctx );

/**
 * @brief Generic Single Write function.
 *
 * @param ctx  Click object.
 * @param reg_addr  Register address.
 * @param data_in  Data to be written.
 *
 * @returns 0x0  - Ok,
 *          0xFE - Invalid register address.
 *
 * @description This function writes one data byte to the desired register.
 */
pressure_err_t
pressure_generic_single_write( pressure_t *ctx, uint8_t reg_addr,
                               uint8_t data_in );

/**
 * @brief Generic Multiple Write function.
 *
 * @param ctx  Click object.
 * @param reg_addr  Register address.
 * @param data_in  Data to be written.
 * @param n_data  Number of bytes to be written.
 *
 * @returns 0x0  - Ok,
 *          0xFE - Invalid register address,
 *          0xFF - Number of bytes is out of range.
 *
 * @description This function writes one or more data bytes starting from the
 * selected register.
 */
pressure_err_t
pressure_generic_multiple_write( pressure_t *ctx, uint8_t reg_addr,
                                 uint8_t *data_in, uint8_t n_data );

/**
 * @brief Generic Multiple Read function.
 *
 * @param ctx  Click object.
 * @param reg_addr  Register address.
 * @param data_out  Memory where read data be stored.
 * @param n_data  Number of bytes to be read.
 *
 * @returns 0x0  - Ok,
 *          0xFE - Invalid register address,
 *          0xFF - Number of bytes is out of range.
 *
 * @description This function reads one or more data bytes starting from the
 * selected register.
 */
pressure_err_t
pressure_generic_multiple_read( pressure_t *ctx, uint8_t reg_addr,
                                uint8_t *data_out, uint8_t n_data );

/**
 * @brief ID Read function.
 *
 * @param ctx  Click object.
 *
 * @returns Device ID byte.
 *
 * @description This function reads the device ID.
 */
uint8_t
pressure_read_id( pressure_t *ctx );

/**
 * @brief Output Data Rate Set function.
 *
 * @param ctx  Click object.
 * @param odr  Data Rate value.
 *
 * @description This function executes output data rate setting.
 */
void
pressure_set_odr( pressure_t *ctx, pressure_odr_t odr );

/**
 * @brief Device Power Control function.
 *
 * @param ctx  Click object.
 * @param state  Power state of the device [0 - Disable, 1 - Enable].
 *
 * @description This function performs the power control of the device.
 */
void
pressure_pwr_ctrl( pressure_t *ctx, pressure_pwr_ctrl_t state );

/**
 * @brief Interrupt Power Control function.
 *
 * @param ctx  Click object.
 * @param state  Interrupt power state [0 - Disable, 1 - Enable].
 *
 * @description This function performs the power control of the interrupt.
 */
void
pressure_pwr_ctrl_interrupt( pressure_t *ctx, pressure_pwr_ctrl_t state );

/**
 * @brief Data Update Block function.
 *
 * @param ctx  Click object.
 * @param state  0 - Not blocked, 1 - Blocked.
 *
 * @description This function allows output registers to not be updated until
 * MSB and LSB reading was done.
 * @note In other case the continuous data update will be performed.
 */
void
pressure_block_data_update( pressure_t *ctx, pressure_pwr_ctrl_t state );

/**
 * @brief Delta Pressure Power Control function.
 *
 * @param ctx  Click object.
 * @param state  Power state of delta pressure [0 - Disable, 1 - Enable].
 *
 * @description This function performs the power control of delta pressure
 * registers.
 */
void
pressure_pwr_ctrl_delta_pressure( pressure_t *ctx, pressure_pwr_ctrl_t state );

/**
 * @brief Memory Reboot function.
 *
 * @param ctx  Click object.
 *
 * @description This function is used to refresh the content of the internal
 * registers stored in the Flash memory block.
 */
void
pressure_reboot_memory( pressure_t *ctx );

/**
 * @brief Software Reset function.
 *
 * @param ctx  Click object.
 *
 * @description This function allows device to be reset to the power on
 * configuration.
 */
void
pressure_sw_reset( pressure_t *ctx );

/**
 * @brief Pressure Get function.
 *
 * @param ctx  Click object.
 *
 * @returns Pressure [mbar].
 *
 * @description This function returns the pressure converted to mbar.
 */
float
pressure_get_pressure( pressure_t *ctx );

/**
 * @brief Temperature Get function.
 *
 * @param ctx  Click object.
 *
 * @returns Temperature [Celsius degrees].
 *
 * @description This function returns the temperature converted to Celsius
 * degrees.
 */
float
pressure_get_temperature( pressure_t *ctx );

/**
 * @brief Status Get function.
 *
 * @param ctx  Click object.
 * @param bit_mask  Selects the flag bits which will be checked in status byte.
 *
 * @returns Status byte.
 *
 * @description This function allows user to check the desired flags in Status
 * register.
 */
uint8_t
pressure_get_status( pressure_t *ctx, uint8_t bit_mask );

/**
 * @brief INT Pin Get function.
 *
 * @param ctx  Click object.
 *
 * @returns Pin state [bool].
 *
 * @description This function returns true if the high voltage level detected
 * on the INT pin, or returns false if the low voltage level detected on the
 * INT pin.
 */
uint8_t
pressure_get_int_pin( pressure_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  //  _PRESSURE_H_

/** \} */ //  End public_function group
/// \}    //  End pressure group
/*! @} */
// ------------------------------------------------------------------------ END
