/*!
 * \file 
 * \brief Pixi Click example
 * 
 * # Description
 * This example showcases how to initialize, configure and use the Pixi click moduel. The click
 * features Maxim Integrated's versatile, proprietary PIXI™ technology - the industry's first
 * configurable 20-channel mixed-signal data converter. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the click and logger modules. After the initial setup
 * a device id check is performed which will stop the module if the check fails. Additional con-
 * figurating is done in the default_cfg(...) function.
 * 
 * ## Application Task
 * This function sets the output signal on port 0 to different values every second. 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pixi.h"

// ------------------------------------------------------------------ VARIABLES

static pixi_t pixi;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    pixi_cfg_t cfg;
    uint32_t res;

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
    Delay_ms ( 100 );

    //  Click initialization.

    pixi_cfg_setup( &cfg );
    PIXI_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pixi_init( &pixi, &cfg );

    //  Device ID check.

    pixi_read_reg( &pixi, PIXI_REG_DEVICE_ID, &res );
    if ( res != 1060 )
    {
        log_printf( &logger, "ERROR : WRONG DEVICE ID!\r\n" );
        for( ; ; );
    }
    else
    {
        log_printf( &logger, "Driver Init - DONE!\r\n" );
    }

    //  Default configuration.

    pixi_default_cfg( &pixi );
}

void application_task ( )
{
    pixi_write_reg( &pixi, PIXI_REG_GPO_DATA, 0x1 );
    log_printf( &logger, "Led on\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    pixi_write_reg( &pixi, PIXI_REG_GPO_DATA, 0 );
    log_printf( &logger, "Led off\r\n" );
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
