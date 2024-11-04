/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish,distribute, sublicense, and/or sell
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
 * @file tdc2.h
 * @brief This file contains API for TDC 2 Click Driver.
 */

#ifndef TDC2_H
#define TDC2_H

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
 * @addtogroup tdc2 TDC 2 Click Driver
 * @brief API for configuring and manipulating TDC 2 Click driver.
 * @{
 */

/**
 * @defgroup tdc2_reg TDC 2 Registers List
 * @brief List of registers of TDC 2 Click driver.
 */

/**
 * @addtogroup tdc2_reg
 * @{
 */

/**
 * @brief TDC 2 description register.
 * @details Specified register for description of TDC 2 Click driver.
 */

/**
 * @brief TDC 2 configuration register.
 * @details Specified configuration register for description of TDC 2 Click driver.
 */
#define TDC2_REG_CFG0                       0x00
#define TDC2_REG_CFG1                       0x01
#define TDC2_REG_CFG2                       0x02
#define TDC2_REG_CFG3                       0x03
#define TDC2_REG_CFG4                       0x04
#define TDC2_REG_CFG5                       0x05
#define TDC2_REG_CFG6                       0x06
#define TDC2_REG_CFG7                       0x07
#define TDC2_REG_CFG8                       0x08
#define TDC2_REG_CFG9                       0x09
#define TDC2_REG_CFG10                      0x0A
#define TDC2_REG_CFG11                      0x0B
#define TDC2_REG_CFG12                      0x0C
#define TDC2_REG_CFG13                      0x0D
#define TDC2_REG_CFG14                      0x0E
#define TDC2_REG_CFG15                      0x0F
#define TDC2_REG_CFG16                      0x10

/**
 * @brief TDC 2 data register.
 * @details Specified data register for description of TDC 2 Click driver.
 */
#define TDC2_REG_INDEX_CH1_BYTE3            0x08
#define TDC2_REG_INDEX_CH1_BYTE2            0x09
#define TDC2_REG_INDEX_CH1_BYTE1            0x0A
#define TDC2_REG_STOP_CH1_BYTE3             0x0B
#define TDC2_REG_STOP_CH1_BYTE2             0x0C
#define TDC2_REG_STOP_CH1_BYTE1             0x0D
#define TDC2_REG_INDEX_CH2_BYTE3            0x0E
#define TDC2_REG_INDEX_CH2_BYTE2            0x0F
#define TDC2_REG_INDEX_CH2_BYTE1            0x10
#define TDC2_REG_STOP_CH2_BYTE3             0x11
#define TDC2_REG_STOP_CH2_BYTE2             0x12
#define TDC2_REG_STOP_CH2_BYTE1             0x13
#define TDC2_REG_INDEX_CH3_BYTE3            0x14
#define TDC2_REG_INDEX_CH3_BYTE2            0x15
#define TDC2_REG_INDEX_CH3_BYTE1            0x16
#define TDC2_REG_STOP_CH3_BYTE3             0x17
#define TDC2_REG_STOP_CH3_BYTE2             0x18
#define TDC2_REG_STOP_CH3_BYTE1             0x19
#define TDC2_REG_INDEX_CH4_BYTE3            0x1A
#define TDC2_REG_INDEX_CH4_BYTE2            0x1B
#define TDC2_REG_INDEX_CH4_BYTE1            0x1C
#define TDC2_REG_STOP_CH4_BYTE3             0x1D
#define TDC2_REG_STOP_CH4_BYTE2             0x1E
#define TDC2_REG_STOP_CH4_BYTE1             0x1F

/*! @} */ // tdc2_reg

/**
 * @defgroup tdc2_set TDC 2 Registers Settings
 * @brief Settings for registers of TDC 2 Click driver.
 */

/**
 * @addtogroup tdc2_set
 * @{
 */

/**
 * @brief TDC 2 description setting.
 * @details Specified setting for description of TDC 2 Click driver.
 */

/**
 * @brief TDC 2 commands.
 * @details Specified commands of TDC 2 Click driver.
 */
#define TDC2_SPIOPC_POWER                   0x30
#define TDC2_SPIOPC_INIT                    0x18
#define TDC2_SPIOPC_WRITE_CONFIG            0x80
#define TDC2_SPIOPC_READ_CONFIG             0x40
#define TDC2_SPIOPC_READ_RESULTS            0x60
#define TDC2_SPIOPC_READ_RESULTS            0x60

/**
 * @brief TDC 2 CFG0 register description setting.
 * @details Specified setting for CFG0 register of TDC 2 Click driver.
 */
#define TDC2_ENABLE_STOP1_PIN               0x01
#define TDC2_DISABLE_STOP1_PIN              0x00
#define TDC2_ENABLE_STOP2_PIN               0x02
#define TDC2_DISABLE_STOP2_PIN              0x00
#define TDC2_ENABLE_STOP3_PIN               0x04
#define TDC2_DISABLE_STOP3_PIN              0x00
#define TDC2_ENABLE_STOP4_PIN               0x08
#define TDC2_DISABLE_STOP4_PIN              0x00
#define TDC2_ENABLE_REFCLK_PIN              0x10
#define TDC2_DISABLE_REFCLK_PIN             0x00
#define TDC2_ENABLE_DISABLE_PIN             0x40
#define TDC2_DISABLE_DISABLE_PIN            0x00
#define TDC2_ENABLE_RSTINDX_PIN             0x80
#define TDC2_DISABLE_RSTINDX_PIN            0x00

/**
 * @brief TDC 2 CFG1 register description setting.
 * @details Specified setting for CFG1 register of TDC 2 Click driver.
 */
#define TDC2_HIT_ENABLE_STOP1               0x01
#define TDC2_HIT_DISABLE_STOP1              0x00
#define TDC2_HIT_ENABLE_STOP2               0x02
#define TDC2_HIT_DISABLE_STOP2              0x00
#define TDC2_HIT_ENABLE_STOP3               0x04
#define TDC2_HIT_DISABLE_STOP3              0x00
#define TDC2_HIT_ENABLE_STOP4               0x08
#define TDC2_HIT_DISABLE_STOP4              0x00
#define TDC2_CHANNEL_COMBINE_NORMAL         0x00
#define TDC2_CHANNEL_COMBINE_PULSE_DISTANCE 0x10
#define TDC2_CHANNEL_COMBINE_PULSE_WIDTH    0x20
#define TDC2_HIGH_RESOLUTION_OFF            0x00
#define TDC2_HIGH_RESOLUTION_X2             0x40
#define TDC2_HIGH_RESOLUTION_X4             0x80

/**
 * @brief TDC 2 CFG2 register description setting.
 * @details Specified setting for CFG2 register of TDC 2 Click driver.
 */
#define TDC2_FIFO_COMMON_READ_OFF           0x00
#define TDC2_FIFO_COMMON_READ_ON            0x40
#define TDC2_FIFO_BLOCKWISE_READ_OFF        0x00
#define TDC2_FIFO_BLOCKWISE_READ_ON         0x80

/**
 * @brief TDC 2 fixed value registers description setting.
 * @details Specified setting for fixed value registers of TDC 2 Click driver.
 */
#define TDC2_CFG6_FIXED_VALUE               0xC0
#define TDC2_CFG8_FIXED_VALUE               0xA1
#define TDC2_CFG9_FIXED_VALUE               0x13
#define TDC2_CFG10_FIXED_VALUE              0x00
#define TDC2_CFG11_FIXED_VALUE              0x0A
#define TDC2_CFG12_FIXED_VALUE              0xCC
#define TDC2_CFG13_FIXED_VALUE              0x05
#define TDC2_CFG14_FIXED_VALUE              0xF1
#define TDC2_CFG15_FIXED_VALUE              0x7D
#define TDC2_CFG16_FIXED_VALUE              0x04

/**
 * @brief TDC 2 CFG7 register description setting.
 * @details Specified setting for CFG7 register of TDC 2 Click driver.
 */
#define TDC2_CFG7_FIXED_VALUE               0x23
#define TDC2_REFERENCE_CLOCK_INTERNAL       0x80
#define TDC2_REFERENCE_CLOCK_EXTERNAL       0x00

/**
 * @brief TDC 2 resolution setting.
 * @details Specified setting for resolution of TDC 2 Click driver.
 */
#define TDC2_1pS_RESOLUTION                 125000
#define TDC2_5pS_RESOLUTION                 62500
#define TDC2_10pS_RESOLUTION                12500

#define TDC2_uS_TO_mS                       1000000

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b tdc2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define TDC2_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define TDC2_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // tdc2_set

/**
 * @defgroup tdc2_map TDC 2 MikroBUS Map
 * @brief MikroBUS pin mapping of TDC 2 Click driver.
 */

/**
 * @addtogroup tdc2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of TDC 2 Click to the selected MikroBUS.
 */
#define TDC2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rir  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.dis = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // tdc2_map
/*! @} */ // tdc2

/**
 * @brief TDC 2 Click context object.
 * @details Context object definition of TDC 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rir;      /**< Reference index reset signal. */
    digital_out_t rst;      /**< Chip ID select. */
    digital_out_t dis;      /**< Disabling pin for stop channels.. */

    // Input pins
    digital_in_t int_pin;   /**< SPI interrupt. */

    // Modules
    spi_master_t spi;                  /**< SPI driver object. */

    pin_name_t   chip_select;          /**< Chip select pin descriptor (used for SPI driver). */

} tdc2_t;

/**
 * @brief TDC 2 Click configuration object.
 * @details Configuration object definition of TDC 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rir;             /**< Reference index reset signal. */
    pin_name_t rst;             /**< Chip ID select. */
    pin_name_t dis;             /**< Disabling pin for stop channels. */
    pin_name_t int_pin;         /**< SPI interrupt. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} tdc2_cfg_t;

/**
 * @brief TDC 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TDC2_OK = 0,
    TDC2_ERROR = -1

} tdc2_return_value_t;

/*!
 * @addtogroup tdc2 TDC 2 Click Driver
 * @brief API for configuring and manipulating TDC 2 Click driver.
 * @{
 */

/**
 * @brief TDC 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #tdc2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void tdc2_cfg_setup ( tdc2_cfg_t *cfg );

/**
 * @brief TDC 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #tdc2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #tdc2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tdc2_init ( tdc2_t *ctx, tdc2_cfg_t *cfg );

/**
 * @brief TDC 2 default configuration function.
 * @details This function executes a default configuration of TDC 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #tdc2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t tdc2_default_cfg ( tdc2_t *ctx );

/**
 * @brief TDC 2 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #tdc2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tdc2_generic_write ( tdc2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief TDC 2 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #tdc2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tdc2_generic_read ( tdc2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief TDC 2 config data writing function.
 * @details This function writes a desired number of configuration data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #tdc2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Configuration data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tdc2_write_config ( tdc2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief TDC 2 config data reading function.
 * @details This function reads a desired number of configuration data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #tdc2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read configuration data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tdc2_read_config ( tdc2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief TDC 2 results data reading function.
 * @details This function reads a reference index and stop result 
 * data from FIFO by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #tdc2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] reference_index : Reference index output data.
 * @param[out] stop_result : Stop result read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tdc2_read_results( tdc2_t *ctx, uint8_t reg, uint32_t *reference_index, uint32_t *stop_result );

/**
 * @brief TDC 2 send command function.
 * @details This function is used to send byte of command 
 * data by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #tdc2_t object definition for detailed explanation.
 * @param[in] command : Command to be sent.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tdc2_send_command ( tdc2_t *ctx, uint8_t command );

/**
 * @brief TDC 2 software reset function.
 * @details This function is used to perform a software reset of the device.
 * @param[in] ctx : Click context object.
 * See #tdc2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tdc2_sw_reset ( tdc2_t *ctx );

/**
 * @brief TDC 2 start measuring function.
 * @details This function is used to configure the device into reading mode.
 * @param[in] ctx : Click context object.
 * See #tdc2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tdc2_start_measuring ( tdc2_t *ctx );

/**
 * @brief TDC 2 set resolution function.
 * @details This function is used to write resolution of the device.
 * @param[in] ctx : Click context object.
 * See #tdc2_t object definition for detailed explanation.
 * @param[in] resolution : Resolution of the device.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tdc2_set_resolution ( tdc2_t *ctx, uint32_t resolution );

/**
 * @brief TDC 2 set resolution function.
 * @details This function is used to read resolution of the device.
 * @param[in] ctx : Click context object.
 * See #tdc2_t object definition for detailed explanation.
 * @param[out] resolution : Resolution of the device.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tdc2_get_resolution ( tdc2_t *ctx, uint32_t *resolution );

/**
 * @brief TDC 2 reset reference index function.
 * @details This function is used to reset reference index of the device.
 * @param[in] ctx : Click context object.
 * See #tdc2_t object definition for detailed explanation.
 * @return Nothing.
 * @note To use this function RIR pin must be activated by configuring it.
 */
void tdc2_reset_index ( tdc2_t *ctx );

/**
 * @brief TDC 2 disable stop channels function.
 * @details This function is used to disable STOP channels of the device.
 * @param[in] ctx : Click context object.
 * See #tdc2_t object definition for detailed explanation.
 * @return Nothing.
 * @note To use this function DIS pin must be activated by configuring it.
 */
void tdc2_disable_stop_channels ( tdc2_t *ctx );

/**
 * @brief TDC 2 enable stop channels function.
 * @details This function is used to enable STOP channels of the device.
 * @param[in] ctx : Click context object.
 * See #tdc2_t object definition for detailed explanation.
 * @return Nothing.
 * @note To use this function DIS pin must be activated by configuring it.
 */
void tdc2_enable_stop_channels ( tdc2_t *ctx );

/**
 * @brief TDC 2 get int state function.
 * @details This function is used to read SPI interrupt state of the device.
 * @param[in] ctx : Click context object.
 * See #tdc2_t object definition for detailed explanation.
 * @return @li @c 0 - Int pin is low,
 *         @li @c 1 - Int pin is high.
 * @note None.
 */
uint8_t tdc2_get_int_state ( tdc2_t *ctx );

/**
 * @brief TDC 2 get time between stops function.
 * @details This function is used to get time between two stops in uS.
 * @param[in] ctx : Click context object.
 * See #tdc2_t object definition for detailed explanation.
 * @param[in] stop_result1 : Stop result of first event.
 * @param[in] reference_index1 : Reference index of first event.
 * @param[in] stop_result2 : Stop result of second event.
 * @param[in] reference_index2 : Reference index of second event.
 * @param[out] time_in_us : Calculated time in uS.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t tdc2_get_time_between_stops ( tdc2_t *ctx, uint32_t stop_result1, uint32_t reference_index1, 
                                    uint32_t stop_result2, uint32_t reference_index2, 
                                    uint32_t *time_in_us );

#ifdef __cplusplus
}
#endif
#endif // TDC2_H

/*! @} */ // tdc2

// ------------------------------------------------------------------------ END
