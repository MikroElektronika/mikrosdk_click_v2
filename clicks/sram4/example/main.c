/*!
 * @file main.c
 * @brief SRAM4 Click example
 *
 * # Description
 * This example application showcases ability of device
 * ability to manipulate with memory( writing and reading data ).
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of communication modules(SPI, UART) and additional 
 * pins. Reads ID and checks if it matches with SRAM4_DEVICE_ID to 
 * check communication. Then clears protection from memory access.
 *
 * ## Application Task
 * Writes 3 times to memory with length of data offset in memory address.
 * Then reads 2 times first 2 data written should be read in one read,
 * and 3rd write should be read separately.
 *
 * @author Luka FIlipovic
 *
 */

#include "board.h"
#include "log.h"
#include "sram4.h"

static sram4_t sram4;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    sram4_cfg_t sram4_cfg;  /**< Click config object. */

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
    sram4_cfg_setup( &sram4_cfg );
    SRAM4_MAP_MIKROBUS( sram4_cfg, MIKROBUS_1 );
    err_t init_flag  = sram4_init( &sram4, &sram4_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    if ( sram4_default_cfg ( &sram4 ) )
    {
        log_error( &logger, " Default configuration. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    char read_buf[ 100 ] = { 0 };
    char click_name[ ] = "SRAM 4";
    char company_name[ ] = "MikroE";
    char product_name[ ] = " Click board";
    static const uint16_t START_ADR = 0x0001;
    uint16_t mem_adr = START_ADR;

    //Write Data
    sram4_memory_write( &sram4, mem_adr, click_name, strlen( click_name ) );
    mem_adr += strlen( click_name );
    sram4_memory_write( &sram4, mem_adr, product_name, strlen( product_name ) );
    mem_adr += strlen( product_name );
    sram4_memory_write( &sram4, mem_adr, company_name, strlen( company_name ) );

    //Read Data
    mem_adr = START_ADR;
    sram4_memory_read( &sram4, mem_adr, read_buf, strlen( click_name ) + strlen( product_name ) );
    log_printf( &logger, " > Read Data from 0x%.4X memory address: %s\r\n", mem_adr, read_buf );
    memset( read_buf, 0, strlen( read_buf ) );
    mem_adr += strlen(click_name) + strlen( product_name );
    sram4_memory_read( &sram4, mem_adr, read_buf, strlen( company_name ) );
    log_printf( &logger, " > Read Data from 0x%.4X memory address: %s\r\n", mem_adr, read_buf );
    log_printf( &logger, "**********************************************************************\r\n" );

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
