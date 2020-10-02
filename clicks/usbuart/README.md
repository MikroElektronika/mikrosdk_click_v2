\mainpage Main Page
 
---
# USB UART click

USB UART click offers a USB to asynchronous serial data (UART) interface, allowing the microcontroller based designs to communicate with the personal computer, in a very simple way.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/grupe/usb-uart-group.png" height=300px>
</p>

> * [click Product page - USB UART ](<https://www.mikroe.com/usb-uart-click>)
> * [click Product page - USB UART 2 ](<https://www.mikroe.com/usb-uart-2-click>)
> * [click Product page - USB UART 4 ](<https://www.mikroe.com/usb-uart-4-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the UsbUart Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for UsbUart Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void usbuart_cfg_setup ( usbuart_cfg_t *cfg ); 
 
- Initialization function.
> USBUART_RETVAL usbuart_init ( usbuart_t *ctx, usbuart_cfg_t *cfg );

#### Example key functions :

- Power control.
> void usbuart_pwr_ctrl ( usbuart_t *ctx, uint8_t state );
 
- Set device mode
> void usbuart_set_mode ( usbuart_t *ctx, uint8_t mode );

- Function for send command
> void usbuart_send_command ( usbuart_t *ctx, char *command );

## Examples Description

> This example reads and processes data from USB UART clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and power module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    usbuart_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    usbuart_cfg_setup( &cfg );
    USBUART_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    usbuart_init( &usbuart, &cfg );

    usbuart_pwr_ctrl( &usbuart, USBUART_POWER_ON );
    usbuart_set_cts( &usbuart, USBUART_CTS_NO_ACTIVE );
    usbuart_set_mode( &usbuart, USBUART_MODE_NORMAL );
}
  
```

### Application Task

> Reads the received data.

```c

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    usbuart_process( );
#endif    
    
#ifdef DEMO_APP_TRANSMITER
    usbuart_send_command( &usbuart, MESSAGE_TO_SENT );
    usbuart_process( );
#endif    
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.UsbUart

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
