/*!
 * @file main.c
 * @brief Ambient 20 Click example
 *
 * # Description
 * This example demonstrates the use of Ambient 20 click board by measuring 
 * the ambient light level.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Measuring ambient light level by reading DATA0 and DATA1 channels of the Ambient 20 click board
 * and displaying it using UART Serial terminal.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "ambient20.h"

static ambient20_t ambient20;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient20_cfg_t ambient20_cfg;  /**< Click config object. */

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
    ambient20_cfg_setup( &ambient20_cfg );
    AMBIENT20_MAP_MIKROBUS( ambient20_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient20_init( &ambient20, &ambient20_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMBIENT20_ERROR == ambient20_default_cfg ( &ambient20 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint8_t id;
    ambient20_get_manufacturer_id( &ambient20, &id );
    
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " Part ID = 0x%.2X \r\n", ( uint16_t ) id );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );

    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
}

void application_task ( void ) 
{
    //  Task implementation.
    float data0, data1;
    ambient20_get_data_lux( &ambient20, &data0, &data1 );
    
    log_printf( &logger, "Data 0: %.2f lx \r\n", data0 );
    log_printf( &logger, "Data 1: %.2f lx \r\n", data1 );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    
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
