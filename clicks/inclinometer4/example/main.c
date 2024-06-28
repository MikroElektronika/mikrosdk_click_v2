/*!
 * @file main.c
 * @brief Inclinometer 4 Click example
 *
 * # Description
 * This example demonstrates the use of Inclinometer 4 click board by reading and displaying 
 * accel data (X, Y, and Z axis) as well as temperature measurements on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration which enables data ready
 * interrupt on INT2 pin and sets full scale range to +/-2G and output data rate to 160ms.
 *
 * ## Application Task
 * Waits for a data ready interrupt, then reads and displays the accel data (X, Y, and Z axis)
 * as well as temperature measurements on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "inclinometer4.h"

static inclinometer4_t inclinometer4;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    inclinometer4_cfg_t inclinometer4_cfg;  /**< Click config object. */

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
    inclinometer4_cfg_setup( &inclinometer4_cfg );
    INCLINOMETER4_MAP_MIKROBUS( inclinometer4_cfg, MIKROBUS_1 );
    err_t init_flag = inclinometer4_init( &inclinometer4, &inclinometer4_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( INCLINOMETER4_ERROR == inclinometer4_default_cfg ( &inclinometer4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    inclinometer4_data_t accel_data;
    
    // Wait for a data ready interrupt
    while ( inclinometer4_get_int2_pin ( &inclinometer4 ) );

    if ( INCLINOMETER4_OK == inclinometer4_get_data ( &inclinometer4, &accel_data ) )
    {
        log_printf( &logger, " X: %.3f g\r\n", accel_data.x );
        log_printf( &logger, " Y: %.3f g\r\n", accel_data.y );
        log_printf( &logger, " Z: %.3f g\r\n", accel_data.z );
        log_printf( &logger, " Temperature: %d degC\r\n\n", ( int16_t ) accel_data.temperature );
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
