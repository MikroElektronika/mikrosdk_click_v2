
---
# MCP73871 click

MCP73871 click is a fully integrated solution for system power delivery and Li-Po/Li-Ion battery charge management.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mcp73871_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/mcp73871-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the Mcp73871 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Mcp73871 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mcp73871_cfg_setup ( mcp73871_cfg_t *cfg ); 
 
- Initialization function.
> MCP73871_RETVAL mcp73871_init ( mcp73871_t *ctx, mcp73871_cfg_t *cfg );

#### Example key functions :

- Enable pin control
> void mcp73871_enable_pin_control ( mcp73871_t *ctx, uint8_t pin_state );
 
- Prog pin control
> void mcp73871_prog_pin_control ( mcp73871_t *ctx, uint8_t pin_state );

- Timer pin control
> void mcp73871_timer_pin_control ( mcp73871_t *ctx, uint8_t pin_state );

## Examples Description

> This application is battery charger.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the click driver, and enables the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    mcp73871_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    mcp73871_cfg_setup( &cfg );
    MCP73871_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mcp73871_init( &mcp73871, &cfg );
}
  
```

### Application Task

> This is the example of MCP73871 click functions usage.
> It enables this click, sets input current to 100mA, 
> and enables safety timer.

```c

void application_task ( void )
{
    mcp73871_enable_pin_control( &mcp73871, 1 );
    mcp73871_prog_pin_control( &mcp73871, 0 );
    mcp73871_timer_pin_control( &mcp73871, 0 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Mcp73871

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
