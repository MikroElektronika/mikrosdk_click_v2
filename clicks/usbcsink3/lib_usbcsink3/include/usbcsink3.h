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
 * @file usbcsink3.h
 * @brief This file contains API for USB-C Sink 3 Click Driver.
 */

#ifndef USBCSINK3_H
#define USBCSINK3_H

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
#include "drv_i2c_master.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"
#include "drv_analog_in.h"

/*!
 * @addtogroup usbcsink3 USB-C Sink 3 Click Driver
 * @brief API for configuring and manipulating USB-C Sink 3 Click driver.
 * @{
 */

/**
 * @defgroup usbcsink3_reg USB-C Sink 3 Registers List
 * @brief List of registers of USB-C Sink 3 Click driver.
 */

/**
 * @addtogroup usbcsink3_reg
 * @{
 */

/**
 * @brief USB-C Sink 3 description expander register.
 * @details Specified register for description of USB-C Sink 3 Click driver.
 */
#define USBCSINK3_REG_INPUT_PORT             0x00
#define USBCSINK3_REG_OUTPUT_PORT            0x01
#define USBCSINK3_REG_POLARITY_INV           0x02
#define USBCSINK3_REG_CONFIG                 0x03
#define USBCSINK3_REG_SPECIAL_FUNC           0x50

/*! @} */ // usbcsink3_reg

/**
 * @addtogroup usbcsink3_cmd
 * @{
 */

/**
 * @brief USB-C Sink 3 description digital POT command.
 * @details Specified digital POT command of USB-C Sink 3 Click driver.
 */
#define USBCSINK3_CMD_SEL_NONE               0x00
#define USBCSINK3_CMD_SEL_DATA_WRITE         0x10
#define USBCSINK3_CMD_SEL_SHUTDOWN           0x20

/**
 * @brief USB-C Sink 3 description digital POT selection.
 * @details Specified digital POT selection of USB-C Sink 3 Click driver.
 */
#define USBCSINK3_POT_SEL_DUMMY_CODE         0x00
#define USBCSINK3_POT_SEL_DIGI_POT_1         0x01
#define USBCSINK3_POT_SEL_DIGI_POT_2         0x02
#define USBCSINK3_POT_SEL_DIGI_POT_BOTH      0x03

/*! @} */ // usbcsink3_cmd

/**
 * @defgroup usbcsink3_set USB-C Sink 3 Registers Settings
 * @brief Settings for registers of USB-C Sink 3 Click driver.
 */

/**
 * @addtogroup usbcsink3_set
 * @{
 */

/**
 * @brief USB-C Sink 3 expander pin bit mask values.
 * @details Specified expander pin bit mask values of USB-C Sink 3 Click driver.
 */
#define USBCSINK3_NO_PIN_BIT_MASK            0x00
#define USBCSINK3_PIN_0_BIT_MASK             0x01
#define USBCSINK3_PIN_1_BIT_MASK             0x02
#define USBCSINK3_PIN_2_BIT_MASK             0x04
#define USBCSINK3_PIN_3_BIT_MASK             0x08
#define USBCSINK3_ALL_PINS_BIT_MASK          0xF0

/**
 * @brief USB-C Sink 3 expander I/O pin direction values.
 * @details Specified I/O pin direction values of USB-C Sink 3 Click driver.
 */
#define USBCSINK3_DIRECTION_OUTPUT           0x00
#define USBCSINK3_DIRECTION_INPUT            0x01

/**
 * @brief RS Transceiver expander VSEL pin direction values.
 * @details Specified VSEL pin direction values of RS Transceiver Click driver.
 */
#define USBCSINK3_VSEL0_DISABLE              0x00
#define USBCSINK3_VSEL0_ENABLE               0x01
#define USBCSINK3_VSEL0_PIN_BIT_MASK         0x0E
#define USBCSINK3_VSEL1_DISABLE              0x00
#define USBCSINK3_VSEL1_ENABLE               0x02
#define USBCSINK3_VSEL1_PIN_BIT_MASK         0x0D
#define USBCSINK3_VSEL2_DISABLE              0x00
#define USBCSINK3_VSEL2_ENABLE               0x04
#define USBCSINK3_VSEL2_PIN_BIT_MASK         0x0B

/**
 * @brief USB-C Sink 3 expander special function values.
 * @details Specified special function values of USB-C Sink 3 Click driver.
 */
#define USBCSINK3_SPEC_FUNC_P3_AS_INT        0x80
#define USBCSINK3_SPEC_FUNC_PU_DISABLED      0x40

/**
 * @brief USB-C Sink 3 VBUS voltage values.
 * @details Specified VBUS voltage of USB-C Sink 3 Click driver.
 */
#define USBCSINK3_VBUS_VTG_0V                0.0f
#define USBCSINK3_VBUS_VTG_5V                5.0f
#define USBCSINK3_VBUS_VTG_9V                9.0f
#define USBCSINK3_VBUS_VTG_15V               15.0f
#define USBCSINK3_VBUS_VTG_20V               20.3f
#define USBCSINK3_VBUS_VTG_4_3V              4.3f
#define USBCSINK3_VBUS_VTG_8_6V              8.6f
#define USBCSINK3_VBUS_VTG_12_9V             12.9f
#define USBCSINK3_VBUS_VTG_17_2V             17.2f

/**
 * @brief USB-C Sink 3 wiper and resistance data values.
 * @details Specified wiper and resistance data values of USB-C Sink 3 Click driver.
 */
#define USBCSINK3_WIPER_POS_MAX              255
#define USBCSINK3_RES_6_8_KOHM               6.8f
#define USBCSINK3_RES_16_KOHM                16.0f
#define USBCSINK3_RES_27_KOHM                27.0f
#define USBCSINK3_RES_36_KOHM                36.0f
#define USBCSINK3_RES_45_3_KOHM              45.3f
#define USBCSINK3_RES_56_KOHM                56.0f
#define USBCSINK3_RES_64_9_KOHM              64.9f
#define USBCSINK3_RES_75_KOHM                75.0f
#define USBCSINK3_RES_82_KOHM                82.0f
#define USBCSINK3_RES_91_KOHM                91.0f
#define USBCSINK3_RES_100_KOHM               100.0f
#define USBCSINK3_VBUS_R11_RES_73_2_KOHM     73.2f
#define USBCSINK3_VBUS_R13_RES_10_KOHM       10.0f

/**
 * @brief USB-C Sink 3 ADC setting.
 * @details Specified settings for ADC of USB-C Sink 3 Click driver.
 */
#define USBCSINK3_ADC_RESOLUTION             0x0FFF
#define USBCSINK3_VREF_3V3                   3.3
#define USBCSINK3_VREF_5V                    5.0

/**
 * @brief USB-C Sink 3 device address setting.
 * @details Specified setting for device slave address selection of
 * USB-C Sink 3 Click driver.
 */
#define USBCSINK3_DEVICE_ADDRESS             0x41

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b usbcsink3_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define USBCSINK3_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define USBCSINK3_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // usbcsink3_set

/**
 * @defgroup usbcsink3_map USB-C Sink 3 MikroBUS Map
 * @brief MikroBUS pin mapping of USB-C Sink 3 Click driver.
 */

/**
 * @addtogroup usbcsink3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of USB-C Sink 3 Click to the selected MikroBUS.
 */
#define USBCSINK3_MAP_MIKROBUS( cfg, mikrobus )     \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN )

/*! @} */ // usbcsink3_map
/*! @} */ // usbcsink3


/**
 * @brief USB-C Sink 3 Click context object.
 * @details Context object definition of USB-C Sink 3 Click driver.
 */
typedef struct usbcsink3_s
{
    analog_in_t  adc;     /**< ADC module object. */
    float        vref;    /**< ADC reference voltage. */

    i2c_master_t i2c;     /**< I2C driver object. */
    spi_master_t spi;     /**< SPI driver object. */

    uint8_t      slave_address;    /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;      /**< Chip select pin descriptor (used for SPI driver). */

} usbcsink3_t;

/**
 * @brief USB-C Sink 3 Click configuration object.
 * @details Configuration object definition of USB-C Sink 3 Click driver.
 */
typedef struct
{
    pin_name_t scl;     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;     /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;     /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;      /**< Chip select pin descriptor for SPI driver. */
    pin_name_t an;      /**< Analog pin descriptor. */
   
   analog_in_resolution_t resolution;    /**< ADC resolution. */
   float        vref;                    /**< ADC reference voltage. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */
    
    uint32_t                          spi_speed;      /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;       /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;    /**< Chip select pin polarity. */

} usbcsink3_cfg_t;

/**
 * @brief USB-C Sink 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    USBCSINK3_OK = 0,
    USBCSINK3_ERROR = -1

} usbcsink3_return_value_t;

/**
 * @brief USB-C Sink 3 Click voltage selection value data.
 * @details Predefined enum values for driver voltage selection values.
 */
typedef enum
{
    USBCSINK3_VTG_SEL_5V = 0,
    USBCSINK3_VTG_SEL_9V,
    USBCSINK3_VTG_SEL_15V,
    USBCSINK3_VTG_SEL_20V,
    USBCSINK3_VTG_SEL_4_3V,
    USBCSINK3_VTG_SEL_8_6V,
    USBCSINK3_VTG_SEL_12_9V,
    USBCSINK3_VTG_SEL_17_2V

} usbcsink3_vtg_sel_t;

/**
 * @brief USB-C Sink 3 Click power selection value data.
 * @details Predefined enum values for driver power selection values.
 */
typedef enum
{
    USBCSINK3_PWR_SEL_12W = 0,
    USBCSINK3_PWR_SEL_15W,
    USBCSINK3_PWR_SEL_18W,
    USBCSINK3_PWR_SEL_20W,
    USBCSINK3_PWR_SEL_27W,
    USBCSINK3_PWR_SEL_36W,
    USBCSINK3_PWR_SEL_45W,
    USBCSINK3_PWR_SEL_60W,
    USBCSINK3_PWR_SEL_90W,
    USBCSINK3_PWR_SEL_100W

} usbcsink3_pwr_sel_t;


/*!
 * @addtogroup usbcsink3 USB-C Sink 3 Click Driver
 * @brief API for configuring and manipulating USB-C Sink 3 Click driver.
 * @{
 */

/**
 * @brief USB-C Sink 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #usbcsink3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void usbcsink3_cfg_setup ( usbcsink3_cfg_t *cfg );

/**
 * @brief USB-C Sink 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #usbcsink3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #usbcsink3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink3_init ( usbcsink3_t *ctx, usbcsink3_cfg_t *cfg );

/**
 * @brief USB-C Sink 3 default configuration function.
 * @details This function executes a default configuration of USB-C Sink 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #usbcsink3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t usbcsink3_default_cfg ( usbcsink3_t *ctx );

/**
 * @brief USB-C Sink 3 I2C writing function.
 * @details This function writes a data byte to the selected register 
 * of the TCA9536, Remote 4-Bit I2C and SMBus I/O Expander with Configuration Registers
 * on the USB-C Sink 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #usbcsink3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink3_i2c_write ( usbcsink3_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief USB-C Sink 3 I2C reading function.
 * @details This function reads a data byte from the selected register 
 * of the TCA9536, Remote 4-Bit I2C and SMBus I/O Expander with Configuration Registers
 * on the USB-C Sink 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #usbcsink3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink3_i2c_read ( usbcsink3_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief USB-C Sink 3 SPI writing function.
 * @details This function writes a data byte to the selected register 
 * of the MCP41100T, Single/Dual Digital Potentiometer with SPI Interface
 * on the USB-C Sink 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #usbcsink3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink3_spi_write ( usbcsink3_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief USB-C Sink 3 read raw ADC value function.
 * @details This function ads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #usbcsink3_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink3_read_raw_adc ( usbcsink3_t *ctx, uint16_t *raw_adc );

/**
 * @brief USB-C Sink 3 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #usbcsink3_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t usbcsink3_read_voltage ( usbcsink3_t *ctx, float *voltage );

/**
 * @brief USB-C Sink 3 set vref function.
 * @details This function sets the voltage reference for the USB-C Sink 3 click driver.
 * @param[in] ctx : Click context object.
 * See #usbcsink3_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b usbcsink3_init is 3.3V.
 */
err_t usbcsink3_set_vref ( usbcsink3_t *ctx, float vref );

/**
 * @brief USB-C Sink 3 get VBUS function.
 * @details This function reads raw ADC value and converts it to proportional voltage level
 * and calculate the output voltage using the voltage divider calculation.
 * @param[in] ctx : Click context object.
 * See #usbcsink3_t object definition for detailed explanation.
 * @param[in] vbus : Output voltage [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink3_get_vbus ( usbcsink3_t *ctx, float *vbus );

/**
 * @brief USB-C Sink 3 set the wiper position function.
 * @details This function sets the position of the wiper
 * of the MCP41100T, Single/Dual Digital Potentiometer with SPI Interface
 * on the USB-C Sink 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #usbcsink3_t object definition for detailed explanation.
 * @param[in] wiper_pos : Wiper position [0-255].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink3_set_wiper ( usbcsink3_t *ctx, uint8_t wiper_pos );

/**
 * @brief USB-C Sink 3 set the resistance function.
 * @details This function sets the resistance
 * of the MCP41100T, Single/Dual Digital Potentiometer with SPI Interface
 * on the USB-C Sink 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #usbcsink3_t object definition for detailed explanation.
 * @param[in] resistence : Resistance from 6.8 to 91.0 [kOhm].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink3_set_resistence ( usbcsink3_t *ctx, float resistence );

/**
 * @brief USB-C Sink 3 set the voltage function.
 * @details This function sets the output voltage 
 * of the TCA9536, Remote 4-Bit I2C and SMBus I/O Expander with Configuration Registers
 * on the USB-C Sink 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #usbcsink3_t object definition for detailed explanation.
 * @param[in] voltage : Voltage from 5.0 to 17.2 [V].
 * See usbcsink3_vtg_sel_t definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink3_set_voltage ( usbcsink3_t *ctx, usbcsink3_vtg_sel_t voltage );

/**
 * @brief USB-C Sink 3 set the power function.
 * @details This function sets the output power by sets desired resistance value
 * of the MCP41100T, Single/Dual Digital Potentiometer with SPI Interface
 * on the USB-C Sink 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #usbcsink3_t object definition for detailed explanation.
 * @param[in] power : Power from 12.0 to 100.0 [W].
 * See usbcsink3_pwr_sel_t definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink3_set_power ( usbcsink3_t *ctx, usbcsink3_pwr_sel_t power );

#ifdef __cplusplus
}
#endif
#endif // USBCSINK3_H

/*! @} */ // usbcsink3

// ------------------------------------------------------------------------ END
