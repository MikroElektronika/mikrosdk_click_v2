/*!
 * \file 
 * \brief Motion EKMC Click example
 * 
 * # Description
 * <DEMOAPP_DESCRIPTION>
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * <DEMOAPP_INIT_DESCRIPTION>
 * 
 * ## Application Task  
 * <DEMOAPP_TASK_DESCRIPTION>
 * 
 * *note:* 
 * <NOTE>
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "motionekmc.h"

// ------------------------------------------------------------------ VARIABLES

static motionekmc_t motionekmc;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    motionekmc_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    motionekmc_cfg_setup( &cfg );
    MOTIONEKMC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    motionekmc_init( &motionekmc, &cfg );
    
    motionekmc_default_cfg( &motionekmc );
}

void application_task ( void )
{
    uint8_t int_status;

    int_status = motionekmc_detect_state( &motionekmc );

    if ( int_status == MOTIONEKMC_DETECT_OBJECT )
    {
        log_printf( &logger, "Motion detected \r\n" );
        while ( int_status == MOTIONEKMC_DETECT_OBJECT )
        {
            int_status = motionekmc_detect_state( &motionekmc );
        }
        log_printf( &logger, "Motion wait \r\n" );
        Delay_ms( 100 );
    }
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
