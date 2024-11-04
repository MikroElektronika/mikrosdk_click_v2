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
 * @file digiin.h
 * @brief This file contains API for DIGI IN Click Driver.
 */

#ifndef DIGIIN_H
#define DIGIIN_H

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
 * @addtogroup digiin DIGI IN Click Driver
 * @brief API for configuring and manipulating DIGI IN Click driver.
 * @{
 */

/**
 * @defgroup digiin_reg DIGI IN Registers List
 * @brief List of registers of DIGI IN Click driver.
 */

/**
 * @addtogroup digiin_reg
 * @{
 */

/**
 * @brief DIGI IN description register.
 * @details Specified register for description of DIGI IN Click driver.
 */
#define DIGIIN_REG_DISTATE                      0x02
#define DIGIIN_REG_FAULT1                       0x04
#define DIGIIN_REG_FILTER_IN1                   0x06
#define DIGIIN_REG_FILTER_IN2                   0x08
#define DIGIIN_REG_FILTER_IN3                   0x0A
#define DIGIIN_REG_FILTER_IN4                   0x0C
#define DIGIIN_REG_FILTER_IN5                   0x0E
#define DIGIIN_REG_FILTER_IN6                   0x10
#define DIGIIN_REG_FILTER_IN7                   0x12
#define DIGIIN_REG_FILTER_IN8                   0x14
#define DIGIIN_REG_CONFIGURATION                0x18
#define DIGIIN_REG_INOPUT_ENABLE                0x1A
#define DIGIIN_REG_FAULT2                       0x1C
#define DIGIIN_REG_FAULT2_ENABLE                0x1E
#define DIGIIN_REG_GPO                          0x22
#define DIGIIN_REG_FAULT1_ENABLE                0x24
#define DIGIIN_REG_NO_OP                        0x26

/*! @} */ // digiin_reg

/**
 * @defgroup digiin_set DIGI IN Registers Settings
 * @brief Settings for registers of DIGI IN Click driver.
 */

/**
 * @addtogroup digiin_set
 * @{
 */

/**
 * @brief DIGI IN description setting.
 * @details Specified setting for description of DIGI IN Click driver.
 */
#define DIGIIN_M0_0                             0x00
#define DIGIIN_M0_1                             0x01

/**
 * @brief DIGI IN FAULT1 register setting.
 * @details Specified setting for FAULT1 register of DIGI IN Click driver.
 */
#define DIGIIN_CRC_ERROR_FLAG                   0x80
#define DIGIIN_POR                              0x40
#define DIGIIN_FAULT2                           0x20
#define DIGIIN_TERMAL_SHUTDOWN                  0x10
#define DIGIIN_TEMPERATURE_ALARM                0x08
#define DIGIIN_V24_UNDERVOLTAGE                 0x04
#define DIGIIN_VM_VOLTAGE_LOW                   0x02

/**
 * @brief DIGI IN FAULT2 register setting.
 * @details Specified setting for FAULT2 register of DIGI IN Click driver.
 */
#define DIGIIN_SPI8_CLK_ERROR                   0x10
#define DIGIIN_OTSHDN_ERROR                     0x08

/**
 * @brief DIGI IN FAULT1_ENABLE register setting.
 * @details Specified setting for FAULT1_ENABLE register of DIGI IN Click driver.
 */
#define DIGIIN_CRC_ERROR_FLAG_MASK              0x80
#define DIGIIN_POR_MASK                         0x40
#define DIGIIN_POR_CLEAR_MASK                   0x00
#define DIGIIN_FAULT2_MASK                      0x20
#define DIGIIN_TERMAL_SHUTDOWN_MASK             0x10
#define DIGIIN_TEMPERATURE_ALARM_MASK           0x08
#define DIGIIN_V24_UNDERVOLTAGE_MASK            0x04
#define DIGIIN_VM_VOLTAGE_LOW_MASK              0x02

/**
 * @brief DIGI IN FAULT2_ENABLE register setting.
 * @details Specified setting for FAULT2_ENABLE register of DIGI IN Click driver.
 */
#define DIGIIN_SPI8_CLK_ERROR_MASK              0x10
#define DIGIIN_OTSHDN_ERROR_MASK                0x08

/**
 * @brief DIGI IN GPO register setting.
 * @details Specified setting for GPO register of DIGI IN Click driver.
 */
#define DIGIIN_FAULT_STICKY                     0x80
#define DIGIIN_FAULT_NOT_STICKY                 0x00

/**
 * @brief DIGI IN DISTATE register setting.
 * @details Specified setting for DISTATE register of DIGI IN Click driver.
 */
#define DIGIIN_CHANNEL_NONE_MASK                0x00
#define DIGIIN_CHANNEL_1_MASK                   0x01
#define DIGIIN_CHANNEL_2_MASK                   0x02
#define DIGIIN_CHANNEL_3_MASK                   0x04
#define DIGIIN_CHANNEL_4_MASK                   0x08
#define DIGIIN_CHANNEL_5_MASK                   0x10
#define DIGIIN_CHANNEL_6_MASK                   0x20
#define DIGIIN_CHANNEL_7_MASK                   0x40
#define DIGIIN_CHANNEL_8_MASK                   0x80
#define DIGIIN_CHANNEL_ALL_MASK                 0xFF

/**
 * @brief DIGI IN FLT register setting.
 * @details Specified setting for FLT register of DIGI IN Click driver.
 */
#define DIGIIN_DELAY_50US                       0x00
#define DIGIIN_DELAY_100US                      0x01
#define DIGIIN_DELAY_400US                      0x02
#define DIGIIN_DELAY_800US                      0x03
#define DIGIIN_DELAY_1600US                     0x04
#define DIGIIN_DELAY_3000US                     0x05
#define DIGIIN_DELAY_12MS8                      0x06
#define DIGIIN_DELAY_20MS                       0x07
#define DIGIIN_FILTER_BYPASSED                  0x08

/**
 * @brief DIGI IN pin state setting.
 * @details Specified setting for pin state of DIGI IN Click driver.
 */
#define DIGIIN_PIN_STATE_HIGH                   0x01
#define DIGIIN_PIN_STATE_LOW                    0x00

/**
 * @brief DIGI IN SPI write mask setting.
 * @details Specified setting for SPI write mask of DIGI IN Click driver.
 */
#define DIGIIN_SPI_WRITE_MASK                   0x80

/**
 * @brief DIGI IN CRC mask setting.
 * @details Specified setting for CRC mask of DIGI IN Click driver.
 */
#define DIGIIN_CRC_MASK                         0x1F

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b digiin_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define DIGIIN_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define DIGIIN_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // digiin_set

/**
 * @defgroup digiin_map DIGI IN MikroBUS Map
 * @brief MikroBUS pin mapping of DIGI IN Click driver.
 */

/**
 * @addtogroup digiin_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DIGI IN Click to the selected MikroBUS.
 */
#define DIGIIN_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rdy = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.ltc = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // digiin_map
/*! @} */ // digiin

/**
 * @brief DIGI IN Click context object.
 * @details Context object definition of DIGI IN Click driver.
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

    uint8_t crc_en;             /**< CRC enable selection. */

} digiin_t;

/**
 * @brief DIGI IN Click configuration object.
 * @details Configuration object definition of DIGI IN Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  rdy;            /**< Ready pin. */
    pin_name_t ltc;             /**< Data latching pin. */
    pin_name_t flt;             /**< Fault indicator pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} digiin_cfg_t;

/**
 * @brief DIGI IN Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DIGIIN_OK = 0,
    DIGIIN_ERROR = -1

} digiin_return_value_t;

/*!
 * @addtogroup digiin DIGI IN Click Driver
 * @brief API for configuring and manipulating DIGI IN Click driver.
 * @{
 */

/**
 * @brief DIGI IN configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #digiin_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void digiin_cfg_setup ( digiin_cfg_t *cfg );

/**
 * @brief DIGI IN initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #digiin_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #digiin_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digiin_init ( digiin_t *ctx, digiin_cfg_t *cfg );

/**
 * @brief DIGI IN default configuration function.
 * @details This function executes a default configuration of DIGI IN
 * Click board.
 * @param[in] ctx : Click context object.
 * See #digiin_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t digiin_default_cfg ( digiin_t *ctx );

/**
 * @brief DIGI IN data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #digiin_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digiin_generic_write ( digiin_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief DIGI IN data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #digiin_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digiin_generic_read ( digiin_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief DIGI IN set LTC pin function.
 * @details This function is used to set state of the LTC pin.
 * @param[in] ctx : Click context object.
 * See #digiin_t object definition for detailed explanation.
 * @param[in] pin_state : State of the LTC pin.
 * @return Nothing.
 * @note None.
 */
void digiin_set_ltc_pin ( digiin_t *ctx, uint8_t pin_state );

/**
 * @brief DIGI IN get RDY pin state function.
 * @details This function is used to get state of the RDY pin.
 * @param[in] ctx : Click context object.
 * See #digiin_t object definition for detailed explanation.
 * @return State of the RDY pin.
 * @note None.
 */
uint8_t digiin_get_rdy_pin ( digiin_t *ctx );

/**
 * @brief DIGI IN get FLT pin state function.
 * @details This function is used to get state of the FLT pin.
 * @param[in] ctx : Click context object.
 * See #digiin_t object definition for detailed explanation.
 * @return State of the FLT pin.
 * @note None.
 */
uint8_t digiin_get_flt_pin ( digiin_t *ctx );

/**
 * @brief DIGI IN register write function.
 * @details This function is used to write data into the selected register 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #digiin_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digiin_write_reg ( digiin_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief DIGI IN register reading function.
 * @details This function reads a data byte from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #digiin_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digiin_read_reg ( digiin_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief DIGI IN send latch pulse function.
 * @details This function is used to generate LATCH pulse for capturing channel data.
 * @param[in] ctx : Click context object.
 * See #digiin_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void digiin_pulse_latch ( digiin_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // DIGIIN_H

/*! @} */ // digiin

// ------------------------------------------------------------------------ END
