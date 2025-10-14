/*!
 * @file main.c
 * @brief I2C Repeater Click example
 *
 * # Description
 * This example demonstrates the communication through the I2C Repeater Click board.
 * It initializes the device, sets the slave I2C address of an external I2C sensor (e.g. 6DOF IMU 11 Click),
 * and reads its device ID register, verifying if the expected ID is returned.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the I2C Repeater Click, then enables the device.
 *
 * ## Application Task
 * Sets the I2C address of a connected I2C sensor and reads its device ID,
 * then logs whether the returned ID matches the expected value.
 *
 * @note
 * Make sure to provide the power supply to VCCB side for the connected I2C sensor. 
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "i2crepeater.h"

#define DEVICE_NAME             "6DOF IMU 11 Click"
#define DEVICE_SLAVE_ADDRESS    0x0E
#define DEVICE_REG_ID           0x00
#define DEVICE_ID               0x2D

static i2crepeater_t i2crepeater;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    i2crepeater_cfg_t i2crepeater_cfg;  /**< Click config object. */

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
    i2crepeater_cfg_setup( &i2crepeater_cfg );
    I2CREPEATER_MAP_MIKROBUS( i2crepeater_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == i2crepeater_init( &i2crepeater, &i2crepeater_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    i2crepeater_enable_device ( &i2crepeater );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t device_id = 0;
    if ( I2CREPEATER_OK == i2crepeater_set_i2c_address ( &i2crepeater, DEVICE_SLAVE_ADDRESS ) )
    {
        if ( I2CREPEATER_OK == i2crepeater_i2c_read_reg ( &i2crepeater, DEVICE_REG_ID, &device_id, 1 ) )
        {
            log_printf( &logger, " %s - Device ID: 0x%.2X - %s\r\n\n", 
                        ( char * ) DEVICE_NAME, ( uint16_t ) device_id, 
                        ( char * ) ( ( DEVICE_ID == device_id ) ? "OK" : "NOK" ) );
        }
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
