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
 * @file c3dhall4.h
 * @brief This file contains API for 3D Hall 4 Click Driver.
 */

#ifndef C3DHALL4_H
#define C3DHALL4_H

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
#include "drv_analog_in.h"

/*!
 * @addtogroup c3dhall4 3D Hall 4 Click Driver
 * @brief API for configuring and manipulating 3D Hall 4 Click driver.
 * @{
 */

/**
 * @defgroup c3dhall4_reg 3D Hall 4 Registers List
 * @brief List of registers of 3D Hall 4 Click driver.
 */

/**
 * @addtogroup c3dhall4_reg
 * @{
 */

/**
 * @brief 3D Hall 4 register map.
 * @details Specified register map of 3D Hall 4 Click driver.
 */
#define C3DHALL4_REG_0                      0x00
#define C3DHALL4_REG_1                      0x01
#define C3DHALL4_REG_2                      0x02
#define C3DHALL4_REG_3                      0x03
#define C3DHALL4_REG_4                      0x04
#define C3DHALL4_REG_5                      0x05
#define C3DHALL4_REG_6                      0x06
#define C3DHALL4_REG_7                      0x07
#define C3DHALL4_REG_PWM_CTRL               0x08
#define C3DHALL4_REG_CHANNEL_CTRL           0x09
#define C3DHALL4_REG_OSC_TRIM               0x0A
#define C3DHALL4_REG_THRES_X                0x0B
#define C3DHALL4_REG_THRES_Z                0x0C
#define C3DHALL4_REG_THRES_Y                0x0D
#define C3DHALL4_REG_G_CTRL_X               0x0E
#define C3DHALL4_REG_G_CTRL_Z               0x0F
#define C3DHALL4_REG_G_CTRL_Y               0x10
#define C3DHALL4_REG_DAC_X                  0x11
#define C3DHALL4_REG_DAC_Z                  0x12
#define C3DHALL4_REG_DAC_Y                  0x13
#define C3DHALL4_REG_SENS_X                 0x14
#define C3DHALL4_REG_SENS_Z                 0x15
#define C3DHALL4_REG_SENS_Y                 0x16
#define C3DHALL4_REG_SENS_TC_X              0x17
#define C3DHALL4_REG_SENS_TC_Z              0x18
#define C3DHALL4_REG_SENS_TC_Y              0x19
#define C3DHALL4_REG_OFFSET_X               0x1A
#define C3DHALL4_REG_OFFSET_Z               0x1B
#define C3DHALL4_REG_OFFSET_Y               0x1C
#define C3DHALL4_REG_OFFSET_TC_X            0x1D
#define C3DHALL4_REG_OFFSET_TC_Z            0x1E
#define C3DHALL4_REG_OFFSET_TC_Y            0x1F
#define C3DHALL4_REG_STATUS                 0x3F
#define C3DHALL4_REG_ADC_DATAXL             0x40
#define C3DHALL4_REG_ADC_DATAXH             0x41
#define C3DHALL4_REG_ADC_DATAZL             0x42
#define C3DHALL4_REG_ADC_DATAZH             0x43
#define C3DHALL4_REG_ADC_DATAYL             0x44
#define C3DHALL4_REG_ADC_DATAYH             0x45
#define C3DHALL4_REG_ADC_DATATL             0x46
#define C3DHALL4_REG_ADC_DATATH             0x47

/**
 * @brief 3D Hall 4 eeprom map.
 * @details Specified eeprom map of 3D Hall 4 Click driver.
 */
#define C3DHALL4_EREG_0                     0x00
#define C3DHALL4_EREG_1                     0x01
#define C3DHALL4_EREG_2                     0x02
#define C3DHALL4_EREG_3                     0x03
#define C3DHALL4_EREG_4                     0x04
#define C3DHALL4_EREG_5                     0x05
#define C3DHALL4_EREG_6                     0x06
#define C3DHALL4_EREG_7                     0x07
#define C3DHALL4_EREG_PWM_CTRL              0x08
#define C3DHALL4_EREG_CHANNEL_CTRL          0x09
#define C3DHALL4_EREG_OSC_TRIM              0x0A
#define C3DHALL4_EREG_THRES_Y               0x0B
#define C3DHALL4_EREG_THRES_X               0x0C
#define C3DHALL4_EREG_THRES_Z               0x0D
#define C3DHALL4_EREG_GAIN_SEL              0x0E
#define C3DHALL4_EREG_DAC_Y_G0              0x40
#define C3DHALL4_EREG_DAC_X_G0              0x41
#define C3DHALL4_EREG_DAC_Z_G0              0x42
#define C3DHALL4_EREG_SENS_Y_G0             0x43
#define C3DHALL4_EREG_SENS_X_G0             0x44
#define C3DHALL4_EREG_SENS_Z_G0             0x45
#define C3DHALL4_EREG_SENS_TC_Y_G0          0x46
#define C3DHALL4_EREG_SENS_TC_X_G0          0x47
#define C3DHALL4_EREG_SENS_TC_Z_G0          0x48
#define C3DHALL4_EREG_OFFSET_Y_G0           0x49
#define C3DHALL4_EREG_OFFSET_X_G0           0x4A
#define C3DHALL4_EREG_OFFSET_Z_G0           0x4B
#define C3DHALL4_EREG_OFFSET_TC_Y_G0        0x4C
#define C3DHALL4_EREG_OFFSET_TC_X_G0        0x4D
#define C3DHALL4_EREG_OFFSET_TC_Z_G0        0x4E
#define C3DHALL4_EREG_DAC_Y_G1              0x50
#define C3DHALL4_EREG_DAC_X_G1              0x51
#define C3DHALL4_EREG_DAC_Z_G1              0x52
#define C3DHALL4_EREG_SENS_Y_G1             0x53
#define C3DHALL4_EREG_SENS_X_G1             0x54
#define C3DHALL4_EREG_SENS_Z_G1             0x55
#define C3DHALL4_EREG_SENS_TC_Y_G1          0x56
#define C3DHALL4_EREG_SENS_TC_X_G1          0x57
#define C3DHALL4_EREG_SENS_TC_Z_G1          0x58
#define C3DHALL4_EREG_OFFSET_Y_G1           0x59
#define C3DHALL4_EREG_OFFSET_X_G1           0x5A
#define C3DHALL4_EREG_OFFSET_Z_G1           0x5B
#define C3DHALL4_EREG_OFFSET_TC_Y_G1        0x5C
#define C3DHALL4_EREG_OFFSET_TC_X_G1        0x5D
#define C3DHALL4_EREG_OFFSET_TC_Z_G1        0x5E
#define C3DHALL4_EREG_DAC_Y_G2              0x60
#define C3DHALL4_EREG_DAC_X_G2              0x61
#define C3DHALL4_EREG_DAC_Z_G2              0x62
#define C3DHALL4_EREG_SENS_Y_G2             0x63
#define C3DHALL4_EREG_SENS_X_G2             0x64
#define C3DHALL4_EREG_SENS_Z_G2             0x65
#define C3DHALL4_EREG_SENS_TC_Y_G2          0x66
#define C3DHALL4_EREG_SENS_TC_X_G2          0x67
#define C3DHALL4_EREG_SENS_TC_Z_G2          0x68
#define C3DHALL4_EREG_OFFSET_Y_G2           0x69
#define C3DHALL4_EREG_OFFSET_X_G2           0x6A
#define C3DHALL4_EREG_OFFSET_Z_G2           0x6B
#define C3DHALL4_EREG_OFFSET_TC_Y_G2        0x6C
#define C3DHALL4_EREG_OFFSET_TC_X_G2        0x6D
#define C3DHALL4_EREG_OFFSET_TC_Z_G2        0x6E
#define C3DHALL4_EREG_DAC_Y_G3              0x70
#define C3DHALL4_EREG_DAC_X_G3              0x71
#define C3DHALL4_EREG_DAC_Z_G3              0x72
#define C3DHALL4_EREG_SENS_Y_G3             0x73
#define C3DHALL4_EREG_SENS_X_G3             0x74
#define C3DHALL4_EREG_SENS_Z_G3             0x75
#define C3DHALL4_EREG_SENS_TC_Y_G3          0x76
#define C3DHALL4_EREG_SENS_TC_X_G3          0x77
#define C3DHALL4_EREG_SENS_TC_Z_G3          0x78
#define C3DHALL4_EREG_OFFSET_Y_G3           0x79
#define C3DHALL4_EREG_OFFSET_X_G3           0x7A
#define C3DHALL4_EREG_OFFSET_Z_G3           0x7B
#define C3DHALL4_EREG_OFFSET_TC_Y_G3        0x7C
#define C3DHALL4_EREG_OFFSET_TC_X_G3        0x7D
#define C3DHALL4_EREG_OFFSET_TC_Z_G3        0x7E
#define C3DHALL4_EREG_KEY                   0xFE
#define C3DHALL4_EREG_CHECKSUM              0xFF

/*! @} */ // c3dhall4_reg

/**
 * @defgroup c3dhall4_set 3D Hall 4 Registers Settings
 * @brief Settings for registers of 3D Hall 4 Click driver.
 */

/**
 * @addtogroup c3dhall4_set
 * @{
 */

/**
 * @brief 3D Hall 4 special commands setting.
 * @details Specified setting for special commands of 3D Hall 4 Click driver.
 */
#define C3DHALL4_CMD_REG_WRITE              0x00
#define C3DHALL4_CMD_REG_READ               0x80
#define C3DHALL4_CMD_EREG_WRITE             0x01
#define C3DHALL4_CMD_EREG_READ              0x81
#define C3DHALL4_CMD_SPECIAL_KEY            0xA5

/**
 * @brief 3D Hall 4 ADC VREF setting.
 * @details Specified setting for ADC VREF of 3D Hall 4 Click driver.
 */
#define C3DHALL4_ADC_VREF_3V3               3.3f
#define C3DHALL4_ADC_VREF_5V                5.0f

/**
 * @brief 3D Hall 4 range/sens/offset setting.
 * @details Specified setting for range/sens/offset of 3D Hall 4 Click driver.
 */
#define C3DHALL4_RANGE_20                   0x00
#define C3DHALL4_RANGE_40                   0x01
#define C3DHALL4_RANGE_350                  0x02
#define C3DHALL4_RANGE_3000                 0x03
#define C3DHALL4_RANGE_MASK                 0x03
#define C3DHALL4_SENS_RANGE_3000            6.0f
#define C3DHALL4_SENS_RANGE_350             60.0f
#define C3DHALL4_SENS_RANGE_40              550.0f
#define C3DHALL4_SENS_RANGE_20              1000.0f
#define C3DHALL4_SENS_TEMPERATURE           168.0f
#define C3DHALL4_OFFSET_XYZ                 32768
#define C3DHALL4_OFFSET_TEMPERATURE         19913

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b c3dhall4_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define C3DHALL4_SET_DATA_SAMPLE_EDGE       SET_SPI_DATA_SAMPLE_EDGE
#define C3DHALL4_SET_DATA_SAMPLE_MIDDLE     SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // c3dhall4_set

/**
 * @defgroup c3dhall4_map 3D Hall 4 MikroBUS Map
 * @brief MikroBUS pin mapping of 3D Hall 4 Click driver.
 */

/**
 * @addtogroup c3dhall4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 3D Hall 4 Click to the selected MikroBUS.
 */
#define C3DHALL4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.tan  = MIKROBUS( mikrobus, MIKROBUS_AN );

/*! @} */ // c3dhall4_map
/*! @} */ // c3dhall4

/**
 * @brief 3D Hall 4 Click context object.
 * @details Context object definition of 3D Hall 4 Click driver.
 */
typedef struct
{
    spi_master_t spi;           /**< SPI driver object. */
    analog_in_t  adc;           /**< ADC module object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */
    
    float        x_sens;        /**< X-axis sensitivity data. */
    float        y_sens;        /**< Y-axis sensitivity data. */
    float        z_sens;        /**< Z-axis sensitivity data. */

} c3dhall4_t;

/**
 * @brief 3D Hall 4 Click configuration object.
 * @details Configuration object definition of 3D Hall 4 Click driver.
 */
typedef struct
{
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */
    pin_name_t tan;             /**< Sensor chip temperature voltage output pin. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */
    
    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */

} c3dhall4_cfg_t;

/**
 * @brief 3D Hall 4 Click data object.
 * @details Data object definition of 3D Hall 4 Click driver.
 */
typedef struct
{
    uint8_t status;             /**< Status byte. */
    float x_data;               /**< X-axis data. */
    float y_data;               /**< Y-axis data. */
    float z_data;               /**< Z-axis data. */
    float chip_temp;            /**< Chip internal temperature. */

} c3dhall4_data_t;

/**
 * @brief 3D Hall 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C3DHALL4_OK = 0,
    C3DHALL4_ERROR = -1

} c3dhall4_return_value_t;

/*!
 * @addtogroup c3dhall4 3D Hall 4 Click Driver
 * @brief API for configuring and manipulating 3D Hall 4 Click driver.
 * @{
 */

/**
 * @brief 3D Hall 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c3dhall4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c3dhall4_cfg_setup ( c3dhall4_cfg_t *cfg );

/**
 * @brief 3D Hall 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #c3dhall4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c3dhall4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall4_init ( c3dhall4_t *ctx, c3dhall4_cfg_t *cfg );

/**
 * @brief 3D Hall 4 default configuration function.
 * @details This function executes a default configuration of 3D Hall 4
 * click board.
 * @param[in] ctx : Click context object.
 * See #c3dhall4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c3dhall4_default_cfg ( c3dhall4_t *ctx );

/**
 * @brief 3D Hall 4 reg write function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c3dhall4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall4_reg_write ( c3dhall4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 3D Hall 4 reg read function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c3dhall4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall4_reg_read ( c3dhall4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief 3D Hall 4 EEPROM write function.
 * @details This function writes a desired data to the selected EEPROM address
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c3dhall4_t object definition for detailed explanation.
 * @param[in] address : EEPROM address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The c3dhall4_eeprom_update_cksum function must be called after EEPROM write in order
 * for the changes to take effect after power up.
 */
err_t c3dhall4_eeprom_write ( c3dhall4_t *ctx, uint8_t address, uint8_t data_in );

/**
 * @brief 3D Hall 4 EEPROM read function.
 * @details This function reads data from the selected EEPROM address by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c3dhall4_t object definition for detailed explanation.
 * @param[in] address : EEPROM address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall4_eeprom_read ( c3dhall4_t *ctx, uint8_t address, uint8_t *data_out );

/**
 * @brief 3D Hall 4 EEPROM update cksum function.
 * @details This function updates EEPROM checksum. It must be called after EEPROM write
 * in order for the changes to take effect after power up.
 * @param[in] ctx : Click context object.
 * See #c3dhall4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall4_eeprom_update_cksum ( c3dhall4_t *ctx );

/**
 * @brief 3D Hall 4 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #c3dhall4_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall4_read_an_pin_value ( c3dhall4_t *ctx, uint16_t *data_out );

/**
 * @brief 3D Hall 4 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #c3dhall4_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t c3dhall4_read_an_pin_voltage ( c3dhall4_t *ctx, float *data_out );

/**
 * @brief 3D Hall 4 read data function.
 * @details This function reads the measurement status, 3-axes magnetic field data,
 * and the chip internal temperature.
 * @param[in] ctx : Click context object.
 * See #c3dhall4_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * See #c3dhall4_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall4_read_data ( c3dhall4_t *ctx, c3dhall4_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // C3DHALL4_H

/*! @} */ // c3dhall4

// ------------------------------------------------------------------------ END
