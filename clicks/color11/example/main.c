/*!
 * @file main.c
 * @brief Color 11 Click example
 *
 * # Description
 * This library contains API for the Color 11 Click driver.
 * The demo application sets sensor configuration 
 * and reads and displays ALS data measurement results.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After the driver init, the app executes a default configuration.
 *
 * ## Application Task
 * This example demonstrates the use of the Color 11 Click board™.
 * Reads and displays the results of the ALS data measurements.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "color11.h"

static color11_t color11;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    color11_cfg_t color11_cfg;  /**< Click config object. */

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
    color11_cfg_setup( &color11_cfg );
    COLOR11_MAP_MIKROBUS( color11_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == color11_init( &color11, &color11_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COLOR11_ERROR == color11_default_cfg ( &color11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ------------------\r\n" );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{   
    uint8_t status = 0;
    if ( COLOR11_OK == color11_get_data_valid_status( &color11, &status ) )
    {
        color11_als_data_t color_data;
        if ( COLOR11_OK == color11_get_als_data( &color11, &color_data ) && ( COLOR11_STATUS2_AVALID & status ) )
        {
            log_printf( &logger, " Clear: %u\r\n", color_data.clear );
            log_printf( &logger, " Red : %u\r\n", color_data.red );
            log_printf( &logger, " Green : %u\r\n", color_data.green );
            log_printf( &logger, " Blue : %u\r\n", color_data.blue );
            log_printf( &logger, " Wideband : %u\r\n", color_data.wideband );
            log_printf( &logger, " Flicker : %u\r\n", color_data.flicker );
            log_printf( &logger, " ------------------\r\n" );
            Delay_ms ( 1000 );
        }
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
