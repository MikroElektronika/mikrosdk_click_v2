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
 * @file printer.h
 * @brief This file contains API for Printer Click Driver.
 */

#ifndef PRINTER_H
#define PRINTER_H

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

/*!
 * @addtogroup printer Printer Click Driver
 * @brief API for configuring and manipulating Printer Click driver.
 * @{
 */

/**
 * @defgroup printer_cmd Printer Device Settings
 * @brief Settings for registers of Printer Click driver.
 */

/**
 * @addtogroup printer_cmd
 * @{
 */

/**
 * @brief Printer control commands.
 * @details Specified setting for control commands of Printer Click driver.
 */
#define PRINTER_CMD_EOT                 0x04
#define PRINTER_CMD_ENQ                 0x05
#define PRINTER_CMD_HT                  0x09
#define PRINTER_CMD_LF                  0x0A
#define PRINTER_CMD_CR                  0x0D
#define PRINTER_CMD_DLE                 0x10
#define PRINTER_CMD_DC4                 0x14
#define PRINTER_CMD_ESC                 0x1B
#define PRINTER_CMD_FS                  0x1C
#define PRINTER_CMD_GS                  0x1D

/**
 * @brief Printer communication mode settings.
 * @details Specified setting for communication mode of Printer Click driver.
 */
#define PRINTER_COM_BAUD_RATE_9600      0x00
#define PRINTER_COM_BAUD_RATE_19200     0x01
#define PRINTER_COM_BAUD_RATE_38400     0x02
#define PRINTER_COM_BAUD_RATE_57600     0x03
#define PRINTER_COM_BAUD_RATE_115200    0x04
#define PRINTER_COM_FLOW_CTRL_OFF       0x00
#define PRINTER_COM_FLOW_CTRL_SW        0x01
#define PRINTER_COM_FLOW_CTRL_HW        0x02

/**
 * @brief Printer printer head settings.
 * @details Specified setting for printer head of Printer Click driver.
 */
#define PRINTER_HEAD_MM58_FTP628MCL101  0x00
#define PRINTER_HEAD_MM80_FTP638MCL101  0x01
#define PRINTER_HEAD_MM58_LTP02_245_13  0x02
#define PRINTER_HEAD_MM58_LTP02_245_C1  0x03

/**
 * @brief Printer font type settings.
 * @details Specified setting for font type of Printer Click driver.
 */
#define PRINTER_FONT_TYPE_NORMAL        0x00
#define PRINTER_FONT_TYPE_ITALIC        0x02
#define PRINTER_FONT_TYPE_BOLD          0x08
#define PRINTER_FONT_TYPE_DOUBLE_HEIGHT 0x10
#define PRINTER_FONT_TYPE_DOUBLE_WIDTH  0x20
#define PRINTER_FONT_TYPE_REVERSE       0x40
#define PRINTER_FONT_TYPE_UNDERLINE     0x80

/**
 * @brief Printer font size settings.
 * @details Specified setting for font size of Printer Click driver.
 */
#define PRINTER_FONT_SIZE_SMALL         0x01
#define PRINTER_FONT_SIZE_LARGE         0x02

/**
 * @brief Printer horizontal align settings.
 * @details Specified setting for horizontal align of Printer Click driver.
 */
#define PRINTER_ALIGN_LEFT              0x00
#define PRINTER_ALIGN_CENTER            0x01
#define PRINTER_ALIGN_RIGHT             0x02

/**
 * @brief Printer grayscale settings.
 * @details Specified setting for grayscale of Printer Click driver.
 */
#define PRINTER_GRAYSCALE_0             0x00
#define PRINTER_GRAYSCALE_1             0x01
#define PRINTER_GRAYSCALE_2             0x02
#define PRINTER_GRAYSCALE_3             0x03
#define PRINTER_GRAYSCALE_4             0x04
#define PRINTER_GRAYSCALE_5             0x05
#define PRINTER_GRAYSCALE_6             0x06
#define PRINTER_GRAYSCALE_7             0x07
#define PRINTER_GRAYSCALE_8             0x08

/**
 * @brief Printer picture settings.
 * @details Specified setting for picture of Printer Click driver.
 */
#define PRINTER_PICTURE_TYPE_NORMAL     0x00

/**
 * @brief Printer barcode settings.
 * @details Specified setting for barcode of Printer Click driver.
 */
#define PRINTER_BARCODE_SYS_UPCA        0x00
#define PRINTER_BARCODE_SYS_UPCE        0x01
#define PRINTER_BARCODE_SYS_EAN13       0x02
#define PRINTER_BARCODE_SYS_EAN8        0x03
#define PRINTER_BARCODE_SYS_CODE39      0x04
#define PRINTER_BARCODE_SYS_ITF25       0x05
#define PRINTER_BARCODE_SYS_CODABAR     0x06
#define PRINTER_BARCODE_SYS_CODE93      0x07
#define PRINTER_BARCODE_SYS_CODE128     0x08

/**
 * @brief Printer printer callback settings.
 * @details Specified setting for printer callback of Printer Click driver.
 */
#define PRINTER_CB_STATE_DEFAULT        0x00
#define PRINTER_CB_STATE_PAPEROUT       0x04
#define PRINTER_CB_STATE_OVERHEAT       0x08

/**
 * @brief Printer bitmap settings.
 * @details Specified setting for bitmap of Printer Click driver.
 */
#define PRINTER_BITMAP_LOCATION_1       0x01
#define PRINTER_BITMAP_LOCATION_2       0x02
#define PRINTER_BITMAP_LOCATION_3       0x03
#define PRINTER_BITMAP_LOCATION_4       0x04
#define PRINTER_BITMAP_ALIGN            0x00
#define PRINTER_BITMAP_MODE_NORMAL      0x00

/**
 * @brief Printer QR code settings.
 * @details Specified setting for QR code of Printer Click driver.
 */
#define PRINTER_QR_SIZE_21_53           0x00
#define PRINTER_QR_SIZE_57_121          0x01
#define PRINTER_QR_SIZE_125_177         0x02
#define PRINTER_QR_ERROR_7_PCT          0x00
#define PRINTER_QR_ERROR_15_PCT         0x01
#define PRINTER_QR_ERROR_25_PCT         0x02
#define PRINTER_QR_ERROR_30_PCT         0x03

/**
 * @brief Printer device ready timeout.
 * @details Specified setting for device ready timeout of Printer Click driver.
 */
#define PRINTER_READY_TIMEOUT           5000

/**
 * @brief Printer driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define PRINTER_TX_DRV_BUFFER_SIZE      500
#define PRINTER_RX_DRV_BUFFER_SIZE      100

/*! @} */ // printer_cmd

/**
 * @defgroup printer_map Printer MikroBUS Map
 * @brief MikroBUS pin mapping of Printer Click driver.
 */

/**
 * @addtogroup printer_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Printer Click to the selected MikroBUS.
 */
#define PRINTER_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // printer_map
/*! @} */ // printer

/**
 * @brief Printer Click context object.
 * @details Context object definition of Printer Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t rts;               /**< RTS/BUSY pin - LOW device is ready, HIGH device is busy. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ PRINTER_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ PRINTER_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */

    uint8_t status[ 16 ];           /**< Status string. */
    uint8_t fw_info[ 64 ];          /**< Firmware info string. */

} printer_t;

/**
 * @brief Printer Click configuration object.
 * @details Configuration object definition of Printer Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rts;                 /**< RTS/BUSY pin - LOW device is ready, HIGH device is busy. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} printer_cfg_t;

/**
 * @brief Printer Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PRINTER_OK = 0,
    PRINTER_ERROR = -1

} printer_return_value_t;

/*!
 * @addtogroup printer Printer Click Driver
 * @brief API for configuring and manipulating Printer Click driver.
 * @{
 */

/**
 * @brief Printer configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #printer_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void printer_cfg_setup ( printer_cfg_t *cfg );

/**
 * @brief Printer initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #printer_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_init ( printer_t *ctx, printer_cfg_t *cfg );

/**
 * @brief Printer default configuration function.
 * @details This function executes a default configuration of Printer
 * Click board.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t printer_default_cfg ( printer_t *ctx );

/**
 * @brief Printer data writing function.
 * @details This function waits for a device ready flag and writes a desired number of data
 * bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_generic_write ( printer_t *ctx, uint8_t *data_in, uint32_t len );

/**
 * @brief Printer data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_generic_read ( printer_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief Printer get RTS pin function.
 * @details This function returns the RTS/Busy pin logic state.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t printer_get_rts_pin ( printer_t *ctx );

/**
 * @brief Printer get status function.
 * @details This function reads the paper status and temperature of the printer and stores
 * results in ctx->status string buffer.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Response format: 1st line: 0 = No Paper, 1 = Paper OK
 *                        2nd line: xxC = temperature in Celsius.
 */
err_t printer_get_status ( printer_t *ctx );

/**
 * @brief Printer get FW info function.
 * @details This function reads the firmware information of the printer and stores
 * results in ctx->fw_info string buffer.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Response format: 1st line: controller type
 *                        2nd line: firmware version
 *                        3rd line: firmware date
 *                        4th line: print head family index.
 */
err_t printer_get_fw_info ( printer_t *ctx );

/**
 * @brief Printer set com mode function.
 * @details This function sets the device serial communication baud rate and flow control.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[in] baud_rate : @li @c 0 - 9600,
 *                        @li @c 1 - 19200,
 *                        @li @c 2 - 38400,
 *                        @li @c 3 - 57600,
 *                        @li @c 4 - 115200.
 * @param[in] flow_control : @li @c 0 - No flow control,
 *                           @li @c 1 - Software flow control (xon/xoff),
 *                           @li @c 2 - Hardware flow control.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_set_com_mode ( printer_t *ctx, uint8_t baud_rate, uint8_t flow_control );

/**
 * @brief Printer set printer head function.
 * @details This function sets the printer head type.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[in] head_index : @li @c 0 - MM58_FTP628MCL101 - 58mm 6stb 7.2V compatible designs
 *                         @li @c 1 - MM80_FTP638MCL101 - 80mm 5stb 7.2V compatible designs
 *                         @li @c 2 - MM58_LTP02_245_13 - 58mm 1stb line 7.2V designs
 *                         @li @c 3 - MM58_LTP02_245_C1 - 58mm 1stb line 4.0V designs.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_set_printer_head ( printer_t *ctx, uint8_t head_index );

/**
 * @brief Printer soft init function.
 * @details This function restores the printer to default configuration.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_soft_init ( printer_t *ctx );

/**
 * @brief Printer print LF function.
 * @details This function prints new line.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_print_lf ( printer_t *ctx );

/**
 * @brief Printer print CR function.
 * @details This function prints move to starting position.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_print_cr ( printer_t *ctx );

/**
 * @brief Printer print string function.
 * @details This function sends a string message to print buffer.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[in] data_in : String message buffer.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_print_string ( printer_t *ctx, char *data_in );

/**
 * @brief Printer print string function.
 * @details This function prints a string message with line feed.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[in] data_in : String message buffer.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_print_string_lf ( printer_t *ctx, char *data_in );

/**
 * @brief Printer print dots function.
 * @details This function prints and feeds paper for number of line dots.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[in] num_dots : Dot line number.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_print_dots ( printer_t *ctx, uint8_t num_dots );

/**
 * @brief Printer print lines function.
 * @details This function prints and feeds paper for number of font lines.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[in] num_lines : Font lines number.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_print_lines ( printer_t *ctx, uint8_t num_lines );

/**
 * @brief Printer set font type function.
 * @details This function sets the printing font type.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[in] font_type : Font type combination, see PRINTER_FONT_TYPE_x definitions.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_set_font_type ( printer_t *ctx, uint8_t font_type );

/**
 * @brief Printer set alignment function.
 * @details This function sets the printing horizontal alignment.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[in] align : @li @c 0 - Left,
 *                    @li @c 1 - Center,
 *                    @li @c 2 - Right.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_set_alignment ( printer_t *ctx, uint8_t align );

/**
 * @brief Printer set line spacing function.
 * @details This function sets the line spacing for number of line dots.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[in] num_dots : Dot line number.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_set_line_spacing ( printer_t *ctx, uint8_t num_dots );

/**
 * @brief Printer default line spacing function.
 * @details This function sets the line spacing to defaults.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_default_line_spacing ( printer_t *ctx );

/**
 * @brief Printer set horizontal tab function.
 * @details This function sets a desired number of horizontal tabs.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[in] col_pos : Array of column position.
 * @param[in] num_tabs : Number of tabs / column positions.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_set_horizontal_tab ( printer_t *ctx, uint8_t *col_pos, uint8_t num_tabs );

/**
 * @brief Printer horizontal tab function.
 * @details This function moves the printing position to the next tab position in horizontal.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_horizontal_tab ( printer_t *ctx );

/**
 * @brief Printer print picture function.
 * @details This function prints a raster bit image.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[in] pic_buf : Starting address of the image buffer.
 * @param[in] h_size : Horizontal byte number.
 * @param[in] v_size : Vertical dot number.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_print_picture ( printer_t *ctx, uint8_t *pic_buf, uint16_t h_size, uint16_t v_size );

/**
 * @brief Printer set left margin function.
 * @details This function sets the left margin to number of dots.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[in] num_dots : Number of dots.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_set_left_margin ( printer_t *ctx, uint8_t num_dots );

/**
 * @brief Printer set right margin function.
 * @details This function sets the right margin to number of dots.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[in] num_dots : Number of dots.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_set_right_margin ( printer_t *ctx, uint8_t num_dots );

/**
 * @brief Printer set abs print pos function.
 * @details This function moves the printing position for number of dots.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[in] num_dots : Number of dots.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_set_abs_print_pos ( printer_t *ctx, uint16_t num_dots );

/**
 * @brief Printer set font grayscale function.
 * @details This function sets the font grayscale level.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[in] grayscale : Grayscale level from 0 (min) to 8 (max).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_set_font_grayscale ( printer_t *ctx, uint8_t grayscale );

/**
 * @brief Printer set db mode function.
 * @details This function starts double-byte character mode.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_set_db_mode ( printer_t *ctx );

/**
 * @brief Printer cancel db mode function.
 * @details This function cancels double-byte character mode.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_cancel_db_mode ( printer_t *ctx );

/**
 * @brief Printer set font size function.
 * @details This function sets the font size to small or large.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[in] size : Font size 1 - small, 2 - large.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_set_font_size ( printer_t *ctx, uint8_t size );

/**
 * @brief Printer hide barcode text function.
 * @details This function sets a barcode text to hide.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_hide_barcode_text ( printer_t *ctx );

/**
 * @brief Printer show barcode text function.
 * @details This function sets a barcode text to show.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_show_barcode_text ( printer_t *ctx );

/**
 * @brief Printer set barcode height function.
 * @details This function sets a barcode height level.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[in] height : Barcode height from 1 to 128.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_set_barcode_height ( printer_t *ctx, uint8_t height );

/**
 * @brief Printer set barcode width function.
 * @details This function sets a barcode width level.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[in] width : Barcode width from 1 to 4.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_set_barcode_width ( printer_t *ctx, uint8_t width );

/**
 * @brief Printer print barcode function.
 * @details This function prints a barcode in selected mode.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[in] barcode_sys : Barcode system, see PRINTER_BARCODE_SYS_x macro definitions.
 * @param[in] barcode : Starting address of the barcode buffer.
 * @param[in] barcode_len : Barcode buffer length.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_print_barcode ( printer_t *ctx, uint8_t barcode_sys, uint8_t *barcode, uint8_t barcode_len );

/**
 * @brief Printer clear print buffer function.
 * @details This function clears and resets the print buffer.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_clear_print_buffer ( printer_t *ctx );

/**
 * @brief Printer set printer cb function.
 * @details This function sets the printer states automatic callback.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[in] callback : Callback - 0 - Normal, 1 - Paper end, 2 - Overheat.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_set_printer_cb ( printer_t *ctx, uint8_t callback );

/**
 * @brief Printer download NV Bitmap function.
 * @details This function loads bitmaps into flash memory.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[in] location : Bitmap location in flash from 1 to 4.
 * @param[in] h_size : Horizontal byte number.
 * @param[in] v_size : Vertical dot number.
 * @param[in] bitmap : Starting address of the bitmap buffer.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_download_nv_bitmap ( printer_t *ctx, uint8_t location, uint8_t h_size, uint8_t v_size, uint8_t *bitmap );

/**
 * @brief Printer print NV Bitmap function.
 * @details This function prints a bitmap loaded into flash memory.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[in] location : Bitmap location in flash from 1 to 4.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_print_nv_bitmap ( printer_t *ctx, uint8_t location );

/**
 * @brief Printer set QR size function.
 * @details This function sets the QR code size/version.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[in] size : @li @c 0 - 21->53,
 *                   @li @c 1 - 57->121,
 *                   @li @c 2 - 125->177.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_set_qr_size ( printer_t *ctx, uint8_t size );

/**
 * @brief Printer set QR error corr function.
 * @details This function sets the QR code error correction level.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[in] corr_level : @li @c 0 - 7%,
 *                         @li @c 1 - 15%,
 *                         @li @c 2 - 25%,
 *                         @li @c 3 - 30%.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_set_qr_error_corr ( printer_t *ctx, uint8_t corr_level );

/**
 * @brief Printer transfer QR code function.
 * @details This function transfers QR code data to encode buffer.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[in] qr_code : Starting address of the QR code buffer.
 * @param[in] code_len : QR code length.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_transfer_qr_code ( printer_t *ctx, uint8_t *qr_code, uint16_t code_len );

/**
 * @brief Printer print QR code function.
 * @details This function prints the QR code buffer.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t printer_print_qr_code ( printer_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // PRINTER_H

/*! @} */ // printer

// ------------------------------------------------------------------------ END
