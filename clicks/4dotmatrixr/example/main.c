/*!
 * \file 
 * \brief c4dotmatrixr Click example
 * 
 * # Description
 * This example demonstrates the use of 4Dot-Matrix R click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and performs the click default configuration.
 * 
 * ## Application Task  
 * Displays a desired text message and then numbers from -20 to 20 on the click board.
 * Each step will be logged on the USB UART where you can track the program flow.
 *  
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c4dotmatrixr.h"

// ------------------------------------------------------------------ VARIABLES

static c4dotmatrixr_t c4dotmatrixr;
static log_t logger;

static uint8_t text[23] = { ' ',' ',' ','M', 'i', 'k', 'r', 'o', 'E','l','e',
                            'k','t','r','o','n','i','k','a',' ',' ',' ',' '};

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c4dotmatrixr_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c4dotmatrixr_cfg_setup( &cfg );
    C4DOTMATRIXR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c4dotmatrixr_init( &c4dotmatrixr, &cfg );
    
    c4dotmatrixr_default_cfg ( &c4dotmatrixr );
    log_info( &logger, "---- Application Task ----" );
}

void application_task ( void )
{
    int8_t i;
    log_printf( &logger, "------------------------------------\r\n" );
    log_printf( &logger, "Displaying \"Mikroelektronika\" on the click board...\r\n" );
    for ( i = 0; i < 20; i++ )
    {
        c4dot_write_text(  &c4dotmatrixr, text + i );
        Delay_ms( 150 );
    }
        
    // Clear and delay.
    c4dot_clear_display( &c4dotmatrixr );
    Delay_ms( 500 );
        
    log_printf( &logger, "Displaying all integer numbers from -20 to 20 on the click board...\r\n" );
    // Write some numbers on the display.
    for ( i = -20; i <= 20; i++ )
    {
        c4dot_write_int_dec( &c4dotmatrixr, i );
        Delay_ms( 150 );
    }

    // Clear and delay.
    c4dot_clear_display( &c4dotmatrixr );
    Delay_ms( 500 );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}


// ------------------------------------------------------------------------ END
