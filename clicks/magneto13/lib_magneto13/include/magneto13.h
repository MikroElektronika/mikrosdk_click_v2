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
 * @file magneto13.h
 * @brief This file contains API for Magneto 13 Click Driver.
 */

#ifndef MAGNETO13_H
#define MAGNETO13_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup magneto13 Magneto 13 Click Driver
 * @brief API for configuring and manipulating Magneto 13 Click driver.
 * @{
 */

/**
 * @defgroup magneto13_reg Magneto 13 Registers List
 * @brief List of registers of Magneto 13 Click driver.
 */

/**
 * @addtogroup magneto13_reg
 * @{
 */

/**
 * @brief Magneto 13 description register.
 * @details Specified register for description of Magneto 13 Click driver.
 */
#define MAGNETO13_REG_ZERO_0                0x00
#define MAGNETO13_REG_ZERO_1                0x01
#define MAGNETO13_REG_BCT                   0x02
#define MAGNETO13_REG_ET_YX                 0x03
#define MAGNETO13_REG_MG_LT_HT_MG           0x06
#define MAGNETO13_REG_IRQM_RAR_HYST         0x07
#define MAGNETO13_REG_THR                   0x08
#define MAGNETO13_REG_RD                    0x09
#define MAGNETO13_REG_REF                   0x0A
#define MAGNETO13_REG_TRISTATE_SPI_PULL     0x0D
#define MAGNETO13_REG_FW                    0x0E
#define MAGNETO13_REG_ERR_PAR_MEM_NVM       0x1A
#define MAGNETO13_REG_M_GH_GL               0x1B

/*! @} */ // magneto13_reg

/**
 * @addtogroup magneto13_cmd
 * @{
 */

/**
 * @brief Magneto 13 description command.
 * @details Specified command for description of Magneto 13 Click driver.
 */
#define MAGNETO13_CMD_READ_ANGLE            0x00
#define MAGNETO13_CMD_CLEAR_ERR_FLAGS       0x01
#define MAGNETO13_CMD_READ_REGISTER         0x02
#define MAGNETO13_CMD_WRITE_REGISTER        0x04
#define MAGNETO13_CMD_RESTORE_ALL_NVM       0x05
#define MAGNETO13_CMD_STORE_ALL_NVM         0x06
#define MAGNETO13_CMD_STORE_SINGLE_NVM      0x07

/*! @} */ // magneto13_cmd

/**
 * @defgroup magneto13_set Magneto 13 Registers Settings
 * @brief Settings for registers of Magneto 13 Click driver.
 */

/**
 * @addtogroup magneto13_set
 * @{
 */

/**
 * @brief Magneto 13 descriptions of the command and register bit masks.
 * @details Specified command and register bit masks of Magneto 13 Click driver.
 */
#define MAGNETO13_CMD_BIT_MASK              0x07
#define MAGNETO13_REG_BIT_MASK              0x1F

/**
 * @brief Magneto 13 description of trimming settings.
 * @details Specified trimming settings of Magneto 13 Click driver.
 */
#define MAGNETO13_TRIMMING_X_DIS            0x00
#define MAGNETO13_TRIMMING_X_EN             0x01
#define MAGNETO13_TRIMMING_Y_DIS            0x00
#define MAGNETO13_TRIMMING_Y_EN             0x02

/**
 * @brief Magneto 13 description of magnetic field threshold settings.
 * @details Specified trimming and magnetic settings of Magneto 13 Click driver.
 */
#define MAGNETO13_MG_LT_LVL_0               0x00
#define MAGNETO13_MG_LT_LVL_1               0x40
#define MAGNETO13_MG_LT_LVL_2               0x80
#define MAGNETO13_MG_LT_LVL_3               0xC0
#define MAGNETO13_MG_HT_LVL_0               0x00
#define MAGNETO13_MG_HT_LVL_1               0x10
#define MAGNETO13_MG_HT_LVL_2               0x20
#define MAGNETO13_MG_HT_LVL_3               0x30
#define MAGNETO13_MG_BIT_MASK               0xF0
#define MAGNETO13_MG_FLD_THD_DIS            0x00
#define MAGNETO13_MG_FLD_THD_EN             0x01

/**
 * @brief Magneto 13 description of field strength level.
 * @details Specified field strength level of Magneto 13 Click driver.
 */
#define MAGNETO13_FLD_ST_OK                 0x00
#define MAGNETO13_FLD_ST_MGL                0x01
#define MAGNETO13_FLD_ST_MGH                0x02
#define MAGNETO13_FLD_ST_BIT_MASK           0x03

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b magneto13_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define MAGNETO13_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define MAGNETO13_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // magneto13_set

/**
 * @defgroup magneto13_map Magneto 13 MikroBUS Map
 * @brief MikroBUS pin mapping of Magneto 13 Click driver.
 */

/**
 * @addtogroup magneto13_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Magneto 13 Click to the selected MikroBUS.
 */
#define MAGNETO13_MAP_MIKROBUS( cfg, mikrobus )     \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.err = MIKROBUS( mikrobus, MIKROBUS_AN );    \
    cfg.nvm = MIKROBUS( mikrobus, MIKROBUS_PWM );   \
    cfg.irq = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // magneto13_map
/*! @} */ // magneto13

/**
 * @brief Magneto 13 Click context object.
 * @details Context object definition of Magneto 13 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t err;    /**< Error flag pin. */
    digital_in_t nvm;    /**< Non-volatile memory (NVM) pin. */
    digital_in_t irq;    /**< Interrupt on angle change pin. */

    // Modules
    spi_master_t spi;            /**< SPI driver object. */

    pin_name_t   chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} magneto13_t;

/**
 * @brief Magneto 13 Click configuration object.
 * @details Configuration object definition of Magneto 13 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  err;    /**< Error flag pin. */
    pin_name_t nvm;     /**< Non-volatile memory (NVM) pin. */
    pin_name_t irq;     /**< Interrupt on angle change pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} magneto13_cfg_t;

/**
 * @brief Magneto 13 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MAGNETO13_OK = 0,
    MAGNETO13_ERROR = -1

} magneto13_return_value_t;

/*!
 * @addtogroup magneto13 Magneto 13 Click Driver
 * @brief API for configuring and manipulating Magneto 13 Click driver.
 * @{
 */

/**
 * @brief Magneto 13 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #magneto13_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void magneto13_cfg_setup ( magneto13_cfg_t *cfg );

/**
 * @brief Magneto 13 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #magneto13_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #magneto13_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto13_init ( magneto13_t *ctx, magneto13_cfg_t *cfg );

/**
 * @brief Magneto 13 default configuration function.
 * @details This function executes a default configuration of Magneto 13
 * click board.
 * @param[in] ctx : Click context object.
 * See #magneto13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t magneto13_default_cfg ( magneto13_t *ctx );

/**
 * @brief Magneto 13 data writing function.
 * @details This function writes a data byte to 
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #magneto13_t object definition for detailed explanation.
 * @param[in] cmd : Command.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto13_write_reg ( magneto13_t *ctx, uint8_t cmd, uint8_t reg, uint8_t data_in );

/**
 * @brief Magneto 13 data reading function.
 * @details This function reads a data byte from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #magneto13_t object definition for detailed explanation.
 * @param[in] cmd : Command.
 * @param[in] reg : Register address
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto13_read_reg ( magneto13_t *ctx, uint8_t cmd, uint8_t reg, uint8_t *data_out );

/**
 * @brief Magneto 13 gets the angle raw data function.
 * @details This function reads a 16-bit angle raw data
 * of the MagAlpha MA736, Contactless Digital Angle Sensor
 * on the Magneto 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #magneto13_t object definition for detailed explanation.
 * @param[out] raw_data : Angle raw data [0-65535].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto13_get_angle_raw_data ( magneto13_t *ctx, uint16_t *raw_data );

/**
 * @brief Magneto 13 gets the angular position function.
 * @details This function reads an angular position in degrees
 * of the MagAlpha MA736, Contactless Digital Angle Sensor
 * on the Magneto 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #magneto13_t object definition for detailed explanation.
 * @param[out] angle : Angle data, degrees [0-360].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto13_get_angle ( magneto13_t *ctx, float *angle );

/**
 * @brief Magneto 13 sets the magnetic field threshold function.
 * @details This function sets the magnetic field's high and low thresholds
 * of the MagAlpha MA736, Contactless Digital Angle Sensor
 * on the Magneto 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #magneto13_t object definition for detailed explanation.
 * @param[in] mglt : Sets the field strength low threshold.
 * @param[in] mght : Sets the field strength high threshold.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto13_set_mag_field_thd ( magneto13_t *ctx, uint8_t mglt, uint8_t mght );

/**
 * @brief Magneto 13 enables the magnetic field threshold detection function.
 * @details This function activates the magnetic field threshold detection
 * of the MagAlpha MA736, Contactless Digital Angle Sensor
 * on the Magneto 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #magneto13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto13_enable_fld_thd_det ( magneto13_t *ctx );

/**
 * @brief Magneto 13 gets the magnetic field strength function.
 * @details This function reads a magnetic field strength detection
 * of the MagAlpha MA736, Contactless Digital Angle Sensor
 * on the Magneto 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #magneto13_t object definition for detailed explanation.
 * @param[out] field_strength : 
 *         @li @c  0 - Magnetic field strength OK,
 *         @li @c  1 - Magnetic field strength below the MGLT level,
 *         @li @c  2 - Magnetic field strength above the MGHT level.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto13_get_field_strength ( magneto13_t *ctx, uint8_t *field_strength );

/**
 * @brief Magneto 13 gets the error flag function.
 * @details This function gets states of the error flag ( ERR ) pin
 * of the MagAlpha MA736, Contactless Digital Angle Sensor
 * on the Magneto 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #magneto13_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t magneto13_get_error_flag ( magneto13_t *ctx );

/**
 * @brief Magneto 13 checks the access to the NVM function.
 * @details This function indicates whether the chip is busy accessing the NVM
 * of the MagAlpha MA736, Contactless Digital Angle Sensor
 * on the Magneto 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #magneto13_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t magneto13_get_nvm_access_state ( magneto13_t *ctx );

/**
 * @brief Magneto 13 gets the interrupt on the angle change state function.
 * @details This function indicates whether the angle change 
 * has exceeded the defined threshold
 * of the MagAlpha MA736, Contactless Digital Angle Sensor
 * on the Magneto 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #magneto13_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t magneto13_get_interrupt ( magneto13_t *ctx );



#ifdef __cplusplus
}
#endif
#endif // MAGNETO13_H

/*! @} */ // magneto13

// ------------------------------------------------------------------------ END
