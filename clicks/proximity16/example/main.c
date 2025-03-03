/*!
 * @file main.c
 * @brief Proximity 16 Click example
 *
 * # Description
 * This example demonstrates the use of Proximity 16 Click board by reading and displaying
 * 8x8 zones measurements on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads all zone measurements approximately every 500ms and logs them to the USB UART as an 8x8 map. 
 * The silicon temperature measurement in degrees Celsius is also displayed.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "proximity16.h"

static proximity16_t proximity16;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity16_cfg_t proximity16_cfg;  /**< Click config object. */

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
    proximity16_cfg_setup( &proximity16_cfg );
    PROXIMITY16_MAP_MIKROBUS( proximity16_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proximity16_init( &proximity16, &proximity16_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY16_ERROR == proximity16_default_cfg ( &proximity16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( !proximity16_get_int_pin ( &proximity16 ) )
    {
        proximity16_results_data_t results;
        uint8_t resolution, map_side;
        err_t error_flag = proximity16_get_resolution ( &proximity16, &resolution );
        error_flag |= proximity16_get_ranging_data ( &proximity16, &results );
        if ( PROXIMITY16_OK == error_flag )
        {
            map_side = ( PROXIMITY16_RESOLUTION_4X4 == resolution ) ? 4 : 8;
            log_printf ( &logger, "\r\n %ux%u MAP (mm):\r\n", ( uint16_t ) map_side, ( uint16_t ) map_side );
            for ( uint16_t cnt = 1; cnt <= resolution; cnt++ )
            {
                log_printf ( &logger, " %u\t", results.distance_mm[ cnt - 1 ] );
                if ( 0 == ( cnt % map_side ) )
                {
                    log_printf ( &logger, "\r\n" );
                }
            }
            log_printf ( &logger, " Silicon temperature : %d degC\r\n", ( int16_t ) results.silicon_temp_degc );
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
