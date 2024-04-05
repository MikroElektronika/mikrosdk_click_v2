/*!
 * @file main.c
 * @brief Smart Buck 3 Click example
 *
 * # Description
 * This example demonstrates the use of Smart Buck 3 Click board™.
 * This driver provides functions for device configurations 
 * and for the sets and reads the output voltage.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After initializing the driver, the default configuration is executed 
 * and the device is turned on.
 *
 * ## Application Task
 * This example demonstrates the use of the Smart Buck 3 Click board™.
 * Changes the output voltage every 3 seconds 
 * and displays the current voltage output value.
 * Results are sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "smartbuck3.h"

static smartbuck3_t smartbuck3;
static log_t logger;
static uint16_t vout_mv;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartbuck3_cfg_t smartbuck3_cfg;  /**< Click config object. */

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
    smartbuck3_cfg_setup( &smartbuck3_cfg );
    SMARTBUCK3_MAP_MIKROBUS( smartbuck3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == smartbuck3_init( &smartbuck3, &smartbuck3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    if ( SMARTBUCK3_ERROR == smartbuck3_default_cfg ( &smartbuck3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
    vout_mv = SMARTBUCK3_VOUT_MIN;
}

void application_task ( void ) 
{
    if ( SMARTBUCK3_OK == smartbuck3_set_voltage( &smartbuck3, vout_mv ) )
    {
        Delay_ms ( 100 );
        if ( SMARTBUCK3_OK == smartbuck3_get_voltage( &smartbuck3, &vout_mv ) )
        {
            log_printf ( &logger, " Vout: %u mV\r\n", vout_mv );
        }
    }
    vout_mv += 100;
    if ( vout_mv > SMARTBUCK3_VOUT_MAX )
    {
        vout_mv = SMARTBUCK3_VOUT_MIN;
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
