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
 * @file solenoiddriver.h
 * @brief This file contains API for Solenoid Driver Click Driver.
 */

#ifndef SOLENOIDDRIVER_H
#define SOLENOIDDRIVER_H

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
 * @addtogroup solenoiddriver Solenoid Driver Click Driver
 * @brief API for configuring and manipulating Solenoid Driver Click driver.
 * @{
 */

/**
 * @defgroup solenoiddriver_reg Solenoid Driver Registers List
 * @brief List of registers of Solenoid Driver Click driver.
 */

/**
 * @addtogroup solenoiddriver_reg
 * @{
 */

/**
 * @brief Solenoid Driver register list.
 * @details Specified register list of Solenoid Driver Click driver.
 */
#define SOLENOIDDRIVER_REG_OUT_CTRL                 0x00
#define SOLENOIDDRIVER_REG_STANDARD_DIAGNOSIS       0x01
#define SOLENOIDDRIVER_REG_IN0_MAP                  0x04
#define SOLENOIDDRIVER_REG_IN1_MAP                  0x05
#define SOLENOIDDRIVER_REG_IN_STATUS_MONITOR        0x06
#define SOLENOIDDRIVER_REG_OPEN_LOAD_CURRENT_CTRL   0x08
#define SOLENOIDDRIVER_REG_OUT_STATUS_MONITOR       0x09
#define SOLENOIDDRIVER_REG_CONFIG                   0x0C
#define SOLENOIDDRIVER_REG_OUT_CLEAR_LATCH          0x0D
#define SOLENOIDDRIVER_REG_CONFIG2                  0x28

/*! @} */ // solenoiddriver_reg

/**
 * @defgroup solenoiddriver_set Solenoid Driver Registers Settings
 * @brief Settings for registers of Solenoid Driver Click driver.
 */

/**
 * @addtogroup solenoiddriver_set
 * @{
 */

/**
 * @brief Solenoid Driver STANDARD_DIAGNOSIS register setting.
 * @details Specified setting for STANDARD_DIAGNOSIS register of Solenoid Driver Click driver.
 */
#define SOLENOIDDRIVER_DIAG_UVRVM                   0x4000
#define SOLENOIDDRIVER_DIAG_MODE_LIMP_HOME          0x0800
#define SOLENOIDDRIVER_DIAG_MODE_ACTIVE             0x1000
#define SOLENOIDDRIVER_DIAG_MODE_IDLE               0x1800
#define SOLENOIDDRIVER_DIAG_MODE_MASK               0x1800
#define SOLENOIDDRIVER_DIAG_TER                     0x0400
#define SOLENOIDDRIVER_DIAG_OLOFF                   0x0100
#define SOLENOIDDRIVER_DIAG_ERR_OUT3                0x0008
#define SOLENOIDDRIVER_DIAG_ERR_OUT2                0x0004
#define SOLENOIDDRIVER_DIAG_ERR_OUT1                0x0002
#define SOLENOIDDRIVER_DIAG_ERR_OUT0                0x0001

/**
 * @brief Solenoid Driver OUT_CTRL register setting.
 * @details Specified setting for OUT_CTRL register of Solenoid Driver Click driver.
 */
#define SOLENOIDDRIVER_OUT_CTRL_EN3                 0x08
#define SOLENOIDDRIVER_OUT_CTRL_EN2                 0x04
#define SOLENOIDDRIVER_OUT_CTRL_EN1                 0x02
#define SOLENOIDDRIVER_OUT_CTRL_EN0                 0x01

/**
 * @brief Solenoid Driver IN0_MAP register setting.
 * @details Specified setting for IN0_MAP register of Solenoid Driver Click driver.
 */
#define SOLENOIDDRIVER_IN0_MAP_OUT3                 0x08
#define SOLENOIDDRIVER_IN0_MAP_OUT2                 0x04
#define SOLENOIDDRIVER_IN0_MAP_OUT1                 0x02
#define SOLENOIDDRIVER_IN0_MAP_OUT0                 0x01
#define SOLENOIDDRIVER_IN0_MAP_NONE                 0x00

/**
 * @brief Solenoid Driver IN1_MAP register setting.
 * @details Specified setting for IN1_MAP register of Solenoid Driver Click driver.
 */
#define SOLENOIDDRIVER_IN1_MAP_OUT3                 0x08
#define SOLENOIDDRIVER_IN1_MAP_OUT2                 0x04
#define SOLENOIDDRIVER_IN1_MAP_OUT1                 0x02
#define SOLENOIDDRIVER_IN1_MAP_OUT0                 0x01
#define SOLENOIDDRIVER_IN1_MAP_NONE                 0x00

/**
 * @brief Solenoid Driver IN_STATUS_MONITOR register setting.
 * @details Specified setting for IN_STATUS_MONITOR register of Solenoid Driver Click driver.
 */
#define SOLENOIDDRIVER_IN_STATUS_MONITOR_TER        0x80
#define SOLENOIDDRIVER_IN_STATUS_MONITOR_INST1      0x02
#define SOLENOIDDRIVER_IN_STATUS_MONITOR_INST0      0x01

/**
 * @brief Solenoid Driver OPEN_LOAD_CURRENT_CTRL register setting.
 * @details Specified setting for OPEN_LOAD_CURRENT_CTRL register of Solenoid Driver Click driver.
 */
#define SOLENOIDDRIVER_OPEN_LOAD_CURRENT_CTRL_IOL3  0x08
#define SOLENOIDDRIVER_OPEN_LOAD_CURRENT_CTRL_IOL2  0x04
#define SOLENOIDDRIVER_OPEN_LOAD_CURRENT_CTRL_IOL1  0x02
#define SOLENOIDDRIVER_OPEN_LOAD_CURRENT_CTRL_IOL0  0x01

/**
 * @brief Solenoid Driver OUT_STATUS_MONITOR register setting.
 * @details Specified setting for OUT_STATUS_MONITOR register of Solenoid Driver Click driver.
 */
#define SOLENOIDDRIVER_OUT_STATUS_MONITOR_OSM3      0x08
#define SOLENOIDDRIVER_OUT_STATUS_MONITOR_OSM2      0x04
#define SOLENOIDDRIVER_OUT_STATUS_MONITOR_OSM1      0x02
#define SOLENOIDDRIVER_OUT_STATUS_MONITOR_OSM0      0x01

/**
 * @brief Solenoid Driver CONFIG register setting.
 * @details Specified setting for CONFIG register of Solenoid Driver Click driver.
 */
#define SOLENOIDDRIVER_CONFIG_ACT                   0x80
#define SOLENOIDDRIVER_CONFIG_RST                   0x40
#define SOLENOIDDRIVER_CONFIG_DISOL                 0x20
#define SOLENOIDDRIVER_CONFIG_OCP                   0x10
#define SOLENOIDDRIVER_CONFIG_PAR1                  0x02
#define SOLENOIDDRIVER_CONFIG_PAR0                  0x01

/**
 * @brief Solenoid Driver OUT_CLEAR_LATCH register setting.
 * @details Specified setting for OUT_CLEAR_LATCH register of Solenoid Driver Click driver.
 */
#define SOLENOIDDRIVER_OUT_CLEAR_LATCH_CLR3         0x08
#define SOLENOIDDRIVER_OUT_CLEAR_LATCH_CLR2         0x04
#define SOLENOIDDRIVER_OUT_CLEAR_LATCH_CLR1         0x02
#define SOLENOIDDRIVER_OUT_CLEAR_LATCH_CLR0         0x01

/**
 * @brief Solenoid Driver CONFIG2 register setting.
 * @details Specified setting for CONFIG2 register of Solenoid Driver Click driver.
 */
#define SOLENOIDDRIVER_CONFIG2_LOCK_SET_LOCK        0xC0
#define SOLENOIDDRIVER_CONFIG2_LOCK_SET_UNLOCK      0x60
#define SOLENOIDDRIVER_CONFIG2_LOCK_MASK            0xE0
#define SOLENOIDDRIVER_CONFIG2_OTW                  0x04
#define SOLENOIDDRIVER_CONFIG2_SR_1_2V              0x00
#define SOLENOIDDRIVER_CONFIG2_SR_3V                0x01
#define SOLENOIDDRIVER_CONFIG2_SR_MASK              0x01

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b solenoiddriver_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define SOLENOIDDRIVER_SET_DATA_SAMPLE_EDGE         SET_SPI_DATA_SAMPLE_EDGE
#define SOLENOIDDRIVER_SET_DATA_SAMPLE_MIDDLE       SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // solenoiddriver_set

/**
 * @defgroup solenoiddriver_map Solenoid Driver MikroBUS Map
 * @brief MikroBUS pin mapping of Solenoid Driver Click driver.
 */

/**
 * @addtogroup solenoiddriver_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Solenoid Driver Click to the selected MikroBUS.
 */
#define SOLENOIDDRIVER_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.in1   = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.sleep = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.in0   = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // solenoiddriver_map
/*! @} */ // solenoiddriver

/**
 * @brief Solenoid Driver Click context object.
 * @details Context object definition of Solenoid Driver Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t in1;          /**< Input 1 pin. */
    digital_out_t sleep;        /**< Sleep pin (active low). */
    digital_out_t in0;          /**< Input 0 pin. */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t chip_select;     /**< Chip select pin descriptor (used for SPI driver). */

    uint16_t diagnosis;         /**< Diagnosis word, updates on register write or standard diagnosis register read. */

} solenoiddriver_t;

/**
 * @brief Solenoid Driver Click configuration object.
 * @details Configuration object definition of Solenoid Driver Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t in1;             /**< Input 1 pin. */
    pin_name_t sleep;           /**< Sleep pin (active low). */
    pin_name_t in0;             /**< Input 0 pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} solenoiddriver_cfg_t;

/**
 * @brief Solenoid Driver Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SOLENOIDDRIVER_OK = 0,
    SOLENOIDDRIVER_ERROR = -1

} solenoiddriver_return_value_t;

/*!
 * @addtogroup solenoiddriver Solenoid Driver Click Driver
 * @brief API for configuring and manipulating Solenoid Driver Click driver.
 * @{
 */

/**
 * @brief Solenoid Driver configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #solenoiddriver_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void solenoiddriver_cfg_setup ( solenoiddriver_cfg_t *cfg );

/**
 * @brief Solenoid Driver initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #solenoiddriver_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #solenoiddriver_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solenoiddriver_init ( solenoiddriver_t *ctx, solenoiddriver_cfg_t *cfg );

/**
 * @brief Solenoid Driver default configuration function.
 * @details This function executes a default configuration of Solenoid Driver
 * Click board.
 * @param[in] ctx : Click context object.
 * See #solenoiddriver_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t solenoiddriver_default_cfg ( solenoiddriver_t *ctx );

/**
 * @brief Solenoid Driver write register function.
 * @details This function writes a single byte to the selected register of the Solenoid Driver Click board.
 * @param[in] ctx : Click context object.
 * See #solenoiddriver_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t solenoiddriver_write_reg ( solenoiddriver_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Solenoid Driver read register function.
 * @details This function reads a single byte from the selected register of the Solenoid Driver Click board.
 * @param[in] ctx : Click context object.
 * See #solenoiddriver_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to memory to store read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t solenoiddriver_read_reg ( solenoiddriver_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Solenoid Driver set IN0 pin function.
 * @details This function sets the logic state of the IN0 pin.
 * @param[in] ctx : Click context object.
 * See #solenoiddriver_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void solenoiddriver_set_in0_pin ( solenoiddriver_t *ctx, uint8_t state );

/**
 * @brief Solenoid Driver set IN1 pin function.
 * @details This function sets the logic state of the IN1 pin.
 * @param[in] ctx : Click context object.
 * See #solenoiddriver_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void solenoiddriver_set_in1_pin ( solenoiddriver_t *ctx, uint8_t state );

/**
 * @brief Solenoid Driver set SLEEP pin function.
 * @details This function sets the logic state of the SLEEP pin.
 * @param[in] ctx : Click context object.
 * See #solenoiddriver_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void solenoiddriver_set_sleep_pin ( solenoiddriver_t *ctx, uint8_t state );

/**
 * @brief Solenoid Driver enter sleep mode function.
 * @details This function sets all control pins to LOW and enters the device into sleep mode.
 * @param[in] ctx : Click context object.
 * See #solenoiddriver_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void solenoiddriver_enter_sleep ( solenoiddriver_t *ctx );

/**
 * @brief Solenoid Driver exit sleep mode function.
 * @details This function exits the device from sleep mode and enables it.
 * @param[in] ctx : Click context object.
 * See #solenoiddriver_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void solenoiddriver_exit_sleep ( solenoiddriver_t *ctx );

/**
 * @brief Solenoid Driver device reset function.
 * @details This function performs a software reset of the Solenoid Driver Click board.
 * @param[in] ctx : Click context object.
 * See #solenoiddriver_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t solenoiddriver_reset_device ( solenoiddriver_t *ctx );

/**
 * @brief Solenoid Driver lock settings function.
 * @details This function locks the configuration registers to prevent further changes.
 * @param[in] ctx : Click context object.
 * See #solenoiddriver_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t solenoiddriver_lock_settings ( solenoiddriver_t *ctx );

/**
 * @brief Solenoid Driver unlock settings function.
 * @details This function unlocks the configuration registers to allow changes.
 * @param[in] ctx : Click context object.
 * See #solenoiddriver_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t solenoiddriver_unlock_settings ( solenoiddriver_t *ctx );

/**
 * @brief Solenoid Driver clear latch outputs function.
 * @details This function clears all latch output states via register write.
 * @param[in] ctx : Click context object.
 * See #solenoiddriver_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t solenoiddriver_clear_latch ( solenoiddriver_t *ctx );

/**
 * @brief Solenoid Driver set output function.
 * @details This function sets the desired output control configuration to the output control register.
 * @param[in] ctx : Click context object.
 * See #solenoiddriver_t object definition for detailed explanation.
 * @param[in] out_ctrl : Output control data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t solenoiddriver_set_output ( solenoiddriver_t *ctx, uint8_t out_ctrl );

#ifdef __cplusplus
}
#endif
#endif // SOLENOIDDRIVER_H

/*! @} */ // solenoiddriver

// ------------------------------------------------------------------------ END
