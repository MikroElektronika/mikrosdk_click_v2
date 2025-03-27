/*!
 * @file main.c
 * @brief I2C MUX 8 Click example
 *
 * # Description
 * This example demonstrates the use of I2C MUX 8 Click board by reading the
 * device ID of a 6DOF IMU 11 and Compass 3 Click boards connected to 
 * the channels 1 and 4 respectfully.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and resets the device.
 *
 * ## Application Task
 * Reads the device ID of the connected Click boards.
 * Channel 1 : 6DOF IMU 11 Click [slave address: 0x0E; reg: 0x00; id: 0x2D],
 * Channel 4 : Compass 3 Click   [slave address: 0x30; reg: 0x2F; id: 0x0C].
 * All data is being logged on the USB UART where you can check the device ID.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "i2cmux8.h"

#define DEVICE0_NAME                "6DOF IMU 11 Click"
#define DEVICE0_POSITION            I2CMUX8_CHANNEL_1
#define DEVICE0_SLAVE_ADDRESS       0x0E
#define DEVICE0_REG_ID              0x00
#define DEVICE0_ID                  0x2D

#define DEVICE1_NAME                "Compass 3 Click"
#define DEVICE1_POSITION            I2CMUX8_CHANNEL_4
#define DEVICE1_SLAVE_ADDRESS       0x30
#define DEVICE1_REG_ID              0x2F
#define DEVICE1_ID                  0x0C

static i2cmux8_t i2cmux8;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    i2cmux8_cfg_t i2cmux8_cfg;  /**< Click config object. */

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
    i2cmux8_cfg_setup( &i2cmux8_cfg );
    I2CMUX8_MAP_MIKROBUS( i2cmux8_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == i2cmux8_init( &i2cmux8, &i2cmux8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    i2cmux8_reset_device ( &i2cmux8 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t channel = 0, device_id = 0;
    if ( I2CMUX8_OK == i2cmux8_set_channel ( &i2cmux8, DEVICE0_POSITION, DEVICE0_SLAVE_ADDRESS ) )
    {
        if ( I2CMUX8_OK == i2cmux8_read_channel ( &i2cmux8, &channel ) )
        {
            log_printf( &logger, " --- Channel %u --- \r\n", ( uint16_t ) channel );
        }
        if ( I2CMUX8_OK == i2cmux8_i2c_read_reg ( &i2cmux8, DEVICE0_REG_ID, &device_id, 1 ) )
        {
            log_printf( &logger, " %s - Device ID: 0x%.2X \r\n\n", ( char * ) DEVICE0_NAME, ( uint16_t ) device_id );
        }
        Delay_ms ( 1000 );
    }
    if ( I2CMUX8_OK == i2cmux8_set_channel ( &i2cmux8, DEVICE1_POSITION, DEVICE1_SLAVE_ADDRESS ) )
    {
        if ( I2CMUX8_OK == i2cmux8_read_channel ( &i2cmux8, &channel ) )
        {
            log_printf( &logger, " --- Channel %u --- \r\n", ( uint16_t ) channel );
        }
        if ( I2CMUX8_OK == i2cmux8_i2c_read_reg ( &i2cmux8, DEVICE1_REG_ID, &device_id, 1 ) )
        {
            log_printf( &logger, " %s - Device ID: 0x%.2X \r\n\n", ( char * ) DEVICE1_NAME, ( uint16_t ) device_id );
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
