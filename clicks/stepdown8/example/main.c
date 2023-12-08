/*!
 * @file main.c
 * @brief Step Down 8 Click example
 *
 * # Description
 * This library contains API for the Step Down 8 Click driver.
 * This driver provides the functions to set the output voltage treshold.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization, default settings sets output voltage to 3 V.
 *
 * ## Application Task
 * This example demonstrates the use of the Step Down 8 Click board™ by changing 
 * output voltage every 2 seconds starting from 3 V up to 18 V.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "stepdown8.h"

static stepdown8_t stepdown8;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepdown8_cfg_t stepdown8_cfg;  /**< Click config object. */

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
    stepdown8_cfg_setup( &stepdown8_cfg );
    STEPDOWN8_MAP_MIKROBUS( stepdown8_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepdown8_init( &stepdown8, &stepdown8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPDOWN8_ERROR == stepdown8_default_cfg ( &stepdown8 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    for ( uint8_t n_cnt = STEPDOWN8_MIN_OUTPUT; n_cnt <= STEPDOWN8_MAX_OUTPUT; n_cnt++ )
    {
        stepdown8_set_output( &stepdown8, ( float ) n_cnt );
        log_printf( &logger, " Output voltage %d V\r\n", ( uint16_t ) n_cnt );
        Delay_ms( 2000 );
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

// ------------------------------------------------------------------------ END
