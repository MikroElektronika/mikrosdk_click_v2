
---
# SHT1x click

SHT11 Click is an accessory board in mikroBus™ form factor. It includes a digital humidity and temperature sensor SHT11.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/sht1x_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/sht1x-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the Sht1x Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Sht1x Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void sht1x_cfg_setup ( sht1x_cfg_t *cfg ); 
 
- Initialization function.
> SHT1X_RETVAL sht1x_init ( sht1x_t *ctx, sht1x_cfg_t *cfg );

- Click Default Configuration function.
> void sht1x_default_cfg ( sht1x_t *ctx );


#### Example key functions :

- Set pin on output.
> void sht1x_output_sda ( sht1x_t *ctx, sht1x_cfg_t *cfg );
 
- Set pin on input.
> void sht1x_input_sda ( sht1x_t *ctx, sht1x_cfg_t *cfg );

- Set SDA high function.
> void sht1x_sda_high ( sht1x_t *ctx );

## Examples Description

> This click measures temperature and humidity.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables GPIO.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    sht1x_cfg_setup( &cfg );
    SHT1X_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    sht1x_init( &sht1x, &cfg );
}
  
```

### Application Task

> This example demonstrates the use of SHT1x Click board by measuring 
  temperature and humidity, and displays the results on USART terminal.

```c

void application_task ( void )
{
    sht1x_read_results( &temperature, &humidity );
    log_printf( &logger, " Temperature: %.2f ", temperature );
    log_printf( &logger, " C \r\n" );
  
    log_printf( &logger, " Humidity: %.2f ", humidity );
    log_printf( &logger, " %% \r\n", humidity );
    
    Delay_ms( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Sht1x

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
