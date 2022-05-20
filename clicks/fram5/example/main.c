/*!
 * @file main.c
 * @brief FRAM5 Click example
 *
 * # Description
 * This example demonstrates the use of FRAM 5 click board by writing specified data to
 * the memory and reading it back.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and checks the communication with the click board.
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
#include "fram5.h"

static fram5_t fram5;
static log_t logger;

#define DEMO_TEXT_MESSAGE           "MikroE - FRAM 5 click board"
#define STARTING_ADDRESS            0x01234   

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    fram5_cfg_t fram5_cfg;  /**< Click config object. */

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
    fram5_cfg_setup( &fram5_cfg );
    FRAM5_MAP_MIKROBUS( fram5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == fram5_init( &fram5, &fram5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( FRAM5_ERROR == fram5_check_communication ( &fram5 ) )
    {
        log_error( &logger, " Check communication." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t data_buf[ 128 ] = { 0 };
    if ( FRAM5_OK == fram5_memory_write ( &fram5, STARTING_ADDRESS, 
                                          DEMO_TEXT_MESSAGE, strlen ( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf ( &logger, "Data written to address 0x%.5lx: %s\r\n", ( uint32_t ) STARTING_ADDRESS, 
                                                                           ( char * ) DEMO_TEXT_MESSAGE );
    }
    if ( FRAM5_OK == fram5_memory_read ( &fram5, STARTING_ADDRESS, 
                                         data_buf, strlen ( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf ( &logger, "Data read from address  0x%.5lx: %s\r\n\n", ( uint32_t ) STARTING_ADDRESS, 
                                                                                        data_buf );
        Delay_ms ( 3000 );
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
