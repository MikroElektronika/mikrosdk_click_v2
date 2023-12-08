/*!
 * @file main.c
 * @brief EEPROM 6 Click Example.
 *
 * # Description
 * This example demonstrates the use of EEPROM6 click board by writing 
 * string to a memory at some specific location and then reading it back.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * This example shows capabilities of EEPROM 6 Click board by writting a string 
 * into memory location from a specific address, and then reading it back every 5 seconds.
 *
 * @author Nikola Citakovic
 *
 */

#include "board.h"
#include "log.h"
#include "eeprom6.h"

static eeprom6_t eeprom6;
static log_t logger;

#define EEPROM6_DEMO_TEXT       "MikroE - EEPROM 6 click board"
#define EEPROM6_TEXT_ADDRESS    0x0000

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    eeprom6_cfg_t eeprom6_cfg;  /**< Click config object. */

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
    eeprom6_cfg_setup( &eeprom6_cfg );
    EEPROM6_MAP_MIKROBUS( eeprom6_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == eeprom6_init( &eeprom6, &eeprom6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EEPROM6_ERROR == eeprom6_default_cfg ( &eeprom6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{        
    log_printf( &logger, "Writing \"%s\" to memory address 0x%.4X\r\n", 
                ( uint8_t * ) EEPROM6_DEMO_TEXT, EEPROM6_TEXT_ADDRESS );
    eeprom6_write_mem( &eeprom6, EEPROM6_TEXT_ADDRESS, ( char * ) EEPROM6_DEMO_TEXT,
                       strlen ( EEPROM6_DEMO_TEXT ) );
    Delay_ms( 100 );    
    uint8_t read_buf[ 100 ] = { 0 };
    eeprom6_read_mem ( &eeprom6, EEPROM6_TEXT_ADDRESS,read_buf,
                       strlen ( EEPROM6_DEMO_TEXT ) );
    log_printf( &logger, "Reading \"%s\" from memory address 0x%.4X\r\n\n",
                read_buf, ( uint16_t ) EEPROM6_TEXT_ADDRESS );
    Delay_ms( 5000 );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
