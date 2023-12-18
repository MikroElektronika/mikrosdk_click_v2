/*!
 * @file main.c
 * @brief I2C Isolator 7 Click example
 *
 * # Description
 * This demo application shows an example of an I2C Isolator 7 Click 
 * wired to the PRESS Click board™ for reading device ID (Who am I).
 * The library also includes an I2C writing and reading functions.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C module and log UART.
 * After driver initialization, the app sets the PRESS Click board™ slave address.
 *
 * ## Application Task
 * This example demonstrates the use of the I2C Isolator 7 Click board™.
 * Logs device ID values of the PRESS Click board™ 
 * wired to the I2C Isolator 7 Click board™.
 *
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "i2cisolator7.h"

#define PRESS_DEVICE_ADDRESS               0x5C
#define PRESS_REG_WHO_AM_I                 0x0F
#define PRESS_WHO_AM_I                     0xB4

static i2cisolator7_t i2cisolator7;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    i2cisolator7_cfg_t i2cisolator7_cfg;  /**< Click config object. */

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
    i2cisolator7_cfg_setup( &i2cisolator7_cfg );
    I2CISOLATOR7_MAP_MIKROBUS( i2cisolator7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == i2cisolator7_init( &i2cisolator7, &i2cisolator7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms( 100 );
    
    if ( I2CISOLATOR7_ERROR == i2cisolator7_set_slave_address( &i2cisolator7, PRESS_DEVICE_ADDRESS ) )
    {
        log_error( &logger, " Set I2C Slave address ERROR." );
        for ( ; ; );
    }
    Delay_ms( 100 );

    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    uint8_t device_id = 0;
    uint8_t reg = PRESS_REG_WHO_AM_I;
    if ( I2CISOLATOR7_OK == i2cisolator7_write_then_read( &i2cisolator7, &reg, 1, &device_id, 1 ) )
    {
        if ( PRESS_WHO_AM_I == device_id )
        {
            log_printf( &logger, " Device ID: 0x%.2X\r\n", ( uint16_t ) device_id );
            log_printf( &logger, "---------------------\r\n" );
        }
    }
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
