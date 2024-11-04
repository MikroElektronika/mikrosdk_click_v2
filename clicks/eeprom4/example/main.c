/*!
 * \file 
 * \brief Eeprom4 Click example
 * 
 * # Description
 * This Click reads and writes memory.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes Click driver and configures Click that all memory block > is unprotected.
 * Also configures that HOLD operation is disabled, and the memory and > status register are writable.
 * 
 * ## Application Task  
 * Enables writting to memory array, writes data from buffer to memory,
 * checks if the part is in a write cycle, and if is not reads data >  > from memory array and stores data to buffer.
 * Storaged data shows on USB UART. 
 *  
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "eeprom4.h"

// ------------------------------------------------------------------ VARIABLES

static eeprom4_t eeprom4;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    eeprom4_cfg_t cfg;

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

    eeprom4_cfg_setup( &cfg );
    EEPROM4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    eeprom4_init( &eeprom4, &cfg );
    
    eeprom4_default_cfg( &eeprom4 );
}

void application_task (  )
{
    uint8_t data_write[ 13 ] = { 'M', 'i', 'K', 'r', 'O', 'e', 0 };
    uint8_t data_read[ 255 ] = { 0 };
    uint8_t cnt;
    uint8_t check_state;

    eeprom4_send_command( &eeprom4, EEPROM4_SET_WRITE_ENABLE_LATCH_COMMAND );
    eeprom4_write_memory( &eeprom4, EEPROM4_FIRST_MEMORY_LOCATION, data_write, 6 );

    cnt = eeprom4_check_status_reg( &eeprom4, EEPROM4_READY_BIT );
    check_state = eeprom4_send_command( &eeprom4, EEPROM4_LOW_POWER_WRITE_POLL_COMMAND );
    
    while ( cnt | check_state )
    {
        cnt = eeprom4_check_status_reg( &eeprom4, EEPROM4_READY_BIT );
        check_state = eeprom4_send_command( &eeprom4, EEPROM4_LOW_POWER_WRITE_POLL_COMMAND );
    }
    
    eeprom4_read_memory( &eeprom4, 0x00000000, data_read, 6 );

    for ( cnt = 0; cnt < 6; cnt++ )
    {
        log_printf( &logger, " %c ", data_read[cnt] );
    }
    log_printf( &logger, "-----   \r\n" );
    
    Delay_ms ( 1000 );
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
