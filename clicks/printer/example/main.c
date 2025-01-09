/*!
 * @file main.c
 * @brief Printer Click Example.
 *
 * # Description
 * This example demonstrates the use of Printer Click board by providing user interaction
 * with a thermal printer, allowing the user to check paper status, display commands,
 * and execute various printing tasks based on user commands through a UART interface.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, performs the Click default configuration, and displays the list
 * of supported commands on the USB UART.
 *
 * ## Application Task
 * Checks the paper status and processes user commands.
 * 
 * @note
 * The default printer head type is set to LTP02-245-13.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "printer.h"

static printer_t printer;
static log_t logger;

/**
 * @brief Printer check paper function.
 * @details This function checks if the paper is presented and feeds the newly inserted paper.
 * @return None.
 * @note None.
 */
static void printer_check_paper ( printer_t *ctx );

/**
 * @brief Printer display commands function.
 * @details This function displays the list of supported terminal commands on the USB UART.
 * @return None.
 * @note None.
 */
static void printer_display_commands ( void );

/**
 * @brief Printer parse command function.
 * @details This function checks if the input command is supported and executes it.
 * @param[in] ctx : Click context object.
 * See #printer_t object definition for detailed explanation.
 * @param[in] command : Command input, for more details refer to @b printer_display_commands function.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Wrong command or command is not executed properly.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t printer_parse_command ( printer_t *ctx, uint8_t command );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    printer_cfg_t printer_cfg;  /**< Click config object. */

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    printer_cfg_setup( &printer_cfg );
    PRINTER_MAP_MIKROBUS( printer_cfg, MIKROBUS_1 );
    if ( UART_ERROR == printer_init( &printer, &printer_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRINTER_ERROR == printer_default_cfg ( &printer ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    printer_display_commands ( );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t command = 0;
    printer_check_paper ( &printer );
    if ( 1 == log_read ( &logger, &command, 1 ) ) 
    {
        printer_parse_command ( &printer, command );
    }
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

static void printer_check_paper ( printer_t *ctx )
{
    static uint8_t valid_change = 0;
    static uint8_t no_paper = 0;
    if ( PRINTER_OK == printer_get_status ( ctx ) )
    {
        if ( '0' == printer.status[ 0 ] )
        {
            if ( !no_paper )
            {
                // Confirm paper status change with 10 consecutive validation before taking actions
                if ( ++valid_change > 10 )
                {
                    log_printf ( &logger, "No paper detected!\r\n" );
                    no_paper = 1;
                    valid_change = 0;
                }
            }
        }
        else
        {
            if ( no_paper )
            {
                // Confirm paper status change with 10 consecutive validation before taking actions
                if ( ++valid_change > 10 )
                {
                    // Feeding inserted paper
                    for ( uint8_t cnt = 0; cnt < 5; cnt++ )
                    {
                        printer_print_lf ( ctx );
                        Delay_ms ( 10 );
                    }
                    log_printf ( &logger, "Paper OK!\r\n" );
                    no_paper = 0;
                    valid_change = 0;
                }
            }
        }
        Delay_ms ( 100 );
    }
}

static void printer_display_commands ( void )
{
    log_printf( &logger, "--- UART commands list (no case sensitive) ---\r\n" );
    log_printf( &logger, "'+' - New line / Feed paper.\r\n" );
    log_printf( &logger, "'T' - Print \"MIKROE - Printer Click\" message.\r\n" );
    log_printf( &logger, "'R' - Print POS receipt sample.\r\n" );
    Delay_ms ( 10 );
    log_printf( &logger, "'A' - Print tab and alignment sample.\r\n" );
    log_printf( &logger, "'S' - Get status.\r\n" );
    log_printf( &logger, "'F' - Get firmware information.\r\n" );
    log_printf( &logger, "'L' - Display commands list.\r\n" );
    Delay_ms ( 10 );
}

static err_t printer_parse_command ( printer_t *ctx, uint8_t command )
{
    err_t error_flag = PRINTER_OK;
    log_printf( &logger, "\r\n" );
    switch ( command )
    {
        case '+': 
        {
            log_printf( &logger, "Printing New Line / Feed paper\r\n" );
            error_flag |= printer_print_lf ( ctx );
            break;
        }
        case 'T': case 't': 
        {
            log_printf( &logger, "Printing \"MIKROE - Printer Click\" message.\r\n" );
            error_flag |= printer_soft_init ( ctx );
            error_flag |= printer_set_alignment ( ctx, PRINTER_ALIGN_CENTER );
            error_flag |= printer_set_font_type ( ctx, PRINTER_FONT_TYPE_NORMAL );
            error_flag |= printer_print_string_lf ( ctx, "MIKROE - Printer Click" );
            error_flag |= printer_print_lines ( ctx, 1 );
            break;
        }
        case 'R': case 'r': 
        {
            log_printf( &logger, "Printing POS receipt sample.\r\n" );
            error_flag |= printer_soft_init ( ctx );
            error_flag |= printer_set_font_grayscale ( ctx, PRINTER_GRAYSCALE_4 );
            error_flag |= printer_set_alignment ( ctx, PRINTER_ALIGN_CENTER );
            error_flag |= printer_set_font_type ( ctx, PRINTER_FONT_TYPE_BOLD );
            error_flag |= printer_print_string_lf ( ctx, "MIKROE" );
            error_flag |= printer_set_font_type ( ctx, PRINTER_FONT_TYPE_NORMAL );
            error_flag |= printer_print_lines ( ctx, 1 );
            error_flag |= printer_print_string_lf ( ctx, "Customer Receipt" );
            error_flag |= printer_print_lines ( ctx, 2 );
            error_flag |= printer_set_alignment ( ctx, PRINTER_ALIGN_LEFT );
            error_flag |= printer_print_string_lf ( ctx, "Date: DD/MM/YYYY" );
            error_flag |= printer_print_string_lf ( ctx, "PID: 034/344/00288394" );
            error_flag |= printer_print_lines ( ctx, 2 );
            error_flag |= printer_print_string_lf ( ctx, "  Qty      Item      Price" );
            error_flag |= printer_print_string_lf ( ctx, "................................" );
            error_flag |= printer_print_string_lf ( ctx, "2x  1L 1.5% Milk     $3.98" );
            error_flag |= printer_print_string_lf ( ctx, "6x  1L 3.5% Milk     $16.75" );
            error_flag |= printer_print_string_lf ( ctx, "10x 100g Yogurt Cup  $8.50" );
            error_flag |= printer_print_string_lf ( ctx, "................................" );
            error_flag |= printer_set_font_type ( ctx, PRINTER_FONT_TYPE_BOLD );
            error_flag |= printer_print_string_lf ( ctx, "Total:              $29.23" );
            error_flag |= printer_print_lines ( ctx, 1 );
            error_flag |= printer_set_font_type ( ctx, PRINTER_FONT_TYPE_NORMAL );
            error_flag |= printer_print_string_lf ( ctx, "Incl. 19% VAT $5.55 (Net $23.68)" );
            error_flag |= printer_print_string_lf ( ctx, "................................" );
            error_flag |= printer_set_font_type ( ctx, PRINTER_FONT_TYPE_DOUBLE_HEIGHT );
            error_flag |= printer_print_string_lf ( ctx, "Credit Card         $29.23" );
            error_flag |= printer_print_lines ( ctx, 2 );
            error_flag |= printer_set_alignment ( ctx, PRINTER_ALIGN_CENTER );
            error_flag |= printer_print_string_lf ( ctx, "THANK YOU FOR YOUR VISIT" );
            error_flag |= printer_print_lines ( ctx, 2 );
            break;
        }
        case 'A': case 'a': 
        {
            uint8_t tabs[ 3 ] = { 8, 24, 38 };
            log_printf( &logger, "Printing tab and alignment sample.\r\n" );
            error_flag |= printer_soft_init ( ctx );
            error_flag |= printer_set_alignment ( ctx, PRINTER_ALIGN_LEFT );
            error_flag |= printer_set_horizontal_tab ( ctx, tabs, 3 );
            error_flag |= printer_set_font_type ( ctx, PRINTER_FONT_TYPE_NORMAL );
            error_flag |= printer_print_string_lf ( ctx, "................................" );
            error_flag |= printer_print_string_lf ( ctx, "No Tab: abcd" );
            error_flag |= printer_horizontal_tab ( ctx );
            error_flag |= printer_print_string ( ctx, "Tab1" );
            error_flag |= printer_horizontal_tab ( ctx );
            error_flag |= printer_print_string ( ctx, "Tab2" );
            error_flag |= printer_horizontal_tab ( ctx );
            error_flag |= printer_print_string_lf ( ctx, "Tab3" );
            error_flag |= printer_print_string_lf ( ctx, "................................" );
            error_flag |= printer_set_abs_print_pos ( ctx, 50 );
            error_flag |= printer_print_string_lf ( ctx, "Abs: 1234" );
            error_flag |= printer_print_string_lf ( ctx, "................................" );
            error_flag |= printer_set_alignment ( ctx, PRINTER_ALIGN_CENTER );
            error_flag |= printer_print_string_lf ( ctx, "Center: abcd" );
            error_flag |= printer_set_alignment ( ctx, PRINTER_ALIGN_RIGHT );
            error_flag |= printer_print_string_lf ( ctx, "Right: abcd" );
            error_flag |= printer_set_alignment ( ctx, PRINTER_ALIGN_LEFT );
            error_flag |= printer_print_string_lf ( ctx, "Left: abcd" );
            error_flag |= printer_print_string_lf ( ctx, "................................" );
            break;
        }
        case 'S': case 's': 
        {
            error_flag |= printer_get_status ( ctx );
            if ( PRINTER_OK == error_flag )
            {
                log_printf ( &logger, "--- Status ---\r\n" );
                log_printf ( &logger, "%s", printer.status );
                if ( '0' == printer.status[ 0 ] )
                {
                    log_printf ( &logger, "No paper detected!\r\n" );
                }
                else
                {
                    log_printf ( &logger, "Paper OK!\r\n" );
                }
            }
            break;
        }
        case 'F': case 'f': 
        {
            error_flag |= printer_get_fw_info ( ctx );
            if ( PRINTER_OK == error_flag )
            {
                log_printf ( &logger, "--- Firmware information ---\r\n" );
                log_printf ( &logger, "%s", printer.fw_info );
                uint8_t head_type_index = strlen ( ( char * ) printer.fw_info ) - 3;
                log_printf ( &logger, "Printer head type: " );
                if ( '0' == printer.fw_info[ head_type_index ] )
                {
                    log_printf ( &logger, "MM58_FTP628MCL101\r\n" );
                }
                else if ( '1' == printer.fw_info[ head_type_index ] )
                {
                    log_printf ( &logger, "MM80_FTP638MCL101\r\n" );
                }
                else if ( '2' == printer.fw_info[ head_type_index ] )
                {
                    log_printf ( &logger, "MM58_LTP02_245_13\r\n" );
                }
                else if ( '3' == printer.fw_info[ head_type_index ] )
                {
                    log_printf ( &logger, "MM58_LTP02_245_C1\r\n" );
                }
                else
                {
                    log_printf ( &logger, "UNKNOWN\r\n" );
                }
            }
            break;
        }
        case 'L': case 'l': 
        {
            printer_display_commands ( );
            break;
        }
        default :
        {
            log_error( &logger, "Unknown command." );
            error_flag |= PRINTER_ERROR;
            break;
        }
    }
    log_printf( &logger, "----------------------------------------------\r\n" );
    Delay_ms ( 100 );
    return error_flag;
}

// ------------------------------------------------------------------------ END
