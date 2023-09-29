/*!
 * @file main.c
 * @brief Step Down 9 Click example
 *
 * # Description
 * This library contains API for the Step Down 9 Click driver.
 * This driver provides the functions to set the output voltage treshold.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization, default settings sets output voltage to 1.6 V.
 *
 * ## Application Task
 * This example demonstrates the use of the Step Down 9 Click board™ by changing 
 * output voltage every 5 seconds starting from 1.6 V up to 10 V.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "stepdown9.h"

static stepdown9_t stepdown9;
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
    stepdown9_cfg_t stepdown9_cfg;  /**< Click config object. */

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
    stepdown9_cfg_setup( &stepdown9_cfg );
    STEPDOWN9_MAP_MIKROBUS( stepdown9_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == stepdown9_init( &stepdown9, &stepdown9_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPDOWN9_ERROR == stepdown9_default_cfg ( &stepdown9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    for ( uint8_t n_cnt = STEPDOWN9_VOUT_1V6; n_cnt <= STEPDOWN9_VOUT_10V; n_cnt++ )
    {
        stepdown9_set_output( &stepdown9, n_cnt );
        log_printf( &logger, " Selected output is:" );
        print_selected_output_level ( n_cnt );
        Delay_ms( 5000 );
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

static void print_selected_output_level ( uint8_t sel_level )
{
    switch ( sel_level )
    {
        case ( STEPDOWN9_VOUT_1V6 ):
        {
            log_printf( &logger, " 1.6V\r\n" );
            break;
        }
        case ( STEPDOWN9_VOUT_2V ):
        {
            log_printf( &logger, " 2V\r\n" );
            break;
        }
        case ( STEPDOWN9_VOUT_2V5 ):
        {
            log_printf( &logger, " 2.5V\r\n" );
            break;
        }
        case ( STEPDOWN9_VOUT_3V ):
        {
            log_printf( &logger, " 3V\r\n" );
            break;
        }
        case ( STEPDOWN9_VOUT_3V3 ):
        {
            log_printf( &logger, " 3.3V\r\n" );
            break;
        }
        case ( STEPDOWN9_VOUT_3V5 ):
        {
            log_printf( &logger, " 3.5V\r\n" );
            break;
        }
        case ( STEPDOWN9_VOUT_4V ):
        {
            log_printf( &logger, " 4V\r\n" );
            break;
        }
        case ( STEPDOWN9_VOUT_4V5 ):
        {
            log_printf( &logger, " 4.5V\r\n" );
            break;
        }
        case ( STEPDOWN9_VOUT_5V ):
        {
            log_printf( &logger, " 5V\r\n" );
            break;
        }
        case ( STEPDOWN9_VOUT_5V5 ):
        {
            log_printf( &logger, " 5.5V\r\n" );
            break;
        }
        case ( STEPDOWN9_VOUT_6V ):
        {
            log_printf( &logger, " 6V\r\n" );
            break;
        }
        case ( STEPDOWN9_VOUT_6V5 ):
        {
            log_printf( &logger, " 6.5V\r\n" );
            break;
        }
        case ( STEPDOWN9_VOUT_7V ):
        {
            log_printf( &logger, " 7V\r\n" );
            break;
        }
        case ( STEPDOWN9_VOUT_7V5 ):
        {
            log_printf( &logger, " 7.5V\r\n" );
            break;
        }
        case ( STEPDOWN9_VOUT_8V ):
        {
            log_printf( &logger, " 8V\r\n" );
            break;
        }
        case ( STEPDOWN9_VOUT_8V5 ):
        {
            log_printf( &logger, " 8.5V\r\n" );
            break;
        }
        case ( STEPDOWN9_VOUT_9V ):
        {
            log_printf( &logger, " 9V\r\n" );
            break;
        }
        case ( STEPDOWN9_VOUT_9V5 ):
        {
            log_printf( &logger, " 9.5V\r\n" );
            break;
        }
        case ( STEPDOWN9_VOUT_10V ):
        {
            log_printf( &logger, " 10V\r\n" );
            break;
        }
        default:
        {
            log_printf( &logger, " ERROR\r\n" );
        }
    }
}

// ------------------------------------------------------------------------ END
