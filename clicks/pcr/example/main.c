/*!
 * @file main.c
 * @brief PCR Click example
 *
 * # Description
 * This example demonstrates the use of PCR click board by 
 * reading distance between click board and object. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger and performs the click default configuration.
 *
 * ## Application Task
 * Reading distance between click board and object every 2 seconds and logging it on UART terminal.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "pcr.h"

static pcr_t pcr;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pcr_cfg_t pcr_cfg;  /**< Click config object. */

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
    pcr_cfg_setup( &pcr_cfg );
    PCR_MAP_MIKROBUS( pcr_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == pcr_init( &pcr, &pcr_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PCR_ERROR == pcr_default_cfg ( &pcr ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint32_t distance_data = 0;

    pcr_get_distance ( &pcr, &distance_data );
    log_printf( &logger, " Distance: %lu mm \r\n", distance_data );
    Delay_ms( 2000 );

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
