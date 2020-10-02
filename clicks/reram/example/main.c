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

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init( void )
{
    reram_cfg_t reram_cfg;
    log_cfg_t logger_cfg;
    uint8_t data_in[ RERAM_TRANSFER_BYTES_MAX ];
    uint16_t cnt;

    //  Click object initialization.
    reram_cfg_setup( &reram_cfg );
    RERAM_MAP_MIKROBUS( reram_cfg, MIKROBUS_1 );
    reram_init( &reram, &reram_cfg );

    //  Click start configuration.
    reram_default_cfg( &reram );

    //  Logger initialization.
    LOG_MAP_USB_UART( logger_cfg );
    logger_cfg.level = LOG_LEVEL_DEBUG;
    logger_cfg.baud = 57600;
    log_init( &logger, &logger_cfg );
    log_printf( &logger, "***  ReRAM Initialization Done  ***\r\n" );
    log_printf( &logger, "***********************************\r\n" );

    //  Memory writing.
    data_in[ RERAM_MEM_ADDR_START ] = 0;

    for (cnt = 0x1; cnt < RERAM_TRANSFER_BYTES_MAX; cnt++)
    {
        data_in[ cnt ] = data_in[ cnt - 1 ] + 1;
    }

    reram_send_cmd( &reram, RERAM_CMD_WREN );
    reram_write_memory( &reram, RERAM_MEM_ADDR_START, data_in,
                        RERAM_TRANSFER_BYTES_MAX );
    Delay_ms( 1000 );
}

void application_task( void )
{
    uint8_t data_out;
    static uint16_t mem_addr = RERAM_MEM_ADDR_START;

    reram_read_memory( &reram, mem_addr, &data_out, 1 );

    log_printf( &logger, "* Memory Address [0x%X] : %u", mem_addr, data_out );
    log_printf( &logger, "\r\n" );

    if (mem_addr < 0xFF)
    {
        mem_addr++;
    }
    else
    {
        mem_addr = RERAM_MEM_ADDR_START;
    }

    Delay_ms( 500 );
}

void main( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
