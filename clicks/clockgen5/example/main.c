/*!
 * @file main.c
 * @brief ClockGen5 Click example
 *
 * # Description
 * This is an example that demonstrates the use of the Clock Gen 5 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver enables - SPI,
 * set output configuration CLK 180, also write log.
 *
 * ## Application Task
 * In this example, we adjusts different frequencies every 3 sec.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "clockgen5.h"

static clockgen5_t clockgen5;
static log_t logger;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    clockgen5_cfg_t clockgen5_cfg;  /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.

    clockgen5_cfg_setup( &clockgen5_cfg );
    CLOCKGEN5_MAP_MIKROBUS( clockgen5_cfg, MIKROBUS_1 );
    err_t init_flag  = clockgen5_init( &clockgen5, &clockgen5_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... %d", init_flag );

        for ( ; ; );
    }
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "    Enabling Output   \r\n" );
    clockgen5_out_enable( &clockgen5, CLOCKGEN5_OUTPUT_ENABLE);
    
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "   Set configuration   \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    clockgen5_set_config( &clockgen5, CLOCKGEN5_CFG_ON_CLK_180 );
    Delay_ms( 500 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "        12.0 MHz       \r\n" );
    clockgen5_set_freq( &clockgen5, 12000.0 );
    Delay_ms( 3000 );
    
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "         8.0 MHz       \r\n" );
    clockgen5_set_freq( &clockgen5, 8000.0 );
    Delay_ms( 3000 );
    
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "         5.5 MHz       \r\n" );
    clockgen5_set_freq( &clockgen5, 5500.0 );
    Delay_ms( 3000 );
    
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "         2.7 MHz       \r\n" );
    clockgen5_set_freq( &clockgen5, 2700.0 );
    Delay_ms( 3000 );
    
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "         0.8 MHz       \r\n" );
    clockgen5_set_freq( &clockgen5, 800.0 );
    Delay_ms( 3000 );
    
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "         0.2 MHz       \r\n" );
    clockgen5_set_freq( &clockgen5, 200.0 );
    Delay_ms( 3000 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
