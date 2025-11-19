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
 * @file canlinsbc.h
 * @brief This file contains API for CAN-LIN SBC Click Driver.
 */

#ifndef CANLINSBC_H
#define CANLINSBC_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup canlinsbc CAN-LIN SBC Click Driver
 * @brief API for configuring and manipulating CAN-LIN SBC Click driver.
 * @{
 */

/**
 * @defgroup canlinsbc_reg CAN-LIN SBC Registers List
 * @brief List of registers of CAN-LIN SBC Click driver.
 */

/**
 * @addtogroup canlinsbc_reg
 * @{
 */

/**
 * @brief CAN-LIN SBC register list.
 * @details Specified register list of CAN-LIN SBC Click driver.
 */
#define CANLINSBC_REG_DMCR                      0x01
#define CANLINSBC_REG_LDOCR                     0x02
#define CANLINSBC_REG_DMSR                      0x03
#define CANLINSBC_REG_SECR                      0x04
#define CANLINSBC_REG_LDOECR                    0x05
#define CANLINSBC_REG_GPM0                      0x06
#define CANLINSBC_REG_GPM1                      0x07
#define CANLINSBC_REG_GPM2                      0x08
#define CANLINSBC_REG_GPM3                      0x09
#define CANLINSBC_REG_RWPR                      0x0A
#define CANLINSBC_REG_TRXCR                     0x20
#define CANLINSBC_REG_LTRXCR                    0x21
#define CANLINSBC_REG_TRXSR                     0x22
#define CANLINSBC_REG_TRXECR                    0x23
#define CANLINSBC_REG_LTRXSR                    0x24
#define CANLINSBC_REG_REGCR                     0x25
#define CANLINSBC_REG_DRCR                      0x26
#define CANLINSBC_REG_CIDR0                     0x27
#define CANLINSBC_REG_CIDR1                     0x28
#define CANLINSBC_REG_CIDR2                     0x29
#define CANLINSBC_REG_CIDR3                     0x2A
#define CANLINSBC_REG_CIDMR0                    0x2B
#define CANLINSBC_REG_CIDMR1                    0x2C
#define CANLINSBC_REG_CIDMR2                    0x2D
#define CANLINSBC_REG_CIDMR3                    0x2E
#define CANLINSBC_REG_CFCR                      0x2F
#define CANLINSBC_REG_BFECR                     0x32
#define CANLINSBC_REG_BFIR                      0x33
#define CANLINSBC_REG_TRXECR2                   0x34
#define CANLINSBC_REG_TRXESR2                   0x35
#define CANLINSBC_REG_WDCR1                     0x36
#define CANLINSBC_REG_WDCR2                     0x37
#define CANLINSBC_REG_WDSR                      0x38
#define CANLINSBC_REG_WDTRIG                    0x39
#define CANLINSBC_REG_EFCR                      0x3A
#define CANLINSBC_REG_FECR                      0x3B
#define CANLINSBC_REG_GLFT                      0x67
#define CANLINSBC_REG_CDMR0                     0x68
#define CANLINSBC_REG_CDMR1                     0x69
#define CANLINSBC_REG_CDMR2                     0x6A
#define CANLINSBC_REG_CDMR3                     0x6B
#define CANLINSBC_REG_CDMR4                     0x6C
#define CANLINSBC_REG_CDMR5                     0x6D
#define CANLINSBC_REG_CDMR6                     0x6E
#define CANLINSBC_REG_CDMR7                     0x6F
#define CANLINSBC_REG_PWKS                      0x4B
#define CANLINSBC_REG_WKECR                     0x4C
#define CANLINSBC_REG_GESR                      0x60
#define CANLINSBC_REG_SESR                      0x61
#define CANLINSBC_REG_LTRXESR                   0x62
#define CANLINSBC_REG_CTRXESR                   0x63
#define CANLINSBC_REG_WKESR                     0x64
#define CANLINSBC_REG_BFESR                     0x65
#define CANLINSBC_REG_LDOESR                    0x66
#define CANLINSBC_REG_DIDR                      0x7E

/*! @} */ // canlinsbc_reg

/**
 * @defgroup canlinsbc_set CAN-LIN SBC Registers Settings
 * @brief Settings for registers of CAN-LIN SBC Click driver.
 */

/**
 * @addtogroup canlinsbc_set
 * @{
 */

/**
 * @brief CAN-LIN SBC Device Mode Control Register (DMCR) setting.
 * @details Specified setting for Device Mode Control Register (DMCR) of CAN-LIN SBC Click driver.
 */
#define CANLINSBC_DMCR_RSTEN                    0x20
#define CANLINSBC_DMCR_VCCOVSD                  0x10
#define CANLINSBC_DMCR_SLPVCCUC                 0x08
#define CANLINSBC_DMCR_DOPM_SLEEP_MODE          0x01
#define CANLINSBC_DMCR_DOPM_STANDBY_MODE        0x04
#define CANLINSBC_DMCR_DOPM_NORMAL_MODE         0x07
#define CANLINSBC_DMCR_DOPM_MASK                0x07

/**
 * @brief CAN-LIN SBC CAN Transceiver Control Register (TRXCR) setting.
 * @details Specified setting for CAN Transceiver Control Register (TRXCR) of CAN-LIN SBC Click driver.
 */
#define CANLINSBC_TRXCR_CFDPE                   0x40
#define CANLINSBC_TRXCR_PNCFOK                  0x20
#define CANLINSBC_TRXCR_CPNE                    0x10
#define CANLINSBC_TRXCR_COMP_STANDBY_MODE       0x00
#define CANLINSBC_TRXCR_COMP_NORMAL_MODE        0x01
#define CANLINSBC_TRXCR_COMP_SILENT_MODE        0x03
#define CANLINSBC_TRXCR_COMP_MASK               0x03

/**
 * @brief CAN-LIN SBC Watchdog Configuration Register 1 (WDCR1) setting.
 * @details Specified setting for Watchdog Configuration Register 1 (WDCR1) of CAN-LIN SBC Click driver.
 */
#define CANLINSBC_WDCR1_WDC_OFF_MODE            0x20
#define CANLINSBC_WDCR1_WDC_TIME_OUT_MODE       0x40
#define CANLINSBC_WDCR1_WDC_WINDOW_MODE         0x80
#define CANLINSBC_WDCR1_WDC_MASK                0xE0
#define CANLINSBC_WDCR1_WDPRE_FACTOR_1          0x00
#define CANLINSBC_WDCR1_WDPRE_FACTOR_1_5        0x08
#define CANLINSBC_WDCR1_WDPRE_FACTOR_2_5        0x10
#define CANLINSBC_WDCR1_WDPRE_FACTOR_3_5        0x18
#define CANLINSBC_WDCR1_WDPRE_MASK              0x18
#define CANLINSBC_WDCR1_WDLSP                   0x04
#define CANLINSBC_WDCR1_WDLW                    0x02

/**
 * @brief CAN-LIN SBC Watchdog Trigger Register (WDTRIG) setting.
 * @details Specified setting for Watchdog Trigger Register (WDTRIG) of CAN-LIN SBC Click driver.
 */
#define CANLINSBC_WDTRIG_RESET                  0x55

/**
 * @brief CAN-LIN SBC device ID setting.
 * @details Specified setting for device ID of CAN-LIN SBC Click driver.
 */
#define CANLINSBC_DEVICE_ID                     0x86

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b canlinsbc_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define CANLINSBC_SET_DATA_SAMPLE_EDGE          SET_SPI_DATA_SAMPLE_EDGE
#define CANLINSBC_SET_DATA_SAMPLE_MIDDLE        SET_SPI_DATA_SAMPLE_MIDDLE

/**
 * @brief CAN-LIN SBC driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define CANLINSBC_TX_DRV_BUFFER_SIZE            100
#define CANLINSBC_RX_DRV_BUFFER_SIZE            300

/*! @} */ // canlinsbc_set

/**
 * @defgroup canlinsbc_map CAN-LIN SBC MikroBUS Map
 * @brief MikroBUS pin mapping of CAN-LIN SBC Click driver.
 */

/**
 * @addtogroup canlinsbc_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of CAN-LIN SBC Click to the selected MikroBUS.
 */
#define CANLINSBC_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.txd_lin = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rxd_lin = MIKROBUS( mikrobus, MIKROBUS_INT ); \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX );

/*! @} */ // canlinsbc_map
/*! @} */ // canlinsbc

/**
 * @brief CAN-LIN SBC Click context object.
 * @details Context object definition of CAN-LIN SBC Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin (active low). */
    digital_out_t txd_lin;      /**< LIN transmit pin. */

    // Input pins
    digital_in_t rxd_lin;       /**< LIN receive pin. */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    // Modules
    uart_t uart;                /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ CANLINSBC_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ CANLINSBC_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */

    pin_name_t chip_select;     /**< Chip select pin descriptor (used for SPI driver). */

} canlinsbc_t;

/**
 * @brief CAN-LIN SBC Click configuration object.
 * @details Configuration object definition of CAN-LIN SBC Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */
    pin_name_t rx_pin;          /**< RX pin. */
    pin_name_t tx_pin;          /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;             /**< Reset pin (active low). */
    pin_name_t txd_lin;         /**< LIN transmit pin. */
    pin_name_t rxd_lin;         /**< LIN receive pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */
    uint32_t         baud_rate;                     /**< Clock speed. */
    bool             uart_blocking;                 /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;                      /**< Data bits. */
    uart_parity_t    parity_bit;                    /**< Parity bit. */
    uart_stop_bits_t stop_bit;                      /**< Stop bits. */

} canlinsbc_cfg_t;

/**
 * @brief CAN-LIN SBC Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CANLINSBC_OK = 0,
    CANLINSBC_ERROR = -1

} canlinsbc_return_value_t;

/*!
 * @addtogroup canlinsbc CAN-LIN SBC Click Driver
 * @brief API for configuring and manipulating CAN-LIN SBC Click driver.
 * @{
 */

/**
 * @brief CAN-LIN SBC configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #canlinsbc_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void canlinsbc_cfg_setup ( canlinsbc_cfg_t *cfg );

/**
 * @brief CAN-LIN SBC initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #canlinsbc_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #canlinsbc_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t canlinsbc_init ( canlinsbc_t *ctx, canlinsbc_cfg_t *cfg );

/**
 * @brief CAN-LIN SBC default configuration function.
 * @details This function executes a default configuration of CAN-LIN SBC
 * Click board.
 * @param[in] ctx : Click context object.
 * See #canlinsbc_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t canlinsbc_default_cfg ( canlinsbc_t *ctx );

/**
 * @brief CAN LIN SBC write register function.
 * @details This function writes a byte of data to the specified register using the SPI interface.
 * @param[in] ctx : Click context object.
 * See #canlinsbc_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written to the register.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t canlinsbc_write_reg ( canlinsbc_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief CAN LIN SBC read register function.
 * @details This function reads a byte of data from the specified register using the SPI interface.
 * @param[in] ctx : Click context object.
 * See #canlinsbc_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to store the read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t canlinsbc_read_reg ( canlinsbc_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief CAN LIN SBC generic write function.
 * @details This function writes a specified number of bytes to the CAN LIN SBC device using UART communication.
 * @param[in] ctx : Click context object.
 * See #canlinsbc_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t canlinsbc_generic_write ( canlinsbc_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief CAN LIN SBC generic read function.
 * @details This function reads a specified number of bytes from the CAN LIN SBC device using UART communication.
 * @param[in] ctx : Click context object.
 * See #canlinsbc_t object definition for detailed explanation.
 * @param[out] data_out : Buffer to store the read data.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t canlinsbc_generic_read ( canlinsbc_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief CAN LIN SBC set reset pin function.
 * @details This function sets the logic state of the reset (RST) pin.
 * @param[in] ctx : Click context object.
 * See #canlinsbc_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void canlinsbc_set_rst_pin ( canlinsbc_t *ctx, uint8_t state );

/**
 * @brief CAN LIN SBC set TXD LIN pin function.
 * @details This function sets the logic state of the TXD LIN pin.
 * @param[in] ctx : Click context object.
 * See #canlinsbc_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void canlinsbc_set_txd_lin_pin ( canlinsbc_t *ctx, uint8_t state );

/**
 * @brief CAN LIN SBC get RXD LIN pin function.
 * @details This function reads the logic state of the RXD LIN pin.
 * @param[in] ctx : Click context object.
 * See #canlinsbc_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t canlinsbc_get_rxd_lin_pin ( canlinsbc_t *ctx );

/**
 * @brief CAN LIN SBC reset device function.
 * @details This function resets the CAN LIN SBC device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #canlinsbc_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void canlinsbc_reset_device ( canlinsbc_t *ctx );

/**
 * @brief CAN LIN SBC check communication function.
 * @details This function checks the communication with the device by reading and verifying the device ID register.
 * @param[in] ctx : Click context object.
 * See #canlinsbc_t object definition for detailed explanation.
 * @return @li @c  0 - Success (Device ID matches),
 *         @li @c -1 - Error (Device ID mismatch or communication failure).
 * @note None.
 */
err_t canlibsbc_check_communication ( canlinsbc_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // CANLINSBC_H

/*! @} */ // canlinsbc

// ------------------------------------------------------------------------ END
