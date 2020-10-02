
---
# RN4678 click

RN4678 click carries the RN4678 Bluetooth® 4.2 dual mode module from Microchip. The click is designed to run on a 3.3V power supply. It communicates with the target microcontroller over I2C and UART interface, with additional functionality provided by the following pins on the mikroBUS™ line: AN, RST, CS, PWM, INT.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rn4678_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/rn4678-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the Rn4678 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rn4678 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rn4678_cfg_setup ( rn4678_cfg_t *cfg ); 
 
- Initialization function.
> RN4678_RETVAL rn4678_init ( rn4678_t *ctx, rn4678_cfg_t *cfg );

- Click Default Configuration function.
> void rn4678_default_cfg ( rn4678_t *ctx );


#### Example key functions :

- The function initializes RN4678 Bluetooth� 4.2 dual mode module by resets the module, disable I2C communications pins, reboots the device for change to take effect, enters CMD mode again, and sets the address of the device.
> void rn4678_initialize ( rn4678_t *ctx, char *dev_addr );
 
- The function sends message to slave device.
> void rn4678_send ( rn4678_t *ctx, uint8_t msg_type, uint16_t data_type, uint8_t dev_id, uint8_t *tx_data );

- The function receives character by waits for '#' - character to start parsing message, waits for '*' - character to stop parsing message and sets flag if whole and properly formated message is received.
> void rn4678_receive ( rn4678_t *ctx, char character );

## Examples Description

> This example reads and processes data from RN4678 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - UART, also write log..

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rn4678_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rn4678_cfg_setup( &cfg );
    RN4678_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rn4678_init( &rn4678, &cfg );

    dev_type = RN4678_DEVICE_TYPE_MASTER;

    if ( dev_type == RN4678_DEVICE_TYPE_MASTER )
    {
        rn4678_initialize( &rn4678, &RN4678_ADDR_MASTER[ 0 ] );
    }
    else if ( dev_type == RN4678_DEVICE_TYPE_SLAVE )
    {
        rn4678_initialize( &rn4678, &RN4678_ADDR_SLAVE1[ 0 ] );
        log_text = &receive_buffer[ 7 ];
    }

    memset( &rn4678.device_buffer, 0, 255 );

    log_printf( &logger, " Clearing Msg Data  \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms( 100 );

}
  
```

### Application Task

> This is an example which demonstrates the use of RN4870 Click board.
> If 'MASTER' - connects to 'SLAVE', sends message and disconnects.
> If 'SLAVE' - waits for connect request and message from 'MASTER' and LOGs received message.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void )
{
    rn4678_process( );
    
    if ( dev_type == RN4678_DEVICE_TYPE_MASTER )
    {
        rn4678_connect( &rn4678, &RN4678_ADDR_SLAVE1[ 0 ] );
        rn4678_send( &rn4678, RN4678_MTYPE_MSG, RN4678_DTYPE_STRING, RN4678_ID_SLAVE, &MESSAGE_DATA[ 0 ] );
        log_printf( &logger, "    Message Send    \r\n" );
        rn4678_disconnect( &rn4678 );
    }
    else if ( dev_type == RN4678_DEVICE_TYPE_SLAVE )
    {
        msg_flag = rn4678_read( &rn4678, &MESSAGE_DATA[ 0 ] );

        if ( msg_flag == 1 )
        {
            log_printf( &logger, " %s \r\n", log_text );
        }
    }
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rn4678

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
