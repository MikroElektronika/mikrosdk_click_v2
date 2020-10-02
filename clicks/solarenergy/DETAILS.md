
---
# SOLAR ENERGY click

There are many battery chargers and solar energy harvesters out there already, but the Solar energy click has the unique feature - it encompasses both of these devices in a single package. The click uses Texas Instruments BQ25570 - a nano-power high-efficiency boost charger and buck converter device, designed to work with very low power energy harvesting elements, such as the photovoltaic and thermoelectric generators


<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/solarenergy_click.png" height=300px>
</p>



[click Product page](<https://www.mikroe.com/solar-energy-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the SolarEnergy Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for SolarEnergy Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void solarenergy_cfg_setup ( solarenergy_cfg_t *cfg ); 
 
- Initialization function.
> SOLARENERGY_RETVAL solarenergy_init ( solarenergy_t *ctx, solarenergy_cfg_t *cfg );


#### Example key functions :

- Charge enable function.
> void solarenergy_charge_enable ( solarenergy_t *ctx );
 
- Charge disable functions.
> void solarenergy_charge_disable ( solarenergy_t *ctx );

- Battery good indicator functions.
> uint8_t solarenergy_check_indicator ( solarenergy_t *ctx );

## Examples Description

> This application charge the batery when is empty.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - GPIO and start to write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    solarenergy_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    solarenergy_cfg_setup( &cfg );
    SOLARENERGY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    solarenergy_init( &solarenergy, &cfg );

    log_printf( &logger, "   Initialization   \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, " Charge the battery \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms( 1000 );
}
  
```

### Application Task

> This is an example which demonstrates the use of Solar Energy Click board. The following example will charge the battery if it is empty, and stop charging when the battery is full. When battery full status is detected, the device is disabled, but will check battery status every 10 seconds. Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void )
{
    if ( solarenergy_check_indicator( &solarenergy ) )
    {
        solarenergy_charge_disable( &solarenergy );
        Delay_ms ( 10000 );
    }
    else
    {
        solarenergy_charge_enable( &solarenergy );
    }
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.SolarEnergy

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
