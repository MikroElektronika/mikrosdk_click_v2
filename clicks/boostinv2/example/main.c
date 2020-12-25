/*!
 * \file 
 * \brief boostinv2 Click example
 * 
 * # Description
 * First increse positiv voltage by 2V every 3 seconda, then 
 * decrese negative value for -2v every 3 seconds.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes Driver init and enable chip
 * 
 * ## Application Task  
 * Changes the positive and negative output voltage. 
 * Positive output voltage goes from 5V to 15V. 
 * Negative output voltage goes from -5V to -15V
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "boostinv2.h"

// ------------------------------------------------------------------ VARIABLES

static boostinv2_t boostinv2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    boostinv2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    boostinv2_cfg_setup( &cfg );
    BOOSTONV2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    boostinv2_init( &boostinv2, &cfg );
    
    boostinv2_enable( &boostinv2 );   
}

void application_task ( void )
{
     // Positive output voltage 
     log_printf( &logger, "VOUT = 6V\r\n");
     boostinv2_set_positive_voltage( &boostinv2, BOOSTINV2_POS_VOUT_6V );
     Delay_ms( 3000 );
     log_printf( &logger, "VOUT = 8V\r\n");
     boostinv2_set_positive_voltage( &boostinv2, BOOSTINV2_POS_VOUT_8V );
     Delay_ms( 3000 );
     log_printf( &logger, "VOUT = 12V\r\n");
     boostinv2_set_positive_voltage( &boostinv2, BOOSTINV2_POS_VOUT_12V );
     Delay_ms( 3000 );
     log_printf( &logger, "VOUT = 14V\r\n");
     boostinv2_set_positive_voltage( &boostinv2, BOOSTINV2_POS_VOUT_14V );
     Delay_ms( 3000 );
     log_printf( &logger, "VOUT = 12V\r\n");
     boostinv2_set_positive_voltage( &boostinv2, BOOSTINV2_POS_VOUT_12V );
     Delay_ms( 3000 );
     log_printf( &logger, "VOUT = 8V\r\n");
     boostinv2_set_positive_voltage( &boostinv2, BOOSTINV2_POS_VOUT_8V );
     Delay_ms( 3000 );
     
     // Negative output voltage 
     
     log_printf( &logger, "VOUT = -5V\r\n");
     boostinv2_set_negative_voltage( &boostinv2, BOOSTINV2_NEG_VOUT_5V );
     Delay_ms( 3000 );
     log_printf( &logger, "VOUT = -7V\r\n");
     boostinv2_set_negative_voltage( &boostinv2, BOOSTINV2_NEG_VOUT_7V );
     Delay_ms( 3000 );
     log_printf( &logger, "VOUT = -13V\r\n");
     boostinv2_set_negative_voltage( &boostinv2, BOOSTINV2_NEG_VOUT_13V );
     Delay_ms( 3000 );
     log_printf( &logger, "VOUT = -7V\r\n");
     boostinv2_set_negative_voltage( &boostinv2, BOOSTINV2_NEG_VOUT_7V );
     Delay_ms( 3000 );
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
