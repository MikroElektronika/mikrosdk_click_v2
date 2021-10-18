/*!
 * \file 
 * \brief Power Reset Click example
 * 
 * # Description
 * Reads PWR and RST pin states and performs a control of the timer counter depending on the pressed button.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device and logger module, prints Initialization done message.
 * 
 * ## Application Task  
 * Checks the states of the PWR and RST pins and logs every change.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "powerreset.h"

// ------------------------------------------------------------------ VARIABLES

static powerreset_t powerreset;
static log_t logger;

powerreset_state_t pwr_state;
powerreset_state_t rst_state;

powerreset_state_t new_pwr_state;
powerreset_state_t new_rst_state;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    powerreset_cfg_t cfg;

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

    powerreset_cfg_setup( &cfg );
    POWERRESET_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    powerreset_init( &powerreset, &cfg );

    Delay_ms( 100 );
    
    log_printf( &logger, "** Touch Button initialization done **\r\n");
    log_printf( &logger, "**************************************\r\n");
}

void application_task ( void )
{
    new_pwr_state = powerreset_get_pwr( &powerreset );
    new_rst_state = powerreset_get_rst( &powerreset );
    
    if ( new_pwr_state != pwr_state )
    {
        if ( new_pwr_state == POWERRESET_ACTIVE )
        {
            log_printf( &logger, "POWER ON\r\n" );
            Delay_ms( 100 );
        }
        else if ( new_pwr_state == POWERRESET_INACTIVE )
        {
            log_printf( &logger, "POWER OFF\r\n" );
            Delay_ms( 100 );
        }
        pwr_state = new_pwr_state;
    }

    if ( new_rst_state != rst_state )
    {
        if ( new_rst_state == POWERRESET_ACTIVE )
        {
            log_printf( &logger, "Reset occured!\r\n" );
            Delay_ms( 100 );
        }
        rst_state = new_rst_state;
    }
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
