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
 * @file texttospeech.h
 * @brief This file contains API for TextToSpeech Click Driver.
 */

#ifndef TEXTTOSPEECH_H
#define TEXTTOSPEECH_H

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
 * @addtogroup texttospeech TextToSpeech Click Driver
 * @brief API for configuring and manipulating TextToSpeech Click driver.
 * @{
 */

/**
 * @defgroup texttospeech_cmd TextToSpeech Messages
 * @brief Message identifiers of TextToSpeech Click driver.
 */

/**
 * @addtogroup texttospeech_cmd
 * @{
 */

/**
 * @brief TextToSpeech ISC message identifiers.
 * @details Identifiers from the S1V30120 message protocol. Header fields use little-endian byte order.
 * The SPI bus transfers each byte MSB first. REQ, RESP, and IND mean request, response, and indication.
 * Low-level messages require the payload and operating sequence specified by Epson.
 */
#define TEXTTOSPEECH_ISC_ERROR_IND                          0x0000
#define TEXTTOSPEECH_ISC_TEST_REQ                           0x0003
#define TEXTTOSPEECH_ISC_TEST_RESP                          0x0004
#define TEXTTOSPEECH_ISC_VERSION_REQ                        0x0005
#define TEXTTOSPEECH_ISC_VERSION_RESP                       0x0006
#define TEXTTOSPEECH_ISC_MSG_BLOCKED_RESP                   0x0007
#define TEXTTOSPEECH_ISC_AUDIO_CONFIG_REQ                   0x0008
#define TEXTTOSPEECH_ISC_AUDIO_CONFIG_RESP                  0x0009
#define TEXTTOSPEECH_ISC_AUDIO_VOLUME_REQ                   0x000A
#define TEXTTOSPEECH_ISC_AUDIO_VOLUME_RESP                  0x000B
#define TEXTTOSPEECH_ISC_AUDIO_MUTE_REQ                     0x000C
#define TEXTTOSPEECH_ISC_AUDIO_MUTE_RESP                    0x000D
#define TEXTTOSPEECH_ISC_TTS_CONFIG_REQ                     0x0012
#define TEXTTOSPEECH_ISC_TTS_CONFIG_RESP                    0x0013
#define TEXTTOSPEECH_ISC_TTS_SPEAK_REQ                      0x0014
#define TEXTTOSPEECH_ISC_TTS_SPEAK_RESP                     0x0015
#define TEXTTOSPEECH_ISC_TTS_PAUSE_REQ                      0x0016
#define TEXTTOSPEECH_ISC_TTS_PAUSE_RESP                     0x0017
#define TEXTTOSPEECH_ISC_TTS_STOP_REQ                       0x0018
#define TEXTTOSPEECH_ISC_TTS_STOP_RESP                      0x0019
#define TEXTTOSPEECH_ISC_TTS_READY_IND                      0x0020
#define TEXTTOSPEECH_ISC_TTS_FINISHED_IND                   0x0021
#define TEXTTOSPEECH_ISC_GPIO_REGISTER_REQ                  0x0045
#define TEXTTOSPEECH_ISC_GPIO_REGISTER_RESP                 0x0046
#define TEXTTOSPEECH_ISC_GPIO_OUTPUT_CONFIG_REQ             0x004E
#define TEXTTOSPEECH_ISC_GPIO_OUTPUT_CONFIG_RESP            0x004F
#define TEXTTOSPEECH_ISC_GPIO_OUTPUT_SET_REQ                0x0050
#define TEXTTOSPEECH_ISC_GPIO_OUTPUT_SET_RESP               0x0051
#define TEXTTOSPEECH_ISC_SPCODEC_CONFIG_REQ                 0x0056
#define TEXTTOSPEECH_ISC_SPCODEC_CONFIG_RESP                0x0057
#define TEXTTOSPEECH_ISC_SPCODEC_START_REQ                  0x0058
#define TEXTTOSPEECH_ISC_SPCODEC_START_RESP                 0x0059
#define TEXTTOSPEECH_ISC_SPCODEC_STOP_REQ                   0x005A
#define TEXTTOSPEECH_ISC_SPCODEC_STOP_RESP                  0x005B
#define TEXTTOSPEECH_ISC_SPCODEC_PAUSE_REQ                  0x005C
#define TEXTTOSPEECH_ISC_SPCODEC_PAUSE_RESP                 0x005D
#define TEXTTOSPEECH_ISC_SPCODEC_READY_IND                  0x0060
#define TEXTTOSPEECH_ISC_SPCODEC_FINISHED_IND               0x0061
#define TEXTTOSPEECH_ISC_PMAN_CONFIG_REQ                    0x0062
#define TEXTTOSPEECH_ISC_PMAN_CONFIG_RESP                   0x0063
#define TEXTTOSPEECH_ISC_PMAN_STANDBY_ENTRY_REQ             0x0064
#define TEXTTOSPEECH_ISC_PMAN_STANDBY_ENTRY_RESP            0x0065
#define TEXTTOSPEECH_ISC_PMAN_STANDBY_EXIT_IND              0x0066
#define TEXTTOSPEECH_ISC_TTS_UDICT_DATA_REQ                 0x00CE
#define TEXTTOSPEECH_ISC_TTS_UDICT_DATA_RESP                0x00D0
#define TEXTTOSPEECH_ISC_BOOT_LOAD_REQ                      0x1000
#define TEXTTOSPEECH_ISC_BOOT_LOAD_RESP                     0x1001
#define TEXTTOSPEECH_ISC_BOOT_RUN_REQ                       0x1002
#define TEXTTOSPEECH_ISC_BOOT_RUN_RESP                      0x1003

/*! @} */ // texttospeech_cmd

/**
 * @defgroup texttospeech_set TextToSpeech Settings
 * @brief Settings of TextToSpeech Click driver.
 */

/**
 * @addtogroup texttospeech_set
 * @{
 */

/**
 * @brief TextToSpeech voice selection.
 * @details Voice indices supported by the S1V30120 protocol; other indices are reserved.
 */
#define TEXTTOSPEECH_VOICE_PAUL                             0
#define TEXTTOSPEECH_VOICE_HARRY                            1
#define TEXTTOSPEECH_VOICE_DENNIS                           4
#define TEXTTOSPEECH_VOICE_WENDY                            8

/**
 * @brief TextToSpeech language and parser selection.
 * @details Text uses ISO-8859-1 encoding. DECtalk mode accepts DECtalk inline commands;
 * Epson mode enables the additional Epson text parser. Available languages depend on the firmware image.
 */
#define TEXTTOSPEECH_LANGUAGE_US_ENGLISH                    0
#define TEXTTOSPEECH_LANGUAGE_CASTILIAN_SPANISH             1
#define TEXTTOSPEECH_LANGUAGE_LATIN_SPANISH                 4
#define TEXTTOSPEECH_PARSER_DECTALK                         0
#define TEXTTOSPEECH_PARSER_EPSON                           1

/**
 * @brief TextToSpeech operating limits and defaults.
 * @details Speech rate is in words per minute and volume is absolute analogue gain in dB.
 * The maximum text length excludes the terminating null byte. Audio is mono at 11.025 kHz.
 */
#define TEXTTOSPEECH_RATE_MIN                               75
#define TEXTTOSPEECH_RATE_MAX                               600
#define TEXTTOSPEECH_RATE_DEFAULT                           200
#define TEXTTOSPEECH_VOLUME_MIN                             (-48)
#define TEXTTOSPEECH_VOLUME_MAX                             18
#define TEXTTOSPEECH_VOLUME_DEFAULT                         (-12)
#define TEXTTOSPEECH_TEXT_MAX_LEN                           2047
#define TEXTTOSPEECH_SPI_SPEED                              500000
#define TEXTTOSPEECH_RESPONSE_TIMEOUT_MS                    600
#define TEXTTOSPEECH_RESPONSE_SIZE                          20
#define TEXTTOSPEECH_FEATURE_TTS                            0x00000001UL

/**
 * @brief TextToSpeech control pin states.
 * @details MUTE is active high, reset is active low, and DRDY is high when a message is available.
 */
#define TEXTTOSPEECH_MUTE_DISABLE                           0
#define TEXTTOSPEECH_MUTE_ENABLE                            1
#define TEXTTOSPEECH_PAUSE_DISABLE                          0
#define TEXTTOSPEECH_PAUSE_ENABLE                           1

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b texttospeech_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define TEXTTOSPEECH_SET_DATA_SAMPLE_EDGE                   SET_SPI_DATA_SAMPLE_EDGE
#define TEXTTOSPEECH_SET_DATA_SAMPLE_MIDDLE                 SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // texttospeech_set

/**
 * @defgroup texttospeech_map TextToSpeech MikroBUS Map
 * @brief MikroBUS pin mapping of TextToSpeech Click driver.
 */

/**
 * @addtogroup texttospeech_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of TextToSpeech Click to the selected MikroBUS.
 */
#define TEXTTOSPEECH_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.mute = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.drdy = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // texttospeech_map
/*! @} */ // texttospeech

/**
 * @brief TextToSpeech Click context object.
 * @details Context object definition of TextToSpeech Click driver.
 * @note The driver is blocking and must be called from one execution context.
 * Receive state is preserved across SPI transfers so responses arriving during transmission are retained.
 * Use texttospeech_default_cfg after a latched receive error to reload the device.
 */
typedef struct
{
    // Output pins
    digital_out_t mute;         /**< Active-high amplifier mute pin. */
    digital_out_t rst;          /**< Active-low S1V30120 reset pin. */

    // Input pins
    digital_in_t drdy;          /**< Active-high message-ready input. */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t chip_select;     /**< Chip select pin descriptor (used for SPI driver). */
    uint8_t rx_buffer[ TEXTTOSPEECH_RESPONSE_SIZE ];        /**< Current ISC frame, including its header. */
    uint8_t response[ TEXTTOSPEECH_RESPONSE_SIZE - 4 ];     /**< Saved response payload. */
    uint16_t response_id;       /**< Identifier of the saved response. */
    uint16_t device_status;     /**< Most recent status or error code reported by the S1V30120. */
    uint8_t response_len;       /**< Length of the saved response payload. */
    uint8_t response_ready;     /**< One response is waiting to be consumed. */
    uint8_t request_pending;    /**< A request has been sent and its response has not been consumed. */
    uint8_t rx_active;          /**< A start byte was received and its frame is incomplete. */
    uint8_t rx_index;           /**< Number of header/payload bytes received. */
    uint16_t rx_length;         /**< Declared ISC frame length. */
    uint8_t rx_padding;         /**< Additional clocks required after the most recent received frame. */
    uint8_t speech_ready;       /**< TTS can accept a new text message. */
    uint8_t speech_finished;    /**< TTS has finished the submitted text. */
    err_t rx_error;             /**< Latched communication, framing, timeout, or device indication error. */

} texttospeech_t;

/**
 * @brief TextToSpeech Click configuration object.
 * @details Configuration object definition of TextToSpeech Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t mute;            /**< Amplifier mute pin. */
    pin_name_t rst;             /**< S1V30120 reset pin. */
    pin_name_t drdy;            /**< S1V30120 message-ready pin. */

    // static variable
    uint32_t                            spi_speed;      /**< SPI serial speed. */
    spi_master_mode_t                   spi_mode;       /**< SPI master mode. */
    spi_master_chip_select_polarity_t   cs_polarity;    /**< Chip select pin polarity. */

} texttospeech_cfg_t;

/**
 * @brief TextToSpeech version data.
 * @details Hardware and firmware identifiers returned by ISC_VERSION_RESP.
 * Feature and language masks are valid only after firmware upload and host registration.
 */
typedef struct
{
    uint8_t hardware_major;     /**< Hardware integer identifier. */
    uint8_t hardware_minor;     /**< Hardware fractional identifier. */
    uint8_t firmware_major;     /**< Firmware X version. */
    uint8_t firmware_minor;     /**< Firmware Y version. */
    uint8_t firmware_patch;     /**< Firmware Z version. */
    uint32_t features;          /**< Firmware feature mask. */
    uint32_t languages;         /**< Firmware language mask. */

} texttospeech_version_t;

/**
 * @brief TextToSpeech Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TEXTTOSPEECH_OK = 0,
    TEXTTOSPEECH_ERROR = -1,             /**< Invalid argument or SPI/GPIO failure. */
    TEXTTOSPEECH_ERROR_TIMEOUT = -2,     /**< Response or speech-completion wait expired. */
    TEXTTOSPEECH_ERROR_PROTOCOL = -3,    /**< Invalid frame, unexpected response, or response overflow. */
    TEXTTOSPEECH_ERROR_DEVICE = -4,      /**< S1V30120 rejected the request or reported an error. */
    TEXTTOSPEECH_ERROR_BUSY = -5         /**< Previous request or speech is still active. */

} texttospeech_return_value_t;

/*!
 * @addtogroup texttospeech TextToSpeech Click Driver
 * @brief API for configuring and manipulating TextToSpeech Click driver.
 * @{
 */

/**
 * @brief TextToSpeech configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #texttospeech_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note All used pins are set to the unconnected state. SPI defaults to mode 3 at 500 kHz.
 */
void texttospeech_cfg_setup ( texttospeech_cfg_t *cfg );

/**
 * @brief TextToSpeech initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board, mutes the amplifier, and holds the S1V30120 in reset.
 * @param[out] ctx : Click context object.
 * See #texttospeech_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #texttospeech_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - SPI peripheral initialization error.
 * See #err_t definition for detailed explanation.
 * @note SPI mode 3 and active-low CS are required. Call texttospeech_default_cfg before speaking.
 */
err_t texttospeech_init ( texttospeech_t *ctx, texttospeech_cfg_t *cfg );

/**
 * @brief TextToSpeech default configuration function.
 * @details This function resets the device, uploads the supplied firmware, registers the host,
 * and configures mono audio and US English speech using Paul at 200 words per minute and -12 dB gain.
 * @param[in] ctx : Click context object.
 * See #texttospeech_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid argument or communication error,
 *         @li @c -2 - Timeout,
 *         @li @c -3 - Protocol error,
 *         @li @c -4 - Device error,
 *         @li @c -5 - Device busy.
 * See #texttospeech_return_value_t definition for detailed explanation.
 * @note The amplifier remains muted until configuration succeeds. The firmware is reloaded after each reset.
 * The firmware image occupies 31208 bytes of program memory; allow additional space for the driver and application.
 */
err_t texttospeech_default_cfg ( texttospeech_t *ctx );

/**
 * @brief TextToSpeech reset function.
 * @details This function mutes the amplifier, applies a hardware reset, and clears receive state.
 * @param[in] ctx : Click context object.
 * See #texttospeech_t object definition for detailed explanation.
 * @return Nothing.
 * @note The 150 ms boot wait uses fixed delays without SPI clocks. Reload firmware before speaking.
 */
void texttospeech_reset ( texttospeech_t *ctx );

/**
 * @brief TextToSpeech write message function.
 * @details This function sends an ISC header, payload, and required padding while receiving all
 * simultaneous SPI input. The response is retained separately from speech indications.
 * @param[in] ctx : Click context object.
 * See #texttospeech_t object definition for detailed explanation.
 * @param[in] message_id : ISC request identifier.
 * @param[in] data_in : Payload buffer; may be NULL only when len is zero.
 * @param[in] len : Payload length, excluding the four-byte ISC header.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid argument or communication error,
 *         @li @c -2 - Timeout,
 *         @li @c -3 - Protocol error,
 *         @li @c -4 - Device error,
 *         @li @c -5 - Device busy.
 * See #texttospeech_return_value_t definition for detailed explanation.
 * @note Call texttospeech_read_response before sending another request. Protocol-specific payload limits apply.
 * Boot payloads are limited to 2044 bytes; main-mode payloads are limited to 2112 bytes.
 */
err_t texttospeech_write_message ( texttospeech_t *ctx, uint16_t message_id, uint8_t *data_in, uint16_t len );

/**
 * @brief TextToSpeech read response function.
 * @details This function waits for the requested response, checks its identifier and payload size,
 * and copies the payload after flushing receive padding.
 * @param[in] ctx : Click context object.
 * See #texttospeech_t object definition for detailed explanation.
 * @param[in] response_id : Expected ISC response identifier.
 * @param[out] data_out : Output buffer of len bytes; unchanged on error.
 * @param[in] len : Exact expected payload length, from 0 to 16 bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid argument or communication error,
 *         @li @c -2 - Timeout,
 *         @li @c -3 - Protocol error,
 *         @li @c -4 - Device error,
 *         @li @c -5 - Device busy.
 * See #texttospeech_return_value_t definition for detailed explanation.
 * @note The response polling timeout is TEXTTOSPEECH_RESPONSE_TIMEOUT_MS, plus SPI and call overhead.
 * A successful read verifies framing only; the caller must interpret the returned device status.
 */
err_t texttospeech_read_response ( texttospeech_t *ctx, uint16_t response_id, uint8_t *data_out, uint8_t len );

/**
 * @brief TextToSpeech process function.
 * @details This function clocks pending receive data and updates response and speech indication state.
 * @param[in] ctx : Click context object.
 * See #texttospeech_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid argument or communication error,
 *         @li @c -2 - Timeout,
 *         @li @c -3 - Protocol error,
 *         @li @c -4 - Device error,
 *         @li @c -5 - Device busy.
 * See #texttospeech_return_value_t definition for detailed explanation.
 * @note Call regularly during asynchronous speech. Each call processes at most 64 SPI bytes.
 */
err_t texttospeech_process ( texttospeech_t *ctx );

/**
 * @brief TextToSpeech get version function.
 * @details This function reads the hardware identifiers, firmware version, and supported feature masks.
 * @param[in] ctx : Click context object.
 * See #texttospeech_t object definition for detailed explanation.
 * @param[out] version : Version data; unchanged on error.
 * See #texttospeech_version_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid argument or communication error,
 *         @li @c -2 - Timeout,
 *         @li @c -3 - Protocol error,
 *         @li @c -4 - Device error,
 *         @li @c -5 - Device busy.
 * See #texttospeech_return_value_t definition for detailed explanation.
 * @note Firmware fields are reserved in boot mode. Read after texttospeech_default_cfg for valid firmware data.
 */
err_t texttospeech_get_version ( texttospeech_t *ctx, texttospeech_version_t *version );

/**
 * @brief TextToSpeech set configuration function.
 * @details This function configures the TTS voice, language, parser, and speaking rate.
 * @param[in] ctx : Click context object.
 * See #texttospeech_t object definition for detailed explanation.
 * @param[in] voice : TEXTTOSPEECH_VOICE_* selection.
 * @param[in] language : TEXTTOSPEECH_LANGUAGE_* selection.
 * @param[in] rate : Speaking rate from 75 to 600 words per minute.
 * @param[in] parser : TEXTTOSPEECH_PARSER_DECTALK or TEXTTOSPEECH_PARSER_EPSON.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid argument or communication error,
 *         @li @c -2 - Timeout,
 *         @li @c -3 - Protocol error,
 *         @li @c -4 - Device error,
 *         @li @c -5 - Device busy.
 * See #texttospeech_return_value_t definition for detailed explanation.
 * @note Configure before speaking. Language availability depends on the loaded firmware.
 */
err_t texttospeech_set_config ( texttospeech_t *ctx, uint8_t voice, uint8_t language, uint16_t rate, uint8_t parser );

/**
 * @brief TextToSpeech set volume function.
 * @details This function sets absolute analogue gain and configures mono 11.025 kHz audio output.
 * @param[in] ctx : Click context object.
 * See #texttospeech_t object definition for detailed explanation.
 * @param[in] gain_db : Gain from -48 to +18 dB.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid argument or communication error,
 *         @li @c -2 - Timeout,
 *         @li @c -3 - Protocol error,
 *         @li @c -4 - Device error,
 *         @li @c -5 - Device busy.
 * See #texttospeech_return_value_t definition for detailed explanation.
 * @note Uses ISC_AUDIO_CONFIG_REQ. ISC_AUDIO_VOLUME_REQ changes gain relatively, not absolutely.
 * Gain above 0 dB can clip synthesized audio.
 */
err_t texttospeech_set_volume ( texttospeech_t *ctx, int8_t gain_db );

/**
 * @brief TextToSpeech speak function.
 * @details This function sends a null-terminated text message and verifies that speech was accepted.
 * @param[in] ctx : Click context object.
 * See #texttospeech_t object definition for detailed explanation.
 * @param[in] text : ISO-8859-1 text, from 1 to 2047 characters excluding the null terminator.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid argument or communication error,
 *         @li @c -2 - Timeout,
 *         @li @c -3 - Protocol error,
 *         @li @c -4 - Device error,
 *         @li @c -5 - Device busy.
 * See #texttospeech_return_value_t definition for detailed explanation.
 * @note End the text with sentence punctuation. Success means accepted, not playback finished.
 * Call texttospeech_wait_complete to wait for completion. texttospeech_stop ends speech without resetting TTS.
 */
err_t texttospeech_speak ( texttospeech_t *ctx, char *text );

/**
 * @brief TextToSpeech wait complete function.
 * @details This function processes received messages until speech is finished and TTS is ready.
 * @param[in] ctx : Click context object.
 * See #texttospeech_t object definition for detailed explanation.
 * @param[in] timeout_ms : Maximum number of one-millisecond polling delays.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid argument or communication error,
 *         @li @c -2 - Timeout,
 *         @li @c -3 - Protocol error,
 *         @li @c -4 - Device error,
 *         @li @c -5 - Device busy.
 * See #texttospeech_return_value_t definition for detailed explanation.
 * @note SPI and call overhead add to the polling time. A speech timeout does not stop playback;
 * call texttospeech_stop to terminate it.
 */
err_t texttospeech_wait_complete ( texttospeech_t *ctx, uint32_t timeout_ms );

/**
 * @brief TextToSpeech set pause function.
 * @details This function pauses or resumes speech output.
 * @param[in] ctx : Click context object.
 * See #texttospeech_t object definition for detailed explanation.
 * @param[in] enable : TEXTTOSPEECH_PAUSE_ENABLE or TEXTTOSPEECH_PAUSE_DISABLE.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid argument or communication error,
 *         @li @c -2 - Timeout,
 *         @li @c -3 - Protocol error,
 *         @li @c -4 - Device error,
 *         @li @c -5 - Device busy.
 * See #texttospeech_return_value_t definition for detailed explanation.
 * @note Buffered audio may continue briefly after pause is requested.
 */
err_t texttospeech_set_pause ( texttospeech_t *ctx, uint8_t enable );

/**
 * @brief TextToSpeech stop function.
 * @details This function stops speech and clears pending text while retaining TTS configuration.
 * @param[in] ctx : Click context object.
 * See #texttospeech_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid argument or communication error,
 *         @li @c -2 - Timeout,
 *         @li @c -3 - Protocol error,
 *         @li @c -4 - Device error,
 *         @li @c -5 - Device busy.
 * See #texttospeech_return_value_t definition for detailed explanation.
 * @note The TTS configuration and allocated resources are retained, allowing the next text to be spoken immediately.
 */
err_t texttospeech_stop ( texttospeech_t *ctx );

/**
 * @brief TextToSpeech set mute function.
 * @details This function controls the Click board amplifier mute pin.
 * @param[in] ctx : Click context object.
 * See #texttospeech_t object definition for detailed explanation.
 * @param[in] enable : Zero unmutes the amplifier; any nonzero value mutes it.
 * @return Nothing.
 * @note Muting the amplifier does not pause speech synthesis.
 */
void texttospeech_set_mute ( texttospeech_t *ctx, uint8_t enable );

#ifdef __cplusplus
}
#endif
#endif // TEXTTOSPEECH_H

/*! @} */ // texttospeech

// ------------------------------------------------------------------------ END
