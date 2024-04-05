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
 * @file digipot9.h
 * @brief This file contains API for DIGI POT 9 Click Driver.
 */

#ifndef DIGIPOT9_H
#define DIGIPOT9_H

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

/*!
 * @addtogroup digipot9 DIGI POT 9 Click Driver
 * @brief API for configuring and manipulating DIGI POT 9 Click driver.
 * @{
 */

/**
 * @defgroup digipot9_cmd DIGI POT 9 Command byte List
 * @brief List of command bytes of DIGI POT 9 Click driver.
 */

/**
 * @addtogroup digipot9_cmd
 * @{
 */

/**
 * @brief DIGI POT 9 command bits list.
 * @details Command bits list of DIGI POT 9 Click driver.
 */
#define DIGIPOT9_CMD_NOP                        0
#define DIGIPOT9_CMD_RESTORE_EEMEM              1
#define DIGIPOT9_CMD_STORE_RDAC                 2
#define DIGIPOT9_CMD_STORE_USER_DATA            3
#define DIGIPOT9_CMD_DECREMENT_6DB              4
#define DIGIPOT9_CMD_DECREMENT_ALL_6DB          5
#define DIGIPOT9_CMD_DECREMENT_ONE_STEP         6
#define DIGIPOT9_CMD_DECREMENT_ALL_ONE_STEP     7
#define DIGIPOT9_CMD_RESET_EEMEM                8
#define DIGIPOT9_CMD_READ_EEMEM                 9
#define DIGIPOT9_CMD_READ_RDAC                  10
#define DIGIPOT9_CMD_WRITE_DATA                 11
#define DIGIPOT9_CMD_INCREMENT_6DB              12
#define DIGIPOT9_CMD_INCREMENT_ALL_6DB          13
#define DIGIPOT9_CMD_INCREMENT_ONE_STEP         14
#define DIGIPOT9_CMD_INCREMENT_ALL_ONE_STEP     15

/**
 * @brief DIGI POT 9 address bits list.
 * @details Address bits list of DIGI POT 9 Click driver.
 */
#define DIGIPOT9_ADDRESS_RDAC1                  0
#define DIGIPOT9_ADDRESS_RDAC2                  1
#define DIGIPOT9_ADDRESS_USER_DATA_0            2
#define DIGIPOT9_ADDRESS_USER_DATA_1            3
#define DIGIPOT9_ADDRESS_USER_DATA_2            4
#define DIGIPOT9_ADDRESS_USER_DATA_3            5
#define DIGIPOT9_ADDRESS_USER_DATA_4            6
#define DIGIPOT9_ADDRESS_USER_DATA_5            7
#define DIGIPOT9_ADDRESS_USER_DATA_6            8
#define DIGIPOT9_ADDRESS_USER_DATA_7            9
#define DIGIPOT9_ADDRESS_USER_DATA_8            10
#define DIGIPOT9_ADDRESS_USER_DATA_9            11
#define DIGIPOT9_ADDRESS_USER_DATA_10           12
#define DIGIPOT9_ADDRESS_USER_DATA_11           13
#define DIGIPOT9_ADDRESS_USER_DATA_12           14
#define DIGIPOT9_ADDRESS_FACTORY_USAGE          15

/*! @} */ // digipot9_cmd

/**
 * @defgroup digipot9_set DIGI POT 9 RDAC Settings
 * @brief Settings for RDAC of DIGI POT 9 Click driver.
 */

/**
 * @addtogroup digipot9_set
 * @{
 */

/**
 * @brief DIGI POT 9 Wiper setting.
 * @details Specified setting for wiper of DIGI POT 9 Click driver.
 */
#define DIGIPOT9_WIPER_FULL_SCALE               1023
#define DIGIPOT9_WIPER_MID_SCALE                512
#define DIGIPOT9_WIPER_ZERO_SCALE               0

/*! @} */ // digipot9_set

/**
 * @defgroup digipot9_map DIGI POT 9 MikroBUS Map
 * @brief MikroBUS pin mapping of DIGI POT 9 Click driver.
 */

/**
 * @addtogroup digipot9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DIGI POT 9 Click to the selected MikroBUS.
 */
#define DIGIPOT9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.pr = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.wp = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rdy = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // digipot9_map
/*! @} */ // digipot9

/**
 * @brief DIGI POT 9 Click context object.
 * @details Context object definition of DIGI POT 9 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  pr;          /**< Optional Hardware Override Preset. */
    digital_out_t  wp;          /**< Optional Write Protect. */

    // Input pins
    digital_in_t  rdy;          /**< Ready. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} digipot9_t;

/**
 * @brief DIGI POT 9 Click configuration object.
 * @details Configuration object definition of DIGI POT 9 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                 /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                 /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                  /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                   /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  pr;                                   /**< Optional Hardware Override Preset. */
    pin_name_t  wp;                                   /**< Optional Write Protect. */
    pin_name_t  rdy;                                  /**< Ready. */

    // static variable
    uint32_t                           spi_speed;     /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;      /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;   /**< Chip select pin polarity. */

} digipot9_cfg_t;

/**
 * @brief DIGI POT 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DIGIPOT9_OK = 0,
    DIGIPOT9_ERROR = -1

} digipot9_return_value_t;

/*!
 * @addtogroup digipot9 DIGI POT 9 Click Driver
 * @brief API for configuring and manipulating DIGI POT 9 Click driver.
 * @{
 */

/**
 * @brief DIGI POT 9 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #digipot9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void digipot9_cfg_setup ( digipot9_cfg_t *cfg );

/**
 * @brief DIGI POT 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #digipot9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #digipot9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot9_init ( digipot9_t *ctx, digipot9_cfg_t *cfg );

/**
 * @brief DIGI POT 9 default configuration function.
 * @details This function executes a default configuration of DIGI POT 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #digipot9_t object definition for detailed explanation.
 * @return None.
 *
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void digipot9_default_cfg ( digipot9_t *ctx );

/**
 * @brief DIGI POT 9 data writing function.
 * @details This function writes two data bytes to the selected command and address 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #digipot9_t object definition for detailed explanation.
 * @param[in] command : 4-bits command.
 * @param[in] address : 4-bits address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot9_generic_write ( digipot9_t *ctx, uint8_t command, uint8_t address, uint16_t data_in );

/**
 * @brief DIGI POT 9 data reading function.
 * @details This function reads two data bytes from the selected command and address 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #digipot9_t object definition for detailed explanation.
 * @param[in] command : 4-bits command.
 * @param[in] address : 4-bits address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot9_generic_read ( digipot9_t *ctx, uint8_t command, uint8_t address, uint16_t *data_out );

/**
 * @brief DIGI POT 9 Set wiper 1 function.
 * @details This function sets wiper 1 to desired value.
 * @param[in] ctx : Click context object.
 * See #digipot9_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written to wiper 1 register.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot9_set_wiper_1 ( digipot9_t *ctx, uint16_t data_in );

/**
 * @brief DIGI POT 9 Set wiper 2 function.
 * @details This function sets wiper 2 to desired value.
 * @param[in] ctx : Click context object.
 * See #digipot9_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written to wiper 2 register.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot9_set_wiper_2 ( digipot9_t *ctx, uint16_t data_in );

/**
 * @brief DIGI POT 9 Set PR pin function.
 * @details This function sets the PR pin to desired logic state.
 * @param[in] ctx : Click context object.
 * See #digipot9_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void digipot9_set_pr_pin ( digipot9_t *ctx, uint8_t state );

/**
 * @brief DIGI POT 9 Set WP pin function.
 * @details This function sets the WP pin to desired logic state.
 * @param[in] ctx : Click context object.
 * See #digipot9_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void digipot9_set_wp_pin ( digipot9_t *ctx, uint8_t state );

/**
 * @brief DIGI POT 9 get RDY pin function.
 * @details This function returns the RDY pin logic state.
 * @param[in] ctx : Click context object.
 * See #digipot9_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t digipot9_get_rdy_pin ( digipot9_t *ctx );

/**
 * @brief DIGI POT 9 write user data function.
 * @details This function writes two bytes of user data to a desired address of EEMEM.
 * @param[in] ctx : Click context object.
 * See #digipot9_t object definition for detailed explanation.
 * @param[in] address : User data address in EEMEM [2-14].
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot9_write_user_data ( digipot9_t *ctx, uint8_t address, uint16_t data_in );

/**
 * @brief DIGI POT 9 read user data function.
 * @details This function reads two bytes of user data from a desired address of EEMEM.
 * @param[in] ctx : Click context object.
 * See #digipot9_t object definition for detailed explanation.
 * @param[in] address : User data address in EEMEM [2-14].
 * @param[in] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot9_read_user_data ( digipot9_t *ctx, uint8_t address, uint16_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // DIGIPOT9_H

/*! @} */ // digipot9

// ------------------------------------------------------------------------ END
