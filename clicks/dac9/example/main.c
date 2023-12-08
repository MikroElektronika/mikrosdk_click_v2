/*!
 * @file main.c
 * @brief DAC9 Click example
 *
 * # Description
 * This is an example that demonstrates the use of the DAC 9 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initalizes SPI or I2C driver and applies default settings.
 *
 * ## Application Task
 * Demonstrates use of DAC 9 click board by changing output values every two seconds.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "dac9.h"

static dac9_t dac9;
static log_t logger;
static uint16_t res = 2500;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac9_cfg_t dac9_cfg;  /**< Click config object. */

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
    dac9_cfg_setup( &dac9_cfg );
    DAC9_MAP_MIKROBUS( dac9_cfg, MIKROBUS_1 );
    err_t init_flag  = dac9_init( &dac9, &dac9_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "     Soft reset      \r\n" );
    dac9_soft_reset( &dac9 );
    Delay_ms( 200 );

    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "  Vref divided by 2  \r\n" );
    log_printf( &logger, "  Set DAC gain of 2  \r\n" );
    dac9_set_gain( &dac9, DAC9_GAIN_REF_DIV_2, DAC9_GAIN_BUFF_GAIN_2 );
    Delay_ms( 100 );

    log_printf( &logger, "---------------------\r\n" );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    uint16_t n_cnt;
    for ( n_cnt = 0; n_cnt <= res; n_cnt += 500 ) {
        log_printf( &logger, "Output Voltage : %d mV\r\n", ( uint16_t ) n_cnt );
        dac9_set_vout( &dac9, n_cnt );
        Delay_ms( 2000 );
    }
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
