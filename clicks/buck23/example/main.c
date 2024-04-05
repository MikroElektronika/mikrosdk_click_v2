/*!
 * @file main.c
 * @brief Buck 23 Click example
 *
 * # Description
 * This example demonstrates the use of Buck 23 click by changing the output voltage.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the device default configuration.
 *
 * ## Application Task
 * Changes the output voltage once per second and displays on the USB UART the currently set
 * voltage output value as well as its range and resolution. It also checks and displays the status
 * register content and the power good pin indication.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "buck23.h"

static buck23_t buck23;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buck23_cfg_t buck23_cfg;  /**< Click config object. */

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
    buck23_cfg_setup( &buck23_cfg );
    BUCK23_MAP_MIKROBUS( buck23_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == buck23_init( &buck23, &buck23_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BUCK23_ERROR == buck23_default_cfg ( &buck23 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint16_t vout_mv;
    uint8_t status;
    if ( BUCK23_OK == buck23_set_vstep ( &buck23, BUCK23_VSTEP_10 ) )
    {
        log_printf ( &logger, " ------------------------------------\r\n" );
        log_printf ( &logger, " VOUT resolution: 10mV\r\n VOUT range: 500mV to 1270mV\r\n" );
        log_printf ( &logger, " ------------------------------------" );
    }
    for ( vout_mv = BUCK23_VOUT_MIN_VSTEP_10; vout_mv <= BUCK23_VOUT_MAX_VSTEP_10; vout_mv += 50 )
    {
        if ( BUCK23_OK == buck23_read_register ( &buck23, BUCK23_REG_STATUS, &status ) )
        {
            log_printf ( &logger, "\r\n STATUS: 0x%.2X\r\n", ( uint16_t ) status );
        }
        if ( BUCK23_OK == buck23_set_vout ( &buck23, vout_mv ) )
        {
            log_printf ( &logger, " VOUT: %u mV\r\n", vout_mv );
        }
        if ( !buck23_get_pg_pin ( &buck23 ) )
        {
            log_printf ( &logger, " ERROR: No power good\r\n" );
            log_printf ( &logger, " Restarting device\r\n" );
            buck23_restart_device ( &buck23 );
            vout_mv -= 50;
        }
        Delay_ms ( 1000 );
    }
    if ( BUCK23_OK == buck23_set_vstep ( &buck23, BUCK23_VSTEP_12_5 ) )
    {
        log_printf ( &logger, " ------------------------------------\r\n" );
        log_printf ( &logger, " VOUT resolution: 12.5mV\r\n VOUT range: 625mV to 1587.5mV\r\n" );
        log_printf ( &logger, " ------------------------------------" );
    }
    for ( vout_mv = BUCK23_VOUT_MIN_VSTEP_12_5; vout_mv <= BUCK23_VOUT_MAX_VSTEP_12_5; vout_mv += 50 )
    {
        if ( BUCK23_OK == buck23_read_register ( &buck23, BUCK23_REG_STATUS, &status ) )
        {
            log_printf ( &logger, "\r\n STATUS: 0x%.2X\r\n", ( uint16_t ) status );
        }
        if ( BUCK23_OK == buck23_set_vout ( &buck23, vout_mv ) )
        {
            log_printf ( &logger, " VOUT: %u mV\r\n", vout_mv );
        }
        if ( !buck23_get_pg_pin ( &buck23 ) )
        {
            log_printf ( &logger, " ERROR: No power good\r\n" );
            log_printf ( &logger, " Restarting device\r\n" );
            buck23_restart_device ( &buck23 );
            vout_mv -= 50;
        }
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
