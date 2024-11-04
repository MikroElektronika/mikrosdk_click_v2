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
 * @file c6dofimu23.h
 * @brief This file contains API for 6DOF IMU 23 Click Driver.
 */

#ifndef C6DOFIMU23_H
#define C6DOFIMU23_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup c6dofimu23 6DOF IMU 23 Click Driver
 * @brief API for configuring and manipulating 6DOF IMU 23 Click driver.
 * @{
 */

/**
 * @defgroup c6dofimu23_reg 6DOF IMU 23 Registers List
 * @brief List of registers of 6DOF IMU 23 Click driver.
 */

/**
 * @addtogroup c6dofimu23_reg
 * @{
 */

 /**
 * @brief 6DOF IMU 23 description offset bank 0.
 * @details Specified offset for description of 6DOF IMU 23 Click driver.
 */
#define C6DOFIMU23_OFFSET_X_DATA                0x00
#define C6DOFIMU23_OFFSET_Y_DATA                0x01
#define C6DOFIMU23_OFFSET_Z_DATA                0x02
#define C6DOFIMU23_OFFSET_TEMPERATURE_1         0x03
#define C6DOFIMU23_OFFSET_ACCEL_X_DATA          0x04
#define C6DOFIMU23_OFFSET_ACCEL_Y_DATA          0x05
#define C6DOFIMU23_OFFSET_ACCEL_Z_DATA          0x06
#define C6DOFIMU23_OFFSET_TEMPERATURE_2         0x07
#define C6DOFIMU23_OFFSET_LR_ACCEL_X_DATA       0x08
#define C6DOFIMU23_OFFSET_LR_ACCEL_Y_DATA       0x09
#define C6DOFIMU23_OFFSET_LR_ACCEL_Z_DATA       0x0A
#define C6DOFIMU23_OFFSET_FIXED_VALUE           0x0B
#define C6DOFIMU23_OFFSET_FILTER_SETTINGS_YZ    0x0C
#define C6DOFIMU23_OFFSET_FILTER_SETTINGS_X     0x0E
#define C6DOFIMU23_OFFSET_TEMPERATURE_DIF       0x0F
#define C6DOFIMU23_OFFSET_DC_TRIGGER            0x16
#define C6DOFIMU23_OFFSET_TEST                  0x17
#define C6DOFIMU23_OFFSET_RESET                 0x18
#define C6DOFIMU23_OFFSET_MODE                  0x19
#define C6DOFIMU23_OFFSET_ID                    0x1B
#define C6DOFIMU23_OFFSET_HW_REV                0x1C
#define C6DOFIMU23_OFFSET_ID_CODE_3             0x1D
#define C6DOFIMU23_OFFSET_ID_CODE_4             0x1E
#define C6DOFIMU23_OFFSET_BANK_SELECTION        0x1F

 /**
 * @brief 6DOF IMU 23 description offset bank 1.
 * @details Specified offset for description of 6DOF IMU 23 Click driver.
 */
#define C6DOFIMU23_OFFSET_SELF_TEST_ACCEL       0x11
#define C6DOFIMU23_OFFSET_SELF_TEST_GYRO        0x12
#define C6DOFIMU23_OFFSET_WHO_AM_I              0x0E

 /**
 * @brief 6DOF IMU 23 description offset bank 6.
 * @details Specified offset for description of 6DOF IMU 23 Click driver.
 */
#define C6DOFIMU23_OFFSET_ODR_CFG_1             0x11
#define C6DOFIMU23_OFFSET_ODR_CFG_2             0x13
#define C6DOFIMU23_OFFSET_ODR_CFG_3             0x14
#define C6DOFIMU23_OFFSET_ODR_CFG_4             0x14
#define C6DOFIMU23_OFFSET_ODR_CFG_5             0x15
#define C6DOFIMU23_OFFSET_ODR_CFG_6             0x16

 /**
 * @brief 6DOF IMU 23 description offset bank 7.
 * @details Specified offset for description of 6DOF IMU 23 Click driver.
 */
#define C6DOFIMU23_OFFSET_SENSITIVITY_CFG       0x14

/*! @} */ // c6dofimu23_reg

/**
 * @defgroup c6dofimu23_set 6DOF IMU 23 Registers Settings
 * @brief Settings for registers of 6DOF IMU 23 Click driver.
 */

/**
 * @addtogroup c6dofimu23_set
 * @{
 */

/**
 * @brief 6DOF IMU 23 fixed value.
 * @details Specified setting for fixed value of 6DOF IMU 23 Click driver.
 */
#define C6DOFIMU23_FIXED_VALUE                  0xAA55

/**
 * @brief 6DOF IMU 23 resolution.
 * @details Specified setting for calculations of 6DOF IMU 23 Click driver.
 */
#define C6DOFIMU23_DATA_RESOLUTION              32768.0f
#define C6DOFIMU23_ACCEL_FS_DEFAULT             16.384f
#define C6DOFIMU23_GYRO_FS_DEFAULT              655.36f
#define C6DOFIMU23_TEMP_DATA_RESOLUTION         20.0f
#define C6DOFIMU23_TEMP_DATA_OFFSET             25.0f

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b c6dofimu23_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define C6DOFIMU23_SET_DATA_SAMPLE_EDGE         SET_SPI_DATA_SAMPLE_EDGE
#define C6DOFIMU23_SET_DATA_SAMPLE_MIDDLE       SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // c6dofimu23_set

/**
 * @defgroup c6dofimu23_map 6DOF IMU 23 MikroBUS Map
 * @brief MikroBUS pin mapping of 6DOF IMU 23 Click driver.
 */

/**
 * @addtogroup c6dofimu23_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 6DOF IMU 23 Click to the selected MikroBUS.
 */
#define C6DOFIMU23_MAP_MIKROBUS( cfg, mikrobus )    \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST );  \
    cfg.odr  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // c6dofimu23_map
/*! @} */ // c6dofimu23

/**
 * @brief 6DOF IMU 23 Click context object.
 * @details Context object definition of 6DOF IMU 23 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;           /**< Reset signal (active low). */

    // Input pins
    digital_in_t odr;            /**< Output Data-ready for synchronous sensor data readings. */

    // Modules
    spi_master_t spi;            /**< SPI driver object. */

    pin_name_t   chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

    float acc_fs;               /**< Accel full-scale range. */
    float gyro_fs;              /**< Gyro full-scale range. */

} c6dofimu23_t;

/**
 * @brief 6DOF IMU 23 Click configuration object.
 * @details Configuration object definition of 6DOF IMU 23 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;     /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;      /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rst;    /**< Reset signal (active low). */
    pin_name_t odr;    /**< Output Data-ready for synchronous sensor data readings. */


    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} c6dofimu23_cfg_t;

/**
 * @brief 6DOF IMU 23 Click axes data structure.
 * @details Axes data object definition of of 6DOF IMU 23 Click driver.
 */
typedef struct
{
    float x;    /**< X axis. */
    float y;    /**< Y axis. */
    float z;    /**< Z axis. */

} c6dofimu23_axis_t;

/**
 * @brief 6DOF IMU 23 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C6DOFIMU23_OK = 0,
    C6DOFIMU23_ERROR = -1

} c6dofimu23_return_value_t;

/*!
 * @addtogroup c6dofimu23 6DOF IMU 23 Click Driver
 * @brief API for configuring and manipulating 6DOF IMU 23 Click driver.
 * @{
 */

/**
 * @brief 6DOF IMU 23 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c6dofimu23_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c6dofimu23_cfg_setup ( c6dofimu23_cfg_t *cfg );

/**
 * @brief 6DOF IMU 23 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #c6dofimu23_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c6dofimu23_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu23_init ( c6dofimu23_t *ctx, c6dofimu23_cfg_t *cfg );

/**
 * @brief 6DOF IMU 23 default configuration function.
 * @details This function executes a default configuration of 6DOF IMU 23
 * Click board.
 * @param[in] ctx : Click context object.
 * See #c6dofimu23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c6dofimu23_default_cfg ( c6dofimu23_t *ctx );

/**
 * @brief 6DOF IMU 23 reg write function.
 * @details This function writes a data word to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c6dofimu23_t object definition for detailed explanation.
 * @param[in] address : Register offset with respect to the bank that is currently selected.
 * @param[in] data_in : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu23_reg_write ( c6dofimu23_t *ctx, uint8_t address, uint16_t data_in );

/**
 * @brief 6DOF IMU 23 reg read function.
 * @details This function reads a data word from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c6dofimu23_t object definition for detailed explanation.
 * @param[in] address : Register offset with respect to the bank that is currently selected.
 * @param[out] data_out : 16-bit output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu23_reg_read ( c6dofimu23_t *ctx, uint8_t address, uint16_t *data_out );

/**
 * @brief 6DOF IMU 23 check communication function.
 * @details This function checks the communication by reading and verifying the fixed value register from bank 0.
 * @param[in] ctx : Click context object.
 * See #c6dofimu23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu23_check_communication ( c6dofimu23_t *ctx );

/**
 * @brief 6DOF IMU 23 device enable function.
 * @details This function enables the device by setting the RST pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #c6dofimu23_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void c6dofimu23_device_enable ( c6dofimu23_t *ctx );

/**
 * @brief 6DOF IMU 23 device disable function.
 * @details This function disables the device by setting the RST pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #c6dofimu23_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void c6dofimu23_device_disable ( c6dofimu23_t *ctx );

/**
 * @brief 6DOF IMU 23 get odr function.
 * @details This function gets states of the output data-ready ( ODR-INT ) pin 
 * of the IIM-20670, SmartIndustrial 6-axis MotionTracking MEMS
 * on the 6DOF IMU 23 Click board.
 * @param[in] ctx : Click context object.
 * See #c6dofimu23_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t c6dofimu23_get_odr ( c6dofimu23_t *ctx );

/**
 * @brief 6DOF IMU 23 get the accel sensor axes function.
 * @details This function reads the accelerometer sensor axes measurement data 
 * of the IIM-20670, SmartIndustrial 6-axis MotionTracking MEMS
 * on the 6DOF IMU 23 Click board.
 * @param[in] ctx : Click context object.
 * See #c6dofimu23_t object definition for detailed explanation.
 * @param[out] acc_axis : Linear acceleration output data object (mg).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu23_get_accel_data ( c6dofimu23_t *ctx, c6dofimu23_axis_t *acc_axis );

/**
 * @brief 6DOF IMU 23 get the gyro sensor axes function.
 * @details This function reads the gyroscope sensor axes measurement data 
 * of the IIM-20670, SmartIndustrial 6-axis MotionTracking MEMS
 * on the 6DOF IMU 23 Click board.
 * @param[in] ctx : Click context object.
 * See #c6dofimu23_t object definition for detailed explanation.
 * @param[out] gyro_axis : Angular rate output data object (dps).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu23_get_gyro_data ( c6dofimu23_t *ctx, c6dofimu23_axis_t *gyro_axis );

/**
 * @brief 6DOF IMU 23 get the internal temperature function.
 * @details This function reads the internal temperature sensor measurement in degrees Celsius
 * of the IIM-20670, SmartIndustrial 6-axis MotionTracking MEMS
 * on the 6DOF IMU 23 Click board.
 * @param[in] ctx : Click context object.
 * See #c6dofimu23_t object definition for detailed explanation.
 * @param[out] temperature : Internal temperature (degrees Celsius).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu23_get_temperature ( c6dofimu23_t *ctx, float *temperature );

#ifdef __cplusplus
}
#endif
#endif // C6DOFIMU23_H

/*! @} */ // c6dofimu23

// ------------------------------------------------------------------------ END
