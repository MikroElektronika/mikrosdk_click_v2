/*!
 * @file main.c
 * @brief Temp-Log 7 Click Example.
 *
 * # Description
 * This example demonstrates the use of Temp-Log 7 click board by reading
 * the temperature in Celsius, then writing the specified data to the memory
 * and reading it back.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration which
 * clears the EEPROM memory, sets the temperature resolution to 16-bit, enables
 * alert interrupt and sets the temperature alerts to 5 degrees Celsius for low
 * and 40 degrees for high level. Other three IO pins are configured as INPUT.
 *
 * ## Application Task
 * Reads the temperature in degrees Celsius and the gpio state. After that writes
 * a desired number of bytes to the memory and then verifies if it is written
 * correctly by reading from the same memory location and displaying the memory
 * content. All data is displayed on the USB UART where you can track changes.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "templog7.h"

#define DEMO_TEXT_MESSAGE           "MikroE - Temp-Log 7 click"
#define STARTING_ADDRESS            0x00

static templog7_t templog7;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    templog7_cfg_t templog7_cfg;  /**< Click config object. */

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
    templog7_cfg_setup( &templog7_cfg );
    TEMPLOG7_MAP_MIKROBUS( templog7_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == templog7_init( &templog7, &templog7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TEMPLOG7_ERROR == templog7_default_cfg ( &templog7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t eeprom_data[ 64 ] = { 0 };
    uint8_t gpio_state = 0;
    float temperature = 0;
    if ( TEMPLOG7_OK == templog7_read_temperature ( &templog7, &temperature ) )
    {
        log_printf( &logger, "\r\n Temperature: %.2f C\r\n", temperature );
    }
    if ( TEMPLOG7_OK == templog7_read_gpio ( &templog7, &gpio_state ) )
    {
        log_printf( &logger, " GPIO state: 0x%.2X\r\n", ( uint16_t ) gpio_state );
    }
    if ( TEMPLOG7_OK == templog7_write_eeprom ( &templog7, STARTING_ADDRESS, DEMO_TEXT_MESSAGE, 
                                                    sizeof ( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf ( &logger, " EEPROM write: %s\r\n", ( uint8_t * ) DEMO_TEXT_MESSAGE );
    }
    if ( TEMPLOG7_OK == templog7_read_eeprom ( &templog7, STARTING_ADDRESS, eeprom_data, 
                                                   sizeof ( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf ( &logger, " EEPROM read: %s\r\n", eeprom_data );
    }
    if ( !templog7_get_alert_pin ( &templog7 ) )
    {
        log_info( &logger, " ALERT detected " );
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
