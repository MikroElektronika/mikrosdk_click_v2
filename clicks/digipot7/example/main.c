/*!
 * @file main.c
 * @brief DIGIPOT7 Click example
 *
 * # Description
 * This is an example that demonstrate the use of the DIGI POT 7 Click board.
 * 
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization enables I2C, perform a hardware reset, enable write and set to normal operating mode, 
 * also write log.
 *
 * ## Application Task
 * In this example we set different resistance values:
 * 1.024 kOhm, 2.048 kOhm, 4.096 kOhm and 8.192 kOhm.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on USB uart changes approximately for every 5 sec.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "digipot7.h"

static digipot7_t digipot7;
static log_t logger;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    digipot7_cfg_t digipot7_cfg;  /**< Click config object. */

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
    digipot7_cfg_setup( &digipot7_cfg );
    DIGIPOT7_MAP_MIKROBUS( digipot7_cfg, MIKROBUS_1 );
    err_t init_flag = digipot7_init( &digipot7, &digipot7_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, " Hardware Reset \r\n" );
    digipot7_hw_reset( &digipot7 );
    Delay_ms ( 100 );
    
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, " Enable Write \r\n" );
    digipot7_enable_write( &digipot7 );
    Delay_ms ( 100 );
    
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, " Set normal operating mode \r\n" );
    digipot7_operating_mode( &digipot7, DIGIPOT7_NORMAL_MODE );
    Delay_ms ( 100 );
    
    log_printf( &logger, "----------------------------\r\n" );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "----------------------------\r\n" );
}

void application_task ( void ) {
    log_printf( &logger, " Set Resistance: 1.024 kOhm \r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    digipot7_set_resistance( &digipot7, 1024 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Set Resistance: 2.048 kOhm \r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    digipot7_set_resistance( &digipot7, 2048 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Set Resistance: 4.096 kOhm \r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    digipot7_set_resistance( &digipot7, 4096 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Set Resistance: 8.192 kOhm \r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    digipot7_set_resistance( &digipot7, 8192 );
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
