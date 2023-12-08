/*!
 * \file 
 * \brief TouchClamp Click example
 * 
 * # Description
 * This demo-app shows the touch position using TouchClamp click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Setting the click in the default configuration.
 * 
 * ## Application Task  
 * Detect and dispay touch position when the click is triggered.
 * 
 * \author Nenad Filipovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "touchclamp.h"

// ------------------------------------------------------------------ VARIABLES

static touchclamp_t touchclamp;
static log_t logger;
uint16_t touch_data;
uint16_t touch_data_old;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    touchclamp_cfg_t cfg;

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

    touchclamp_cfg_setup( &cfg );
    TOUCHCLAMP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    touchclamp_init( &touchclamp, &cfg );
    Delay_ms( 100 );
    
    touchclamp_soft_reset( &touchclamp );
    Delay_ms( 100 );
    
    touchclamp_default_cfg( &touchclamp );
    Delay_ms( 100 );
    
    touch_data_old = TOUCHCLAMP_NO_TOUCH;
    
    log_printf( &logger, "-------------------\r\n" );
    log_printf( &logger, " Touch Clamp Click \r\n" );
    log_printf( &logger, "-------------------\r\n" );
}

void application_task ( void )
{
    touch_data = touchclamp_get_touch_data( &touchclamp );
    
    if ( touch_data_old != touch_data )
    {
        if ( touch_data == TOUCHCLAMP_TOUCH_POSITION_H )
            log_printf( &logger, "  - - - - - - - H\r\n" );
            
        if ( touch_data == TOUCHCLAMP_TOUCH_POSITION_G )
            log_printf( &logger, "  - - - - - - G -\r\n" );
            
        if ( touch_data == TOUCHCLAMP_TOUCH_POSITION_F )
            log_printf( &logger, "  - - - - - F - -\r\n" );
                                                       
        if ( touch_data == TOUCHCLAMP_TOUCH_POSITION_E )                       
            log_printf( &logger, "  - - - - E - - -\r\n" );
                                                       
        if ( touch_data == TOUCHCLAMP_TOUCH_POSITION_D )                       
            log_printf( &logger, "  - - - D - - - -\r\n" );
                                                       
        if ( touch_data == TOUCHCLAMP_TOUCH_POSITION_C )                       
            log_printf( &logger, "  - - C - - - - -\r\n" );
                                                       
        if ( touch_data == TOUCHCLAMP_TOUCH_POSITION_B )                       
            log_printf( &logger, "  - B - - - - - -\r\n" );
                                                       
        if ( touch_data == TOUCHCLAMP_TOUCH_POSITION_A )                       
            log_printf( &logger, "  A - - - - - - -\r\n" );
      
        touch_data_old = touch_data;
    }
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}


// ------------------------------------------------------------------------ END
