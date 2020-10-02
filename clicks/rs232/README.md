\mainpage Main Page
 
---
# RS232 click

RS232 click provides an interface between the TTL/CMOS logic levels commonly used on microcontrollers and the RS-232 bus.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rs232_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/rs232-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the Rs232 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rs232 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rs232_cfg_setup ( rs232_cfg_t *cfg ); 
 
- Initialization function.
> RS232_RETVAL rs232_init ( rs232_t *ctx, rs232_cfg_t *cfg );

#### Example key functions :

- Get CTS pin state (Clear to send)
> uint8_t rs232_get_cts_state ( rs232_t *ctx );
 
- Set RTS pin state
> void rs232_set_rts_state ( rs232_t *ctx, uint8_t state );

- Function for send command
> void rs232_send_command ( rs232_t *ctx, char *command );

## Examples Description

> This example reads and processes data from RS232 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rs232_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rs232_cfg_setup( &cfg );
    RS232_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs232_init( &rs232, &cfg );
}
  
```

### Application Task

> Reads the received data.

```c

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    rs232_process( );
#endif    
    
#ifdef DEMO_APP_TRANSMITER
    rs232_send_command( &rs232, TEXT_TO_SEND );
    rs232_process( );
    Delay_ms( 2000 );
#endif    
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rs232

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
