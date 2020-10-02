\mainpage Main Page
 
---
# MCP2518FD click

MCP2518FD click is a complete CAN solution, which can be used as a control node in a CAN network. The Click board™ is used to provide the microcontroller (MCU) with unrestricted access to the CAN network bus. MCP2518FD click is equipped with both the control logic and the physical interface ICs. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mcp2518fd_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/mcp2518fd-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Mcp2518Fd Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Mcp2518Fd Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mcp2518fd_cfg_setup ( mcp2518fd_cfg_t *cfg ); 
 
- Initialization function.
> MCP2518FD_RETVAL mcp2518fd_init ( mcp2518fd_t *ctx, mcp2518fd_cfg_t *cfg );

- Click Default Configuration function.
> void mcp2518fd_default_cfg ( mcp2518fd_t *ctx );


#### Example key functions :

- Returns content of complete CiTREC
> int8_t mcp2518fd_error_count_state_get ( mcp2518fd_t *ctx, uint8_t *tec, uint8_t *rec, uint8_t *flags );
 
- Transmits the desired message and checks is message successfully sent.
> void mcp2518fd_transmit_message ( mcp2518fd_t *ctx, uint8_t num_data_bytes, uint8_t *transmit_flag, uint8_t *data_in );

- Receives the message and checks is message successfully received.
> void mcp2518fd_receive_message ( mcp2518fd_t *ctx, uint8_t *receive_flag, uint8_t *data_out );

## Examples Description

> This click is used as a control node in a CAN network. It provides a reliable high-speed CAN 
> interface to the MCU, providing multiple operating modes ( CAN 2.0, CAN FD, Listen Only mode, 
> Sleep and Low Power mode… ), CAN bit stream processing ( decoding and encoding of the CAN 
> messages, error handling… ), TX prioritizing, RX filtering, FIFO buffer and interrupt engine. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes SPI interface and performs the device configuration to work properly.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    mcp2518fd_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mcp2518fd_cfg_setup( &cfg );
    MCP2518FD_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mcp2518fd_init( &mcp2518fd, &cfg );

    mcp2518fd_default_cfg ( &mcp2518fd );

    log_printf( &logger, "MCP2517FD is initialized for ARM\r\n" );
}
  
```

### Application Task

> Always checks is new message in FIFO ready for receiving and when
> is message ready, receives a message from the other device.
> Also in this example we can sent the desired message via CAN communication to the other device.
> We can choose a message to be sent by sending the determined command to the UART.
> In this example the command, which determines a message, can be number from 1 to 7.

```c

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

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Mcp2518Fd

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
