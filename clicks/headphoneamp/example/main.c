/*!
 * @file main.c
 * @brief Headphone AMP Click Example.
 *
 * # Description
 * This library contains API for the Headphone AMP click driver.
 * This demo application shows use of a Headphone AMP click board™.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of GPIO module and log UART.
 * After driver initialization the app set default settings, 
 * performs power-up sequence, sets a the sound volume of -12 dB.
 *
 * ## Application Task
 * This is an example that shows the use of Headphone AMP click board™.
 * The app performs circles the volume from -12 dB to 3 dB back and forth,
 * increase/decrement by 3dB.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "headphoneamp.h"

static headphoneamp_t headphoneamp;   /**< Headphone AMP Click driver object. */
static log_t logger;                  /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;                    /**< Logger config object. */
    headphoneamp_cfg_t headphoneamp_cfg;  /**< Click config object. */

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

    headphoneamp_cfg_setup( &headphoneamp_cfg );
    HEADPHONEAMP_MAP_MIKROBUS( headphoneamp_cfg, MIKROBUS_1 );
    if ( headphoneamp_init( &headphoneamp, &headphoneamp_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    headphoneamp_default_cfg ( &headphoneamp );
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
    
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "    Performs Power-up\r\n" );
    headphoneamp_power_up( &headphoneamp );
    Delay_ms( 100 );
    
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "  Set volume gain -12dB\r\n", HEADPHONEAMP_SOUND_VOLUME_NEG_12_dB );
    headphoneamp_set_sound_volume( &headphoneamp, HEADPHONEAMP_SOUND_VOLUME_NEG_12_dB ); 
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms( 5000 );
}

void application_task ( void ) 
{
    for ( uint8_t n_cnt = 0; n_cnt < 5; n_cnt++ ) {
        log_printf( &logger, "    Turning volume up\r\n" );
        headphoneamp_volume_up ( &headphoneamp ); 
        Delay_ms( 2000 );    
    }
    
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms( 5000 );
    
    for ( uint8_t n_cnt = 0; n_cnt < 5; n_cnt++ ) {
        log_printf( &logger, "   Turning volume down\r\n" );
        headphoneamp_volume_down ( &headphoneamp ); 
        Delay_ms( 2000 );    
    }
       
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms( 5000 );
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
