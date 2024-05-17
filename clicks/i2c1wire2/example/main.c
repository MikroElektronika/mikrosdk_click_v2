/*!
 * @file main.c
 * @brief I2C 1-Wire 2 Click example
 *
 * # Description
 * This example demonstrates the use of the I2C 1-Wire 2 Click board
 * by searching if a device is connected and reading its ROMID.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module, log UART and perform Click default configuration.
 *
 * ## Application Task
 * Performing 1-Wire Search algorithm to find if any device is connected.
 * If a device is connected and detected, its ROMID will be read and displayed.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "i2c1wire2.h"

static i2c1wire2_t i2c1wire2;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    i2c1wire2_cfg_t i2c1wire2_cfg;  /**< Click config object. */

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
    i2c1wire2_cfg_setup( &i2c1wire2_cfg );
    I2C1WIRE2_MAP_MIKROBUS( i2c1wire2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == i2c1wire2_init( &i2c1wire2, &i2c1wire2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( I2C1WIRE2_ERROR == i2c1wire2_default_cfg ( &i2c1wire2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    err_t error_flag;
    uint8_t flag;
    uint8_t last_flag;
    uint8_t rom_id[ 8 ] = { 0 };
    #define I2C1WIRE2_DEVICE_SEARCH_CODE            0xF0

    error_flag = i2c1wire2_search ( &i2c1wire2, &flag, rom_id, &last_flag, I2C1WIRE2_SEARCH_RESET | 
                                    I2C1WIRE2_SEARCH_1WIRE_RESET, I2C1WIRE2_DEVICE_SEARCH_CODE );
    if ( I2C1WIRE2_OK == error_flag )
    {   
        if ( I2C1WIRE2_RESULT_BYTE_OK == flag )
        {
            log_printf( &logger, " Device found: \r\n" );
            log_printf( &logger, " Device ROMID: 0x" );
            for ( uint8_t n_cnt = 0; n_cnt < 8; n_cnt++ )
            {
                log_printf( &logger, "%.2X", ( uint16_t ) rom_id[ n_cnt ] );
            }
            log_printf( &logger, " \r\n" );
            log_printf( &logger, " Last device flag %d \r\n", last_flag );
        }
        else if ( I2C1WIRE2_NO_DEVICE_DETECTED == flag )
        {
            log_printf( &logger, " No device detected \r\n" );
        }
        else if ( I2C1WIRE2_NO_PRESENCE_PULS == flag )
        {
            log_printf( &logger, " No presence puls \r\n" );
        }
    }
    else 
    {
        log_printf( &logger, " ERROR \r\n" );
    }
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
