/*!
 * \file main.c
 * \brief DIGI POT 5 Click example
 *
 * # Description
 * This example demonstrates the use of the DIGI POT 5 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes all necessary peripherals and pins used for the DIGI POT 5 click.
 * Also allows the device to be reset and configured to enable all wipers (4).
 * UART console module will be initialized also in this function.
 *
 * ## Application Task
 * Demonstrates the use of click driver functions by performing a control of
 * the all wipers positions. By checking the uart console, user can be informed
 * about the all current wipers positions.
 *
 * *note:*
 * Increment/decrement command can be issued only to volatile wiper locations.
 *
 * \author Nemanja Medakovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "digipot5.h"


// ------------------------------------------------------------------ VARIABLES

static digipot5_t digipot5;
static log_t console;
static uint8_t i;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init( void )
{
    digipot5_cfg_t digipot5_cfg;
    log_cfg_t console_cfg;

    //  Click initialization.
    digipot5_cfg_setup( &digipot5_cfg );
    DIGIPOT5_MAP_MIKROBUS( digipot5_cfg, MIKROBUS_1 );
    digipot5_init( &digipot5, &digipot5_cfg );
    digipot5_reset( &digipot5 );
    digipot5_default_cfg( &digipot5 );

    //  Console module initialization.
    LOG_MAP_USB_UART( console_cfg );
    console_cfg.level = LOG_LEVEL_DEBUG;
    console_cfg.baud = 57600;
    log_init( &console, &console_cfg );
    log_printf( &console, "***  DIGI POT 5 Initialization Done  ***\r\n" );
    log_printf( &console, "****************************************\r\n" );
}

void application_task( void )
{
    log_printf( &console, "* Setting wiper 0 to zero scale.\r\n" );
    digipot5_generic_write( &digipot5, DIGIPOT5_REG_WIPER0_VOL,
                            DIGIPOT5_RES_ZEROSCALE );
    log_printf( &console, "* Setting wiper 1 to 3k Ohm.\r\n" );
    digipot5_generic_write( &digipot5, DIGIPOT5_REG_WIPER1_VOL,
                            DIGIPOT5_RES_3KOHM );
    log_printf( &console, "* Setting wiper 2 to half scale (5k Ohm).\r\n" );
    digipot5_generic_write( &digipot5, DIGIPOT5_REG_WIPER2_VOL,
                            DIGIPOT5_RES_5KOHM_HALFSCALE );
    log_printf( &console, "* Setting wiper 3 to full scale (10k Ohm).\r\n" );
    digipot5_generic_write( &digipot5, DIGIPOT5_REG_WIPER3_VOL,
                            DIGIPOT5_RES_10KOHM_FULLSCALE );

    Delay_ms( 3000 );
    log_printf( &console, "* Decrementing wiper 3 by 5 steps.\r\n" );
    for ( i = 0; i < 5; i++ )
    {
        digipot5_decrement_wiper( &digipot5, DIGIPOT5_REG_WIPER3_VOL );
    }

    Delay_ms( 3000 );
    log_printf( &console, "* Incrementing wiper 0 by 10 steps.\r\n" );
    for ( i = 0; i < 10; i++ )
    {
        digipot5_increment_wiper( &digipot5, DIGIPOT5_REG_WIPER0_VOL );
    }

    Delay_ms( 3000 );
    log_printf( &console, "* Setting wiper 0 to 2k Ohm.\r\n" );
    digipot5_generic_write( &digipot5, DIGIPOT5_REG_WIPER0_VOL,
                            DIGIPOT5_RES_2KOHM );
    log_printf( &console, "* Setting wiper 1 to 2k Ohm.\r\n" );
    digipot5_generic_write( &digipot5, DIGIPOT5_REG_WIPER1_VOL,
                            DIGIPOT5_RES_2KOHM );
    log_printf( &console, "* Setting wiper 2 to 2k Ohm.\r\n" );
    digipot5_generic_write( &digipot5, DIGIPOT5_REG_WIPER2_VOL,
                            DIGIPOT5_RES_2KOHM );
    log_printf( &console, "* Setting wiper 3 to 2k Ohm.\r\n" );
    digipot5_generic_write( &digipot5, DIGIPOT5_REG_WIPER3_VOL,
                            DIGIPOT5_RES_2KOHM );

    Delay_ms( 3000 );
    log_printf( &console, "****************************************\r\n" );
}

void main( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}


// ------------------------------------------------------------------------ END
