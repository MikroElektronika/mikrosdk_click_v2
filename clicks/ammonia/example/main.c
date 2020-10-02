/*!
 * \file 
 * \brief Ammonia Click example
 * 
 * # Description
 * This demo application reads ADC value.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes SPI driver, turns on the heater, and makes an initial log.
 * 
 * ## Application Task  
 * This is an example that shows the capabilities of the ADC 9 click by reading ADC value and displaying it via UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ammonia.h"

// ------------------------------------------------------------------ VARIABLES

static ammonia_t ammonia;
static log_t logger;

uint32_t spi_adc_value;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ammonia_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ammonia_cfg_setup( &cfg );
    AMMONIA_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uint8_t err_flag = ammonia_init( &ammonia, &cfg );
    if (err_flag == AMMONIA_INIT_ERROR)
    {
        log_info( &logger, "---- Error Init ----" );
        for(;;);
    }
    Delay_ms( 100 );

    ammonia_heater( &ammonia, AMMONIA_HEATER_ON );
    Delay_ms( 1000 );

    log_printf( &logger, "-------------------- \r\n" );
    log_printf( &logger, "   Ammonia  click    \r\n" );
    log_printf( &logger, "-------------------- \r\n" );
}

void application_task ( void )
{
    spi_adc_value = ammonia_data_read( &ammonia );

    log_printf( &logger, "ADC value: %lu \r\n", spi_adc_value );

    Delay_ms( 1000 );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
