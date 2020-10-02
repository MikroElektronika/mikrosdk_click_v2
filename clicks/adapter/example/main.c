/*!
 * \file 
 * \brief Adapter Click example
 * 
 * # Description
 * Adapter click is a breakout board which simplifies connection of add-on boards. 
 * There are two ways of establishing connection: using male or female IDC10 connectors. 
 * Male header must be soldered on the top side of Adapter Click to connect the add-on board 
 * directly or via flat cable. Female header can be soldered either on the top, or the bottom 
 * side, depending on which one is more convenient in given circumstances.  
 * There are two jumpers for SPI/I2C selection and one for selection of power supply range.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes I2C or SPI driver and makes an initial log.
 * 
 * ## Application Task  
 * This is an example that shows the use of the Adapter click board. 
 * In I2C mode we are reading ID registrer from another device (THERMO 5 click board).
 * In SPI mode example we are writing into a shift register.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "adapter.h"

// ------------------------------------------------------------------ VARIABLES

static adapter_t adapter;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    adapter_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    adapter_cfg_setup( &cfg );
    ADAPTER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adapter_init( &adapter, &cfg );
}

void application_task ( void )
{
    uint8_t wr_value;
    uint8_t rd_value;

    if ( adapter.master_sel == ADAPTER_MASTER_SPI )
    {
        adapter_turn_pwm_on( &adapter );

        wr_value = 0x79; 
        adapter_generic_write ( &adapter, 0x00, &wr_value, 1 );
    }
    else if ( adapter.master_sel == ADAPTER_MASTER_I2C )
    {
        adapter_generic_read ( &adapter, 0xFD, &rd_value, 1 );

        log_printf( &logger, " Read data :  %d\r\n", rd_value );
        log_printf( &logger, "-----------------\r\n" );
    
        Delay_ms( 2000 );
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
