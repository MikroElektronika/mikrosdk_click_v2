/*!
 * \file 
 * \brief Scanner Click example
 * 
 * # Description
 * This example reads data from Scanner clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and starts up the module.
 * 
 * ## Application Task  
 * Reads the array of 102 pixels and displays the results on the USB UART 
 * as frequently as possible.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "scanner.h"

// ------------------------------------------------------------------ VARIABLES

static scanner_t scanner;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    scanner_cfg_t cfg;

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
    log_info( &logger, "--->>> APP INIT <<<---\r\n" );

    //  Click initialization.

    scanner_cfg_setup( &cfg );
    SCANNER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    scanner_init( &scanner, &cfg );

    Delay_ms( 300 );

    scanner_startup( &scanner );
    Delay_ms( 100 );
    
    scanner_serial_write_reg( &scanner, SCANNER_REG_MODE, SCANNER_DATA_NORMAL_MODE );
    
    for ( uint8_t data_cnt = 0; data_cnt < 3; )
    {
        scanner_serial_write_reg( &scanner, SCANNER_REG_OFFSET_LEFT + ( 2 * data_cnt ), 25 );
        data_cnt++;
        scanner_serial_write_reg( &scanner, SCANNER_REG_GAIN_LEFT + ( 2 * data_cnt ), 25 );
        data_cnt++;
    }
    log_printf( &logger, "--->>> APP TASK <<<--- \r\n" );
}

void application_task ( void )
{
    uint8_t pixels[ 102 ];
    scanner_read_pixel( &scanner, pixels );
    
    log_printf( &logger, "left center right\r\n" );
    for ( uint8_t cnt = 0; cnt < 34; cnt++ )
    {
        log_printf( &logger, " %u   %u   %u \r\n", ( uint16_t ) pixels[ cnt ], 
                                                   ( uint16_t ) pixels[ cnt + 34 ], 
                                                   ( uint16_t ) pixels[ cnt + 68 ] );
    }
    log_printf( &logger, "----------------\r\n" );
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
