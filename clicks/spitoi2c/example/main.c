/*!
 * @file main.c
 * @brief SPI to I2C Click example
 *
 * # Description
 * This example demonstrates the use of SPI to I2C Click board by reading the manufacturer ID
 * of a 3D Hall 11 Click board connected to the I2C port and controlling the GPIO pins.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default config which enables
 * the device and sets the GPIO pins 0-2 as push-pull output and others as input.
 * Then sets the I2C clock to 99KHz, I2C address to 127 and disables I2C timeout.
 * After that, reads and displays the chip firmware version.
 *
 * ## Application Task
 * Reads the manufacturer ID of a 3D Hall 11 Click board connected to the I2C port, 
 * toggles the output pins and displays the GPIO port state. The results will
 * be displayed on the USB UART approximately once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "spitoi2c.h"

// I2C target device configuration
#define DEVICE_NAME                 "3D Hall 11 Click"
#define DEVICE_SLAVE_ADDRESS        0x35
#define DEVICE_REG_MAN_ID           0x0E
#define DEVICE_MAN_ID_0             0x49
#define DEVICE_MAN_ID_1             0x54

static spitoi2c_t spitoi2c;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    spitoi2c_cfg_t spitoi2c_cfg;  /**< Click config object. */

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
    spitoi2c_cfg_setup( &spitoi2c_cfg );
    SPITOI2C_MAP_MIKROBUS( spitoi2c_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == spitoi2c_init( &spitoi2c, &spitoi2c_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SPITOI2C_ERROR == spitoi2c_default_cfg ( &spitoi2c ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint8_t version[ 16 ] = { 0 };
    if ( SPITOI2C_OK == spitoi2c_read_version ( &spitoi2c, version ) )
    {
        log_printf( &logger, " Firmware version: %s\r\n", version );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static uint8_t gpio_state = SPITOI2C_NO_PIN_MASK;
    uint8_t reg_addr = DEVICE_REG_MAN_ID;
    uint8_t man_id[ 2 ] = { 0 };
    err_t error_flag = spitoi2c_i2c_read_after_write ( &spitoi2c, DEVICE_SLAVE_ADDRESS, 
                                                       &reg_addr, 1, man_id, 2 );
    log_printf( &logger, " %s - ID read: %s\r\n", ( char * ) DEVICE_NAME,
                ( char * ) ( ( ( DEVICE_MAN_ID_0 == man_id[ 0 ] ) && 
                               ( DEVICE_MAN_ID_1 == man_id[ 1 ] ) && 
                               ( SPITOI2C_OK == error_flag ) ) ? "Success" : "Fail" ) );
    if ( ( SPITOI2C_OK == spitoi2c_gpio_write ( &spitoi2c, gpio_state ) ) && 
         ( SPITOI2C_OK == spitoi2c_gpio_read ( &spitoi2c, &gpio_state ) ) )
    {
        log_printf( &logger, " GPIO state: 0x%.2X\r\n\n", ( uint16_t ) gpio_state );
        gpio_state = ~gpio_state;
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
