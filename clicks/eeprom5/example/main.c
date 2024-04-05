/*!
 * @file main.c
 * @brief EEPROM5 Click example
 *
 * # Description
 * This is an example that demonstrates the use of the EEPROM 5 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver enables SPI, also write log.
 *
 * ## Application Task
 * In this example, we write and then read data from EEPROM memory.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on USB uart changes approximately for every 3 sec.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "eeprom5.h"

static eeprom5_t eeprom5;
static log_t logger;

static uint8_t demo_data[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13 ,10 , 0 };
static uint8_t read_data[ 9 ] = { 0 };

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    eeprom5_cfg_t eeprom5_cfg;  /**< Click config object. */

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
    eeprom5_cfg_setup( &eeprom5_cfg );
    EEPROM5_MAP_MIKROBUS( eeprom5_cfg, MIKROBUS_1 );
    err_t init_flag  = eeprom5_init( &eeprom5, &eeprom5_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    log_printf( &logger, " - - - - - - - - - - - \r\n" );
    log_printf( &logger, " Disabling HOLD \r\n" );
    log_printf( &logger, " - - - - - - - - - - - \r\n" );
    eeprom5_set_hold( &eeprom5, EEPROM5_HOLD_DISABLE );
    Delay_ms ( 100 );
    log_printf( &logger, " Disabling Write Protection \r\n" );
    log_printf( &logger, " - - - - - - - - - - - \r\n" );
    eeprom5_set_write_protect( &eeprom5, EEPROM5_WRITE_PROTECT_DISABLE );
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, " - - - - - - - - - - - \r\n" );
}

void application_task ( void ) 
{
    eeprom5_enable_memory_write( &eeprom5, EEPROM5_WRITE_MEMORY_ENABLE );
    Delay_ms ( 10 );
    
    eeprom5_write_memory( &eeprom5, 14, demo_data, 9 );
    log_printf( &logger, " Write data : %s ", demo_data );
    log_printf( &logger, " - - - - - - - - - - - \r\n" );
    Delay_ms ( 100 );
    
    eeprom5_read_memory( &eeprom5, 14, read_data, 9 );
    log_printf( &logger, " Read data : %s ", read_data );
    log_printf( &logger, " - - - - - - - - - - - \r\n" );
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
