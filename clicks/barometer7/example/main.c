/*!
 * @file main.c
 * @brief Barometer7 Click example
 *
 * # Description
 * This library contains API for Barometer 7 Click driver.
 * The demo application reads and calculate temperature and pressure data.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes SPI driver and log UART.
 * After driver initialization the app set default settings 
 * and display sensor identifier data.
 *
 * ## Application Task
 * This is an example that demonstrates the use of the Barometer 7 Click board™.
 * In this example, display the Pressure ( mBar ) and Temperature ( degree Celsius ) data.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * ## Additional Function
 * - static void display_error ( void )
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "barometer7.h"

static barometer7_t barometer7;
static log_t logger;

static void display_error ( void ) 
{
    if ( BAROMETER7_EEPROM_FEC_ERROR == barometer7.diagnosis )
    {
        log_printf( &logger, " EEPROM: FEC error\r\n" );    
    }
    
    if ( BAROMETER7_ACQUISITION_CHAIN_FAILURE == barometer7.diagnosis )
    {
        log_printf( &logger, " Acquisition chain failure: Diag1\r\n" );    
    }
    
    if ( BAROMETER7_SENSOR_CELL_FAILURE == barometer7.diagnosis )
    {
        log_printf( &logger, " Sensor cell failure: Diag2\r\n" );    
    }
    
    if ( BAROMETER7_PRESSURE_OUT_OF_RANGE_HIGH == barometer7.diagnosis )
    {
        log_printf( &logger, " Pressure out of range: High\r\n" );    
    }
    
    if ( BAROMETER7_PRESSURE_OUT_OF_RANGE_LOW == barometer7.diagnosis )
    {
        log_printf( &logger, " Pressure out of range: Low\r\n" );    
    }
}

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    barometer7_cfg_t barometer7_cfg;  /**< Click config object. */

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
    barometer7_cfg_setup( &barometer7_cfg );
    BAROMETER7_MAP_MIKROBUS( barometer7_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == barometer7_init( &barometer7, &barometer7_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    BAROMETER7_SET_DATA_SAMPLE_EDGE;
    
    if ( BAROMETER7_ERROR == barometer7_default_cfg ( &barometer7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );;
    
    static barometer7_identifier_t id_data;
    barometer7_get_identifier ( &barometer7, &id_data );
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " > Supplier         : %d <\r\n", ( uint16_t ) id_data.supplier );
    log_printf( &logger, " > Silicon Version  : %d <\r\n", ( uint16_t ) id_data.silicon_version );
    log_printf( &logger, " > Metal Version    : %d <\r\n", ( uint16_t ) id_data.metal_version );
    log_printf( &logger, " > ASCI Name        : %c <\r\n", id_data.asic_name );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 1000 );
}

void application_task ( void )
{
    static float pressure; 
    static float temperature;
    
    barometer7_get_pressure( &barometer7, &pressure );
    if ( BAROMETER7_NO_ERROR != barometer7.diagnosis )
    {
        display_error( );
    }
    log_printf( &logger, " Pressure     : %.0f mbar\r\n", pressure );
    
    barometer7_get_temperature( &barometer7, &temperature );
    if ( BAROMETER7_NO_ERROR != barometer7.diagnosis )
    {
        display_error( );   
    }
    log_printf( &logger, " Temperature  : %.2f C\r\n", temperature );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 2000 );
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
