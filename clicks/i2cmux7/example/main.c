/*!
 * @file main.c
 * @brief I2CMUX7 Click example
 *
 * # Description
 * This example demonstrates the use of I2C MUX 7 click board by reading the
 * device ID of a 6DOF IMU 11 and Compass 3 click boards connected to 
 * the channels 0 and 7 respectfully.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and resets the device.
 *
 * ## Application Task
 * Reads the device ID of the connected click boards.
 * Channel 0 : 6DOF IMU 11 click [slave address: 0x0E; reg: 0x00; id: 0x2D],
 * Channel 7 : Compass 3 click   [slave address: 0x30; reg: 0x2F; id: 0x0C].
 * All data is being logged on the USB UART where you can check the device ID.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "i2cmux7.h"

#define DEVICE0_NAME                "6DOF IMU 11 click"
#define DEVICE0_POSITION            I2CMUX7_CHANNEL_0
#define DEVICE0_SLAVE_ADDRESS       0x0E
#define DEVICE0_REG_ID              0x00
#define DEVICE0_ID                  0x2D

#define DEVICE1_NAME                "Compass 3 click"
#define DEVICE1_POSITION            I2CMUX7_CHANNEL_7
#define DEVICE1_SLAVE_ADDRESS       0x30
#define DEVICE1_REG_ID              0x2F
#define DEVICE1_ID                  0x0C

static i2cmux7_t i2cmux7;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    i2cmux7_cfg_t i2cmux7_cfg;  /**< Click config object. */

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
    i2cmux7_cfg_setup( &i2cmux7_cfg );
    I2CMUX7_MAP_MIKROBUS( i2cmux7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == i2cmux7_init( &i2cmux7, &i2cmux7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    i2cmux7_reset_device ( &i2cmux7 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t channel, device_id;
    if ( I2CMUX7_OK == i2cmux7_set_channel ( &i2cmux7, DEVICE0_POSITION, DEVICE0_SLAVE_ADDRESS ) )
    {
        if ( I2CMUX7_OK == i2cmux7_read_channel ( &i2cmux7, &channel ) )
        {
            log_printf( &logger, " --- Channel %u --- \r\n", ( uint16_t ) ( channel & I2CMUX7_CHANNEL_NUM_MASK ) );
        }
        if ( I2CMUX7_OK == i2cmux7_generic_read ( &i2cmux7, DEVICE0_REG_ID, &device_id, 1 ) )
        {
            log_printf( &logger, " %s - Device ID: 0x%.2X \r\n\n", ( char * ) DEVICE0_NAME, ( uint16_t ) device_id );
        }
        Delay_ms( 1000 );
    }
    if ( I2CMUX7_OK == i2cmux7_set_channel ( &i2cmux7, DEVICE1_POSITION, DEVICE1_SLAVE_ADDRESS ) )
    {
        if ( I2CMUX7_OK == i2cmux7_read_channel ( &i2cmux7, &channel ) )
        {
            log_printf( &logger, " --- Channel %u --- \r\n", ( uint16_t ) ( channel & I2CMUX7_CHANNEL_NUM_MASK ) );
        }
        if ( I2CMUX7_OK == i2cmux7_generic_read ( &i2cmux7, DEVICE1_REG_ID, &device_id, 1 ) )
        {
            log_printf( &logger, " %s - Device ID: 0x%.2X \r\n\n", ( char * ) DEVICE1_NAME, ( uint16_t ) device_id );
        }
        Delay_ms( 1000 );
    }
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
