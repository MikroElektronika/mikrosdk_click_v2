/*!
 * @file main.c
 * @brief SolidSwitch Click example
 *
 * # Description
 * This example demonstrates the use of SolidSwitch click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger and enables the click board.
 *
 * ## Application Task
 * Enables different outputs every 3 seconds and displays all enabled 
 * outputs on USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "solidswitch.h"

static solidswitch_t solidswitch;
static log_t logger;

/**
 * @brief Displays all enabled channels on USB UART.
 * @details This function reads logic state of outputs and 
 *          displays all enabled channels on USB UART.
 * 
 * @return None.
 * @note None.
 */
static void solidswitch_display_enabled_channels ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    solidswitch_cfg_t solidswitch_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.

    solidswitch_cfg_setup( &solidswitch_cfg );
    SOLIDSWITCH_MAP_MIKROBUS( solidswitch_cfg, MIKROBUS_1 );
    err_t init_flag = solidswitch_init( &solidswitch, &solidswitch_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    solidswitch_default_cfg ( &solidswitch );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    solidswitch_write_single ( &solidswitch, SOLIDSWITCH_ENABLE_OUT0 | SOLIDSWITCH_ENABLE_OUT1 );
    solidswitch_display_enabled_channels( );
    Delay_ms ( 3000 );
    solidswitch_write_single ( &solidswitch, SOLIDSWITCH_ENABLE_OUT6 | SOLIDSWITCH_ENABLE_OUT7 );
    solidswitch_display_enabled_channels( );
    Delay_ms ( 3000 );
    solidswitch_write_single ( &solidswitch, SOLIDSWITCH_ENABLE_ALL_OUTPUTS );
    solidswitch_display_enabled_channels( );
    Delay_ms ( 3000 );
    solidswitch_write_single ( &solidswitch, SOLIDSWITCH_DISABLE_ALL_OUTPUTS );
    solidswitch_display_enabled_channels( );
    Delay_ms ( 3000 );
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

static void solidswitch_display_enabled_channels ( void )
{
    uint8_t logic_state;
    uint8_t enabled_flag = 0;
    
    solidswitch_read_single ( &solidswitch, &logic_state );
    log_printf( &logger, " Outputs enabled: " );
    for ( uint8_t cnt = 0; cnt < 8; cnt++ )
    {
        if ( logic_state & 1 )
        {
            if ( enabled_flag == 1 )
            {
                log_printf( &logger, ", %u", ( uint16_t ) cnt );
            }
            else
            {
                log_printf( &logger, " %u", ( uint16_t ) cnt );
            }
            enabled_flag = 1;
        }
        logic_state >>= 1;
    }
    
    if ( enabled_flag == 0 )
    {
        log_printf( &logger, " none" );
    }
    log_printf( &logger, "\r\n-----------------------\r\n" );
}

// ------------------------------------------------------------------------ END
