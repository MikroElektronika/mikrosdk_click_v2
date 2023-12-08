/*!
 * @file main.c
 * @brief Step Down 7 Click example
 *
 * # Description
 * This library contains API for the Step Down 7 Click driver.
 * This driver provides the functions to set the output voltage treshold.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization, default settings sets output voltage to 1.5 V.
 *
 * ## Application Task
 * This example demonstrates the use of the Step Down 7 Click board™ by changing 
 * output voltage every 5 seconds starting from 1.5 V up to 3.3 V.
 * 
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "stepdown7.h"

static stepdown7_t stepdown7;
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
    stepdown7_cfg_t stepdown7_cfg;  /**< Click config object. */

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
    stepdown7_cfg_setup( &stepdown7_cfg );
    STEPDOWN7_MAP_MIKROBUS( stepdown7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepdown7_init( &stepdown7, &stepdown7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPDOWN7_ERROR == stepdown7_default_cfg ( &stepdown7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    for ( uint8_t n_cnt = STEPDOWN7_OUTPUT_1V5; n_cnt <= STEPDOWN7_OUTPUT_3V3; n_cnt++ )
    {
        stepdown7_set_output( &stepdown7, n_cnt );
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
        case ( STEPDOWN7_OUTPUT_1V5 ):
        {
            log_printf( &logger, " 1.5V\r\n" );
            break;
        }
        case ( STEPDOWN7_OUTPUT_2V5 ):
        {
            log_printf( &logger, " 2.5V\r\n" );
            break;
        }
        case ( STEPDOWN7_OUTPUT_3V3 ):
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
