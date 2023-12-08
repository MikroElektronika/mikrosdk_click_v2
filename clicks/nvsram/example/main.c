/*!
 * @file main.c
 * @brief nvSRAM Click example
 *
 * # Description
 * This is an example that demonstrates the use of the nvSRAM click board.
 * In this example, we write and then read data from nvSRAM memory.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on USB uart changes approximately for every 5 sec.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver enables - I2C, lock Serial Number write, disable Block Protection
 * and enable Memory Write, also write log.
 *
 * ## Application Task
 * Writing data to a memory address, then reading it back and logging it onto uart terminal.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "nvsram.h"

static nvsram_t nvsram;
static log_t logger;

char demo_data[ 9 ] = { 'm', 'i', 'k', 'r', 'o', 'E', 13 ,10 , 0 };
char read_data[ 9 ];
uint32_t mem_addr;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    nvsram_cfg_t nvsram_cfg;  /**< Click config object. */

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
    mem_addr = 1024;

    // Click initialization.
    nvsram_cfg_setup( &nvsram_cfg );
    NVSRAM_MAP_MIKROBUS( nvsram_cfg, MIKROBUS_1 );
    err_t init_flag = nvsram_init( &nvsram, &nvsram_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_printf( &logger,  "  Serial Number Lock   \r\n" );
    log_printf( &logger, " None Block Protection \r\n" );
    nvsram_reg_write( &nvsram, NVSRAM_MEM_CTL_REG, NVSRAM_SNL | NVSRAM_BP_NONE );
    Delay_ms( 100 );
    log_printf( &logger, " Enable Memory Write \r\n" );
    nvsram_enable_memory_write( &nvsram, NVSRAM_WRITE_MEMORY_ENABLE );
    Delay_ms( 100 );
    
    log_info( &logger, " Application Task \r\n" );
}

void application_task ( void ) {
    log_printf( &logger, "  Write data : %s \r\n", demo_data );
    nvsram_memory_write( &nvsram, mem_addr, &demo_data[ 0 ], 9 );
    log_printf( &logger, "- - - - - - - - - - - - \r\n" );
    Delay_ms( 100 );

    nvsram_memory_read( &nvsram, mem_addr, &read_data[ 0 ], 9 );
    log_printf( &logger, "  Read data  : %s \r\n", read_data );
    log_printf( &logger, "----------------------- \r\n" );
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
