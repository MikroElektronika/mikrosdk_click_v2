/*!
 * @file main.c
 * @brief Brushless 27 Click example
 *
 * # Description
 * This example demonstrates the use of the Brushless 27 click board by driving the 
 * motor in both directions at different speeds.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Drives the motor in both directions and changes the motor speed approximately every 2 seconds.
 * The driving direction and speed will be displayed on the USB UART.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "brushless27.h"

static brushless27_t brushless27;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless27_cfg_t brushless27_cfg;  /**< Click config object. */

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
    brushless27_cfg_setup( &brushless27_cfg );
    BRUSHLESS27_MAP_MIKROBUS( brushless27_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == brushless27_init( &brushless27, &brushless27_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS27_ERROR == brushless27_default_cfg ( &brushless27 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf ( &logger, "\r\n Driving motor clockwise \r\n" );
    for ( uint8_t speed = BRUSHLESS27_SPEED_MIN; speed <= BRUSHLESS27_SPEED_MAX; speed += 20 )
    {
        log_printf ( &logger, " Speed gain: %u\r\n", ( uint16_t ) speed );
        if ( BRUSHLESS27_OK != brushless27_drive_motor ( &brushless27, BRUSHLESS27_DIR_CW, speed, 2000 ) )
        {
            log_error ( &logger, " Drive motor " );
        }
    }
    Delay_ms ( 1000 );
    
    log_printf ( &logger, "\r\n Driving motor counter-clockwise \r\n" );
    for ( uint8_t speed = BRUSHLESS27_SPEED_MIN; speed <= BRUSHLESS27_SPEED_MAX; speed += 20 )
    {
        log_printf ( &logger, " Speed gain: %u\r\n", ( uint16_t ) speed );
        if ( BRUSHLESS27_OK != brushless27_drive_motor ( &brushless27, BRUSHLESS27_DIR_CCW, speed, 2000 ) )
        {
            log_error ( &logger, " Drive motor " );
        }
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
