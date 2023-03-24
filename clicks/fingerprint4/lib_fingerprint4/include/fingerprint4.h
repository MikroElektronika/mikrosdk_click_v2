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
 * @file fingerprint4.h
 * @brief This file contains API for Fingerprint 4 Click Driver.
 */

#ifndef FINGERPRINT4_H
#define FINGERPRINT4_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"
#include "drv_uart.h"

/*!
 * @addtogroup fingerprint4 Fingerprint 4 Click Driver
 * @brief API for configuring and manipulating Fingerprint 4 Click driver.
 * @{
 */

/**
 * @defgroup fingerprint4_reg Fingerprint 4 Registers List
 * @brief List of registers of Fingerprint 4 Click driver.
 */

/**
 * @addtogroup fingerprint4_reg
 * @{
 */

/**
 * @brief Fingerprint 4 HCP command list.
 * @details Specified HCP command list of Fingerprint 4 Click driver.
 */
#define FINGERPRINT4_CMD_NONE                   0x0000
#define FINGERPRINT4_CMD_CAPTURE                0x0001
#define FINGERPRINT4_CMD_ENROLL                 0x0002
#define FINGERPRINT4_CMD_IDENTIFY               0x0003
#define FINGERPRINT4_CMD_MATCH                  0x0004
#define FINGERPRINT4_CMD_IMAGE                  0x0005
#define FINGERPRINT4_CMD_TEMPLATE               0x0006
#define FINGERPRINT4_CMD_WAIT                   0x0007
#define FINGERPRINT4_CMD_SETTINGS               0x0008
#define FINGERPRINT4_CMD_NAVIGATE               0x1001
#define FINGERPRINT4_CMD_SENSOR                 0x1002
#define FINGERPRINT4_CMD_DEADPIXELS             0x1003
#define FINGERPRINT4_CMD_CONNECT                0x2001
#define FINGERPRINT4_CMD_RECONNECT              0x2002
#define FINGERPRINT4_CMD_RESET                  0x3002
#define FINGERPRINT4_CMD_CANCEL                 0x3003
#define FINGERPRINT4_CMD_INFO                   0x3004
#define FINGERPRINT4_CMD_STORAGE_TEMPLATE       0x4002
#define FINGERPRINT4_CMD_STORAGE_CALIBRATION    0x4003
#define FINGERPRINT4_CMD_STORAGE_LOG            0x4004
#define FINGERPRINT4_CMD_STORAGE_SETTINGS       0x4005
#define FINGERPRINT4_CMD_TEST                   0x5001
#define FINGERPRINT4_CMD_MCU                    0x5002
#define FINGERPRINT4_CMD_GPIO                   0x5003
#define FINGERPRINT4_CMD_COMMUNICATION          0x6001
#define FINGERPRINT4_CMD_APP_BASE               0xE000
#define FINGERPRINT4_CMD_DIAG                   0xF003
#define FINGERPRINT4_CMD_FFFF                   0xFFFF

/**
 * @brief Fingerprint 4 HCP argument list.
 * @details Specified HCP argument list of Fingerprint 4 Click driver.
 */
#define FINGERPRINT4_ARG_NONE                   0x0000
#define FINGERPRINT4_ARG_FINGER_DOWN            0x0001
#define FINGERPRINT4_ARG_FINGER_UP              0x0002
#define FINGERPRINT4_ARG_START                  0x0003
#define FINGERPRINT4_ARG_ADD                    0x0004
#define FINGERPRINT4_ARG_FINISH                 0x0005
#define FINGERPRINT4_ARG_ID                     0x0006
#define FINGERPRINT4_ARG_ALL                    0x0007
#define FINGERPRINT4_ARG_EXTRACT                0x0008
#define FINGERPRINT4_ARG_MATCH_IMAGE            0x0009
#define FINGERPRINT4_ARG_MATCH                  0x000A
#define FINGERPRINT4_ARG_ACQUIRE                0x1001
#define FINGERPRINT4_ARG_RELEASE                0x1002
#define FINGERPRINT4_ARG_SET                    0x1003
#define FINGERPRINT4_ARG_GET                    0x1004
#define FINGERPRINT4_ARG_UPLOAD                 0x1005
#define FINGERPRINT4_ARG_DOWNLOAD               0x1006
#define FINGERPRINT4_ARG_CREATE                 0x1007
#define FINGERPRINT4_ARG_SAVE                   0x1008
#define FINGERPRINT4_ARG_DELETE                 0x1009
#define FINGERPRINT4_ARG_DATA                   0x100A
#define FINGERPRINT4_ARG_UPDATE                 0x100B
#define FINGERPRINT4_ARG_SEQ_NR                 0x100C
#define FINGERPRINT4_ARG_SEQ_LEN                0x100D
#define FINGERPRINT4_ARG_RESULT                 0x2001
#define FINGERPRINT4_ARG_COUNT                  0x2002
#define FINGERPRINT4_ARG_SIZE                   0x2003
#define FINGERPRINT4_ARG_LEVEL                  0x2004
#define FINGERPRINT4_ARG_FORMAT                 0x2005
#define FINGERPRINT4_ARG_FLAG                   0x2006
#define FINGERPRINT4_ARG_PROPERTIES             0x2007
#define FINGERPRINT4_ARG_SPEED                  0x2008
#define FINGERPRINT4_ARG_PROD_TEST              0x2009
#define FINGERPRINT4_ARG_SENSOR_TYPE            0x3001
#define FINGERPRINT4_ARG_WIDTH                  0x3002
#define FINGERPRINT4_ARG_HEIGHT                 0x3003
#define FINGERPRINT4_ARG_RESET                  0x3004
#define FINGERPRINT4_ARG_DPI                    0x3005
#define FINGERPRINT4_ARG_MAX_SPI_CLOCK          0x3006
#define FINGERPRINT4_ARG_NUM_SUB_AREAS_WIDTH    0x3007
#define FINGERPRINT4_ARG_NUM_SUB_AREAS_HEIGHT   0x3008
#define FINGERPRINT4_ARG_IRQ_STATUS             0x3009
#define FINGERPRINT4_ARG_RESET_HARD             0x300A
#define FINGERPRINT4_ARG_IDLE                   0x4001
#define FINGERPRINT4_ARG_SLEEP                  0x4002
#define FINGERPRINT4_ARG_DEEP_SLEEP             0x4003
#define FINGERPRINT4_ARG_POWER_MODE             0x4004
#define FINGERPRINT4_ARG_BUSY_WAIT              0x4005
#define FINGERPRINT4_ARG_TIMEOUT                0x5001
#define FINGERPRINT4_ARG_DONE                   0x5002
#define FINGERPRINT4_ARG_BOOT                   0x6001
#define FINGERPRINT4_ARG_STATUS                 0x6002
#define FINGERPRINT4_ARG_VERSION                0x6003
#define FINGERPRINT4_ARG_UNIQUE_ID              0x6004
#define FINGERPRINT4_ARG_APP_BASE               0x7000
#define FINGERPRINT4_ARG_NONCE                  0x8001
#define FINGERPRINT4_ARG_MAC                    0x8002
#define FINGERPRINT4_ARG_RANDOM                 0x8003
#define FINGERPRINT4_ARG_CLAIM                  0x8004
#define FINGERPRINT4_ARG_PUBLIC_KEY             0x8005
#define FINGERPRINT4_ARG_CIPHERTEXT             0x8006
#define FINGERPRINT4_ARG_MTU                    0x9001
#define FINGERPRINT4_ARG_STACK                  0xE001
#define FINGERPRINT4_ARG_FILL                   0xE002
#define FINGERPRINT4_ARG_HEAP                   0xE003
#define FINGERPRINT4_ARG_MODE                   0xF001
#define FINGERPRINT4_ARG_DEBUG                  0xF002
#define FINGERPRINT4_ARG_FFFF                   0xFFFF

/*! @} */ // fingerprint4_reg

/**
 * @defgroup fingerprint4_set Fingerprint 4 Registers Settings
 * @brief Settings for registers of Fingerprint 4 Click driver.
 */

/**
 * @addtogroup fingerprint4_set
 * @{
 */

/**
 * @brief Fingerprint 4 buffers size setting.
 * @details Specified setting for buffers size of Fingerprint 4 Click driver.
 */
#define FINGERPRINT4_ARG_PAYLOAD_MAX_SIZE       234
#define FINGERPRINT4_PHY_MTU_SIZE               256
#define FINGERPRINT4_TRANSPORT_LAYER_PLD_SIZE   242

/**
 * @brief Fingerprint 4 communication acknowledge bytes.
 * @details Specified communication acknowledge bytes of Fingerprint 4 Click driver.
 */
#define FINGERPRINT4_ACK_BYTES                  0x7F01FF7Ful

/**
 * @brief Fingerprint 4 capture images number setting.
 * @details Specified setting for capture images number of Fingerprint 4 Click driver.
 */
#define FINGERPRINT4_NUM_IMAGES                 3

/**
 * @brief Fingerprint 4 timeout setting.
 * @details Specified setting for timeout of Fingerprint 4 Click driver.
 */
#define FINGERPRINT4_DEFAULT_PHY_RX_TIMEOUT_MS  3000
#define FINGERPRINT4_INFINITE_TIMEOUT           0

/**
 * @brief Fingerprint 4 driver interface selection setting.
 * @details Specified setting for driver interface selection of Fingerprint 4 Click driver.
 */
#define FINGERPRINT4_DRV_INTERFACE_UART         0
#define FINGERPRINT4_DRV_INTERFACE_SPI          1
#define FINGERPRINT4_DRV_INTERFACE              FINGERPRINT4_DRV_INTERFACE_SPI

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b fingerprint4_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define FINGERPRINT4_SET_DATA_SAMPLE_EDGE       SET_SPI_DATA_SAMPLE_EDGE
#define FINGERPRINT4_SET_DATA_SAMPLE_MIDDLE     SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // fingerprint4_set

/**
 * @defgroup fingerprint4_map Fingerprint 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Fingerprint 4 Click driver.
 */

/**
 * @addtogroup fingerprint4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Fingerprint 4 Click to the selected MikroBUS.
 */
#if ( FINGERPRINT4_DRV_INTERFACE == FINGERPRINT4_DRV_INTERFACE_SPI )
#define FINGERPRINT4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.irq  = MIKROBUS( mikrobus, MIKROBUS_INT )
#elif ( FINGERPRINT4_DRV_INTERFACE == FINGERPRINT4_DRV_INTERFACE_UART )
#define FINGERPRINT4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST );
#endif

/*! @} */ // fingerprint4_map
/*! @} */ // fingerprint4

/**
 * @brief Fingerprint 4 Click HCP argument data object.
 * @details HCP argument data object definition of Fingerprint 4 Click driver.
 */
typedef struct
{
    uint16_t arg;           /**< Argument. */
    uint16_t size;          /**< Size of data. */
    uint8_t payload[ FINGERPRINT4_ARG_PAYLOAD_MAX_SIZE ];   /**< HCP argument payload. */
    
} fingerprint4_hcp_arg_data_t;

/**
 * @brief Fingerprint 4 Click HCP packet object.
 * @details HCP packet object definition of Fingerprint 4 Click driver.
 */
typedef struct
{
    uint16_t cmd_id;        /**< Command ID. */
    uint16_t num_args;      /**< Number of arguments. */
    uint8_t args[ FINGERPRINT4_ARG_PAYLOAD_MAX_SIZE + 4 ];  /**< HCP argument data. */
    
} fingerprint4_hcp_packet_t;

/**
 * @brief Fingerprint 4 Click PHY packet object.
 * @details PHY packet object definition of Fingerprint 4 Click driver.
 */
typedef struct
{
    uint16_t lnk_chn;       /**< Link layer channel. */
    uint16_t lnk_size;      /**< Link layer payload size. */
    uint16_t t_size;        /**< Transport layer payload size. */
    uint16_t t_seq_nr;      /**< Transport layer the current packet chunk number. */
    uint16_t t_seq_len;     /**< Transport layer the total number of chunks. */
    fingerprint4_hcp_packet_t hcp_packet;   /**< Transport layer payload or HCP packet data. */
    uint32_t crc;           /**< CRC word. */
   
} fingerprint4_packet_t;

/**
 * @brief Fingerprint 4 Click context object.
 * @details Context object definition of Fingerprint 4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin (Active low). */
#if ( FINGERPRINT4_DRV_INTERFACE == FINGERPRINT4_DRV_INTERFACE_SPI )
    // Input pins
    digital_in_t irq;           /**< Interrupt pin. */
    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */
#elif ( FINGERPRINT4_DRV_INTERFACE == FINGERPRINT4_DRV_INTERFACE_UART )
    // Modules
    uart_t uart;                /**< UART driver object. */
    
    // Buffers
    char uart_rx_buffer[ FINGERPRINT4_PHY_MTU_SIZE ]; /**< Buffer size. */
    char uart_tx_buffer[ FINGERPRINT4_PHY_MTU_SIZE ]; /**< Buffer size. */
#endif
    uint32_t phy_rx_timeout;    /** Receive timeout (msec). Applies ONLY to receiving packets on physical layer. */
    
    fingerprint4_hcp_arg_data_t arg;    /** Values of last argument pulled by fingerprint4_get_arg. 
                                            Values are valid only right after fingerprint4_get_arg() call. */
    fingerprint4_packet_t phy_pkt;      /** Physical layer packet object. */

} fingerprint4_t;

/**
 * @brief Fingerprint 4 Click configuration object.
 * @details Configuration object definition of Fingerprint 4 Click driver.
 */
typedef struct
{
#if ( FINGERPRINT4_DRV_INTERFACE == FINGERPRINT4_DRV_INTERFACE_SPI )
    // Communication gpio pins    
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */
    
    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */
    
    // Additional gpio pins
    pin_name_t rst;             /**< Reset pin (Active low). */
    pin_name_t irq;             /**< Interrupt pin. */
#elif ( FINGERPRINT4_DRV_INTERFACE == FINGERPRINT4_DRV_INTERFACE_UART )
    // Communication gpio pins    
    pin_name_t rx_pin;          /**< RX pin. */
    pin_name_t tx_pin;          /**< TX pin. */
    
    // static variable
    uint32_t         baud_rate;         /**< Clock speed. */
    bool             uart_blocking;     /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;          /**< Data bits. */
    uart_parity_t    parity_bit;        /**< Parity bit. */
    uart_stop_bits_t stop_bit;          /**< Stop bits. */
    
    // Additional gpio pins
    pin_name_t rst;             /**< Reset pin (Active low). */
#endif

} fingerprint4_cfg_t;

/**
 * @brief Fingerprint 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    FINGERPRINT4_RES_OK = 0,                        /**< No errors occurred. */
    FINGERPRINT4_RES_ERROR = -1,                    /**< General error. */
    FINGERPRINT4_RES_INTERNAL_ERROR = -2,           /**< Internal error. */
    FINGERPRINT4_RES_INVALID_ARGUMENT = -3,         /**< Invalid argument. */
    FINGERPRINT4_RES_NOT_IMPLEMENTED = -4,          /**< The functionality is not implemented. */
    FINGERPRINT4_RES_CANCELLED = -5,                /**< The operation was cancelled. */
    FINGERPRINT4_RES_NO_MEMORY = -6,                /**< Out of memory. */
    FINGERPRINT4_RES_NO_RESOURCE = -7,              /**< Resources are not available. */
    FINGERPRINT4_RES_IO_ERROR = -8,                 /**< An I/O error occurred. */
    FINGERPRINT4_RES_BROKEN_SENSOR = -9,            /**< Sensor is broken. */
    FINGERPRINT4_RES_WRONG_STATE = -10,             /**< The operation cannot be performed in the current state. */
    FINGERPRINT4_RES_TIMEOUT = -11,                 /**< The operation timed out. */
    FINGERPRINT4_RES_ID_NOT_UNIQUE = -12,           /**< The ID is not unique. */
    FINGERPRINT4_RES_ID_NOT_FOUND = -13,            /**< The ID is not found. */
    FINGERPRINT4_RES_INVALID_FORMAT = -14,          /**< The format is invalid. */
    FINGERPRINT4_RES_IMAGE_CAPTURE_ERROR = -15,     /**< An image capture error occurred. */
    FINGERPRINT4_RES_SENSOR_MISMATCH = -16,         /**< Sensor hardware id or sensor configuration mismatch. */
    FINGERPRINT4_RES_INVALID_PARAMETER = -17,       /**< Invalid parameter. */
    FINGERPRINT4_RES_MISSING_TEMPLATE = -18,        /**< Missing Template. */
    FINGERPRINT4_RES_INVALID_CALIBRATION = -19,     /**< Invalid Calibration.*/
    FINGERPRINT4_RES_STORAGE_NOT_FORMATTED = -20,   /**< Calibration/template storage not formatted.*/
    FINGERPRINT4_RES_SENSOR_NOT_INITIALIZED = -21,  /**< Sensor hasn't been initialized. */
    FINGERPRINT4_RES_TOO_MANY_BAD_IMAGES = -22,     /**< Enroll fail after too many bad images. */
    FINGERPRINT4_RES_CRYPTO_ERROR = -23,            /**< Cryptographic operation failed. */
    FINGERPRINT4_RES_NOT_SUPPORTED = -24,           /**< The functionality is not supported. */
    FINGERPRINT4_RES_FINGER_NOT_STABLE = -25,       /**< Finger not stable during image capture. */
    FINGERPRINT4_RES_NOT_INITIALIZED = -26,         /**< The functionality could not be used before it's initialized. */

} fingerprint4_return_value_t;

/*!
 * @addtogroup fingerprint4 Fingerprint 4 Click Driver
 * @brief API for configuring and manipulating Fingerprint 4 Click driver.
 * @{
 */

/**
 * @brief Fingerprint 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #fingerprint4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void fingerprint4_cfg_setup ( fingerprint4_cfg_t *cfg );

/**
 * @brief Fingerprint 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #fingerprint4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_init ( fingerprint4_t *ctx, fingerprint4_cfg_t *cfg );

/**
 * @brief Fingerprint 4 data writing function.
 * @details This function writes a desired number of data bytes by using @b FINGERPRINT4_DRV_INTERFACE serial interface.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_generic_write ( fingerprint4_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief Fingerprint 4 data reading function.
 * @details This function reads a desired number of data bytes by using @b FINGERPRINT4_DRV_INTERFACE serial interface.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_generic_read ( fingerprint4_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief Fingerprint 4 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void fingerprint4_set_rst_pin ( fingerprint4_t *ctx, uint8_t state );

#if ( FINGERPRINT4_DRV_INTERFACE == FINGERPRINT4_DRV_INTERFACE_SPI )
/**
 * @brief Fingerprint 4 get irq pin function.
 * @details This function returns the IRQ pin logic state.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t fingerprint4_get_irq_pin ( fingerprint4_t *ctx );
#endif

/**
 * @brief Fingerprint 4 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void fingerprint4_reset_device ( fingerprint4_t *ctx );

/**
 * @brief Fingerprint 4 init cmd function.
 * @details This function initializes a new HCP command in the @b ctx->phy_pkt.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @param[in] cmd : HCP command word.
 * @param[in] arg_key : HCP argument word for the selected command without parameters.
 * Use @b FINGERPRINT4_ARG_NONE and add arguments with @b fingerprint4_add_arg() if you need to add argument with parameter.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_init_cmd ( fingerprint4_t *ctx, uint16_t cmd, uint16_t arg_key );

/**
 * @brief Fingerprint 4 add arg function.
 * @details This function adds an argument to the HCP command in the @b ctx->phy_pkt. 
 * Must be used only after the command is initialized with @b fingerprint4_init_cmd().
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @param[in] arg_key : HCP argument key word.
 * @param[in] arg_data : HCP argument data payload.
 * @param[in] arg_size : HCP argument payload size.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_add_arg ( fingerprint4_t *ctx, uint16_t arg_key, void *arg_data, uint16_t arg_size );

/**
 * @brief Fingerprint 4 get arg function.
 * @details This function searches for the selected argument in the @b ctx->phy_pkt. 
 * If found, it will be stored in the @b ctx->arg.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @param[in] arg_key : HCP argument key word to search for.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_get_arg ( fingerprint4_t *ctx, uint16_t arg_key );

/**
 * @brief Fingerprint 4 copy arg function.
 * @details This function searches for the selected argument in the @b ctx->phy_pkt. 
 * If found, it will be stored in the @b ctx->arg, and @b arg_size bytes will be copied in the @b arg_data.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @param[in] arg_key : HCP argument key word to search for.
 * @param[out] arg_data : Pointer to memory where to copy argument payload.
 * @param[in] arg_size : Number of bytes to copy from argument payload to @b arg_data.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_copy_arg ( fingerprint4_t *ctx, uint16_t arg_key, void *arg_data, uint16_t arg_size );

/**
 * @brief Fingerprint 4 transceive function.
 * @details This function sends a prepared command packet to the sensor and reads the answer. 
 * The @b FINGERPRINT4_ARG_RESULT answer will be stored in the @b ctx->arg. Some commands do not return
 * result in @b FINGERPRINT4_ARG_RESULT. They return data with some other argument instead.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_transceive ( fingerprint4_t *ctx );

/**
 * @brief Fingerprint 4 receive function.
 * @details This function reads the answer from the sensor. 
 * The result will be stored in the @b ctx->phy_pkt.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_receive ( fingerprint4_t *ctx );

/**
 * @brief Fingerprint 4 send function.
 * @details This function sends a prepared command packet to the sensor. 
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_send ( fingerprint4_t *ctx );

/**
 * @brief Fingerprint 4 send cmd function.
 * @details This function builds and sends the command packet to the sensor. 
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @param[in] cmd : HCP command word.
 * @param[in] arg_key : HCP argument word for the selected command without parameters.
 * Set to @b FINGERPRINT4_ARG_NONE if the command has no argument.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_send_cmd ( fingerprint4_t *ctx, uint16_t cmd, uint16_t arg_key );

/**
 * @brief Fingerprint 4 send cmd arg function.
 * @details This function builds and sends to the sensor the command packet with additional argument with parameters. 
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @param[in] cmd : HCP command word.
 * @param[in] arg1_key : HCP argument 1 word for the selected command without parameters.
 * Set to @b FINGERPRINT4_ARG_NONE if the command has no argument without parameter.
 * @param[in] arg2_key : HCP argument 2 word for the selected command.
 * @param[in] arg2_data : HCP argument 2 data payload. Set to 0 if the argument 2 has no parameter.
 * @param[in] arg2_length : HCP argument 2 data length. Set to 0 if the argument 2 has no parameter.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_send_cmd_arg ( fingerprint4_t *ctx, uint16_t cmd, uint16_t arg1_key, 
                                  uint16_t arg2_key, void *arg2_data, uint16_t arg2_length );

/**
 * @brief Fingerprint 4 identify finger function.
 * @details This function captures and identifies finger against existing templates in Flash storage. 
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @param[in] timeout : Timeout in milliseconds. Set to 0 for waiting indefinitely.
 * @param[out] template_id : Pointer for matched template ID.
 * @param[out] match : Pointer to match result. @li @c 1 - Match,
 *                                              @li @c 0 - No match.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_identify_finger ( fingerprint4_t *ctx, uint32_t timeout, uint16_t *template_id, bool *match );

/**
 * @brief Fingerprint 4 wait finger present function.
 * @details This function waits in Wait-for-finger mode until a finger is detected on the sensor.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @param[in] timeout : Timeout in milliseconds. Set to 0 for waiting indefinitely.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_wait_finger_present ( fingerprint4_t *ctx, uint32_t timeout );

/**
 * @brief Fingerprint 4 wait finger not present function.
 * @details This function waits until no finger is detected on the sensor.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @param[in] timeout : Timeout in milliseconds. Set to 0 for waiting indefinitely.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_wait_finger_not_present ( fingerprint4_t *ctx, uint32_t timeout );

/**
 * @brief Fingerprint 4 image get size function.
 * @details This function reads the size of a captured image. 
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @param[out] size : Size of a captured image.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_image_get_size ( fingerprint4_t *ctx, uint32_t *size );

/**
 * @brief Fingerprint 4 image create function.
 * @details This function allocates image buffer on the sensor. 
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_image_create ( fingerprint4_t *ctx );

/**
 * @brief Fingerprint 4 image delete function.
 * @details This function deletes image buffer on the sensor. 
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_image_delete ( fingerprint4_t *ctx );

/**
 * @brief Fingerprint 4 image get function.
 * @details This function pulls captured image from the sensor. 
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to image buffer.
 * @param[in] size : Size of the image buffer. If buffer size is not enough the image will be truncated.
 * The @b ctx->arg.size will contain the real size of the image.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_image_get ( fingerprint4_t *ctx, uint8_t *data_out, uint32_t size );

/**
 * @brief Fingerprint 4 image put function.
 * @details This function push image to the sensor. 
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @param[in] data_in : Pointer to image buffer.
 * @param[in] size : Size of the image buffer.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_image_put ( fingerprint4_t *ctx, uint8_t *data_in, uint32_t size );

/**
 * @brief Fingerprint 4 image extract function.
 * @details This function extracts features from an image into a template.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_image_extract ( fingerprint4_t *ctx );

/**
 * @brief Fingerprint 4 identify function.
 * @details This function runs an identification of the template in memory against the templates in storage.
 * Extracts features from an image into a template.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_identify ( fingerprint4_t *ctx );

/**
 * @brief Fingerprint 4 template save function.
 * @details This function stores the enrolled template template ID to the Flash storage.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @param[in] template_id : The enrolled template ID.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_template_save ( fingerprint4_t *ctx, uint16_t template_id );

/**
 * @brief Fingerprint 4 template remove ram function.
 * @details This function removes template from RAM.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_template_remove_ram ( fingerprint4_t *ctx );

/**
 * @brief Fingerprint 4 template get function.
 * @details This function pulls template stored in RAM from the sensor.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to template buffer.
 * @param[in] size : Size of the template buffer. If buffer size is not enough the template will be truncated.
 * The @b ctx->arg.size will contain the real size of the template.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_template_get ( fingerprint4_t *ctx, uint8_t *data_out, uint32_t size );

/**
 * @brief Fingerprint 4 template put function.
 * @details This function push template to the sensor and stores it to the RAM.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @param[in] data_in : Pointer to template buffer.
 * @param[in] size : Size of the template buffer.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_template_put ( fingerprint4_t *ctx, uint8_t *data_in, uint16_t size );

/**
 * @brief Fingerprint 4 template remove function.
 * @details This function deletes from the Flash storage the template with the provided ID.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @param[in] template_id : The template ID to remove.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_template_remove ( fingerprint4_t *ctx, uint16_t template_id );

/**
 * @brief Fingerprint 4 template remove all function.
 * @details This function deletes all templates from the Flash storage.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_template_remove_all ( fingerprint4_t *ctx );

/**
 * @brief Fingerprint 4 template load storage function.
 * @details This function copies template with the provided ID from Flash storage to RAM.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @param[in] template_id : The template ID to copy.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_template_load_storage ( fingerprint4_t *ctx, uint16_t template_id );

/**
 * @brief Fingerprint 4 template get count function.
 * @details This function reads the number of templates in the Flash storage.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @param[out] count : The number of templates in the Flash storage.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_template_get_count ( fingerprint4_t *ctx, uint16_t *count );

/**
 * @brief Fingerprint 4 template get ids function.
 * @details This function get array of template IDs stored in the Flash storage.
 * @b ctx->arg.payload - pointer to array of uint16_t of IDs
 * @b ctx->arg.size - length of the array (in bytes). For calculating number of templates divide it by 2.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_template_get_ids ( fingerprint4_t *ctx );

/**
 * @brief Fingerprint 4 sw reset function.
 * @details This function performs the software reset of the sensor.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_sw_reset ( fingerprint4_t *ctx );

/**
 * @brief Fingerprint 4 sensor calibrate function.
 * @details This function calibrate the sensor and store the calibration data to the Flash storage.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_sensor_calibrate ( fingerprint4_t *ctx );

/**
 * @brief Fingerprint 4 sensor calibrate remove function.
 * @details This function removes the sensor calibration data from the Flash storage.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_sensor_calibrate_remove ( fingerprint4_t *ctx );

/**
 * @brief Fingerprint 4 version function.
 * @details This function reads out version information from the device. The response contains a variable
 * length string that contains version information of the device.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @param[out] version : Pointer to data buffer where the version info will be stored.
 * @param[in] len : Size of the data buffer. If buffer size is not enough the data will be truncated.
 * The @b ctx->arg.size will contain the real size of the data.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_version ( fingerprint4_t *ctx, char *version, uint8_t len );

/**
 * @brief Fingerprint 4 version function.
 * @details This function reads out unique ID information from the device. The response contains 12 bytes
 * of LSB data that contains unique ID information of the device.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @param[out] unique_id : Pointer to data buffer where the unique ID info will be stored.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_unique_id_get ( fingerprint4_t *ctx, uint8_t *unique_id );

/**
 * @brief Fingerprint 4 uart speed set function.
 * @details This function sets requested UART communication speed.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @param[in] speed : UART speed.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_uart_speed_set ( fingerprint4_t *ctx, uint32_t speed );

/**
 * @brief Fingerprint 4 uart speed get function.
 * @details This function gets current UART communication speed.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @param[out] speed : UART speed.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_uart_speed_get ( fingerprint4_t *ctx, uint32_t *speed );

/**
 * @brief Fingerprint 4 sensor reset function.
 * @details This function performs a reset of the sensor.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint4_sensor_reset ( fingerprint4_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // FINGERPRINT4_H

/*! @} */ // fingerprint4

// ------------------------------------------------------------------------ END
