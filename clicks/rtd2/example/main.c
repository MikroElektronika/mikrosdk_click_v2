/*!
 * \file 
 * \brief Rtd 2 Click example
 * 
 * # Description
 * RTD 2 Click board is commonly used for measuring ambient temperature
 * from the PT100 3-wire temperature probe.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver, performs a hardware reset, and sets the click 
 * default configuration.
 * 
 * ## Application Task  
 * Reads an ambient temperature measured by the PT100 3-wire temperature probe
 * connected to the RTD 2 click board, and logs the results on the USB UART each second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rtd2.h"

// ------------------------------------------------------------------ VARIABLES

static rtd2_t rtd2;
static log_t logger;
static float temperature;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rtd2_cfg_t cfg;

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
    rtd2_cfg_setup( &cfg );
    RTD2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtd2_init( &rtd2, &cfg );
    Delay_ms ( 200 );

    log_printf( &logger, "----- Hardware Reset ------\r\n" );
    rtd2_hw_reset( &rtd2 );
    Delay_ms ( 100 );
    
    log_printf( &logger, "-- Default configuration --\r\n" );
    rtd2_default_cfg( &rtd2 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "     Start Measurement    \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 100 );
}

void application_task ( void )
{
    if ( rtd2_check_new_data_ready( &rtd2 ) == RTD2_NEW_DATA_IS_READY )
    {
        temperature = rtd2_get_temperature( &rtd2 );
        log_printf( &logger, " Temperature : %.2f C\r\n", temperature );
        log_printf( &logger, "--------------------------\r\n");
        Delay_ms ( 1000 );
    }
    else
    {
        rtd2_enable_start( &rtd2, RTD2_START_CONVERSION_DISABLE );
        Delay_ms ( 1000 );
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


// ------------------------------------------------------------------------ END
