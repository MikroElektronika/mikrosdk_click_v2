/*!
 * \file 
 * \brief THERMO5 Click example
 * 
 * # Description
 * This app measures internal and external temperature.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes device.
 * 
 * ## Application Task  
 * This is an example that shows the most important functions that Thermo 5 Click has.
 *
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "thermo5.h"

// ------------------------------------------------------------------ VARIABLES

static thermo5_t thermo5;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo5_cfg_t cfg;

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

    thermo5_cfg_setup( &cfg );
    THERMO5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo5_init( &thermo5, &cfg );
    Delay_ms ( 500 );
    log_printf( &logger, " Thermo 5 Click ready! \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 100 );
}

void application_task ( void )
{
    float inter_temp;
    float exter_temp_1;
    float exter_temp_2;
    float exter_temp_3;

    inter_temp = thermo5_read_inter_temp( &thermo5 );
    log_printf( &logger, " Internal temperature :   %.2f \r\n", inter_temp );
    exter_temp_1 = thermo5_read_extern_1_temp( &thermo5 );
    log_printf( &logger, " External temperature 1 : %.2f \r\n", exter_temp_1 );
    exter_temp_2 = thermo5_read_extern_2_temp( &thermo5 );
    log_printf( &logger, " External temperature 2 : %.2f \r\n", exter_temp_2 );
    exter_temp_3 = thermo5_read_extern_3_temp( &thermo5 );
    log_printf( &logger, " External temperature 3 : %.2f \r\n", exter_temp_2 );
    log_printf( &logger, "---------------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
