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
 * @file digipot2.h
 * @brief This file contains API for DIGI POT 2 Click Driver.
 */

#ifndef DIGIPOT2_H
#define DIGIPOT2_H

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
#include "drv_spi_master.h"

/*!
 * @addtogroup digipot2 DIGI POT 2 Click Driver
 * @brief API for configuring and manipulating DIGI POT 2 Click driver.
 * @{
 */

/**
 * @defgroup digipot2_map DIGI POT 2 MikroBUS Map
 * @brief MikroBUS pin mapping of DIGI POT 2 Click driver.
 */

/**
 * @addtogroup digipot2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DIGI POT 2 Click to the selected MikroBUS.
 */
#define DIGIPOT2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS )

/*! @} */ // digipot2_map

/**
 * @defgroup digipot2_macros DIGI POT 2 Macros
 * @brief Macros of Click driver.
 */

/**
 * @addtogroup digipot2_macros
 * @{
 */

/**
 * @brief DIGI POT 2 EEPROM data
 * @details Adding EEPROM data of DIGI POT 2 Click driver.
 */
#define DIGIPOT2_DATA_EEPROM_6                0x06
#define DIGIPOT2_DATA_EEPROM_7                0x07
#define DIGIPOT2_DATA_EEPROM_8                0x08
#define DIGIPOT2_DATA_EEPROM_9                0x09
#define DIGIPOT2_DATA_EEPROM_A                0x0A
#define DIGIPOT2_DATA_EEPROM_B                0x0B
#define DIGIPOT2_DATA_EEPROM_C                0x0C
#define DIGIPOT2_DATA_EEPROM_D                0x0D
#define DIGIPOT2_DATA_EEPROM_E                0x0E
#define DIGIPOT2_DATA_EEPROM_F                0x0F
#define DIGIPOT2_DATA_WRITE_CMD               0x20

/**
 * @brief DIGI POT 2 DIGIPOT2 Command
 * @details Adding DIGIPOT2 Commands of DIGI POT 2 Click driver.
 */
#define DIGIPOT2_VOLATILE_WIPER_0             0x00
#define DIGIPOT2_VOLATILE_WIPER_1             0x01
#define DIGIPOT2_NON_VOLATILE_WIPER_0         0x02
#define DIGIPOT2_NON_VOLATILE_WIPER_1         0x03
#define DIGIPOT2_VOLATILE_TCON_REGISTER       0x04
#define DIGIPOT2_STATUS_REGISTER              0x05

/*! @} */ // digipot2_macros
/*! @} */ // digipot2

/**
 * @brief DIGI POT 2 Click context object.
 * @details Context object definition of DIGI POT 2 Click driver.
 */
typedef struct
{
    // Output pins
    
    digital_out_t cs;
    
    // Modules
    spi_master_t  spi;                               /**< SPI driver object. */

    pin_name_t  chip_select;                         /**< Chip select pin descriptor (used for SPI driver). */

} digipot2_t;

/**
 * @brief DIGI POT 2 Click configuration object.
 * @details Configuration object definition of DIGI POT 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                      /**< Chip select pin descriptor for SPI driver. */

    // static variable
    
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} digipot2_cfg_t;

/**
 * @brief DIGI POT 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   DIGIPOT2_OK = 0,
   DIGIPOT2_ERROR = -1

} digipot2_return_value_t;

/*!
 * @addtogroup digipot2 DIGI POT 2 Click Driver
 * @brief API for configuring and manipulating DIGI POT 2 Click driver.
 * @{
 */

/**
 * @brief DIGI POT 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #digipot2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void digipot2_cfg_setup ( digipot2_cfg_t *cfg );

/**
 * @brief DIGI POT 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #digipot2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #digipot2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot2_init ( digipot2_t *ctx, digipot2_cfg_t *cfg );

/**
 * @brief Generic transfer function.
 * @details Generic SPI transfer, for sending and receiving packages
 * @param[in] ctx : Click context object.
 * See #digipot2_t object definition for detailed explanation.
 * @param[in] wr_buf : Write data buffer
 * @param[in] wr_len : Number of byte in write data buffer
 * @param[out] rd_buf : Read data buffer
 * @param[in] rd_len : Number of byte in read data buffer
 * @return Nothing.
 * 
 */
void digipot2_generic_transfer ( digipot2_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief Set wiper position
 * @details The function sets 8-bit wiper positions data.
 * @param[in] ctx : Click context object.
 * See #digipot2_t object definition for detailed explanation.
 * @param[out] wiper_pos : uint8_t wiper positions data.
 * @return Nothing.
 * 
 */
void digipot2_set_wiper_positions ( digipot2_t *ctx, uint8_t wiper_pos );

/**
 * @brief Convert ADC value to volatage
 * @details The function convert 10-bit ADC value to volatage reference.
 * @param[in] adc_val : 10-bit ADC value.
 * @param[in] wiper_pos : float voltage reference: 3.3V or 5V.
 *
 * @return float voltage ( 0V - 3.3V ) or ( 0V - 5.0V ).
 * 
 */
float digipot2_convert_output ( uint16_t adc_val, float v_ref );

#ifdef __cplusplus
}
#endif
#endif // DIGIPOT2_H

/*! @} */ // digipot2

// ------------------------------------------------------------------------ END
