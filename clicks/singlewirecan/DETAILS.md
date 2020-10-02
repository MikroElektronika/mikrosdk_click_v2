
---
# Single Wire CAN click

Single Wire CAN Click is a compact add-on board that contains an IC for a single wire data link capable of operating with various protocols such as the Controller Area Network (CAN). This board features the NCV7356D1R2G, Single Wire CAN transceiver from ON Semiconductor, which operates from a supply voltage from 5V to 27V with bus speed up to 40 kbps. 

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>

[click Product page](https://www.mikroe.com/single-wire-can-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the SingleWireCan Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for SingleWireCan Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void singlewirecan_cfg_setup ( singlewirecan_cfg_t *cfg ); 
 
- Initialization function.
> SINGLEWIRECAN_RETVAL singlewirecan_init ( singlewirecan_t *ctx, singlewirecan_cfg_t *cfg );

- Click Default Configuration function.
> void singlewirecan_default_cfg ( singlewirecan_t *ctx );


#### Example key functions :

- The function set desired operating mode of NCV7356 Single Wire CAN Transceiver
> void singlewirecan_set_operating_mode ( singlewirecan_t *ctx, uint8_t op_mode );
 
- This function write specified number of bytes
> void singlewirecan_generic_write ( singlewirecan_t *ctx, char *data_buf, uint16_t len );

- This function read maximum length of data.
> uint16_t singlewirecan_generic_read ( singlewirecan_t *ctx, char *data_buf, uint16_t max_len );

## Examples Description

> This example demonstrate sending a data by using one Single Wire CAN click
> and print recived data using the other Single Wire CAN click.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - UART,
> performs an operating mode and sets CS and RST pins as output.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    singlewirecan_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    singlewirecan_cfg_setup( &cfg );
    SINGLEWIRECAN_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    singlewirecan_init( &singlewirecan, &cfg );

    singlewirecan_default_cfg( &singlewirecan );
    log_printf( &logger, "  Set Normal Op. Mode \r\n" );
}
  
```

### Application Task

> This is an example that demonstrates the use of the One Wire CAN click board.
> This application task adjusted on Transmiter Mode, writes message data via UART every 3 seconds.
> And another clicks task, adjusted on Reciver Mode, read and represent result on the Usart Terminal.

```c

void application_task ( void )
{
    #ifdef DEMO_APP_TRANSMITER
        singlewirecan_generic_write( &singlewirecan, &demo_message_data[ 0 ], strlen( demo_message_data ) );
        log_printf( &logger, "Sending message\r\n" );
        log_printf( &logger, "\r\n" );
    #endif

    #ifdef DEMO_APP_RECEIVER    
        singlewirecan_process(  );
        log_printf( &logger, "----------------------\r\n" );
        log_printf( &logger, "\r\n" );
    #endif
    Delay_ms( 3000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.SingleWireCan

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
