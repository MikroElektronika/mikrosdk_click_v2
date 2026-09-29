/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file c6lowpant.h
 * @brief This file contains API for 6LoWPAN T Click Driver.
 */

#ifndef C6LOWPANT_H
#define C6LOWPANT_H

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
 * @addtogroup c6lowpant 6LoWPAN T Click Driver
 * @brief API for configuring and manipulating 6LoWPAN T Click driver.
 * @{
 */

/**
 * @defgroup c6lowpant_reg 6LoWPAN T Registers List
 * @brief List of registers of 6LoWPAN T Click driver.
 */

/**
 * @addtogroup c6lowpant_reg
 * @{
 */

/**
 * @brief 6LoWPAN T register addresses.
 * @details Configuration and status registers used by 6LoWPAN T Click.
 */
#define C6LOWPANT_REG_FRMFILT0                              0x00
#define C6LOWPANT_REG_FRMFILT1                              0x01
#define C6LOWPANT_REG_SRCMATCH                              0x02
#define C6LOWPANT_REG_SRCSHORTEN0                           0x04
#define C6LOWPANT_REG_SRCSHORTEN1                           0x05
#define C6LOWPANT_REG_SRCSHORTEN2                           0x06
#define C6LOWPANT_REG_SRCEXTEN0                             0x08
#define C6LOWPANT_REG_SRCEXTEN1                             0x09
#define C6LOWPANT_REG_SRCEXTEN2                             0x0A
#define C6LOWPANT_REG_FRMCTRL0                              0x0C
#define C6LOWPANT_REG_FRMCTRL1                              0x0D
#define C6LOWPANT_REG_RXENABLE0                             0x0E
#define C6LOWPANT_REG_RXENABLE1                             0x0F
#define C6LOWPANT_REG_EXCFLAG0                              0x10
#define C6LOWPANT_REG_EXCFLAG1                              0x11
#define C6LOWPANT_REG_EXCFLAG2                              0x12
#define C6LOWPANT_REG_EXCMASKA0                             0x14
#define C6LOWPANT_REG_EXCMASKA1                             0x15
#define C6LOWPANT_REG_EXCMASKA2                             0x16
#define C6LOWPANT_REG_EXCMASKB0                             0x18
#define C6LOWPANT_REG_EXCMASKB1                             0x19
#define C6LOWPANT_REG_EXCMASKB2                             0x1A
#define C6LOWPANT_REG_EXCBINDX0                             0x1C
#define C6LOWPANT_REG_EXCBINDX1                             0x1D
#define C6LOWPANT_REG_EXCBINDY0                             0x1E
#define C6LOWPANT_REG_EXCBINDY1                             0x1F
#define C6LOWPANT_REG_GPIOCTRL0                             0x20
#define C6LOWPANT_REG_GPIOCTRL1                             0x21
#define C6LOWPANT_REG_GPIOCTRL2                             0x22
#define C6LOWPANT_REG_GPIOCTRL3                             0x23
#define C6LOWPANT_REG_GPIOCTRL4                             0x24
#define C6LOWPANT_REG_GPIOCTRL5                             0x25
#define C6LOWPANT_REG_GPIOPOLARITY                          0x26
#define C6LOWPANT_REG_GPIOCTRL                              0x28
#define C6LOWPANT_REG_DPUCON                                0x2A
#define C6LOWPANT_REG_DPUSTAT                               0x2C
#define C6LOWPANT_REG_FREQCTRL                              0x2E
#define C6LOWPANT_REG_FREQTUNE                              0x2F
#define C6LOWPANT_REG_TXPOWER                               0x30
#define C6LOWPANT_REG_TXCTRL                                0x31
#define C6LOWPANT_REG_FSMSTAT0                              0x32
#define C6LOWPANT_REG_FSMSTAT1                              0x33
#define C6LOWPANT_REG_FIFOPCTRL                             0x34
#define C6LOWPANT_REG_FSMCTRL                               0x35
#define C6LOWPANT_REG_CCACTRL0                              0x36
#define C6LOWPANT_REG_CCACTRL1                              0x37
#define C6LOWPANT_REG_RSSI                                  0x38
#define C6LOWPANT_REG_RSSISTAT                              0x39
#define C6LOWPANT_REG_RXFIRST                               0x3C
#define C6LOWPANT_REG_RXFIFOCNT                             0x3E
#define C6LOWPANT_REG_TXFIFOCNT                             0x3F
#define C6LOWPANT_REG_CHIPID                                0x40
#define C6LOWPANT_REG_VERSION                               0x42
#define C6LOWPANT_REG_EXTCLOCK                              0x44
#define C6LOWPANT_REG_MDMCTRL0                              0x46
#define C6LOWPANT_REG_MDMCTRL1                              0x47
#define C6LOWPANT_REG_FREQEST                               0x48
#define C6LOWPANT_REG_RXCTRL                                0x4A
#define C6LOWPANT_REG_FSCTRL                                0x4C
#define C6LOWPANT_REG_FSCAL0                                0x4E
#define C6LOWPANT_REG_FSCAL1                                0x4F
#define C6LOWPANT_REG_FSCAL2                                0x50
#define C6LOWPANT_REG_FSCAL3                                0x51
#define C6LOWPANT_REG_AGCCTRL0                              0x52
#define C6LOWPANT_REG_AGCCTRL1                              0x53
#define C6LOWPANT_REG_AGCCTRL2                              0x54
#define C6LOWPANT_REG_AGCCTRL3                              0x55
#define C6LOWPANT_REG_ADCTEST0                              0x56
#define C6LOWPANT_REG_ADCTEST1                              0x57
#define C6LOWPANT_REG_ADCTEST2                              0x58

/*! @} */ // c6lowpant_reg

/**
 * @defgroup c6lowpant_set 6LoWPAN T Registers Settings
 * @brief Settings for registers of 6LoWPAN T Click driver.
 */

/**
 * @addtogroup c6lowpant_set
 * @{
 */

/**
 * @brief 6LoWPAN T SPI commands.
 * @details Register, memory, FIFO, and radio control instructions for 6LoWPAN T Click.
 */
#define C6LOWPANT_CMD_SNOP                                  0x00
#define C6LOWPANT_CMD_SRES                                  0x0F
#define C6LOWPANT_CMD_MEMRD                                 0x10
#define C6LOWPANT_CMD_MEMWR                                 0x20
#define C6LOWPANT_CMD_RXBUF                                 0x30
#define C6LOWPANT_CMD_TXBUF                                 0x3A
#define C6LOWPANT_CMD_SXOSCON                               0x40
#define C6LOWPANT_CMD_STXCAL                                0x41
#define C6LOWPANT_CMD_SRXON                                 0x42
#define C6LOWPANT_CMD_STXON                                 0x43
#define C6LOWPANT_CMD_STXONCCA                              0x44
#define C6LOWPANT_CMD_SRFOFF                                0x45
#define C6LOWPANT_CMD_SXOSCOFF                              0x46
#define C6LOWPANT_CMD_SFLUSHRX                              0x47
#define C6LOWPANT_CMD_SFLUSHTX                              0x48
#define C6LOWPANT_CMD_SACK                                  0x49
#define C6LOWPANT_CMD_SACKPEND                              0x4A
#define C6LOWPANT_CMD_SNACK                                 0x4B
#define C6LOWPANT_CMD_REGRD                                 0x80
#define C6LOWPANT_CMD_REGWR                                 0xC0

/**
 * @brief 6LoWPAN T memory addresses.
 * @details Address storage and RAM limits for 6LoWPAN T Click.
 */
#define C6LOWPANT_MEM_EXT_ADDR                              0x03EA
#define C6LOWPANT_MEM_PAN_ID                                0x03F2
#define C6LOWPANT_MEM_SHORT_ADDR                            0x03F4
#define C6LOWPANT_MEM_RAM_START                             0x0100
#define C6LOWPANT_MEM_RAM_END                               0x03FF
#define C6LOWPANT_REG_END                                   0x7F

/**
 * @brief 6LoWPAN T status masks.
 * @details SPI status, frame completion, FIFO errors, and CRC status for 6LoWPAN T Click.
 */
#define C6LOWPANT_STATUS_XOSC_STABLE                        0x80
#define C6LOWPANT_STATUS_RSSI_VALID                         0x40
#define C6LOWPANT_STATUS_TX_ACTIVE                          0x02
#define C6LOWPANT_STATUS_RX_ACTIVE                          0x01
#define C6LOWPANT_EXC_TX_FRM_DONE                           0x02
#define C6LOWPANT_EXC_TX_UNDERFLOW                          0x08
#define C6LOWPANT_EXC_TX_OVERFLOW                           0x10
#define C6LOWPANT_EXC_RX_UNDERFLOW                          0x20
#define C6LOWPANT_EXC_RX_OVERFLOW                           0x40
#define C6LOWPANT_EXC_RX_FRM_DONE                           0x01
#define C6LOWPANT_FSM_FIFO                                  0x80
#define C6LOWPANT_FSM_FIFOP                                 0x40
#define C6LOWPANT_FSM_SAMPLED_CCA                           0x08
#define C6LOWPANT_CRC_OK                                    0x80
#define C6LOWPANT_CORRELATION_MASK                          0x7F

/**
 * @brief 6LoWPAN T frame settings.
 * @details Short-address data frames, hardware CRC, and GPIO signals for 6LoWPAN T Click.
 */
#define C6LOWPANT_FRM_FILTER_EN                             0x01
#define C6LOWPANT_ACCEPT_DATA_FRAMES                        0x10
#define C6LOWPANT_AUTOCRC                                   0x40
#define C6LOWPANT_AUTOACK                                   0x20
#define C6LOWPANT_GPIO_FIFO                                 0x27
#define C6LOWPANT_GPIO_FIFOP                                0x28
#define C6LOWPANT_GPIO_SFD                                  0x2A
#define C6LOWPANT_FCF_DATA_LOW                              0x41
#define C6LOWPANT_FCF_DATA_HIGH                             0x88
#define C6LOWPANT_MAC_HEADER_SIZE                           9
#define C6LOWPANT_FCS_SIZE                                  2
#define C6LOWPANT_MAX_FRAME_SIZE                            127
#define C6LOWPANT_MAX_PAYLOAD_SIZE                          116
#define C6LOWPANT_LENGTH_FIELD_SIZE                         1
#define C6LOWPANT_FREG_LIMIT                                0x40
#define C6LOWPANT_BROADCAST_ADDR                            0xFFFF
#define C6LOWPANT_RESERVED_SHORT_ADDR                       0xFFFE
#define C6LOWPANT_MAX_PAN_ID                                0xFFFE
#define C6LOWPANT_MAX_SHORT_ADDR                            0xFFFD
#define C6LOWPANT_CHIP_ID                                   0x84
#define C6LOWPANT_RSSI_OFFSET                               76
#define C6LOWPANT_RSSI_SIGN_BIT                             0x80
#define C6LOWPANT_CHANNEL_MIN                               11
#define C6LOWPANT_CHANNEL_MAX                               26
#define C6LOWPANT_CHANNEL_FREQUENCY_BASE                    2405
#define C6LOWPANT_CHANNEL_FREQUENCY_STEP                    5
#define C6LOWPANT_FREQCTRL_BASE                             11
#define C6LOWPANT_MODE_TX                                   0
#define C6LOWPANT_MODE_RX                                   1

/**
 * @brief 6LoWPAN T default settings.
 * @details Default radio values and manufacturer-recommended analog settings for 6LoWPAN T Click.
 */
#define C6LOWPANT_DEFAULT_CHANNEL                           20
#define C6LOWPANT_DEFAULT_PAN_ID                            0x1234
#define C6LOWPANT_DEFAULT_SHORT_ADDR                        0x0001
#define C6LOWPANT_DEFAULT_TX_POWER                          0x32
#define C6LOWPANT_DEFAULT_CCACTRL0                          0xF8
#define C6LOWPANT_DEFAULT_MDMCTRL0                          0x85
#define C6LOWPANT_DEFAULT_MDMCTRL1                          0x14
#define C6LOWPANT_DEFAULT_RXCTRL                            0x3F
#define C6LOWPANT_DEFAULT_FSCTRL                            0x5A
#define C6LOWPANT_DEFAULT_FSCAL1                            0x2B
#define C6LOWPANT_DEFAULT_AGCCTRL1                          0x11
#define C6LOWPANT_DEFAULT_ADCTEST0                          0x10
#define C6LOWPANT_DEFAULT_ADCTEST1                          0x0E
#define C6LOWPANT_DEFAULT_ADCTEST2                          0x03
#define C6LOWPANT_DEFAULT_FRMFILT0                          0x0D
#define C6LOWPANT_DEFAULT_SRCMATCH                          0x00
#define C6LOWPANT_DEFAULT_FRMCTRL1                          0x00
#define C6LOWPANT_DEFAULT_FIFOPCTRL                         C6LOWPANT_MAX_FRAME_SIZE
#define C6LOWPANT_DEFAULT_SPI_SPEED                         1000000

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b c6lowpant_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define C6LOWPANT_SET_DATA_SAMPLE_EDGE                      SET_SPI_DATA_SAMPLE_EDGE
#define C6LOWPANT_SET_DATA_SAMPLE_MIDDLE                    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // c6lowpant_set

/**
 * @defgroup c6lowpant_map 6LoWPAN T MikroBUS Map
 * @brief MikroBUS pin mapping of 6LoWPAN T Click driver.
 */

/**
 * @addtogroup c6lowpant_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 6LoWPAN T Click to the selected MikroBUS.
 */
#define C6LOWPANT_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.gp0  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.ven  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.gp1  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // c6lowpant_map
/*! @} */ // c6lowpant

/**
 * @brief 6LoWPAN T Click context object.
 * @details Context object definition of 6LoWPAN T Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< External reset pin, active low. */
    digital_out_t ven;          /**< When high, digital voltage regulator is active. */

    // Input pins
    digital_in_t gp0;           /**< General purpose digital I/O 0 pin. */
    digital_in_t gp1;           /**< General purpose digital I/O 1 pin. */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t chip_select;     /**< Chip select pin descriptor (used for SPI driver). */

    uint16_t pan_id;            /**< PAN identifier used in transmitted frames. */
    uint16_t short_addr;        /**< Local short address used in transmitted frames. */
    uint8_t sequence;           /**< MAC sequence number for the next transmission. */
    uint8_t mode;               /**< Mode restored after packet transmission. */

} c6lowpant_t;

/**
 * @brief 6LoWPAN T Click configuration object.
 * @details Configuration object definition of 6LoWPAN T Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t gp0;             /**< General purpose digital I/O 0 pin. */
    pin_name_t rst;             /**< External reset pin, active low. */
    pin_name_t ven;             /**< When high, digital voltage regulator is active. */
    pin_name_t gp1;             /**< General purpose digital I/O 1 pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} c6lowpant_cfg_t;

/**
 * @brief 6LoWPAN T Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C6LOWPANT_OK = 0,
    C6LOWPANT_ERROR = -1,
    C6LOWPANT_NO_DATA = -2,
    C6LOWPANT_TIMEOUT = -3,
    C6LOWPANT_CHANNEL_BUSY = -4,
    C6LOWPANT_FRAME_ERROR = -5,
    C6LOWPANT_BUFFER_ERROR = -6

} c6lowpant_return_value_t;

/**
 * @brief 6LoWPAN T received packet information.
 * @details Address, sequence, length, and link measurements from a valid 6LoWPAN T Click data frame.
 */
typedef struct
{
    uint16_t source;            /**< Sender short address. */
    uint16_t destination;       /**< Destination short address or broadcast address. */
    uint16_t pan_id;            /**< Destination PAN identifier. */
    uint8_t sequence;           /**< Received eight-bit MAC sequence number. */
    uint8_t length;             /**< Application payload length, excluding MAC header and FCS. */
    int16_t rssi;               /**< Estimated signal strength in dBm, using a 76 dB reference offset. */
    uint8_t correlation;        /**< Raw correlation from 0 to 127; not a percentage or calibrated LQI. */

} c6lowpant_packet_info_t;

/*!
 * @addtogroup c6lowpant 6LoWPAN T Click Driver
 * @brief API for configuring and manipulating 6LoWPAN T Click driver.
 * @{
 */

/**
 * @brief 6LoWPAN T configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c6lowpant_cfg_t object definition for detailed explanation.
 * @return None.
 * @note All used pins will be set to unconnected state.
 */
void c6lowpant_cfg_setup ( c6lowpant_cfg_t *cfg );

/**
 * @brief 6LoWPAN T initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #c6lowpant_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c6lowpant_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6lowpant_init ( c6lowpant_t *ctx, c6lowpant_cfg_t *cfg );

/**
 * @brief 6LoWPAN T default configuration function.
 * @details This function resets and configures 6LoWPAN T Click for 250 kbps data frames on channel 20.
 * @param[in] ctx : Click context object.
 * See #c6lowpant_t object definition for detailed explanation.
 * @return C6LOWPANT_OK, C6LOWPANT_TIMEOUT, or C6LOWPANT_ERROR.
 * @note Uses PAN 0x1234, short address 0x0001, 0 dBm output power, frame filtering, and automatic CRC.
 * Applies the recommended radio settings and verifies the channel/address values. Leaves TX standby selected;
 * automatic ACK is disabled.
 */
err_t c6lowpant_default_cfg ( c6lowpant_t *ctx );

/**
 * @brief 6LoWPAN T write register function.
 * @details This function writes a single byte of data to the selected 6LoWPAN T Click register.
 * @param[in] ctx : Click context object.
 * See #c6lowpant_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6lowpant_write_reg ( c6lowpant_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief 6LoWPAN T write registers function.
 * @details This function writes a sequential block of data starting from the selected 6LoWPAN T Click register.
 * FREG accesses use REGWR; SREG accesses and bursts crossing the FREG boundary use MEMWR.
 * @param[in] ctx : Click context object.
 * See #c6lowpant_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Pointer to the input data buffer.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6lowpant_write_regs ( c6lowpant_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 6LoWPAN T read register function.
 * @details This function reads a single byte of data from the selected 6LoWPAN T Click register.
 * @param[in] ctx : Click context object.
 * See #c6lowpant_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6lowpant_read_reg ( c6lowpant_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief 6LoWPAN T read registers function.
 * @details This function reads a sequential block of data starting from the selected 6LoWPAN T Click register.
 * FREG accesses use REGRD; SREG accesses and bursts crossing the FREG boundary use MEMRD.
 * @param[in] ctx : Click context object.
 * See #c6lowpant_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Pointer to the output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6lowpant_read_regs ( c6lowpant_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief 6LoWPAN T write memory function.
 * @details This function writes sequential bytes to 6LoWPAN T Click registers or RAM.
 * @param[in] ctx : Click context object.
 * See #c6lowpant_t object definition for detailed explanation.
 * @param[in] address : Start address in the register or RAM region.
 * @param[in] data_in : Input bytes.
 * @param[in] len : Number of bytes to write within that region.
 * @return C6LOWPANT_OK on success, or C6LOWPANT_ERROR on invalid arguments or SPI failure.
 * @note Avoid direct FIFO memory writes; use the packet API for radio frames.
 */
err_t c6lowpant_write_memory ( c6lowpant_t *ctx, uint16_t address, uint8_t *data_in, uint16_t len );

/**
 * @brief 6LoWPAN T read memory function.
 * @details This function reads sequential bytes from 6LoWPAN T Click registers or RAM.
 * @param[in] ctx : Click context object.
 * See #c6lowpant_t object definition for detailed explanation.
 * @param[in] address : Start address in the register or RAM region.
 * @param[out] data_out : Output buffer with space for len bytes.
 * @param[in] len : Number of bytes to read within that region.
 * @return C6LOWPANT_OK on success, or C6LOWPANT_ERROR on invalid arguments or SPI failure.
 * @note Reading FIFO memory directly does not advance the FIFO read pointer.
 */
err_t c6lowpant_read_memory ( c6lowpant_t *ctx, uint16_t address, uint8_t *data_out, uint16_t len );

/**
 * @brief 6LoWPAN T send command function.
 * @details This function issues a supported 6LoWPAN T Click radio command.
 * @param[in] ctx : Click context object.
 * See #c6lowpant_t object definition for detailed explanation.
 * @param[in] command : SNOP, SRES, or a radio strobe from SXOSCON through SNACK.
 * @return C6LOWPANT_OK on success, or C6LOWPANT_ERROR on invalid arguments or SPI failure.
 * @note SRES and SXOSCON include the required second SPI byte. Raw strobes do not update the cached mode.
 */
err_t c6lowpant_send_command ( c6lowpant_t *ctx, uint8_t command );

/**
 * @brief 6LoWPAN T get status function.
 * @details This function reads the 6LoWPAN T Click SPI status byte with a no-operation command.
 * @param[in] ctx : Click context object.
 * See #c6lowpant_t object definition for detailed explanation.
 * @param[out] status : Status byte with oscillator, RSSI, and radio activity flags.
 * @return C6LOWPANT_OK on success, or C6LOWPANT_ERROR on invalid arguments or SPI failure.
 * @note None.
 */
err_t c6lowpant_get_status ( c6lowpant_t *ctx, uint8_t *status );

/**
 * @brief 6LoWPAN T reset function.
 * @details This function powers and resets 6LoWPAN T Click, waits for its oscillator, and verifies its identity.
 * @param[in] ctx : Click context object.
 * See #c6lowpant_t object definition for detailed explanation.
 * @return C6LOWPANT_OK, C6LOWPANT_TIMEOUT if the oscillator does not start, or C6LOWPANT_ERROR.
 * @note Reset discards radio configuration and queued packets. Apply default configuration before using packet functions.
 */
err_t c6lowpant_reset ( c6lowpant_t *ctx );

/**
 * @brief 6LoWPAN T get identification function.
 * @details This function reads the 6LoWPAN T Click chip identification and revision registers.
 * @param[in] ctx : Click context object.
 * See #c6lowpant_t object definition for detailed explanation.
 * @param[out] chip_id : Chip identification byte; expected value is C6LOWPANT_CHIP_ID.
 * @param[out] version : Silicon revision byte.
 * @return C6LOWPANT_OK on success, or C6LOWPANT_ERROR on invalid arguments or SPI failure.
 * @note None.
 */
err_t c6lowpant_get_id ( c6lowpant_t *ctx, uint8_t *chip_id, uint8_t *version );

/**
 * @brief 6LoWPAN T set mode function.
 * @details This function selects 6LoWPAN T Click transmitter standby or continuous reception.
 * @param[in] ctx : Click context object.
 * See #c6lowpant_t object definition for detailed explanation.
 * @param[in] mode : C6LOWPANT_MODE_TX or C6LOWPANT_MODE_RX.
 * @return C6LOWPANT_OK on success, or C6LOWPANT_ERROR on invalid arguments or SPI failure.
 * @note Discards queued RX packets when changing modes. TX mode waits for c6lowpant_send_packet to transmit.
 */
err_t c6lowpant_set_mode ( c6lowpant_t *ctx, uint8_t mode );

/**
 * @brief 6LoWPAN T set channel function.
 * @details This function sets and verifies the 6LoWPAN T Click IEEE 802.15.4 channel.
 * @param[in] ctx : Click context object.
 * See #c6lowpant_t object definition for detailed explanation.
 * @param[in] channel : Channel index from 11 (2405 MHz) to 26 (2480 MHz).
 * @return C6LOWPANT_OK on success, or C6LOWPANT_ERROR on invalid arguments or SPI failure.
 * @note Use in TX standby. Both peers must use the same channel.
 */
err_t c6lowpant_set_channel ( c6lowpant_t *ctx, uint8_t channel );

/**
 * @brief 6LoWPAN T set address function.
 * @details This function sets and verifies the 6LoWPAN T Click PAN identifier and local short address.
 * @param[in] ctx : Click context object.
 * See #c6lowpant_t object definition for detailed explanation.
 * @param[in] pan_id : PAN identifier from 0x0000 to 0xFFFE.
 * @param[in] short_addr : Local short address from 0x0000 to 0xFFFD.
 * @return C6LOWPANT_OK on success, or C6LOWPANT_ERROR on invalid arguments or SPI failure.
 * @note Use in TX standby. Updates the cached addresses used to build outgoing MAC headers.
 */
err_t c6lowpant_set_address ( c6lowpant_t *ctx, uint16_t pan_id, uint16_t short_addr );

/**
 * @brief 6LoWPAN T send packet function.
 * @details This function sends a short-address 6LoWPAN T Click data frame after clear-channel assessment.
 * @param[in] ctx : Click context object.
 * See #c6lowpant_t object definition for detailed explanation.
 * @param[in] destination : Destination short address, or C6LOWPANT_BROADCAST_ADDR.
 * @param[in] data_in : Application payload bytes.
 * @param[in] len : Payload size from 1 to C6LOWPANT_MAX_PAYLOAD_SIZE.
 * @return C6LOWPANT_OK if sent, C6LOWPANT_CHANNEL_BUSY, C6LOWPANT_TIMEOUT, or C6LOWPANT_ERROR.
 * @note Success means transmission completed, not delivery confirmation. No ACK or automatic retry is requested.
 * Restores the selected mode and discards queued RX packets. Call from one execution context only.
 */
err_t c6lowpant_send_packet ( c6lowpant_t *ctx, uint16_t destination, uint8_t *data_in, uint8_t len );

/**
 * @brief 6LoWPAN T receive packet function.
 * @details This function reads and validates one 6LoWPAN T Click short-address data frame.
 * @param[in] ctx : Click context object.
 * See #c6lowpant_t object definition for detailed explanation.
 * @param[out] data_out : Buffer for the application payload; the data is not null-terminated.
 * @param[in] capacity : Available output buffer size in bytes.
 * @param[out] info : Packet information; length is zero unless a valid packet is returned.
 * See #c6lowpant_packet_info_t object definition for detailed explanation.
 * @return C6LOWPANT_OK, C6LOWPANT_NO_DATA, C6LOWPANT_FRAME_ERROR, C6LOWPANT_BUFFER_ERROR, or C6LOWPANT_ERROR.
 * @note Accepts the unencrypted, PAN-compressed frame format produced by c6lowpant_send_packet.
 * Bad-CRC and unsupported frames are discarded. FIFO recovery discards all queued frames.
 * RSSI uses the reference-design offset; correlation is raw and is not a calibrated LQI.
 */
err_t c6lowpant_receive_packet ( c6lowpant_t *ctx, uint8_t *data_out, uint8_t capacity, c6lowpant_packet_info_t *info );

#ifdef __cplusplus
}
#endif
#endif // C6LOWPANT_H

/*! @} */ // c6lowpant

// ------------------------------------------------------------------------ END
