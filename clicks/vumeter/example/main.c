/*!
 * @file main.c
 * @brief VUMeter Click example
 *
 * # Description
 * This example demonstrates the use of VU Meter click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and sets the gain level (the microphone sensitivity) to maximum.
 *
 * ## Application Task
 * Calculates VU level from the analog voltage read from AN pin, and displays the results
 * on the USB UART approximately every 100ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "vumeter.h"

static vumeter_t vumeter;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    vumeter_cfg_t vumeter_cfg;  /**< Click config object. */

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

    vumeter_cfg_setup( &vumeter_cfg );
    VUMETER_MAP_MIKROBUS( vumeter_cfg, MIKROBUS_1 );
    err_t init_flag  = vumeter_init( &vumeter, &vumeter_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    vumeter_set_gain_level ( &vumeter, VUMETER_GAIN_LEVEL_MAX );
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    log_printf( &logger, " VU level: %.3f VU\r\n", vumeter_calculate_vu_level ( &vumeter, 100 ) );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
