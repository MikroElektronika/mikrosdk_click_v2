\mainpage Main Page
 
 

---
# Pressure 12 click

Pressure 12 click is a barometric gauge pressure measuring Click board™, equipped with the Amplified Basic Pressure sensor series (ABP), which features a ratiometric analog output, which is proportional to the applied pressure.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pressure12_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/pressure-12-click>)

---


#### Click library 

- **Author**        : Luka Filipovic
- **Date**          : Nov 2019.
- **Type**          : ADC type


# Software Support

We provide a library for the Pressure12 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Pressure12 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void pressure12_cfg_setup ( pressure12_cfg_t *cfg ); 
 
- Initialization function.
> PRESSURE12_RETVAL pressure12_init ( pressure12_t *ctx, pressure12_cfg_t *cfg );

- Click Default Configuration function.
> void pressure12_default_cfg ( pressure12_t *ctx );


#### Example key functions :

- Get pressure function.
> float pressure12_get_pressure ( pressure12_t *ctx );
 
- Get voltage function.
> float pressure12_get_voltage ( pressure12_t *ctx );

- Set ADC resolution function.
> void pressure12_set_adc_resolution ( pressure12_t *ctx, float adc_res );

## Examples Description

> Reads ADC value, convert ADC data to Voltage[ mV ] and pressure [ mBar ].

**The demo application is composed of two sections :**

### Application Init 

> Initializes ADC and LOG for logging data.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure12_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    pressure12_cfg_setup( &cfg );
    PRESSURE12_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure12_init( &pressure12, &cfg );
    
    log_printf( &logger, "    Pressure 12 Click\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    pressure12_default_cfg ( &pressure12 );
    Delay_ms( 100 );
}
  
```

### Application Task

> Reads ADC value, convert ADC data to Voltage[ mV ] on the AN pin and
> convert to Pressure data in mBar. All data logs to the USBUART every 3 sec.

```c

void application_task ( void )
{
    pressure12_data_t tmp;
    float pressure;
    float voltage;
    
    //  Task implementation.
    
    tmp = pressure12_generic_read ( &pressure12 );
    log_printf( &logger, " ADC value \r\n" );
    log_printf( &logger, " [ DEC ]  : %d\r\n", tmp );
    log_printf( &logger, " [ HEX ]  : 0x%x \r\n", tmp );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    
    voltage = pressure12_get_voltage( &pressure12 );
    log_printf( &logger, " Voltage  :  %.2f mV\r\n", voltage );
    
    pressure = pressure12_get_pressure( &pressure12 );
    log_printf( &logger, " Pressure : %.2f mBar\r\n", pressure );
    log_printf( &logger, "-------------------------\r\n" );
    
    Delay_ms( 3000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure12

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
