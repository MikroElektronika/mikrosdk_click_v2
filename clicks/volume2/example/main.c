/*!
 * @file main.c
 * @brief Volume2 Click example
 *
 * # Description
 * This example shows how Volume 2 click board can be used
 * for controlling the audio channels. Thanks to this, a
 * simple audio effect is created by switching volume from
 * right to left and vice versa.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * UART LOG and I2C drivers are initialized, following the
 * default configuration. By default, both channels are set
 * to 9 dB gain with zero cross detection enabled.
 *
 * ## Application Task
 * The task performs and effect of switching the volume
 * from right to left channel and vice versa. Like playing
 * ping-pong with the sound.
 *
 * @author Stefan Nikolic
 *
 */

#include "board.h"
#include "log.h"
#include "volume2.h"

static volume2_t volume2;
static log_t logger;

static volume2_vol_data_t volume_upd_data;
static uint8_t rising_vol;
static uint8_t max_atten = 60;

void application_init ( void ) {
    log_cfg_t log_cfg;          /**< Logger config object. */
    volume2_cfg_t volume2_cfg;  /**< Click config object. */

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

    volume2_cfg_setup( &volume2_cfg );
    VOLUME2_MAP_MIKROBUS( volume2_cfg, MIKROBUS_1 );
    err_t init_flag = volume2_init( &volume2, &volume2_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    volume2_default_cfg( &volume2 );
    Delay_ms( 100 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    for ( rising_vol = 0 ; rising_vol < max_atten ; rising_vol++ ) {
        volume_upd_data.attenuation_ch1 = rising_vol;
        volume_upd_data.attenuation_ch2 = max_atten - rising_vol;
        volume2_update_vol_data( &volume2, volume_upd_data );
        Delay_ms( 50 );
    }
    Delay_ms( 1000 );
    for ( rising_vol = 0 ; rising_vol < max_atten ; rising_vol++ ) {
        volume_upd_data.attenuation_ch1 = max_atten - rising_vol;
        volume_upd_data.attenuation_ch2 = rising_vol;
        volume2_update_vol_data( &volume2, volume_upd_data );
        Delay_ms( 50 );
    }
    Delay_ms( 1000 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
