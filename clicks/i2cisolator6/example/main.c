/*!
 * @file main.c
 * @brief I2C Isolator 6 Click example
 *
 * # Description
 * This library contains API for the I2C Isolator 6 Click driver.
 * This demo application shows an example of an I2C Isolator 6 Click 
 * wired to the Accel 21 Click for reading device ID.
 * The library also includes an I2C writing and reading functions.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of the I2C module, log UART.
 * After the driver init, the app sets Accel 21 Click I2C Slave address.
 *
 * ## Application Task
 * This example demonstrates the use of the I2C Isolator 6 Click board™.
 * Logs device ID values of the Accel 21 Click 
 * wired to the I2C Isolator 6 Click board™.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "i2cisolator6.h"

#define ACCEL21_DEVICE_ADDRESS_GND    0x18
#define ACCEL21_DEVICE_ADDRESS_VCC    0x19
#define ACCEL21_REG_WHO_AM_I          0x0F
#define ACCEL21_DEVICE_ID             0x33

static i2cisolator6_t i2cisolator6;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    i2cisolator6_cfg_t i2cisolator6_cfg;  /**< Click config object. */

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
    i2cisolator6_cfg_setup( &i2cisolator6_cfg );
    I2CISOLATOR6_MAP_MIKROBUS( i2cisolator6_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == i2cisolator6_init( &i2cisolator6, &i2cisolator6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms( 100 );
    
    if ( I2CISOLATOR6_ERROR == i2cisolator6_set_slave_address( &i2cisolator6, ACCEL21_DEVICE_ADDRESS_GND ) )
    {
        log_error( &logger, " Set I2C Slave address ERROR." );
        for ( ; ; );
    }
    Delay_ms( 100 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------\r\n" );
}

void application_task ( void ) 
{
    static uint8_t device_id = 0;
    static uint8_t reg = ACCEL21_REG_WHO_AM_I;
    if ( I2CISOLATOR6_OK == i2cisolator6_write_then_read( &i2cisolator6, &reg, 1, &device_id, 1 ) )
    {
        if ( ACCEL21_DEVICE_ID == device_id )
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
