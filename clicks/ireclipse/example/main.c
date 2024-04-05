/*!
 * \file 
 * \brief Ir Eclipse Click example
 * 
 * # Description
 * This is an example of IR ECLIPSE click board
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of IR eclipse Click board.
 * When the beam from the transmitter is eclipsed by placing an object in
 * the gap ( like a piece of paper ), when the sensor is triggered, the 
 * counter is incremented by one. Results are being sent to the Usart 
 * Terminal where you can track their changes. Data logs on usb uart 
 * when the sensor is triggered.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ireclipse.h"

// ------------------------------------------------------------------ VARIABLES

static ireclipse_t ireclipse;
static log_t logger;
uint8_t state_new;
uint8_t state_old;
uint16_t n_cnt;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ireclipse_cfg_t cfg;

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
    log_printf(&logger, "- Application Init -\r\n");

    //  Click initialization.

    ireclipse_cfg_setup( &cfg );
    IRECLIPSE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ireclipse_init( &ireclipse, &cfg );
    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, "   Start counting:  \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    
    n_cnt = IRECLIPSE_START_CNT_VAL;
    state_old = IRECLIPSE_LOW;
    state_new = IRECLIPSE_LOW;
}

void application_task ( void )
{
    state_new = ireclipse_int_status( &ireclipse );

    if ( ( state_new == IRECLIPSE_HIGH ) && ( state_old == IRECLIPSE_LOW ) )
    {
        state_old = IRECLIPSE_HIGH;
        log_printf( &logger, "  Counter = %d \r\n", ++n_cnt );

    }

    if ( ( state_new == IRECLIPSE_LOW ) && ( state_old == IRECLIPSE_HIGH ) )
    {
        log_printf( &logger, "--------------------\r\n" );
        state_old = IRECLIPSE_LOW;
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
