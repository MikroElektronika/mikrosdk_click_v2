/*!
 * @file main.c
 * @brief 1-Wire I2C Click Example.
 *
 * # Description
 * This example demonstrates the use of 1-Wire I2C Click board by reading
 * the temperature measurement from connected Thermo 4 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads the temperature measurement from connected Thermo 4 Click board and
 * displays the results on the USB UART once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "c1wirei2c.h"

// Thermo 4 device settings
#define DEVICE_NAME                "Thermo 4 Click"
#define DEVICE_SLAVE_ADDRESS       0x48
#define DEVICE_REG_TEMPERATURE     0x00
#define DEVICE_TEMPERATURE_RES     0.125f

static c1wirei2c_t c1wirei2c;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c1wirei2c_cfg_t c1wirei2c_cfg;  /**< Click config object. */

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
    c1wirei2c_cfg_setup( &c1wirei2c_cfg );
    C1WIREI2C_MAP_MIKROBUS( c1wirei2c_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == c1wirei2c_init( &c1wirei2c, &c1wirei2c_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C1WIREI2C_ERROR == c1wirei2c_default_cfg ( &c1wirei2c ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float temperature = 0;
    uint8_t reg_data[ 2 ] = { 0 };
    uint8_t reg_addr = DEVICE_REG_TEMPERATURE;
    if ( ( C1WIREI2C_OK == c1wirei2c_write_data ( &c1wirei2c, DEVICE_SLAVE_ADDRESS, &reg_addr, 1 ) ) && 
         ( C1WIREI2C_OK == c1wirei2c_read_data_stop ( &c1wirei2c, DEVICE_SLAVE_ADDRESS, reg_data, 2 ) ) )
    {
        temperature = ( ( ( int16_t ) ( ( ( uint16_t ) reg_data[ 0 ] << 8 ) | 
                                                       reg_data[ 1 ] ) ) >> 5 ) * DEVICE_TEMPERATURE_RES;
        log_printf( &logger, "\r\n%s - Temperature: %.3f degC\r\n", ( char * ) DEVICE_NAME, temperature );
    }
    else
    {
        log_error( &logger, "%s - no communication!\r\n", ( char * ) DEVICE_NAME );
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
