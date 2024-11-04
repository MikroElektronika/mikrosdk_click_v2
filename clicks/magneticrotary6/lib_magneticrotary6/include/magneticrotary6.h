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
 * @file magneticrotary6.h
 * @brief This file contains API for Magnetic Rotary 6 Click Driver.
 */

#ifndef MAGNETICROTARY6_H
#define MAGNETICROTARY6_H

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
 * @addtogroup magneticrotary6 Magnetic Rotary 6 Click Driver
 * @brief API for configuring and manipulating Magnetic Rotary 6 Click driver.
 * @{
 */

/**
 * @defgroup magneticrotary6_reg Magnetic Rotary 6 Registers List
 * @brief List of registers of Magnetic Rotary 6 Click driver.
 */

/**
 * @addtogroup magneticrotary6_reg
 * @{
 */

/**
 * @brief Magnetic Rotary 6 volatile registers list.
 * @details Specified list of volatile registers of Magnetic Rotary 6 Click driver.
 */
#define MAGNETICROTARY6_REG_NOP                 0x0000u
#define MAGNETICROTARY6_REG_ERRFL               0x0001u
#define MAGNETICROTARY6_REG_PROG                0x0003u
#define MAGNETICROTARY6_REG_DIA                 0x3FF5u
#define MAGNETICROTARY6_REG_AGC                 0x3FF9u
#define MAGNETICROTARY6_REG_SIN_DATA            0x3FFAu
#define MAGNETICROTARY6_REG_COS_DATA            0x3FFBu
#define MAGNETICROTARY6_REG_VEL                 0x3FFCu
#define MAGNETICROTARY6_REG_MAG                 0x3FFDu
#define MAGNETICROTARY6_REG_ANGLEUNC            0x3FFEu
#define MAGNETICROTARY6_REG_ANGLECOM            0x3FFFu
#define MAGNETICROTARY6_REG_ECC_CHECKSUM        0x00D1u

/**
 * @brief Magnetic Rotary 6 non-volatile registers list.
 * @details Specified list of non-volatile registers of Magnetic Rotary 6 Click driver.
 */
#define MAGNETICROTARY6_REG_DISABLE             0x0015u
#define MAGNETICROTARY6_REG_ZPOSM               0x0016u
#define MAGNETICROTARY6_REG_ZPOSL               0x0017u
#define MAGNETICROTARY6_REG_SETTINGS1           0x0018u
#define MAGNETICROTARY6_REG_SETTINGS2           0x0019u
#define MAGNETICROTARY6_REG_SETTINGS3           0x001Au
#define MAGNETICROTARY6_REG_ECC                 0x001Bu

/*! @} */ // magneticrotary6_reg

/**
 * @defgroup magneticrotary6_set Magnetic Rotary 6 Registers Settings
 * @brief Settings for registers of Magnetic Rotary 6 Click driver.
 */

/**
 * @addtogroup magneticrotary6_set
 * @{
 */

/**
 * @brief Magnetic Rotary 6 ERRFL register settings.
 * @details Specified settings for ERRFL register of Magnetic Rotary 6 Click driver.
 */
#define MAGNETICROTARY6_ERRFL_CORDIC_OF         0x0400u
#define MAGNETICROTARY6_ERRFL_OFF_COMP_NOT_FIN  0x0200u
#define MAGNETICROTARY6_ERRFL_BRKHALL           0x0100u
#define MAGNETICROTARY6_ERRFL_WDTST             0x0080u
#define MAGNETICROTARY6_ERRFL_CRC_ERROR         0x0040u
#define MAGNETICROTARY6_ERRFL_CMD_ERROR         0x0020u
#define MAGNETICROTARY6_ERRFL_FRAMING_ERROR     0x0010u
#define MAGNETICROTARY6_ERRFL_P2RAM_ERROR       0x0008u
#define MAGNETICROTARY6_ERRFL_P2RAM_WARNING     0x0004u
#define MAGNETICROTARY6_ERRFL_MAGHALF           0x0002u
#define MAGNETICROTARY6_ERRFL_AGC_WARNING       0x0001u

/**
 * @brief Magnetic Rotary 6 PROG register settings.
 * @details Specified settings for PROG register of Magnetic Rotary 6 Click driver.
 */
#define MAGNETICROTARY6_PROG_PROGVER            0x0040u
#define MAGNETICROTARY6_PROG_PROGOTP            0x0008u
#define MAGNETICROTARY6_PROG_OTPREF             0x0004u
#define MAGNETICROTARY6_PROG_PROGEN             0x0001u

/**
 * @brief Magnetic Rotary 6 DIA register settings.
 * @details Specified settings for DIA register of Magnetic Rotary 6 Click driver.
 */
#define MAGNETICROTARY6_DIA_SPI_CNT             0x1800u
#define MAGNETICROTARY6_DIA_FUSA_ERROR          0x0400u
#define MAGNETICROTARY6_DIA_AGC_FIN             0x0200u
#define MAGNETICROTARY6_DIA_OFF_COMP_FIN        0x0100u
#define MAGNETICROTARY6_DIA_SINOFF_FIN          0x0080u
#define MAGNETICROTARY6_DIA_COSOFF_FIN          0x0040u
#define MAGNETICROTARY6_DIA_MAGHALF_FLAG        0x0020u
#define MAGNETICROTARY6_DIA_COMP_H              0x0010u
#define MAGNETICROTARY6_DIA_COMP_L              0x0008u
#define MAGNETICROTARY6_DIA_CORDIC_OF           0x0004u
#define MAGNETICROTARY6_DIA_LOOPSFIN            0x0002u
#define MAGNETICROTARY6_DIA_VDD_MODE_5V         0x0001u
#define MAGNETICROTARY6_DIA_VDD_MODE_3V         0x0000u

/**
 * @brief Magnetic Rotary 6 DISABLE register settings.
 * @details Specified settings for DISABLE register of Magnetic Rotary 6 Click driver.
 */
#define MAGNETICROTARY6_DISABLE_FILTER_DISABLE  0x0040u
#define MAGNETICROTARY6_DISABLE_BRKHALL_SET     0x003Cu
#define MAGNETICROTARY6_DISABLE_ABI_OFF         0x0002u
#define MAGNETICROTARY6_DISABLE_UVW_OFF         0x0001u

/**
 * @brief Magnetic Rotary 6 ZPOSL register settings.
 * @details Specified settings for ZPOSL register of Magnetic Rotary 6 Click driver.
 */
#define MAGNETICROTARY6_ZPOSL_DIA2_EN           0x0080u
#define MAGNETICROTARY6_ZPOSL_DIA1_EN           0x0040u
#define MAGNETICROTARY6_ZPOSL_LSB               0x003Fu

/**
 * @brief Magnetic Rotary 6 SETTINGS1 register settings.
 * @details Specified settings for SETTINGS1 register of Magnetic Rotary 6 Click driver.
 */
#define MAGNETICROTARY6_SETTINGS1_DIA3_EN       0x0040u
#define MAGNETICROTARY6_SETTINGS1_K_MIN         0x0038u
#define MAGNETICROTARY6_SETTINGS1_K_MAX         0x0007u

/**
 * @brief Magnetic Rotary 6 SETTINGS2 register settings.
 * @details Specified settings for SETTINGS2 register of Magnetic Rotary 6 Click driver.
 */
#define MAGNETICROTARY6_SETTINGS2_PWMON         0x0080u
#define MAGNETICROTARY6_SETTINGS2_DATA_SELECT   0x0040u
#define MAGNETICROTARY6_SETTINGS2_ABI_DEC       0x0020u
#define MAGNETICROTARY6_SETTINGS2_DAECDIS       0x0010u
#define MAGNETICROTARY6_SETTINGS2_UVW_ABI       0x0008u
#define MAGNETICROTARY6_SETTINGS2_DIR_CW        0x0000u
#define MAGNETICROTARY6_SETTINGS2_DIR_CCW       0x0004u
#define MAGNETICROTARY6_SETTINGS2_DIR_MASK      0x0004u
#define MAGNETICROTARY6_SETTINGS2_NOISESET      0x0002u
#define MAGNETICROTARY6_SETTINGS2_IWIDTH        0x0001u

/**
 * @brief Magnetic Rotary 6 SETTINGS3 register settings.
 * @details Specified settings for SETTINGS3 register of Magnetic Rotary 6 Click driver.
 */
#define MAGNETICROTARY6_SETTINGS3_ABIRES_MASK   0x00E0u
#define MAGNETICROTARY6_SETTINGS3_HYS_MASK      0x0018u
#define MAGNETICROTARY6_SETTINGS3_UVWPP_1PP     0x0000u
#define MAGNETICROTARY6_SETTINGS3_UVWPP_2PP     0x0001u
#define MAGNETICROTARY6_SETTINGS3_UVWPP_3PP     0x0002u
#define MAGNETICROTARY6_SETTINGS3_UVWPP_4PP     0x0003u
#define MAGNETICROTARY6_SETTINGS3_UVWPP_5PP     0x0004u
#define MAGNETICROTARY6_SETTINGS3_UVWPP_6PP     0x0005u
#define MAGNETICROTARY6_SETTINGS3_UVWPP_7PP     0x0006u
#define MAGNETICROTARY6_SETTINGS3_UVWPP_MASK    0x0007u

/**
 * @brief Magnetic Rotary 6 ECC register settings.
 * @details Specified settings for ECC register of Magnetic Rotary 6 Click driver.
 */
#define MAGNETICROTARY6_ECC_EN                  0x0080u
#define MAGNETICROTARY6_ECC_CHSUM_MASK          0x007Fu

/**
 * @brief Magnetic Rotary 6 die selection values.
 * @details Specified die selection values of Magnetic Rotary 6 Click driver.
 */
#define MAGNETICROTARY6_DIE_BOTTOM              0
#define MAGNETICROTARY6_DIE_TOP                 1

/**
 * @brief Magnetic Rotary 6 angle calculation values.
 * @details Specified angle calculation values of Magnetic Rotary 6 Click driver.
 */
#define MAGNETICROTARY6_DATA_RESOLUTION         0x3FFFu
#define MAGNETICROTARY6_FULL_CIRCLE             360u

/**
 * @brief Magnetic Rotary 6 rotation direction settings.
 * @details Specified settings for rotation direction of Magnetic Rotary 6 Click driver.
 */
#define MAGNETICROTARY6_DIR_CW                  0
#define MAGNETICROTARY6_DIR_CCW                 1

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU.
 */
#define MAGNETICROTARY6_SET_DATA_SAMPLE_EDGE    SET_SPI_DATA_SAMPLE_EDGE
#define MAGNETICROTARY6_SET_DATA_SAMPLE_MIDDLE  SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // magneticrotary6_set

/**
 * @defgroup magneticrotary6_map Magnetic Rotary 6 MikroBUS Map
 * @brief MikroBUS pin mapping of Magnetic Rotary 6 Click driver.
 */

/**
 * @addtogroup magneticrotary6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Magnetic Rotary 6 Click to the selected MikroBUS.
 */
#define MAGNETICROTARY6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs_t = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.cs_b = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // magneticrotary6_map
/*! @} */ // magneticrotary6

/**
 * @brief Magnetic Rotary 6 Click context object.
 * @details Context object definition of Magnetic Rotary 6 Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   cs_t;          /**< Chip select pin for top die (used for SPI driver). */
    pin_name_t   cs_b;          /**< Chip select pin for bottom die (used for SPI driver). */

} magneticrotary6_t;

/**
 * @brief Magnetic Rotary 6 Click configuration object.
 * @details Configuration object definition of Magnetic Rotary 6 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;           /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;           /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;            /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs_t;           /**< Chip select pin for top die (used for SPI driver). */
    pin_name_t  cs_b;           /**< Chip select pin for bottom die (used for SPI driver). */

    // static variable
    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

} magneticrotary6_cfg_t;

/**
 * @brief Magnetic Rotary 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MAGNETICROTARY6_OK = 0,
    MAGNETICROTARY6_ERROR = -1

} magneticrotary6_return_value_t;

/*!
 * @addtogroup magneticrotary6 Magnetic Rotary 6 Click Driver
 * @brief API for configuring and manipulating Magnetic Rotary 6 Click driver.
 * @{
 */

/**
 * @brief Magnetic Rotary 6 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #magneticrotary6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void magneticrotary6_cfg_setup ( magneticrotary6_cfg_t *cfg );

/**
 * @brief Magnetic Rotary 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #magneticrotary6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #magneticrotary6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneticrotary6_init ( magneticrotary6_t *ctx, magneticrotary6_cfg_t *cfg );

/**
 * @brief Magnetic Rotary 6 default configuration function.
 * @details This function executes a default configuration of Magnetic Rotary 6
 * Click board.
 * @param[in] ctx : Click context object.
 * See #magneticrotary6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t magneticrotary6_default_cfg ( magneticrotary6_t *ctx );

/**
 * @brief Magnetic Rotary 6 write register function.
 * @details This function writes a desired data to the selected register of a desired sensor die
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #magneticrotary6_t object definition for detailed explanation.
 * @param[in] die_sel : Sensor die selection: 0 - Bottom die, 1 - Top die.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneticrotary6_write_register ( magneticrotary6_t *ctx, uint8_t die_sel, uint16_t reg, uint16_t data_in );

/**
 * @brief Magnetic Rotary 6 read register b function.
 * @details This function reads data from the selected register of a desired sensor die
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #magneticrotary6_t object definition for detailed explanation.
 * @param[in] die_sel : Sensor die selection: 0 - Bottom die, 1 - Top die.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneticrotary6_read_register ( magneticrotary6_t *ctx, uint8_t die_sel, uint16_t reg, uint16_t *data_out );

/**
 * @brief Magnetic Rotary 6 get angle function.
 * @details This function reads the absolute position raw data of a desired sensor die and converts
 * it to degrees (Angle).
 * @param[in] ctx : Click context object.
 * See #magneticrotary6_t object definition for detailed explanation.
 * @param[in] die_sel : Sensor die selection: 0 - Bottom die, 1 - Top die.
 * @param[out] angle : Angle in degrees [0-360].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneticrotary6_get_angle ( magneticrotary6_t *ctx, uint8_t die_sel, float *angle );

/**
 * @brief Magnetic Rotary 6 set direction function.
 * @details This function sets the rotation direction of a desired sensor die.
 * @param[in] ctx : Click context object.
 * See #magneticrotary6_t object definition for detailed explanation.
 * @param[in] die_sel : Sensor die selection: 0 - Bottom die, 1 - Top die.
 * @param[in] dir : Rotation direction: 0 - Clockwise, 1 - Counter-Clockwise.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneticrotary6_set_direction ( magneticrotary6_t *ctx, uint8_t die_sel, uint8_t dir );

#ifdef __cplusplus
}
#endif
#endif // MAGNETICROTARY6_H

/*! @} */ // magneticrotary6

// ------------------------------------------------------------------------ END
