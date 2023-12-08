/*!
 * \file 
 * \brief I2C Isolator 2 Click example
 * 
 * # Description
 * This example showcases how to initialize, configure and use the I2C Isolator 2 click module.
 * The click provides I2C lines and power isolation for slave devices. In order for this 
 * example to work, you need the EEPROM 3 click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and enables the power output.
 * 
 * ## Application Task  
 * Writes the desired message to EEPROM 3 click board and reads it back every 2 seconds.
 * All data is being displayed on the USB UART where you can track the program flow.
 * 
 * @note
 * Make sure to provide the VCC power supply on VCC pin and EEPROM 3 click.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "i2cisolator2.h"

// ------------------------------------------------------------------ VARIABLES

#define EEPROM3_MEMORY_ADDRESS   0x10000ul
#define EEPROM3_SLAVE_ADDRESS    0x54
#define EEPROM3_DEMO_TEXT        "MikroE - I2C Isolator 2 with EEPROM 3 click!"

static i2cisolator2_t i2cisolator2;
static log_t logger;

// ------------------------------------------------------ ADDITIONAL FUNCTIONS

err_t eeprom3_write_page( uint32_t address, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 257 ] = { 0 };
    uint8_t slave_addr = ( uint8_t ) ( ( address >> 16 ) & 0x03 ) | EEPROM3_SLAVE_ADDRESS;
    i2cisolator2_set_slave_address ( &i2cisolator2, slave_addr );
    data_buf[ 0 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( address & 0xFF );
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 2 ] = data_in[ cnt ];
    }
    return i2cisolator2_write( &i2cisolator2, data_buf, len + 2 );
}

err_t eeprom3_read_page( uint32_t address, uint8_t *data_out, uint8_t len )
{
    uint8_t data_buf[ 2 ] = { 0 };
    uint8_t slave_addr = ( uint8_t ) ( ( address >> 16 ) & 0x03 ) | EEPROM3_SLAVE_ADDRESS;
    i2cisolator2_set_slave_address ( &i2cisolator2, slave_addr );
    data_buf[ 0 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( address & 0xFF );
    err_t error_flag = i2cisolator2_write( &i2cisolator2, data_buf, 2 );
    error_flag |= i2cisolator2_read( &i2cisolator2, data_out, len );
    return error_flag;
}
// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    i2cisolator2_cfg_t cfg;

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
    i2cisolator2_cfg_setup( &cfg );
    I2CISOLATOR2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2cisolator2_init( &i2cisolator2, &cfg );
    
    i2cisolator2_enable_power( &i2cisolator2, I2CISOLATOR2_POWER_ENABLE );
    Delay_ms( 100 );

    log_info( &logger, " Application Task " );
}

void application_task ( )
{
    uint8_t read_buf[ 100 ] = { 0 };
    if ( I2CISOLATOR2_OK == eeprom3_write_page ( EEPROM3_MEMORY_ADDRESS, EEPROM3_DEMO_TEXT, 
                                                 strlen( EEPROM3_DEMO_TEXT ) ) )
    {
        log_printf( &logger, " Demo text message is written to EEPROM 3 click!\r\n" );
    }
    Delay_ms( 1000 );
    
    if ( I2CISOLATOR2_OK == eeprom3_read_page ( EEPROM3_MEMORY_ADDRESS, read_buf, 
                                                strlen( EEPROM3_DEMO_TEXT ) ) )
    {
        read_buf[ strlen( EEPROM3_DEMO_TEXT ) ] = 0;
        log_printf( &logger, " Read data: \"%s\"\r\n\n", read_buf );
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
