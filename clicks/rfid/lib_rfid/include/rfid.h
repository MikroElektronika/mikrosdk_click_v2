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
 * @file rfid.h
 * @brief This file contains API for RFID Click Driver.
 */

#ifndef RFID_H
#define RFID_H

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
#include "drv_uart.h"

/*!
 * @addtogroup rfid RFID Click Driver
 * @brief API for configuring and manipulating RFID Click driver.
 * @{
 */

/**
 * @defgroup rfid_reg RFID Registers List
 * @brief List of registers of RFID Click driver.
 */

/**
 * @addtogroup rfid_reg
 * @{
 */

/**
 * @brief RFID control bytes.
 * @details Specified register for description of RFID Click driver.
 */
#define RFID_SEND_CMD_CRTL  0x00
#define RFID_RESET_CTRL     0x01
#define RFID_READ_CTRL      0x02
#define RFID_POLL_CTRL      0x03

/*! @} */ // rfid_reg

/**
 * @defgroup rfid_set RFID Registers Settings
 * @brief Settings for registers of RFID Click driver.
 */

/**
 * @addtogroup rfid_set
 * @{
 */

/**
 * @brief RFID commands.
 * @details Specified setting for description of RFID Click driver.
 */
#define RFID_IDN            0x01
#define RFID_PROT_SELECT    0x02
#define RFID_SEND_RECV      0x04
#define RFID_IDLE           0x07
#define RFID_RD_WAKEUP_REG  0x08
#define RFID_WR_WAKEUP_REG  0x09
#define RFID_SET_BAUD       0x0A
#define RFID_ECHO           0x55

/**
 * @brief RFID protocols.
 * @details RFID protocol settings.
 */
#define RFID_FIELD_OFF      0x00
#define RFID_ISO_15693      0x01
#define RFID_ISO_14443A     0x02    
#define RFID_ISO_14443B     0x03
#define RFID_ISO_18092NFC   0x04

/**
 * @brief Communication interface.
 * @details Communication interface settings.
 */
#define RFID_UART           0x00
#define RFID_SPI            0x01

/**
 * @brief Data len.
 * @details Max data length value.
 */
#define RFID_MAX_DATA_LEN   0xFF

/**
 * @brief Data ready.
 * @details Data ready flag.
 */
#define RFID_DATA_READY     0x08
#define RFID_DATA_NOT_READY 0x00

/*! @} */ // rfid_set

/**
 * @defgroup rfid_map RFID MikroBUS Map
 * @brief MikroBUS pin mapping of RFID Click driver.
 */

/**
 * @addtogroup rfid_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RFID Click to the selected MikroBUS.
 */
#define RFID_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ssi_1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.ssi_0 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.irq_in = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.irq_out = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // rfid_map
/*! @} */ // rfid

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 500
/** \} */

/**
 * @brief RFID Click context object.
 * @details Context object definition of RFID Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t  ssi_1;       /**< Serial select pin 1. */
    digital_out_t  ssi_0;       /**< Serial select pin 0. */
    digital_out_t  irq_in;      /**< IRQ input. */

    // Input pins

    digital_in_t  irq_out;      /**< IRQ output. */

    // Modules

    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */
    
    uart_t uart;                /**< UART driver object. */

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ]; /**< UART rx buffer. */
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ]; /**< UART tx buffer. */
    
    // Variables
    
    uint8_t com_interface; /**< Communication interface */
    uint8_t rx_data[ DRV_RX_BUFFER_SIZE ]; /**< RX data buffer */

} rfid_t;

/**
 * @brief RFID Click configuration object.
 * @details Configuration object definition of RFID Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t  miso;          /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;          /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;           /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;            /**< Chip select pin descriptor for SPI driver. */
    pin_name_t  rx_pin;        /**< RX pin. */ 
    pin_name_t  tx_pin;        /**< TX pin. */

    // Additional gpio pins

    pin_name_t  ssi_1;         /**< Serial select pin 1. */
    pin_name_t  ssi_0;         /**< Serial select pin 0. */
    pin_name_t  irq_in;        /**< IRQ input. */
    pin_name_t  irq_out;       /**< IRQ output. */

    // static variable

    uint32_t                           spi_speed;   /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;    /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity; /**< Chip select pin polarity. */
    
    uint32_t          baud_rate;     /**< Clock speed. */
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      /**< Data bits. */ 
    uart_parity_t     parity_bit;    /**< Parity bit. */
    uart_stop_bits_t  stop_bit;      /**< Stop bits. */   

} rfid_cfg_t;

/**
 * @brief RFID Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   RFID_OK = 0,
   RFID_ERROR = -1

} rfid_return_value_t;

/*!
 * @addtogroup rfid RFID Click Driver
 * @brief API for configuring and manipulating RFID Click driver.
 * @{
 */

/**
 * @brief RFID configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rfid_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rfid_cfg_setup ( rfid_cfg_t *cfg );

/**
 * @brief RFID initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #rfid_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rfid_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rfid_init ( rfid_t *ctx, rfid_cfg_t *cfg );

/**
 * @brief RFID default configuration function.
 * @details This function executes a default configuration of RFID
 * Click board.
 * @param[in] ctx : Click context object.
 * See #rfid_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t rfid_default_cfg ( rfid_t *ctx );

/**
 * @brief RFID command writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected command.
 * @param[in] ctx : Click context object.
 * See #rfid_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rfid_send_command ( rfid_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );

/**
 * @brief RFID data reading function.
 * @details This function reads all available data bytes.
 * @param[in] ctx : Click context object.
 * See #rfid_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rfid_read_data ( rfid_t *ctx, uint8_t *data_out );

/**
 * @brief RFID data ready function.
 * @details This function checks if there's any data ready ( SPI mode only ).
 * @param[in] ctx : Click context object.
 * See #rfid_t object definition for detailed explanation.
 * @return @li @c  0x08 - data is ready,
 *         @li @c  0 - data is not ready.
 *
 * @note None.
 */
uint8_t rfid_data_ready ( rfid_t *ctx );

/**
 * @brief RFID reset function.
 * @details This function resets the device ( SPI mode only ).
 * @param[in] ctx : Click context object.
 * See #rfid_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rfid_reset ( rfid_t *ctx );

/**
 * @brief RFID check echo response.
 * @details This function checks the echo response.
 * @param[in] ctx : Click context object.
 * See #rfid_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rfid_check_echo ( rfid_t *ctx );

/**
 * @brief RFID calibration function.
 * @details This function calibrates the module.
 * @param[in] ctx : Click context object.
 * See #rfid_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rfid_calibration ( rfid_t *ctx );

/**
 * @brief RFID get device id function.
 * @details This function gets the device id.
 * @param[in] ctx : Click context object.
 * @param[out] device_id : Device id.
 * See #rfid_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rfid_get_device_id ( rfid_t *ctx, uint8_t *device_id );

/**
 * @brief Select communication interface.
 * @details This function selects the communication interface.
 * @param[in] ctx : Click context object.
 * See #rfid_t object definition for detailed explanation.
 * @param[in] com_interface : Communication interface ( 0x01 - SPI, 0x00 - UART ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rfid_select_communication_interface ( rfid_t* ctx, uint8_t com_interface );

/**
 * @brief Select RF communication protocol.
 * @details This function selects the RF communication protocol.
 * @param[in] ctx : Click context object.
 * @param[in] rfid_protocol : RFID protocol ( 0x02 - RFID_ISO_14443A, 0x04 - RFID_ISO_18092NFC ).
 * See #rfid_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rfid_select_rfid_protocol ( rfid_t *ctx, uint8_t rfid_protocol );

/**
 * @brief Configure IndexMod and Gain.
 * @details This function sets IndexMod and Gain in Analog Value register.
 * @param[in] ctx : Click context object.
 * See #rfid_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rfid_set_index_mod_and_gain ( rfid_t *ctx );

/**
 * @brief Configure auto detect filter.
 * @details This function sets Auto Detect filter register.
 * @param[in] ctx : Click context object.
 * See #rfid_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rfid_auto_detect_filter ( rfid_t *ctx );

/**
 * @brief RFID get RFID tag uid function.
 * @details This function gets the RFID tag uid.
 * @param[in] ctx : Click context object.
 * @param[in] rfid_protocol : RFID protocol ( 0x02 - RFID_ISO_14443A, 0x04 - RFID_ISO_18092NFC ).
 * @param[out] tag_uid : Tag uid.
 * See #rfid_t object definition for detailed explanation.
 * @return @li @c  >0 - Tag length in bytes, 
 *         @li @c  0 - No tag detected,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rfid_get_tag_uid ( rfid_t *ctx, uint8_t rfid_protocol, uint8_t *tag_uid );

#ifdef __cplusplus
}
#endif
#endif // RFID_H

/*! @} */ // rfid

// ------------------------------------------------------------------------ END
