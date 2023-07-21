/*!
 * \file 
 * \brief Balancer 3 Click example
 * 
 * # Description
 * This application is device for 2-series cell lithium-ion battery.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device coummunication and enables cell balancing.
 * 
 * ## Application Task  
 * Checks if overvoltage is occured and disables cell balancing. 
 * If overvoltage doesn't occur it enables cell balancing.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "balancer3.h"

// ------------------------------------------------------------------ VARIABLES

static balancer3_t balancer3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    balancer3_cfg_t cfg;

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    balancer3_cfg_setup( &cfg );
    BALANCER3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    balancer3_init( &balancer3, &cfg );
         
    balancer3_enable_cell_balance( &balancer3, BALANCER3_CELL_BALANCE_EN );
    log_printf( &logger, "* Normal operation - Cell balance enabled *\r\n" );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static uint8_t old_ov_state = 0;
    uint8_t ov_state = balancer3_check_overvoltage( &balancer3 );
    if ( old_ov_state != ov_state )
    {
        old_ov_state = ov_state;
        if ( BALANCER3_OV_COND_NOT_DETECTED == ov_state )
        {
            log_printf( &logger, "* Normal operation - Cell balance enabled *\r\n" );
            balancer3_enable_cell_balance( &balancer3, BALANCER3_CELL_BALANCE_EN );
        }
        else
        {
            log_printf( &logger, "* Overvoltage condition - Cell balance disabled * \r\n" );
            balancer3_enable_cell_balance( &balancer3, BALANCER3_CELL_BALANCE_DIS );
        }
    }
    Delay_ms( 1 );
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
