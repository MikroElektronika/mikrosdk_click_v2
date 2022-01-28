/*!
 * @file main.c
 * @brief Barometer6 Click example
 *
 * # Description
 * This is an example that demonstrates the use of the Barometer 6 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initalizes SPI or I2C driver, applies default settings and reads Chip ID.
 *
 * ## Application Task
 * Demonstrates use of Barometer 6 click board by reading pressure and temperature data seconds 
 * and logging it on the UART terminal.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "barometer6.h"

static barometer6_t barometer6;
static log_t logger;
static uint8_t dev_id;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    barometer6_cfg_t barometer6_cfg;  /**< Click config object. */

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
    barometer6_cfg_setup( &barometer6_cfg );
    BAROMETER6_MAP_MIKROBUS( barometer6_cfg, MIKROBUS_1 );
    err_t init_flag  = barometer6_init( &barometer6, &barometer6_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    barometer6_default_cfg ( &barometer6 );
    
    barometer6_read_id( &barometer6, &dev_id );
    if ( BAROMETER6_ID_VALUE != dev_id )
    {
        log_printf( &logger, " Device communication Error " );
        for ( ; ; );
    }
    
    log_printf( &logger, "- - - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " Device ID : 0x%.2X \r\n", ( uint16_t ) dev_id );
    log_printf( &logger, "- - - - - - - - - - - - - - -\r\n" );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float pressure;
    float temperature;
    
    barometer6_read_temperature_value( &barometer6, &temperature );
    barometer6_read_preassure_value( &barometer6, &pressure );
        
    log_printf( &logger, " Temperature : %.2f C    \r\n", temperature );
    log_printf( &logger, " Pressure    : %.2f mBar \r\n", pressure );
    log_printf( &logger, "- - - - - - - - - - - - - - -\r\n" );
    
    Delay_ms( 1000 );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
