/*!
 * \file 
 * \brief Mic24045 Click example
 * 
 * # Description
 * Initializes GPIO, I2C and LOG structures, 
 * sets RST pin as output and INT pin as input and start write log.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - I2C, also write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of MIC24045 Click board.
 * System will slowly decrement vOut in 0.25 V steps.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on usb uart changes for every sec.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mic24045.h"

// ------------------------------------------------------------------ VARIABLES

static mic24045_t mic24045;
static log_t logger;
static float current_voltage;
static float v_out;
static uint8_t cnt;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mic24045_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mic24045_cfg_setup( &cfg );
    MIC24045_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mic24045_init( &mic24045, &cfg );
    mic24045_default_cfg ( &mic24045 );
    Delay_ms( 100 );
    
    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, "     MIC24045 Click     \r\n" );
    log_printf( &logger, "------------------------\r\n" );
}

void application_task ( void )
{
    //  Task implementation.

    for ( cnt = 21; cnt > 2; cnt-- )
    {
        v_out = cnt * 0.25;
        
        mic24045_set_vout( &mic24045, v_out );
        mic24045_enable ( &mic24045 );
        current_voltage = mic24045_get_vout( &mic24045 );
    
        log_printf( &logger, " Current voltage: %.2f V\r\n", current_voltage );
        log_printf( &logger, "------------------------\r\n" );
        Delay_ms( 1000 );
        
        mic24045_disable ( &mic24045 );
        Delay_ms( 1000 );
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
