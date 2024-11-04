/*!
 * @file main.c
 * @brief Step Down 3 Click Example.
 *
 * # Description
 * This example demonstrates the use of Step Down 3 Click board by
 * iterating through the entire output voltage range.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger, then enables the Click board and disables
 * the auxiliary output.
 *
 * ## Application Task
 * Changes the output voltage every 3 seconds and displays the set voltage output value
 * on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "stepdown3.h"

static stepdown3_t stepdown3;   /**< Step Down 3 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepdown3_cfg_t stepdown3_cfg;  /**< Click config object. */

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
    stepdown3_cfg_setup( &stepdown3_cfg );
    STEPDOWN3_MAP_MIKROBUS( stepdown3_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == stepdown3_init( &stepdown3, &stepdown3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    stepdown3_enable_device ( &stepdown3 );
    stepdown3_disable_aux_output ( &stepdown3 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t vout = STEPDOWN3_OUT_VOLTAGE_1V6;
    stepdown3_set_output_voltage ( &stepdown3, vout );
    switch ( vout )
    {
        case STEPDOWN3_OUT_VOLTAGE_1V6:
        {
            log_printf( &logger, " Output voltage: 1.6 V\r\n\n" );
            break;
        }
        case STEPDOWN3_OUT_VOLTAGE_1V8:
        {
            log_printf( &logger, " Output voltage: 1.8 V\r\n\n" );
            break;
        }
        case STEPDOWN3_OUT_VOLTAGE_2V1:
        {
            log_printf( &logger, " Output voltage: 2.1 V\r\n\n" );
            break;
        }
        case STEPDOWN3_OUT_VOLTAGE_2V5:
        {
            log_printf( &logger, " Output voltage: 2.5 V\r\n\n" );
            break;
        }
        case STEPDOWN3_OUT_VOLTAGE_2V7:
        {
            log_printf( &logger, " Output voltage: 2.7 V\r\n\n" );
            break;
        }
        case STEPDOWN3_OUT_VOLTAGE_2V8:
        {
            log_printf( &logger, " Output voltage: 2.8 V\r\n\n" );
            break;
        }
        case STEPDOWN3_OUT_VOLTAGE_3V0:
        {
            log_printf( &logger, " Output voltage: 3.0 V\r\n\n" );
            break;
        }
        case STEPDOWN3_OUT_VOLTAGE_3V3:
        {
            log_printf( &logger, " Output voltage: 3.3 V\r\n\n" );
            break;
        }
    }
    if ( ++vout > STEPDOWN3_OUT_VOLTAGE_3V3 )
    {
        vout = STEPDOWN3_OUT_VOLTAGE_1V6;
    }
    Delay_ms ( 1000 );
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
