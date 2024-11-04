/*!
 * \file 
 * \brief Ldc1000 Click example
 * 
 * # Description
 * This example showcases how to initialize and configure the logger and Click modules and
 * read and display proximity and impendance data.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and Click modules. Configuration data 
 * is written to the: rp maximum/minimum, sensor frequency, LDC/Clock/Power registers.
 * 
 * ## Application Task  
 * This function reads and displays proximity and impendance data every 10th of a second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ldc1000.h"

// ------------------------------------------------------------------ VARIABLES

static ldc1000_t ldc1000;
static log_t logger;

static uint16_t old_proximity;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    ldc1000_cfg_t cfg;

    old_proximity = 0;

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

    ldc1000_cfg_setup( &cfg );
    LDC1000_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ldc1000_init( &ldc1000, &cfg );
    Delay_ms ( 100 );
    ldc1000_default_cfg( &ldc1000 );
    Delay_ms ( 100 );
}

void application_task ( )
{
    uint16_t proximity;
    float inductance;

    proximity = ldc1000_get_proximity_data( &ldc1000 );
    inductance = ldc1000_get_inductance_data( &ldc1000 );

    if ( ( ( proximity - old_proximity ) > LDC1000_SENSITIVITY ) &&
         ( ( old_proximity - proximity ) > LDC1000_SENSITIVITY ) )
    {
        log_printf( &logger, " * Proximity: %d \r\n", proximity );

        log_printf( &logger, " * Impendance: %f uH\r\n", inductance );

        old_proximity = proximity;

        log_printf( &logger, "--------------------\r\n" );
        Delay_ms ( 100 );
    }
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
