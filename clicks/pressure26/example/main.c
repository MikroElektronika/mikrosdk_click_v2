/*!
 * @file main.c
 * @brief Pressure 26 Click example
 *
 * # Description
 * This example demonstrates the use of the Pressure 26 Click board for
 * measuring pressure and temperature data. The application reads sensor
 * values via the SPI interface and displays the measured results on
 * the serial terminal.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and Pressure 26 Click driver and verifies
 * the device identifier.
 *
 * ## Application Task
 * Periodically reads pressure and temperature values from the sensor and
 * logs the results to the serial terminal.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "pressure26.h"

#ifndef MIKROBUS_POSITION_PRESSURE26
    #define MIKROBUS_POSITION_PRESSURE26 MIKROBUS_1
#endif

static pressure26_t pressure26;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure26_cfg_t pressure26_cfg;  /**< Click config object. */

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
    pressure26_cfg_setup( &pressure26_cfg );
    PRESSURE26_MAP_MIKROBUS( pressure26_cfg, MIKROBUS_POSITION_PRESSURE26 );
    if ( SPI_MASTER_ERROR == pressure26_init( &pressure26, &pressure26_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
      
    uint16_t identifier = 0;
    if ( PRESSURE26_OK == pressure26_get_identifier( &pressure26, &identifier ) )
    {   
        /* Response structure: [SUPPLIER(2)] [SILICON_VER(3)] [METAL_VER(3)] [spi_id(8)] */
        uint8_t supplier        = ( uint8_t ) ( ( identifier >> 14 ) & PRESSURE26_IDENTIFIER_SUPPLIER_MASK );
        uint8_t silicon_version = ( uint8_t ) ( ( identifier >> 11 ) & PRESSURE26_IDENTIFIER_SILICON_VERSION_MASK );
        uint8_t metal_version   = ( uint8_t ) ( ( identifier >> 8  ) & PRESSURE26_IDENTIFIER_METAL_VERSION_MASK );
        uint8_t spi_id          = ( uint8_t ) ( identifier & PRESSURE26_IDENTIFIER_SPI_ID_MASK );

        log_printf( &logger, " --- Identifier Response ---\r\n" );
        log_printf( &logger, " Supplier:        0x%.2X\r\n", ( uint16_t ) supplier );
        log_printf( &logger, " Silicon version: 0x%.1X\r\n", ( uint16_t ) silicon_version );
        log_printf( &logger, " Metal version:   0x%.1X\r\n", ( uint16_t ) metal_version );
        log_printf( &logger, " SPI ID:          0x%.2X\r\n", ( uint16_t ) spi_id );
        log_printf( &logger, " ---------------------------\r\n" );
    }

    if ( PRESSURE26_IDENTIFIER_SPI_ID != ( identifier & PRESSURE26_IDENTIFIER_SPI_ID_MASK ) )
    {
        log_error( &logger, " SPI ID read fail." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float pressure = 0;
    float temperature = 0;

    if ( PRESSURE26_OK == pressure26_get_pressure( &pressure26, &pressure ) )
    {
        log_printf( &logger, " Pressure: %.1f mBar\r\n", pressure );
    }
    if ( PRESSURE26_OK == pressure26_get_temperature( &pressure26, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.1f degC\r\n\n", temperature );
    }

    Delay_ms( 1000 );
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
