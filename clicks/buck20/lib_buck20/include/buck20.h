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
 * @file buck20.h
 * @brief This file contains API for Buck 20 Click Driver.
 */

#ifndef BUCK20_H
#define BUCK20_H

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
 * @addtogroup buck20 Buck 20 Click Driver
 * @brief API for configuring and manipulating Buck 20 Click driver.
 * @{
 */

/**
 * @defgroup buck20_cmd Buck 20 Command byte List
 * @brief List of command bytes of Buck 20 Click driver.
 */

/**
 * @addtogroup buck20_cmd
 * @{
 */

/**
 * @brief Buck 20 digipot command bits list.
 * @details Digipot command bits list of Buck 20 Click driver.
 */
#define BUCK20_CMD_NOP                      0
#define BUCK20_CMD_RESTORE_EEMEM            1
#define BUCK20_CMD_STORE_RDAC               2
#define BUCK20_CMD_STORE_USER_DATA          3
#define BUCK20_CMD_DECREMENT_6DB            4
#define BUCK20_CMD_DECREMENT_ALL_6DB        5
#define BUCK20_CMD_DECREMENT_ONE_STEP       6
#define BUCK20_CMD_DECREMENT_ALL_ONE_STEP   7
#define BUCK20_CMD_RESET_EEMEM              8
#define BUCK20_CMD_READ_EEMEM               9
#define BUCK20_CMD_READ_RDAC                10
#define BUCK20_CMD_WRITE_DATA               11
#define BUCK20_CMD_INCREMENT_6DB            12
#define BUCK20_CMD_INCREMENT_ALL_6DB        13
#define BUCK20_CMD_INCREMENT_ONE_STEP       14
#define BUCK20_CMD_INCREMENT_ALL_ONE_STEP   15

/**
 * @brief Buck 20 digipot address bits list.
 * @details Digipot address bits list of Buck 20 Click driver.
 */
#define BUCK20_ADDRESS_RDAC1                0
#define BUCK20_ADDRESS_RDAC2                1
#define BUCK20_ADDRESS_USER_DATA_0          2
#define BUCK20_ADDRESS_USER_DATA_1          3
#define BUCK20_ADDRESS_USER_DATA_2          4
#define BUCK20_ADDRESS_USER_DATA_3          5
#define BUCK20_ADDRESS_USER_DATA_4          6
#define BUCK20_ADDRESS_USER_DATA_5          7
#define BUCK20_ADDRESS_USER_DATA_6          8
#define BUCK20_ADDRESS_USER_DATA_7          9
#define BUCK20_ADDRESS_USER_DATA_8          10
#define BUCK20_ADDRESS_USER_DATA_9          11
#define BUCK20_ADDRESS_USER_DATA_10         12
#define BUCK20_ADDRESS_USER_DATA_11         13
#define BUCK20_ADDRESS_USER_DATA_12         14
#define BUCK20_ADDRESS_FACTORY_USAGE        15

/*! @} */ // buck20_cmd

/**
 * @defgroup buck20_set Buck 20 Registers Settings
 * @brief Settings for registers of Buck 20 Click driver.
 */

/**
 * @addtogroup buck20_set
 * @{
 */

/**
 * @brief Buck 20 digipot wiper setting.
 * @details Specified setting for digipot wiper of Buck 20 Click driver.
 */
#define BUCK20_WIPER_FULL_SCALE             1023
#define BUCK20_WIPER_MID_SCALE              512
#define BUCK20_WIPER_ZERO_SCALE             0

/**
 * @brief Buck 20 voltage calculation values.
 * @details Specified voltage calculation values of Buck 20 Click driver.
 */
#define BUCK20_RESISTOR_R6_KOHM             47.0f
#define BUCK20_DIGIPOT_MAX_KOHM             250.0f
#define BUCK20_BUCK_R2_KOHM                 40.2f
#define BUCK20_BUCK_VREF                    0.6f

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b buck20_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define BUCK20_SET_DATA_SAMPLE_EDGE         SET_SPI_DATA_SAMPLE_EDGE
#define BUCK20_SET_DATA_SAMPLE_MIDDLE       SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // buck20_set

/**
 * @defgroup buck20_map Buck 20 MikroBUS Map
 * @brief MikroBUS pin mapping of Buck 20 Click driver.
 */

/**
 * @addtogroup buck20_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Buck 20 Click to the selected MikroBUS.
 */
#define BUCK20_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rdy  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // buck20_map
/*! @} */ // buck20

/**
 * @brief Buck 20 Click context object.
 * @details Context object definition of Buck 20 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Active high buck chip enable pin. */

    // Input pins
    digital_in_t rdy;               /**< Active high digipot ready pin. */

    // Modules
    spi_master_t spi;               /**< SPI driver object. */

    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */

} buck20_t;

/**
 * @brief Buck 20 Click configuration object.
 * @details Configuration object definition of Buck 20 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Active high buck chip enable pin. */
    pin_name_t rdy;                 /**< Active high digipot ready pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} buck20_cfg_t;

/**
 * @brief Buck 20 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BUCK20_OK = 0,
    BUCK20_ERROR = -1

} buck20_return_value_t;

/*!
 * @addtogroup buck20 Buck 20 Click Driver
 * @brief API for configuring and manipulating Buck 20 Click driver.
 * @{
 */

/**
 * @brief Buck 20 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #buck20_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void buck20_cfg_setup ( buck20_cfg_t *cfg );

/**
 * @brief Buck 20 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #buck20_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #buck20_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck20_init ( buck20_t *ctx, buck20_cfg_t *cfg );

/**
 * @brief Buck 20 data writing function.
 * @details This function writes two data bytes to the selected command and address 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #buck20_t object definition for detailed explanation.
 * @param[in] command : 4-bits command.
 * @param[in] address : 4-bits address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck20_generic_write ( buck20_t *ctx, uint8_t command, uint8_t address, uint16_t data_in );

/**
 * @brief Buck 20 data reading function.
 * @details This function reads two data bytes from the selected command and address 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #buck20_t object definition for detailed explanation.
 * @param[in] command : 4-bits command.
 * @param[in] address : 4-bits address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck20_generic_read ( buck20_t *ctx, uint8_t command, uint8_t address, uint16_t *data_out );

/**
 * @brief Buck 20 Set wiper 1 function.
 * @details This function sets wiper 1 to desired value.
 * @param[in] ctx : Click context object.
 * See #buck20_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written to wiper 1 register.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck20_set_wiper_1 ( buck20_t *ctx, uint16_t data_in );

/**
 * @brief Buck 20 write user data function.
 * @details This function writes two bytes of user data to a desired address of EEMEM.
 * @param[in] ctx : Click context object.
 * See #buck20_t object definition for detailed explanation.
 * @param[in] address : User data address in EEMEM [2-14].
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck20_write_user_data ( buck20_t *ctx, uint8_t address, uint16_t data_in );

/**
 * @brief Buck 20 read user data function.
 * @details This function reads two bytes of user data from a desired address of EEMEM.
 * @param[in] ctx : Click context object.
 * See #buck20_t object definition for detailed explanation.
 * @param[in] address : User data address in EEMEM [2-14].
 * @param[in] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck20_read_user_data ( buck20_t *ctx, uint8_t address, uint16_t *data_out );

/**
 * @brief Buck 20 get rdy pin function.
 * @details This function returns the digipot RDY pin logic state.
 * @param[in] ctx : Click context object.
 * See #buck20_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t buck20_get_rdy_pin ( buck20_t *ctx );

/**
 * @brief Buck 20 enable device function.
 * @details This function enables the buck device by setting the RST pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #buck20_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void buck20_enable_device ( buck20_t *ctx );

/**
 * @brief Buck 20 disable device function.
 * @details This function disables the buck device by setting the RST pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #buck20_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void buck20_disable_device ( buck20_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BUCK20_H

/*! @} */ // buck20

// ------------------------------------------------------------------------ END
