/*!
 * @file main.c
 * @brief UART to I2C Click Example.
 *
 * # Description
 * This example demonstrates the use of USB to I2C click board by reading the device ID
 * of a 3D Hall 11 click board connected to the I2C port and controlling the GPIO pins.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default config which resets
 * the device and sets the GPIO pins 0-3 as push-pull output and others as input.
 * After that, reads and displays the chip firmware version.
 *
 * ## Application Task
 * Reads the device ID of a 3D Hall 11 click board connected to the I2C port, 
 * toggles the output pins and displays the GPIO port state. The results will
 * be displayed on the USB UART approximately once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "uarttoi2c.h"

// I2C target device configuration
#define DEVICE_NAME                 "3D Hall 11 click"
#define DEVICE_SLAVE_ADDRESS        0x35
#define DEVICE_REG_ID               0x0D
#define DEVICE_ID                   0x01

static uarttoi2c_t uarttoi2c;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    uarttoi2c_cfg_t uarttoi2c_cfg;  /**< Click config object. */

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
    uarttoi2c_cfg_setup( &uarttoi2c_cfg );
    UARTTOI2C_MAP_MIKROBUS( uarttoi2c_cfg, MIKROBUS_1 );
    if ( UART_ERROR == uarttoi2c_init( &uarttoi2c, &uarttoi2c_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( UARTTOI2C_ERROR == uarttoi2c_default_cfg ( &uarttoi2c ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint8_t version[ 16 ] = { 0 };
    if ( UARTTOI2C_OK == uarttoi2c_read_version ( &uarttoi2c, version ) )
    {
        log_printf( &logger, " Firmware version: %s\r\n", version );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t gpio_state = UARTTOI2C_NO_PIN_MASK;
    uint8_t slave_address = DEVICE_SLAVE_ADDRESS;
    uint8_t reg_addr = DEVICE_REG_ID;
    uint8_t device_id;
    if ( UARTTOI2C_OK == uarttoi2c_i2c_write_then_read ( &uarttoi2c, slave_address, 
                                                         &reg_addr, 1, &device_id, 1 ) )
    {
        log_printf( &logger, " %s - Device ID read: %s\r\n", ( char * ) DEVICE_NAME,
                    ( char * ) ( ( DEVICE_ID == device_id ) ? "Success" : "Fail" ) );
    }
    uarttoi2c_gpio_write ( &uarttoi2c, gpio_state );
    if ( UARTTOI2C_OK == uarttoi2c_gpio_read ( &uarttoi2c, &gpio_state ) )
    {
        log_printf( &logger, " GPIO state: 0x%.2X\r\n\n", ( uint16_t ) gpio_state );
        gpio_state = ~gpio_state;
    }
    Delay_ms ( 1000 );
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
