
# 3XBUCK click

3xBuck click is a triple step-down (buck) converter Click board™. It features three independent output terminals that can provide 1.8V, 3.3V, and 5V with the combined current output up to 3A. 

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/3xbuck_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/3xbuck-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the 3xbuck Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 3xbuck Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c3xbuck_cfg_setup ( c3xbuck_cfg_t *cfg ); 
 
- Initialization function.
> c3xbuck_RETVAL c3xbuck_init ( c3xbuck_t *ctx, c3xbuck_cfg_t *cfg );

- Click Default Configuration function.
> void c3xbuck_default_cfg ( c3xbuck_t *ctx );


#### Example key functions :

- Function for enable Buck.
> void c3xbuck_enable_buck ( c3xbuck_t *ctx, uint8_t buck );
 
- Function for enable Buck.
> void c3xbuck_enable_buck ( c3xbuck_t *ctx, uint8_t buck );

- Function for disable Buck.
> void c3xbuck_disable_buck ( c3xbuck_t *ctx, uint8_t buck );

## Examples Description

> This specific selection of output voltages makes this Click board™ a perfect choice for an embedded application power supply, as these voltages are the most commonly used values.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver init, enable and configuration Buck 1, Buck 2 and Buck 3.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c3xbuck_cfg_t cfg;

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    c3xbuck_cfg_setup( &cfg );
    c3xbuck_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3xbuck_init( &c3xbuck, &cfg );
    c3xbuck_default_cfg ( &c3xbuck );
}
  
```

### Application Task

> Sets variable output voltage and default output voltage. 

```c

void application_task ( void )
{
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_1, C3XBUCK_OUTPUT_VOLTAGE_1000mV );
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_2, C3XBUCK_OUTPUT_VOLTAGE_1250mV );
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_3, C3XBUCK_OUTPUT_VOLTAGE_1500mV );
    Delay_ms( 5000 );
    
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_1, C3XBUCK_BUCK_DEFAULT_OUTPUT_VOLTAGE );
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_2, C3XBUCK_BUCK_DEFAULT_OUTPUT_VOLTAGE );
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_3, C3XBUCK_BUCK_DEFAULT_OUTPUT_VOLTAGE );
    Delay_ms( 5000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.3xbuck

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
