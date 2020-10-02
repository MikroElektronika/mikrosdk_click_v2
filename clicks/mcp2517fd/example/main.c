/*!
 * \file 
 * \brief Mcp2517Fd Click example
 * 
 * # Description
 * Using this click we can send the desired message via CAN communication to the other device. 
 * It communicates with the target microcontroller through the SPI interface, 
 * with additional functionality provided by the following pins
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes SPI interface and performs the device configuration to work properly.
 * 
 * ## Application Task  
 * Always checks is a new message in FIFO ready for receiving and when
 * is message ready, receives a message from the other device.
 * Also in this example we can send the desired message via CAN communication to the other device.
 * We can choose a message to be sent by sending the determined command to the UART.
 * In this example the command can be number from 1 to 7.
 * 
 * *note:* 
 * For selecting the interface voltage level, use the onboard jumper, and choose between 
 * the 3.3V and 5V. For more information, see the Jumpers and Settings table below.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mcp2517fd.h"
#include "string.h"

// ------------------------------------------------------------------ VARIABLES

static mcp2517fd_t mcp2517fd;
static log_t logger;

uint8_t check_flag;
uint8_t rx_dat;
mcp2517fd_config_t con_obj;
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
    uint8_t osc_byte;
    log_cfg_t log_cfg;
    mcp2517fd_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mcp2517fd_cfg_setup( &cfg );
    MCP2517DF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mcp2517fd_init( &mcp2517fd, &cfg );

    mcp2517fd_default_cfg ( &mcp2517fd );

    log_printf( &logger, "MCP2517FD is initialized for ARM\r\n" );
}

void application_task ( void )
{
    rx_dat = '1'; // Select the number of message you want to send

    ch_ptr = &txd[ 0 ];

        switch ( rx_dat )
        {
            case '1' :
            {
                strcpy( ch_ptr, &txt_message1[ 0 ] );
                mcp2517fd_transmit_message( &mcp2517fd, 5, &check_flag, &txd[ 0 ] );
                if ( check_flag == 1 )
                {
                    log_printf( &logger, "Message Sent\r\n" );
                }
            break;
            }
            case '2' :
            {
                strcpy( ch_ptr, &txt_message2[ 0 ] );
                mcp2517fd_transmit_message( &mcp2517fd, 7, &check_flag, &txd[ 0 ] );
                if ( check_flag == 1 )
                {
                    log_printf( &logger, "Message Sent\r\n" );
                }
            break;
            }
            case '3' :
            {
                strcpy( ch_ptr, &txt_message3[ 0 ] );
                mcp2517fd_transmit_message( &mcp2517fd, 2, &check_flag, &txd[ 0 ] );
                if ( check_flag == 1 )
                {
                    log_printf( &logger, "Message Sent\r\n" );
                }
            break;
            }
            case '4' :
            {
                strcpy( ch_ptr, &txt_message4[ 0 ] );
                mcp2517fd_transmit_message( &mcp2517fd, 4, &check_flag, &txd[ 0 ] );
                if ( check_flag == 1 )
                {
                    log_printf( &logger, "Message Sent\r\n" );
                }
            break;
            }
            case '5' :
            {
                strcpy( ch_ptr, &txt_message5[ 0 ] );
                mcp2517fd_transmit_message( &mcp2517fd, 3, &check_flag, &txd[ 0 ] );
                if ( check_flag == 1 )
                {
                    log_printf( &logger, "Message Sent\r\n" );
                }
            break;
            }
            case '6' :
            {
                strcpy( ch_ptr, &txt_message6[ 0 ] );
                mcp2517fd_transmit_message( &mcp2517fd, 3, &check_flag, &txd[ 0 ] );
                if ( check_flag == 1 )
                {
                    log_printf( &logger, "Message Sent\r\n" );
                }
            break;
            }
            case '7' :
            {
                strcpy( ch_ptr, &txt_message7[ 0 ] );
                mcp2517fd_transmit_message( &mcp2517fd, 7, &check_flag, &txd[ 0 ] );
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
        
    mcp2517fd_receive_message( &mcp2517fd, &check_flag, &rxd[ 0 ] );
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
