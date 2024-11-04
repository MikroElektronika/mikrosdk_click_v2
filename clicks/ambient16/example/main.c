/*!
 * @file main.c
 * @brief Ambient16 Click example
 *
 * # Description
 * This is an example that demonstrates the use of the Ambient 16 Click board 
 * by measuring illuminance and displaying the value in Lux.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C driver performs software reset and applies default settings.
 *
 * ## Application Task
 * Demonstrates use of Ambient 16 Click board by reading data values of DATA0 and DATA1 in Lux
 * every second, and logging it on the UART terminal.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "ambient16.h"

static ambient16_t ambient16;
static log_t logger;
static float data0;
static float data1;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient16_cfg_t ambient16_cfg;  /**< Click config object. */

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
    ambient16_cfg_setup( &ambient16_cfg );
    AMBIENT16_MAP_MIKROBUS( ambient16_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient16_init( &ambient16, &ambient16_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMBIENT16_ERROR == ambient16_default_cfg ( &ambient16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint8_t id;
    ambient16_get_part_id( &ambient16, &id );
    
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " Part ID = 0x%.2X \r\n", ( uint16_t ) id );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    Delay_ms ( 500 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
}

void application_task ( void ) 
{
    ambient16_read_data( &ambient16, &data0, &data1 );
    
    log_printf( &logger, " DATA 0 = %.2f lx    \r\n", data0 );
    log_printf( &logger, " DATA 1 = %.2f lx    \r\n", data1 );
    log_printf( &logger, "- - - - - - - - - - -\r\n" );
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
