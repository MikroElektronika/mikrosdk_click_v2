/*!
 * @file main.c
 * @brief Accel17 Click example
 *
 * # Description
 * This example showcases ability of the device to read
 * x, y axis orientation.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of communication modules(I2C, UART), and
 * configures device.
 *
 * ## Application Task
 * Reads axis data and calculates it and logs result every 300ms.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "accel17.h"

static accel17_t accel17;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel17_cfg_t accel17_cfg;  /**< Click config object. */

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
    accel17_cfg_setup( &accel17_cfg );
    ACCEL17_MAP_MIKROBUS( accel17_cfg, MIKROBUS_1 );
    err_t init_flag = accel17_init( &accel17, &accel17_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    accel17_default_cfg ( &accel17 );
    Delay_ms ( 1000 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    accel17_axes_t axes;
    accel17_get_axes_data ( &accel17, &axes );
    log_printf( &logger, " > X[degree]: %.2f\r\n > Y[degree]: %.2f\r\n", axes.x, axes.y );
    log_printf( &logger, "*********************************\r\n" );
    Delay_ms ( 300 );
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
