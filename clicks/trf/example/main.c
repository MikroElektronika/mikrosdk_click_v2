/*!
 * \file 
 * \brief Trf Click example
 * 
 * # Description
 * This is a example which demonstrates the use of Trf Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * 
 * ## Application Task  
 * Checks if new data byte have received in rx buffer (ready for reading),
 * and if ready than reads one byte from rx buffer. In second case aplication task writes
 * message data via UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "trf.h"

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSMITER

static trf_t trf;
static log_t logger;

static char demo_message[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    trf_cfg_t cfg;

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

    trf_cfg_setup( &cfg );
    TRF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    trf_init( &trf, &cfg );
    
    Delay_ms ( 100 );
}

void application_task ( void )
{
    char tmp;
    uint8_t cnt;
    
#ifdef DEMO_APP_RECEIVER

    // RECEIVER - UART polling

    tmp =  trf_generic_single_read( &trf );
    log_printf( &logger, " %c ", tmp );
    
#endif
#ifdef DEMO_APP_TRANSMITER

    // TRANSMITER - TX each 2 sec
       
    for ( cnt = 0; cnt < 8; cnt ++ )
    {
        trf_generic_single_write( &trf, demo_message[ cnt ] );
        Delay_ms ( 100 );
    }
       
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
#endif
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
