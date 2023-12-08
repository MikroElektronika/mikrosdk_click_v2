/*!
 * @file main.c
 * @brief EEPROM7 Click example
 *
 * # Description
 * This is an example that demonstrates the use of the EEPROM 7 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver enables - SPI, also write log.
 *
 * ## Application Task
 * In this example, we write and then read data from EEPROM memory.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on USB uart changes approximately for every 3 sec.
 *
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "eeprom7.h"

static eeprom7_t eeprom7;
static log_t logger;

static char demo_data[ 9 ] = { 'm', 'i', 'k', 'r', 'o', 'E', 13 ,10 , 0 };
static char read_data[ 9 ];
static uint8_t check_status;
static uint8_t n_cnt;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    eeprom7_cfg_t eeprom7_cfg;  /**< Click config object. */

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

    eeprom7_cfg_setup( &eeprom7_cfg );
    EEPROM7_MAP_MIKROBUS( eeprom7_cfg, MIKROBUS_1 );
    err_t init_flag  = eeprom7_init( &eeprom7, &eeprom7_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    eeprom7_default_cfg ( &eeprom7 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    eeprom7_send_cmd( &eeprom7, EEPROM7_OPCODE_STATUS_WREN );
    Delay_ms( 100 );
    
    eeprom7_write_memory( &eeprom7, 0x00001234, &demo_data[ 0 ], 9 );
    Delay_ms( 100 );
    
    log_printf( &logger, " > Write data: %s", demo_data );

    while ( eeprom7_is_device_ready( &eeprom7 ) == EEPROM7_DEVICE_IS_READY ) {
        check_status = eeprom7_send_cmd( &eeprom7, EEPROM7_OPCODE_STATUS_WRBP );
        Delay_ms( 1 );
    }

    eeprom7_read_memory( &eeprom7, 0x00001234, &read_data[ 0 ], 9 );
    Delay_ms( 100 );
    log_printf( &logger, " > Read data: %s", read_data );


    log_printf( &logger, "---------------------\r\n" );
    Delay_ms( 3000 );
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
