/*!
 * \file 
 * \brief CapWheel Click example
 * 
 * # Description
 * This application is use for controling various devices.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C interface, performs the device reset and
 * activates the desired channels (from CH0 to CH9), in this example all channels are activated.
 * 
 * ## Application Task  
 * Checks is sense data ready for reading and if was ready, 
  then reads wheel coordinates and sends these results to the LEDs.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "capwheel.h"

// ------------------------------------------------------------------ VARIABLES

static capwheel_t capwheel;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    capwheel_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    capwheel_cfg_setup( &cfg );
    CAPWHEEL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    capwheel_init( &capwheel, &cfg );

    capwheel_reset ( &capwheel );
    capwheel_enable_chann( &capwheel, CAPWHEEL_CH0_PROX_EN | CAPWHEEL_CH1_EN | CAPWHEEL_CH2_EN | 
                            CAPWHEEL_CH3_EN | CAPWHEEL_CH4_EN | CAPWHEEL_CH5_EN | CAPWHEEL_CH6_EN | 
                            CAPWHEEL_CH7_EN | CAPWHEEL_CH8_EN | CAPWHEEL_CH9_EN );
    capwheel_set_threshold( &capwheel, 0x03 );
    Delay_ms( 500 );
    
    log_printf( &logger, "CAP Wheel is initialized and ready\r\n" );
}

void application_task ( void )
{
    uint16_t sense_data;
    uint8_t ready_check;

    ready_check = capwheel_check_data_ready( &capwheel );

    if (ready_check == CAPWHEEL_DATA_READY)
    {
        capwheel_get_data( &capwheel, &sense_data );
        
        capwheel_set_output( &capwheel, sense_data, CAPWHEEL_LED_BRIGHTNESS_NUMBER );
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
