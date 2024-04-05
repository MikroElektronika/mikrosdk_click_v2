/*!
 * \file 
 * \brief Stretch Click example
 * 
 * # Description
 * The application is for stretch measuring 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables GPIO and ADC, turn off the LED and starts write log. 
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of Stretch Click board. Stretch Click reads and display ADC value.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "stretch.h"

// ------------------------------------------------------------------ VARIABLES

static stretch_t stretch;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    stretch_cfg_t cfg;

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

    stretch_cfg_setup( &cfg );
    STRETCH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    stretch_init( &stretch, &cfg );

    Delay_100ms();

    log_printf( &logger, "------------------- \r\n" );
    log_printf( &logger, "  Stretch  click  "  );
    log_printf( &logger, "-------------------\r\n" );

    stretch_turn_off_led( &stretch );
    Delay_100ms( );

    log_printf( &logger, " ADC Initializated " );
    log_printf( &logger, "-------------------" );
}

void application_task ( void )
{
    stretch_data_t tmp;
    
    //  Task implementation.
    
    tmp = stretch_generic_read ( &stretch );
    log_printf( &logger, "** ADC value : [DEC]- %d, [HEX]- 0x%x \r\n", tmp, tmp );
    Delay_ms ( 1000 );

    Delay_100ms( );
    
    if ( tmp < 500 )
    {
        stretch_turn_on_led( &stretch );
    }
        
    else
    {
        stretch_turn_off_led( &stretch );
    }

    log_printf( &logger, " Resistance : %d \r\n", tmp );
    log_printf( &logger, "-------------------\r\n" );
    Delay_1sec( );
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
