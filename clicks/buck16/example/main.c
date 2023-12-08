/*!
 * @file main.c
 * @brief Buck16 Click example
 *
 * # Description
 * This example showcases ability of the device to
 * control voltage output of device. Output voltage 
 * can range from 800 to 5500 depending of VIN. By default
 * it will go from 800 to 3300 VIN==VCC.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of communication modules (SPI, UART) 
 * and additional pin for enabling output and sets it to
 * high.
 * 
 *
 * ## Application Task
 * Sets voltage output first to 900mV then to 2500 mV.
 * Then disables and enables output by toggling pin.
 * In the end sets output value to 1500mV.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "buck16.h"

static buck16_t buck16;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    buck16_cfg_t buck16_cfg;    /**< Click config object. */

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
    log_printf( &logger, "\r> Application Init <\r\n" );

    // Click initialization.
    buck16_cfg_setup( &buck16_cfg );
    BUCK16_MAP_MIKROBUS( buck16_cfg, MIKROBUS_1 );
    err_t init_flag  = buck16_init( &buck16, &buck16_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    buck16_enable_output( &buck16, 1 );
    log_printf( &logger, "> Application Task <\r\n" );
}

void application_task ( void )
{
    log_printf( &logger, " > Setting output to 0.9V\r\n" );
    buck16_set_output( &buck16, 900 );
    Delay_ms( 5000 );
    log_printf( &logger, " > Setting output to 2.5V\r\n" );
    buck16_set_output( &buck16, 2500 );
    Delay_ms( 5000 );
    log_printf( &logger, " > Disable output\r\n" );
    buck16_enable_output( &buck16, 0 );
    Delay_ms( 3000 );
    log_printf( &logger, " > Enable output\r\n" );
    buck16_enable_output( &buck16, 1 );
    Delay_ms( 3000 );
    log_printf( &logger, " > Setting output to 1.5V\r\n" );
    buck16_set_output( &buck16, 1500 );
    Delay_ms( 5000 );
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
