/*!
 * \file 
 * \brief Buck 9 / 10 Click example
 * 
 * # Description
 * Demo application shows basic usage of Buck 9 and Buck 10 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Settings the click in the default configuration.
 * 
 * ## Application Task  
 * Enable and Disable device every 2500 ms.
 * 
 * *Note for Buck 9 click:* 
 *   User can connect from 3v3 or 5v to 36V on the input(VIN) and when 
 *   enable the device get 3v3 or 5v voltage on the output(VOUT).
 *   On the VOUT connect the load to 3A.
 * 
 * Note for Buck 10 click: 
 *   Input voltage recommended range - from 4V to 18V
 *   Low-side valley current limit - from 3A to 3.9A
 *   Low-side negative current limit - (-2.5A)
 *   Output voltage - 3.3V or 5V
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "buck_9_10.h"

// ------------------------------------------------------------------ VARIABLES

static buck_9_10_t buck_9_10;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    buck_9_10_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    buck_9_10_cfg_setup( &cfg );
    BUCK_9_10_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck_9_10_init( &buck_9_10, &cfg );

    buck_9_10_default_cfg( &buck_9_10 );
}

void application_task ( void )
{
    //  Task implementation.

    buck9_set_device_mode ( &buck_9_10, BUCK_9_10_DEVICE_DISABLE );
    Delay_ms( 2500 );
    buck9_set_device_mode ( &buck_9_10, BUCK_9_10_DEVICE_ENABLE );
    Delay_ms( 2500 );
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
