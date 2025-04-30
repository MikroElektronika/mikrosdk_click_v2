/*!
 * @file main.c
 * @brief IR Sense 6 Click example
 *
 * # Description
 * This example demonstrates the functionality of the IR Sense 6 Click board, 
 * which measures ambient and object temperatures using an infrared sensor. 
 * The example initializes the device and continuously logs temperature readings.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the driver and enables the device.
 *
 * ## Application Task
 * Continuously reads and logs ambient and object temperatures. 
 * The readings are displayed in degrees Celsius.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "irsense6.h"

static irsense6_t irsense6;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irsense6_cfg_t irsense6_cfg;  /**< Click config object. */

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
    irsense6_cfg_setup( &irsense6_cfg );
    IRSENSE6_MAP_MIKROBUS( irsense6_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == irsense6_init( &irsense6, &irsense6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    irsense6_enable_device ( &irsense6 );
    Delay_ms ( 1000 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float obj_temp = 0;
    float amb_temp = 0;
    if ( IRSENSE6_OK == irsense6_read_data ( &irsense6, &obj_temp, &amb_temp ) )
    {
        log_printf ( &logger, " Ambient temperature: %.1f degC\r\n", amb_temp );
        log_printf ( &logger, " Object temperature: %.1f degC\r\n\n", obj_temp );
        Delay_ms ( 500 );
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
