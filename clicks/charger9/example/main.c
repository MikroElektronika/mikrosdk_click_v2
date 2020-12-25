/*!
 * \file 
 * \brief Charger 9 Click example
 * 
 * # Description
 * This application is battery charger, capable of charging one, two or three battery cells. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO driver and turns OFF the charger as initial state.
 * 
 * ## Application Task  
 * Checks which command was sent by user and performs the selected command.
 * Also checks the fault condition, and when fault condition is detected sends a report message to the uart terminal 
 * and turns OFF the charger.
 * 
 * *note:* 
 * When user sends a desired command to the charger, a report message will be sent to the uart terminal as 
 * indication to the user.
 * The possible commands, for Charger 9 control, will be written to the uart terminal.
 * The alarm sound will be generated on the determined commands: enable, disable and fault condition detecting.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "charger9.h"

// ------------------------------------------------------------------ VARIABLES

static charger9_t charger9;
static log_t logger;
static CHARGER9_STATE en_flag;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    charger9_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    charger9_cfg_setup( &cfg );
    CHARGER9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    charger9_init( &charger9, &cfg );
    
    charger9_enable( &charger9, CHARGER9_DISABLE );
    en_flag = CHARGER9_DISABLE;
    Delay_ms( 100 );
    
    log_printf( &logger, "** Charger 9 initialization done ** \r\n" );
}

void application_task ( )
{   
    CHARGER9_RETVAL charge_state;
    
    if ( en_flag == CHARGER9_DISABLE )
    {
        charger9_enable( &charger9, CHARGER9_ENABLE );
        en_flag = CHARGER9_ENABLE;
        
        Delay_ms( 2000 );
        log_printf( &logger, "** Charger 9 is enabled ** \r\n" );
    }

    charge_state = charger9_full_charge_ind( &charger9 );
                
    if ( charge_state == CHARGER9_IND_ACTIVE )
    {
        log_printf( &logger, "** Full-Charge state ** \r\n" );
        Delay_ms( 2000 );
    }
    
    charge_state = charger9_fast_charge_ind( &charger9 );
    if ( charge_state == CHARGER9_IND_ACTIVE )
    {
        log_printf( &logger, "** Fast-Charge state ** \r\n" );
        Delay_ms( 2000 );
    }

    charge_state = charger9_fault_ind ( &charger9 );
    
    if ( charge_state == CHARGER9_IND_ACTIVE )
    {
        charger9_enable( &charger9, CHARGER9_DISABLE );
        en_flag = CHARGER9_DISABLE;
        
        Delay_ms( 3000 );
        log_printf( &logger, "** Fault condition! ** \r\n" );
        log_printf( &logger, "** Charger 9 is disabled ** \r\n" );
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
