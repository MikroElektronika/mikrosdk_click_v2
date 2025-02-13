/*!
 * @file main.c
 * @brief LightRanger 12 Click example
 *
 * # Description
 * This example demonstrates the use of LightRanger 12 Click board by reading and displaying
 * 8x8 zones measurements on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads all zone measurements approximately every 200ms and logs them to the USB UART as an 8x8 map. 
 * The silicon temperature measurement in degrees Celsius is also displayed.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "lightranger12.h"

static lightranger12_t lightranger12;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lightranger12_cfg_t lightranger12_cfg;  /**< Click config object. */

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
    lightranger12_cfg_setup( &lightranger12_cfg );
    LIGHTRANGER12_MAP_MIKROBUS( lightranger12_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == lightranger12_init( &lightranger12, &lightranger12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LIGHTRANGER12_ERROR == lightranger12_default_cfg ( &lightranger12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    err_t error_flag = LIGHTRANGER12_OK;
    lightranger12_results_data_t results;
    uint8_t resolution = 0;
    uint8_t map_side = 0;

    // Wait for a data ready interrupt
    while ( lightranger12_get_int_pin ( &lightranger12 ) );

    error_flag |= lightranger12_get_resolution ( &lightranger12, &resolution );
    error_flag |= lightranger12_get_ranging_data ( &lightranger12, &results );
    if ( LIGHTRANGER12_OK == error_flag )
    {
        map_side = ( LIGHTRANGER12_RESOLUTION_4X4 == resolution ) ? 4 : 8;
        log_printf ( &logger, "----------------------- %ux%u MAP (mm) -----------------------\r\n", 
                    ( uint16_t ) map_side, ( uint16_t ) map_side );
        for ( uint8_t cnt_0 = 1; cnt_0 <= map_side; cnt_0++ )
        {
            for ( uint8_t cnt_1 = 1; cnt_1 <= map_side; cnt_1++ )
            {
                // Checking the zone measurement validity (5 & 9 means ranging OK)
                if ( ( 5 == results.target_status[ cnt_0 * map_side - cnt_1 ] ) ||
                     ( 9 == results.target_status[ cnt_0 * map_side - cnt_1 ] ) )
                {
                    log_printf ( &logger, "%d\t", results.distance_mm[ cnt_0 * map_side - cnt_1 ] );
                }
                else
                {
                    log_printf ( &logger, "NOK\t" );
                }
            }
            log_printf ( &logger, "\r\n" );
            Delay_ms ( 5 );
        }
        log_printf ( &logger, "Silicon temperature : %d degC\r\n", ( int16_t ) results.silicon_temp_degc );
        log_printf ( &logger, "------------------------------------------------------------\r\n\n" );
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
