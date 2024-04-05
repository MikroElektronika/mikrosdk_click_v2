/*!
 * \file 
 * \brief 7seg Click example
 * 
 * # Description
 * Example code consist of two sections: AppInit and AppTask,
 * and shows number or character on 7seg display.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Application Init performs Logger and Click Initialization.
 * 
 * ## Application Task  
 * Application Task shows functionality of the 7seg click,
 * shows number or character on left and right display.
 *  
 * \author Mihajlo Djordjevic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c7seg.h"

// ------------------------------------------------------------------ VARIABLES

static c7seg_t c7seg;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c7seg_cfg_t cfg;

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

    c7seg_cfg_setup( &cfg );
    C7SEG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c7seg_init( &c7seg, &cfg );
    
    c7seg_default_cfg ( &c7seg );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    uint8_t counter;

    c7seg_display_mode( &c7seg, C7SEG_DISPLAY_ON );
    Delay_ms ( 1000 );
    
    for ( counter = 0; counter < 9; counter ++ )
    {
        c7seg_write_data_number( &c7seg, counter, counter + 1 );
        Delay_ms ( 1000 );
    }
    Delay_ms ( 1000 );

    for ( counter = 65; counter < 90; counter ++ )
    {
        c7seg_write_data_character( &c7seg, counter, counter + 1 );
        Delay_ms ( 1000 );
    }
    Delay_ms ( 1000 );

    c7seg_display_mode( &c7seg, C7SEG_DISPLAY_OFF );
    Delay_ms ( 1000 );
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

// ------------------------------------------------------------------------ END
