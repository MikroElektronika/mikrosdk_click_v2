/*!
 * @file main.c
 * @brief SPIIsolator4 Click example
 *
 * # Description
 * This library contains API for the SPI Isolator 4 Click driver.
 * This demo application shows an example of an SPI Isolator 4 Click wired 
 * to the nvSRAM 4 Click for reading Device ID.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SPI module and log UART.
 * After driver initialization, the app sets the default configuration.
 *
 * ## Application Task
 * This is an example that shows the use of an SPI Isolator 4 Click board™.
 * Logs Device ID of the nvSRAM 4 Click wired to the SPI Isolator 4 board™.  
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * ## Additional Function
 * - static void get_device_id ( void )
 *
 * @author Mikroe Team
 *
 */

#include "board.h"
#include "log.h"
#include "spiisolator4.h"

static spiisolator4_t spiisolator4;
static log_t logger;
static uint32_t device_id;

static void get_device_id ( void ) {
    uint8_t rx_data[ 4 ];
    
    spiisolator4_generic_read( &spiisolator4, 0x9F, &rx_data[ 0 ], 4 );
    
    device_id = rx_data[ 0 ];
    device_id <<= 8;
    device_id |= rx_data[ 1 ];
    device_id <<= 8;
    device_id |= rx_data[ 2 ];
    device_id <<= 8;
    device_id |= rx_data[ 3 ];
}

void application_init ( void )
{
    log_cfg_t log_cfg;                    /**< Logger config object. */
    spiisolator4_cfg_t spiisolator4_cfg;  /**< Click config object. */

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

    spiisolator4_cfg_setup( &spiisolator4_cfg );
    SPIISOLATOR4_MAP_MIKROBUS( spiisolator4_cfg, MIKROBUS_1 );
    err_t init_flag  = spiisolator4_init( &spiisolator4, &spiisolator4_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    spiisolator4_default_cfg ( &spiisolator4 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------------\r\n" ); 
    Delay_ms ( 100 );
}

void application_task ( void )
{
    get_device_id( );
    log_printf( &logger, "  Device ID : 0x%.8LX\r\n", device_id ); 
    log_printf( &logger, "--------------------------\r\n" ); 
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
