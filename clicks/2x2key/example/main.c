/*!
 * \file 
 * \brief 2x2 key Click example
 * 
 * # Description
 * 2x2 Key click has a 4 button keypad and allows multiple key presses.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Application Init performs Logger and Click initialization.
 * 
 * ## Application Task  
 * This example code demonstrates the usage of 2X2 Key Click board.
 * Detects whether any of the keys is pressed where results are being sent 
 * to the UART terminal where you can track changes.
 * 
 * \author Mihajlo Djordjevic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c2x2key.h"

uint8_t t1_state     = 0;
uint8_t t1_state_old = 1;
uint8_t t2_state     = 0;
uint8_t t2_state_old = 1;
uint8_t t3_state     = 0;
uint8_t t3_state_old = 1;
uint8_t t4_state     = 0;
uint8_t t4_state_old = 1;

// ------------------------------------------------------------------ VARIABLES

static c2x2key_t c2x2key;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c2x2key_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_printf( &logger, "-- Application  Init --\r\n" );
    Delay_ms ( 1000 );

    //  Click initialization.

    c2x2key_cfg_setup( &cfg );
    C2X2KEY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c2x2key_init( &c2x2key, &cfg );
    
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "     2X2 key Click     \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "    System is ready    \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
   t1_state = c2x2key_t1_state( &c2x2key );
   
   if ( ( t1_state == 1 ) && ( t1_state_old == 0 ) )
    {
        log_printf( &logger, "-----------------------\r\n" );
        log_printf( &logger, "     Key 1 pressed     \r\n" );
        log_printf( &logger, "-----------------------\r\n" );
        t1_state_old = 1;
    }
    
    if ( ( t1_state == 0 ) && ( t1_state_old == 1 ) )
    {
        t1_state_old = 0;
    }
    
    t2_state = c2x2key_t2_state( &c2x2key );
   
   if ( ( t2_state == 1 ) && ( t2_state_old == 0 ) )
    {
        log_printf( &logger, "-----------------------\r\n" );
        log_printf( &logger, "     Key 2 pressed     \r\n" );
        log_printf( &logger, "-----------------------\r\n" );
        t2_state_old = 1;
    }
    
    if ( ( t2_state == 0 ) && ( t2_state_old == 1 ) )
    {
        t2_state_old = 0;
    }
    
    t3_state = c2x2key_t3_state( &c2x2key );
   
   if ( ( t3_state == 1 ) && ( t3_state_old == 0 ) )
    {
        log_printf( &logger, "-----------------------\r\n" );
        log_printf( &logger, "     Key 3 pressed     \r\n" );
        log_printf( &logger, "-----------------------\r\n" );
        t3_state_old = 1;
    }
    
    if ( ( t3_state == 0 ) && ( t3_state_old == 1 ) )
    {
        t3_state_old = 0;
    }
    
    t4_state = c2x2key_t4_state( &c2x2key );
   
   if ( ( t4_state == 1 ) && ( t4_state_old == 0 ) )
    {
        log_printf( &logger, "-----------------------\r\n" );
        log_printf( &logger, "     Key 4 pressed     \r\n" );
        log_printf( &logger, "-----------------------\r\n" );
        t4_state_old = 1;
    }
    
    if ( ( t4_state == 0 ) && ( t4_state_old == 1 ) )
    {
        t4_state_old = 0;
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
