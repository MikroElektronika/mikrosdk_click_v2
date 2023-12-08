/*!
 * \file 
 * \brief iqRF Click example
 * 
 * # Description
 * IQRF Click carries the RF transceiver, operating in the 868/916 MHz frequency.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Application Init performs Logger and Click initialization.
 * 
 * ## Application Task  
 * Checks if new data byte has received in RX buffer ( ready for reading ),
 * and if ready than reads one byte from RX buffer. In the second case, 
 * the application task writes message data via UART. Results are being sent 
 * to the Usart Terminal where you can track their changes.
 * 
 * \author Mihajlo Djordjevic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "iqrf.h"

// ------------------------------------------------------------------ VARIABLES

//#define DEMO_APP_RECEIVER
 #define DEMO_APP_TRANSCEIVER


static iqrf_t iqrf;
static log_t logger;

static const char demo_message[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };
static char rx_message[ 10 ];
static uint8_t idx;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    iqrf_cfg_t cfg;

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
    Delay_ms ( 1000 );

    //  Click initialization.

    iqrf_cfg_setup( &cfg );
    IQRF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    iqrf_init( &iqrf, &cfg );
    
    log_printf( &logger, "------------------------------------\r\n" );
    log_printf( &logger, "------------ iqRF  Click -----------\r\n" );
    log_printf( &logger, "------------------------------------\r\n" );
    Delay_ms ( 1000 );
    
    iqrf_default_cfg ( &iqrf );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "---------- Initialization ----------\r\n" );
    log_printf( &logger, "------------------------------------\r\n" );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    char tmp;
    
#ifdef DEMO_APP_RECEIVER

    // RECEIVER - UART polling

    tmp =  iqrf_generic_single_read( &iqrf );
    log_printf( &logger, " %c ", tmp );
        
#endif
        
#ifdef DEMO_APP_TRANSCEIVER

    // TRANSMITER - TX each 2 sec
        
    uint8_t cnt;
        
    for ( cnt = 0; cnt < 9; cnt ++ )
    {
        iqrf_generic_single_write( &iqrf, demo_message[ cnt ] );
        Delay_ms( 100 );
    }
    
    Delay_ms( 2000 );
       
#endif
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
