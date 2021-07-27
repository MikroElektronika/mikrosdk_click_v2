
---
# Opto Encoder 3 click

Opto Encoder 3 Click is a linear incremental optical sensor/encoder click, which can be used for the movement or rotation encoding.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/optoencoder3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/opto-encoder-3-click)

---


#### Click library 

- **Author**        : Luka Filipovic
- **Date**          : okt 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the OptoEncoder3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for OptoEncoder3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void optoencoder3_cfg_setup ( optoencoder3_cfg_t *cfg ); 
 
- Initialization function.
> OPTOENCODER3_RETVAL optoencoder3_init ( optoencoder3_t *ctx, optoencoder3_cfg_t *cfg );


#### Example key functions :

- Functions for reading number of swipes
> uint8_t optoencoder3_cnt ( optoencoder3_t *ctx );
 
- Sets state of click
> void optoencoder3_enable ( optoencoder3_t *ctx, uint8_t active );

- Sets state of all pins
> void optoencoder3_read_all_pins ( optoencoder3_t *ctx, optoencoder3_pins_t *pins );

## Examples Description

> The demo application displays the counter value or displays the status of each O pins.

**The demo application is composed of two sections :**

### Application Init 

> Configures the driver and logger, and selects the demo application mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    optoencoder3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    optoencoder3_cfg_setup( &cfg );
    OPTOENCODER3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    optoencoder3_init( &optoencoder3, &cfg );

    optoencoder3_enable ( &optoencoder3, OPTOENCODER3_ENABLE );
    
    example_setter = DEMO_CNT;
}
```

### Application Task

> Depending on the demo application mode set in the application init it:
>    - Measures and displays the value of the counter - DEMO_CNT mode; or
>    - Draws the status of each O pin - DEMO_GRAPH mode.

```c
void application_task ( void )
{
    if ( example_setter == DEMO_GRAPH )
    {
        draw_pins_status(  );
    }
    else if ( example_setter == DEMO_CNT )
    {
        view_counters(  );
    }
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.OptoEncoder3

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
