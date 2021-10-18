/*!
 * \file 
 * \brief Eeprom2 Click example
 * 
 * # Description
 * This application demonstrates the process of writing and
 * reading of data from EEPROM.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes EEPROM 2 driver.
 * 
 * ## Application Task  
 * Writing data to EEPROM and then reading that data and writing it via UART.
 * 
 * *note:* 
 * <NOTE>
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "eeprom2.h"

// ------------------------------------------------------------------ VARIABLES

static eeprom2_t eeprom2;
static log_t logger;
uint8_t text[ 6 ] = { 'M','i','k','r','o','e' };
char mem_value[ 6 ];

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    eeprom2_cfg_t cfg;

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

    eeprom2_cfg_setup( &cfg );
    EEPROM2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    eeprom2_init( &eeprom2, &cfg );
}

void application_task ( void )
{
    eeprom2_write_bytes ( &eeprom2, 0x01, text, 6 );
    log_printf ( &logger, "Writing Mikroe to EEPROM 2 click\r\n" );
    Delay_ms( 1000 );
    eeprom2_read_bytes ( &eeprom2, 0x01 , mem_value, 6);
    log_printf ( &logger, "Data read: %s\r\n", mem_value );
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
