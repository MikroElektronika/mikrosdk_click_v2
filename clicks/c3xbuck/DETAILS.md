
---
# 3 x Buck click

3xBuck click is a triple step-down (buck) converter Click board™. It features three independent output terminals that can provide 1.8V, 3.3V, and 5V with the combined current output up to 3A. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/3xbuck_click.png">
</p>

[click Product page](https://www.mikroe.com/3xbuck-click)

---


#### Click library 

- **Author**        : Petar Suknjaja
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the 3xBuck Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 3xBuck Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c3xbuck_cfg_setup ( c3xbuck_cfg_t *cfg ); 
 
- Initialization function.
> C3XBUCK_RETVAL c3xbuck_init ( c3xbuck_t *ctx, c3xbuck_cfg_t *cfg );

- Click Default Configuration function.
> void c3xbuck_default_cfg ( c3xbuck_t *ctx );


#### Example key functions :

- This function enables desired Buck on the click.
> void c3xbuck_enable_buck ( c3xbuck_t *ctx, uint8_t buck );
 
- This function disables desired Buck on the click.
> void c3xbuck_disable_buck ( c3xbuck_t *ctx, uint8_t buck );

- This function sets voltage on desired Buck.
> void c3xbuck_set_voltage ( c3xbuck_t *ctx, uint8_t buck, uint8_t voltage );

## Examples Description
 
> This example demonstrates the use of the 3 x Buck Click Board.


**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c3xbuck_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c3xbuck_cfg_setup( &cfg );
    C3XBUCK_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3xbuck_init( &c3xbuck, &cfg );
    Delay_ms( 100 );
    
    c3xbuck_default_cfg ( &c3xbuck );
    log_info( &logger, "---- Application Task ----" );
}
  
```

### Application Task

> Alternates between predefined and default values for the Bucks output and logs the current set values on the USB UART.

```c

void application_task ( void )
{
    //  Task implementation.
    log_printf( &logger, "Setting predefined values : \r\n" );
    log_printf( &logger, "Buck 1 : 1000 mV\r\n");
    log_printf( &logger, "Buck 2 : 1250 mV\r\n");
    log_printf( &logger, "Buck 3 : 1500 mV\r\n");
    
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_1, C3XBUCK_OUTPUT_VOLTAGE_1000mV );
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_2, C3XBUCK_OUTPUT_VOLTAGE_1250mV );
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_3, C3XBUCK_OUTPUT_VOLTAGE_1500mV );
    
    Delay_ms( 10000 );
    
    log_printf( &logger, "Setting default values: \r\n");
    log_printf( &logger, "Buck 1 : 1800 mV\r\n");
    log_printf( &logger, "Buck 2 : 3300 mV\r\n");
    log_printf( &logger, "Buck 3 : 5000 mV\r\n");
    
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_1, C3XBUCK_BUCK_DEFAULT_OUTPUT_VOLTAGE );
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_2, C3XBUCK_BUCK_DEFAULT_OUTPUT_VOLTAGE );
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_3, C3XBUCK_BUCK_DEFAULT_OUTPUT_VOLTAGE );
    
    Delay_ms( 5000 );
}

```

## Note

> The default output voltage on Buck 1 is 1800mV, Buck 2 is 3300mV, and Buck 3 is 5000mV.
> Configurable output voltage on all Bucks ranges from 680mV to 1950mV.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.3xBuck

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
