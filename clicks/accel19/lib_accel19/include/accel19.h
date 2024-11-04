/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file accel19.h
 * @brief This file contains API for Accel 19 Click Driver.
 */

#ifndef ACCEL19_H
#define ACCEL19_H

#ifdef __cplusplus
extern "C"{
#endif

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
#include "spi_specifics.h"

/*!
 * @addtogroup accel19 Accel 19 Click Driver
 * @brief API for configuring and manipulating Accel 19 Click driver.
 * @{
 */

/**
 * @defgroup accel19_reg Accel 19 Registers List
 * @brief List of registers of Accel 19 Click driver.
 */

/**
 * @addtogroup accel19_reg
 * @{
 */

/**
 * @brief Accel 19 description register.
 * @details Specified register for description of Accel 19 Click driver.
 */
#define ACCEL19_REG_OUT_T_L                       0x0D
#define ACCEL19_REG_OUT_T_H                       0x0E
#define ACCEL19_REG_WHO_AM_I                      0x0F
#define ACCEL19_REG_CTRL1                         0x20
#define ACCEL19_REG_CTRL2                         0x21
#define ACCEL19_REG_CTRL3                         0x22
#define ACCEL19_REG_CTRL4_INT1_PAD_CTRL           0x23
#define ACCEL19_REG_CTRL5_INT2_PAD_CTRL           0x24
#define ACCEL19_REG_CTRL6                         0x25
#define ACCEL19_REG_STATUS                        0x27
#define ACCEL19_REG_OUT_X_L                       0x28
#define ACCEL19_REG_OUT_X_H                       0x29
#define ACCEL19_REG_OUT_Y_L                       0x2A
#define ACCEL19_REG_OUT_Y_H                       0x2B
#define ACCEL19_REG_OUT_Z_L                       0x2C
#define ACCEL19_REG_OUT_Z_H                       0x2D    
#define ACCEL19_REG_FIFO_CTRL                     0x2E
#define ACCEL19_REG_FIFO_SAMPLES                  0x2F
#define ACCEL19_REG_TAP_THS_X                     0x30
#define ACCEL19_REG_TAP_THS_Y                     0x31
#define ACCEL19_REG_TAP_THS_Z                     0x32
#define ACCEL19_REG_INT_DUR                       0x33
#define ACCEL19_REG_WAKE_UP_THS                   0x34
#define ACCEL19_REG_WAKE_UP_DUR                   0x35
#define ACCEL19_REG_FREE_FALL                     0x36
#define ACCEL19_REG_STATUS_DUP                    0x37
#define ACCEL19_REG_WAKE_UP_SRC                   0x38
#define ACCEL19_REG_TAP_SRC                       0x39
#define ACCEL19_REG_SIXD_SRC                      0x3A
#define ACCEL19_REG_ALL_INT_SRC                   0x3B
#define ACCEL19_REG_X_OFS_USR                     0x3C
#define ACCEL19_REG_Y_OFS_USR                     0x3D
#define ACCEL19_REG_Z_OFS_USR                     0x3E
#define ACCEL19_REG_CTRL7                         0x3F

/*! @} */ // accel19_reg

/**
 * @defgroup accel19_set Accel 19 Registers Settings
 * @brief Settings for registers of Accel 19 Click driver.
 */

/**
 * @addtogroup accel19_set
 * @{
 */

/**
 * @brief Accel 19 description setting.
 * @details Specified setting for description of Accel 19 Click driver.
 */
#define ACCEL19_DEVICE_ID                         0x44

/**
 * @brief Accel 19 Power mode and data rate configuration setting.
 * @details Specified power mode and data rate configuration setting for description of Accel 19 Click driver.
 */
#define ACCEL19_CTRL1_ODR_BIT_MASK                0xF0
#define ACCEL19_CTRL1_ODR_POWER_DOWN              0x00
#define ACCEL19_CTRL1_ODR_LP_1_6_Hz               0x10
#define ACCEL19_CTRL1_ODR_HP_12_5_Hz              0x10
#define ACCEL19_CTRL1_ODR_HP_LP_12_5_Hz           0x20
#define ACCEL19_CTRL1_ODR_HP_LP_25_Hz             0x30
#define ACCEL19_CTRL1_ODR_HP_LP_50_Hz             0x40
#define ACCEL19_CTRL1_ODR_HP_LP_100_Hz            0x50
#define ACCEL19_CTRL1_ODR_HP_LP_200_Hz            0x60
#define ACCEL19_CTRL1_ODR_LP_200_Hz               0x70
#define ACCEL19_CTRL1_ODR_HP_400_Hz               0x70
#define ACCEL19_CTRL1_ODR_HP_800_Hz               0x80
#define ACCEL19_CTRL1_ODR_HP_1600_Hz              0x90

/**
 * @brief Accel 19 Mode selection setting.
 * @details Specified mode selection setting for description of Accel 19 Click driver.
 */
#define ACCEL19_CTRL1_OP_MODE_BIT_MASK            0x0C
#define ACCEL19_CTRL1_OP_MODE_LOW_POWER_MODE      0x00
#define ACCEL19_CTRL1_OP_MODE_HIGH_POWER_MODE     0x04
#define ACCEL19_CTRL1_OP_MODE_SINGLE_DATA_CONV    0x08

/**
 * @brief Accel 19 Low-power mode setting.
 * @details Specified low-power mode setting for description of Accel 19 Click driver.
 */
#define ACCEL19_CTRL1_LP_MODE_BIT_MASK            0x03
#define ACCEL19_CTRL1_LP_MODE1_RES_12_bit         0x00
#define ACCEL19_CTRL1_LP_MODE2_RES_14_bit         0x01
#define ACCEL19_CTRL1_LP_MODE3_RES_14_bit         0x02
#define ACCEL19_CTRL1_LP_MODE4_RES_14_bit         0x03

/**
 * @brief Accel 19 Soft reset data.
 * @details Specified soft reset data for description of Accel 19 Click driver.
 */
#define ACCEL19_CTRL2_SOFT_RESET                  0x40

/**
 * @brief Accel 19 data ready.
 * @details Specified data ready for description of Accel 19 Click driver.
 */
#define ACCEL19_INT_DRDY                          0x00
#define ACCEL19_STATUS_DRDY                       0x01

/**
 * @brief Accel 19 Bandwidth selection setting.
 * @details Specified Bandwidth selection setting for description of Accel 19 Click driver.
 */
#define ACCEL19_CTRL6_BW_FILT_BIT_MASK            0xC0
#define ACCEL19_CTRL6_BW_FILT_ODR_2               0x00
#define ACCEL19_CTRL6_BW_FILT_ODR_4               0x40
#define ACCEL19_CTRL6_BW_FILT_ODR_10              0x80
#define ACCEL19_CTRL6_BW_FILT_ODR_20              0xC0

/**
 * @brief Accel 19 FS selection setting.
 * @details Specified FS selection setting for description of Accel 19 Click driver.
 */
#define ACCEL19_CTRL6_FS_BIT_MASK                 0x30
#define ACCEL19_CTRL6_FS_2g                       0x00
#define ACCEL19_CTRL6_FS_4g                       0x10
#define ACCEL19_CTRL6_FS_8g                       0x20
#define ACCEL19_CTRL6_FS_16g                      0x30

/**
 * @brief Accel 19 device address setting.
 * @details Specified setting for device slave address selection of
 * Accel 19 Click driver.
 */
#define ACCEL19_SET_DEV_ADDR_0                    0x18
#define ACCEL19_SET_DEV_ADDR_1                    0x19

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b accel19_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ACCEL19_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define ACCEL19_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // accel19_set

/**
 * @defgroup accel19_map Accel 19 MikroBUS Map
 * @brief MikroBUS pin mapping of Accel 19 Click driver.
 */

/**
 * @addtogroup accel19_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Accel 19 Click to the selected MikroBUS.
 */
#define ACCEL19_MAP_MIKROBUS( cfg, mikrobus )       \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.in2 = MIKROBUS( mikrobus, MIKROBUS_PWM );   \
    cfg.in1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // accel19_map
/*! @} */ // accel19

/**
 * @brief Accel 19 Click driver selector.
 * @details Selects target driver interface of Accel 19 Click driver.
 */
typedef enum
{
    ACCEL19_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    ACCEL19_DRV_SEL_I2C       /**< I2C driver descriptor. */

} accel19_drv_t;

/**
 * @brief Accel 19 Click driver interface.
 * @details Definition of driver interface of Accel 19 Click driver.
 */
typedef err_t ( *accel19_master_io_t )( struct accel19_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Accel 19 Click context object.
 * @details Context object definition of Accel 19 Click driver.
 */
typedef struct accel19_s
{
    digital_in_t  in2;    /**< Description. */
    digital_in_t  in1;    /**< Description. */

    i2c_master_t  i2c;    /**< I2C driver object. */
    spi_master_t  spi;    /**< SPI driver object. */

    uint8_t     slave_address;       /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;         /**< Chip select pin descriptor (used for SPI driver). */
    accel19_drv_t  drv_sel;          /**< Master driver interface selector. */

    accel19_master_io_t  write_f;    /**< Master write function. */
    accel19_master_io_t  read_f;     /**< Master read function. */

} accel19_t;

/**
 * @brief Accel 19 Click configuration object.
 * @details Configuration object definition of Accel 19 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  miso;       /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;       /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;        /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;         /**< Chip select pin descriptor for SPI driver. */

    pin_name_t  in2;        /**< Description. */
    pin_name_t  in1;        /**< Description. */

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

    accel19_drv_t  drv_sel;                             /**< Master driver interface selector. */

} accel19_cfg_t;

/**
 * @brief Accel 19 axis data structure.
 * @details Axis object definition of Accel 19 Click driver.
 */
typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;

} accel19_axis_t;

/**
 * @brief Accel 19 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ACCEL19_OK = 0,
    ACCEL19_ERROR = -1

} accel19_return_value_t;

/*!
 * @addtogroup accel19 Accel 19 Click Driver
 * @brief API for configuring and manipulating Accel 19 Click driver.
 * @{
 */

/**
 * @brief Accel 19 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #accel19_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void accel19_cfg_setup ( accel19_cfg_t *cfg );

/**
 * @brief Accel 19 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #accel19_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #accel19_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void accel19_drv_interface_selection ( accel19_cfg_t *cfg, accel19_drv_t drv_sel );

/**
 * @brief Accel 19 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #accel19_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #accel19_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel19_init ( accel19_t *ctx, accel19_cfg_t *cfg );

/**
 * @brief Accel 19 default configuration function.
 * @details This function executes a default configuration of Accel 19
 * Click board.
 * @param[in] ctx : Click context object.
 * See #accel19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t accel19_default_cfg ( accel19_t *ctx );

/**
 * @brief Accel 19 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accel19_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel19_generic_write ( accel19_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 19 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accel19_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel19_generic_read ( accel19_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 19 get temperature function.
 * @details This function reads a temperature data  
 * of the LIS2DTW12 MEMS digital output dual motion and temperature sensor
 * on the Accel 19 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel19_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in degree Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel19_get_temperature ( accel19_t *ctx, float *temperature );

/**
 * @brief Accel 19 check device ID function.
 * @details This function rcheck device ID and communication
 * of the LIS2DTW12 MEMS digital output dual motion and temperature sensor
 * on the Accel 19 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel19_check_device_id ( accel19_t *ctx );

/**
 * @brief Accel 19 set control function.
 * @details This function set control 1 register 
 * of the LIS2DTW12 MEMS digital output dual motion and temperature sensor
 * on the Accel 19 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel19_t object definition for detailed explanation.
 * @param[in] odr : Data rate configuration.
 * @param[in] op_mode : Mode selection.
 * @param[in] lp_mode : Low-power mode selection.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel19_set_control ( accel19_t *ctx, uint8_t odr, uint8_t op_mode, uint8_t lp_mode );

/**
 * @brief Accel 19 soft reset function.
 * @details This function executes a software reset
 * of the LIS2DTW12 MEMS digital output dual motion and temperature sensor
 * on the Accel 19 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel19_soft_reset ( accel19_t *ctx );

/**
 * @brief Accel 19 get status function.
 * @details This function reads status register
 * of the LIS2DTW12 MEMS digital output dual motion and temperature sensor
 * on the Accel 19 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel19_t object definition for detailed explanation.
 * @param[out] status : Status data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel19_get_status ( accel19_t *ctx, uint8_t *status );

/**
 * @brief Accel 19 data ready function.
 * @details This function check data ready interrupt reporte
 * of the LIS2DTW12 MEMS digital output dual motion and temperature sensor
 * on the Accel 19 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel19_t object definition for detailed explanation.
 * @return @li @c 0 - Data is not ready,
 *         @li @c 1 - Data is ready.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t accel19_data_ready (accel19_t *ctx );

/**
 * @brief Accel 19 set full scale function.
 * @details This function set full scales 
 * of the LIS2DTW12 MEMS digital output dual motion and temperature sensor
 * on the Accel 19 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel19_t object definition for detailed explanation.
 * @param[in] full_scale : Full scales of ±2g/±4g/±8g/±16g.
 * @return @li @c 0 - Data is not ready,
 *         @li @c 1 - Data is ready.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel19_set_full_scale ( accel19_t *ctx, uint8_t full_scale );

/**
 * @brief Accel 19 set digital filtering cutoff function.
 * @details This function bandwidth selection 
 * of the LIS2DTW12 MEMS digital output dual motion and temperature sensor
 * on the Accel 19 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel19_t object definition for detailed explanation.
 * @param[in] bw_filt_odr : Digital filtering cutoff selection.
 * @return @li @c 0 - Data is not ready,
 *         @li @c 1 - Data is ready.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel19_set_bw_filt_odr ( accel19_t *ctx, uint8_t bw_filt_odr );

/**
 * @brief Accel 19 get accelerometer axis function.
 * @details This function get accelerometer data
 * of the LIS2DTW12 MEMS digital output dual motion and temperature sensor
 * on the Accel 19 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel19_t object definition for detailed explanation.
 * @param[out] axis : An object that contains X , Y and Z axis data.
 * @return @li @c 0 - Data is not ready,
 *         @li @c 1 - Data is ready.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel19_get_axis_data ( accel19_t *ctx, accel19_axis_t *axis );

/**
 * @brief Accel 19 get Interrupt 1 function.
 * @details This function get states of the Interrupt 1 ( INT pin )
 * of the LIS2DTW12 MEMS digital output dual motion and temperature sensor
 * on the Accel 19 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel19_t object definition for detailed explanation.
 * @return @li @c  0 - Low pin state,
 *         @li @c -1 - High pin state.
 *
 * @note None.
 */
uint8_t accel19_get_int_1 ( accel19_t *ctx );

/**
 * @brief Accel 19 get Interrupt 2 function.
 * @details This function get states of the Interrupt 2 ( PWM pin )
 * of the LIS2DTW12 MEMS digital output dual motion and temperature sensor
 * on the Accel 19 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel19_t object definition for detailed explanation.
 * @return @li @c  0 - Low pin state,
 *         @li @c -1 - High pin state.
 *
 * @note None.
 */
uint8_t accel19_get_int_2 ( accel19_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ACCEL19_H

/*! @} */ // accel19

// ------------------------------------------------------------------------ END
