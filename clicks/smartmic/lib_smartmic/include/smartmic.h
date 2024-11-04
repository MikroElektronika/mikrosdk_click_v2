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
 * @file smartmic.h
 * @brief This file contains API for Smart Mic Click Driver.
 */

#ifndef SMARTMIC_H
#define SMARTMIC_H

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
#include "drv_uart.h"
#include "drv_i2c_master.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup smartmic Smart Mic Click Driver
 * @brief API for configuring and manipulating Smart Mic Click driver.
 * @{
 */

/**
 * @defgroup smartmic_reg Smart Mic Registers List
 * @brief List of registers of Smart Mic Click driver.
 */

/**
 * @addtogroup smartmic_reg
 * @{
 */

/**
 * @brief Smart Mic API commands for IA611.
 * @details Specified API commands of Smart Mic Click driver.
 */
#define SMARTMIC_NO_RESPONSE_BIT            0x1000
#define SMARTMIC_CMD_SYNC                   0x8000
#define SMARTMIC_CMD_SET_AUDIO_DATA_PORT    0x8004
#define SMARTMIC_CMD_GET_DEVICE_PARAM       0x800B
#define SMARTMIC_CMD_SET_DEVICE_PARAM_ID    0x800C
#define SMARTMIC_CMD_SET_DEVICE_PARAM       0x800D
#define SMARTMIC_CMD_GET_CHIP_ID            0x800E
#define SMARTMIC_CMD_SET_POWER_STATE        ( 0x8010 | SMARTMIC_NO_RESPONSE_BIT )
#define SMARTMIC_CMD_SET_CLOCK_SOURCE       0x8011
#define SMARTMIC_CMD_SET_UART_STOP_BITS     0x8012
#define SMARTMIC_CMD_GET_SIG_RMS            0x8013
#define SMARTMIC_CMD_GET_SIG_PEAK           0x8014
#define SMARTMIC_CMD_SET_DIG_GAIN           0x8015
#define SMARTMIC_CMD_GET_ALGO_PARAM         0x8016
#define SMARTMIC_CMD_SET_ALGO_PARAM_ID      0x8017
#define SMARTMIC_CMD_SET_ALGO_PARAM         0x8018
#define SMARTMIC_CMD_UART_RATE_REQUEST      0x8019
#define SMARTMIC_CMD_SET_EVENT_RESP         0x801A
#define SMARTMIC_CMD_SET_DIAG_CONFIG        0x801C
#define SMARTMIC_CMD_GET_DIG_GAIN           0x801D
#define SMARTMIC_CMD_OUTPUT_KNOWN_SIG       0x801E
#define SMARTMIC_CMD_GET_FIRST_BUILD_STR    0x8020
#define SMARTMIC_CMD_GET_NEXT_BUILD_STR     0x8021
#define SMARTMIC_CMD_GET_INFO               0x8022
#define SMARTMIC_CMD_SET_SPI_SAMPLE_CFG     0x8023
#define SMARTMIC_CMD_SET_STREAMING          0x8025
#define SMARTMIC_CMD_GET_BAF_INFO           0x8027
#define SMARTMIC_CMD_SELECT_STREAMING       0x8028
#define SMARTMIC_CMD_CONFIG_DATA_PORT       0x802C
#define SMARTMIC_CMD_READ_DATA_BLOCK        0x802E
#define SMARTMIC_CMD_WRITE_DATA_BLOCK       0x802F
#define SMARTMIC_CMD_SET_SAMPLE_RATE        0x8030
#define SMARTMIC_CMD_SET_PRESET             0x8031
#define SMARTMIC_CMD_SELECT_ROUTE           0x8032
#define SMARTMIC_CMD_STOP_ROUTE             0x8033
#define SMARTMIC_CMD_SET_BUFF_DATA_FORMAT   0x8034
#define SMARTMIC_CMD_SET_FRAME_SIZE         0x8035
#define SMARTMIC_CMD_PDM_BYPASS_MODE        0x8040
#define SMARTMIC_CMD_SET_AUDIO_PORT_CLK_F   0x8042
#define SMARTMIC_CMD_POWER_DOWN_INT_OSC     0x8043
#define SMARTMIC_CMD_SET_DIG_HW_PT          0x8052
#define SMARTMIC_CMD_ENABLE_DISABLE_JTAG    0x8061
#define SMARTMIC_CMD_SET_PAD_CONTROL        0x8062
#define SMARTMIC_CMD_GET_EVENT              0x806D

/*! @} */ // smartmic_reg

/**
 * @defgroup smartmic_set Smart Mic Registers Settings
 * @brief Settings for registers of Smart Mic Click driver.
 */

/**
 * @addtogroup smartmic_set
 * @{
 */

/**
 * @brief Smart Mic API set algo param commands.
 * @details Specified API set algo param commands of Smart Mic Click driver.
 */
#define SMARTMIC_VQ_CMD_VS_PROCESSING_MODE  0x5003
#define SMARTMIC_VQ_CMD_OEM_SENSITIVITY     0x5008
#define SMARTMIC_VQ_CMD_UTK_SENSITIVITY     0x5009
#define SMARTMIC_VQ_CMD_VID_SENSITIVITY     0x500D
#define SMARTMIC_VQ_CMD_RESET               0x500E

/**
 * @brief Smart Mic API set algo param settings.
 * @details Specified API set algo param settings of Smart Mic Click driver.
 */
#define SMARTMIC_VS_PROCESSING_MODE_KW      0x0000  // Keyword Detection mode
#define SMARTMIC_OEM_SENSITIVITY_5          0x0005  // Set the OEM Detection Sensitivity to 5
#define SMARTMIC_UTK_SENSITIVITY_0          0x0000  // Set the UTK Detection Sensitivity to 0
#define SMARTMIC_VID_SENSITIVITY_2          0x0002  // Set the Voice ID Detection Sensitivity to 0
#define SMARTMIC_RESET                      0x0001  // Perform reset

/**
 * @brief Smart Mic API settings.
 * @details Specified API settings of Smart Mic Click driver.
 */
#define SMARTMIC_SYNC_BYTE                  0xB7
#define SMARTMIC_BOOT_BYTE                  0x01
#define SMARTMIC_SAMPLE_RATE_16K            0x0001  // 16k Sample Rate
#define SMARTMIC_FRAME_SIZE_16MS            0x0010  // For Voice Q 16 mS Frame Size
#define SMARTMIC_BUFF_DATA_FORMAT_16BIT     0x0002  // 16 bit Buffer Data Format
#define SMARTMIC_ROUTE_6                    0x0006  // Select Route 6
#define SMARTMIC_DIGITAL_GAIN_20            0x0C14  // 20 db Gain and End point ID = 12
#define SMARTMIC_END_POINT_ID               0x0C00  // Endpoint ID for Route-6 Stream manager-0
#define SMARTMIC_LOW_POWER_MODE_RT6         0x0002  // Low Power mode for Route 6
#define SMARTMIC_IA611_INT_RISING_EDGE      0x04
#define SMARTMIC_IA611_INT_FALLING_EDGE     0x03
#define SMARTMIC_IA611_INT_LOW_LEVEL        0x01
#define SMARTMIC_WDB_SIZE_NO_HEADER         508     // Data block size without 4 byte Header
#define SMARTMIC_WDB_SIZE                   512     // Data block size with 4 byte Header
#define SMARTMIC_UART_EVENT_HEADER          0xFE
#define SMARTMIC_NO_KWD_DETECTED            0
#define SMARTMIC_OEM1_KWD_DETECTED          1
#define SMARTMIC_OEM2_KWD_DETECTED          2
#define SMARTMIC_OEM3_KWD_DETECTED          3
#define SMARTMIC_OEM4_KWD_DETECTED          4

/**
 * @brief Smart Mic Click driver selector.
 * @details Selects target driver interface of Smart Mic Click driver.
 */
#define SMARTMIC_DRIVER_UART                0
#define SMARTMIC_DRIVER_SPI                 1
#define SMARTMIC_DRIVER_I2C                 2
#define SMARTMIC_DRIVER_SELECTOR            SMARTMIC_DRIVER_I2C

/**
 * @brief Smart Mic Click system config selector.
 * @details Selects system config of Smart Mic Click driver.
 */
#define SMARTMIC_SYS_CFG_6SEC_TO            0
#define SMARTMIC_SYS_CFG_6SEC_TO_UTK        1
#define SMARTMIC_SYS_CFG_6SEC_TO_VID        2
#define SMARTMIC_SYS_CFG_SELECTOR           SMARTMIC_SYS_CFG_6SEC_TO

/**
 * @brief Smart Mic device address setting.
 * @details Specified setting for device slave address selection of
 * Smart Mic Click driver.
 */
#define SMARTMIC_DEVICE_ADDRESS_0           0x3E
#define SMARTMIC_DEVICE_ADDRESS_1           0x3F
#define SMARTMIC_DEVICE_ADDRESS_2           0x38
#define SMARTMIC_DEVICE_ADDRESS_3           0x39

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b smartmic_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define SMARTMIC_SET_DATA_SAMPLE_EDGE       SET_SPI_DATA_SAMPLE_EDGE
#define SMARTMIC_SET_DATA_SAMPLE_MIDDLE     SET_SPI_DATA_SAMPLE_MIDDLE

/**
 * @brief Smart Mic driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE                     256

/*! @} */ // smartmic_set

/**
 * @defgroup smartmic_map Smart Mic MikroBUS Map
 * @brief MikroBUS pin mapping of Smart Mic Click driver.
 */

/**
 * @addtogroup smartmic_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Smart Mic Click to the selected MikroBUS.
 */
#define SMARTMIC_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.en   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // smartmic_map
/*! @} */ // smartmic

/**
 * @brief Smart Mic Click context object.
 * @details Context object definition of Smart Mic Click driver.
 */
typedef struct smartmic_s
{
    digital_out_t en;               /**< Enable device pin. */

    digital_in_t  irq;              /**< Interrupt pin. */

#if ( SMARTMIC_DRIVER_SELECTOR == SMARTMIC_DRIVER_UART )
    uart_t  uart;                   /**< UART driver object. */
    char    uart_rx_buffer[ DRV_BUFFER_SIZE ];  /**< Buffer size. */
    char    uart_tx_buffer[ DRV_BUFFER_SIZE ];  /**< Buffer size. */
#elif ( SMARTMIC_DRIVER_SELECTOR == SMARTMIC_DRIVER_I2C )
    i2c_master_t  i2c;              /**< I2C driver object. */
    uint8_t       slave_address;    /**< Device slave address (used for I2C driver). */
#else
    spi_master_t  spi;              /**< SPI driver object. */
    pin_name_t    chip_select;      /**< Chip select pin descriptor (used for SPI driver). */
#endif

} smartmic_t;

/**
 * @brief Smart Mic Click configuration object.
 * @details Configuration object definition of Smart Mic Click driver.
 */
typedef struct
{
    pin_name_t  rx_pin;             /**< RX pin. */
    pin_name_t  tx_pin;             /**< TX pin. */
    pin_name_t  scl;                /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  miso;               /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;               /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                 /**< Chip select pin descriptor for SPI driver. */
    pin_name_t  en;                 /**< Enable device pin. */
    pin_name_t  int_pin;            /**< Interrupt pin. */
    
#if ( SMARTMIC_DRIVER_SELECTOR == SMARTMIC_DRIVER_UART )
    uint32_t          baud_rate;    /**< Clock speed. */
    bool              uart_blocking;/**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;     /**< Data bits. */
    uart_parity_t     parity_bit;   /**< Parity bit. */
    uart_stop_bits_t  stop_bit;     /**< Stop bits. */
#elif ( SMARTMIC_DRIVER_SELECTOR == SMARTMIC_DRIVER_I2C )
    uint32_t  i2c_speed;            /**< I2C serial speed. */
    uint8_t   i2c_address;          /**< I2C slave address. */
#else
    uint32_t                           spi_speed;   /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;    /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity; /**< Chip select pin polarity. */
#endif

} smartmic_cfg_t;

/**
 * @brief Smart Mic Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SMARTMIC_OK = 0,
    SMARTMIC_ERROR = -1,
    SMARTMIC_FIRMWARE_OK = 2

} smartmic_return_value_t;

/*!
 * @addtogroup smartmic Smart Mic Click Driver
 * @brief API for configuring and manipulating Smart Mic Click driver.
 * @{
 */

/**
 * @brief Smart Mic configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #smartmic_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void smartmic_cfg_setup ( smartmic_cfg_t *cfg );

/**
 * @brief Smart Mic initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #smartmic_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #smartmic_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartmic_init ( smartmic_t *ctx, smartmic_cfg_t *cfg );

/**
 * @brief Smart Mic default configuration function.
 * @details This function executes a default configuration of Smart Mic
 * Click board.
 * @param[in] ctx : Click context object.
 * See #smartmic_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t smartmic_default_cfg ( smartmic_t *ctx );

/**
 * @brief Smart Mic write data function.
 * @details This function writes the specified number of data bytes to the module.
 * @param[in] ctx : Click context object.
 * See #smartmic_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartmic_write_data ( smartmic_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief Smart Mic read data function.
 * @details This function reads a desired number of data bytes from the module.
 * @param[in] ctx : Click context object.
 * See #smartmic_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartmic_read_data ( smartmic_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief Smart Mic send command function.
 * @details This function sends a command word and a data word to the module and waits for a response. 
 * If no response is expected from the module then the SMARTMIC_NO_RESPONSE_BIT bit in command word should be set.
 * @param[in] ctx : Click context object.
 * See #smartmic_t object definition for detailed explanation.
 * @param[in] cmd : Command word to send to the module.
 * @param[in] data_in : Data word to send to the module.
 * @param[out] response : Response word from the module in case the SMARTMIC_NO_RESPONSE_BIT is not set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartmic_send_command ( smartmic_t *ctx, uint16_t cmd, uint16_t data_in, uint16_t *response );

/**
 * @brief Smart Mic download bin function.
 * @details This function downloads system config or firmware binary to the module.
 * @param[in] ctx : Click context object.
 * See #smartmic_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  2 - Firmware download success (for UART communication only),
 *         @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartmic_download_bin ( smartmic_t *ctx, uint8_t *data_in, uint32_t len );

/**
 * @brief Smart Mic download config function.
 * @details This function downloads system config to the module. The system config image
 * must be named as @b smartmic_system_config.
 * @param[in] ctx : Click context object.
 * See #smartmic_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartmic_download_config ( smartmic_t *ctx );

/**
 * @brief Smart Mic download firmware function.
 * @details This function downloads firmware to the module. The firmware image
 * must be named as @b smartmic_firmware.
 * @param[in] ctx : Click context object.
 * See #smartmic_t object definition for detailed explanation.
 * @return @li @c  2 - Firmware download success (for UART communication only),
 *         @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartmic_download_firmware ( smartmic_t *ctx );

/**
 * @brief Smart Mic download keyword function.
 * @details This function downloads keyword models to the module.
 * @param[in] ctx : Click context object.
 * See #smartmic_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartmic_download_keyword ( smartmic_t *ctx, uint16_t *data_in, uint16_t len );

/**
 * @brief Smart Mic voice make function.
 * @details This function performs voice make feature. It stops the route, then sets digital gain to 20db,
 * sample rate to 16K, frame size to 16 ms, and finally it selects route 6 and configures algorithm parameters.
 * @param[in] ctx : Click context object.
 * See #smartmic_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartmic_voice_make ( smartmic_t *ctx );

/**
 * @brief Smart Mic wait keyword function.
 * @details This function waits for a keyword event and then reads it and returns the keyword ID number.
 * @param[in] ctx : Click context object.
 * See #smartmic_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note A voice make and set low power mode features will be performed after event read.
 */
err_t smartmic_wait_keyword ( smartmic_t *ctx );

/**
 * @brief Smart Mic enable device function.
 * @details This function enables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #smartmic_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void smartmic_enable_device ( smartmic_t *ctx );

/**
 * @brief Smart Mic disable device function.
 * @details This function disables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #smartmic_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void smartmic_disable_device ( smartmic_t *ctx );

/**
 * @brief Smart Mic get irq pin function.
 * @details This function returns the IRQ pin logic state.
 * @param[in] ctx : Click context object.
 * See #smartmic_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t smartmic_get_irq_pin ( smartmic_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // SMARTMIC_H

/*! @} */ // smartmic

// ------------------------------------------------------------------------ END
