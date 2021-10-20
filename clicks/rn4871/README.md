\mainpage Main Page
 
---
# RN4871 click

RN4871 click carries the RN4871 Bluetooth® 4.2 low energy module from Microchip.The click is designed to run on a 3.3V power supply. It uses ASCII Command Interface over UART for communication with target microcontroller, with additional functionality provided by the following pins on the mikroBUS™ line: RST, CS, and INT.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rn4871_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rn4871-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the Rn4871 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rn4871 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rn4871_cfg_setup ( rn4871_cfg_t *cfg ); 
 
- Initialization function.
> RN4871_RETVAL rn4871_init ( rn4871_t *ctx, rn4871_cfg_t *cfg );


#### Example key functions :

- This function gets message from 'void rn4871_receive function if flag was set. This function replaces '*' (character with end of string) with '0x00' and stores received message to process_buffer
> uint8_t rn4871_read ( rn4871_t *ctx, uint8_t *process_buffer );
 
- The function receives character by waits for '#' - character to start parsing message, waits for '*' - character to stop parsing message and sets flag if whole and properly formated message is received.
> void rn4871_receive ( rn4871_t *ctx, char tmp );

- The function connects to slave device with desired register address by secures the connection and entering data stream mode.
> void rn4871_connect ( rn4871_t *ctx, char *p_addr );

## Examples Description

> This example reads and processes data from RN4871 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes UART driver. Initializes device and parser.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rn4871_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rn4871_cfg_setup( &cfg );
    RN4871_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rn4871_init( &rn4871, &cfg );

    dev_type = RN4871_DEVICETYPE_MASTER;

    if ( dev_type == RN4871_DEVICETYPE_MASTER )
    {
        rn4871_initialize( &rn4871, &RN4871_ADDR_MASTER[ 0 ] );
    }
    else if ( dev_type == RN4871_DEVICETYPE_SLAVE )
    {
        rn4871_initialize( &rn4871, &RN4871_ADDR_SLAVE[ 0 ] );
        ptr = &receive_buffer[ 7 ];
    }

    memset( &rn4871.device_buffer, 0, 255 );
    log_printf( &logger, " >>> app init done <<<  \r\n" );
}
  
```

### Application Task

> If 'MASTER' - connects to 'SLAVE', sends message and disconnects. If 'SLAVE' - waits for connect request 
> and message from 'MASTER' and LOGs received message.

```c

void application_task ( void )
{
    rn4871_process(  );
    if ( dev_type == RN4871_DEVICETYPE_MASTER )
    {
        rn4871_connect( &rn4871, &RN4871_ADDR_SLAVE[ 0 ] );
        log_printf( &logger, ">>> sending data  <<<\r\n" );
        rn4871_send( &rn4871, RN4871_MTYPE_MSG, RN4871_DTYPE_STRING, RN4871_ID_MASTER, &message_payload[ 0 ] );
        rn4871_disconnect( &rn4871 );
    }
    else if ( dev_type == RN4871_DEVICETYPE_SLAVE )
    {
        msg_flag = rn4871_read( &rn4871, &receive_buffer[ 0 ] );

        if ( msg_flag == 1 )
        {
            log_printf( &logger, ">>> data received <<<\r\n" );
            log_printf( &logger, ">>> data : " );
            log_printf( &logger, "%s\r\n", ptr );     
        }
    }
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rn4871

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
