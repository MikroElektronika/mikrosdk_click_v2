/*!
 * \file 
 * \brief Ambient5 Click example
 * 
 * # Description
 * This application calculates the ambiance light. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes i2c driver, powers the device and calculates refresh time.
 * 
 * ## Application Task  
 * Logs high resolution data after a period of time ( refresh time calculated using - ambient5_getRefreshTime( ) )
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ambient5.h"

// ------------------------------------------------------------------ VARIABLES

static ambient5_t ambient5;
static log_t logger;

static uint16_t r_time;
static uint16_t i;
static uint16_t lth;
static uint16_t hth;
static float high_res_light_level;
static float res;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient5_cfg_t ambient_cfg;

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

    ambient5_cfg_setup( &ambient_cfg );
    AMBIENT5_MAP_MIKROBUS( ambient_cfg, MIKROBUS_1 );
    ambient5_init( &ambient5, &ambient_cfg );
    ambient5_default_cfg( &ambient5 );

	log_printf( &logger, "App init done\r\n" );
}

void application_task ( void )
{
    r_time = ambient5_get_refresh_time( &ambient5 );
    
    for (i = 0; i < r_time; i++)
	{
		Delay_ms(1);
	}

	high_res_light_level = ambient5_get_high_resolution_light_level( &ambient5 );

	log_printf( &logger, " Ambient Light Level : %.2f lx\r\n", high_res_light_level );
    
    Delay_ms( 500 );
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
