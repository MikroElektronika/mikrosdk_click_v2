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
 * @file digiin2.h
 * @brief This file contains API for DIGI IN 2 Click Driver.
 */

#ifndef DIGIIN2_H
#define DIGIIN2_H

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
 * @addtogroup digiin2 DIGI IN 2 Click Driver
 * @brief API for configuring and manipulating DIGI IN 2 Click driver.
 * @{
 */

/**
 * @defgroup digiin2_reg DIGI IN 2 Registers List
 * @brief List of registers of DIGI IN 2 Click driver.
 */

/**
 * @addtogroup digiin2_reg
 * @{
 */

/**
 * @brief DIGI IN 2 description register.
 * @details Specified register for description of DIGI IN 2 Click driver.
 */
#define DIGIIN2_REG_DISTATE                         0x00
#define DIGIIN2_REG_FAULT                           0x01
#define DIGIIN2_REG_F1MASK                          0x02
#define DIGIIN2_REG_CNFG1                           0x03
#define DIGIIN2_REG_CNFG2                           0x04
#define DIGIIN2_REG_CNFG3                           0x05
#define DIGIIN2_REG_CNFG4                           0x06
#define DIGIIN2_REG_CNFG5                           0x07
#define DIGIIN2_REG_CNFG6                           0x08
#define DIGIIN2_REG_CNFG7                           0x09
#define DIGIIN2_REG_CNFG8                           0x0A
#define DIGIIN2_REG_GLOBLCFG                        0x0B
#define DIGIIN2_REG_LED                             0x0C
#define DIGIIN2_REG_FAULT2                          0x0D
#define DIGIIN2_REG_F2MASK                          0x0E
#define DIGIIN2_REG_START_STOP                      0x0F
#define DIGIIN2_REG_CNT1_LSB                        0x10
#define DIGIIN2_REG_CNT1_MSB                        0x11
#define DIGIIN2_REG_CNT2_LSB                        0x12
#define DIGIIN2_REG_CNT2_MSB                        0x13
#define DIGIIN2_REG_CNT3_LSB                        0x14
#define DIGIIN2_REG_CNT3_MSB                        0x15
#define DIGIIN2_REG_CNT4_LSB                        0x16
#define DIGIIN2_REG_CNT4_MSB                        0x17
#define DIGIIN2_REG_CNT5_LSB                        0x18
#define DIGIIN2_REG_CNT5_MSB                        0x19
#define DIGIIN2_REG_CNT6_LSB                        0x1A
#define DIGIIN2_REG_CNT6_MSB                        0x1B
#define DIGIIN2_REG_CNT7_LSB                        0x1C
#define DIGIIN2_REG_CNT7_MSB                        0x1D
#define DIGIIN2_REG_CNT8_LSB                        0x1E
#define DIGIIN2_REG_CNT8_MSB                        0x1F

/*! @} */ // digiin2_reg

/**
 * @defgroup digiin2_set DIGI IN 2 Registers Settings
 * @brief Settings for registers of DIGI IN 2 Click driver.
 */

/**
 * @addtogroup digiin2_set
 * @{
 */

/**
 * @brief DIGI IN 2 DISTATE register setting.
 * @details Specified setting for DISTATE register of DIGI IN 2 Click driver.
 */
#define DIGIIN2_CHANNEL_1_MASK                      0x01
#define DIGIIN2_CHANNEL_2_MASK                      0x02
#define DIGIIN2_CHANNEL_3_MASK                      0x04
#define DIGIIN2_CHANNEL_4_MASK                      0x08
#define DIGIIN2_CHANNEL_5_MASK                      0x10
#define DIGIIN2_CHANNEL_6_MASK                      0x20
#define DIGIIN2_CHANNEL_7_MASK                      0x40
#define DIGIIN2_CHANNEL_8_MASK                      0x80

/**
 * @brief DIGI IN 2 Channel selection setting.
 * @details Specified setting for Channel selection of DIGI IN 2 Click driver.
 */
#define DIGIIN2_CHANNEL_1_SEL                       0x00
#define DIGIIN2_CHANNEL_2_SEL                       0x01
#define DIGIIN2_CHANNEL_3_SEL                       0x02
#define DIGIIN2_CHANNEL_4_SEL                       0x03
#define DIGIIN2_CHANNEL_5_SEL                       0x04
#define DIGIIN2_CHANNEL_6_SEL                       0x05
#define DIGIIN2_CHANNEL_7_SEL                       0x06
#define DIGIIN2_CHANNEL_8_SEL                       0x07

/**
 * @brief DIGI IN 2 FAULT1 register setting.
 * @details Specified setting for FAULT1 register of DIGI IN 2 Click driver.
 */
#define DIGIIN2_CRC_ERROR_FLAG                      0x80
#define DIGIIN2_POR                                 0x40
#define DIGIIN2_FAULT2                              0x20
#define DIGIIN2_TERMAL_SHUTDOWN                     0x10
#define DIGIIN2_TEMPERATURE_ALARM                   0x08
#define DIGIIN2_V24_UNDERVOLTAGE                    0x04
#define DIGIIN2_VM_VOLTAGE_LOW                      0x02

/**
 * @brief DIGI IN 2 F1MASK register setting.
 * @details Specified setting for F1MASK register of DIGI IN 2 Click driver.
 */
#define DIGIIN2_CRC_ERROR_FLAG_MASK                 0x80
#define DIGIIN2_FAULT2_MASK                         0x20
#define DIGIIN2_TERMAL_SHUTDOWN_MASK                0x10
#define DIGIIN2_TEMPERATURE_ALARM_MASK              0x08
#define DIGIIN2_V24_UNDERVOLTAGE_MASK               0x04
#define DIGIIN2_VM_VOLTAGE_LOW_MASK                 0x02

/**
 * @brief DIGI IN 2 CNFGx register setting.
 * @details Specified setting for CNFGx register of DIGI IN 2 Click driver.
 */
#define DIGIIN2_HITHR_HIGH                          0x80
#define DIGIIN2_HITHR_LOW                           0x00
#define DIGIIN2_SINK_MODE                           0x00
#define DIGIIN2_SOURCE_MODE                         0x40
#define DIGIIN2_CURR_OFF                            0x00
#define DIGIIN2_CURR_X1                             0x10
#define DIGIIN2_CURR_X3                             0x20
#define DIGIIN2_CURR_TTL_OFF                        0x30
#define DIGIIN2_GLITCH_FIL_EN                       0x08
#define DIGIIN2_GLITCH_FIL_DIS                      0x00
#define DIGIIN2_GLITCH_FIL_DELAY_50_US              0x00
#define DIGIIN2_GLITCH_FIL_DELAY_100_US             0x01
#define DIGIIN2_GLITCH_FIL_DELAY_400_US             0x02
#define DIGIIN2_GLITCH_FIL_DELAY_800_US             0x03
#define DIGIIN2_GLITCH_FIL_DELAY_1600_US            0x04
#define DIGIIN2_GLITCH_FIL_DELAY_3200_US            0x05
#define DIGIIN2_GLITCH_FIL_DELAY_12800_US           0x06
#define DIGIIN2_GLITCH_FIL_DELAY_20_MS              0x07

/**
 * @brief DIGI IN 2 GLOBLCFG register setting.
 * @details Specified setting for GLOBLCFG register of DIGI IN 2 Click driver.
 */
#define DIGIIN2_GPO_CFG_LED                         0x80
#define DIGIIN2_GPO_CFG_LEDINT                      0x00
#define DIGIIN2_LEDINT_CFG_GPO                      0x00
#define DIGIIN2_LEDINT_CFG_VMLOW                    0x40
#define DIGIIN2_LED9_ON                             0x00
#define DIGIIN2_LED9_OFF                            0x20
#define DIGIIN2_FSPICLEAR_READ                      0x10
#define DIGIIN2_FSPICLEAR_AUTO                      0x00
#define DIGIIN2_CLR_FILTER_ON                       0x08
#define DIGIIN2_CLR_FILTER_OFF                      0x00
#define DIGIIN2_REFDISHTCFG_DIS                     0x00
#define DIGIIN2_REFDISHTCFG_EN                      0x01

/**
 * @brief DIGI IN 2 LED register setting.
 * @details Specified setting for LED register of DIGI IN 2 Click driver.
 */
#define DIGIIN2_LED_1_MASK                          0x01
#define DIGIIN2_LED_2_MASK                          0x02
#define DIGIIN2_LED_3_MASK                          0x04
#define DIGIIN2_LED_4_MASK                          0x08
#define DIGIIN2_LED_5_MASK                          0x10
#define DIGIIN2_LED_6_MASK                          0x20
#define DIGIIN2_LED_7_MASK                          0x40
#define DIGIIN2_LED_8_MASK                          0x80

/**
 * @brief DIGI IN 2 FAULT2 register setting.
 * @details Specified setting for FAULT2 register of DIGI IN 2 Click driver.
 */
#define DIGIIN2_VAUV_UNDER_TRESHOLD                 0x10
#define DIGIIN2_SPI8_CLK_ERROR                      0x08
#define DIGIIN2_OTSHDN2_ERROR                       0x04
#define DIGIIN2_RFDIO_ERROR                         0x02
#define DIGIIN2_RFDIS_ERROR                         0x01

/**
 * @brief DIGI IN 2 F2MASK register setting.
 * @details Specified setting for F2MASK register of DIGI IN 2 Click driver.
 */
#define DIGIIN2_VAUV_UNDER_TRESHOLD_MASK            0x10
#define DIGIIN2_SPI8_CLK_ERROR_MASK                 0x08
#define DIGIIN2_OTSHDN2_ERROR_MASK                  0x04
#define DIGIIN2_RFDIO_ERROR_MASK                    0x02
#define DIGIIN2_RFDIS_ERROR_MASK                    0x01

/**
 * @brief DIGI IN 2 pin state setting.
 * @details Specified setting for pin state of DIGI IN 2 Click driver.
 */
#define DIGIIN2_PIN_STATE_HIGH                      0x01
#define DIGIIN2_PIN_STATE_LOW                       0x00

/**
 * @brief DIGI IN 2 CRC Settings setting.
 * @details Specified setting for CRC Settings of DIGI IN 2 Click driver.
 */
#define DIGIIN2_CRC_ENABLED                         0x01
#define DIGIIN2_CRC_DISABLED                        0x00

/**
 * @brief DIGI IN 2 chip address setting.
 * @details Specified setting for chip address of DIGI IN 2 Click driver.
 */
#define DIGIIN2_CHIP_ADDRESS_00                     0x00
#define DIGIIN2_CHIP_ADDRESS_01                     0x40
#define DIGIIN2_CHIP_ADDRESS_10                     0x80
#define DIGIIN2_CHIP_ADDRESS_11                     0xC0



/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b digiin2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define DIGIIN2_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define DIGIIN2_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // digiin2_set

/**
 * @defgroup digiin2_map DIGI IN 2 MikroBUS Map
 * @brief MikroBUS pin mapping of DIGI IN 2 Click driver.
 */

/**
 * @addtogroup digiin2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DIGI IN 2 Click to the selected MikroBUS.
 */
#define DIGIIN2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rdy  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.ltc  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.flt  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // digiin2_map
/*! @} */ // digiin2

/**
 * @brief DIGI IN 2 Click context object.
 * @details Context object definition of DIGI IN 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t ltc;          /**< Data latching pin. */

    // Input pins
    digital_in_t rdy;           /**< Ready pin. */
    digital_in_t flt;           /**< Fault indicator pin. */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

    uint8_t device_address;     /**< Chip device Address. */
    uint8_t crc_en;             /**< CRC enable selection. */

} digiin2_t;

/**
 * @brief DIGI IN 2 Click configuration object.
 * @details Configuration object definition of DIGI IN 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rdy;             /**< Ready pin. */
    pin_name_t ltc;             /**< Data latching pin. */
    pin_name_t flt;             /**< Fault indicator pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} digiin2_cfg_t;

/**
 * @brief DIGI IN 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DIGIIN2_OK = 0,
    DIGIIN2_ERROR = -1

} digiin2_return_value_t;

/*!
 * @addtogroup digiin2 DIGI IN 2 Click Driver
 * @brief API for configuring and manipulating DIGI IN 2 Click driver.
 * @{
 */

/**
 * @brief DIGI IN 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #digiin2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void digiin2_cfg_setup ( digiin2_cfg_t *cfg );

/**
 * @brief DIGI IN 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #digiin2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #digiin2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digiin2_init ( digiin2_t *ctx, digiin2_cfg_t *cfg );

/**
 * @brief DIGI IN 2 default configuration function.
 * @details This function executes a default configuration of DIGI IN 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #digiin2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t digiin2_default_cfg ( digiin2_t *ctx );

/**
 * @brief DIGI IN 2 set device address function.
 * @details This function is used to set device address.
 * @param[in] ctx : Click context object.
 * See #digiin2_t object definition for detailed explanation.
 * @param[in] device_address : Selected device address.
 * @return Nothing.
 * @note None.
 */
void digiin2_set_dev_address ( digiin2_t *ctx, uint8_t device_address );

/**
 * @brief DIGI IN 2 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #digiin2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digiin2_generic_write ( digiin2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief DIGI IN 2 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #digiin2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digiin2_generic_read ( digiin2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief DIGI IN 2 set LTC pin function.
 * @details This function is used to set state of the LTC pin.
 * @param[in] ctx : Click context object.
 * See #digiin2_t object definition for detailed explanation.
 * @param[in] pin_state : State of the LTC pin.
 * @return Nothing.
 * @note None.
 */
void digiin2_set_ltc_pin ( digiin2_t *ctx, uint8_t pin_state );

/**
 * @brief DIGI IN 2 get RDY pin state function.
 * @details This function is used to get state of the RDY pin.
 * @param[in] ctx : Click context object.
 * See #digiin2_t object definition for detailed explanation.
 * @return State of the RDY pin.
 * @note None.
 */
uint8_t digiin2_get_rdy_pin ( digiin2_t *ctx );

/**
 * @brief DIGI IN 2 get FLT pin state function.
 * @details This function is used to get state of the FLT pin.
 * @param[in] ctx : Click context object.
 * See #digiin2_t object definition for detailed explanation.
 * @return State of the FLT pin.
 * @note None.
 */
uint8_t digiin2_get_flt_pin ( digiin2_t *ctx );

/**
 * @brief DIGI IN 2 register write function.
 * @details This function is used to write data into the selected register 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #digiin2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digiin2_write_reg ( digiin2_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief DIGI IN 2 register reading function.
 * @details This function reads a data byte from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #digiin2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digiin2_read_reg ( digiin2_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief DIGI IN 2 channel counter reading function.
 * @details This function counter data from
 * the selected channel by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #digiin2_t object definition for detailed explanation.
 * @param[in] channel_sel : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digiin2_read_ch_counter ( digiin2_t *ctx, uint8_t channel_sel, uint16_t *data_out );

/**
 * @brief DIGI IN 2 send latch pulse function.
 * @details This function is used to generate LATCH pulse for capturing channel data.
 * @param[in] ctx : Click context object.
 * See #digiin2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void digiin2_pulse_latch ( digiin2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // DIGIIN2_H

/*! @} */ // digiin2

// ------------------------------------------------------------------------ END
