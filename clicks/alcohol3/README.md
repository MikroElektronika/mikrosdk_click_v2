\mainpage Main Page
 
 

---
# Alcohol 3 click

Alcohol 3 click is a gas sensor Click board, that reacts to the presence of deoxidizing and reducing gases, such as ethanol (also known as alcohol).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/alcohol3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/alcohol-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : nov 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Alcohol3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Alcohol3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void alcohol3_cfg_setup ( alcohol3_cfg_t *cfg ); 
 
- Initialization function.
> ALCOHOL3_RETVAL alcohol3_init ( alcohol3_t *ctx, alcohol3_cfg_t *cfg );

- Click Default Configuration function.
> void alcohol3_default_cfg ( alcohol3_t *ctx );


#### Example key functions :

- This function reads CO (Carbon monoxide) data in ppm (1 ppm - 1000 ppm).
> uint16_t alcohol3_get_co_in_ppm ( alcohol3_t *ctx );
 
- This function reads percentage of alcohol in the blood (BAC).
> float alcohol3_get_percentage_bac ( alcohol3_t *ctx );

- This function reads 12bit ADC value.
> uint16_t alcohol3_get_adc_data ( alcohol3_t *ctx );

## Examples Description
 
> Code of this sensor reacts to the presence of deoxidizing and reducing gases,
> such as ethanol (also known as alcohol).

**The demo application is composed of two sections :**

### Application Init 

> Application Init performs Logger and Click initialization.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    alcohol3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_printf( &logger, "--------------------------\r\n\n" );
    log_printf( &logger, "     Application  Init\r\n" );
    Delay_ms ( 100 );

    //  Click initialization.

    alcohol3_cfg_setup( &cfg );
    ALCOHOL3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    alcohol3_init( &alcohol3, &cfg );

    log_printf( &logger, "--------------------------\r\n\n" );
    log_printf( &logger, " ---- Alcohol 3 Click ----\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 1000 );

    log_printf( &logger, " ---- Initialization ---\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 1000 );
}
  
```

### Application Task

> Reads percentage of alcohol in the blood (BAC) 
> and this data logs to USBUART every 1 sec.

```c

void application_task ( void )
{
    uint16_t co_ppm;
    uint16_t p_bac;

    //  Task implementation.

    log_printf( &logger, " --- Alcohol diagnostics ---- \r\n" );

    co_ppm = alcohol3_get_co_in_ppm ( &alcohol3 );
    log_printf( &logger, " co in ppm  %d    | \r\n", co_ppm );

    p_bac = alcohol3_get_percentage_bac( &alcohol3 ) * 1000;

    if ( 10 > p_bac && p_bac < 100 )
    {
        log_printf( &logger, " BAC    %d  | 0.00\r\n", p_bac );
    }
    else if ( 100 <= p_bac && 1000 > p_bac )
    {
        log_printf( &logger, " BAC    %d  | 0.00\r\n", p_bac );
    }
    else if ( p_bac >= 1000 )
    {
        log_printf( &logger, " BAC    %d  | 0.\r\n", p_bac );
    }
    else
    {
        log_printf( &logger, " BAC  | 0.0000\r\n" );
    }
    log_printf( &logger, " ---------------------------- \r\n" );

    Delay_ms( 1000 );
} 

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Alcohol3

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
