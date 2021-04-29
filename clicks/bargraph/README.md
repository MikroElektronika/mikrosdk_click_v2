\mainpage Main Page
 
 

---
# BarGraph click

BarGraph click is a 10-segment bar graph display click, which uses a high-quality bar graph LED display. The bar graph display is a very popular device for displaying various properties, whether it be an audio level, current/voltage level, the position of the encoder, or any other property that can be displayed in a form of a bar graph.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/bargraph_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/bargraph-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the BarGraph Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for BarGraph Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void bargraph_cfg_setup ( bargraph_cfg_t *cfg ); 
 
- Initialization function.
> BARGRAPH_RETVAL bargraph_init ( bargraph_t *ctx, bargraph_cfg_t *cfg );

- Generic transfer function.
> void bargraph_generic_transfer ( bargraph_t *ctx, spi_master_transfer_data_t *block );


#### Example key functions :

- Functions for initializes the chip.
> void bargraph_driver_init ( bargraph_t *ctx );
 
- Functions for reset the chip.
> void bargraph_reset ( bargraph_t *ctx );

- Displays function.
> void bargraph_display( bargraph_t *ctx, uint8_t input );

## Examples Description

> This application uses a high-quality bar graph LED display. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init and BarGraph init. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    bargraph_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    bargraph_cfg_setup( &cfg );
    BARGRAPH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    bargraph_init( &bargraph, &cfg );
}
  
```

### Application Task

> Counter passes through the loop and logs the value of the counter on the bargraph display.

```c

void application_task ( void )
{
    for ( cnt = 0; cnt <= 10; cnt++ )
    {
        bargraph_display( &bargraph, cnt );
        Delay_ms( 500 );
    }
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.BarGraph

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
