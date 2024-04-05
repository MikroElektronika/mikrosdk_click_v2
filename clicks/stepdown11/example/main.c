/*!
 * @file main.c
 * @brief Step Down 11 Click example
 *
 * # Description
 * This library contains API for the Step Down 11 Click driver.
 * This driver provides the functions to set the output voltage treshold.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization, default settings sets output voltage to 1 V.
 *
 * ## Application Task
 * This example demonstrates the use of the Step Down 11 Click board™ by changing 
 * output voltage every 5 seconds starting from 1 V up to 5 V.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "stepdown11.h"

static stepdown11_t stepdown11;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepdown11_cfg_t stepdown11_cfg;  /**< Click config object. */

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
    stepdown11_cfg_setup( &stepdown11_cfg );
    STEPDOWN11_MAP_MIKROBUS( stepdown11_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepdown11_init( &stepdown11, &stepdown11_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPDOWN11_ERROR == stepdown11_default_cfg ( &stepdown11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    for ( uint8_t vout = 1; vout <= 5; vout++ )
    {
        log_printf( &logger, " Set output voltage %dV \r\n", ( uint16_t ) vout );
        stepdown11_set_voltage ( &stepdown11, vout );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
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
