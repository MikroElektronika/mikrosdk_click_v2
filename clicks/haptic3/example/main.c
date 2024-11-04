/*!
 * @file main.c
 * @brief HAPTIC3 Click example
 *
 * # Description
 * This example demonstrates the use of HAPTIC 3 Click board by controlling
 * the attached motor vibration level.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Changes the motor vibration level every 2 seconds from MAX to MIN, 
 * and displays the currently set level on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "haptic3.h"

static haptic3_t haptic3;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    haptic3_cfg_t haptic3_cfg;  /**< Click config object. */

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
    haptic3_cfg_setup( &haptic3_cfg );
    HAPTIC3_MAP_MIKROBUS( haptic3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == haptic3_init( &haptic3, &haptic3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HAPTIC3_ERROR == haptic3_default_cfg ( &haptic3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float vibration_level;
    if ( HAPTIC3_OK == haptic3_set_vibration_level ( &haptic3, HAPTIC3_VIBRATION_LEVEL_MAX ) )
    {
        if ( HAPTIC3_OK == haptic3_get_vibration_level ( &haptic3, &vibration_level ) )
        {
            log_printf( &logger, " Vibration level: %.3f \r\n\n", vibration_level );
        }
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    if ( HAPTIC3_OK == haptic3_set_vibration_level ( &haptic3, HAPTIC3_VIBRATION_LEVEL_MIN ) )
    {
        if ( HAPTIC3_OK == haptic3_get_vibration_level ( &haptic3, &vibration_level ) )
        {
            log_printf( &logger, " Vibration level: %.3f \r\n\n", vibration_level );
        }
    }
    Delay_ms ( 1000 );
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
