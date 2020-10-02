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
 * Initializes device sets the time interval variable (time_inter) to the 0, which is used for OV condition message logging.
 * 
 * ## Application Task  
 * Allows user to enter a commands that can enable or disable
 *  cell balance and check the overvoltage condition.
 *  When OV condition is not detected, the status message 
 * will be sent after every 8 seconds.
 *  When OV condition is detected, 
 * the status message will be sent after every 2 seconds.
 *  Press '0' when you want to disable cell balance.
 *  Press '1' when you want to enable cell balance.
 *  Press '2' when you want to check the OV condition status immediately.
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

const uint8_t RX_NOT_READY = 0;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    balancer3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    balancer3_cfg_setup( &cfg );
    BALANCER3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    balancer3_init( &balancer3, &cfg );
}

void application_task ( void )
{
    uint16_t time_inter;
    uint8_t ov_cond;

    balancer3_enable_cell_balance( &balancer3, BALANCER3_CELL_BALANCE_DIS );
    log_printf( &logger, "* Cell balance is disabled * %d\r\n" );
         
    balancer3_enable_cell_balance( &balancer3, BALANCER3_CELL_BALANCE_EN );
    log_printf( &logger, "* Cell balance is enabled * %d\r\n" );

    
    ov_cond = balancer3_check_overvoltage_cond( &balancer3 );
    
    if ( ( time_inter == 8000 ) || ( ov_cond == BALANCER3_OV_COND_DETECTED ) )
    {
        if ( ov_cond == BALANCER3_OV_COND_NOT_DETECTED )
        {
            log_printf( &logger, "* Overvoltage condition is not detected * %d\r\n" );
            time_inter = 0;
        }
        else if ( time_inter > 2000 )
        {
            log_printf( &logger, "* Overvoltage condition is detected * %d\r\n", ov_cond );
            time_inter = 0;
        }
        else
        {
            time_inter++;
        }
    }
    else
    {
        time_inter++;
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
