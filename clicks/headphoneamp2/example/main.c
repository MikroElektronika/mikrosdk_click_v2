/*!
 * @file main.c
 * @brief Headphone AMP 2 Click example
 *
 * # Description
 * This example demonstrates the use of the Headphone AMP 2 Click board™, 
 * the headphone amplifier with BassMax and volume control.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C module and log UART.
 * After driver initialization, the app sets the default configuration.
 *
 * ## Application Task
 * This example demonstrates the use of the Headphone AMP 2 Click board™.
 * The application wakes up the device, enables BassMax and Maximum Gain modes, 
 * and switches the sound volume from level 1 to the max level.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "headphoneamp2.h"

static headphoneamp2_t headphoneamp2;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    headphoneamp2_cfg_t headphoneamp2_cfg;  /**< Click config object. */

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
    headphoneamp2_cfg_setup( &headphoneamp2_cfg );
    HEADPHONEAMP2_MAP_MIKROBUS( headphoneamp2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == headphoneamp2_init( &headphoneamp2, &headphoneamp2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HEADPHONEAMP2_ERROR == headphoneamp2_default_cfg ( &headphoneamp2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    static headphoneamp2_cmd_t cmd_ctrl;
    cmd_ctrl.wakes_up = HEADPHONEAMP2_CMD_ENABLE;
    cmd_ctrl.bass_max = HEADPHONEAMP2_CMD_ENABLE;
    cmd_ctrl.gain_max = HEADPHONEAMP2_CMD_ENABLE;
    cmd_ctrl.volume   = HEADPHONEAMP2_VOL_MUTE;
    
    log_printf( &logger, " Volume : " );
    for ( uint8_t volume = HEADPHONEAMP2_VOL_LVL_1; volume <= HEADPHONEAMP2_VOL_LVL_MAX; volume++ )
    {
        cmd_ctrl.volume = volume;
        if ( HEADPHONEAMP2_OK == headphoneamp2_set_command( &headphoneamp2, cmd_ctrl ) )
        {
            log_printf( &logger, "|" );
        }
        Delay_ms( 1000 );
    }
    log_printf( &logger, "\r\n-------------------------\r\n" );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
