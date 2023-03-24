/*!
 * \file 
 * \brief Eeprom3 Click example
 * 
 * # Description
 * This application demonstrates the process of reading and writing to the EEPROM.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes EEPROM 3 driver.
 * 
 * ## Application Task  
 * Writing data to EEPROM, reading that data and displaying it via UART
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "eeprom3.h"

// ------------------------------------------------------------------ VARIABLES

static eeprom3_t eeprom3;
static log_t logger;
uint8_t text[ 6 ] = { 'M','i','k','r','o','e' };
char mem_value[ 10 ] = { 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    eeprom3_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    eeprom3_cfg_setup( &cfg );
    EEPROM3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    eeprom3_init( &eeprom3, &cfg );
}

void application_task ( void )
{
    eeprom3_write_page( &eeprom3, 0x100, text, 6 );
    log_printf( &logger, "Writing Mikroe to EEPROM 3 click\r\n" );
    Delay_ms( 1000 );
    
    eeprom3_read( &eeprom3, 0x100, mem_value, 6 );
    log_printf( &logger, "Data read: %s\r\n", mem_value );
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
