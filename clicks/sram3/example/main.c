/*!
 * @file main.c
 * @brief SRAM3 Click example
 *
 * # Description
 * This is an example that shows the use of SRAM memory, using SRAM 3 click. SRAM 3 click is based on ANV32AA1W, 
 * and ANV32AA1W is a 1Mb serial SRAM with a non-volatile SONOS storage element included with each memory cell, 
 * organized as 128k words of 8 bits each. The devices are accessed by a high speed SPI-compatible bus. 
 * Specifically in this example, we used the high-speed SPI communication characteristics to write data to a specific 
 * registration address and read it.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization SPI module, logger initalization and click initialization.
 *
 * ## Application Task
 * First, we write the data to the registry address 0x00, and then we read the data from 0x00 address.
 *
 * @author Jelena Milosavljevic
 *
 */

#include "board.h"
#include "log.h"
#include "sram3.h"

static sram3_t sram3;
static log_t logger;
uint8_t buf[10] = { 'M','i','k','r','o','E', 0 };

void application_init ( void ) {
    log_cfg_t log_cfg;         /**< Logger config object. */
    sram3_cfg_t sram3_cfg;     /**< Click config object. */

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
    sram3_cfg_setup( &sram3_cfg );
    SRAM3_MAP_MIKROBUS( sram3_cfg, MIKROBUS_1 );
    err_t init_flag  = sram3_init( &sram3, &sram3_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {        
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    sram3_release_hold( &sram3 );
    Delay_ms ( 100 );
}

void application_task ( void ) {
    char buff_out[ 10 ] = { 0 };
        
    log_printf( &logger, "Writing [ %s ] to memory...\r\n", buf );
    sram3_enable_write( &sram3 );
    sram3_write( &sram3, 0x00, &buf[0], 6 );

    Delay_ms ( 100 );
    sram3_read( &sram3, 0x00, &buff_out[0], 6 );
    Delay_ms ( 100 );
    log_printf( &logger, "Data read from memory: %s \r\n", buff_out );
    log_printf( &logger, "---------------------------------------------\r\n" );

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
