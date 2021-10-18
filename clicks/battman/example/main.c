/*!
 * \file 
 * \brief BATT-MAN Click example
 * 
 * # Description
 * BATT-MAN click is a very versatile battery operated power manager. When powered via mikroBUS,
 * it will charge the connected Li-Ion/Li-Po 3.7V battery, while providing the output voltage 
 * on all its outputs at the same time.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the click driver and logger utility and enables the click board.
 * 
 * ## Application Task  
 * Checks the charging indicator status, and in relation to its state 
 * it displays an appropriate message on USB UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "battman.h"

// ------------------------------------------------------------------ VARIABLES

static battman_t battman;
static log_t logger;
static uint8_t chg_flag;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    battman_cfg_t cfg;

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

    battman_cfg_setup( &cfg );
    BATTMAN_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    battman_init( &battman, &cfg );
    
    battman_set_enable( &battman, 1 );
    log_printf( &logger, "BATT-MAN click enabled.\r\n" );
    chg_flag = 0;
}

void application_task ( void )
{
    if ( !battman_get_charging_indicator ( &battman ) )
    {
        if ( chg_flag == 1 )
        {
            log_printf( &logger, "Charging enabled.\r\n" );
        }
        chg_flag = 0;
    }
    else
    {
        if ( chg_flag == 0 )
        {
            log_printf( &logger, "Charging disabled.\r\n" );
        }
        chg_flag = 1;
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
