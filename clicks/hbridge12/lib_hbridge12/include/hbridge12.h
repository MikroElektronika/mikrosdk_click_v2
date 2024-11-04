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
 * @file hbridge12.h
 * @brief This file contains API for H-Bridge 12 Click Driver.
 */

#ifndef HBRIDGE12_H
#define HBRIDGE12_H

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
 * @addtogroup hbridge12 H-Bridge 12 Click Driver
 * @brief API for configuring and manipulating H-Bridge 12 Click driver.
 * @{
 */

/**
 * @defgroup hbridge12_reg H-Bridge 12 Registers List
 * @brief List of registers of H-Bridge 12 Click driver.
 */

/**
 * @addtogroup hbridge12_reg
 * @{
 */

/**
 * @brief H-Bridge 12 description register.
 * @details Specified register for description of H-Bridge 12 Click driver.
 */
#define HBRIDGE12_ADDR_AB                       0x00
#define HBRIDGE12_ADDR_CD                       0x01

/*! @} */ // hbridge12_reg

/**
 * @defgroup hbridge12_set H-Bridge 12 Registers Settings
 * @brief Settings for registers of H-Bridge 12 Click driver.
 */

/**
 * @addtogroup hbridge12_set
 * @{
 */

/**
 * @brief H-Bridge 12 description setting.
 * @details Specified setting for description of H-Bridge 12 Click driver.
 */
#define HBRIDGE12_CURRENT_SCALE_20_PER          0x00
#define HBRIDGE12_CURRENT_SCALE_38_PER          0x04
#define HBRIDGE12_CURRENT_SCALE_56_PER          0x02
#define HBRIDGE12_CURRENT_SCALE_71_PER          0x06
#define HBRIDGE12_CURRENT_SCALE_83_PER          0x01
#define HBRIDGE12_CURRENT_SCALE_92_PER          0x05
#define HBRIDGE12_CURRENT_SCALE_98_PER          0x03
#define HBRIDGE12_CURRENT_SCALE_100_PER         0x07

/**
 * @brief H-Bridge 12 phase setting.
 * @details Specified setting for output phase of H-Bridge 12 Click driver.
 */
#define HBRIDGE12_PHASE_OUT1_H_OUT2_L           0x01
#define HBRIDGE12_PHASE_OUT1_L_OUT2_H           0x00

/**
 * @brief H-Bridge 12 bridge enable setting.
 * @details Specified setting for enabling bridge of H-Bridge 12 Click driver.
 */
#define HBRIDGE12_ENABLE_BRIDGE_OUTPUT          0x01
#define HBRIDGE12_DISABLE_BRIDGE_OUTPUT         0x00

/**
 * @brief H-Bridge 12 bridge selection setting.
 * @details Specified setting for selection of bridge of H-Bridge 12 Click driver.
 */
#define HBRIDGE12_AB_BRIDGE_SEL                 0x00
#define HBRIDGE12_CD_BRIDGE_SEL                 0x01

/**
 * @brief H-Bridge 12 pin setting.
 * @details Specified setting for pin state of H-Bridge 12 Click driver.
 */
#define HBRIDGE12_PIN_STATE_LOW                 0x00
#define HBRIDGE12_PIN_STATE_HIGH                0x01

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b hbridge12_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define HBRIDGE12_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define HBRIDGE12_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // hbridge12_set

/**
 * @defgroup hbridge12_map H-Bridge 12 MikroBUS Map
 * @brief MikroBUS pin mapping of H-Bridge 12 Click driver.
 */

/**
 * @addtogroup hbridge12_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of H-Bridge 12 Click to the selected MikroBUS.
 */
#define HBRIDGE12_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.slp = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.stb = MIKROBUS( mikrobus, MIKROBUS_AN )

/*! @} */ // hbridge12_map
/*! @} */ // hbridge12

/**
 * @brief H-Bridge 12 Click configuration structure.
 * @details Configuration structure definition of H-Bridge 12 Click driver.
 */
typedef struct
{
    uint8_t addr;           /**< Address of the selected bridge. */
    uint8_t ch1_en;         /**< Chanel 1 enable. */
    uint8_t ch1_phase;      /**< Chanel 1 phase. */
    uint8_t ch1_cur_scale;  /**< Chanel 1 current scale. */
    uint8_t ch1_decay;      /**< Chanel 1 decay. */
    uint8_t ch2_en;         /**< Chanel 2 enable. */
    uint8_t ch2_phase;      /**< Chanel 2 phase. */
    uint8_t ch2_cur_scale;  /**< Chanel 2 current scale. */
    uint8_t ch2_decay;      /**< Chanel 2 decay. */

} hbridge12_config_t;

/**
 * @brief H-Bridge 12 Click context object.
 * @details Context object definition of H-Bridge 12 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin. */
    digital_out_t slp;              /**< Sleep pin. */
    digital_out_t stb;              /**< Strobe pin. */
    
    // Configuration structures
    hbridge12_config_t ab_config_data;  /**< AB bridge configuration. */
    hbridge12_config_t cd_config_data;  /**< CD bridge configuration. */

    // Modules
    spi_master_t spi;               /**< SPI driver object. */

    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */

} hbridge12_t;

/**
 * @brief H-Bridge 12 Click configuration object.
 * @details Configuration object definition of H-Bridge 12 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rst;             /**< Reset pin. */
    pin_name_t slp;             /**< Sleep pin. */
    pin_name_t stb;             /**< Strobe pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} hbridge12_cfg_t;

/**
 * @brief H-Bridge 12 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HBRIDGE12_OK = 0,
    HBRIDGE12_ERROR = -1

} hbridge12_return_value_t;

/*!
 * @addtogroup hbridge12 H-Bridge 12 Click Driver
 * @brief API for configuring and manipulating H-Bridge 12 Click driver.
 * @{
 */

/**
 * @brief H-Bridge 12 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hbridge12_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hbridge12_cfg_setup ( hbridge12_cfg_t *cfg );

/**
 * @brief H-Bridge 12 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #hbridge12_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hbridge12_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge12_init ( hbridge12_t *ctx, hbridge12_cfg_t *cfg );

/**
 * @brief H-Bridge 12 default configuration function.
 * @details This function executes a default configuration of H-Bridge 12
 * Click board.
 * @param[in] ctx : Click context object.
 * See #hbridge12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t hbridge12_default_cfg ( hbridge12_t *ctx );

/**
 * @brief H-Bridge 12 set RST pin state function.
 * @details This function sets the seleccted state of the RST pin.
 * @param[in] cfg : Click configuration structure.
 * See #hbridge12_cfg_t object definition for detailed explanation.
 * @param[in] pin_state : State of the RST pin.
 * @return Nothing.
 * @note None.
 */
void hbridge12_set_rst ( hbridge12_t *ctx, uint8_t pin_state );

/**
 * @brief H-Bridge 12 set SLP pin state function.
 * @details This function sets the seleccted state of the SLP pin.
 * @param[in] cfg : Click configuration structure.
 * See #hbridge12_cfg_t object definition for detailed explanation.
 * @param[in] pin_state : State of the SLP pin.
 * @return Nothing.
 * @note None.
 */
void hbridge12_set_slp ( hbridge12_t *ctx, uint8_t pin_state );

/**
 * @brief H-Bridge 12 set STB pin state function.
 * @details This function sets the seleccted state of the STB pin.
 * @param[in] cfg : Click configuration structure.
 * See #hbridge12_cfg_t object definition for detailed explanation.
 * @param[in] pin_state : State of the STB pin.
 * @return Nothing.
 * @note None.
 */
void hbridge12_set_strobe ( hbridge12_t *ctx, uint8_t pin_state );

/**
 * @brief H-Bridge 12 generate strobe signal function.
 * @details This function is used to generate strobe signal to latch data into motor driver.
 * @param[out] cfg : Click configuration structure.
 * See #hbridge12_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void hbridge12_generate_strobe ( hbridge12_t *ctx );

/**
 * @brief H-Bridge 12 get settings function.
 * @details This function reads settings that are written into a register.
 * @param[in] cfg : Click configuration structure.
 * See #hbridge12_cfg_t object definition for detailed explanation.
 * @param[in] channel_sel : Selection between AB and CD channels.
 * @param[out] config_data : Written configuration data.
 * @return Nothing.
 * @note None.
 */
void hbridge12_get_settings ( hbridge12_t *ctx, uint8_t channel_sel, hbridge12_config_t *config_data );

/**
 * @brief H-Bridge 12 set settings function.
 * @details This function writes settings for configuration of H-Bridge 12
 * Click board into structure.
 * @param[in] cfg : Click configuration structure.
 * See #hbridge12_cfg_t object definition for detailed explanation.
 * @param[in] channel_sel : Selection between AB and CD channels.
 * @param[in] config_data : Written configuration data.
 * @return Nothing.
 * @note None.
 */
void hbridge12_set_settings ( hbridge12_t *ctx, uint8_t channel_sel, hbridge12_config_t config_data );


/**
 * @brief H-Bridge 12 write settings function.
 * @details This function writes settings for configuration of H-Bridge 12
 * Click board.
 * @param[in] cfg : Click configuration structure.
 * See #hbridge12_cfg_t object definition for detailed explanation.
 * @param[in] config_data : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge12_write_config ( hbridge12_t *ctx, hbridge12_config_t config_data );

/**
 * @brief H-Bridge 12 set current scale function.
 * @details This function writes the current scale configuration of the selected channel H-Bridge 12
 * Click board.
 * @param[in] cfg : Click configuration structure.
 * See #hbridge12_cfg_t object definition for detailed explanation.
 * @param[in] channel_sel : Selection between AB and CD channels.
 * @param[in] out1_curr_scale : Output 1 current scale.
 * @param[in] out2_curr_scale : Output 2 current scale.
 * @return Nothing.
 * @note None.
 */
void hbridge12_set_current_scale ( hbridge12_t *ctx, uint8_t channel_sel, uint8_t out1_curr_scale,
                                   uint8_t out2_curr_scale );

/**
 * @brief H-Bridge 12 set decay function.
 * @details This function writes the decay configuration of the selected channel H-Bridge 12
 * Click board.
 * @param[in] cfg : Click configuration structure.
 * See #hbridge12_cfg_t object definition for detailed explanation.
 * @param[in] channel_sel : Selection between AB and CD channels.
 * @param[in] out1_curr_scale : Output 1 decay.
 * @param[in] out2_curr_scale : Output 2 decay.
 * @return Nothing.
 * @note None.
 */
void hbridge12_set_decay ( hbridge12_t *ctx, uint8_t channel_sel, uint8_t out1_decay, 
                           uint8_t out2_decay );

/**
 * @brief H-Bridge 12 turn motor clockwise function.
 * @details This function writes the configuration to turn the motor in clockwise direction.
 * @param[in] cfg : Click configuration structure.
 * See #hbridge12_cfg_t object definition for detailed explanation.
 * @param[in] channel_sel : Selection between AB and CD channels.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge12_turn_clockwise ( hbridge12_t *ctx, uint8_t channel_sel );

/**
 * @brief H-Bridge 12 turn motor counterclockwise function.
 * @details This function writes the configuration to turn the motor in counterclockwise direction.
 * @param[in] cfg : Click configuration structure.
 * See #hbridge12_cfg_t object definition for detailed explanation.
 * @param[in] channel_sel : Selection between AB and CD channels.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge12_turn_counterclockwise ( hbridge12_t *ctx, uint8_t channel_sel );

/**
 * @brief H-Bridge 12 turn motor brake on function.
 * @details This function writes the configuration to turn the motor brake on.
 * @param[in] cfg : Click configuration structure.
 * See #hbridge12_cfg_t object definition for detailed explanation.
 * @param[in] channel_sel : Selection between AB and CD channels.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge12_turn_brake_on ( hbridge12_t *ctx, uint8_t channel_sel );

/**
 * @brief H-Bridge 12 set motor into freewheeling mode function.
 * @details This function writes the configuration to turn on freewheeling mode.
 * @param[in] cfg : Click configuration structure.
 * See #hbridge12_cfg_t object definition for detailed explanation.
 * @param[in] channel_sel : Selection between AB and CD channels.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge12_freewheeling_on ( hbridge12_t *ctx, uint8_t channel_sel );

#ifdef __cplusplus
}
#endif
#endif // HBRIDGE12_H

/*! @} */ // hbridge12

// ------------------------------------------------------------------------ END
