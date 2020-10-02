/*!
 * \file 
 * \brief c3DHall Click example
 * 
 * # Description
 * This application use to determine angle position.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - SPI and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of 3D Hall Click board.
 * 3D Hall Click communicates with register via SPI by read data from register
 * and calculate Alpha and Beta angle position.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs on usb uart for aproximetly every 3 sec.
 * 
 *
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c3dhall.h"

// ------------------------------------------------------------------ VARIABLES

static c3dhall_t c3dhall;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    c3dhall_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c3dhall_cfg_setup( &cfg );
    C3DHALL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3dhall_init( &c3dhall, &cfg );
}

void application_task ( void )
{
    c3dhall_all_data_t all_data;

    uint8_t angle_alpha;
    uint8_t angle_beta;

    c3dhall_read_all_data( &c3dhall, &all_data );
    Delay_100ms( );

    if ( ( all_data.data_error | all_data.data_sum ) == C3DHALL_NO_ERRORS )
    {
        angle_alpha = c3dhall_calculate_angle( &c3dhall, all_data.data_angle_a );
        angle_beta = c3dhall_calculate_angle( &c3dhall, all_data.data_angle_b );


        log_printf( &logger, "     Alpha : %d\r\n", angle_alpha );



        log_printf( &logger, "     Beta  : %d\r\n", angle_beta );

        log_printf( &logger, "-------------------------\r\n", angle_beta );

        Delay_1sec( );
        Delay_1sec( );
        Delay_1sec( );
    }
    else
    {
        if ( all_data.data_error == C3DHALL_F_ADCMONITOR )
            log_printf( &logger, "       ADC Failure       \r\n" );
        else if ( all_data.data_error == C3DHALL_F_ADCSATURA )
            log_printf( &logger, "    Electrical failure   \r\n"  );
        else if ( all_data.data_error == C3DHALL_F_GAINTOOLOW )
            log_printf( &logger, "    Gain code is less    \r\n" );
        else if ( all_data.data_error == C3DHALL_F_GAINTOOHIGH )
            log_printf( &logger, "   Gain code is greater  \r\n" );
        else if ( all_data.data_error == C3DHALL_F_NORMTOOLOW )
            log_printf( &logger, "   Fast norm below 30   \r\n" );
        else if ( all_data.data_error == C3DHALL_F_FIELDTOOLOW )
            log_printf( &logger, "     The norm is less    \r\n" );
        else if ( all_data.data_error == C3DHALL_F_FIELDTOOHIGH )
            log_printf( &logger, "   The norm is greater   \r\n" );
        else if ( all_data.data_error == C3DHALL_F_ROCLAMP )
            log_printf( &logger, "  Analog Chain Rough off \r\n" );
        else if ( all_data.data_error == C3DHALL_F_DEADZONEALPHA )
            log_printf( &logger, " Angle ALPHA in deadzone \r\n" );
        else if ( all_data.data_error == C3DHALL_F_DEADZONEBETA )
            log_printf( &logger, "  Angle BETA in deadzone \r\n" );
        else if ( all_data.data_error == C3DHALL_MULTIPLE_ERRORS )
            log_printf( &logger, "   More than one error   \r\n" );
        else
            log_printf( &logger, "      Unknown error      \r\n" );

        log_printf( &logger, "-------------------------\r\n" );
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
