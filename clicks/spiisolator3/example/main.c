/*!
 * @file main.c
 * @brief SpiIsolator3 Click example
 *
 * # Description
 * This library contains API for the SPI Isolator 3 click driver.
 * This demo application shows an example of an SPI Isolator 3 click wired 
 * to the nvSRAM 4 click for reading Device ID.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SPI module and log UART.
 * After driver initialization, the app sets the default configuration.
 *
 * ## Application Task
 * This is an example that shows the use of an SPI Isolator 3 click board™.
 * Logs Device ID of the nvSRAM 4 click wired to the SPI Isolator 3 board™.  
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @note
 * void get_device_id ( void ) - Get Device ID function. 
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "spiisolator3.h"

static spiisolator3_t spiisolator3;
static log_t logger;
static uint32_t device_id;

void get_device_id ( void ) {
    uint8_t rx_data[ 4 ];
    
    spiisolator3_generic_read( &spiisolator3, 0x9F, &rx_data[ 0 ], 4 );
    
    device_id = rx_data[ 0 ];
    device_id <<= 8;
    device_id |= rx_data[ 1 ];
    device_id <<= 8;
    device_id |= rx_data[ 2 ];
    device_id <<= 8;
    device_id |= rx_data[ 3 ];
}

void application_init ( void ) {
    log_cfg_t log_cfg;                    /**< Logger config object. */
    spiisolator3_cfg_t spiisolator3_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.

    spiisolator3_cfg_setup( &spiisolator3_cfg );
    SPIISOLATOR3_MAP_MIKROBUS( spiisolator3_cfg, MIKROBUS_1 );
    err_t init_flag  = spiisolator3_init( &spiisolator3, &spiisolator3_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    spiisolator3_default_cfg ( &spiisolator3 );
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

void application_task ( void ) {
    get_device_id( );
    log_printf( &logger, " Device ID : 0x%.8LX\r\n", device_id ); 
    Delay_ms( 1000 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
