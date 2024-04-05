/*!
 * @file main.c
 * @brief ClockGen4 Click example
 *
 * # Description
 * This example demonstrates the use of Clock Gen 4 click which is based on CS2200-CP for changing the channel clock. The CS2200-CP is an extremely 
 * versatile system clocking device that utilizes a programmable phase lock loop. The CS2200-CP is based on an analog PLL architecture and this 
 * architecture allows for frequency synthesis and clock generation from a stable reference clock. The CS2200-CP supports both I²C and SPI for full software control.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C and SPI, sets CS pin as output and starts to write log, applies default settings and adjusted ratio to obtain a frequency.
 *
 * ## Application Task
 * Clock Gen 4 click is used in this example to generate and change the clock on the output channel.
 *
 * @author Jelena Milosavljevic
 *
 */

#include "board.h"
#include "log.h"
#include "clockgen4.h"

static clockgen4_t clockgen4;
static log_t logger;

uint8_t com_itfc = 0;

void application_init ( void ){
    log_cfg_t log_cfg;                     /**< Logger config object. */
    clockgen4_cfg_t clockgen4_cfg;         /**< Click config object. */

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
    
    Delay_ms ( 100 );
    log_printf( &logger, "---------------------" );
    log_printf( &logger, "  Clock Gen 4 Click  " );
    log_printf( &logger, "---------------------" );
    
    // Click initialization.
    clockgen4_cfg_setup( &clockgen4_cfg );
    CLOCKGEN4_MAP_MIKROBUS( clockgen4_cfg, MIKROBUS_1 );
    err_t init_flag  = clockgen4_init( &clockgen4, &clockgen4_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    clockgen4_default_cfg ( &clockgen4 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

void application_task ( void ){
    clockgen4_dev_ctl ( &clockgen4, CLOCKGEN4_AUX_OUT_DIS | CLOCKGEN4_CLK_OUT_EN );
    log_printf( &logger, "  PLL Clock          \r\n" );
    log_printf( &logger, "  output enabled!    \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 1000 );
    
    clockgen4_dev_ctl ( &clockgen4, CLOCKGEN4_AUX_OUT_EN | CLOCKGEN4_CLK_OUT_DIS );
    log_printf( &logger, "  AUX Clock          \r\n" );
    log_printf( &logger, "  output enabled!    \r\n" );
    log_printf( &logger, "---------------------\r\n" );
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
