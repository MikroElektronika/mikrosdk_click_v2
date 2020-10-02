/*!
 * \file 
 * \brief Opto Encoder 2 Click example
 * 
 * # Description
 * This application is used to encode motion or rotation
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO driver and resets encoder counter to 0(zero)
 * 
 * ## Application Task  
 * If encoder is moving - increments or decrements encoder position 
 * on every rising edge on Channel A (INT pin) and logs encoder position
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "optoencoder2.h"

// ------------------------------------------------------------------ VARIABLES

static optoencoder2_t optoencoder2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    optoencoder2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    optoencoder2_cfg_setup( &cfg );
    OPTOENCODER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    optoencoder2_init( &optoencoder2, &cfg );

    optoencoder2_zero_counter( &optoencoder2 );
    log_printf( &logger, "> app init done \r\n" );
}

void application_task ( )
{
    int32_t encoder_position = 0;
    uint8_t stop_flag = 0;

    stop_flag = optoencoder2_isr( &optoencoder2, 100 );
    encoder_position = optoencoder2_get_position( &optoencoder2 );
    
    if ( stop_flag == 0 )
    {
        log_printf( &logger, "> pos: %d \r\n", encoder_position );
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
