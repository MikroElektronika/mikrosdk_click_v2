/*!
 * \file 
 * \brief SMARTBUCK Click example
 * 
 * # Description
 * <DEMOAPP_DESCRIPTION>
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C interface and peforms the click configuration to work in Single-Shot Mode
 * with signed averaged data of 64 samples. CH1 and CH3 are only activated and included in conversion cycle.
 * 
 * ## Application Task  
 * Sends command to update data registers with new converted data, waits one second and after that reads
 * new data from data registers. On this way user can get voltage, current and power data for activated channels.
 * Results for activated channels logs on uart terminal.
 * 
 * *note:* 
 * If we want to update registers with new converted data, after at least one conversion cycle is done, we should send first REFRESH or
 * REFRESH_V command, before data be read, which will update registers with new values. Also these commands will update Control register with
 * new desired configurations.
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
    switch (check_byte)
    {
        case 0x80 :
        {
            log_printf( &logger, " \nCH1     " );
        break;
        }
        case 0x40 :
        {
            log_printf( &logger, "\nCH2     " );
        break;
        }
        case 0x20 :
        {
            log_printf( &logger, "\nCH3     " );
        break;
        }
        case 0x10 :
        {
            log_printf( &logger, "\nCH4     " );
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
    Delay_ms( 1000 );
    smartbuck_get_data( &smartbuck, &voltage_res[0], &current_res[0], &power_res[0] );
    
    check_byte = 0x80;
    index = 0;
    
    for ( cnt = 0; cnt < 4; cnt++ )
    {
        if ( ( smartbuck.enabled_chann & check_byte ) == 0 )
        {
            channel_log();
            
            log_printf( &logger, "%f V ", voltage_res[ index ] );
            log_printf( &logger, "%f mA ", current_res[ index ] );
            log_printf( &logger, "%f mW ", power_res[ index ] );
            
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
