/*!
 * @file main.c
 * @brief Brushless 20 Click example
 *
 * # Description
 * This example demonstrates the use of the Brushless 20 Click board by driving the 
 * motor in both directions at different speeds.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Drives the motor in both directions and changes the motor speed every 3 seconds approximately.
 * The current driving direction and speed will be displayed on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "brushless20.h"

static brushless20_t brushless20;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless20_cfg_t brushless20_cfg;  /**< Click config object. */

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
    brushless20_cfg_setup( &brushless20_cfg );
    BRUSHLESS20_MAP_MIKROBUS( brushless20_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == brushless20_init( &brushless20, &brushless20_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS20_ERROR == brushless20_default_cfg ( &brushless20 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf ( &logger, "\r\n Driving motor clockwise \r\n" );
    for ( uint8_t speed = BRUSHLESS20_SPEED_MIN; speed <= BRUSHLESS20_SPEED_MAX; speed += 20 )
    {
        log_printf ( &logger, " Speed: %u\r\n", ( uint16_t ) speed );
        if ( BRUSHLESS20_OK != brushless20_drive_motor ( &brushless20, BRUSHLESS20_DIR_CW, speed, 3000 ) )
        {
            log_error ( &logger, " Drive motor " );
        }
    }
    Delay_ms ( 1000 );
    log_printf ( &logger, "\r\n Driving motor counter-clockwise \r\n" );
    for ( uint8_t speed = BRUSHLESS20_SPEED_MIN; speed <= BRUSHLESS20_SPEED_MAX; speed += 20 )
    {
        log_printf ( &logger, " Speed: %u\r\n", ( uint16_t ) speed );
        if ( BRUSHLESS20_OK != brushless20_drive_motor ( &brushless20, BRUSHLESS20_DIR_CCW, speed, 3000 ) )
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
