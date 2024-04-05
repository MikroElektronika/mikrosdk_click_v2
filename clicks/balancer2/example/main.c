/*!
 * \file 
 * \brief Balancer2 Click example
 * 
 * # Description
 * This application enable the batery charge. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Sets reference volatage of device, sets pins for supply and cells to high.
 * 
 * ## Application Task  
 * Every 2 seconds logs readings of battery mV lvl
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "balancer2.h"

// ------------------------------------------------------------------ VARIABLES

static balancer2_t balancer2;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    balancer2_cfg_t cfg;

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

    balancer2_cfg_setup( &cfg );
    BALANCER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    balancer2_init( &balancer2, &cfg );

    Delay_ms ( 100 );
    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, "  Balancer 2 Click  \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms ( 100 );
    balancer2_default_cfg ( &balancer2 );
    Delay_ms ( 100 );
}

void application_task ( void )
{
    float battery;

    battery = balancer2_get_batttery_lvl( &balancer2, BALANCER2_BATT1 );
    log_printf( &logger, "Battery 1 : %f mV\r\n", battery );

    battery = balancer2_get_batttery_lvl( &balancer2, BALANCER2_BATT2 );
    log_printf( &logger, "Battery 2 : %f mV\r\n", battery );

    battery = balancer2_get_batttery_lvl( &balancer2, BALANCER2_BATT_BOTH );
    log_printf( &logger, "Batteries : %f mV\r\n", battery );

    log_printf( &logger, "__________________________________________\r\n" );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
