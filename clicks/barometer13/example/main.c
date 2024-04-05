/*!
 * @file main.c
 * @brief Barometer 13 Click example
 *
 * # Description
 * This example demonstrates the use of  Barometer 13  Click board™ 
 * by reading and displaying the pressure and temperature measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C or SPI module and log UART.
 * After driver initialization, the app sets the default configuration.
 *
 * ## Application Task
 * The demo application reads and displays the Pressure [mBar] and Temperature [degree Celsius] data.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "barometer13.h"

static barometer13_t barometer13;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    barometer13_cfg_t barometer13_cfg;  /**< Click config object. */

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
    barometer13_cfg_setup( &barometer13_cfg );
    BAROMETER13_MAP_MIKROBUS( barometer13_cfg, MIKROBUS_1 );
    err_t init_flag = barometer13_init( &barometer13, &barometer13_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BAROMETER13_ERROR == barometer13_default_cfg ( &barometer13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ______________________ \r\n" );
}

void application_task ( void )
{   
    float pressure = 0, temperature = 0;
    if ( ( BAROMETER13_OK == barometer13_get_measurement( &barometer13, &pressure, &temperature ) ) &&
         barometer13_get_interrupt( &barometer13 ) )
    {
        log_printf( &logger, " Pressure    : %.2f mBar \r\n", pressure );
        log_printf( &logger, " Temperature : %.2f degC \r\n", temperature );
        log_printf( &logger, " ______________________ \r\n" );
        Delay_ms ( 1000 );
    }
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
