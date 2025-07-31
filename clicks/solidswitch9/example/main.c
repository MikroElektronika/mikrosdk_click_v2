/*!
 * @file main.c
 * @brief SolidSwitch 9 Click example
 *
 * # Description
 * This example demonstrates the use of the SolidSwitch 9 Click board by 
 * gradually increasing and decreasing the output duty cycle of each output channel one by one. 
 * After each update, the output is enabled and the diagnostic status is cleared.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and the Click board driver, and applies the default configuration.
 *
 * ## Application Task
 * Adjusts the output duty cycle from 0% to 100% and back to 0% for each channel sequentially 
 * and clears the diagnostic status after each duty cycle update. The currently active output
 * channel number is logged on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "solidswitch9.h"

static solidswitch9_t solidswitch9;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    solidswitch9_cfg_t solidswitch9_cfg;  /**< Click config object. */

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
    solidswitch9_cfg_setup( &solidswitch9_cfg );
    SOLIDSWITCH9_MAP_MIKROBUS( solidswitch9_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == solidswitch9_init( &solidswitch9, &solidswitch9_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SOLIDSWITCH9_ERROR == solidswitch9_default_cfg ( &solidswitch9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static uint8_t out_ch_old = SOLIDSWITCH9_OUT_MASK;
    static uint8_t out_ch = SOLIDSWITCH9_OUT1;
    static int16_t duty = SOLIDSWITCH9_OUT_DUTY_0_PCT;
    static int8_t duty_inc = 1;
    if ( out_ch_old != out_ch )
    {
        log_printf ( &logger, "\r\n Active channel: " );
        if ( SOLIDSWITCH9_OUT3 == out_ch )
        {
            log_printf ( &logger, "3\r\n" );
        }
        else
        {
            log_printf ( &logger, "%u\r\n", ( uint16_t ) ( out_ch >> 1 ) );
        }
        out_ch_old = out_ch;
    }
    solidswitch9_set_out_duty ( &solidswitch9, out_ch, duty );
    solidswitch9_enable_out ( &solidswitch9, out_ch );
    solidswitch9_clear_all_status ( &solidswitch9 );
    duty += duty_inc;
    if ( ( duty > SOLIDSWITCH9_OUT_DUTY_100_PCT ) || ( duty < SOLIDSWITCH9_OUT_DUTY_0_PCT ) )
    {
        if ( duty < SOLIDSWITCH9_OUT_DUTY_0_PCT )
        {
            out_ch <<= 1;
            if ( out_ch > SOLIDSWITCH9_OUT3 )
            {
                out_ch = SOLIDSWITCH9_OUT0;
            }
        }
        duty_inc *= -1;
        duty += duty_inc;
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
