/*!
 * @file main.c
 * @brief Brushless 26 Click example
 *
 * # Description
 * This example demonstrates the use of the Brushless 26 click board by driving the 
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
#include "brushless26.h"

static brushless26_t brushless26;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless26_cfg_t brushless26_cfg;  /**< Click config object. */

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
    brushless26_cfg_setup( &brushless26_cfg );
    BRUSHLESS26_MAP_MIKROBUS( brushless26_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == brushless26_init( &brushless26, &brushless26_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS26_ERROR == brushless26_default_cfg ( &brushless26 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task");
}

void application_task ( void ) 
{
    log_printf ( &logger, "\r\n Driving motor clockwise \r\n" );
    for ( uint8_t speed = BRUSHLESS26_SPEED_MIN; speed <= BRUSHLESS26_SPEED_MAX; speed += 20 )
    {
        log_printf ( &logger, " Speed gain: %u\r\n", ( uint16_t ) speed );
        if ( BRUSHLESS26_OK != brushless26_drive_motor ( &brushless26, BRUSHLESS26_DIR_CW, speed, 2000 ) )
        {
            log_error ( &logger, " Drive motor " );
        }
    }
    Delay_ms ( 1000 );
    
    log_printf ( &logger, "\r\n Driving motor counter-clockwise \r\n" );
    for ( uint8_t speed = BRUSHLESS26_SPEED_MIN; speed <= BRUSHLESS26_SPEED_MAX; speed += 20 )
    {
        log_printf ( &logger, " Speed gain: %u\r\n", ( uint16_t ) speed );
        if ( BRUSHLESS26_OK != brushless26_drive_motor ( &brushless26, BRUSHLESS26_DIR_CCW, speed, 2000 ) )
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
