/*!
 * @file main.c
 * @brief AudioAMP 11 Click example
 *
 * # Description
 * This library contains API for the AudioAMP 11 click driver.
 * This demo application shows use of a AudioAMP 11 click board™.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization the app set default settings, 
 * performs power-up sequence, sets the volume level to 0.
 *
 * ## Application Task
 * This example demonstrates the use of the AudioAMP 11 click board™.
 * If GAIN SEL switches are set to 12dB, the app performs circles 
 * switching the volume from -20.5 dB to 12 dB.
 * If the GAIN SEL switches are different, the app sets the volume level to 31 (maximum).
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "audioamp11.h"

static audioamp11_t audioamp11;
static log_t logger;
uint8_t vol_ctrl = AUDIOAMP11_GS_12dB_VOLCTRL_m20_5dB;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    audioamp11_cfg_t audioamp11_cfg;  /**< Click config object. */

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
    audioamp11_cfg_setup( &audioamp11_cfg );
    AUDIOAMP11_MAP_MIKROBUS( audioamp11_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == audioamp11_init( &audioamp11, &audioamp11_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AUDIOAMP11_ERROR == audioamp11_default_cfg ( &audioamp11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "----------------------\r\n" );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{
    uint8_t gain_level = 0;
    uint8_t volume_level = 0;
    
    audioamp11_check_gain( &audioamp11, &gain_level );
    log_printf( &logger, " Gain set to %d dB\r\n", AUDIOAMP11_CALC_GAIN_CONFIG( gain_level ) );
    
    if ( AUDIOAMP11_GAINDEC_12dB == gain_level )
    {
        float volume_table[ 32 ] = { OUTPUT_VOLUME_12dB };
        audioamp11_set_output_volume_level( &audioamp11, vol_ctrl );
        Delay_ms ( 100 );
        
        if ( vol_ctrl > AUDIOAMP11_GS_12dB_VOLCTRL_12dB )
        {
            vol_ctrl--;
        }
        else
        {
            vol_ctrl = AUDIOAMP11_GS_12dB_VOLCTRL_m20_5dB;
        }
        
        audioamp11_get_output_volume_level( &audioamp11, &volume_level );
        log_printf( &logger, " Volume set to  %.1f dB\r\n", volume_table[ volume_level ] );
    }
    else
    {
        audioamp11_set_output_volume_level( &audioamp11, AUDIOAMP11_VOLUME_LEVEL_31 );
        audioamp11_get_output_volume_level( &audioamp11, &volume_level );        
    }
    
    log_printf( &logger, " Volume Level %d: ", ( uint16_t ) ( AUDIOAMP11_VOLUME_LEVEL_0 - volume_level ) );
    for ( uint8_t n_cnt = 0; n_cnt < ( AUDIOAMP11_VOLUME_LEVEL_0 - volume_level ); n_cnt++ )
    {
        log_printf( &logger, "|" );    
    }
    log_printf( &logger, "\r\n----------------------\r\n" );
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
