/*!
 * @file main.c
 * @brief Step Down 5 Click example
 *
 * # Description
 * This library contains API for the Step Down 5 Click driver.
 * This driver provides the functions to set the output voltage treshold.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization, default settings sets output voltage to 0.6 V.
 *
 * ## Application Task
 * This example demonstrates the use of the Step Down 5 Click board™ by changing 
 * output voltage every 5 seconds starting from 0.6 V up to 3.3 V.
 * 
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "stepdown5.h"

static stepdown5_t stepdown5;
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
    stepdown5_cfg_t stepdown5_cfg;  /**< Click config object. */

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
    stepdown5_cfg_setup( &stepdown5_cfg );
    STEPDOWN5_MAP_MIKROBUS( stepdown5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepdown5_init( &stepdown5, &stepdown5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPDOWN5_ERROR == stepdown5_default_cfg ( &stepdown5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    for ( uint8_t n_cnt = STEPDOWN5_OUTPUT_0V6; n_cnt <= STEPDOWN5_OUTPUT_3V3; n_cnt++ )
    {
        stepdown5_set_output( &stepdown5, n_cnt );
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
        case ( STEPDOWN5_OUTPUT_0V6 ):
        {
            log_printf( &logger, " 0.6V\r\n" );
            break;
        }
        case ( STEPDOWN5_OUTPUT_1V5 ):
        {
            log_printf( &logger, " 1.5V\r\n" );
            break;
        }
        case ( STEPDOWN5_OUTPUT_2V5 ):
        {
            log_printf( &logger, " 2.5V\r\n" );
            break;
        }
        case ( STEPDOWN5_OUTPUT_3V3 ):
        {
            log_printf( &logger, " 3.3V\r\n" );
            break;
        }
        default:
        {
            log_printf( &logger, " ERROR\r\n" );
        }
    }
}

// ------------------------------------------------------------------------ END
