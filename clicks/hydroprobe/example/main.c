/*!
 * \file 
 * \brief HydroProbe Click example
 * 
 * # Description
 * This demo application measures moisture.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes I2C driver, prerforms calibration and makes an initial log.
 * 
 * ## Application Task  
 * This example shows the capabilities of the Hydro Probe Click by measuring 
 * environment moisture content and displaying it in percent via USB UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "hydroprobe.h"

// ------------------------------------------------------------------ VARIABLES

static hydroprobe_t hydroprobe;
static log_t logger;

static uint8_t humy_val = 0;
static uint16_t dry_val = 0;
static uint16_t wet_val = 0;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void hydroprobe_calib ( )
{
    uint8_t cnt;

    log_printf( &logger, " Keep the Probe dry \r\n" );
    dry_val = hydroprobe_max_val( &hydroprobe );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Submerge the Probe in liquid \r\n" );
    for ( cnt = 5; cnt > 0; cnt-- )
    {
        log_printf( &logger, " %d \r\n ", ( uint16_t ) cnt );
        Delay_ms ( 1000 );
    }
    log_printf( &logger, " Keep the Probe submerged \r\n" );
    Delay_ms ( 100 );
    wet_val = hydroprobe_min_val( &hydroprobe );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    hydroprobe_cfg_t cfg;

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

    hydroprobe_cfg_setup( &cfg );
    HYDROPROBE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hydroprobe_init( &hydroprobe, &cfg );
    
    Delay_ms ( 100 );

    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "  Hydro Probe Click  \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    hydroprobe_calib( );
    log_printf( &logger, "     Calibrated      \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    humy_val = hydroprobe_rel_env_hum( &hydroprobe, dry_val, wet_val );
    log_printf( &logger, "Environment moisture content: %d %% \r\n ", ( uint16_t ) humy_val );
    log_printf( &logger, "------------------------------\r\n" );
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
