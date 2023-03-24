/*!
 * @file main.c
 * @brief Buck 22 Click example
 *
 * # Description
 * This example demonstrates the use of Buck 22 click by changing the output voltage.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and sets the control settings.
 *
 * ## Application Task
 * Changes the output voltage every 3 seconds and displays on the USB UART
 * the currently set voltage output value. It also checks the power good pin indicator.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "buck22.h"

static buck22_t buck22;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buck22_cfg_t buck22_cfg;  /**< Click config object. */

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
    buck22_cfg_setup( &buck22_cfg );
    BUCK22_MAP_MIKROBUS( buck22_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == buck22_init( &buck22, &buck22_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BUCK22_ERROR == buck22_set_control ( &buck22, BUCK22_CONTROL_DEFAULT_SETTING ) )
    {
        log_error( &logger, " Set control." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( !buck22_get_pg_pin ( &buck22 ) )
    {
        log_info ( &logger, " Device is shut down. " );
        while ( !buck22_get_pg_pin ( &buck22 ) );
        log_info ( &logger, " Device is powered up. " );
    }
    static uint16_t vout_mv = BUCK22_VOUT_MIN;
    if ( BUCK22_OK == buck22_set_vout ( &buck22, vout_mv ) )
    {
        if ( BUCK22_OK == buck22_read_vout ( &buck22, &vout_mv ) )
        {
            log_printf ( &logger, " Vout: %u mV\r\n", vout_mv );
        }
    }
    vout_mv += 100;
    if ( vout_mv > BUCK22_VOUT_MAX )
    {
        vout_mv = BUCK22_VOUT_MIN;
    }
    Delay_ms ( 3000 );
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
