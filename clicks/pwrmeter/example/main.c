/*!
 * \file 
 * \brief PwrMeter Click example
 * 
 * # Description
 * This Click is capable of measuring voltage and current through the load, connected to either 
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
 * Reads voltage, current and power measurements from data registers, then converts this values
 * to determined units and logs all results on uart terminal each second.
 * 
 * ## Additional Function
 * - void check_response ( ) - Displays an appropriate message on USB UART 
 * if there's an error occurred in the last response from the module.
 * 
 * ## Note
 * Do not apply higher voltage than 60V to this board! This Click is designed for lower voltage 
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

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pwrmeter_cfg_t cfg;

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

    pwrmeter_cfg_setup( &cfg );
    PWRMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pwrmeter_init( &pwrmeter, &cfg );
    Delay_ms ( 500 );
    
    pwrmeter_enable( &pwrmeter, PWRMETER_ENABLE );
    Delay_ms ( 100 );
    
    response_byte = pwrmeter_write_reg_dword ( &pwrmeter, PWRMETER_SYS_CONFIG_REG, PWRMETER_VOLT_GAIN_1 | PWRMETER_CURR_GAIN_8 | PWRMETER_UART_BR_9600 );
    check_response( );
    response_byte = pwrmeter_send_command( &pwrmeter, PWRMETER_SAVE_TO_FLASH_COMM );
    check_response( );

    log_printf( &logger, "PWR Meter is initialized\r\n" );
    Delay_ms ( 100 );
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
    

    log_printf( &logger, "RMS voltage:  " );
    if ( ( ( status_byte & PWRMETER_DCMODE_MASK ) != 0) && ( ( status_byte & PWRMETER_DCVOLT_SIGN_MASK ) == 0 ) )
    {
        log_printf( &logger, "-" );
    }
    log_printf( &logger, "%.2f[ V ]\r\n", meas_data[ 0 ] );
    
    
    log_printf( &logger, "RMS current:  " );
    if ( ( ( status_byte & PWRMETER_DCMODE_MASK ) != 0 ) && ( ( status_byte & PWRMETER_DCCURR_SIGN_MASK ) == 0 ) )
    {
        log_printf( &logger, "-" );
    }
    log_printf( &logger, "%.2f[ mA ]\r\n", meas_data[ 1 ] );
    
    
    log_printf( &logger, "Active power:  " );
    if ( ( status_byte & PWRMETER_PA_SIGN_MASK ) == 0 )
    {
        log_printf( &logger, "-" );
    }
    log_printf( &logger, "%.2f[ W ]\r\n", meas_data[ 2 ] );
    
    
    log_printf( &logger, "Reactive power:  " );
    if ( ( status_byte & PWRMETER_PR_SIGN_MASK ) == 0 )
    {
        log_printf( &logger, "-" );
    }
    log_printf( &logger, "%.2f[ VAr ]\r\n", meas_data[ 3 ] );
    
   
    log_printf( &logger, "Apparent power:  " );
    log_printf( &logger, "%.2f[ VA ]\r\n", meas_data[ 4 ] );

    
    log_printf( &logger, "Power factor:  %.2f\r\n", meas_data[ 5 ] );
    log_printf( &logger, "-----------------------------------\r\n" );
    
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
