\mainpage Main Page
 
 

---
# Buck 13 click

Buck 13 Click is a high-efficiency step-down converter which provides a highly regulated output voltage derived from the connected power source, rated from 4.5V to 5.5V. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/buck13_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/buck-13-click>)

---


#### Click library 

- **Author**        : Petar Suknjaja
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Buck13 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Buck13 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void buck13_cfg_setup ( buck13_cfg_t *cfg ); 
 
- Initialization function.
> BUCK13_RETVAL buck13_init ( buck13_t *ctx, buck13_cfg_t *cfg );

- Click Default Configuration function.
> void buck13_default_cfg ( buck13_t *ctx );


#### Example key functions :

- Enables the Buck 13 output.
> void buck13_enable ( buck13_t *ctx, uint8_t pwr_state );
 
- Gets the ADC values from the module.
> uint16_t buck13_get_adc( buck13_t *ctx );

- Gets the output voltage.
> uint16_t buck13_get_voltage( buck13_t *ctx );

## Examples Description
 
> This example switches the output of the Buck13 and logs the output voltage on the Vout terminal.
 
**The demo application is composed of two sections :**

### Application Init 

>Initializes driver and turns OFF the Buck 13 output as default state.
 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    buck13_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    buck13_cfg_setup( &cfg );
    BUCK13_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck13_default_cfg ( &buck13 );
    buck13_init( &buck13, &cfg );
    log_info( &logger, "Buck 13 is enabled now" );
}
  
```

### Application Task

> Displays the output voltage every 2 seconds.

```c

void application_task ( void )
{
    //  Task implementation.

    buck13_enable( &buck13, BUCK13_ENABLE ); 
    out_voltage = buck13_get_voltage( &buck13 );
    log_printf( &logger, "Vout =  %d mV\r\n", out_voltage );
    
    Delay_ms( 2000 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck13

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
