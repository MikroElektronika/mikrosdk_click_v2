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
 * @file miwi2.h
 * @brief This file contains API for MiWi 2 Click Driver.
 */

#ifndef MIWI2_H
#define MIWI2_H

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
 * @addtogroup miwi2 MiWi 2 Click Driver
 * @brief API for configuring and manipulating MiWi 2 Click driver.
 * @{
 */

/**
 * @defgroup miwi2_reg MiWi 2 Registers List
 * @brief List of registers of MiWi 2 Click driver.
 */

/**
 * @addtogroup miwi2_reg
 * @{
 */

/**
 * @brief MiWi 2 Register Map.
 * @details Specified Register Map of MiWi 2 Click driver.
 */
#define MIWI2_REG_GCONREG                             0x00
#define MIWI2_REG_DMODREG                             0x01
#define MIWI2_REG_FDEVREG                             0x02
#define MIWI2_REG_BRSREG                              0x03
#define MIWI2_REG_FLTHREG                             0x04
#define MIWI2_REG_FIFOCREG                            0x05
#define MIWI2_REG_R1CREG                              0x06
#define MIWI2_REG_P1CREG                              0x07
#define MIWI2_REG_S1CREG                              0x08
#define MIWI2_REG_R2CREG                              0x09
#define MIWI2_REG_P2CREG                              0x0A
#define MIWI2_REG_S2CREG                              0x0B
#define MIWI2_REG_PACREG                              0x0C
#define MIWI2_REG_FTXRXIREG                           0x0D
#define MIWI2_REG_FTPRIREG                            0x0E
#define MIWI2_REG_RSTHIREG                            0x0F
#define MIWI2_REG_FILCREG                             0x10
#define MIWI2_REG_PFCREG                              0x11
#define MIWI2_REG_SYNCREG                             0x12
#define MIWI2_REG_RESVREG                             0x13
#define MIWI2_REG_RSTSREG                             0x14
#define MIWI2_REG_OOKCREG                             0x15
#define MIWI2_REG_SYNCV31REG                          0x16
#define MIWI2_REG_SYNCV23REG                          0x17
#define MIWI2_REG_SYNCV15REG                          0x18
#define MIWI2_REG_SYNCV07REG                          0x19
#define MIWI2_REG_TXCONREG                            0x1A
#define MIWI2_REG_CLKOREG                             0x1B
#define MIWI2_REG_PLOADREG                            0x1C
#define MIWI2_REG_NADDSREG                            0x1D
#define MIWI2_REG_PKTCREG                             0x1E
#define MIWI2_REG_FCRCREG                             0x1F

/*! @} */ // miwi2_reg

/**
 * @defgroup miwi2_set MiWi 2 Registers Settings
 * @brief Settings for registers of MiWi 2 Click driver.
 */

/**
 * @addtogroup miwi2_set
 * @{
 */

/**
 * @brief MiWi 2 default register configuration setting.
 * @details Specified default register configuration setting of MiWi 2 Click driver.
 */
#define MIWI2_GCONREG_STBY_915_VCOT1_RSP1             0x2A
#define MIWI2_GCONREG_FS_915_VCOT1_RSP1               0x4A
#define MIWI2_DMODREG_FSK_PACKET_MODE                 0x8C
#define MIWI2_FDEVREG_33_KHZ                          0x0B
#define MIWI2_BRSREG_BIT_RATE_5KPBS                   0x27
#define MIWI2_FIFOCREG_FIFO_64_THR1                   0xC1
#define MIWI2_FTXRXIREG_RX_PLREADY_CRCOK_TX_TXDONE    0x08
#define MIWI2_FTPRIREG_FIFO_SYNC_AUTOFILL             0x00
#define MIWI2_FILCREG_5KPBS_100KHZ_DEV                0xA3
#define MIWI2_R1CREG_915_KHZ                          0x77
#define MIWI2_P1CREG_915_KHZ                          0x64
#define MIWI2_S1CREG_915_KHZ                          0x32
#define MIWI2_SYNCREG_32BIT_SYNC_ENABLE               0x38
#define MIWI2_SYNCV31REG_VALUE                        0xAA
#define MIWI2_SYNCV23REG_VALUE                        0x2D
#define MIWI2_SYNCV15REG_VALUE                        0xD4
#define MIWI2_SYNCV07REG_VALUE                        0x55
#define MIWI2_TXCONREG_200_KHZ_13_DBM                 0x70
#define MIWI2_CLKOREG_427_KHZ                         0xBC
#define MIWI2_PLOADREG_PAYLOAD_16_BYTES               0x10
#define MIWI2_PKTCREG_FIXED_LENGHT_CRC_ON             0x48
#define MIWI2_FCRCREG_WRITE_MODE_AUTO_CLEAR           0x00

/**
 * @brief MiWi 2 FTPRIREG register setting.
 * @details Specified setting for FTPRIREG register of MiWi 2 Click driver.
 */
#define MIWI2_FTPRIREG_LSTSPLL_MASK                   0x02

/**
 * @brief MiWi 2 GCONREG register setting.
 * @details Specified setting for GCONREG register of MiWi 2 Click driver.
 */
#define MIWI2_GCONREG_CMOD_MASK                       0xE0

/**
 * @brief MiWi 2 FCRCREG register setting.
 * @details Specified setting for FCRCREG register of MiWi 2 Click driver.
 */
#define MIWI2_FCRCREG_FIFO_WRITE_MASK                 0x40

/**
 * @brief MiWi 2 payload length setting.
 * @details Specified payload length setting of MiWi 2 Click driver.
 */
#define MIWI2_PAYLOAD_LEN                             16u     

/**
 * @brief MiWi 2 timing setting.
 * @details Specified timing setting of MiWi 2 Click driver.
 */
#define MIWI2_TX_TIMEOUT_MS                           500u    
#define MIWI2_TX_INTERVAL_MS                          2000u
#define MIWI2_RX_TIMEOUT_MS                           5000u   

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b miwi2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define MIWI2_SET_DATA_SAMPLE_EDGE                    SET_SPI_DATA_SAMPLE_EDGE
#define MIWI2_SET_DATA_SAMPLE_MIDDLE                  SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // miwi2_set

/**
 * @defgroup miwi2_map MiWi 2 MikroBUS Map
 * @brief MikroBUS pin mapping of MiWi 2 Click driver.
 */

/**
 * @addtogroup miwi2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of MiWi 2 Click to the selected MikroBUS.
 */
#define MIWI2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.csdat = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.csc = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.in1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.in0 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // miwi2_map
/*! @} */ // miwi2

/**
 * @brief MiWi 2 Click context object.
 * @details Context object definition of MiWi 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t csc;              /**< Chip select for SPI CONFIG (active low). */
    digital_out_t csdat;            /**< Chip select for SPI DATA (active low). */
    digital_out_t rst;              /**< Reset pin (active high). */

    // Input pins
    digital_in_t in1;               /**< IRQ1 pin (active high). */
    digital_in_t in0;               /**< IRQ0 pin (active high). */

    // Modules
    spi_master_t spi;               /**< SPI driver object. */

} miwi2_t;

/**
 * @brief MiWi 2 Click configuration object.
 * @details Configuration object definition of MiWi 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t csdat;                               /**< DATA Chip select pin descriptor for SPI driver. */
    pin_name_t csc;                                 /**< CONFIG Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rst;                                 /**< Reset pin. */
    pin_name_t in1;                                 /**< IRQ1 pin. */
    pin_name_t in0;                                 /**< IRQ0 pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */

} miwi2_cfg_t;

/**
 * @brief MiWi 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MIWI2_OK = 0,
    MIWI2_ERROR = -1

} miwi2_return_value_t;

/**
 * @brief MiWi 2 Click RF operating modes.
 * @details Predefined RF mode values mapped to GCONREG.CMOD[7:5] field.
 */
typedef enum
{
    MIWI2_RF_SLEEP = 0,
    MIWI2_RF_STANDBY = 1,
    MIWI2_RF_SYNTH = 2,
    MIWI2_RF_RECEIVER = 3,
    MIWI2_RF_TRANSMITTER = 4

} miwi2_rf_mode_t;

/*!
 * @addtogroup miwi2 MiWi 2 Click Driver
 * @brief API for configuring and manipulating MiWi 2 Click driver.
 * @{
 */

/**
 * @brief MiWi 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #miwi2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void miwi2_cfg_setup ( miwi2_cfg_t *cfg );

/**
 * @brief MiWi 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #miwi2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #miwi2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t miwi2_init ( miwi2_t *ctx, miwi2_cfg_t *cfg );

/**
 * @brief MiWi 2 default configuration function.
 * @details This function executes a default configuration of MiWi 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #miwi2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t miwi2_default_cfg ( miwi2_t *ctx );

/**
 * @brief MiWi 2 register write function.
 * @details This function performs a single-byte register write over CSCON.
 * @param[in] ctx : Click context object.
 * See #miwi2_t object definition for detailed explanation.
 * @param[in] addr : Register address.
 * @param[in] value : Data byte to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t miwi2_reg_write ( miwi2_t *ctx, uint8_t addr, uint8_t value );

/**
 * @brief MiWi 2 register read function.
 * @details This function performs a single-byte register read over CSCON.
 * @param[in] ctx : Click context object.
 * See #miwi2_t object definition for detailed explanation.
 * @param[in] addr : Register address.
 * @param[in] value : Pointer to output data byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t miwi2_reg_read ( miwi2_t *ctx, uint8_t addr, uint8_t *value );

/**
 * @brief MiWi 2 register update function.
 * @details This function performs Read-modify-write operation in
 * order to update desired bits.
 * @param[in] ctx : Click context object.
 * See #miwi2_t object definition for detailed explanation.
 * @param[in] addr : Register address.
 * @param[in] field_mask : bit mask selecting bits to be updated.
 * @param[in] value_shifted : bit mask with desired value already shifted to corresponding bits.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t miwi2_reg_update ( miwi2_t *ctx, uint8_t addr, uint8_t field_mask, uint8_t value_shifted );

/**
 * @brief MiWi 2 FIFO write function.
 * @details This function uses CSDAT in order to write one byte into FIFO.
 * @param[in] ctx : Click context object.
 * See #miwi2_t object definition for detailed explanation.
 * @param[in] value : Data byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t miwi2_fifo_write( miwi2_t *ctx, uint8_t value );

/**
 * @brief MiWi 2 FIFO read function.
 * @details This function uses CSDAT in order to read one byte from FIFO.
 * @param[in] ctx : Click context object.
 * See #miwi2_t object definition for detailed explanation.
 * @param[in] value : Pointer to output data byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t miwi2_fifo_read ( miwi2_t *ctx, uint8_t *value );

/**
 * @brief MiWi 2 set bit function.
 * @details This function sets one or more bits in a register.
 * @param[in] ctx : Click context object.
 * See #miwi2_t object definition for detailed explanation.
 * @param[in] addr : Register address.
 * @param[in] bit_mask : Bit mask selecting bits to be set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t miwi2_reg_set_bit ( miwi2_t *ctx, uint8_t addr, uint8_t bit_mask );

/**
 * @brief MiWi 2 clear bit function.
 * @details This function clears one or more bits in a register.
 * @param[in] ctx : Click context object.
 * See #miwi2_t object definition for detailed explanation.
 * @param[in] addr : Register address.
 * @param[in] bit_mask : Bit mask selecting bits to be cleared.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t miwi2_reg_clear_bit ( miwi2_t *ctx, uint8_t addr, uint8_t bit_mask );

/**
 * @brief MiWi 2 set mode function.
 * @details This function sets RF operating mode by
 * updating GCONREG.CMOD[7:5] field.
 * @param[in] ctx : Click context object.
 * See #miwi2_t object definition for detailed explanation.
 * @param[in] mode : RF mode to be set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t miwi2_set_mode ( miwi2_t *ctx, uint8_t mode );

/**
 * @brief MiWi 2 TX packet function.
 * @details This function loads FIFO with payload bytes and switches to TX mode.
 * @param[in] ctx : Click context object.
 * See #miwi2_t object definition for detailed explanation.
 * @param[in] payload : Pointer to payload buffer.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t miwi2_tx_packet ( miwi2_t *ctx, uint8_t *payload );

/**
 * @brief MiWi 2 RX packet function.
 * @details This function reads a fixed number of bytes from the device FIFO
 * using SPI DATA interface.
 * @param[in] ctx : Click context object.
 * See #miwi2_t object definition for detailed explanation.
 * @param[in] payload : Pointer to buffer where received data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t miwi2_rx_packet ( miwi2_t *ctx, uint8_t *payload );

/**
 * @brief MiWi 2 reset function.
 * @details This function performs hardware reset by asserting the RST pin to high
 * for at least 100 µs and then releasing the pin.
 * @param[in] ctx : Click context object.
 * See #miwi2_t object definition for detailed explanation.
 * @return Nothing.
 */
void miwi2_reset ( miwi2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // MIWI2_H

/*! @} */ // miwi2

// ------------------------------------------------------------------------ END
