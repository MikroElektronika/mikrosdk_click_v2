/*!
 * \file 
 * \brief MacAddress Click example
 * 
 * # Description
 * Provides a unique node address for your application.
 *
 * The application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - I2C, also write log.
 * 
 * ## Application Task - (code snippet) This is an example which demonstrates the use of MAC Address click board.
 * MAC Address click communicates with register via I2C protocol by the write to register and read from the register.
 * This example shows write/read single byte and sequential write/read from EEPROM.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on USB uart changes for every 1 sec.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "macaddress.h"

// ------------------------------------------------------------------ VARIABLES

static macaddress_t macaddress;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    macaddress_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    macaddress_cfg_setup( &cfg );
    MACADDRESS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    macaddress_init( &macaddress, &cfg );

    log_printf( &logger,"      <<   I2C Driver Init   >>      \r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    uint8_t cnt;
    uint8_t buffer[ 12 ];
    uint8_t read_mac[ 10 ];
    uint8_t buffer_loop = 0;
    
    macaddress_get_mac( &macaddress, &read_mac );
    Delay_ms( 100 );

    log_printf( &logger, " MAC Address :  \r\n" );
    for ( cnt = 0; cnt < 6; cnt++ )
    {
        log_printf( &logger, "0x%x", read_mac[ cnt ] );
            
        if ( cnt != 5 )
        {
            log_printf( &logger, ": \r\n" );
        }
    }

    log_printf( &logger, "--------------------------------- \r\n" );
    log_printf( &logger, " Write Single Byte Test :  \r\n" );

    macaddress_generic_write( &macaddress, buffer_loop, &buffer_loop, 1 );

    log_printf( &logger, " Byte value [ 0x%x ] successfully written to [ 0x%x ] address \r\n" , buffer_loop + 1, buffer_loop );
    
    log_printf( &logger, "-----------------------------\r\n" );
    log_printf( &logger, "-----------------------------\r\n" );
    log_printf( &logger, " Read Single Byte Test \r\n");

    macaddress_read_byte( &macaddress, buffer_loop );
    
    log_printf( &logger, " Byte value [ 0x%x ] successfully read from  [ 0x%x ] address \r\n", buffer_loop + 1, buffer_loop );
    log_printf( &logger, "----------------------------- \r\n" );
    log_printf( &logger, "----------------------------- \r\n" );

    macaddress_generic_write( &macaddress, buffer_loop, buffer, 12 );
    Delay_ms( 1000 );

    log_printf( &logger, " Array values : \r\n" );

    for ( cnt = 0; cnt < 12; cnt++ )
    {
        log_printf( &logger,"[ 0x%x ] \r\n", buffer[ cnt ] );
    }

    log_printf( &logger," successfully written to [ 0x%x ] address and forward \r\n", buffer_loop );
    log_printf( &logger, "-----------------------------" );
    log_printf( &logger, "-----------------------------" );

    macaddress_generic_read( &macaddress, buffer_loop, buffer, 12 );
    Delay_ms( 1000 );

    log_printf( &logger, " Array values : \r\n" );

    for ( cnt = 0; cnt < 12; cnt++ )
    {
        log_printf( &logger,"[ 0x%x ]", buffer[ cnt ]); 
    }

    log_printf( &logger," successfully read from [ 0x%x ] address and forward \r\n", buffer_loop );
    log_printf( &logger, "-----------------------------" );
    log_printf( &logger, "-----------------------------" );

    if ( buffer_loop < MACADDRESS_END_ADDR )
    {
        buffer_loop++;
    }
    else
    {
        buffer_loop = 0;
    }

    Delay_ms( 1000 );
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

