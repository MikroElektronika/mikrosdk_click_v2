/*!
 * \file 
 * \brief SurfaceTemp2 Click example
 * 
 * # Description
 * This example demonstrates the use of Surface Temp 2 Click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes the driver and configures the click board.
 * 
 * ## Application Task  
 * Reads the temperature in Celsius and displays the value on the USB UART each second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "surfacetemp2.h"

// ------------------------------------------------------------------ VARIABLES

static surfacetemp2_t surfacetemp2;
static log_t logger;

uint8_t setup_val;
float temperature;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    surfacetemp2_cfg_t cfg;

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

    surfacetemp2_cfg_setup( &cfg );
    SURFACETEMP2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    surfacetemp2_init( &surfacetemp2, &cfg );

    setup_val = SURFACETEMP2_CFG_FLT_Q_4 | SURFACETEMP2_CFG_CT_MODE | SURFACETEMP2_CFG_RES_16;
    surfacetemp2_setup ( &surfacetemp2, setup_val );
    surfacetemp2_set_high_trsh( &surfacetemp2, 40.00 );
    surfacetemp2_set_low_trsh( &surfacetemp2, 10.00 );
    surfacetemp2_set_crit_trsh( &surfacetemp2, 70.00 );
    surfacetemp2_set_hys_val( &surfacetemp2, 5 );
    log_info( &logger, "---- Application Task ----" );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    temperature = surfacetemp2_get_temperature( &surfacetemp2 );
    log_printf( &logger, " Temperature : %.2f C \r\n", temperature );
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
