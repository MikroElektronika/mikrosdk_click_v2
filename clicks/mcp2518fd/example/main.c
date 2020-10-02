/*!
 * \file 
 * \brief Mcp2518Fd Click example
 * 
 * # Description
 * This click is used as a control node in a CAN network. It provides a reliable high-speed CAN 
 * interface to the MCU, providing multiple operating modes ( CAN 2.0, CAN FD, Listen Only mode, 
 * Sleep and Low Power mode… ), CAN bit stream processing ( decoding and encoding of the CAN 
 * messages, error handling… ), TX prioritizing, RX filtering, FIFO buffer and interrupt engine. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes SPI interface and performs the device configuration to work properly.
 * 
 * ## Application Task  
 * Always checks is new message in FIFO ready for receiving and when
 * is message ready, receives a message from the other device.
 * Also in this example we can sent the desired message via CAN communication to the other device.
 * We can choose a message to be sent by sending the determined command to the UART.
 * In this example the command, which determines a message, can be number from 1 to 7.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mcp2518fd.h"
#include "string.h"

// ------------------------------------------------------------------ VARIABLES

static mcp2518fd_t mcp2518fd;
static log_t logger;

mcp2518fd_config_t con_obj;
uint8_t check_flag;
uint8_t rx_dat;
char *ch_ptr;

char txt_message1[ 6 ] = "HELLO";
char txt_message2[ 8 ] = "MESSAGE";
char txt_message3[ 3 ] = "IS";
char txt_message4[ 5 ] = "SENT";
char txt_message5[ 4 ] = "CAN";
char txt_message6[ 4 ] = "YOU";
char txt_message7[ 8 ] = "CONFIRM";

// Transmit objects
uint8_t txd[ 64 ];

// Receive objects
uint8_t rxd[ 64 ];

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mcp2518fd_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mcp2518fd_cfg_setup( &cfg );
    MCP2518FD_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mcp2518fd_init( &mcp2518fd, &cfg );

    mcp2518fd_default_cfg ( &mcp2518fd );

    log_printf( &logger, "MCP2517FD is initialized for ARM\r\n" );
}

void application_task ( void )
{
    rx_dat = 1; // Select the number of message you want to send

    ch_ptr = &txd[ 0 ];

        switch ( rx_dat )
        {
            case 1 :
            {
                strcpy( ch_ptr, &txt_message1[ 0 ] );
                mcp2518fd_transmit_message( &mcp2518fd, 5, &check_flag, &txd[ 0 ] );
                if ( check_flag == 1 )
                {
                    log_printf( &logger, "Message Sent\r\n" );
                }
            break;
            }
            case 2 :
            {
                strcpy( ch_ptr, &txt_message2[ 0 ] );
                mcp2518fd_transmit_message( &mcp2518fd, 7, &check_flag, &txd[ 0 ] );
                if ( check_flag == 1 )
                {
                    log_printf( &logger, "Message Sent\r\n" );
                }
            break;
            }
            case 3 :
            {
                strcpy( ch_ptr, &txt_message3[ 0 ] );
                mcp2518fd_transmit_message( &mcp2518fd, 2, &check_flag, &txd[ 0 ] );
                if ( check_flag == 1 )
                {
                    log_printf( &logger, "Message Sent\r\n" );
                }
            break;
            }
            case 4 :
            {
                strcpy( ch_ptr, &txt_message4[ 0 ] );
                mcp2518fd_transmit_message( &mcp2518fd, 4, &check_flag, &txd[ 0 ] );
                if ( check_flag == 1 )
                {
                    log_printf( &logger, "Message Sent\r\n" );
                }
            break;
            }
            case 5 :
            {
                strcpy( ch_ptr, &txt_message5[ 0 ] );
                mcp2518fd_transmit_message( &mcp2518fd, 3, &check_flag, &txd[ 0 ] );
                if ( check_flag == 1 )
                {
                    log_printf( &logger, "Message Sent\r\n" );
                }
            break;
            }
            case 6 :
            {
                strcpy( ch_ptr, &txt_message6[ 0 ] );
                mcp2518fd_transmit_message( &mcp2518fd, 3, &check_flag, &txd[ 0 ] );
                if ( check_flag == 1 )
                {
                    log_printf( &logger, "Message Sent\r\n" );
                }
            break;
            }
            case 7 :
            {
                strcpy( ch_ptr, &txt_message7[ 0 ] );
                mcp2518fd_transmit_message( &mcp2518fd, 7, &check_flag, &txd[ 0 ] );
                if ( check_flag == 1 )
                {
                    log_printf( &logger, "Message Sent\r\n" );
                }
            break;
            }
            default :
            {
            break;
            }
        }
        
    mcp2518fd_receive_message( &mcp2518fd, &check_flag, &rxd[ 0 ] );
    if ( check_flag == 1 )
    {
        ch_ptr = &rxd[ 0 ];
        log_printf( &logger, "Received Message : %d \r\n", ch_ptr );
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
