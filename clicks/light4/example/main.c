/*!
 * @file main.c
 * @brief Light 4 Click example
 *
 * # Description
 * This example demonstrates the use of Light 4 Click board by measuring 
 * the ambient light level in Lux.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, performs the Click default configuration 
 * and checking I2C Communication by reading Device ID.
 *
 * ## Application Task
 * Reading channel 0 ambient light level in lux once per 
 * second and displaying it on the UART terminal.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "light4.h"

static light4_t light4;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    light4_cfg_t light4_cfg;  /**< Click config object. */

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
    light4_cfg_setup( &light4_cfg );
    LIGHT4_MAP_MIKROBUS( light4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == light4_init( &light4, &light4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LIGHT4_ERROR == light4_default_cfg ( &light4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    uint8_t dev_id = 0;
    light4_read_reg ( &light4, LIGHT4_REG_ID, &dev_id ); 
    if ( LIGHT4_DEVICE_ID == dev_id )
    {
        log_printf( &logger, " Device ID: 0x%.2X \r\n", ( uint16_t ) dev_id );
    }
    else
    {
        log_error( &logger, " Read error." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float channel_data = 0;
    err_t error_flag;

    error_flag = light4_read_channel_data( &light4, LIGHT4_CHANNEL0_SEL, &channel_data );
    if( LIGHT4_OK == error_flag )
    {
        log_printf( &logger, " Data: %.2f Lux \r\n", channel_data );
    }
    else if ( LIGHT4_ANALOG_SAT == error_flag )
    {
        log_error( &logger, " Analog saturation \r\n" );
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
