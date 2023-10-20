/*!
 * @file main.c
 * @brief DIGI Isolator Click example
 *
 * # Description
 * This example demonstrates the use of the DIGI Isolator click board 
 * by reading and writing data by using SPI and UART serial interface 
 * and reading results of AD conversion.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SPI, UART and ADC module and log UART.
 *
 * ## Application Task
 * At the start, the demo application reads and checks the manufacturer ID and 
 * device ID of the connected Flash 11 click board by using SPI serial interface. 
 * After that, sends a "MikroE" message, reads the received data, 
 * and parses it by using UART serial interface in loopback mode. 
 * And finally, the demo app reads the results of the AD conversion of the D1 (AN) pin. 
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "digiisolator.h"

#define FLASH11_CMD_GET_ID         0x90, 0x00, 0x00, 0x00, 0x00, 0x00
#define FLASH11_MANUFACTURER_ID    0x1F
#define FLASH11_DEVICE_ID          0x15
#define DEMO_MESSAGE               "\r\nMikroE\r\n"
#define PROCESS_BUFFER_SIZE        200

static digiisolator_t digiisolator;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digiisolator_cfg_t digiisolator_cfg;  /**< Click config object. */

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
    digiisolator_cfg_setup( &digiisolator_cfg );
    DIGIISOLATOR_MAP_MIKROBUS( digiisolator_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == digiisolator_init( &digiisolator, &digiisolator_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " -----------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    static uint8_t cmd_get_id[ 6 ] = { FLASH11_CMD_GET_ID };
    static uint8_t read_id[ 6 ] = { 0 };
    static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    static float voltage = 0;
    
    if ( DIGIISOLATOR_OK == digiisolator_spi_transfer( &digiisolator, &cmd_get_id[ 0 ], &read_id[ 0 ], 6 ) )
    {
        if ( ( FLASH11_MANUFACTURER_ID == read_id[ 4 ] ) && ( FLASH11_DEVICE_ID == read_id[ 5 ] ) )
        {
            log_printf( &logger, " SPI\r\n" );
            log_printf( &logger, " Manufacturer ID: 0x%.2X\r\n", ( uint16_t ) read_id[ 4 ] );
            log_printf( &logger, " Device ID: 0x%.2X    \r\n", ( uint16_t ) read_id[ 5 ] );
            log_printf( &logger, " -----------------------\r\n" );
            Delay_ms( 2000 );
        }
    }
    
    if ( 0 < digiisolator_uart_write( &digiisolator, DEMO_MESSAGE, strlen( DEMO_MESSAGE ) ) )
    {
        if ( 0 < digiisolator_uart_read( &digiisolator, app_buf, strlen( DEMO_MESSAGE ) ) )
        {
            log_printf( &logger, " UART\r\n" );
            log_printf( &logger, "%s", app_buf );
            memset( app_buf, 0, PROCESS_BUFFER_SIZE );
            log_printf( &logger, " -----------------------\r\n" );
            Delay_ms( 2000 );
        }
    }
    
    if ( DIGIISOLATOR_OK == digiisolator_get_d1_pin_voltage ( &digiisolator, &voltage ) ) 
    {
        log_printf( &logger, " ADC\r\n" );
        log_printf( &logger, " Voltage : %.3f[V]\r\n", voltage );
        log_printf( &logger, " -----------------------\r\n" );
        Delay_ms( 2000 );
    }
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
