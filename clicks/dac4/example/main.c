/*!
 * \file 
 * \brief Dac4 Click example
 * 
 * # Description
 * This application enables usage of digital to analog converter.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C driver, executes general call reset and wake up commands and initializes variables to zero
 * 
 * ## Application Task  
 * Waits for user input and based on it logs reports or sets output value for specified channel
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dac4.h"

// ------------------------------------------------------------------ VARIABLES

static dac4_t dac4;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void dac4_log_report ( uint8_t channel_no )
{
    dac4_channel_setting_t dac4_channel_buffer[ 8 ];

    dac4_data_report ( &dac4, dac4_channel_buffer );
    log_printf( &logger, "~--~--~--~--~--~--~--~--~--~--~--~--~\r\n" );
    channel_no *= 2;
    
    log_printf( &logger, "~-- Power ON bit: " );
    switch ( dac4_channel_buffer[ channel_no ].por_bit )
    {
        case 0:
        {
            log_printf( &logger,"Power OFF\r\n" );
            break;
        }
        case 1:
        {
            log_printf( &logger, "Power ON\r\n" );
            break;
        }
        default :
        {
            break;
        }
    }

    log_printf( &logger, "~-- V reference    : " );
    switch ( dac4_channel_buffer[ channel_no ].voltage_reference )
    {
        case DAC4_VREF_EXTERNAL:
        {
            log_printf( &logger, "External\r\n" );
            break;
        }
        case DAC4_VREF_INTERNAL:
        {
            log_printf( &logger, "Internal\r\n" );
            break;
        }
        default :
        {
            break;
        }
    }

    log_printf( &logger, "~-- Power mode     : " );
    switch ( dac4_channel_buffer[ channel_no ].power_mode )
    {
        case DAC4_MODE_NORMAL:
        {
            log_printf( &logger, "Normal\r\n" );
            break;
        }
        case DAC4_MODE_1kOhm:
        {
            log_printf( &logger, "1 kOhm\r\n" );
            break;
        }
        case DAC4_MODE_100kOhm:
        {
            log_printf( &logger, "100 kOhm\r\n" );
            break;
        }
        case DAC4_MODE_500kOhm:
        {
            log_printf( &logger, "500 kOhm\r\n" );
            break;
        }
        default :
        {
            break;
        }
    }

    log_printf( &logger, "~-- Gain value     : " );
    switch ( dac4_channel_buffer[ channel_no ].gain_value )
    {
        case DAC4_MODE_NORMAL:
        {
            log_printf( &logger, "1x Gain\r\n" );
            break;
        }
        case DAC4_MODE_1kOhm:
        {
            log_printf( &logger, "2x Gain\r\n" );
            break;
        }
        default :
        {
            break;
        }
    }
    
    log_printf( &logger, "~-- DAC input data : %d  [0-4095]\r\n", dac4_channel_buffer[ channel_no ].dac_input_data );
}

void dac4_set_output ( uint8_t channel_set, uint8_t output_set )
{
    dac4_channel_setting_t dac4_channel_x;
    uint8_t single_write_flag;
    uint16_t aux_dac_input_data;
    
    switch ( output_set )
    {
        case 1:
        {
            aux_dac_input_data = 0;
        break;
        }
        case 2:
        {
            aux_dac_input_data = 1229;
        break;
        }
        case 3:
        {
            aux_dac_input_data = 2457;
        break;
        }
        case 4:
        {
            aux_dac_input_data = 3685;
        break;
        }
        default :
        {
        break;
        }
    }
    
    dac4_channel_x.channel_select = channel_set;
    dac4_channel_x.udac_bit = DAC4_UPDATE;
    dac4_channel_x.voltage_reference = DAC4_VREF_EXTERNAL;
    dac4_channel_x.power_mode = DAC4_MODE_NORMAL;
    dac4_channel_x.gain_value = DAC4_GAIN_x1;
    dac4_channel_x.dac_input_data = aux_dac_input_data;

    single_write_flag = dac4_single_write( &dac4, &dac4_channel_x );
    if ( 0 != single_write_flag )
    {
        log_printf( &logger, "~-- Fatal ERROR !!! \r\n" );
    }
    else
    {
        log_printf( &logger, "~--~--~--~--~--~--~--~--~--~--~--~--~ \r\n" );
        log_printf( &logger, "~-- Output setup done \r\n" );
        log_printf( &logger, "~--~--~--~--~--~--~--~--~--~--~--~--~ \r\n" );
    }
}

void dac4_channel_report ( )
{
    log_printf( &logger, "-----> Channel A \r\n" );
    dac4_set_output( DAC4_CHANNEL_A, 1 );
    dac4_log_report( 0 );
    Delay_ms( 3000 );
    
    log_printf( &logger, "-----> Channel B \r\n" );
    dac4_set_output( DAC4_CHANNEL_B, 2 );
    dac4_log_report( 1 );
    Delay_ms( 3000 );
    
    log_printf( &logger, "-----> Channel C \r\n" );
    dac4_set_output( DAC4_CHANNEL_C, 3 );
    dac4_log_report( 2 );
    Delay_ms( 3000 );
    
    log_printf( &logger, "-----> Channel D \r\n" );
    dac4_set_output( DAC4_CHANNEL_D, 4 );
    dac4_log_report( 3 );
    Delay_ms( 3000 );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dac4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    dac4_cfg_setup( &cfg );
    DAC4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dac4_init( &dac4, &cfg );
    log_info( &logger, "---- Application ----" );

    Delay_ms( 500 );
    dac4_general_call_reset( &dac4 );
    Delay_ms( 500 );
    dac4_general_call_wake_up( &dac4 );
    Delay_ms( 500 );

    dac4_default_cfg( &dac4 );
    
    log_printf( &logger, "~-- App init done \r\n \r\n" );
}

void application_task ( void )
{
    dac4_channel_report( );
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
