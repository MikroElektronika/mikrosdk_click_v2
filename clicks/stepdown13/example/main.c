/*!
 * @file main.c
 * @brief Step Down 13 Click example
 *
 * # Description
 * This example demonstrates how to initialize the Step Down 13 Click board
 * and how to control its output voltage by adjusting the potentiometer value over I2C.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and Step Down 13 Click driver and enables the device
 * in COT mode.
 *
 * ## Application Task
 * Gradually increases and decreases the output voltage across the supported range
 * and logs the current VOUT value. The VIN must always be higher than the VOUT set.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "stepdown13.h"

static stepdown13_t stepdown13;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepdown13_cfg_t stepdown13_cfg;  /**< Click config object. */

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
    stepdown13_cfg_setup( &stepdown13_cfg );
    STEPDOWN13_MAP_MIKROBUS( stepdown13_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepdown13_init( &stepdown13, &stepdown13_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    stepdown13_set_cot_mode ( &stepdown13 );
    stepdown13_enable_output ( &stepdown13 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static float vout = STEPDOWN13_VOUT_MIN;
    static float step = ( STEPDOWN13_VOUT_MAX - STEPDOWN13_VOUT_MIN ) / 20;

    if ( STEPDOWN13_OK == stepdown13_set_vout ( &stepdown13, vout ) )
    {
        log_printf( &logger, " VOUT: %.2f V\r\n\n", vout );
        vout += step;
        if ( ( vout > ( STEPDOWN13_VOUT_MAX + STEPDOWN13_FLOAT_COMPARE_OFFSET ) ) || 
             ( vout < ( STEPDOWN13_VOUT_MIN - STEPDOWN13_FLOAT_COMPARE_OFFSET ) ) )
        {
            step = -step;
            vout += step;
        }
    }

    Delay_ms ( 1000 );
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
