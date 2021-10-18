/*!
 * @file main.c
 * @brief Proximity14 Click example
 *
 * # Description
 * This example showcases the ability of the device to read proximity 
 * value. It can be configured to detect objects up to 20cm of distance.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of host communication modules (UART, I2C) and 
 * additional pins. Reads device ID and sets default configuration.
 *
 * ## Application Task
 * In span of 100ms reads proximity data from device and logs result.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "proximity14.h"

static proximity14_t proximity14;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity14_cfg_t proximity14_cfg;  /**< Click config object. */

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
    proximity14_cfg_setup( &proximity14_cfg );
    PROXIMITY14_MAP_MIKROBUS( proximity14_cfg, MIKROBUS_1 );
    err_t init_flag = proximity14_init( &proximity14, &proximity14_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    init_flag |= proximity14_default_cfg ( &proximity14 );
    if ( PROXIMITY14_OK != init_flag ) 
    {
        log_error( &logger, " Default configuration. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    uint16_t temp_data = 0;
    init_flag = proximity14_generic_read( &proximity14, PROXIMITY14_REG_ID, &temp_data );
    log_printf( &logger, " > ID: 0x%.4X\r\n", temp_data );
    
    log_info( &logger, " Application Task " );
    Delay_ms( 1000 );
}

void application_task ( void ) 
{
    uint16_t temp_data = 0;
    proximity14_generic_read( &proximity14, PROXIMITY14_REG_DATA, &temp_data );
    log_printf( &logger, " > Data: %u\r\n", temp_data );
    Delay_ms( 100 );
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
