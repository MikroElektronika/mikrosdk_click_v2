/*!
 * @file main.c
 * @brief Thermo20 Click example
 *
 * # Description
 * This example showcases the ability of Thermo 20 Click board to
 * read it's serial number. It can read themperature and measure from -40degC to
 * 120degC.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization communication modules(I2C, UART). Resets device and read Serial Number.
 *
 * ## Application Task
 * In span of ~ 1000ms it sends command for adc conversion of temperature, reads ADC value,
 * and calculates temperature in degrees C.
 * 
 * @note For this driver to work on 18bit PIC MCU-s you need to additionally pull up communication lines.
 *
 * @author Mikroe Team
 *
 */

#include "board.h"
#include "log.h"
#include "thermo20.h"

static thermo20_t thermo20;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo20_cfg_t thermo20_cfg;  /**< Click config object. */

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
    thermo20_cfg_setup( &thermo20_cfg );
    THERMO20_MAP_MIKROBUS( thermo20_cfg, MIKROBUS_1 );
    err_t init_flag = thermo20_init( &thermo20, &thermo20_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    thermo20_default_cfg ( &thermo20 );
    
    uint32_t ser_numb = thermo20_get_serial_number( &thermo20 );
    log_printf( &logger, " > Serial Number: %lu\r\n", ser_numb );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    thermo20_start_conversion( &thermo20 );
    
    float temperature = thermo20_get_temperature( &thermo20 );
    
    log_printf( &logger, " > Temperature[deg C]: %.2f\r\n", temperature );
    
    Delay_ms( 1000 );
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
