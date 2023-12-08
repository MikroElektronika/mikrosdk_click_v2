/*!
 * \file 
 * \brief Tamper Click example
 * 
 * # Description
 * Tamper click is equipped with side-actuated detect switch. The switch itself acts as 
 * a push button and has 2 Normally Open terminals, which get shorted when the force is applied. 
 * The applied pressure closes the circuit, connecting the VCC routed to the first pin 
 * of the switch with the INT pin on the mikroBUS. The microcontroller is then able to detect 
 * a high logical level on the INT pin and the desired task can then be executed.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables GPIO and also starts write log.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of Tamper click board.
 * It detects whether the state of switch on Tamper click is changes to open or to closed.
 * Results are being sent to the Usart Terminal where you can keep track of their changes.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "tamper.h"

// ------------------------------------------------------------------ VARIABLES

static tamper_t tamper;
static log_t logger;

static uint8_t switch_state = 0;
static uint8_t switch_state_old = 1;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    tamper_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    tamper_cfg_setup( &cfg );
    TAMPER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    tamper_init( &tamper, &cfg );
}

void application_task ( void )
{
    switch_state = tamper_state( &tamper );
    
    if ( switch_state == 1 && switch_state_old == 0 )
    {
        log_printf( &logger, "      Closed     \r\n" );
        log_printf( &logger, "- - - - - - - - -\r\n" );
        switch_state_old = 1;
    }

    if ( switch_state == 0 && switch_state_old == 1 )
    {
        log_printf( &logger, "       Open      \r\n" );
        log_printf( &logger, "- - - - - - - - -\r\n" );
        switch_state_old = 0;
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
