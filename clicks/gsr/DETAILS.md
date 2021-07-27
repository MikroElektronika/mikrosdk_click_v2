
---

# GSR click

GSR click can be used to measure the electrodermal activity (EDA) of the human body, also known as the galvanic skin response (GSR). 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gsr_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gsr-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Gsr Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Gsr Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void gsr_cfg_setup ( gsr_cfg_t *cfg ); 
 
- Initialization function.
> GSR_RETVAL gsr_init ( gsr_t *ctx, gsr_cfg_t *cfg );

- Click Default Configuration function.
> void gsr_default_cfg ( gsr_t *ctx );


#### Example key functions :

- This function read measurement using MCP3201 ADC integrated on click board.
> uint16_t gsr_read_value ( gsr_t *ctx );

## Examples Description

> This app measure the electrodermal activity.

**The demo application is composed of two sections :**

### Application Init 

> Initializes GSR driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    gsr_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    gsr_cfg_setup( &cfg );
    GSR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gsr_init( &gsr, &cfg );
}
  
```

### Application Task

> Sequential reading of ADC and logging data 
> to UART. Operation is repeated each 500 ms.

```c

void application_task ( void )
{
    uint16_t adc_value;

    adc_value = gsr_read_value( &gsr );

    log_printf( &logger, "ADC Measurements: %u \r\n", adc_value );
    Delay_ms( 500 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Gsr

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
