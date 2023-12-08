/*!
 * @file main.c
 * @brief Nano Power 3 Click example
 *
 * # Description
 * This library contains API for the Nano Power 3 Click driver.
 * This driver provides the functions to set the output voltage treshold.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization, default settings sets output voltage to 1 V.
 *
 * ## Application Task
 * This example demonstrates the use of the Nano Power 3 Click board™ by changing 
 * output voltage every 5 seconds starting from 1 V up to 4.5 V.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "nanopower3.h"

static nanopower3_t nanopower3;
static log_t logger;

/**
 * @brief Output level printing function.
 * @details This function is used to log value of the selected voltage to UART terminal.
 * @param[in] sel_level : Selected voltage level.
 * @return Nothing.
 * @note None.
 */
static void print_selected_output_level ( uint8_t sel_level );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nanopower3_cfg_t nanopower3_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    nanopower3_cfg_setup( &nanopower3_cfg );
    NANOPOWER3_MAP_MIKROBUS( nanopower3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == nanopower3_init( &nanopower3, &nanopower3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( NANOPOWER3_ERROR == nanopower3_default_cfg ( &nanopower3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    for ( uint8_t n_cnt = NANOPOWER3_1V_OUT_VOLTAGE; n_cnt <= NANOPOWER3_4V5_OUT_VOLTAGE; n_cnt++ )
    {
        nanopower3_set_voltage( &nanopower3, n_cnt );
        log_printf( &logger, " Selected output is:" );
        print_selected_output_level ( n_cnt );
        Delay_ms( 5000 );
    }
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

static void print_selected_output_level ( uint8_t sel_level )
{
    switch ( sel_level )
    {
        case ( NANOPOWER3_1V_OUT_VOLTAGE ):
        {
            log_printf( &logger, " 1V\r\n" );
            break;
        }
        case ( NANOPOWER3_1V2_OUT_VOLTAGE ):
        {
            log_printf( &logger, " 1.2V\r\n" );
            break;
        }
        case ( NANOPOWER3_1V5_OUT_VOLTAGE ):
        {
            log_printf( &logger, " 1.5V\r\n" );
            break;
        }
        case ( NANOPOWER3_1V8_OUT_VOLTAGE ):
        {
            log_printf( &logger, " 1.8V\r\n" );
            break;
        }
        case ( NANOPOWER3_2V_OUT_VOLTAGE ):
        {
            log_printf( &logger, " 2V\r\n" );
            break;
        }
        case ( NANOPOWER3_2V5_OUT_VOLTAGE ):
        {
            log_printf( &logger, " 2.5V\r\n" );
            break;
        }
        case ( NANOPOWER3_3V_OUT_VOLTAGE ):
        {
            log_printf( &logger, " 3V\r\n" );
            break;
        }
        case ( NANOPOWER3_3V3_OUT_VOLTAGE ):
        {
            log_printf( &logger, " 3.3V\r\n" );
            break;
        }
        case ( NANOPOWER3_3V5_OUT_VOLTAGE ):
        {
            log_printf( &logger, " 3.5V\r\n" );
            break;
        }
        case ( NANOPOWER3_4V_OUT_VOLTAGE ):
        {
            log_printf( &logger, " 4V\r\n" );
            break;
        }
        case ( NANOPOWER3_4V5_OUT_VOLTAGE ):
        {
            log_printf( &logger, " 4.5V\r\n" );
            break;
        }
        default:
        {
            log_printf( &logger, " ERROR\r\n" );
        }
    }
}

// ------------------------------------------------------------------------ END
