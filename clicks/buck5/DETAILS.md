
---
# Buck 5 click

Buck 5 Click is a high-efficiency buck (step-down) DC/DC converter, which can provide digitally adjusted step-down voltage on its output while delivering a considerable amount of current. Buck 5 click accepts a wide voltage range on its input - from 5V to 30V. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/buck5_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/buck-5-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : sep 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Buck5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Buck5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void buck5_cfg_setup ( buck5_cfg_t *cfg ); 
 
- Initialization function.
> BUCK5_RETVAL buck5_init ( buck5_t *ctx, buck5_cfg_t *cfg );


#### Example key functions :

- This function wake up the chip.
> void buck5_power_on ( buck5_t *ctx );
 
- This function reset the chip.
> void buck5_reset ( buck5_t *ctx );

- Maximum output voltage is 5.5V (255 set value), and minimum output voltage is 1V (0 set value).
> void buck5_set_output_voltage ( buck5_t *ctx, uint8_t voltage );

## Examples Description

> Buck 5 Click is a high-efficiency buck DC/DC converter, which can provide digitally 
> adjusted step-down voltage on its output while delivering a considerable amount of current. 
> Buck 5 click accepts a wide voltage range on its input - from 5V to 30V. The output voltage 
> may be adjusted via the SPI interface, in the range from 0.9V to approximately 5.5V.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init, power On chip and reset buck 5 click.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    buck5_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    buck5_cfg_setup( &cfg );
    BUCK5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck5_init( &buck5, &cfg );

    buck5_power_on( &buck5 );
    buck5_reset( &buck5 );
}
  
```

### Application Task

> Sets 3 different output voltages every 2 seconds.

```c

void application_task ( void )
{
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_1500mV );
    Delay_ms( 2000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_3000mV );
    Delay_ms( 2000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_4500mV );
    Delay_ms( 2000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_3000mV );
    Delay_ms( 2000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck5

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
