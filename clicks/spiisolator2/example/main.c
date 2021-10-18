/*!
 * @file main.c
 * @brief SPIIsolator2 Click example
 *
 * # Description
 * This is an example that demonstrates the use of the SPI Isolator 2 click board. This board uses the ISO7741 which
 * provides high electromagnetic immunity and low emissions at low power consumption while isolating digital I/Os. 
 * In this example, we write and then read data from the connected EEPROM 5 click to the SPI Isolator 2 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes SPI, begins to write log, set write/read memory address, enable output.
 *
 * ## Application Task
 * After pin starts working, we wait 10ms, then write the text, wait 100ms and read. 
 *
 * @author Jelena Milosavljevic
 *
 */

#include "board.h"
#include "log.h"
#include "spiisolator2.h"

static spiisolator2_t spiisolator2;
static log_t logger;
static char demo_data[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13 ,10 , 0 };
static char read_data[ 9 ];
static uint8_t n_cnt;
static char log_text[ 50 ];
static uint32_t memory_address;

void application_init ( void ) {
    log_cfg_t log_cfg;                         /**< Logger config object. */
    spiisolator2_cfg_t spiisolator2_cfg;       /**< Click config object. */

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
    log_info( &logger, " Application Init \r\n" );

    // Click initialization.
    spiisolator2_cfg_setup( &spiisolator2_cfg );
    SPIISOLATOR2_MAP_MIKROBUS( spiisolator2_cfg, MIKROBUS_1 );
    err_t init_flag  = spiisolator2_init( &spiisolator2, &spiisolator2_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {        
        log_error( &logger, " Application Init Error. \r\n" );
        log_info( &logger, " Please, run program again... \r\n" );

        for ( ; ; );
    }
    
    log_info( &logger, " Application Task \r\n" );
    
    memory_address = 1234;
    
    log_printf( &logger, "   SPI driver init    \r\n" );
    log_printf( &logger, "----------------------\r\n" );
    Delay_ms( 100 );
    
    log_printf( &logger,"     Enable Output     \r\n" );
    log_printf( &logger, "----------------------\r\n" );
    spiisolator2_output_enable( &spiisolator2, SPIISOLATOR2_OUT_ENABLE );
    log_info( &logger, " Application Task \r\n" );
    Delay_ms( 100 );
}

void application_task ( void ) {
    spiisolator2_set_cmd( &spiisolator2, SPIISOLATOR2_EEPROM5_CMD_WRITE_ENABLE );
    Delay_ms( 10 );

    spiisolator2_multi_write( &spiisolator2, SPIISOLATOR2_EEPROM5_CMD_WRITE | memory_address, 4, demo_data, 9 );
    log_printf( &logger," Write data : %s \r\n", demo_data );
    log_printf( &logger, "- - - - - - - - - - - - - - - \r\n" );

    Delay_ms( 100 );

    spiisolator2_multi_read( &spiisolator2, SPIISOLATOR2_EEPROM5_CMD_READ | memory_address, 4, read_data, 9 );
    Delay_ms( 1000 );
    
    log_printf( &logger, " Read data  : %s \r\n", read_data );
    log_printf( &logger, "---------------------------------\r\n" );
    Delay_ms( 5000 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
