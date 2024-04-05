
---
# BT-EZ click

The BT-EZ click is a Click board™ which provide BLE connectivity for any embedded application.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/btez_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/bt-ez-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type


# Software Support

We provide a library for the BtEz Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly from compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for BtEz Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void btez_cfg_setup ( btez_cfg_t *cfg ); 
 
- Initialization function.
> BTEZ_RETVAL btez_init ( btez_t *ctx, btez_cfg_t *cfg );

#### Example key functions :

- Generic write function.
> void btez_generic_write ( btez_t *ctx, char *data_buf, uint16_t len );
 
- Generic read function.
> int32_t btez_generic_read ( btez_t *ctx, char *data_buf, uint16_t max_len );

- Send command function.
> void btez_send_command ( btez_t *ctx, char *command );

## Examples Description

> This example reads and processes data from BT-EZ clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and configures the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    btez_cfg_t cfg;

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

    btez_cfg_setup( &cfg );
    BTEZ_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    btez_init( &btez, &cfg );
    Delay_ms ( 100 );

    log_printf( &logger, "Configuring the module...\r\n" );
    config_mode = 1;
    
    btez_module_reset( &btez );
    btez_process( );
    btez_send_command( &btez, CMD_PING );
    btez_process( );
    btez_send_command( &btez, CMD_DEVICE_NAME );
    btez_process( );
    btez_send_command( &btez, CMD_SAVE );
    btez_process( );
    btez_send_command( &btez, CMD_GDN );
    btez_process( );
    
    config_mode = 0;
    log_printf( &logger, "The module has been configured.\r\n" );
    Delay_1sec( );
}
  
```

### Application Task

> Checks for the received data, reads it and replies with a certain message.

```c

void application_task ( void )
{
    btez_process( );
} 

```
 
## Note

> We have used the Serial Bluetooth Terminal smartphone application for the test. 
> A smartphone and the click board must be paired in order to exchange messages with each other.

The full application code, and ready to use projects can be installed directly from compilers IDE(recommended) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.BtEz

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
