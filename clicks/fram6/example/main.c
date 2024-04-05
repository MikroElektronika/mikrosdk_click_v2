/*!
 * @file main.c
 * @brief FRAM6 Click example
 *
 * # Description
 * This example demonstrates the use of FRAM 6 click board.
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
 */

#include "board.h"
#include "log.h"
#include "fram6.h"

#define DEMO_TEXT_MESSAGE           "MikroE - FRAM 6 click board"
#define STARTING_ADDRESS            0x01234        

static fram6_t fram6;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    fram6_cfg_t fram6_cfg;  /**< Click config object. */

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

    fram6_cfg_setup( &fram6_cfg );
    FRAM6_MAP_MIKROBUS( fram6_cfg, MIKROBUS_1 );
    
    if ( SPI_MASTER_ERROR == fram6_init( &fram6, &fram6_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    if ( FRAM6_ERROR == fram6_default_cfg ( &fram6 ) )
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t data_buf[ 128 ] = { 0 };
    if ( FRAM6_OK == fram6_memory_write ( &fram6, STARTING_ADDRESS, 
                                          DEMO_TEXT_MESSAGE, strlen ( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf ( &logger, "Data written to address 0x%.5lx: \t%s\r\n", ( uint32_t ) STARTING_ADDRESS, 
                                                                             ( char * ) DEMO_TEXT_MESSAGE );
    }
    if ( FRAM6_OK == fram6_memory_read ( &fram6, STARTING_ADDRESS, 
                                         data_buf, strlen ( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf ( &logger, "Data read from address 0x%.5lx: \t%s\r\n\n", ( uint32_t ) STARTING_ADDRESS, 
                                                                                         data_buf );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
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
