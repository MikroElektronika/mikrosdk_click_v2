
---
# RN4870 click

RN4870 click carries the RN4870 Bluetooth® 4.2 low energy module from Microchip.
The click is designed to run on a 3.3V power supply. It uses ASCII Command Interface over UART for communication with target microcontroller, with additional functionality provided by the following pins on the mikroBUS™ line: PWM, INT, RST, CS.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rn4870_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/rn4870-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the Rn4870 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rn4870 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rn4870_cfg_setup ( rn4870_cfg_t *cfg ); 
 
- Initialization function.
> RN4870_RETVAL rn4870_init ( rn4870_t *ctx, rn4870_cfg_t *cfg );

- Click Default Configuration function.
> void rn4870_default_cfg ( rn4870_t *ctx );


#### Example key functions :

-  The function receives character by waits for '#' - character to start parsing message, waits for '*' - character to stop parsing message and sets flag if whole and properly formated message is received.
> void rn4870_receive ( rn4870_t *ctx, char character );
 
- The function connects to slave device with desired register address by secures the connection and entering data stream mode.
> void rn4870_connect( rn4870_t *ctx, char *dev_addr );

- The function check message from if data received ( if flag was set ), stores received message to rx_data pointer to the memory location where the read text data is stored and replaces '*' - character with end of string - '0x00'.
> uint8_t rn4870_read ( rn4870_t *ctx, uint8_t *rx_data );

## Examples Description

> This example reads and processes data from RN4870 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - UART, also write log. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rn4870_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rn4870_cfg_setup( &cfg );
    RN4870_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rn4870_init( &rn4870, &cfg );

    dev_type = RN4870_DEVICETYPE_SLAVE;

    if ( dev_type == RN4870_DEVICETYPE_MASTER )
    {
        rn4870_initialize( &rn4870, &RN4870_ADDR_MASTER[ 0 ] );
    }
    else if ( dev_type == RN4870_DEVICETYPE_SLAVE )
    {
        rn4870_initialize( &rn4870, &RN4870_ADDR_SLAVE2[ 0 ] );
        log_text = &receive_buffer[ 7 ];
    }

    memset( &rn4870.device_buffer, 0, 255 );
    log_printf( &logger, " Clearing Msg Data  \r\n" );
    log_printf( &logger, "--------------------\r\n" );
}
  
```

### Application Task

> This is an example which demonstrates the use of RN4870 Click board.
> If 'MASTER' - connects to 'SLAVE', sends message and disconnects.
> If 'SLAVE' - waits for connect request and message from 'MASTER' and LOGs received message.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void applicationTask()
{
    if ( devType == _RN4870_DEVICETYPE_MASTER )
    {
        rn4870_connect( &RN4870_ADDR_SLAVE1[ 0 ] );
        rn4870_send( _RN4870_MTYPE_MSG, _RN4870_DTYPE_STRING, _RN4870_ID_SLAVE, &MESSAGE_DATA[ 0 ] );
        mikrobus_logWrite( "    Message Send    ", _LOG_LINE );
        rn4870_disconnect();
    }
    else if ( devType == _RN4870_DEVICETYPE_SLAVE )
    {
        msgFlag = rn4870_read( receiveBuffer );

        if ( msgFlag == 1 )
        {
            mikrobus_logWrite( receiveBuffer, _LOG_LINE );
        }
    }
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rn4870

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
