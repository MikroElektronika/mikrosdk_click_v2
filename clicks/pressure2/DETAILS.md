

---
# Pressure 2 click

Pressure 2 click carries MS5803, a high resolution MEMS pressure sensor that is both precise and robust.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pressure_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/pressure-2-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Pressure2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Pressure2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void pressure2_cfg_setup ( pressure2_cfg_t *cfg ); 
 
- Initialization function.
> PRESSURE2_RETVAL pressure2_init ( pressure2_t *ctx, pressure2_cfg_t *cfg );

- Click Default Configuration function.
> void pressure2_default_cfg ( pressure2_t *ctx );


#### Example key functions :

- This function read calibration coefficients and return coefficient.
> uint16_t pressure2_read_coefficient ( pressure2_t *ctx, uint8_t index );

- This function preforms ADC conversion and return 24bit result.
> uint32_t pressure2_send_CmdADC ( pressure2_t *ctx, uint8_t cmd );

- Functions for readding sensor.
> void pressure2_read_sensor ( pressure2_t *ctx, float *P, float *T );

## Examples Description

> This application measures pressure in range from 0 to 14 bars (with a resolution of up to 0.2 mbars), but because of the stainless 
> steel cap enclosure, the sensor can withstand up to 30 bars of pressure.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init and chip init.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure2_cfg_t cfg;
    float pressure_res;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    pressure2_cfg_setup( &cfg );
    PRESSURE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure2_init( &pressure2, &cfg );
}
  
```

### Application Task

> Reads sensor and logs to USBUART pressure and temperature every second. 

```c

void application_task ( void )
{
    pressure2_read_sensor( &pressure2, &pressure_p, &pressure_t );
    
    log_printf( &logger,"Pressure: %.2f\r\n", pressure_p );
    log_printf( &logger,"Temperature: %.2f\r\n", pressure_t );

    Delay_ms( 1000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure2

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
