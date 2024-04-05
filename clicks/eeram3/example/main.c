/*!
 * @file main.c
 * @brief EERAM3 Click example
 *
 * # Description
 * This example demonstrates the use of EERAM 3 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Writes a desired number of bytes to the memory and then verifies that it's written correctly
 * by reading from the same memory location and displaying the memory content on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "eeram3.h"

#define DEMO_TEXT_MESSAGE           "MikroE - EERAM 3 click board"
#define STARTING_ADDRESS            0x1000 

static eeram3_t eeram3;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;        /**< Logger config object. */
    eeram3_cfg_t eeram3_cfg;  /**< Click config object. */

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
    eeram3_cfg_setup( &eeram3_cfg );
    EERAM3_MAP_MIKROBUS( eeram3_cfg, MIKROBUS_1 );
    
    if ( SPI_MASTER_ERROR == eeram3_init( &eeram3, &eeram3_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    eeram3_default_cfg ( &eeram3 );
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t data_buf[ 64 ] = { 0 };
    if ( EERAM3_OK == eeram3_memory_secure_write ( &eeram3, STARTING_ADDRESS, 
                                                   DEMO_TEXT_MESSAGE, strlen ( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf ( &logger, "Data written to address 0x%.4X: %s\r\n", ( uint16_t ) STARTING_ADDRESS, 
                                                                          ( char * ) DEMO_TEXT_MESSAGE );
    }
    Delay_ms ( 100 );

    if ( EERAM3_OK == eeram3_memory_secure_read ( &eeram3, STARTING_ADDRESS, 
                                                  data_buf, strlen ( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf ( &logger, "Data read from address 0x%.4X: %s\r\n\n", ( uint16_t ) STARTING_ADDRESS, 
                                                                                      data_buf );
    }
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
