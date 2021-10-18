/*!
 * @file main.c
 * @brief IrDA 3 Click Example.
 *
 * # Description
 * This example demonstrates the use of IrDA 3 click boards.
 * The example can perform both roles, transmitter and receiver.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes UART driver and all used control pins.
 * Also clears the response buffer.
 *
 * ## Application Task
 * Demonstrates the use of IrDA 3 clicks which can be used as transmitter or
 * receiver. There are four different examples in this project. 
 * Uncomment one of the below macros to select which example will be executed.
 * By default the DEMO_APP_TRANSMITTER_1 example is selected.
 *
 * @author Jelena Milosavljevic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "irda3.h"

// ------------------------------------------------------------------ VARIABLES

#define PROCESS_BUFFER_SIZE 200
//#define DEMO_APP_RECEIVER_1
//#define DEMO_APP_RECEIVER_2
#define DEMO_APP_TRANSMITTER_1
// #define DEMO_APP_TRANSMITTER_2

static irda3_t irda3;
static log_t logger;

static char tx_message[ ] = { 'M', 'i', 'k', 'r', 'o', 'E', '\r', '\n', '\0' };
static char rx_message[ 10 ];
static uint8_t idx;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init( void ) {
    irda3_cfg_t irda3_cfg;
    log_cfg_t logger_cfg;

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
    log_init( &logger, &logger_cfg );
    log_printf( &logger, "***  IrDA initialization done  ***\r\n" );
    log_printf( &logger, "**********************************\r\n" );
    
    //  Click initialization.
    
    irda3_cfg_setup( &irda3_cfg );
    IRDA3_MAP_MIKROBUS( irda3_cfg, MIKROBUS_1 );
    irda3_init( &irda3, &irda3_cfg );
    irda3_default_cfg( &irda3 );
    irda3_reset( &irda3 );

    //  Clear response.
    
    memset( rx_message, 0, sizeof( rx_message ) );
}

void application_task( void ) {

#ifdef DEMO_APP_RECEIVER_1
    rx_message[ 0 ] = irda3_generic_single_receive( &irda3 );

    if ( rx_message[ 0 ] != 0 ) {
        log_printf( &logger, "%c", ( char ) rx_message[ 0 ] );
    }
    Delay_ms( 100 );

#endif

#ifdef DEMO_APP_RECEIVER_2

    irda3_generic_multiple_receive( &irda3, rx_message, '\n' );

    log_printf( &logger, "RECEIVED MESSAGE : " );
    log_printf( &logger, "%s\r\n", rx_message );
    Delay_ms( 100 );

#endif
    
#ifdef DEMO_APP_TRANSMITTER_1

    irda3_generic_multiple_send( &irda3, tx_message );

    log_printf( &logger, "MESSAGE SENT\r\n" );
    Delay_ms( 2000 );

#endif
    
#ifdef DEMO_APP_TRANSMITTER_2

    idx = 0;

    while ( tx_message[ idx ] != '\0' ) {
        irda3_generic_single_send( &irda3, tx_message[ idx++ ] );
    }

    log_printf( &logger, "MESSAGE SENT\r\n" );
    Delay_ms( 2000 );

#endif

}

void main( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}


// ------------------------------------------------------------------------ END

