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
 * @file stepper22.h
 * @brief This file contains API for Stepper 22 Click Driver.
 */

#ifndef STEPPER22_H
#define STEPPER22_H

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
#include "drv_analog_in.h"

/*!
 * @addtogroup stepper22 Stepper 22 Click Driver
 * @brief API for configuring and manipulating Stepper 22 Click driver.
 * @{
 */

/**
 * @defgroup stepper22_reg Stepper 22 Registers List
 * @brief List of registers of Stepper 22 Click driver.
 */

/**
 * @addtogroup stepper22_reg
 * @{
 */

/**
 * @brief Stepper 22 registers list.
 * @details Specified registers list of Stepper 22 Click driver.
 */
#define STEPPER22_REG_CTRL                      0x00
#define STEPPER22_REG_TORQUE                    0x01
#define STEPPER22_REG_OFF                       0x02
#define STEPPER22_REG_BLANK                     0x03
#define STEPPER22_REG_DECAY                     0x04
#define STEPPER22_REG_STALL                     0x05
#define STEPPER22_REG_DRIVE                     0x06
#define STEPPER22_REG_STATUS                    0x07

/**
 * @brief Stepper 22 PCA9538A registers.
 * @details Specified PCA9538A registers of Stepper 22 Click driver.
 */
#define STEPPER22_PCA9538A_REG_INPUT            0x00
#define STEPPER22_PCA9538A_REG_OUTPUT           0x01
#define STEPPER22_PCA9538A_REG_POLARITY         0x02
#define STEPPER22_PCA9538A_REG_CONFIG           0x03

/*! @} */ // stepper22_reg

/**
 * @defgroup stepper22_set Stepper 22 Registers Settings
 * @brief Settings for registers of Stepper 22 Click driver.
 */

/**
 * @addtogroup stepper22_set
 * @{
 */

/**
 * @brief Stepper 22 CTRL register settings.
 * @details Specified settings of CTRL register of Stepper 22 Click driver.
 */
#define STEPPER22_CTRL_DTIME_400_NS             0x0000
#define STEPPER22_CTRL_DTIME_450_NS             0x0400
#define STEPPER22_CTRL_DTIME_650_NS             0x0800
#define STEPPER22_CTRL_DTIME_850_NS             0x0C00
#define STEPPER22_CTRL_DTIME_MASK               0x0C00
#define STEPPER22_CTRL_ISGAIN_5                 0x0000
#define STEPPER22_CTRL_ISGAIN_10                0x0100
#define STEPPER22_CTRL_ISGAIN_20                0x0200
#define STEPPER22_CTRL_ISGAIN_40                0x0300
#define STEPPER22_CTRL_ISGAIN_MASK              0x0300
#define STEPPER22_CTRL_EXSTALL_INT_STALL        0x0000
#define STEPPER22_CTRL_EXSTALL_EXT_STALL        0x0080
#define STEPPER22_CTRL_EXSTALL_MASK             0x0080
#define STEPPER22_CTRL_MODE_FULL_STEP           0x0000
#define STEPPER22_CTRL_MODE_HALF_STEP           0x0008
#define STEPPER22_CTRL_MODE_QUARTER_STEP        0x0010
#define STEPPER22_CTRL_MODE_1_OVER_8            0x0018
#define STEPPER22_CTRL_MODE_1_OVER_16           0x0020
#define STEPPER22_CTRL_MODE_1_OVER_32           0x0028
#define STEPPER22_CTRL_MODE_1_OVER_64           0x0030
#define STEPPER22_CTRL_MODE_1_OVER_128          0x0038
#define STEPPER22_CTRL_MODE_1_OVER_256          0x0040
#define STEPPER22_CTRL_MODE_MASK                0x0078
#define STEPPER22_CTRL_RSTEP_NO_ACTION          0x0000
#define STEPPER22_CTRL_RSTEP_ADV_1_STEP         0x0004
#define STEPPER22_CTRL_RSTEP_MASK               0x0004
#define STEPPER22_CTRL_RDIR_DIR_PIN             0x0000
#define STEPPER22_CTRL_RDIR_INV_DIR_PIN         0x0002
#define STEPPER22_CTRL_RDIR_MASK                0x0002
#define STEPPER22_CTRL_ENBL_MOTOR_DISABLE       0x0000
#define STEPPER22_CTRL_ENBL_MOTOR_ENABLE        0x0001
#define STEPPER22_CTRL_ENBL_MASK                0x0001

/**
 * @brief Stepper 22 TORQUE register settings.
 * @details Specified settings of TORQUE register of Stepper 22 Click driver.
 */
#define STEPPER22_TORQUE_SMPLTH_50_US           0x0000
#define STEPPER22_TORQUE_SMPLTH_100_US          0x0100
#define STEPPER22_TORQUE_SMPLTH_200_US          0x0200
#define STEPPER22_TORQUE_SMPLTH_300_US          0x0300
#define STEPPER22_TORQUE_SMPLTH_400_US          0x0400
#define STEPPER22_TORQUE_SMPLTH_600_US          0x0500
#define STEPPER22_TORQUE_SMPLTH_800_US          0x0600
#define STEPPER22_TORQUE_SMPLTH_1000_US         0x0700
#define STEPPER22_TORQUE_SMPLTH_MASK            0x0700
#define STEPPER22_TORQUE_TORQUE_DEFAULT         0x0000
#define STEPPER22_TORQUE_TORQUE_MASK            0x00FF

/**
 * @brief Stepper 22 OFF register settings.
 * @details Specified settings of OFF register of Stepper 22 Click driver.
 */
#define STEPPER22_OFF_PWMMODE_USE_INDEXER       0x0000
#define STEPPER22_OFF_PWMMODE_BYPASS_INDEXER    0x0100
#define STEPPER22_OFF_PWMMODE_MASK              0x0100
#define STEPPER22_OFF_TOFF_24_5_US              0x0030
#define STEPPER22_OFF_TOFF_MASK                 0x00FF

/**
 * @brief Stepper 22 BLANK register settings.
 * @details Specified settings of BLANK register of Stepper 22 Click driver.
 */
#define STEPPER22_BLANK_ABT_DISABLE             0x0000
#define STEPPER22_BLANK_ABT_ENABLE              0x0100
#define STEPPER22_BLANK_ABT_MASK                0x0100
#define STEPPER22_BLANK_TBLANK_2_58_US          0x0080
#define STEPPER22_BLANK_TBLANK_MASK             0x00FF

/**
 * @brief Stepper 22 DECAY register settings.
 * @details Specified settings of DECAY register of Stepper 22 Click driver.
 */
#define STEPPER22_DECAY_DECMOD_FORCE_SLOW       0x0000
#define STEPPER22_DECAY_DECMOD_SLOW_MIXED       0x0100
#define STEPPER22_DECAY_DECMOD_FORCE_FAST       0x0200
#define STEPPER22_DECAY_DECMOD_MIXED            0x0300
#define STEPPER22_DECAY_DECMOD_SLOW_AUTO_MIXED  0x0400
#define STEPPER22_DECAY_DECMOD_AUTO_MIXED       0x0500
#define STEPPER22_DECAY_DECMOD_MASK             0x0700
#define STEPPER22_DECAY_TDECAY_8_5_US           0x0010
#define STEPPER22_DECAY_TDECAY_MASK             0x00FF

/**
 * @brief Stepper 22 STALL register settings.
 * @details Specified settings of STALL register of Stepper 22 Click driver.
 */
#define STEPPER22_STALL_VDIV_DIV_32             0x0000
#define STEPPER22_STALL_VDIV_DIV_16             0x0400
#define STEPPER22_STALL_VDIV_DIV_8              0x0800
#define STEPPER22_STALL_VDIV_DIV_4              0x0C00
#define STEPPER22_STALL_VDIV_MASK               0x0C00
#define STEPPER22_STALL_SDCNT_1_STEP            0x0000
#define STEPPER22_STALL_SDCNT_2_STEPS           0x0100
#define STEPPER22_STALL_SDCNT_4_STEPS           0x0200
#define STEPPER22_STALL_SDCNT_8_STEPS           0x0300
#define STEPPER22_STALL_SDCNT_MASK              0x0300
#define STEPPER22_STALL_SDTHR_DEFAULT           0x0040
#define STEPPER22_STALL_SDTHR_MASK              0x00FF

/**
 * @brief Stepper 22 DRIVE register settings.
 * @details Specified settings of DRIVE register of Stepper 22 Click driver.
 */
#define STEPPER22_DRIVE_IDRIVEP_50_MA           0x0000
#define STEPPER22_DRIVE_IDRIVEP_100_MA          0x0400
#define STEPPER22_DRIVE_IDRIVEP_150_MA          0x0800
#define STEPPER22_DRIVE_IDRIVEP_200_MA          0x0C00
#define STEPPER22_DRIVE_IDRIVEP_MASK            0x0C00
#define STEPPER22_DRIVE_IDRIVEN_100_MA          0x0000
#define STEPPER22_DRIVE_IDRIVEN_200_MA          0x0100
#define STEPPER22_DRIVE_IDRIVEN_300_MA          0x0200
#define STEPPER22_DRIVE_IDRIVEN_400_MA          0x0300
#define STEPPER22_DRIVE_IDRIVEN_MASK            0x0300
#define STEPPER22_DRIVE_TDRIVEP_250_NS          0x0000
#define STEPPER22_DRIVE_TDRIVEP_500_NS          0x0040
#define STEPPER22_DRIVE_TDRIVEP_1_US            0x0080
#define STEPPER22_DRIVE_TDRIVEP_2_US            0x00C0
#define STEPPER22_DRIVE_TDRIVEP_MASK            0x00C0
#define STEPPER22_DRIVE_TDRIVEN_250_NS          0x0000
#define STEPPER22_DRIVE_TDRIVEN_500_NS          0x0010
#define STEPPER22_DRIVE_TDRIVEN_1_US            0x0020
#define STEPPER22_DRIVE_TDRIVEN_2_US            0x0030
#define STEPPER22_DRIVE_TDRIVEN_MASK            0x0030
#define STEPPER22_DRIVE_OCPDEG_1_US             0x0000
#define STEPPER22_DRIVE_OCPDEG_2_US             0x0004
#define STEPPER22_DRIVE_OCPDEG_4_US             0x0008
#define STEPPER22_DRIVE_OCPDEG_8_US             0x000C
#define STEPPER22_DRIVE_OCPDEG_MASK             0x000C
#define STEPPER22_DRIVE_OCPTH_250_MV            0x0000
#define STEPPER22_DRIVE_OCPTH_500_MV            0x0001
#define STEPPER22_DRIVE_OCPTH_750_MV            0x0002
#define STEPPER22_DRIVE_OCPTH_1000_MV           0x0003
#define STEPPER22_DRIVE_OCPTH_MASK              0x0003

/**
 * @brief Stepper 22 STATUS register settings.
 * @details Specified settings of STATUS register of Stepper 22 Click driver.
 */
#define STEPPER22_STATUS_STDLAT                 0x0080
#define STEPPER22_STATUS_STD                    0x0040
#define STEPPER22_STATUS_UVLO                   0x0020
#define STEPPER22_STATUS_BPDF                   0x0010
#define STEPPER22_STATUS_APDF                   0x0008
#define STEPPER22_STATUS_BOCP                   0x0004
#define STEPPER22_STATUS_AOCP                   0x0002
#define STEPPER22_STATUS_OTS                    0x0001
#define STEPPER22_STATUS_CLEAR_ALL              0x0000

/**
 * @brief Stepper 22 PCA9538A pin mask.
 * @details Specified PCA9538A pin mask of Stepper 22 Click driver.
 */
#define STEPPER22_PIN_STALL                     0x02
#define STEPPER22_PIN_FAULT                     0x04
#define STEPPER22_PIN_BIN2                      0x08
#define STEPPER22_PIN_BIN1                      0x10
#define STEPPER22_PIN_DIR                       0x20
#define STEPPER22_PIN_RESET                     0x40
#define STEPPER22_PIN_SLEEP                     0x80

/**
 * @brief Stepper 22 PCA9538A pin direction config.
 * @details Specified PCA9538A pin direction config of Stepper 22 Click driver.
 */
#define STEPPER22_PCA9538A_DEFAULT_CONFIG       0x07

/**
 * @brief Stepper 22 direction setting.
 * @details Specified setting for direction of Stepper 22 Click driver.
 */
#define STEPPER22_DIR_CW                        0
#define STEPPER22_DIR_CCW                       1

/**
 * @brief Stepper 22 pin logic state setting.
 * @details Specified setting for pin logic state of Stepper 22 Click driver.
 */
#define STEPPER22_PIN_STATE_LOW                 0
#define STEPPER22_PIN_STATE_HIGH                1

/**
 * @brief Stepper 22 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define STEPPER22_SPEED_VERY_SLOW               0
#define STEPPER22_SPEED_SLOW                    1
#define STEPPER22_SPEED_MEDIUM                  2
#define STEPPER22_SPEED_FAST                    3
#define STEPPER22_SPEED_VERY_FAST               4

/**
 * @brief Stepper 22 step resolution setting.
 * @details Specified setting for step resolution of Stepper 22 Click driver.
 */
#define STEPPER22_MODE_FULL_STEP                0
#define STEPPER22_MODE_HALF_STEP                1
#define STEPPER22_MODE_QUARTER_STEP             2
#define STEPPER22_MODE_1_OVER_8                 3
#define STEPPER22_MODE_1_OVER_16                4
#define STEPPER22_MODE_1_OVER_32                5
#define STEPPER22_MODE_1_OVER_64                6
#define STEPPER22_MODE_1_OVER_128               7
#define STEPPER22_MODE_1_OVER_256               8

/**
 * @brief Stepper 22 device address setting.
 * @details Specified setting for device slave address selection of
 * Stepper 22 Click driver.
 */
#define STEPPER22_DEVICE_ADDRESS_A1A0_00        0x70
#define STEPPER22_DEVICE_ADDRESS_A1A0_01        0x71
#define STEPPER22_DEVICE_ADDRESS_A1A0_10        0x72
#define STEPPER22_DEVICE_ADDRESS_A1A0_11        0x73

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b stepper22_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define STEPPER22_SET_DATA_SAMPLE_EDGE          SET_SPI_DATA_SAMPLE_EDGE
#define STEPPER22_SET_DATA_SAMPLE_MIDDLE        SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // stepper22_set

/**
 * @defgroup stepper22_map Stepper 22 MikroBUS Map
 * @brief MikroBUS pin mapping of Stepper 22 Click driver.
 */

/**
 * @addtogroup stepper22_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stepper 22 Click to the selected MikroBUS.
 */
#define STEPPER22_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.bemf = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.step = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepper22_map
/*! @} */ // stepper22

/**
 * @brief Stepper 22 Click context object.
 * @details Context object definition of Stepper 22 Click driver.
 */
typedef struct stepper22_s
{
    digital_out_t rst;                  /**< PCA9538A reset pin. */
    digital_out_t step;                 /**< Step signal pin. */

    digital_in_t int_pin;               /**< PCA9538A interrupt pin. */

    i2c_master_t i2c;                   /**< I2C driver object. */
    spi_master_t spi;                   /**< SPI driver object. */

    uint8_t      slave_address;         /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;           /**< Chip select pin descriptor (used for SPI driver). */

    analog_in_t adc;                    /**< ADC module object. */

} stepper22_t;

/**
 * @brief Stepper 22 Click configuration object.
 * @details Configuration object definition of Stepper 22 Click driver.
 */
typedef struct
{
    pin_name_t scl;                     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                     /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                      /**< Chip select pin descriptor for SPI driver. */
    pin_name_t bemf;                    /**< Motor back EMF analog pin. */
    pin_name_t rst;                     /**< PCA9538A reset pin. */
    pin_name_t step;                    /**< Step signal pin. */
    pin_name_t int_pin;                 /**< PCA9538A interrupt pin. */

    uint32_t   i2c_speed;               /**< I2C serial speed. */
    uint8_t    i2c_address;             /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */

} stepper22_cfg_t;

/**
 * @brief Stepper 22 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPPER22_OK = 0,
    STEPPER22_ERROR = -1

} stepper22_return_value_t;

/*!
 * @addtogroup stepper22 Stepper 22 Click Driver
 * @brief API for configuring and manipulating Stepper 22 Click driver.
 * @{
 */

/**
 * @brief Stepper 22 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepper22_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepper22_cfg_setup ( stepper22_cfg_t *cfg );

/**
 * @brief Stepper 22 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepper22_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper22_init ( stepper22_t *ctx, stepper22_cfg_t *cfg );

/**
 * @brief Stepper 22 default configuration function.
 * @details This function executes a default configuration of Stepper 22
 * click board.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t stepper22_default_cfg ( stepper22_t *ctx );

/**
 * @brief Stepper 22 write reg function.
 * @details This function writes a desired data word to the selected register 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper22_write_reg ( stepper22_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Stepper 22 read reg function.
 * @details This function reads data word from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper22_read_reg ( stepper22_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Stepper 22 pca write reg function.
 * @details This function writes a desired data byte to the selected PCA9538A register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper22_pca_write_reg ( stepper22_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Stepper 22 pca read reg function.
 * @details This function reads data from the selected PCA9538A register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper22_pca_read_reg ( stepper22_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Stepper 22 read BEMF pin voltage level function.
 * @details This function reads results of AD conversion of the BEMF pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t stepper22_read_bemf_voltage ( stepper22_t *ctx, float *data_out );

/**
 * @brief Stepper 22 get STALL pin function.
 * @details This function reads the STALL pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper22_get_stall_pin ( stepper22_t *ctx, uint8_t *state );

/**
 * @brief Stepper 22 get FAULT pin function.
 * @details This function reads the FAULT pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper22_get_fault_pin ( stepper22_t *ctx, uint8_t *state );

/**
 * @brief Stepper 22 get BIN2 pin function.
 * @details This function reads the BIN2 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper22_get_bin2_pin ( stepper22_t *ctx, uint8_t *state );

/**
 * @brief Stepper 22 set BIN2 pin function.
 * @details This function sets the BIN2 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper22_set_bin2_pin ( stepper22_t *ctx, uint8_t state );

/**
 * @brief Stepper 22 get BIN1 pin function.
 * @details This function reads the BIN1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper22_get_bin1_pin ( stepper22_t *ctx, uint8_t *state );

/**
 * @brief Stepper 22 set BIN1 pin function.
 * @details This function sets the BIN1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper22_set_bin1_pin ( stepper22_t *ctx, uint8_t state );

/**
 * @brief Stepper 22 get DIR pin function.
 * @details This function reads the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper22_get_dir_pin ( stepper22_t *ctx, uint8_t *state );

/**
 * @brief Stepper 22 set DIR pin function.
 * @details This function sets the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper22_set_dir_pin ( stepper22_t *ctx, uint8_t state );

/**
 * @brief Stepper 22 get RESET pin function.
 * @details This function reads the RESET pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper22_get_reset_pin ( stepper22_t *ctx, uint8_t *state );

/**
 * @brief Stepper 22 set RESET pin function.
 * @details This function sets the RESET pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper22_set_reset_pin ( stepper22_t *ctx, uint8_t state );

/**
 * @brief Stepper 22 get SLEEP pin function.
 * @details This function reads the SLEEP pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper22_get_sleep_pin ( stepper22_t *ctx, uint8_t *state );

/**
 * @brief Stepper 22 set SLEEP pin function.
 * @details This function sets the SLEEP pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper22_set_sleep_pin ( stepper22_t *ctx, uint8_t state );

/**
 * @brief Stepper 22 enable device function.
 * @details This function enables the device by setting the SLEEP pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper22_enable_device ( stepper22_t *ctx );

/**
 * @brief Stepper 22 disable device function.
 * @details This function disables the device by setting the SLEEP pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper22_disable_device ( stepper22_t *ctx );

/**
 * @brief Stepper 22 set direction function.
 * @details This function sets the motor direction by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Clockwise,
 *                  @li @c 1 - Counter-Clockwise.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper22_set_direction ( stepper22_t *ctx, uint8_t dir );

/**
 * @brief Stepper 22 switch direction function.
 * @details This function switches the motor direction by toggling the DIR pin.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper22_switch_direction ( stepper22_t *ctx );

/**
 * @brief Stepper 22 reset device function.
 * @details This function resets the PCA9538A device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper22_reset_pca ( stepper22_t *ctx );

/**
 * @brief Stepper 22 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper22_set_rst_pin ( stepper22_t *ctx, uint8_t state );

/**
 * @brief Stepper 22 set STEP pin function.
 * @details This function sets the STEP pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper22_set_step_pin ( stepper22_t *ctx, uint8_t state );

/**
 * @brief Stepper 22 get INT pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t stepper22_get_int_pin ( stepper22_t *ctx );

/**
 * @brief Stepper 22 get step mode function.
 * @details This function reads the step mode resolution settings.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @param[out] mode : Step mode resolution:
 *                    @li @c 0 - Full step (2-phase excitation) with 71% current,
 *                    @li @c 1 - 1/2 step,
 *                    @li @c 2 - 1/4 step,
 *                    @li @c 3 - 1/8 step,
 *                    @li @c 4 - 1/16 step,
 *                    @li @c 5 - 1/32 step,
 *                    @li @c 6 - 1/64 step,
 *                    @li @c 7 - 1/128 step,
 *                    @li @c 8 - 1/256 step.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper22_get_step_mode ( stepper22_t *ctx, uint8_t *mode );

/**
 * @brief Stepper 22 set step mode function.
 * @details This function sets the step mode resolution settings.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @param[in] mode : Step mode resolution:
 *                   @li @c 0 - Full step (2-phase excitation) with 71% current,
 *                   @li @c 1 - 1/2 step,
 *                   @li @c 2 - 1/4 step,
 *                   @li @c 3 - 1/8 step,
 *                   @li @c 4 - 1/16 step,
 *                   @li @c 5 - 1/32 step,
 *                   @li @c 6 - 1/64 step,
 *                   @li @c 7 - 1/128 step,
 *                   @li @c 8 - 1/256 step.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper22_set_step_mode ( stepper22_t *ctx, uint8_t mode );

/**
 * @brief Stepper 22 driver motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #stepper22_t object definition for detailed explanation.
 * @param[in] steps : Number of steps to rotate motor.
 * @param[in] speed : Motor rotation speed:
 *                    @li @c 0 - Very slow,
 *                    @li @c 1 - Slow,
 *                    @li @c 2 - Medium,
 *                    @li @c 3 - Fast,
 *                    @li @c 4 - Very fast.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper22_drive_motor ( stepper22_t *ctx, uint32_t steps, uint8_t speed );

#ifdef __cplusplus
}
#endif
#endif // STEPPER22_H

/*! @} */ // stepper22

// ------------------------------------------------------------------------ END
