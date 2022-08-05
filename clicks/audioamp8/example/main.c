/*!
 * @file main.c
 * @brief AudioAmp8 Click example
 *
 * # Description
 * This library contains API for AudioAmp 8 Click driver.
 * The library initializes and defines the I2C bus drivers 
 * to write and read data from registers. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C  module, log UART, and additional pins. 
 * After the driver init and executing a default configuration, 
 * the app performs a BTL signal configuration, configures power mode
 * and configures power mode profile.
 *
 * ## Application Task
 * This is an example that shows the use of a AudioAmp 8 Click board™.
 * Displays status monitoring for channel 0 or channel 1.
 * This task repeats once every 2 seconds.
 * 
 * ## Additional Function
 * - static void channel_status_monitoring ( void )  - The function displays the status monitoring channel.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "audioamp8.h"

static audioamp8_t audioamp8;
static log_t logger;
static audioamp8_pwr_mon_cfg_t pwr_mode;
static audioamp8_pwr_mod_profile_cfg_t pm_profile;
static audioamp8_monitor_channel_t ch_mon;
static uint8_t ch_sel;

static void channel_status_monitoring ( void ) 
{
    audioamp8_channel_monitoring( &audioamp8, ch_sel, &ch_mon );
    Delay_ms( 100 );
    log_printf( &logger, " Frequency mode    : %d\r\n", ( uint16_t ) ch_mon.freq_mode );
    log_printf( &logger, " Power mode        : %d\r\n", ( uint16_t ) ch_mon.pwr_mode );

    log_printf( &logger, " Channel %d mute    : ", ( uint16_t ) ch_sel );
    if ( ch_mon.mute_mon == AUDIOAMP8_SET_ENABLE )
    {
        log_printf( &logger, "ON\r\n" );    
    }
    else
    {
        log_printf( &logger, "OFF\r\n" );    
    }

    log_printf( &logger, " Channel %d VDD     : ", ( uint16_t ) ch_sel );
    if ( ch_mon.vdd_mon == AUDIOAMP8_SET_ENABLE )
    {
        log_printf( &logger, "ON\r\n" );    
    }
    else
    {
        log_printf( &logger, "OFF\r\n" );    
    }

    log_printf( &logger, " Channel %d PVDD    : ", ( uint16_t ) ch_sel );
    if ( ch_mon.pvdd_mon == AUDIOAMP8_SET_ENABLE )
    {
        log_printf( &logger, "ON\r\n" );    
    }
    else
    {
        log_printf( &logger, "OFF\r\n" );    
    }

    log_printf( &logger, " Cfly1 protection  : " );
    if ( ch_mon.cfly1_mon == AUDIOAMP8_SET_ENABLE )
    {
        log_printf( &logger, "ON\r\n" );    
    }
    else
    {
        log_printf( &logger, "OFF\r\n" );    
    }

    log_printf( &logger, " Cfly2 protection  : " );
    if ( ch_mon.cfly2_mon == AUDIOAMP8_SET_ENABLE )
    {
        log_printf( &logger, "ON\r\n" );    
    }
    else
    {
        log_printf( &logger, "OFF\r\n" );    
    }

    log_printf( &logger, " Current protection: " );
    if ( ch_mon.ovc_prot == AUDIOAMP8_SET_ENABLE )
    {
        log_printf( &logger, "ON\r\n" );    
    }
    else
    {
        log_printf( &logger, "OFF\r\n" );    
    }

    log_printf( &logger, " Modulation index  : %d\r\n", ( uint16_t ) ch_mon.modul_index_mon );
    log_printf( &logger, "-------------------------\r\n" );
}

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    audioamp8_cfg_t audioamp8_cfg;  /**< Click config object. */

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
    audioamp8_cfg_setup( &audioamp8_cfg );
    AUDIOAMP8_MAP_MIKROBUS( audioamp8_cfg, MIKROBUS_1 );
    err_t init_flag = audioamp8_init( &audioamp8, &audioamp8_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    audioamp8_default_cfg ( &audioamp8 );
    log_info( &logger, " Application Task " );

    audioamp8_btl_config( &audioamp8 );
    Delay_ms( 100 );

    pwr_mode.manual_pm = AUDIOAMP8_SET_MANUAL_PWR_MODE;
    pwr_mode.pm_man    = AUDIOAMP8_PM_MAN_3;
    pwr_mode.mthr_1to2 = AUDIOAMP8_SET_MTHR_1TO2_DEFAULT;
    pwr_mode.mthr_2to1 = AUDIOAMP8_SET_MTHR_2TO1_DEFAULT;
    pwr_mode.mthr_2to3 = AUDIOAMP8_SET_MTHR_2TO3_DEFAULT;
    pwr_mode.mthr_3to2 = AUDIOAMP8_SET_MTHR_3TO2_DEFAULT;
    audioamp8_set_config_power_mode( &audioamp8, pwr_mode );
    Delay_ms( 100 );

    pm_profile.pm_profile = AUDIOAMP8_PM_PROFILE_3; 
    pm_profile.pm3_man_sh = AUDIOAMP8_SCHEME_C;
    audioamp8_set_config_power_mode_profile( &audioamp8, pm_profile );
    Delay_ms( 100 );

    audioamp8_set_mute( &audioamp8, AUDIOAMP8_SET_DISABLE );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms( 1000 );
}

void application_task ( void ) 
{
    ch_sel = AUDIOAMP8_SET_MON_CH_0;
    channel_status_monitoring( );
    Delay_ms( 1000 );
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
