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
 * @file lbandrtk.h
 * @brief This file contains API for LBAND RTK Click Driver.
 */

#ifndef LBANDRTK_H
#define LBANDRTK_H

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
#include "drv_i2c_master.h"
#include "drv_spi_master.h"
#include "drv_uart.h"
#include "spi_specifics.h"

/*!
 * @addtogroup lbandrtk LBAND RTK Click Driver
 * @brief API for configuring and manipulating LBAND RTK Click driver.
 * @{
 */

/**
 * @defgroup lbandrtk_set LBAND RTK Registers Settings
 * @brief Settings for registers of LBAND RTK Click driver.
 */

/**
 * @addtogroup lbandrtk_set
 * @{
 */

/**
 * @brief LBAND RTK UBX class and message IDs.
 * @details Specified UBX class and message IDs of LBAND RTK Click driver.
 */
#define LBANDRTK_CLASS_ID_UBX_ACK               0x05
#define LBANDRTK_CLASS_ID_UBX_CFG               0x06
#define LBANDRTK_CLASS_ID_UBX_INF               0x04
#define LBANDRTK_CLASS_ID_UBX_MON               0x0A
#define LBANDRTK_CLASS_ID_UBX_RXM               0x02
#define LBANDRTK_MSG_ID_UBX_ACK_ACK             0x01
#define LBANDRTK_MSG_ID_UBX_ACK_NAK             0x00
#define LBANDRTK_MSG_ID_UBX_CFG_RST             0x04
#define LBANDRTK_MSG_ID_UBX_CFG_VALDEL          0x8C
#define LBANDRTK_MSG_ID_UBX_CFG_VALGET          0x8B
#define LBANDRTK_MSG_ID_UBX_CFG_VALSET          0x8A
#define LBANDRTK_MSG_ID_UBX_INF_ERROR           0x00
#define LBANDRTK_MSG_ID_UBX_INF_NOTICE          0x02
#define LBANDRTK_MSG_ID_UBX_INF_WARNING         0x01
#define LBANDRTK_MSG_ID_UBX_MON_HW2             0x0B
#define LBANDRTK_MSG_ID_UBX_MON_VER             0x04
#define LBANDRTK_MSG_ID_UBX_RXM_PMP             0x72
#define LBANDRTK_MSG_ID_UBX_RXM_PMREQ           0x41

/**
 * @brief LBAND RTK UBX configuration items setting.
 * @details Specified UBX configuration items setting of LBAND RTK Click driver.
 */
#define LBANDRTK_VER_CFG_POLL_REQUEST           0x00
#define LBANDRTK_VER_CFG_POLLED                 0x01
#define LBANDRTK_LAYER_RAM                      0x01
#define LBANDRTK_LAYER_BBR                      0x02
#define LBANDRTK_LAYER_FLASH                    0x04
#define LBANDRTK_LAYER_ALL                      0x07
#define LBANDRTK_KEY_ID_SIZE_1_BIT              0x10000000ul
#define LBANDRTK_KEY_ID_SIZE_1_BYTE             0x20000000ul
#define LBANDRTK_KEY_ID_SIZE_2_BYTES            0x30000000ul
#define LBANDRTK_KEY_ID_SIZE_4_BYTES            0x40000000ul
#define LBANDRTK_KEY_ID_SIZE_8_BYTES            0x50000000ul
#define LBANDRTK_KEY_ID_SIZE_MASK               0x70000000ul
#define LBANDRTK_KEY_ID_GROUP_MASK              0x00FF0000ul
#define LBANDRTK_KEY_ID_ITEM_MASK               0x00000FFFul
#define LBANDRTK_CFG_PMP_CENTER_FREQUENCY       0x40B10011ul
#define LBANDRTK_CFG_PMP_SEARCH_WINDOW          0x30B10012ul
#define LBANDRTK_CFG_PMP_USE_SERVICE_ID         0x10B10016ul
#define LBANDRTK_CFG_PMP_SERVICE_ID             0x30B10017ul
#define LBANDRTK_CFG_PMP_DATA_RATE              0x30B10013ul
#define LBANDRTK_CFG_PMP_USE_DESCRAMBLER        0x10B10014ul
#define LBANDRTK_CFG_PMP_DESCRAMBLER_INIT       0x30B10015ul
#define LBANDRTK_CFG_PMP_USE_PRESCRAMBLING      0x10B10019ul
#define LBANDRTK_CFG_PMP_UNIQUE_WORD            0x50B1001Aul

/**
 * @brief LBAND RTK UBX header bytes.
 * @details Specified UBX header byte of LBAND RTK Click driver.
 */
#define LBANDRTK_PREAMBLE_SYNC_CHAR_1           0xB5
#define LBANDRTK_PREAMBLE_SYNC_CHAR_2           0x62

/**
 * @brief LBAND RTK UBX max payload size.
 * @details Specified UBX max payload size of LBAND RTK Click driver.
 */
#define LBANDRTK_MAX_PAYLOAD_LEN                528u

/**
 * @brief LBAND RTK dummy data.
 * @details Definition of dummy data.
 */
#define LBANDRTK_DUMMY                          0xFF

/**
 * @brief LBAND RTK response timeout and retries values
 * @details Specified response timeout value in milliseconds and number of retries of LBAND RTK Click driver.
 */
#define LBANDRTK_TIMEOUT                        3000u
#define LBANDRTK_NUM_OF_RETRIES                 5

/**
 * @brief LBAND RTK CFG-PMP: Point to multipoint (PMP) default configuration.
 * @details Specified CFG-PMP: Point to multipoint (PMP) default configuration of LBAND RTK Click driver.
 */
#define LBANDRTK_PMP_CENTER_FREQ_EU             1545260000ul
#define LBANDRTK_PMP_CENTER_FREQ_US             1556290000ul
#define LBANDRTK_PMP_CENTER_FREQ                LBANDRTK_PMP_CENTER_FREQ_EU
#define LBANDRTK_PMP_SEARCH_WINDOW              2200u
#define LBANDRTK_PMP_USE_SERVICE_ID             0
#define LBANDRTK_PMP_SERVICE_ID                 21845u
#define LBANDRTK_PMP_DATA_RATE                  2400u
#define LBANDRTK_PMP_USE_DESCRAMBLER            1
#define LBANDRTK_PMP_DESCRAMBLER_INIT           26969u
#define LBANDRTK_PMP_USE_PRESCRAMBLING          0
#define LBANDRTK_PMP_UNIQUE_WORD_HIGH           0xE15AE893ul
#define LBANDRTK_PMP_UNIQUE_WORD_LOW            0xE15AE893ul

/**
 * @brief LBAND RTK UBX-RXM-PMP setting.
 * @details Specified UBX-RXM-PMP setting of LBAND RTK Click driver.
 */
#define LBANDRTK_UBX_RXM_PMP_MAX_USER_DATA      504u
#define LBANDRTK_UBX_RXM_PMP_EBN0_SCALE         0.125f

/**
 * @brief LBAND RTK device address setting.
 * @details Specified setting for device slave address selection of
 * LBAND RTK Click driver.
 */
#define LBANDRTK_SET_DEV_ADDR                   0x43

/**
 * @brief LBAND RTK driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define LBANDRTK_DRV_TX_BUFFER_SIZE             ( LBANDRTK_MAX_PAYLOAD_LEN + 8 )
#define LBANDRTK_DRV_RX_BUFFER_SIZE             ( LBANDRTK_MAX_PAYLOAD_LEN + 8 )

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b lbandrtk_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define LBANDRTK_SET_DATA_SAMPLE_EDGE           SET_SPI_DATA_SAMPLE_EDGE
#define LBANDRTK_SET_DATA_SAMPLE_MIDDLE         SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // lbandrtk_set

/**
 * @defgroup lbandrtk_map LBAND RTK MikroBUS Map
 * @brief MikroBUS pin mapping of LBAND RTK Click driver.
 */

/**
 * @addtogroup lbandrtk_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LBAND RTK Click to the selected MikroBUS.
 */
#define LBANDRTK_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl    = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda    = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso   = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi   = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck    = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs     = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.ein    = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst    = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // lbandrtk_map
/*! @} */ // lbandrtk

/**
 * @brief LBAND RTK Click driver selector.
 * @details Selects target driver interface of LBAND RTK Click driver.
 */
typedef enum
{
    LBANDRTK_DRV_SEL_UART,      /**< UART driver descriptor. */
    LBANDRTK_DRV_SEL_SPI,       /**< SPI driver descriptor. */
    LBANDRTK_DRV_SEL_I2C        /**< I2C driver descriptor. */

} lbandrtk_drv_t;

/**
 * @brief LBAND RTK Click driver interface.
 * @details Definition of driver interface of LBAND RTK Click driver.
 */
typedef err_t ( *lbandrtk_master_io_t )( struct lbandrtk_s*, uint8_t*, uint16_t ); /**< Driver serial interface. */

/**
 * @brief LBAND RTK Click UBX frame union object.
 * @details UBX frame union object definition of LBAND RTK Click driver.
 */
typedef union
{
    uint8_t data_buf[ LBANDRTK_MAX_PAYLOAD_LEN + 8 ];
    struct
    {
        uint16_t header;        /**< Every frame starts with a 2-byte preamble consisting of 
                                     two synchronization characters: 0xB5 and 0x62. */
        uint8_t class_id;       /**< 1-byte message class field. A class is a group of messages that are related to each other. */
        uint8_t msg_id;         /**< 1-byte message ID field defines the message that is to follow. */
        uint16_t payload_len;   /**< 2-byte length field. The length is defined as being that of the payload only. */
        uint8_t payload[ LBANDRTK_MAX_PAYLOAD_LEN + 2 ]; /**< The payload field contains a variable number (= payload_len) of bytes.
                                                              A 2 checksum bytes are appended to the payload buffer. */
    };
    
} lbandrtk_ubx_frame_t;

/**
 * @brief LBAND RTK Click CFG-PMP: Point to multipoint (PMP) configuration object.
 * @details This is the configuration for the L-band point to multipoint (PMP) receiver.
 */
typedef struct
{
    uint32_t center_freq;       /**< The center frequency for the receiver can be set from 1525000000 to 1559000000 Hz. */
    uint16_t search_window;     /**< Search window can be set from 0 to 65535 Hz. It is +/- this value from the center
                                     frequency set by CENTER_FREQUENCY. */
    uint8_t use_service_id;     /**< Enable/disable service ID check to confirm the correct service is received. */
    uint16_t service_id;        /**< Defines the expected service ID. */
    uint16_t data_rate;         /**< The data rate of the received data in bps. */
    uint8_t use_descrambler;    /**< Enables/disables the descrambler. */
    uint16_t descrambler_init;  /**< Set the intialisation value for the descrambler. */
    uint8_t use_prescrambling;  /**< Enables/disables the prescrambling. */
    uint32_t unique_word_high;  /**< Defines value of unique word (higher 4 bytes). */
    uint32_t unique_word_low;   /**< Defines value of unique word (lower 4 bytes). */
    
} lbandrtk_pmp_cfg_t;

/**
 * @brief LBAND RTK Click context object.
 * @details Context object definition of LBAND RTK Click driver.
 */
typedef struct lbandrtk_s
{
    digital_out_t rst;          /**< Reset pin. */
    digital_out_t ein;          /**< EXTINT pin. */

    i2c_master_t  i2c;          /**< I2C driver object. */
    spi_master_t  spi;          /**< SPI driver object. */
    uart_t        uart;         /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ LBANDRTK_DRV_RX_BUFFER_SIZE ]; /**< Buffer size. */
    char uart_tx_buffer[ LBANDRTK_DRV_TX_BUFFER_SIZE ]; /**< Buffer size. */

    uint8_t     slave_address;  /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */
    lbandrtk_drv_t drv_sel;     /**< Master driver interface selector. */

    lbandrtk_master_io_t write_f;   /**< Master write function. */
    lbandrtk_master_io_t read_f;    /**< Master read function. */
    lbandrtk_ubx_frame_t frame;

} lbandrtk_t;

/**
 * @brief LBAND RTK Click configuration object.
 * @details Configuration object definition of LBAND RTK Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  miso;           /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;           /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;            /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;             /**< Chip select pin descriptor for SPI driver. */
    pin_name_t  rx_pin;         /**< RX pin. */
    pin_name_t  tx_pin;         /**< TX pin. */
    
    pin_name_t  rst;            /**< Reset pin. */
    pin_name_t  ein;            /**< EXTINT pin. */

    uint32_t    i2c_speed;      /**< I2C serial speed. */
    uint8_t     i2c_address;    /**< I2C slave address. */

    uint32_t                           spi_speed;   /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;    /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity; /**< Chip select pin polarity. */
    
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

    lbandrtk_drv_t   drv_sel;   /**< Master driver interface selector. */

} lbandrtk_cfg_t;

/**
 * @brief LBAND RTK Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LBANDRTK_OK = 0,
    LBANDRTK_ERROR = -1

} lbandrtk_return_value_t;

/*!
 * @addtogroup lbandrtk LBAND RTK Click Driver
 * @brief API for configuring and manipulating LBAND RTK Click driver.
 * @{
 */

/**
 * @brief LBAND RTK configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lbandrtk_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lbandrtk_cfg_setup ( lbandrtk_cfg_t *cfg );

/**
 * @brief LBAND RTK driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #lbandrtk_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #lbandrtk_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void lbandrtk_drv_interface_selection ( lbandrtk_cfg_t *cfg, lbandrtk_drv_t drv_sel );

/**
 * @brief LBAND RTK initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #lbandrtk_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lbandrtk_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lbandrtk_init ( lbandrtk_t *ctx, lbandrtk_cfg_t *cfg );

/**
 * @brief LBAND RTK data writing function.
 * @details This function writes a desired number of data bytes to the module.
 * @param[in] ctx : Click context object.
 * See #lbandrtk_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  >=0 - Success, or number of data bytes written in the case of UART,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lbandrtk_generic_write ( lbandrtk_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief LBAND RTK data reading function.
 * @details This function reads a desired number of data bytes from the module.
 * @param[in] ctx : Click context object.
 * See #lbandrtk_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >=0 - Number of data bytes read.
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lbandrtk_generic_read ( lbandrtk_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief LBAND RTK write ubx frame function.
 * @details This function sends the provided UBX frame to the module.
 * @param[in] ctx : Click context object.
 * See #lbandrtk_t object definition for detailed explanation.
 * @param[in,out] frame : UBX frame to send (No need for the header and checksum bytes to be set).
 * See #lbandrtk_ubx_frame_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success, or number of data bytes written in the case of UART,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lbandrtk_write_ubx_frame ( lbandrtk_t *ctx, lbandrtk_ubx_frame_t *frame );

/**
 * @brief LBAND RTK read ubx frame function.
 * @details This function waits for an UBX frame message to arrive and reads it.
 * @param[in] ctx : Click context object.
 * See #lbandrtk_t object definition for detailed explanation.
 * @param[out] frame : UBX frame message read.
 * See #lbandrtk_ubx_frame_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error or timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lbandrtk_read_ubx_frame ( lbandrtk_t *ctx, lbandrtk_ubx_frame_t *frame );

/**
 * @brief LBAND RTK set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #lbandrtk_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lbandrtk_set_rst_pin ( lbandrtk_t *ctx, uint8_t state );

/**
 * @brief LBAND RTK set ein pin function.
 * @details This function sets the EXTINT pin logic state.
 * @param[in] ctx : Click context object.
 * See #lbandrtk_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lbandrtk_set_ein_pin ( lbandrtk_t *ctx, uint8_t state );

/**
 * @brief LBAND RTK reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #lbandrtk_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void lbandrtk_reset_device ( lbandrtk_t *ctx );

/**
 * @brief LBAND RTK check ack function.
 * @details This function waits for an acknowledge UBX frame for the specifies message ID to arrive and checks it.
 * @param[in] ctx : Click context object.
 * See #lbandrtk_t object definition for detailed explanation.
 * @param[in] class_id : Class of message to check the acknowledge for.
 * @param[in] msg_id : ID of message to check the acknowledge for.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error or timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lbandrtk_check_ack ( lbandrtk_t *ctx, uint8_t class_id, uint8_t msg_id );

/**
 * @brief LBAND RTK set val 8 function.
 * @details This function sets the UBX-CFG 1-bit or 1-byte value to the selected key ID.
 * @param[in] ctx : Click context object.
 * See #lbandrtk_t object definition for detailed explanation.
 * @param[in] key_id : Configuration key ID to set.
 * @param[in] layer : Bit mask for memory layer where the value will be set.
 *                      @li @c 0x01 - RAM,
 *                      @li @c 0x02 - BBR,
 *                      @li @c 0x04 - FLASH,
 *                      @li @c 0x07 - All layers.
 * @param[in] value : Value to be set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error or timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lbandrtk_set_val_8 ( lbandrtk_t *ctx, uint32_t key_id, uint8_t layer, uint8_t value );

/**
 * @brief LBAND RTK set val 16 function.
 * @details This function sets the UBX-CFG 2-bytes value to the selected key ID.
 * @param[in] ctx : Click context object.
 * See #lbandrtk_t object definition for detailed explanation.
 * @param[in] key_id : Configuration key ID to set.
 * @param[in] layer : Bit mask for memory layer where the value will be set.
 *                      @li @c 0x01 - RAM,
 *                      @li @c 0x02 - BBR,
 *                      @li @c 0x04 - FLASH,
 *                      @li @c 0x07 - All layers.
 * @param[in] value : Value to be set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error or timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lbandrtk_set_val_16 ( lbandrtk_t *ctx, uint32_t key_id, uint8_t layer, uint16_t value );

/**
 * @brief LBAND RTK set val 32 function.
 * @details This function sets the UBX-CFG 4-bytes value to the selected key ID.
 * @param[in] ctx : Click context object.
 * See #lbandrtk_t object definition for detailed explanation.
 * @param[in] key_id : Configuration key ID to set.
 * @param[in] layer : Bit mask for memory layer where the value will be set.
 *                      @li @c 0x01 - RAM,
 *                      @li @c 0x02 - BBR,
 *                      @li @c 0x04 - FLASH,
 *                      @li @c 0x07 - All layers.
 * @param[in] value : Value to be set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error or timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lbandrtk_set_val_32 ( lbandrtk_t *ctx, uint32_t key_id, uint8_t layer, uint32_t value );

/**
 * @brief LBAND RTK set val 64 function.
 * @details This function sets the UBX-CFG 8-bytes value to the selected key ID.
 * @param[in] ctx : Click context object.
 * See #lbandrtk_t object definition for detailed explanation.
 * @param[in] key_id : Configuration key ID to set.
 * @param[in] layer : Bit mask for memory layer where the value will be set.
 *                      @li @c 0x01 - RAM,
 *                      @li @c 0x02 - BBR,
 *                      @li @c 0x04 - FLASH,
 *                      @li @c 0x07 - All layers.
 * @param[in] value_high : 4 higher bytes of value to be set.
 * @param[in] value_low : 4 lower bytes of value to be set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error or timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lbandrtk_set_val_64 ( lbandrtk_t *ctx, uint32_t key_id, uint8_t layer, uint32_t value_high, uint32_t value_low );

/**
 * @brief LBAND RTK get val 8 function.
 * @details This function reads the UBX-CFG 1-bit or 1-byte value from the selected key ID.
 * @param[in] ctx : Click context object.
 * See #lbandrtk_t object definition for detailed explanation.
 * @param[in] key_id : Configuration key ID to read.
 * @param[in] layer : Memory layer where the value will be read from (Only one layer could be selected).
 *                      @li @c 0x01 - RAM,
 *                      @li @c 0x02 - BBR,
 *                      @li @c 0x04 - FLASH.
 * @param[out] value : Output value read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error or timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lbandrtk_get_val_8 ( lbandrtk_t *ctx, uint32_t key_id, uint8_t layer, uint8_t *value );

/**
 * @brief LBAND RTK get val 16 function.
 * @details This function reads the UBX-CFG 2-bytes value from the selected key ID.
 * @param[in] ctx : Click context object.
 * See #lbandrtk_t object definition for detailed explanation.
 * @param[in] key_id : Configuration key ID to read.
 * @param[in] layer : Memory layer where the value will be read from (Only one layer could be selected).
 *                      @li @c 0x01 - RAM,
 *                      @li @c 0x02 - BBR,
 *                      @li @c 0x04 - FLASH.
 * @param[out] value : Output value read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error or timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lbandrtk_get_val_16 ( lbandrtk_t *ctx, uint32_t key_id, uint8_t layer, uint16_t *value );

/**
 * @brief LBAND RTK get val 32 function.
 * @details This function reads the UBX-CFG 4-bytes value from the selected key ID.
 * @param[in] ctx : Click context object.
 * See #lbandrtk_t object definition for detailed explanation.
 * @param[in] key_id : Configuration key ID to read.
 * @param[in] layer : Memory layer where the value will be read from (Only one layer could be selected).
 *                      @li @c 0x01 - RAM,
 *                      @li @c 0x02 - BBR,
 *                      @li @c 0x04 - FLASH.
 * @param[out] value : Output value read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error or timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lbandrtk_get_val_32 ( lbandrtk_t *ctx, uint32_t key_id, uint8_t layer, uint32_t *value );

/**
 * @brief LBAND RTK get val 64 function.
 * @details This function reads the UBX-CFG 8-bytes value from the selected key ID.
 * @param[in] ctx : Click context object.
 * See #lbandrtk_t object definition for detailed explanation.
 * @param[in] key_id : Configuration key ID to read.
 * @param[in] layer : Memory layer where the value will be read from (Only one layer could be selected).
 *                      @li @c 0x01 - RAM,
 *                      @li @c 0x02 - BBR,
 *                      @li @c 0x04 - FLASH.
 * @param[out] value_high : 4 higher bytes of value read.
 * @param[out] value_low : 4 lower bytes of value read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error or timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lbandrtk_get_val_64 ( lbandrtk_t *ctx, uint32_t key_id, uint8_t layer, uint32_t *value_high, uint32_t *value_low );

/**
 * @brief LBAND RTK set default pmp cfg function.
 * @details This function sets the Point to multipoint (PMP) to default configuration to RAM layer.
 * @param[in] ctx : Click context object.
 * See #lbandrtk_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error or timeout.
 * See #err_t definition for detailed explanation.
 * @note Refer to LBANDRTK_PMP_x macros definition if you want to check or change the default configuration.
 */
err_t lbandrtk_set_default_pmp_cfg ( lbandrtk_t *ctx );

/**
 * @brief LBAND RTK set pmp cfg function.
 * @details This function sets the specified Point to multipoint (PMP) configuration to RAM layer.
 * @param[in] ctx : Click context object.
 * See #lbandrtk_t object definition for detailed explanation.
 * @param[in] pmp_cfg : Point to multipoint (PMP) configuration structure to be set.
 * See #lbandrtk_pmp_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error or timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lbandrtk_set_pmp_cfg ( lbandrtk_t *ctx, lbandrtk_pmp_cfg_t pmp_cfg );

/**
 * @brief LBAND RTK get pmp cfg function.
 * @details This function reads the Point to multipoint (PMP) configuration from RAM layer.
 * @param[in] ctx : Click context object.
 * See #lbandrtk_t object definition for detailed explanation.
 * @param[out] pmp_cfg : Point to multipoint (PMP) configuration structure read.
 * See #lbandrtk_pmp_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error or timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lbandrtk_get_pmp_cfg ( lbandrtk_t *ctx, lbandrtk_pmp_cfg_t *pmp_cfg );

#ifdef __cplusplus
}
#endif
#endif // LBANDRTK_H

/*! @} */ // lbandrtk

// ------------------------------------------------------------------------ END
