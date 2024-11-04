/*!
 * \file 
 * \brief GainAmp2 Click example
 * 
 * # Description
 * This application is programmable gain amplifier
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes and sets GainAMP 2 Click channel 0 to amplify the signal 2 times
 * 
 * ## Application Task  
 * Displays the voltage measured from VOUT pin
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "gainamp2.h"

// ------------------------------------------------------------------ VARIABLES

static gainamp2_t gainamp2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    gainamp2_cfg_t cfg;

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

    gainamp2_cfg_setup( &cfg );
    GAINAMP2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gainamp2_init( &gainamp2, &cfg );
    
    gainamp2_set_channel_gain ( &gainamp2, GAINAMP2_CH0, GAINAMP2_GAIN_2X );
    log_printf( &logger,"Channel 0 - aplified 2x \r\n" ); 
}

void application_task( void )
{
    log_printf( &logger,"Voltage at VOUT: %f \r\n", gainamp2_get_voltage( &gainamp2 ) );
    log_printf( &logger,"------------------------------- \r\n " );
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
