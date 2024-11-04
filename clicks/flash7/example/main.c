/*!
 * @file main.c
 * @brief Flash7 Click example
 *
 * # Description
 * This is an example that demonstrates the use
 * of the Flash 7 Click board. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver enables SPI,
 * disables write protect and hold, performs whole chip erase,
 * targets the memory address at "4096" for page program starting point
 * and writes data which is also displayed on the log.
 *
 * ## Application Task
 * In this example, the data is read from
 * the targeted memory address. The results are being sent to the Usart Terminal.
 * This task repeats every 5 sec.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "flash7.h"

static flash7_t flash7;
static log_t logger;

static char demo_data[ 9 ] = { 'm', 'i', 'k', 'r', 'o', 'E', 13 ,10 , 0 };
static char rx_data[ 9 ];
static uint32_t memory_addr;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    flash7_cfg_t flash7_cfg;  /**< Click config object. */

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

    flash7_cfg_setup( &flash7_cfg );
    FLASH7_MAP_MIKROBUS( flash7_cfg, MIKROBUS_1 );
    err_t init_flag  = flash7_init( &flash7, &flash7_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    flash7_default_cfg ( &flash7 );
    
    log_printf( &logger, " ----------------------- \r\n" );
    log_printf( &logger, " Chip Erase \r\n" );
    flash7_chip_erase( &flash7 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    memory_addr = 4096;
    
    log_printf( &logger, " ----------------------- \r\n" );
    log_printf( &logger, " Write data : %s ", demo_data );
    log_printf( &logger, " ----------------------- \r\n" );
    flash7_page_program( &flash7, memory_addr, demo_data, 9 );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ----------------------- \r\n" );
}

void application_task ( void ) {
    flash7_read_memory( &flash7, memory_addr, rx_data, 9 );
    log_printf( &logger, " Read data : %s ", rx_data );
    log_printf( &logger, " ----------------------- \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
