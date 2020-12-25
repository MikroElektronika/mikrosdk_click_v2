/*!
 * \file 
 * \brief Opto 2 Click example
 * 
 * # Description
 * This application used to provide an optical isolation of sensitive microcontroller.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device selects the outputs (OUT1 - OUT4) which state be checked.
 * 
 * ## Application Task  
 * Performs the check procedure for selected outputs and logs the states from that
  outputs on USB UART. Repeat the check procedure every 2 seconds.

 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "opto2.h"

// ------------------------------------------------------------------ VARIABLES

static opto2_t opto2;
static log_t logger;

static uint8_t sel_output;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void opto2_set_logger ( uint8_t sel_out1, uint8_t sel_out2, uint8_t sel_out3, uint8_t sel_out4 )
{
    
    if ( sel_out1 > 1 )
    { 
        sel_out1 = 1;
    }
    if ( sel_out2 > 1 )
    {
        sel_out2 = 1;
    }
    if ( sel_out3 > 1 )
    {
        sel_out3 = 1;
    }
    if ( sel_out4 > 1 )
    {
        sel_out4 = 1;
    }

    sel_output = 0;
    sel_output |= sel_out1;
    sel_output |= sel_out2 << 1;
    sel_output |= sel_out3 << 2;
    sel_output |= sel_out4 << 3;
}

void application_init ( void )
{
    log_cfg_t log_cfg;
    opto2_cfg_t cfg;

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );

    opto2_cfg_setup( &cfg );
    OPTO2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    opto2_init( &opto2, &cfg );

    log_info( &logger, "---- Application Init ----" );

    opto2_set_logger( 1, 1, 0, 0 );
    log_printf( &logger, "OPTO 2 is initialized \r\n" );
    log_printf( &logger, "" );
    Delay_ms( 200 );
}

void application_task ( void )
{
    uint8_t check_output;
    uint8_t cnt;
    uint8_t tmp;

    tmp = 1;

    for ( cnt = 0; cnt < 4; cnt++ )
    {
        switch ( sel_output & tmp )
        {
            case 0x01 :
            {
                check_output = opto2_check_out1( &opto2 );

                if ( check_output == 0 )
                {
                    log_printf( &logger, "OUT1 is low\r\n" );
                }
                else
                {
                    log_printf( &logger, "OUT1 is high\r\n" );
                }
                break;
            }
            case 0x02 :
            {
                check_output = opto2_check_out2( &opto2 );

                if ( check_output == 0 )
                {
                    log_printf( &logger, "OUT2 is low\r\n" );
                }
                else
                {
                    log_printf( &logger, "OUT2 is high\r\n" );
                }
                break;
            }
            case 0x04 :
            {
                check_output = opto2_check_out3( &opto2 );

                if ( check_output == 0 )
                {
                    log_printf( &logger, "OUT3 is low\r\n" );
                }
                else
                {
                    log_printf( &logger, "OUT3 is high\r\n" );
                }
                break;
            }
            case 0x08 :
            {
                check_output = opto2_check_out4( &opto2 );

                if ( check_output == 0 )
                {
                    log_printf( &logger, "OUT4 is low\r\n" );
                }
                else
                {
                    log_printf( &logger, "OUT4 is high\r\n" );
                }
                break;
            }
            default :
            {
                break;
            }
        }

        tmp <<= 1;
    }

    Delay_ms( 2000 );
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
