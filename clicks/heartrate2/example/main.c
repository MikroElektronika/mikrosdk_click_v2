/*!
 * \file 
 * \brief HeartRate2 Click example
 * 
 * # Description
 * This app measures heart rate.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Resets device, checks ID and configures device to desired led.
 * 
 * ## Application Task  
 * Reading fifo data and logs it with time.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "heartrate2.h"

// ------------------------------------------------------------------ VARIABLES

static heartrate2_t heartrate2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    heartrate2_cfg_t cfg;
    uint8_t rd_stat;

    //  Logger initialization.
    
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    heartrate2_cfg_setup( &cfg );
    HEARTRATE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    heartrate2_init( &heartrate2, &cfg );

    Delay_ms( 100 );

    heartrate2_set_en( &heartrate2, HEARTRATE2_PIN_HIGH );

    Delay_ms( 100 );

    heartrate2_soft_reset ( &heartrate2 );
    
    rd_stat = heartrate2_generic_read( &heartrate2, HEARTRATE2_REG_PART_ID );

    if ( rd_stat != HEARTRATE2_DEV_ID )
    {
        for ( ; ; );
    }
    
    Delay_ms( 100 );
    
    heartrate2_default_cfg( &heartrate2, HEARTRATE2_CONFIG_GREEN );

    Delay_ms( 200 );
}

void application_task ( void )
{
    heartrate2_fifo_data_t fifo_object;

    heartrate2_read_fifo( &heartrate2, &fifo_object );

    if ( fifo_object.tag == HEARTRATE2_FIFO_TAG_PPG1_LEDC1 )
    {
        log_printf( &logger, " %u \r\n", fifo_object.data_val );
    }
    
    Delay_ms( 4 );
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
