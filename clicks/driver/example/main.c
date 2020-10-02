/*!
 * \file 
 * \brief Driver Click example
 * 
 * # Description
 * This application offering a nine-pole spring terminal that can be used to implement and realize a wide range of different applications.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO driver and selects which inputs will be set in operation.
   Bits from 0 to 6 (selectIN) select inputs from IN1 to IN7, respectively.
 * 
 * ## Application Task  
 * Performs cycles in which selected inputs will be turned on for pulseWidth
   delay time one by one. When one input is turned on, he will be turned off after desired delay time before the next input be turned on.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "driver.h"

// ------------------------------------------------------------------ VARIABLES

static driver_t driver;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    driver_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    driver_cfg_setup( &cfg );
    DRIVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    driver_init( &driver, &cfg );
}

void application_task ( void )
{
    uint8_t select_in;
    uint8_t temp;
    uint8_t count;

    select_in = 0x7F;
    temp = 1;
    
    for (count = 0; count < 7; count++)
    {
        switch ( select_in & temp )
        {
            case 0x01 :
            {
                driver_set_in1( &driver, ENABLE_IN );
                Delay_ms( PULSE_WIDTH );
                driver_set_in1( &driver, DISABLE_IN );
                break;
            }
            case 0x02 :
            {
                driver_set_in2( &driver, ENABLE_IN );
                Delay_ms( PULSE_WIDTH );
                driver_set_in2( &driver, DISABLE_IN );
                break;
            }
            case 0x04 :
            {
                driver_set_in3( &driver, ENABLE_IN );
                Delay_ms( PULSE_WIDTH );
                driver_set_in3( &driver, DISABLE_IN );
                break;
            }
            case 0x08 :
            {
                driver_set_in4( &driver, ENABLE_IN );
                Delay_ms( PULSE_WIDTH );
                driver_set_in4( &driver, DISABLE_IN );
                break;
            }
            case 0x10 :
            {
                driver_set_in5( &driver, ENABLE_IN );
                Delay_ms( PULSE_WIDTH );
                driver_set_in5( &driver, DISABLE_IN );
                break;
            }
            case 0x20 :
            {
                driver_set_in6( &driver, ENABLE_IN );
                Delay_ms( PULSE_WIDTH );
                driver_set_in6( &driver, DISABLE_IN );
                break;
            }
            case 0x40 :
            {
                driver_set_in7( &driver, ENABLE_IN );
                Delay_ms( PULSE_WIDTH );
                driver_set_in7( &driver, DISABLE_IN );
                break;
            }
            default :
            {
                break;
            }
        }

        temp <<= 1;
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
