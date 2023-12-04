/*!
 * @file main.c
 * @brief Smart Buck 2 Click example
 *
 * # Description
 * This library contains API for the Smart Buck 2 Click board™.
 * This driver provides functions for device configurations 
 * and for the sets and reads the output voltage.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization, the app executes a default configuration.
 *
 * ## Application Task
 * This example demonstrates the use of the Smart Buck 2 Click board™.
 * The demo application changes the output voltage in steps of 100mv every 3 seconds 
 * and displays the output voltage value.
 * Results are sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "smartbuck2.h"

#define DEMO_VOUT_STEP_100MV    100

static smartbuck2_t smartbuck2;
static log_t logger;
static uint16_t vout_mv = SMARTBUCK2_VOUT_MIN;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartbuck2_cfg_t smartbuck2_cfg;  /**< Click config object. */

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
    smartbuck2_cfg_setup( &smartbuck2_cfg );
    SMARTBUCK2_MAP_MIKROBUS( smartbuck2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == smartbuck2_init( &smartbuck2, &smartbuck2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SMARTBUCK2_ERROR == smartbuck2_default_cfg ( &smartbuck2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    if ( SMARTBUCK2_OK == smartbuck2_set_voltage( &smartbuck2, vout_mv ) )
    {
        Delay_ms( 100 );
        if ( SMARTBUCK2_OK == smartbuck2_get_voltage( &smartbuck2, &vout_mv ) )
        {
            log_printf( &logger, " Output voltage: %u [mV]\r\n", vout_mv );
        }
    }
    vout_mv += DEMO_VOUT_STEP_100MV;
    if ( vout_mv > SMARTBUCK2_VOUT_MAX )
    {
        vout_mv = SMARTBUCK2_VOUT_MIN;
    }
    Delay_ms( 3000 );
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
