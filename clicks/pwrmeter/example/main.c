/*!
 * \file 
 * \brief PwrMeter Click example
 * 
 * # Description
 * This click is capable of measuring voltage and current through the load, connected to either 
 * AC or DC power source. It is used to calculate all the measurement parameters, returning 
 * values of multiple power parameters directly, over the UART interface, reducing the processing 
 * load on the host MCU. These parameters include active, reactive, and apparent power, current 
 * and voltage RMS, line frequency, and power factor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes UART interface, puts output of regulator in active state and
 * configures gain channel and uart baud rate.
 * 
 * ## Application Task  
 * Reads voltage, current and power measurements from data registers, converts this values
 * to determined units and all results on uart terminal. Repeats operation every second.
 * 
 * ## Additional Function
 * - void check_response ( )
 * - void float_conv ( )
 * - void float_to_string ( float num, char *str )
 * 
 * ## Note
 * Do not apply higher voltage than 60V to this board! This click is designed for lower voltage 
 * monitoring and evaluation of the MCP39F511A and its basic functionalities. 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pwrmeter.h"
#include "string.h"
#include "math.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

// ------------------------------------------------------------------ VARIABLES


static pwrmeter_t pwrmeter;
static log_t logger;

PWRMETER_RETVAL response_byte;
uint16_t voltage_rms;
uint32_t current_rms;
uint32_t active_power;
uint32_t reactive_power;
uint32_t apparent_power;
int32_t power_factor;
uint8_t status_byte;

char text[ 100 ];
float meas_data[ 6 ];

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void check_response ( )
{
    if ( response_byte != PWRMETER_SUCCESSFUL )
    {
        switch ( response_byte )
        {
            case PWRMETER_ADDRESS_FAIL :
            {
                log_printf( &logger, "Wrong address parameter\r\n" );
            break;
            }
            case PWRMETER_CHECKSUM_FAIL :
            {
                log_printf( &logger, "Checksum fail\r\n" );
            break;
            }
            case PWRMETER_COMMAND_FAIL :
            {
                log_printf( &logger, "Command can't be performed\r\n" );
            break;
            }
            case PWRMETER_NBYTES_FAIL :
            {
                log_printf( &logger, "Number of bytes is out of range\r\n" );
            break;
            }
            case PWRMETER_PAGE_NUM_FAIL :
            {
                log_printf( &logger, "Page number is out of range\r\n" );
            break;
            }
            default :
            {
            break;
            }
        }
    }
}

void float_conv ( )
{
    uint8_t count;
    uint8_t con_cnt = 0;
    uint8_t con_var = 0;

    for ( count = 0; count < 100; count++ )
    {
        if ( text[ count ] == '.' )
        {
            con_var = 1;
        }
        if ( con_var == 1 )
        {
            con_cnt++;
        }
        if ( con_cnt > 3 )
        {
            if ( ( text[ count ] == 'e' ) || ( con_var == 2 ) )
            {
                text[ count - (con_cnt - 4) ] = text[ count ];
                text[ count ] = 0;
                con_var = 2;
            }
            else
            {
                text[ count ] = 0;
            }
        }
    }
}

void float_to_string ( float num, char *str )
{
   int whole_part = num;
   int digit = 0; 
   int reminder = 0;
   int log_value = log10( num );
   int index = log_value;
   int  i;
   int precision = 5;
   long wt = 0;
   float fraction_part;
   float tmp1;
   float tmp;

   // Initilise stirng to zero
   memset( str, 0 , 20 );

   // Extract the whole part from float num
   for ( i = 1 ; i < log_value + 2 ; i++ )
   {
       wt  =  pow( 10.0, i );
       reminder = whole_part  %  wt;
       digit = ( reminder - digit ) / ( wt / 10 );

       // Store digit in string
       str[ index-- ] = digit + 48;              // ASCII value of digit  = digit + 48
       if ( index == -1 )
       {
          break;
       }    
   }

    index = log_value + 1;
    str[ index ] = '.';

   fraction_part  = num - whole_part;
   tmp1 = fraction_part;
   tmp = 0;

   // Extract the fraction part from  num
   for ( i= 1; i < precision; i++ )
   {
      wt = 10; 
      tmp  = tmp1 * wt;
      digit = tmp;

      // Store digit in string
      str[ ++index ] = digit + 48;           // ASCII value of digit  = digit + 48
      tmp1 = tmp - digit;
   }    

}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pwrmeter_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    pwrmeter_cfg_setup( &cfg );
    PWRMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pwrmeter_init( &pwrmeter, &cfg );

    pwrmeter_enable( &pwrmeter, PWRMETER_ENABLE );
    Delay_ms( 100 );
    response_byte = pwrmeter_write_reg_dword ( &pwrmeter, PWRMETER_SYS_CONFIG_REG, PWRMETER_VOLT_GAIN_1 | PWRMETER_CURR_GAIN_8 | PWRMETER_UART_BR_9600 );
    check_response( );
    response_byte = pwrmeter_send_command( &pwrmeter, PWRMETER_SAVE_TO_FLASH_COMM );
    check_response( );

    log_printf( &logger, "PWR Meter is initialized\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    response_byte = pwrmeter_read_reg_word( &pwrmeter, PWRMETER_VOLT_RMS_REG, &voltage_rms );
    check_response( );
    response_byte = pwrmeter_read_reg_dword( &pwrmeter, PWRMETER_CURR_RMS_REG, &current_rms );
    check_response( );
    response_byte = pwrmeter_read_reg_dword( &pwrmeter, PWRMETER_ACTIVE_PWR_REG, &active_power );
    check_response( );
    response_byte = pwrmeter_read_reg_dword( &pwrmeter, PWRMETER_REACTIVE_PWR_REG, &reactive_power );
    check_response( );
    response_byte = pwrmeter_read_reg_dword( &pwrmeter, PWRMETER_APPARENT_PWR_REG, &apparent_power );
    check_response( );
    response_byte = pwrmeter_read_reg_signed( &pwrmeter, PWRMETER_PWR_FACTOR_REG, PWRMETER_16BIT_DATA, &power_factor );
    check_response( );
    
    meas_data[ 0 ] = ( float ) voltage_rms / 100;
    meas_data[ 1 ] = ( float ) current_rms / 1000;
    meas_data[ 2 ] = ( float ) active_power / 100000;
    meas_data[ 3 ] = ( float ) reactive_power / 100000;
    meas_data[ 4 ] = ( float ) apparent_power / 100000;
    meas_data[ 5 ] = ( float ) power_factor / 32767;
    
    response_byte = pwrmeter_get_status( &pwrmeter, &status_byte );
    check_response( );
    
    if ( ( status_byte & PWRMETER_DCMODE_MASK ) != 0 )
    {
        log_printf( &logger, "DC mode\r\n" );
    }
    else
    {
        log_printf( &logger, "AC mode\r\n" );
    }
    
    float_to_string( meas_data[ 0 ], text );
    float_conv( );
    log_printf( &logger, "RMS voltage:  " );
    if ( ( ( status_byte & PWRMETER_DCMODE_MASK ) != 0) && ( ( status_byte & PWRMETER_DCVOLT_SIGN_MASK ) == 0 ) )
    {
        log_printf( &logger, "-" );
    }
    log_printf( &logger, "%s[ V ]\r\n", text );
    
    float_to_string( meas_data[ 1 ], text );
    float_conv( );
    log_printf( &logger, "RMS current:  " );
    if ( ( ( status_byte & PWRMETER_DCMODE_MASK ) != 0 ) && ( ( status_byte & PWRMETER_DCCURR_SIGN_MASK ) == 0 ) )
    {
        log_printf( &logger, "-" );
    }
    log_printf( &logger, "%s[ mA ]\r\n", text );
    
    float_to_string( meas_data[ 2 ], text );
    float_conv( );
    log_printf( &logger, "Active power:  " );
    if ( ( status_byte & PWRMETER_PA_SIGN_MASK ) == 0 )
    {
        log_printf( &logger, "-" );
    }
    log_printf( &logger, "%s[ W ]\r\n", text );
    
    float_to_string( meas_data[ 3 ], text );
    float_conv( );
    log_printf( &logger, "Reactive power:  " );
    if ( ( status_byte & PWRMETER_PR_SIGN_MASK ) == 0 )
    {
        log_printf( &logger, "-" );
    }
    log_printf( &logger, "%s[ VAr ]\r\n", text );
    
    float_to_string( meas_data[ 4 ], text );
    float_conv( );
    log_printf( &logger, "Apparent power:  " );
    log_printf( &logger, "%s[ VA ]\r\n", text );

    float_to_string( meas_data[ 5 ], text );
    float_conv( );
    log_printf( &logger, "power factor:  %s\r\n", text );
    log_printf( &logger, "-----------------------------------\r\n" );
    
    Delay_ms( 1000 );
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
