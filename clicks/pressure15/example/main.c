/*!
 * @file main.c
 * @brief Pressure15 Click example
 *
 * # Description
 * This application example showcases the ability of the device to
 * read temperature and pressure data.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of hosts communication modules (UART, SPI/I2C) 
 * and interrupt pin. Checks device ID and sets the default configuration
 * that enables interrupt on new data.
 *
 * ## Application Task
 * Checks if an interrupt occurred. If occurred reads new pressure and temperature
 * data in hPa and degC respectively.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "pressure15.h"

static pressure15_t pressure15;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure15_cfg_t pressure15_cfg;  /**< Click config object. */

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
    pressure15_cfg_setup( &pressure15_cfg );
    PRESSURE15_MAP_MIKROBUS( pressure15_cfg, MIKROBUS_1 );
    err_t init_flag = pressure15_init( &pressure15, &pressure15_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    uint8_t whoami = 0;
    init_flag = pressure15_generic_read( &pressure15, PRESSURE15_REG_WHO_AM_I, &whoami, 1 );
    if ( !init_flag && ( PRESSURE15_ID == whoami ) )
    {
        log_printf( &logger, " > ID: 0x%.2X\r\n", ( uint16_t )whoami );
    }
    else
    {
        log_error( &logger, " ID\r\n");
    }
    
    pressure15_default_cfg ( &pressure15 );
    Delay_ms ( 1000 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( pressure15_get_int( &pressure15 ) )
    {
        float temperature, pressure;
        
        pressure15_get_pressure( &pressure15, &pressure );
        log_printf( &logger, " > Pressure[hPa]: %.2f\r\n", pressure );
        
        pressure15_get_temperature( &pressure15, &temperature );
        log_printf( &logger, " > Temperature[degC]: %.2f\r\n", temperature );
        log_printf( &logger, "***************************************\r\n" );
        Delay_ms ( 200 );
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
