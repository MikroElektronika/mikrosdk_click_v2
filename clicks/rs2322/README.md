\mainpage Main Page
 
---
# RS232 2 click

The RS232 communication standard is established back in the ‘60s, but thanks to its implementation on a wide range of devices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rs2322_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rs232-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the Rs2322 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rs2322 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rs2322_cfg_setup ( rs2322_cfg_t *cfg ); 
 
- Initialization function.
> RS2322_RETVAL rs2322_init ( rs2322_t *ctx, rs2322_cfg_t *cfg );

#### Example key functions :

- This function sets CTS pin state.
> void rs2322_set_cts ( rs2322_t *ctx, uint8_t state );
 
- This function get DTR pin state.
> uint8_t rs2322_get_dtr ( rs2322_t *ctx );

- Function for send command.
> void rs2322_send_command ( rs2322_t *ctx, char *command );

## Examples Description

> This example reads and processes data from RS232 2 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rs2322_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rs2322_cfg_setup( &cfg );
    RS2322_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs2322_init( &rs2322, &cfg );
}
  
```

### Application Task

> Reads the received data.

```c

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    rs2322_process( );
#endif    
    
#ifdef DEMO_APP_TRANSMITER
    rs2322_send_command( &rs2322, TEXT_TO_SEND );
    rs2322_process( );
    Delay_ms( 2000 );
#endif    
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rs2322

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
