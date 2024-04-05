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
 * @file silentstep4.h
 * @brief This file contains API for Silent Step 4 Click Driver.
 */

#ifndef SILENTSTEP4_H
#define SILENTSTEP4_H

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
 * @addtogroup silentstep4 Silent Step 4 Click Driver
 * @brief API for configuring and manipulating Silent Step 4 Click driver.
 * @{
 */

/**
 * @defgroup silentstep4_reg Silent Step 4 Registers List
 * @brief List of registers of Silent Step 4 Click driver.
 */

/**
 * @addtogroup silentstep4_reg
 * @{
 */

 /**
 * @brief Silent Step 4 registers.
 * @details Specified registers of Silent Step 4 Click driver.
 */
#define SILENTSTEP4_REG_GCONF                   0x00
#define SILENTSTEP4_REG_GSTAT                   0x01
#define SILENTSTEP4_REG_IFCNT                   0x02
#define SILENTSTEP4_REG_NODECONF                0x03
#define SILENTSTEP4_REG_IOIN                    0x04
#define SILENTSTEP4_REG_DRV_CONF                0x0A
#define SILENTSTEP4_REG_GLOBAL_SCALER           0x0B
#define SILENTSTEP4_REG_IHOLD_IRUN              0x10
#define SILENTSTEP4_REG_TPOWERDOWN              0x11
#define SILENTSTEP4_REG_TSTEP                   0x12
#define SILENTSTEP4_REG_TPWMTHRS                0x13
#define SILENTSTEP4_REG_TCOOLTHRS               0x14
#define SILENTSTEP4_REG_THIGH                   0x15
#define SILENTSTEP4_REG_DIRECT_MODE             0x2D
#define SILENTSTEP4_REG_ENCMODE                 0x38
#define SILENTSTEP4_REG_X_ENC                   0x39
#define SILENTSTEP4_REG_ENC_CONST               0x3A
#define SILENTSTEP4_REG_ENC_STATUS              0x3B
#define SILENTSTEP4_REG_ENC_LATCH               0x3C
#define SILENTSTEP4_REG_ADC_VSUPPLY_AIN         0x50
#define SILENTSTEP4_REG_ADC_TEMP                0x51
#define SILENTSTEP4_REG_OTW_OV_VTH              0x52
#define SILENTSTEP4_REG_MSLUT_0                 0x60
#define SILENTSTEP4_REG_MSLUT_1                 0x61
#define SILENTSTEP4_REG_MSLUT_2                 0x62
#define SILENTSTEP4_REG_MSLUT_3                 0x63
#define SILENTSTEP4_REG_MSLUT_4                 0x64
#define SILENTSTEP4_REG_MSLUT_5                 0x65
#define SILENTSTEP4_REG_MSLUT_6                 0x66
#define SILENTSTEP4_REG_MSLUT_7                 0x67
#define SILENTSTEP4_REG_MSLUTSEL                0x68
#define SILENTSTEP4_REG_MSLUTSTART              0x69
#define SILENTSTEP4_REG_MSCNT                   0x6A
#define SILENTSTEP4_REG_MSCURACT                0x6B
#define SILENTSTEP4_REG_CHOPCONF                0x6C
#define SILENTSTEP4_REG_COOLCONF                0x6D
#define SILENTSTEP4_REG_DRV_STATUS              0x6F
#define SILENTSTEP4_REG_PWMCONF                 0x70
#define SILENTSTEP4_REG_PWM_SCALE               0x71
#define SILENTSTEP4_REG_PWM_AUTO                0x72
#define SILENTSTEP4_REG_SG4_THRS                0x74
#define SILENTSTEP4_REG_SG4_RESULT              0x75
#define SILENTSTEP4_REG_SG4_IND                 0x76

/**
 * @brief Silent Step 4 PCA9538A registers.
 * @details Specified PCA9538A registers of Silent Step 4 Click driver.
 */
#define SILENTSTEP4_PCA9538A_REG_INPUT          0x00
#define SILENTSTEP4_PCA9538A_REG_OUTPUT         0x01
#define SILENTSTEP4_PCA9538A_REG_POLARITY       0x02
#define SILENTSTEP4_PCA9538A_REG_CONFIG         0x03

/**
 * @defgroup silentstep4_set Silent Step 4 Registers Settings
 * @brief Settings for registers of Silent Step 4 Click driver.
 */

/**
 * @addtogroup silentstep4_set
 * @{
 */

/**
* @brief Silent Step 4 version settings.
* @details Specified version settings of Silent Step 4 Click driver.
*/
#define SILENTSTEP4_IOIN_VERSION_MASK           0xFF000000ul
#define SILENTSTEP4_IOIN_VERSION_DEFAULT        0x40000000ul

/**
 * @brief Silent Step 4 PCA9538A pin mask.
 * @details Specified PCA9538A pin mask of Silent Step 4 Click driver.
 */
#define SILENTSTEP4_PIN_EN                      0x01
#define SILENTSTEP4_PIN_SLEEP                   0x02
#define SILENTSTEP4_PIN_DIAG0                   0x04
#define SILENTSTEP4_PIN_DIAG1                   0x08
#define SILENTSTEP4_PIN_OV                      0x10

/**
 * @brief Silent Step 4 PCA9538A pin direction config.
 * @details Specified PCA9538A pin direction config of Silent Step 4 Click driver.
 */
#define SILENTSTEP4_PCA9538A_DEFAULT_CONFIG     0xFC

/**
 * @brief Silent Step 4 direction setting.
 * @details Specified setting for direction of Silent Step 4 Click driver.
 */
#define SILENTSTEP4_DIR_CW                      0
#define SILENTSTEP4_DIR_CCW                     1

/**
 * @brief Silent Step 4 pin logic state setting.
 * @details Specified setting for pin logic state of Silent Step 4 Click driver.
 */
#define SILENTSTEP4_PIN_STATE_LOW               0
#define SILENTSTEP4_PIN_STATE_HIGH              1

/**
 * @brief Silent Step 4 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define SILENTSTEP4_SPEED_VERY_SLOW             0
#define SILENTSTEP4_SPEED_SLOW                  1
#define SILENTSTEP4_SPEED_MEDIUM                2
#define SILENTSTEP4_SPEED_FAST                  3
#define SILENTSTEP4_SPEED_VERY_FAST             4

/**
 * @brief Silent Step 4 off time settings.
 * @details Specified setting for off time that controls duration of slow decay phase.
 */
#define SILENTSTEP4_TOFF_MASK                   0x0000000Ful
#define SILENTSTEP4_TOFF_SHIFT                  0
#define SILENTSTEP4_TOFF_DRIVER_DISABLE         0
#define SILENTSTEP4_TOFF_MIN                    1
#define SILENTSTEP4_TOFF_DEFAULT                4
#define SILENTSTEP4_TOFF_MAX                    15

/**
 * @brief Silent Step 4 step resolution settings.
 * @details Specified setting for micro step resolution.
 */
#define SILENTSTEP4_MRES_MASK                   0x0F000000ul
#define SILENTSTEP4_MRES_SHIFT                  24
#define SILENTSTEP4_MRES_256                    0
#define SILENTSTEP4_MRES_128                    1
#define SILENTSTEP4_MRES_64                     2
#define SILENTSTEP4_MRES_32                     3
#define SILENTSTEP4_MRES_16                     4
#define SILENTSTEP4_MRES_8                      5
#define SILENTSTEP4_MRES_4                      6
#define SILENTSTEP4_MRES_2                      7
#define SILENTSTEP4_MRES_FULLSTEP               8

/**
 * @brief Silent Step 4 run current settings.
 * @details Specified setting for motor run current.
 */
#define SILENTSTEP4_IRUN_MASK                   0x00000F00ul
#define SILENTSTEP4_IRUN_SHIFT                  8
#define SILENTSTEP4_IRUN_MIN                    0
#define SILENTSTEP4_IRUN_DEFAULT                16
#define SILENTSTEP4_IRUN_MAX                    31

/**
 * @brief Silent Step 4 device address setting.
 * @details Specified setting for device slave address selection of
 * Silent Step 4 Click driver.
 */
#define SILENTSTEP4_DEVICE_ADDRESS_A1A0_00      0x70
#define SILENTSTEP4_DEVICE_ADDRESS_A1A0_01      0x71
#define SILENTSTEP4_DEVICE_ADDRESS_A1A0_10      0x72
#define SILENTSTEP4_DEVICE_ADDRESS_A1A0_11      0x73

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b silentstep4_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define SILENTSTEP4_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define SILENTSTEP4_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // silentstep4_set

/**
 * @defgroup silentstep4_map Silent Step 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Silent Step 4 Click driver.
 */

/**
 * @addtogroup silentstep4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Silent Step 4 Click to the selected MikroBUS.
 */
#define SILENTSTEP4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.step = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // silentstep4_map
/*! @} */ // silentstep4

/**
 * @brief Silent Step 4 Click context object.
 * @details Context object definition of Silent Step 4 Click driver.
 */
typedef struct silentstep4_s
{
    digital_out_t dir;                  /**< Direction control pin. */
    digital_out_t rst;                  /**< PCA9538A reset pin. */
    digital_out_t step;                 /**< Step signal pin. */

    digital_in_t int_pin;               /**< PCA9538A interrupt pin. */

    i2c_master_t i2c;                   /**< I2C driver object. */
    spi_master_t spi;                   /**< SPI driver object. */

    uint8_t      slave_address;         /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;           /**< Chip select pin descriptor (used for SPI driver). */

} silentstep4_t;

/**
 * @brief Silent Step 4 Click configuration object.
 * @details Configuration object definition of Silent Step 4 Click driver.
 */
typedef struct
{
    pin_name_t scl;                     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                     /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                      /**< Chip select pin descriptor for SPI driver. */
    pin_name_t dir;                     /**< Direction control pin. */
    pin_name_t rst;                     /**< PCA9538A reset pin. */
    pin_name_t step;                    /**< Step signal pin. */
    pin_name_t int_pin;                 /**< PCA9538A interrupt pin. */

    uint32_t   i2c_speed;               /**< I2C serial speed. */
    uint8_t    i2c_address;             /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} silentstep4_cfg_t;

/**
 * @brief Silent Step 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SILENTSTEP4_OK = 0,
    SILENTSTEP4_ERROR = -1

} silentstep4_return_value_t;

/*!
 * @addtogroup silentstep4 Silent Step 4 Click Driver
 * @brief API for configuring and manipulating Silent Step 4 Click driver.
 * @{
 */

/**
 * @brief Silent Step 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #silentstep4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void silentstep4_cfg_setup ( silentstep4_cfg_t *cfg );

/**
 * @brief Silent Step 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #silentstep4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #silentstep4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep4_init ( silentstep4_t *ctx, silentstep4_cfg_t *cfg );

/**
 * @brief Silent Step 4 default configuration function.
 * @details This function executes a default configuration of Silent Step 4
 * click board.
 * @param[in] ctx : Click context object.
 * See #silentstep4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t silentstep4_default_cfg ( silentstep4_t *ctx );

/**
 * @brief Silent Step 4 write reg function.
 * @details This function writes a desired 32-bit data to the selected register 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #silentstep4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 32-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep4_write_reg ( silentstep4_t *ctx, uint8_t reg, uint32_t data_in );

/**
 * @brief Silent Step 4 read reg function.
 * @details This function reads 32-bit data from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #silentstep4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read 32-bit data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep4_read_reg ( silentstep4_t *ctx, uint8_t reg, uint32_t *data_out );

/**
 * @brief Silent Step 4 pca write reg function.
 * @details This function writes a desired data byte to the selected PCA9538A register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #silentstep4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep4_pca_write_reg ( silentstep4_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Silent Step 4 pca read reg function.
 * @details This function reads data from the selected PCA9538A register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #silentstep4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep4_pca_read_reg ( silentstep4_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Silent Step 4 check com function.
 * @details This function checks the SPI communication by reading and verifying the device version.
 * @param[in] ctx : Click context object.
 * See #silentstep4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep4_check_com ( silentstep4_t *ctx );

/**
 * @brief Silent Step 4 get en pin function.
 * @details This function reads the enable pin logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep4_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep4_get_en_pin ( silentstep4_t *ctx, uint8_t *state );

/**
 * @brief Silent Step 4 set en pin function.
 * @details This function sets the enable pin logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep4_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep4_set_en_pin ( silentstep4_t *ctx, uint8_t state );

/**
 * @brief Silent Step 4 get sleep pin function.
 * @details This function reads the sleep pin logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep4_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep4_get_sleep_pin ( silentstep4_t *ctx, uint8_t *state );

/**
 * @brief Silent Step 4 set sleep pin function.
 * @details This function sets the sleep pin logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep4_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep4_set_sleep_pin ( silentstep4_t *ctx, uint8_t state );

/**
 * @brief Silent Step 4 get diag0 pin function.
 * @details This function reads the diag0 pin logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep4_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep4_get_diag0_pin ( silentstep4_t *ctx, uint8_t *state );

/**
 * @brief Silent Step 4 get diag1 pin function.
 * @details This function reads the diag1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep4_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep4_get_diag1_pin ( silentstep4_t *ctx, uint8_t *state );

/**
 * @brief Silent Step 4 get ov pin function.
 * @details This function reads the ov pin logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep4_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep4_get_ov_pin ( silentstep4_t *ctx, uint8_t *state );

/**
 * @brief Silent Step 4 enable device function.
 * @details This function enables the device by setting the ENABLE pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep4_enable_device ( silentstep4_t *ctx );

/**
 * @brief Silent Step 4 disable device function.
 * @details This function disables the device by setting the ENABLE pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep4_disable_device ( silentstep4_t *ctx );

/**
 * @brief Silent Step 4 set direction function.
 * @details This function sets the motor direction by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep4_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Clockwise,
 *                  @li @c 1 - Counter-Clockwise.
 * @return None.
 * @note None.
 */
void silentstep4_set_direction ( silentstep4_t *ctx, uint8_t dir );

/**
 * @brief Silent Step 4 switch direction function.
 * @details This function switches the motor direction by toggling the DIR pin.
 * @param[in] ctx : Click context object.
 * See #silentstep4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void silentstep4_switch_direction ( silentstep4_t *ctx );

/**
 * @brief Silent Step 4 reset device function.
 * @details This function resets the PCA9538A device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #silentstep4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void silentstep4_reset_pca ( silentstep4_t *ctx );

/**
 * @brief Silent Step 4 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep4_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void silentstep4_set_rst_pin ( silentstep4_t *ctx, uint8_t state );

/**
 * @brief Silent Step 4 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep4_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t silentstep4_get_int_pin ( silentstep4_t *ctx );

/**
 * @brief Silent Step 4 set step pin function.
 * @details This function sets the STEP pin logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep4_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void silentstep4_set_step_pin ( silentstep4_t *ctx, uint8_t state );

/**
 * @brief Silent Step 4 set toff function.
 * @details This function sets the off time and driver enable bits in CHOPCONF register.
 * @param[in] ctx : Click context object.
 * See #silentstep4_t object definition for detailed explanation.
 * @param[in] toff : TOFF bits setting [0-15].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep4_set_toff ( silentstep4_t *ctx, uint8_t toff );

/**
 * @brief Silent Step 4 set step res function.
 * @details This function sets the microstep resolution bits in CHOPCONF register.
 * @param[in] ctx : Click context object.
 * See #silentstep4_t object definition for detailed explanation.
 * @param[in] mres : MRES bits setting:
 *                   @li @c 0 - 1/256 microsteps,
 *                   @li @c 1 - 1/128 microsteps,
 *                   @li @c 2 - 1/64 microsteps,
 *                   @li @c 3 - 1/32 microsteps,
 *                   @li @c 4 - 1/16 microsteps,
 *                   @li @c 5 - 1/8 microsteps,
 *                   @li @c 6 - quarter step,
 *                   @li @c 7 - half step,
 *                   @li @c 8 - full step.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep4_set_step_res ( silentstep4_t *ctx, uint8_t mres );

/**
 * @brief Silent Step 4 set run current function.
 * @details This function sets the motor run current bits in IHOLD_IRUN register.
 * @param[in] ctx : Click context object.
 * See #silentstep4_t object definition for detailed explanation.
 * @param[in] irun : IRUN bits setting [0-31].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep4_set_run_current ( silentstep4_t *ctx, uint8_t irun );

/**
 * @brief Silent Step 4 driver motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #silentstep4_t object definition for detailed explanation.
 * @param[in] steps : Number of steps to rotate motor.
 * @param[in] speed : Motor rotation speed:
 *                    @li @c 0 - Very slow,
 *                    @li @c 1 - Slow,
 *                    @li @c 2 - Medium,
 *                    @li @c 3 - Fast,
 *                    @li @c 4 - Very fast.
 * @return None.
 * @note None.
 */
void silentstep4_drive_motor ( silentstep4_t *ctx, uint32_t steps, uint8_t speed );

#ifdef __cplusplus
}
#endif
#endif // SILENTSTEP4_H

/*! @} */ // silentstep4

// ------------------------------------------------------------------------ END
