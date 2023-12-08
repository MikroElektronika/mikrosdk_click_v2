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
 * @file sram3.h
 * @brief This file contains API for SRAM 3 Click Driver.
 */

#ifndef SRAM3_H
#define SRAM3_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"

/*!
 * @addtogroup sram3 SRAM 3 Click Driver
 * @brief API for configuring and manipulating SRAM 3 Click driver.
 * @{
 */

/**
 * @defgroup sram3_reg SRAM 3 Registers List
 * @brief List of registers of SRAM 3 Click driver.
 */

/**
 * @defgroup sram3_set SRAM 3 Registers Settings
 * @brief Settings for registers of SRAM 3 Click driver.
 */

/**
 * @addtogroup sram3_set
 * @{
 */

/**
 * @brief SRAM 3 description setting.
 * @details Specified setting for description of SRAM 3 Click driver.
 */
#define SRAM3_OPCODE_WREN                   0x06
#define SRAM3_OPCODE_WRDI                   0x04
#define SRAM3_OPCODE_RDSR                   0x05
#define SRAM3_OPCODE_WRSR                   0x01
#define SRAM3_OPCODE_READ                   0x03
#define SRAM3_OPCODE_SECURE_READ            0x13
#define SRAM3_OPCODE_WRITE                  0x02
#define SRAM3_OPCODE_SECURE_WRITE           0x12
#define SRAM3_OPCODE_STORE                  0x08
#define SRAM3_OPCODE_RECALL                 0x09
#define SRAM3_OPCODE_WRSNR                  0xC2
#define SRAM3_OPCODE_RDSNR                  0xC3
#define SRAM3_OPCODE_HIBERNATE              0xB9

/**
 * @brief SRAM 3 protection ranges.
 * @details Protection ranges of SRAM 3 Click driver.
 */
#define SRAM3_PROT_NONE                     0x00
#define SRAM3_PROT_QUART                    0x04
#define SRAM3_PROT_HALF                     0x08
#define SRAM3_PROT_ALL                      0x0C
                                    
/**
 * @brief SRAM 3 status register bits.
 * @details Status register bits of SRAM 3 Click driver.
 */
#define SRAM3_STATS_RDY_BIT                 0x01
#define SRAM3_STATS_WEN_BIT                 0x02
#define SRAM3_STATS_SWM_BIT                 0x10
#define SRAM3_STATS_PDIS_BIT                0x40

/**
 * @brief SRAM 3 some predefined buffer sizes.
 * @details Some predefined buffer sizes of SRAM 3 Click driver.
 */
#define SRAM3_SERIAL_LEN                    0x10
#define SRAM3_SECURE_BUF_SIZE               0x80
/*! @} */ // sram3_set

/**
 * @defgroup sram3_map SRAM 3 MikroBUS Map
 * @brief MikroBUS pin mapping of SRAM 3 Click driver.
 */

/**
 * @addtogroup sram3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of SRAM 3 Click to the selected MikroBUS.
 */
#define SRAM3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.hold = MIKROBUS( mikrobus, MIKROBUS_PWM ) 

/*! @} */ // sram3_map
/*! @} */ // sram3

/**
 * @brief SRAM 3 Click context object.
 * @details Context object definition of SRAM 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  hold;            /**< Description. */

    // Modules
    spi_master_t  spi;              /**< SPI driver object. */

    pin_name_t  chip_select;        /**< Chip select pin descriptor (used for SPI driver). */

} sram3_t;

/**
 * @brief SRAM 3 Click configuration object.
 * @details Configuration object definition of SRAM 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;               /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;               /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                 /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins    
    pin_name_t  hold;               /**< Description. */

    // static variable    
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} sram3_cfg_t;

/**
 * @brief SRAM 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   SRAM3_OK = 0,
   SRAM3_ERROR = -1

} sram3_return_value_t;

/*!
 * @addtogroup sram3 SRAM 3 Click Driver
 * @brief API for configuring and manipulating SRAM 3 Click driver.
 * @{
 */

/**
 * @brief SRAM 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #sram3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void sram3_cfg_setup ( sram3_cfg_t *cfg );

/**
 * @brief SRAM 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #sram3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #sram3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t sram3_init ( sram3_t *ctx, sram3_cfg_t *cfg );

/**
 * @brief SRAM 3 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #sram3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t sram3_generic_write ( sram3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief SRAM 3 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #sram3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t sram3_generic_read ( sram3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief SRAM 3 enabling writing to memory function.
 * @details This function is for enabling writing to memory, status register or user serial.
 * @param[in] ctx : Click context object.
 * See #sram3_t object definition for detailed explanation.
 * @return Nothing.
 *
 * @note None.
 */
void sram3_enable_write( sram3_t *ctx );

/**
 * @brief SRAM 3 disabling writing to memory function.
 * @details Function for disabling writing to memory, status register or user serial.
 * @param[in] ctx : Click context object.
 * See #sram3_t object definition for detailed explanation.
 * @return Nothing.
 *
 * @note None.
 */
void sram3_disable_write( sram3_t *ctx );

/**
 * @brief SRAM 3 reading function.
 * @details Function wich reads data from status register.
 * @param[in] ctx : Click context object.
 * See #sram3_t object definition for detailed explanation.
 * @return Value of status register.
 * 
 * @note None.
 */
uint8_t sram3_read_status( sram3_t *ctx );

/**
 * @brief SRAM 3 writing function.
 * @details Function which writes data to status register.
 * @param[in] ctx : Click context object.
 * See #sram3_t object definition for detailed explanation.
 * @param[in] status : Value to be written to status register.
 * @return Nothing.
 *
 * @note None.
 */
void sram3_write_status( sram3_t *ctx, uint8_t status );

/**
 * @brief SRAM 3 secures memory function.
 * @details Function which secures part of memory from writing.
 * @param[in] ctx : Click context object.
 * See #sram3_t object definition for detailed explanation.
 * @param[in] protect_range : Part of memory to be protected
 * @return Nothing.
 *
 * @note None.
 */
void sram3_protect_memory( sram3_t *ctx, uint8_t protect_range );

/**
 * @brief SRAM 3 set up enable function.
 * @details Function which set up enable old status.
 * @param[in] ctx : Click context object.
 * See #sram3_t object definition for detailed explanation.
 * @return Nothing.
 *
 * @note None.
 */
void sram3_enable_pdis( sram3_t *ctx );

/**
 * @brief SRAM 3 set up disable function.
 * @details Function which set up disable old status.
 * @param[in] ctx : Click context object.
 * See #sram3_t object definition for detailed explanation.
 * @return Nothing.
 *
 * @note None.
 */
void sram3_disable_pdis( sram3_t *ctx );

/**
 * @brief SRAM 3 relocation data function.
 * @details Function that moves data from FLASH to SRAM.
 * @param[in] ctx : Click context object.
 * See #sram3_t object definition for detailed explanation.
 * @return Nothing.
 *
 * @note None.
 */
void sram3_recall( sram3_t *ctx );

/**
 * @brief SRAM 3 relocation data function.
 * @details Function that moves data from SRAM to FLASH
 * @param[in] ctx : Click context object.
 * See #sram3_t object definition for detailed explanation.
 * @return Nothing.
 *
 * @note None.
 */
void sram3_store( sram3_t *ctx );

/**
 * @brief SRAM 3 changing function.
 * @details Function that puts SRAM3 click to hibernate mode.
 * @param[in] ctx : Click context object.
 * See #sram3_t object definition for detailed explanation.
 * @return Nothing.
 *
 * @note None.
 */
void sram3_hibernate_start( sram3_t *ctx );

/**
 * @brief SRAM 3 changing function.
 * @details Function that ends SRAM3 click to hibernate mode.
 * @param[in] ctx : Click context object.
 * See #sram3_t object definition for detailed explanation.
 * @return Nothing.
 *
 * @note None.
 */
void sram3_hibernate_stop( sram3_t *ctx );

/**
 * @brief SRAM 3 changing pin state function.
 * @details Function that sets hold pin active.
 * @param[in] ctx : Click context object.
 * See #sram3_t object definition for detailed explanation.
 * @return Nothing.
 *
 * @note None.
 */
void sram3_hold( sram3_t *ctx );

/**
 * @brief SRAM 3 changing pin state function.
 * @details Function that sets hold pin inactive.
 * @param[in] ctx : Click context object.
 * See #sram3_t object definition for detailed explanation.
 * @return Nothing.
 *
 * @note None.
 */
void sram3_release_hold( sram3_t *ctx );

/**
 * @brief SRAM 3 reading number function.
 * @details Function that reads serial number of click.
 * @param[in] ctx : Click context object.
 * See #sram3_t object definition for detailed explanation.
 * @param[in] buf : Buffer to be written to.
 * @return Nothing.
 *
 * @note None.
 */
void sram3_read_serial( sram3_t *ctx, uint8_t *buf );

/**
 * @brief SRAM 3 writing number function.
 * @details Function that writes serial number of click.
 * @param[in] ctx : Click context object.
 * See #sram3_t object definition for detailed explanation.
 * @param[in] buf : Buffer to be written to.
 * @return Nothing.
 *
 * @note None.
 */
void sram3_write_serial( sram3_t *ctx, uint8_t *buf );


/**
 * @brief SRAM 3 reading data function.
 * @details Function that reads data from memory.
 * @param[in] ctx : Click context object.
 * See #sram3_t object definition for detailed explanation.
 * @param[in] mem_adr : Address to read from.
 * @param[in] read_buf : Buffer to store data.
 * @param[in] buf_size : Size of data.
 * @return Nothing.
 *
 * @note None.
 */
void sram3_read( sram3_t *ctx, uint32_t mem_adr, uint8_t *read_buf, uint8_t buf_size );

/**
 * @brief SRAM 3 secure reading data function.
 * @details Function for secure reading data from memory.
 * @param[in] ctx : Click context object.
 * See #sram3_t object definition for detailed explanation.
 * @param[in] mem_adr : Address to read from.
 * @param[in] read_buf : Buffer to store data.
 * @return Nothing.
 *
 * @note None.
 */
err_t sram3_secure_read( sram3_t *ctx, uint32_t mem_adr, uint8_t *read_buf );

/**
 * @brief SRAM 3 writing data function.
 * @details Function for writing data memory.
 * @param[in] ctx : Click context object.
 * See #sram3_t object definition for detailed explanation.
 * @param[in] mem_adr : Address to read from.
 * @param[in] write_buf : Data to be written.
 * @param[in] buf_size : Size of data.
 * @return Nothing.
 *
 * @note None.
 */
void sram3_write( sram3_t *ctx, uint32_t mem_adr, uint8_t *write_buf, uint8_t buf_size );

/**
 * @brief SRAM 3 secure writing data function.
 * @details Function for secure writing data to memory function.
 * @param[in] ctx : Click context object.
 * See #sram3_t object definition for detailed explanation.
 * @param[in] mem_adr : Address to read from.
 * @param[in] write_buf : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * @note None.
 */
err_t sram3_secure_write( sram3_t *ctx, uint32_t mem_adr, uint8_t *write_buf );

#ifdef __cplusplus
}
#endif
#endif // SRAM3_H

/*! @} */ // sram3

// ------------------------------------------------------------------------ END
