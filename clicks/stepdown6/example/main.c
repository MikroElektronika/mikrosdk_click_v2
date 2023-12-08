/*!
 * @file main.c
 * @brief Step Down 6 Click example
 *
 * # Description
 * This library contains API for the Step Down 6 Click driver.
 * This driver provides the functions to set the output voltage threshold.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization, default settings sets output voltage to 550 mV.
 *
 * ## Application Task
 * This example demonstrates the use of the Step Down 6 Click board™ by changing 
 * output voltage every 5 seconds starting from 550 mV up to 1820 mV.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "stepdown6.h"

static stepdown6_t stepdown6;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepdown6_cfg_t stepdown6_cfg;  /**< Click config object. */

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
    stepdown6_cfg_setup( &stepdown6_cfg );
    STEPDOWN6_MAP_MIKROBUS( stepdown6_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepdown6_init( &stepdown6, &stepdown6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPDOWN6_ERROR == stepdown6_default_cfg ( &stepdown6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    err_t error_flag = STEPDOWN6_OK;
    for ( uint16_t n_cnt = STEPDOWN6_MIN_VOUT_VAL; n_cnt <= STEPDOWN6_MAX_VOUT_VAL; n_cnt += STEPDOWN6_INCREMENT_VOUT_VAL )
    {
        error_flag |= stepdown6_set_out_voltage( &stepdown6, STEPDOWN6_SELECT_VOUT1, n_cnt );
        error_flag |= stepdown6_set_out_voltage( &stepdown6, STEPDOWN6_SELECT_VOUT2, n_cnt );
        error_flag |= stepdown6_set_out_voltage( &stepdown6, STEPDOWN6_SELECT_VOUT3, n_cnt );
        error_flag |= stepdown6_set_out_voltage( &stepdown6, STEPDOWN6_SELECT_VOUT4, n_cnt );
        log_printf( &logger, "  Set voltage : %d mV \r\n", n_cnt );
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

// ------------------------------------------------------------------------ END
