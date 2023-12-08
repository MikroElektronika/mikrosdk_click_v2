/*!
 * \file 
 * \brief CanIsolator Click example
 * 
 * # Description
 * This is a example which demonstrates the use of Can Isolator Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * 
 * ## Application Task  
 * Checks if new data byte has received in RX buffer ( ready for reading )
 * and if ready than reads one byte from RX buffer.
 * In the second case, the application task writes message data via UART.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "canisolator.h"

// ------------------------------------------------------------------ VARIABLES

//#define DEMO_APP_RECEIVER
#define DEMO_APP_TRANSMITER

static canisolator_t canisolator;
static log_t logger;

static char demo_message[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };

// ------------------------------------------------------- ADDITIONAL FUNCTIONS


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    canisolator_cfg_t cfg;

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

    canisolator_cfg_setup( &cfg );
    CANISOLATOR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    canisolator_init( &canisolator, &cfg );
    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, " CAN Isolator  Click\r\n" );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    char tmp;
    
#ifdef DEMO_APP_RECEIVER

    // RECEIVER - UART polling

    tmp =  canisolator_generic_single_read( &canisolator );
    log_printf( &logger, " %c ", tmp );
    
#endif
#ifdef DEMO_APP_TRANSMITER

    // TRANSMITER - TX each 2 sec
    
    uint8_t cnt;
        
    for ( cnt = 0; cnt < 9; cnt ++ )
    {
        canisolator_generic_single_write( &canisolator, demo_message[ cnt ] );
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
