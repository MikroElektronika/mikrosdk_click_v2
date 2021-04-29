
---
# 3D Hall 6 click

3D Hall 6 Click is a very accurate, magnetic field sensing Click board™, used to measure the intensity of the magnetic field across three perpendicular axes. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/3dhall6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/3d-hall-6-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the 3dHall6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 3dHall6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c3dhall6_cfg_setup ( c3dhall6_cfg_t *cfg ); 
 
- Initialization function.
> C3DHALL6_RETVAL c3dhall6_init ( c3dhall6_t *ctx, c3dhall6_cfg_t *cfg );

- Click Default Configuration function.
> void c3dhall6_default_cfg ( c3dhall6_t *ctx );

#### Example key functions :

- This function sets reference values for voltage and angle calculations.
> void c3dhall6_set_reference_values ( c3dhall6_t *ctx, float reference_voltage, float ref_adc_ch0, float ref_adc_ch1, float ref_adc_ch2, float ref_adc_ch3 );
 
- This function reads ADC value on selected channel.
> void c3dhall6_get_adc_value ( c3dhall6_t *ctx, uint8_t channel_no, uint16_t *adc_value );

- This function reads ADC value on selected channel and converts that value to Volts or miliVolts - depending on reference voltage setting.
> void c3dhall6_get_volt( c3dhall6_t *ctx, uint8_t channel_no, float *channel_voltage );

## Examples Description

> This application measure the intensity of the magnetic field across three perpendicular axes.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c3dhall6_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c3dhall6_cfg_setup( &cfg );
    C3DHALL6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3dhall6_init( &c3dhall6, &cfg );

    Delay_ms( 300 );
    c3dhall6_set_reference_values( &c3dhall6, 3.3, 2048.0, 2048.0, 2048.0, 2048.0 );
}
  
```

### Application Task

> Additional Functions :
>
> - c3dhall6_log_adc_task() - performs and logs adc measurements on all channels
> - c3dhall6_log_volt_task() - performs and logs voltage measurements on all channels
> - c3dhall6_log_angleRad_task() - performs and logs angle measurements in radians on each die
> - c3dhall6_log_angleDeg_task() - performs and logs angle measurements in degrees on each die 

```c

void application_task ( void )
{
    c3dhall6_log_angle_deg_task( );
    Delay_ms( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.3dHall6

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
