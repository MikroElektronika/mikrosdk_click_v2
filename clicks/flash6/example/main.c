/*!
 * \file 
 * \brief Flash6 Click example
 * 
 * # Description
 * This application writes in memory and reads from memory.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver, resets device and tests communication.
 * 
 * ## Application Task  
 * Clears the memory sector, writes "MikroE" to device memory
 * and then reads it and sends it to log every 2 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "flash6.h"

// ------------------------------------------------------------------ VARIABLES

static flash6_t flash6;
static log_t logger;

static char write_buf[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    flash6_cfg_t cfg;

    uint8_t manufacture_id;
    uint8_t device_id;

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

    flash6_cfg_setup( &cfg );
    FLASH6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    flash6_init( &flash6, &cfg );

    flash6_software_reset( &flash6 );
    Delay_ms ( 100 );

    flash6_get_manufacture_device_id( &flash6, &manufacture_id, &device_id );
    log_printf( &logger, "\r\n ------> MANUFACTURE ID: 0x%x \r\n", manufacture_id );
    log_printf( &logger, " ------> DEVICE ID: 0x%x \r\n \r\n", device_id );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    uint32_t start_addr;
    char read_buff[ 50 ];
    uint8_t cnt;
    
    start_addr = 0x002000;

    log_printf( &logger, " ---> Erase sector  \r\n" );
    flash6_erase_memory_segment( &flash6, FLASH6_CMD_SECTOR_ERASE_4KB, start_addr );
    Delay_ms ( 500 );
    
    log_printf( &logger, " ---> Write in memory ... \r\n" );
    flash6_write_memory_data( &flash6, start_addr, &write_buf[ 0 ], 9 );
    log_printf( &logger, " ---> Read from memory \r\n" );
    flash6_read_memory_data( &flash6, start_addr, read_buff, 9 );

    log_printf( &logger, "---->>>> " );
    
    log_printf( &logger, "%s ", read_buff );
    Delay_ms ( 100 );
    log_printf( &logger, "----------------------------------\r\n" );
    
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
