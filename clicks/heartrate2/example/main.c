/*!
 * \file 
 * \brief HeartRate2 Click example
 * 
 * # Description
 * This example demonstrates the use of Heart rate 2 click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initilizes the driver, resets the device, checks the device ID and applies default settings.
 * 
 * ## Application Task  
 * Reads the data from Green diode and displays the results on USB UART if the measured data
 * is above defined threshold, otherwise, it displays a desired message on the terminal.
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
static uint16_t counter = 1000;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    heartrate2_cfg_t cfg;
    uint8_t rd_stat;

    //  Logger initialization.
    
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 115200;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    heartrate2_cfg_setup( &cfg );
    HEARTRATE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    heartrate2_init( &heartrate2, &cfg );
    
    log_printf( &logger, "Configuring the module...\r\n" );
    Delay_ms( 1000 );
    
    heartrate2_set_en( &heartrate2, HEARTRATE2_PIN_HIGH );
    Delay_ms( 100 );
    heartrate2_soft_reset ( &heartrate2 );
    
    rd_stat = heartrate2_generic_read( &heartrate2, HEARTRATE2_REG_PART_ID );

    if ( rd_stat != HEARTRATE2_DEV_ID )
    {
        log_error( &logger, "---- WRONG ID ----" );
        log_printf( &logger, "Please restart your system.\r\n" );
        for ( ; ; );
    }
    
    heartrate2_default_cfg( &heartrate2, HEARTRATE2_CONFIG_GREEN );
    log_printf( &logger, "The module has been configured!\r\n" );
    Delay_ms( 1000 );
}

void application_task ( void )
{
    heartrate2_fifo_data_t fifo_object;

    heartrate2_read_fifo( &heartrate2, &fifo_object );

    if ( fifo_object.tag == HEARTRATE2_FIFO_TAG_PPG1_LEDC1 )
    {
        counter++;
        if ( fifo_object.data_val > 1000 )
        {
            log_printf( &logger, "%lu;\r\n", fifo_object.data_val );
            counter = 1000;
        }
        else if ( counter > 1000 )
        {
            log_printf( &logger, "Please place your index finger on the sensor.\r\n" );
            counter = 0;
        }
    }
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
