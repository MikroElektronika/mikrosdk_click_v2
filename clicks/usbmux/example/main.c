/*!
 * @file main.c
 * @brief USB MUX Click Example.
 *
 * # Description
 * This example demonstrates the use of the USB MUX Click board.
 * This driver provides functions for device configurations 
 * and for the selection of the output.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of the log UART, performing default configuration which disables the output.
 *
 * ## Application Task
 * Reading user input from UART Terminal and using it for the selection of the output of 
 * disabling output of the USB MUX Click board.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "usbmux.h"

static usbmux_t usbmux;   /**< USB MUX Click driver object. */
static log_t logger;    /**< Logger object. */

/**
 * @brief Display possible selection function.
 * @details This function is used to display possible selections for the user input.
 * @return Nothing.
 * @note None.
 */
static void display_selection ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbmux_cfg_t usbmux_cfg;  /**< Click config object. */

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
    usbmux_cfg_setup( &usbmux_cfg );
    USBMUX_MAP_MIKROBUS( usbmux_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == usbmux_init( &usbmux, &usbmux_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    usbmux_default_cfg( &usbmux );
    
    log_info( &logger, " Application Task " );
    display_selection( );
}

void application_task ( void ) 
{
    static char index;
    
    if ( 1 == log_read( &logger, &index, 1 ) ) 
    {
        switch ( index )
        {
            case ( '0' ):
            {
                log_printf( &logger, " Turning output off. \r\n" );
                usbmux_disable_output( &usbmux );
                break;
            }
            case ( '1' ):
            {
                log_printf( &logger, " USB1 Enabled and selected. \r\n" );
                usbmux_set_output( &usbmux, USBMUX_USB1_SELECT );
                usbmux_enable_output( &usbmux );
                break;
            }
            case ( '2' ):
            {
                log_printf( &logger, " USB2 Enabled and selected. \r\n" );
                usbmux_set_output( &usbmux, USBMUX_USB2_SELECT );
                usbmux_enable_output( &usbmux );
                break;
            }
            default:
            {
                display_selection( );
            }
        }
    }
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

static void display_selection ( void )
{
    log_printf( &logger, "  To select USB output settings  \r\n" );
    log_printf( &logger, "  Send one of the numbers: \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " '0' - Turn off output  \r\n" );
    log_printf( &logger, " '1' - Enable and select USB1 \r\n" );
    log_printf( &logger, " '2' - Enable and select USB2  \r\n" );
    log_printf( &logger, "---------------------------\r\n" );
}

// ------------------------------------------------------------------------ END
