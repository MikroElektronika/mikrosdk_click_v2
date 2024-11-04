/*!
 * @file main.c
 * @brief Haptic 4 Click example
 *
 * # Description
 * This example demonstrates the use of Haptic 4 Click board by controlling
 * the attached motor vibration level.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Changes the motor vibration level every 2 seconds between MAX and MIN, 
 * and displays the currently set level on the USB UART.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "haptic4.h"

static haptic4_t haptic4;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    haptic4_cfg_t haptic4_cfg;  /**< Click config object. */

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
    haptic4_cfg_setup( &haptic4_cfg );
    HAPTIC4_MAP_MIKROBUS( haptic4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == haptic4_init( &haptic4, &haptic4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HAPTIC4_ERROR == haptic4_default_cfg ( &haptic4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float vibration_level;
    if ( HAPTIC4_OK == haptic4_set_vibration_level ( &haptic4, HAPTIC4_VIBRATION_LEVEL_MAX ) )
    {
        if ( HAPTIC4_OK == haptic4_get_vibration_level ( &haptic4, &vibration_level ) )
        {
            log_printf( &logger, " Vibration level: %.3f \r\n\n", vibration_level );
        }
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    if ( HAPTIC4_OK == haptic4_set_vibration_level ( &haptic4, HAPTIC4_VIBRATION_LEVEL_MIN ) )
    {
        if ( HAPTIC4_OK == haptic4_get_vibration_level ( &haptic4, &vibration_level ) )
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
