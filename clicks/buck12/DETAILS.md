
---
# Buck 12 click

Buck 12 Click is a high-efficiency step-down converter which provides 3.3V on its output, derived from the connected power supply voltage, in the range from 4.2V to 18V.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/buck12_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/buck-12-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Buck12 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Buck12 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void buck12_cfg_setup ( buck12_cfg_t *cfg ); 
 
- Initialization function.
> BUCK12_RETVAL buck12_init ( buck12_t *ctx, buck12_cfg_t *cfg );

- Click Default Configuration function.
> void buck12_default_cfg ( buck12_t *ctx );


#### Example key functions :

- This function for enable or disable device.
> void buck12_control ( buck12_t *ctx, uint8_t ctrl );
 
- This function reads ADC on the channel.
> uint16_t buck12_get_channel_adc ( buck12_t *ctx, uint8_t channel );

- This function gets Voltage.
> float buck12_get_voltage ( buck12_t *ctx, uint8_t select_volt );

## Examples Description

> This demo application reads the voltage in [mV] at the input and output terminals.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    buck12_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    buck12_cfg_setup( &cfg );
    BUCK12_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck12_init( &buck12, &cfg );

    buck12_control( &buck12, BUCK12_ENABLE );
    Delay_ms( 2000 );
}
  
```

### Application Task

> Reads the voltage in [mV] at the input and output terminals.
> This data logs to the USBUART every 2 sec.

```c

void application_task ( void )
{
    float voltage;

    voltage = buck12_get_voltage( &buck12, BUCK12_INPUT_VOLTAGE );
    
    log_printf( &logger, "* Vin : %f mV \r\n ", voltage);
    
    voltage = buck12_get_voltage( &buck12, BUCK12_OUTPUT_VOLTAGE );

    log_printf( &logger, "* Vout : %f mV \r\n ", voltage);

    log_printf( &logger, "--------------------------\r\n");
    Delay_ms( 2000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck12

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
