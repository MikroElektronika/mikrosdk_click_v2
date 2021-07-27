\mainpage Main Page
 
 

---
# MCP16331 click

MCP16331 click functions as a buck-boost voltage regulator, a switching regulator topology that combines principles of the buck conversion (step-down) and the boost conversion (step-up).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mcp16331_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/mcp16331-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Mcp16331 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Mcp16331 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mcp16331_cfg_setup ( mcp16331_cfg_t *cfg ); 
 
- Initialization function.
> MCP16331_RETVAL mcp16331_init ( mcp16331_t *ctx, mcp16331_cfg_t *cfg );

#### Example key functions :

- mcp16331 set vout
> void mcp16331_set_vout ( mcp16331_t *ctx, uint16_t millivolts_vout );

## Examples Description

> This application is buck-boost voltage regulator.

**The demo application is composed of two sections :**

### Application Init 

> Sends hal pointers, and initializes click

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    mcp16331_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mcp16331_cfg_setup( &cfg );
    MCP16331_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mcp16331_init( &mcp16331, &cfg );
}
  
```

### Application Task

> Switches between 5 V and 12 V values

```c

void application_task ( void )
{
    mcp16331_set_vout( &mcp16331, 5000 );
    delay_ms( 3000 );
    mcp16331_set_vout( &mcp16331, 12000 );
    delay_ms( 3000 );
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Mcp16331

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
