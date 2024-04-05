/*!
 * \file 
 * \brief HallCurrent Click example
 * 
 * # Description
 * The application is current sensor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - SPI and start write log.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of Hall Current Click board.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "hallcurrent.h"

// ------------------------------------------------------------------ VARIABLES

static hallcurrent_t hallcurrent;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    hallcurrent_cfg_t cfg;

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
    hallcurrent_cfg_setup( &cfg );
    HALLCURRENT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hallcurrent_init( &hallcurrent, &cfg );
    
    HALLCURRENT_SET_DATA_SAMPLE_EDGE;
    
    log_printf( &logger,"------------------------\r\n" );
    log_printf( &logger,  "       Hall Current     \r\n" );
    log_printf( &logger, "------------------------\r\n" );
}

void application_task ( void )
{
    log_printf( &logger, " Current : %.3f A \r\n", hallcurrent_read_current( &hallcurrent ) );
    log_printf( &logger, "------------------------\r\n" );
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
