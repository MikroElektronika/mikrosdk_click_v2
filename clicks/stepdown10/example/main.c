/*!
 * @file main.c
 * @brief Step Down 10 Click example
 *
 * # Description
 * This library contains API for the Step Down 10 Click driver.
 * This driver provides the functions to set the output voltage treshold.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization, default settings sets output voltage to 2 V.
 *
 * ## Application Task
 * This example demonstrates the use of the Step Down 10 Click board™ by changing 
 * output voltage every 2 seconds starting from 2 V up to 20 V.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "stepdown10.h"

static stepdown10_t stepdown10;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepdown10_cfg_t stepdown10_cfg;  /**< Click config object. */

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
    stepdown10_cfg_setup( &stepdown10_cfg );
    STEPDOWN10_MAP_MIKROBUS( stepdown10_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepdown10_init( &stepdown10, &stepdown10_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPDOWN10_ERROR == stepdown10_default_cfg ( &stepdown10 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    for ( uint8_t n_cnt = STEPDOWN10_MIN_OUTPUT; n_cnt <= STEPDOWN10_MAX_OUTPUT; n_cnt++ )
    {
        stepdown10_set_output( &stepdown10, ( float ) n_cnt );
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
