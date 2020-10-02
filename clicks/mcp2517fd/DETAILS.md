
---
# MCP2517FD click

MCP2517FD click is a complete CAN solution which carries the MCP2517FD CAN FD controller and ATA6563 high-speed CAN transceiver from Microchip, as well as a DB9 9-pin connector.
The click requires both 3.3V and 5V power supply. It communicates with the target microcontroller through the SPI interface, with additional functionality provided by the following pins on the mikroBUS™ socket: AN, PWM, INT, TX, and RX.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mcp2517fd_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/mcp2517fd-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Mcp2517Fd Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Mcp2517Fd Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mcp2517fd_cfg_setup ( mcp2517fd_cfg_t *cfg ); 
 
- Initialization function.
> MCP2517DF_RETVAL mcp2517fd_init ( mcp2517fd_t *ctx, mcp2517fd_cfg_t *cfg );

- Click Default Configuration function.
> void mcp2517fd_default_cfg ( mcp2517fd_t *ctx );


#### Example key functions :

- Transmits the desired message and checks is message successfully sent.
> void mcp2517fd_transmit_message ( mcp2517fd_t *ctx, uint8_t num_data_bytes, uint8_t *transmit_flag, uint8_t *data_in );
 
- Receives the message and checks is message successfully received.
> void mcp2517fd_receive_message ( mcp2517fd_t *ctx, uint8_t *receive_flag, uint8_t *data_out );

- Loads data into Transmit channel
> int8_t mcp2517fd_transmit_channel_load ( mcp2517fd_t *ctx, uint8_t channel, mcp2517fd_tx_msg_obj_t *tx_obj, bool flush );

## Examples Description

> Using this click we can send the desired message via CAN communication to the other device. 
> It communicates with the target microcontroller through the SPI interface, 
> with additional functionality provided by the following pins

**The demo application is composed of two sections :**

### Application Init 

> Initializes SPI interface and performs the device configuration to work properly.

```c

void application_init ( void )
{
    uint8_t osc_byte;
    log_cfg_t log_cfg;
    mcp2517fd_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mcp2517fd_cfg_setup( &cfg );
    MCP2517DF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mcp2517fd_init( &mcp2517fd, &cfg );

    mcp2517fd_default_cfg ( &mcp2517fd );

    log_printf( &logger, "MCP2517FD is initialized for ARM\r\n" );
}
  
```

### Application Task

> Always checks is a new message in FIFO ready for receiving and when
> is message ready, receives a message from the other device.
> Also in this example we can send the desired message via CAN communication to the other device.
> We can choose a message to be sent by sending the determined command to the UART.
> In this example the command can be number from 1 to 7. 

```c

void application_task ( void )
{
    rx_dat = 1;
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
```

## Note

> For selecting the interface voltage level, use the onboard jumper, and choose between 
> the 3.3V and 5V. For more information, see the Jumpers and Settings table below.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Mcp2517Fd

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
