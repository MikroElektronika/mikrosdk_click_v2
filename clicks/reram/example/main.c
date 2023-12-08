/*!
 * \file main.c
 * \brief ReRAM Click example
 *
 * # Description
 * This example demonstrates the use of the ReRAM Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes SPI serial interface and puts a device to the initial state.
 * Data from 0 to 255 will be written in memory block from address 0x0 to
 * address 0xFF.
 *
 * ## Application Task
 * Reads same memory block starting from address 0x0 to address 0xFF and
 * sends memory content to USB UART, to verify memory write operation.
 *
 * *note:*
 * Write Enable Latch is reset after the following operations:
 *  - After 'Write Disable'command recognition.
 *  - The end of writing process after 'Write Status' command recognition.
 *  - The end of writing process after 'Write Memory' command recognition.
 *
 * Data will not be written in the protected blocks of the ReRAM array.
 *  - Upper 1/4 goes from address 0x60000 to 0x7FFFF.
 *  - Upper 1/2 goes from address 0x40000 to 0x7FFFF.
 *  - The entire ReRAM array goes from address 0x00000 to 0x7FFFF.
 *
 * \author Nemanja Medakovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "reram.h"


// ------------------------------------------------------------------ VARIABLES

static reram_t reram;
static log_t logger;

static char write_buf[  ] = "MikroE";
static char read_buf[ 10 ] = { 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init( void )
{
    reram_cfg_t reram_cfg;
    log_cfg_t logger_cfg;

    //  Click object initialization.
    reram_cfg_setup( &reram_cfg );
    RERAM_MAP_MIKROBUS( reram_cfg, MIKROBUS_1 );
    reram_init( &reram, &reram_cfg );

    //  Click start configuration.
    reram_default_cfg( &reram );

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( logger_cfg );
    log_init( &logger, &logger_cfg );
    
    reram_wake_up( &reram );
    
    uint32_t id_data = reram_read_id( &reram );
    
    if ( RERAM_ID_DATA != id_data )
    {
        log_printf( &logger, "***  ReRAM Error ID  ***\r\n" );
        for( ; ; );
    }
    else
    {    
        log_printf( &logger, "***  ReRAM Initialization Done  ***\r\n" );
        log_printf( &logger, "***********************************\r\n" );
    }


    reram_send_cmd( &reram, RERAM_CMD_WREN );
    Delay_ms( 1000 );
}

void application_task( void )
{   
    log_printf( &logger, "* Writing data *\r\n" );
    
    reram_write_memory( &reram, RERAM_MEM_ADDR_START, write_buf, 6 );
    Delay_ms( 1000 );
    reram_read_memory( &reram, RERAM_MEM_ADDR_START, read_buf, 6 );

    log_printf( &logger, "* Read data:%s\r\n", read_buf );
    Delay_ms( 2000 );
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
