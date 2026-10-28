/*!
 * @file main.c
 * @brief UNI Hall 2 Click Example.
 *
 * # Description
 * This example demonstrates the use of the UNI Hall 2 Click board by reading
 * and displaying the magnetic flux density measured by the on-board A31015
 * linear Hall-effect sensor. The field is actuated by the magnetic switch
 * mounted above the sensor.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads the magnetic flux density in Gauss once per second and logs the result
 * on the USB UART.
 *
 * @note
 * If the EN SEL jumper (JP2) is in the VCC position, the device is always
 * enabled and functions unihall2_enable_device and unihall2_disable_device have no effect.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "unihall2.h"

#ifndef MIKROBUS_POSITION_UNIHALL2
    #define MIKROBUS_POSITION_UNIHALL2 MIKROBUS_1
#endif

static unihall2_t unihall2;   /**< UNI Hall 2 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    unihall2_cfg_t unihall2_cfg;  /**< Click config object. */

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
    unihall2_cfg_setup( &unihall2_cfg );
    UNIHALL2_MAP_MIKROBUS( unihall2_cfg, MIKROBUS_POSITION_UNIHALL2 );
    if ( ADC_ERROR == unihall2_init( &unihall2, &unihall2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float field = 0;

    if ( UNIHALL2_OK == unihall2_read_field( &unihall2, &field ) )
    {
        log_printf( &logger, " Magnetic flux density: %.2f G\r\n", field );
    }
    else
    {
        log_printf( &logger, " Reading magnetic flux density ERROR.\r\n" );
    }

    Delay_ms( 1000 );
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
