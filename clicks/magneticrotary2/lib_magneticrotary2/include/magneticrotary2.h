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
 * @file magneticrotary2.h
 * @brief This file contains API for Magnetic Rotary 2 Click Driver.
 */

#ifndef MAGNETICROTARY2_H
#define MAGNETICROTARY2_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup magneticrotary2 Magnetic Rotary 2 Click Driver
 * @brief API for configuring and manipulating Magnetic Rotary 2 Click driver.
 * @{
 */

/**
 * @defgroup magneticrotary2_reg Magnetic Rotary 2 Registers List
 * @brief List of registers of Magnetic Rotary 2 Click driver.
 */

/**
 * @addtogroup magneticrotary2_reg
 * @{
 */

/**
 * @brief Magnetic Rotary 2 registers list.
 * @details Specified registers list of Magnetic Rotary 2 Click driver.
 */
#define MAGNETICROTARY2_REG_CUST_RES_0              0x00
#define MAGNETICROTARY2_REG_CUST_RES_1              0x01
#define MAGNETICROTARY2_REG_CUST_RES_2              0x02
#define MAGNETICROTARY2_REG_CUST_RES_3              0x03
#define MAGNETICROTARY2_REG_CUST_RES_4              0x04
#define MAGNETICROTARY2_REG_CUST_RES_5              0x05
#define MAGNETICROTARY2_REG_CUST_RES_6              0x06
#define MAGNETICROTARY2_REG_CUST_CONFIG_0_MSB       0x07
#define MAGNETICROTARY2_REG_CUST_CONFIG_0_LSB       0x08
#define MAGNETICROTARY2_REG_CUST_CONFIG_1_MSB       0x09
#define MAGNETICROTARY2_REG_CUST_CONFIG_1_LSB       0x0A
#define MAGNETICROTARY2_REG_CUST_CONFIG_2           0x0B
#define MAGNETICROTARY2_REG_ZERO_RESET_2            0x0C
#define MAGNETICROTARY2_REG_ZERO_RESET_1            0x0D
#define MAGNETICROTARY2_REG_ZERO_RESET_0            0x0E
#define MAGNETICROTARY2_REG_UNLOCK                  0x10
#define MAGNETICROTARY2_REG_PROGRAM                 0x11
#define MAGNETICROTARY2_REG_CALIBRATION             0x12
#define MAGNETICROTARY2_REG_ERROR_BITS              0x21
#define MAGNETICROTARY2_REG_CALIBRATION_STAT        0x22
#define MAGNETICROTARY2_REG_POSITION                0x3F

/*! @} */ // magneticrotary2_reg

/**
 * @defgroup magneticrotary2_set Magnetic Rotary 2 Registers Settings
 * @brief Settings for registers of Magnetic Rotary 2 Click driver.
 */

/**
 * @addtogroup magneticrotary2_set
 * @{
 */

/**
 * @brief Magnetic Rotary 2 register settings.
 * @details Specified setting for registers of Magnetic Rotary 2 Click driver.
 */
#define MAGNETICROTARY2_UNLOCK_VALUE                0xAB
#define MAGNETICROTARY2_LOCK_VALUE                  0xFF
#define MAGNETICROTARY2_PROGRAM_VALUE               0xA1

/**
 * @brief Magnetic Rotary 2 ODD parity flag.
 * @details Specified flag for ODD parity of Magnetic Rotary 2 Click driver.
 */
#define MAGNETICROTARY2_ODD_PARITY                  0x01

/**
 * @brief Magnetic Rotary 2 read write bits.
 * @details Specified bits for read/write operation of Magnetic Rotary 2 Click driver.
 */
#define MAGNETICROTARY2_MSEL1_READ_BIT              0x40
#define MAGNETICROTARY2_MSEL0_WRITE_BIT             0x80

/**
 * @brief Magnetic Rotary 2 custom config 0 registers settings.
 * @details Specified settings for custom config 0 registers of Magnetic Rotary 2 Click driver.
 */
#define MAGNETICROTARY2_CC0_MSB_HW_ST_ZERO_EN       0x80
#define MAGNETICROTARY2_CC0_MSB_HW_ACC_CALIB_EN     0x40
#define MAGNETICROTARY2_CC0_MSB_AXIS_MODE_OFF       0x20
#define MAGNETICROTARY2_CC0_MSB_IWIDTH_90           0x00
#define MAGNETICROTARY2_CC0_MSB_IWIDTH_180          0x04
#define MAGNETICROTARY2_CC0_MSB_IWIDTH_270          0x08
#define MAGNETICROTARY2_CC0_MSB_IWIDTH_360          0x0C
#define MAGNETICROTARY2_CC0_MSB_IPHASE_90           0x00
#define MAGNETICROTARY2_CC0_MSB_IPHASE_180          0x01
#define MAGNETICROTARY2_CC0_MSB_IPHASE_270          0x02
#define MAGNETICROTARY2_CC0_MSB_IPHASE_360          0x03
#define MAGNETICROTARY2_CC0_LSB_HYST_0_00           0x00
#define MAGNETICROTARY2_CC0_LSB_HYST_0_01           0x20
#define MAGNETICROTARY2_CC0_LSB_HYST_0_02           0x40
#define MAGNETICROTARY2_CC0_LSB_HYST_0_04           0x60
#define MAGNETICROTARY2_CC0_LSB_HYST_0_08           0x80
#define MAGNETICROTARY2_CC0_LSB_HYST_0_17           0xA0
#define MAGNETICROTARY2_CC0_LSB_HYST_0_35           0xC0
#define MAGNETICROTARY2_CC0_LSB_HYST_0_70           0xE0
#define MAGNETICROTARY2_CC0_LSB_DIR_CCW             0x10
#define MAGNETICROTARY2_CC0_LSB_ABS_RES_18BIT       0x00
#define MAGNETICROTARY2_CC0_LSB_ABS_RES_17BIT       0x01
#define MAGNETICROTARY2_CC0_LSB_ABS_RES_16BIT       0x02
#define MAGNETICROTARY2_CC0_LSB_ABS_RES_15BIT       0x03
#define MAGNETICROTARY2_CC0_LSB_ABS_RES_14BIT       0x04
#define MAGNETICROTARY2_CC0_LSB_ABS_RES_13BIT       0x05
#define MAGNETICROTARY2_CC0_LSB_ABS_RES_12BIT       0x06
#define MAGNETICROTARY2_CC0_LSB_ABS_RES_11BIT       0x07
#define MAGNETICROTARY2_CC0_LSB_ABS_RES_10BIT       0x08
#define MAGNETICROTARY2_CC0_LSB_ABS_RES_MASK        0x0F

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b magneticrotary2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define MAGNETICROTARY2_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define MAGNETICROTARY2_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // magneticrotary2_set

/**
 * @defgroup magneticrotary2_map Magnetic Rotary 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Magnetic Rotary 2 Click driver.
 */

/**
 * @addtogroup magneticrotary2_map
 * @{
 */

/**
 * @brief Magnetic Rotary 2 Click driver selector.
 * @details Selects target driver interface of Magnetic Rotary 2 Click driver.
 */
typedef enum
{
    MAGNETICROTARY2_MSEL_0,      /**< MSEL 0 selector. */
    MAGNETICROTARY2_MSEL_1       /**< MSEL 1 selector. */

} magneticrotary2_msel_t;

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Magnetic Rotary 2 Click to the selected MikroBUS.
 */
#define MAGNETICROTARY2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS )

/*! @} */ // magneticrotary2_map
/*! @} */ // magneticrotary2

/**
 * @brief Magnetic Rotary 2 Click context object.
 * @details Context object definition of Magnetic Rotary 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t ssi_sel;          /**< MOSI as SSI sel pin. */
    // Modules
    spi_master_t  spi;              /**< SPI driver object. */

    pin_name_t  chip_select;        /**< Chip select pin descriptor (used for SPI driver). */
    magneticrotary2_msel_t msel;    /**< MSEL selector. */
    uint8_t abs_res;                /**< Absolute position resolution. */

} magneticrotary2_t;

/**
 * @brief Magnetic Rotary 2 Click configuration object.
 * @details Configuration object definition of Magnetic Rotary 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                   /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                   /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                    /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                     /**< Chip select pin descriptor for SPI driver. */

    // static variable
    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */
    magneticrotary2_msel_t             msel;            /**< MSEL selector. */

} magneticrotary2_cfg_t;

/**
 * @brief Magnetic Rotary 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MAGNETICROTARY2_OK = 0,
    MAGNETICROTARY2_ERROR = -1

} magneticrotary2_return_value_t;

/*!
 * @addtogroup magneticrotary2 Magnetic Rotary 2 Click Driver
 * @brief API for configuring and manipulating Magnetic Rotary 2 Click driver.
 * @{
 */

/**
 * @brief Magnetic Rotary 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #magneticrotary2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void magneticrotary2_cfg_setup ( magneticrotary2_cfg_t *cfg );

/**
 * @brief Magnetic Rotary 2 MSEL pin selection function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #magneticrotary2_cfg_t object definition for detailed explanation.
 * @param[in] msel : MSEL selection.
 * See #magneticrotary2_msel_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void magneticrotary2_msel_pin_selection ( magneticrotary2_cfg_t *cfg, magneticrotary2_msel_t msel );

/**
 * @brief Magnetic Rotary 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #magneticrotary2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #magneticrotary2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneticrotary2_init ( magneticrotary2_t *ctx, magneticrotary2_cfg_t *cfg );

/**
 * @brief Magnetic Rotary 2 default configuration function.
 * @details This function executes a default configuration of Magnetic Rotary 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #magneticrotary2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t magneticrotary2_default_cfg ( magneticrotary2_t *ctx );

/**
 * @brief Magnetic Rotary 2 write register function.
 * @details This function writes a data byte to the selected register by using SPI serial interface. 
 * It will also verify if the data is written correctly by reading back the same register.
 * @param[in] ctx : Click context object.
 * See #magneticrotary2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneticrotary2_write_register ( magneticrotary2_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Magnetic Rotary 2 read register function.
 * @details This function reads a data byte from the selected register by using SPI serial interface.
 * In the case of SPI4 and absolute position register, it will read 3 bytes of data without parity and error flag bits.
 * @param[in] ctx : Click context object.
 * See #magneticrotary2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneticrotary2_read_register ( magneticrotary2_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Magnetic Rotary 2 unlock eeprom function.
 * @details This function unlocks eeprom by sending the unlock eeprom command.
 * @param[in] ctx : Click context object.
 * See #magneticrotary2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneticrotary2_unlock_eeprom ( magneticrotary2_t *ctx );

/**
 * @brief Magnetic Rotary 2 lock eeprom function.
 * @details This function locks eeprom by writing 0xFF to the unlock eeprom address.
 * @param[in] ctx : Click context object.
 * See #magneticrotary2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneticrotary2_lock_eeprom ( magneticrotary2_t *ctx );

/**
 * @brief Magnetic Rotary 2 program eeprom function.
 * @details This function programs eeprom by sending the program eeprom command.
 * @param[in] ctx : Click context object.
 * See #magneticrotary2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneticrotary2_program_eeprom ( magneticrotary2_t *ctx );

/**
 * @brief Magnetic Rotary 2 get raw data function.
 * @details This function reads the absolute position raw data.
 * @param[in] ctx : Click context object.
 * See #magneticrotary2_t object definition for detailed explanation.
 * @param[out] data_out : Absolute position raw data [18 bits by default].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneticrotary2_get_raw_data ( magneticrotary2_t *ctx, uint32_t *data_out );

/**
 * @brief Magnetic Rotary 2 get angle function.
 * @details This function reads the absolute position raw data and converts it to degrees (Angle).
 * @param[in] ctx : Click context object.
 * See #magneticrotary2_t object definition for detailed explanation.
 * @param[out] angle : Angle in degrees [0-360].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneticrotary2_get_angle ( magneticrotary2_t *ctx, float *angle );

#ifdef __cplusplus
}
#endif
#endif // MAGNETICROTARY2_H

/*! @} */ // magneticrotary2

// ------------------------------------------------------------------------ END
