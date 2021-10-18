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
 * @file nvsram2.h
 * @brief This file contains API for nvSRAM 2 Click Driver.
 */

#ifndef NVSRAM2_H
#define NVSRAM2_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"

/*!
 * @addtogroup nvsram2 nvSRAM 2 Click Driver
 * @brief API for configuring and manipulating nvSRAM 2 Click driver.
 * @{
 */

/**
 * @defgroup nvsram2_reg nvSRAM 2 Registers List
 * @brief List of registers of nvSRAM 2 Click driver.
 */

/**
 * @addtogroup nvsram2_set
 * @{
 */

/**
 * @brief nvSRAM 2 description setting.
 * @details Specified setting for description of nvSRAM 2 Click driver.
 */

/**
 * @brief nvSRAM 2 status register control instructions.
 * @details Status register control instructions of nvSRAM 2 Click driver.
 */
#define NVSRAM2_STATUS_RDSR                                        0x05
#define NVSRAM2_STATUS_FRDSR                                       0x0A
#define NVSRAM2_STATUS_WRSR                                        0x01
#define NVSRAM2_STATUS_WREN                                        0x06
#define NVSRAM2_STATUS_WRDI                                        0x04

/**
 * @brief nvSRAM 2 SRAM read/write instructions.
 * @details Specified SRAM read/write instructions of nvSRAM 2 Click driver.
 */
#define NVSRAM2_SRAM_READ                                          0x03
#define NVSRAM2_SRAM_FREAD                                         0x0B
#define NVSRAM2_SRAM_WRITE                                         0x02

/**
 * @brief nvSRAM 2 SRAM special NV instructions.
 * @details Special NV instructions of nvSRAM 2 Click driver.
 */
#define NVSRAM2_SPEC_NV_STORE                                      0x3C
#define NVSRAM2_SPEC_NV_RECALL                                     0x60
#define NVSRAM2_SPEC_NV_ASENB                                      0x59
#define NVSRAM2_SPEC_NV_ASDISB                                     0x19
                                                                  
/**
 * @brief nvSRAM 2 SRAM special instructions.
 * @details Special instructions of nvSRAM 2 Click driver.
 */                                                        
#define NVSRAM2_SPEC_SLEEP                                         0xB9
#define NVSRAM2_SPEC_WRSN                                          0xC2
#define NVSRAM2_SPEC_RDSN                                          0xC3
#define NVSRAM2_SPEC_FRDSN                                         0xC9
#define NVSRAM2_SPEC_RDID                                          0x9F
#define NVSRAM2_SPEC_FRDID                                         0x99
                                                                
/**
 * @brief nvSRAM 2 status register content.
 * @details Status register content of nvSRAM 2 Click driver.
 */ 
#define NVSRAM2_STATUS_RDY                                         0x01
#define NVSRAM2_STATUS_WEN                                         0x02
#define NVSRAM2_STATUS_BP0                                         0x04
#define NVSRAM2_STATUS_BP1                                         0x08
#define NVSRAM2_STATUS_SNL                                         0x40
#define NVSRAM2_STATUS_WPEN                                        0x80

#define NVSRAM2_HOLD_ENABLE                                        0x00
#define NVSRAM2_HOLD_DISABLE                                       0x01

#define NVSRAM2_DUMMY_BYTE                                         0x00
/*! @} */ // nvsram2_set

/**
 * @defgroup nvsram2_map nvSRAM 2 MikroBUS Map
 * @brief MikroBUS pin mapping of nvSRAM 2 Click driver.
 */

/**
 * @addtogroup nvsram2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of nvSRAM 2 Click to the selected MikroBUS.
 */
#define NVSRAM2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.hld = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    
/*! @} */ // nvsram2_map
/*! @} */ // nvsram2

/**
 * @brief nvSRAM 2 Click context object.
 * @details Context object definition of nvSRAM 2 Click driver.
 */
typedef struct
{
    // Output pins
    
    digital_out_t  hld;                             /**< Description. */

    // Modules
    
    spi_master_t  spi;                              /**< SPI driver object. */

    pin_name_t  chip_select;                        /**< Chip select pin descriptor (used for SPI driver). */

} nvsram2_t;

/**
 * @brief nvSRAM 2 Click configuration object.
 * @details Configuration object definition of nvSRAM 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    
    pin_name_t  miso;                                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                      /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    
    pin_name_t  hld;                                     /**< Description. */

    // static variable
    
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} nvsram2_cfg_t;

/**
 * @brief nvSRAM 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   NVSRAM2_OK = 0,
   NVSRAM2_ERROR = -1

} nvsram2_return_value_t;

/*!
 * @addtogroup nvsram2 nvSRAM 2 Click Driver
 * @brief API for configuring and manipulating nvSRAM 2 Click driver.
 * @{
 */

/**
 * @brief nvSRAM 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #nvsram2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void nvsram2_cfg_setup ( nvsram2_cfg_t *cfg );

/**
 * @brief nvSRAM 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #nvsram2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #nvsram2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nvsram2_init ( nvsram2_t *ctx, nvsram2_cfg_t *cfg );

/**
 * @brief nvSRAM 2 default configuration function.
 * @details This function executes a default configuration of nvSRAM 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #nvsram2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t nvsram2_default_cfg ( nvsram2_t *ctx );

/**
 * @brief nvSRAM 2 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #nvsram2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nvsram2_generic_write ( nvsram2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief nvSRAM 2 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #nvsram2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nvsram2_generic_read ( nvsram2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief nvSRAM 2 data enable hold operation function.
 * @details The function enables hold operation by setting the state of 
 * the HOLD ( PWM ) pin depending on the function argument.
 * @param[in] ctx : Click context object.
 * See #nvsram2_t object definition for detailed explanation.
 * @param[in] en_hold : Resume/pause serial communications with the device.
 * @return Nothing.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void nvsram2_hold ( nvsram2_t *ctx, uint8_t en_hold );

/**
 * @brief nvSRAM 2 send command function.
 * @details The function sends desired command to the CY14B101Q2A 
 * memory on nvSRAM 2 click board.
 * @param[in] ctx : Click context object.
 * See #nvsram2_t object definition for detailed explanation.
 * @param[in] cmd : 8-bit command.
 * @return Nothing.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void nvsram2_set_cmd ( nvsram2_t *ctx, uint8_t cmd );

/**
 * @brief nvSRAM 2 read status register function.
 * @details The function reads status register from 
 * the CY14B101Q2A memory on nvSRAM 2 click board.
 * @param[in] ctx : Click context object.
 * See #nvsram2_t object definition for detailed explanation.
 * @return 8-bit status.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t nvsram2_read_status ( nvsram2_t *ctx );

/**
 * @brief nvSRAM 2 fast read status register function.
 * @details The function reads status register for faster SPI speeds
 * from the CY14B101Q2A memory on nvSRAM 2 click board.
 * @param[in] ctx : Click context object.
 * See #nvsram2_t object definition for detailed explanation.
 * @return 8-bit status.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t nvsram2_fast_read_status ( nvsram2_t *ctx );

/**
 * @brief nvSRAM 2 write status register function.
 * @details The function writes status data 
 * to the CY14B101Q2A memory on nvSRAM 2 click board.
 * @param[in] ctx : Click context object.
 * See #nvsram2_t object definition for detailed explanation.
 * @param[in] data_byte : 8-bit write status data.
 * @return Nothing.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void nvsram2_write_status ( nvsram2_t *ctx, uint8_t data_byte );

/**
 * @brief nvSRAM 2 burst read function.
 * @details The function reads a sequential data starting from the targeted 
 * 17-bit register address of the CY14B101Q2A memory on nvSRAM 2 click board.
 * @param[in] ctx : Click context object.
 * See #nvsram2_t object definition for detailed explanation.
 * @param[in] mem_addr : 17-bit memory address.
 * @param[in] p_rx_data : Pointer to the memory address from which data is read.
 * @param[in] n_bytes : 8-bit number of bytes to be read.
 * @return Nothing.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void nvsram2_burst_read ( nvsram2_t *ctx, uint32_t mem_addr, uint8_t *p_rx_data, uint8_t n_bytes );

/**
 * @brief nvSRAM 2 burst write function.
 * @details The function writes a sequential data starting from the targeted 
 * 17-bit register address of the CY14B101Q2A memory on nvSRAM 2 click board.
 * @param[in] ctx : Click context object.
 * See #nvsram2_t object definition for detailed explanation.
 * @param[in] mem_addr : 17-bit memory address.
 * @param[in] p_rx_data : Pointer to the memory address from which data is read.
 * @param[in] n_bytes : 8-bit number of bytes to be read.
 * @return Nothing.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void nvsram2_burst_write ( nvsram2_t *ctx, uint32_t mem_addr, uint8_t *p_tx_data, uint8_t n_bytes );

/**
 * @brief nvSRAM 2 read ID function.
 * @details The function performs the device ID read of the CY14B101Q2A 
 * memory on nvSRAM 2 click board.
 * @param[in] ctx : Click context object.
 * See #nvsram2_t object definition for detailed explanation.
 * @return 32-bit device ID.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint32_t nvsram2_read_id ( nvsram2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // NVSRAM2_H

/*! @} */ // nvsram2

// ------------------------------------------------------------------------ END
