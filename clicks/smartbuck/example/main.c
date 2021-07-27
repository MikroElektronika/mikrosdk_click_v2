/*!
 * \file 
 * \brief SMARTBUCK Click example
 * 
 * # Description
 * This application reads voltage, current, and power from all available channels.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C interface and logger and peforms the click default configuration.
 * 
 * ## Application Task  
 * Sends command for updating data registers with new converted data, 
 * then waits 500ms and after that reads new data from data registers. 
 * In this way we can get voltage, current and power data from activated channels.
 * Results are being logged on USB UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "smartbuck.h"

// ------------------------------------------------------------------ VARIABLES

static smartbuck_t smartbuck;
static log_t logger;

float voltage_res[ 4 ];
float current_res[ 4 ];
float power_res[ 4 ];
uint8_t check_byte;
uint8_t cnt;
uint8_t index;
char text[ 50 ];

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

//Checks which channel is activated (from CH1 to CH4) and logs text on uart
void channel_log()
{
    switch ( check_byte )
    {
        case 0x80 :
        {
            log_printf( &logger, "\r\nCH1:\t" );
            break;
        }
        case 0x40 :
        {
            log_printf( &logger, "\r\nCH2:\t" );
            break;
        }
        case 0x20 :
        {
            log_printf( &logger, "\r\nCH3:\t" );
            break;
        }
        case 0x10 :
        {
            log_printf( &logger, "\r\nCH4:\t" );
            break;
        }
        default :
        {
            break;
        }
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    smartbuck_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    smartbuck_cfg_setup( &cfg );
    SMARTBUCK_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    smartbuck_init( &smartbuck, &cfg );
    smartbuck_default_cfg( &smartbuck );
}                                                                                                                                            

void application_task ( void )
{
    smartbuck_send_cmd_pac( &smartbuck, SMARTBUCK_REFRESH_V_CMND );
    Delay_ms( 500 );
    smartbuck_get_data( &smartbuck, &voltage_res[ 0 ], &current_res[ 0 ], &power_res[ 0 ] );
    
    check_byte = 0x80;
    index = 0;
    
    for ( cnt = 0; cnt < 4; cnt++ )
    {
        if ( ( smartbuck.enabled_chann & check_byte ) == 0 )
        {
            channel_log();
            
            log_printf( &logger, "U: %.2f V    ", voltage_res[ index ] );
            log_printf( &logger, "I: %.2f mA    ", current_res[ index ] );
            log_printf( &logger, "P: %.2f mW    ", power_res[ index ] );
            
            index++;
        }
        check_byte >>= 1;
    }
    
    log_printf( &logger, "\n");
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
