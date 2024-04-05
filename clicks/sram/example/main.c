/*!
 * \file 
 * \brief Sram Click example
 * 
 * # Description
 * SRAM Click presents additional 1Mbit SRAM memory that can be added to device.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Application Init performs Logger and Click initialization.
 * 
 * ## Application Task  
 * SRAM Click communicates with register via SPI protocol by write data to and read data from 23LC1024 Serial RAM device. 
 * Results are being sent to the UART where you can track their changes. 
 * All data logs on USB UART for aproximetly every 1 sec.
 * 
 * \author Mihajlo Djordjevic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "sram.h"

char send_buffer[ 17 ] = { 'm', 'i', 'k', 'r', 'o', 'E', 'l', 'e', 'k', 't', 'r', 'o', 'n', 'i', 'k', 'a', ' ' };
char mem_data[ 17 ];
uint8_t n_cnt;

// ------------------------------------------------------------------ VARIABLES

static sram_t sram;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    sram_cfg_t cfg;

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
    Delay_ms ( 100 );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    sram_cfg_setup( &cfg );
    SRAM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    sram_init( &sram, &cfg );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " ------ SRAM Click  ----- \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    log_printf( &logger, " Writing text :\r\n" );
   
    for ( n_cnt = 0; n_cnt < 16; n_cnt++ )
    {
        sram_write_byte( &sram, n_cnt, send_buffer[ n_cnt ] );
        Delay_ms ( 100 );
        
        log_printf( &logger, "%c", send_buffer[ n_cnt ] );

        mem_data[ n_cnt ] = sram_read_byte( &sram, n_cnt );
    }
    
    
    log_printf( &logger, "\r\n" );
    log_printf( &logger, " Read text :\r\n" );
    for ( n_cnt = 0; n_cnt < 16; n_cnt++ )
    {
        mem_data[ n_cnt ] = sram_read_byte( &sram, n_cnt );
        Delay_ms ( 100 );
        log_printf( &logger, "%c", mem_data[ n_cnt ] );
    }
    log_printf( &logger, "\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    
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
