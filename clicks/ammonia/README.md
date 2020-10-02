\mainpage Main Page
 
---
# Ammonia click

Ammonia Click is an Ammonia detection (NH3) sensor, based on the MQ-137 gas sensor. This gas sensor has a sensitive layer made of SnO2, which changes its resistance when exposed to ammonia. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ammonia_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/ammonia-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Ammonia Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ammonia Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ammonia_cfg_setup ( ammonia_cfg_t *cfg ); 
 
- Initialization function.
> AMMONIA_RETVAL ammonia_init ( ammonia_t *ctx, ammonia_cfg_t *cfg );

#### Example key functions :

- Sensor heater function
> void ammonia_heater ( ammonia_t *ctx, uint8_t state );

- Read data function
> uint32_t ammonia_data_read ( ammonia_t *ctx );

## Examples Description

> This demo application reads ADC value.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes SPI driver, turns on the heater, and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ammonia_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ammonia_cfg_setup( &cfg );
    AMMONIA_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ammonia_init( &ammonia, &cfg );
    Delay_ms( 100 );

    ammonia_heater( &ammonia, AMMONIA_HEATER_ON );
    Delay_ms( 1000 );

    log_printf( &logger, "-------------------- \r\n" );
    log_printf( &logger, "   Ammonia  click    \r\n" );
    log_printf( &logger, "-------------------- \r\n" );
}
  
```

### Application Task

> This is an example that shows the capabilities of the ADC 9 click by reading ADC value and displaying it via UART.

```c

void application_task ( void )
{
    spi_adc_value = ammonia_data_read( &ammonia );

    log_printf( &logger, "ADC value: %s \r\n", spi_adc_value );

    Delay_ms( 1000 );
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ammonia

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
