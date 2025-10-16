/*!
 * @file main.c
 * @brief Smart Buck 8 Click example
 *
 * # Description
 * This example demonstrates the use of the Smart Buck 8 Click board. The application cyclically adjusts 
 * the output voltage between its minimum and maximum values in steps and monitors the PG (Power Good) pin 
 * for any fault conditions. It logs any detected faults including undervoltage lockout, thermal warning, 
 * or hiccup event status.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the Smart Buck 8 Click driver, and applies the default configuration.
 *
 * ## Application Task
 * Cycles the output voltage up and down between the minimum and maximum supported values. 
 * Checks for fault conditions via the PG pin and logs detailed status flags if any fault is detected.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "smartbuck8.h"

static smartbuck8_t smartbuck8;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartbuck8_cfg_t smartbuck8_cfg;  /**< Click config object. */

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
    smartbuck8_cfg_setup( &smartbuck8_cfg );
    SMARTBUCK8_MAP_MIKROBUS( smartbuck8_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == smartbuck8_init( &smartbuck8, &smartbuck8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SMARTBUCK8_ERROR == smartbuck8_default_cfg ( &smartbuck8 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint16_t vout = SMARTBUCK8_VOUT_MV_MIN;
    static int16_t vout_step = 50;
    static uint8_t status = 0;
    if ( !smartbuck8_get_pg_pin ( &smartbuck8 ) )
    {
        log_printf( &logger, "\r\n Fault indication detected via PG pin!\r\n" );
        if ( SMARTBUCK8_OK == smartbuck8_read_status ( &smartbuck8, &status ) )
        {
            if ( status & SMARTBUCK8_STATUS_THERMAL_WARNING )
            {
                log_printf ( &logger, " Junction temperature is higher than 130C\r\n" );
            }
            if ( status & SMARTBUCK8_STATUS_HICCUP )
            {
                log_printf ( &logger, " Device has HICCUP status once\r\n" );
            }
            if ( status & SMARTBUCK8_STATUS_UVLO )
            {
                log_printf ( &logger, " The input voltage is less than UVLO threshold (falling edge)\r\n" );
            }
        }
    }
    if ( SMARTBUCK8_OK == smartbuck8_set_vout ( &smartbuck8, vout ) )
    {
        log_printf ( &logger, "\r\n VOUT: %u mV\r\n", vout );
        vout += vout_step;
        if ( ( vout > SMARTBUCK8_VOUT_MV_MAX ) || ( vout < SMARTBUCK8_VOUT_MV_MIN ) )
        {
            vout_step = -vout_step;
            vout += vout_step;
            vout += vout_step;
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
