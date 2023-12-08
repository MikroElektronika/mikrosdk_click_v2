/*!
 * @file main.c
 * @brief DiffPress2 Click example
 *
 * # Description
 * This example application showcases ability for device
 * to read and calculate mass flow or diff press pressure
 * in Pascals and temperature in degrees Celsius.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of module communication(I2C, UART) and 
 * additional interrupt pin. Resets device and reads
 * serial and product ID's and logs them.
 *
 * ## Application Task
 * Read and calculate differential in Pascal and temperature 
 * in degrees Celsius every 300ms.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "diffpress2.h"

static diffpress2_t diffpress2;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    diffpress2_cfg_t diffpress2_cfg;  /**< Click config object. */

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
    diffpress2_cfg_setup( &diffpress2_cfg );
    DIFFPRESS2_MAP_MIKROBUS( diffpress2_cfg, MIKROBUS_1 );
    err_t init_flag = diffpress2_init( &diffpress2, &diffpress2_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    if ( diffpress2_default_cfg ( &diffpress2 ) ) 
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_printf( &logger, " > Product ID: 0x%.8LX\r\n", diffpress2.product_id );
    log_printf( &logger, " > Serial ID: 0x%.8LX%.8LX\r\n", 
                diffpress2.serial_id[ 0 ], diffpress2.serial_id[ 1 ] );

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float pressure;
    float temperature;

    if ( diffpress2_trigger_measurement( &diffpress2, DIFFPRESS2_CMD_TRIGGER_MEAS_DIFF_PRESS, 
                                         &pressure, &temperature ) )
    {
        log_error( &logger, " Read data." );
    }
    else
    {
        log_printf( &logger, " > Pressure[Pa]: %.2f\r\n", pressure );
        log_printf( &logger, " > Temperature[degC]: %.2f\r\n", temperature );
        log_printf( &logger, "*************************************\r\n" );
    }

    Delay_ms( 300 );
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
