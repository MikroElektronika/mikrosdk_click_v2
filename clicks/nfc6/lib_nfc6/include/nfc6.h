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
 * @file nfc6.h
 * @brief This file contains API for NFC 6 Click Driver.
 */

#ifndef NFC6_H
#define NFC6_H

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
 * @addtogroup nfc6 NFC 6 Click Driver
 * @brief API for configuring and manipulating NFC 6 Click driver.
 * @{
 */

/**
 * @defgroup nfc6_reg NFC 6 Registers List
 * @brief List of registers of NFC 6 Click driver.
 */

/**
 * @addtogroup nfc6_reg
 * @{
 */

/**
 * @brief NFC 6 control bytes.
 * @details Specified control bytes of NFC 6 Click driver.
 */
#define NFC6_CONTROL_SEND_COMMAND           0x00
#define NFC6_CONTROL_READ_DATA              0x02
#define NFC6_CONTROL_POLL_READY             0x03
#define NFC6_CONTROL_RESET_DEVICE           0x01
#define NFC6_CONTROL_POLL_READY_FLAG        0x08

/**
 * @brief NFC 6 command bytes.
 * @details Specified command bytes of NFC 6 Click driver.
 */
#define NFC6_CMD_IDN                        0x01
#define NFC6_CMD_PROTOCOL_SELECT            0x02
#define NFC6_CMD_POLL_FIELD                 0x03
#define NFC6_CMD_SEND_RECV                  0x04
#define NFC6_CMD_LISTEN                     0x05
#define NFC6_CMD_SEND                       0x06
#define NFC6_CMD_IDLE                       0x07
#define NFC6_CMD_RD_REG                     0x08
#define NFC6_CMD_WR_REG                     0x09
#define NFC6_CMD_SUB_FREQ_RES               0x0B
#define NFC6_CMD_AC_FILTER                  0x0D
#define NFC6_CMD_ECHO                       0x55

/*! @} */ // nfc6_reg

/**
 * @defgroup nfc6_set NFC 6 Registers Settings
 * @brief Settings for registers of NFC 6 Click driver.
 */

/**
 * @addtogroup nfc6_set
 * @{
 */

/**
 * @brief NFC 6 response setting.
 * @details Specified response setting of NFC 6 Click driver.
 */
#define NFC6_RSP_FIXED_BYTES                0x80
#define NFC6_RSP_FIXED_BYTES_MASK           0x8F
#define NFC6_RSP_LONG_FRAME_MASK            0x60
#define NFC6_RSP_OK                         0x00
#define NFC6_RSP_ECHO                       0x55
#define NFC6_RSP_MAX_DATA_LEN               528u
#define NFC6_RSP_READY_TIMEOUT_MS           5000ul

/**
 * @brief NFC 6 IDLE command setting for calibration of tag detector.
 * @details Specified IDLE command setting for calibration of tag detector of NFC 6 Click driver.
 */
#define NFC6_IDLE_CMD_LENGTH                14
#define NFC6_IDLE_CMD_WU_SOURCE             0x03
#define NFC6_IDLE_CMD_ENTER_CTRL_L          0xA1
#define NFC6_IDLE_CMD_ENTER_CTRL_H          0x00
#define NFC6_IDLE_CMD_WU_CTRL_L             0xF8
#define NFC6_IDLE_CMD_WU_CTRL_H             0x01
#define NFC6_IDLE_CMD_LEAVE_CTRL_L          0x18
#define NFC6_IDLE_CMD_LEAVE_CTRL_H          0x00
#define NFC6_IDLE_CMD_WU_PERIOD             0x20
#define NFC6_IDLE_CMD_OSC_START             0x60
#define NFC6_IDLE_CMD_DAC_START             0x60
#define NFC6_IDLE_CMD_DAC_DATA_L            0x00
#define NFC6_IDLE_CMD_DAC_DATA_H            0x00
#define NFC6_IDLE_CMD_DAC_DATA_H_MIN        0x00
#define NFC6_IDLE_CMD_DAC_DATA_H_MAX        0xFC
#define NFC6_IDLE_CMD_SWINGS_CNT            0x3F
#define NFC6_IDLE_CMD_MAX_SLEEP             0x01
#define NFC6_IDLE_RSP_TIMEOUT               0x01
#define NFC6_IDLE_RSP_TAG_DETECT            0x02
#define NFC6_IDLE_RSP_LENGTH                1
#define NFC6_IDLE_CALIB_START               0x80

/**
 * @brief NFC 6 protocol selection setting.
 * @details Specified protocol selection setting of NFC 6 Click driver.
 */
#define NFC6_PROTOCOL_FIELD_OFF             0
#define NFC6_PROTOCOL_ISO_15693             1
#define NFC6_PROTOCOL_ISO_14443A            2
#define NFC6_PROTOCOL_ISO_14443B            3
#define NFC6_PROTOCOL_FELICA                4

/**
 * @brief NFC 6 MIFARE classic setting.
 * @details Specified MIFARE classic setting of NFC 6 Click driver.
 */
#define NFC6_TAG_UID_RSP_MAX_DATA_LEN       10
#define NFC6_TAG_UID_MAX_LEN                7
#define NFC6_MIFARE_REQA                    0x26
#define NFC6_MIFARE_REQA_LEN                0x07
#define NFC6_MIFARE_WUPA                    0x52
#define NFC6_MIFARE_CL1                     0x93
#define NFC6_MIFARE_CL2                     0x95
#define NFC6_MIFARE_ANTICOLLISION           0x20
#define NFC6_MIFARE_ANTICOLLISION_LEN       0x08
#define NFC6_MIFARE_SELECT                  0x70
#define NFC6_MIFARE_CASCADE_TAG             0x88
#define NFC6_MIFARE_READ                    0x30
#define NFC6_MIFARE_WRITE                   0xA0

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b nfc6_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define NFC6_SET_DATA_SAMPLE_EDGE           SET_SPI_DATA_SAMPLE_EDGE
#define NFC6_SET_DATA_SAMPLE_MIDDLE         SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // nfc6_set

/**
 * @defgroup nfc6_map NFC 6 MikroBUS Map
 * @brief MikroBUS pin mapping of NFC 6 Click driver.
 */

/**
 * @addtogroup nfc6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of NFC 6 Click to the selected MikroBUS.
 */
#define NFC6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.irq_in = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.irq_out = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // nfc6_map
/*! @} */ // nfc6

/**
 * @brief NFC 6 Click context object.
 * @details Context object definition of NFC 6 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t irq_in;       /**< Interrupt input pin for ST25R95 device. */

    // Input pins
    digital_in_t irq_out;       /**< Interrupt output pin of ST25R95 device. */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t chip_select;     /**< Chip select pin descriptor (used for SPI driver). */
    
    uint8_t cal_dac_data_h;     /**< Calibrated DAC data H value. */

} nfc6_t;

/**
 * @brief NFC 6 Click configuration object.
 * @details Configuration object definition of NFC 6 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t irq_in;          /**< Interrupt input pin for ST25R95 device. */
    pin_name_t irq_out;         /**< Interrupt output pin of ST25R95 device. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} nfc6_cfg_t;

/**
 * @brief NFC 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    NFC6_OK = 0,
    NFC6_ERROR = -1

} nfc6_return_value_t;

/*!
 * @addtogroup nfc6 NFC 6 Click Driver
 * @brief API for configuring and manipulating NFC 6 Click driver.
 * @{
 */

/**
 * @brief NFC 6 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #nfc6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void nfc6_cfg_setup ( nfc6_cfg_t *cfg );

/**
 * @brief NFC 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #nfc6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #nfc6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc6_init ( nfc6_t *ctx, nfc6_cfg_t *cfg );

/**
 * @brief NFC 6 default configuration function.
 * @details This function executes a default configuration of NFC 6
 * click board.
 * @param[in] ctx : Click context object.
 * See #nfc6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t nfc6_default_cfg ( nfc6_t *ctx );

/**
 * @brief NFC 6 send command function.
 * @details This function sends a desired command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #nfc6_t object definition for detailed explanation.
 * @param[in] cmd : Command byte to send.
 * @param[in] data_in : Command parameter buffer.
 * @param[in] len : Number of bytes in parameter buffer.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc6_send_command ( nfc6_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );

/**
 * @brief NFC 6 read data function.
 * @details This function reads a response data bytes by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #nfc6_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] buffer_size : Data output buffer size.
 * @param[out] rx_len : Number of bytes that were available for read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c >0 - Response code error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc6_read_data ( nfc6_t *ctx, uint8_t *data_out, uint16_t buffer_size, uint16_t *rx_len );

/**
 * @brief NFC 6 poll ready function.
 * @details This function waits for the device data ready indication via command interface.
 * @param[in] ctx : Click context object.
 * See #nfc6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc6_poll_ready ( nfc6_t *ctx );

/**
 * @brief NFC 6 poll ready irq function.
 * @details This function waits for the device data ready indication via IRQ pin.
 * @param[in] ctx : Click context object.
 * See #nfc6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc6_poll_ready_irq ( nfc6_t *ctx );

/**
 * @brief NFC 6 reset device function.
 * @details This function performs a device software reset.
 * @param[in] ctx : Click context object.
 * See #nfc6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc6_reset_device ( nfc6_t *ctx );

/**
 * @brief NFC 6 check command echo function.
 * @details This function checks the communication by sending and checking
 * the command echo response.
 * @param[in] ctx : Click context object.
 * See #nfc6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc6_check_command_echo ( nfc6_t *ctx );

/**
 * @brief NFC 6 pulse irq in function.
 * @details This function sends a pulse on the IRQ_IN pin.
 * @param[in] ctx : Click context object.
 * See #nfc6_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void nfc6_pulse_irq_in ( nfc6_t *ctx );

/**
 * @brief NFC 6 set irq in pin function.
 * @details This function sets the IRQ_IN pin logic state.
 * @param[in] ctx : Click context object.
 * See #nfc6_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void nfc6_set_irq_in_pin ( nfc6_t *ctx, uint8_t state );

/**
 * @brief NFC 6 get irq out pin function.
 * @details This function returns the IRQ_OUT pin logic state.
 * @param[in] ctx : Click context object.
 * See #nfc6_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t nfc6_get_irq_out_pin ( nfc6_t *ctx );

/**
 * @brief NFC 6 calibrate device function.
 * @details This function performs the tag detection calibration.
 * @param[in] ctx : Click context object.
 * See #nfc6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc6_calibrate_device ( nfc6_t *ctx );

/**
 * @brief NFC 6 select protocol function.
 * @details This function selects the RF communication protocol and prepares
 * the ST25R95 for communication with a contactless tag.
 * @param[in] ctx : Click context object.
 * See #nfc6_t object definition for detailed explanation.
 * @param[in] protocol : @li @c 0 - RF field OFF,
 *                       @li @c 1 - ISO/IEC 15693,
 *                       @li @c 2 - ISO/IEC 14443-A,
 *                       @li @c 3 - ISO/IEC 14443-B,
 *                       @li @c 4 - FeliCa.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc6_select_protocol ( nfc6_t *ctx, uint8_t protocol );

/**
 * @brief NFC 6 read MIFARE tag UID function.
 * @details This function reads the UID of a MIFARE ISO14443-A type tags with 4-byte or 7-byte UIDs.
 * @param[in] ctx : Click context object.
 * See #nfc6_t object definition for detailed explanation.
 * @param[out] tag_uid : MIFARE tag UID array (up to 7 bytes).
 * @param[out] tag_uid_len : MIFARE tag UID lenght.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc6_read_mifare_tag_uid ( nfc6_t *ctx, uint8_t *tag_uid, uint8_t *tag_uid_len );

#ifdef __cplusplus
}
#endif
#endif // NFC6_H

/*! @} */ // nfc6

// ------------------------------------------------------------------------ END
