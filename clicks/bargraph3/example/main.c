/*!
 * \file 
 * \brief BarGraph3 Click example
 * 
 * # Description
 * This application used to create various types of VU meters, 
 * status indicators, different types of counters and similar devices.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver init, enable device and set PWM
 * 
 * ## Application Task  
 * Counter passes through the loop and logs the value of the 
 * counter on the bargraph display.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "bargraph3.h"

// ------------------------------------------------------------------ VARIABLES

static bargraph3_t bargraph3;
static log_t logger;


void application_init ( void )
{
    log_cfg_t log_cfg;
    bargraph3_cfg_t cfg;

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

    bargraph3_cfg_setup( &cfg );
    BARGRAPH3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    bargraph3_init( &bargraph3, &cfg );
    
    bargraph3_enable( &bargraph3, BARGRAPH3_DEVICE_ENABLE );
    bargraph3_set_pwm( &bargraph3, BARGRAPH3_DEVICE_ENABLE );
    Delay_ms( 500 );
}

void application_task ( void )
{
   uint8_t bargraph_cnt;
    
    for ( bargraph_cnt = 0; bargraph_cnt <= 5; bargraph_cnt++ )
    {
        bargraph3_display( &bargraph3, BARGRAPH3_INCREASE_LED,  
                           BARGRAPH3_DIRECTION_BOTTOM_TO_TOP, 
                           bargraph_cnt );
        Delay_ms( 1000 );
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
