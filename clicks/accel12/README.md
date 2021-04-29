\mainpage Main Page
 
 

---
# Accel 12 click

Accel 12 click is an advanced 3-axis motion tracking Click board™, which utilizes the MC3216, a low-noise, and low power 3-axis accelerometer.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/accel12_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/accel-12-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Accel12 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Accel12 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void accel12_cfg_setup ( accel12_cfg_t *cfg ); 
 
- Initialization function.
> ACCEL12_RETVAL accel12_init ( accel12_t *ctx, accel12_cfg_t *cfg );

- Click Default Configuration function.
> void accel12_default_cfg ( accel12_t *ctx );


#### Example key functions :

- Functions for configuration one register
> void accel12_configuration ( accel12_t *ctx, uint8_t reg, uint8_t data_in );
 
- Functions for read one Accel axis data
> int16_t accel12_get_one_axis ( accel12_t *ctx, uint8_t axis );

- Functions for read Accel axis data
> void accel12_get_axis_data ( accel12_t *ctx, int16_t *x_axis, int16_t *y_axis, int16_t *z_axis);

## Examples Description

> This application allows acceleration measurement in three perpendicular axes.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init and configuration Accel measuremen and Tap detection interrupt

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    accel12_cfg_t cfg;
    uint8_t temp;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    accel12_cfg_setup( &cfg );
    ACCEL12_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel12_init( &accel12, &cfg );

    accel12_default_cfg( &accel12 );
    
    log_printf( &logger, "--- Start measurement --- \r\n" );
}
  
```

### Application Task

> Reads the acceleration data in 3 axis and detects the tap on the axes. All data logs on the USBUART every 1.5sec.

```c

void application_task ( void )
{
    int16_t X_Axis;
    int16_t Y_Axis;
    int16_t Z_Axis;
    uint8_t tap;

    /* Accelerometer measurement */
    accel12_get_axis_data( &accel12, &X_Axis, &Y_Axis, &Z_Axis );

    log_printf( &logger, " X axis : %d \r\n", X_Axis );

    log_printf( &logger, " Y axis : %d \r\n", Y_Axis );

    log_printf( &logger, " Z axis : %d \r\n", Z_Axis );

    /* TAP interrupt */
    tap = accel12_get_tap_detection( &accel12 );
    switch ( tap )
    {
        case 1:
        {
            log_printf( &logger, " X positive \r\n" );
            break;
        }
        case 2:
        {
            log_printf( &logger, " Y positive \r\n" );
            break;
        }
        case 3:
        {
            log_printf( &logger, " Z positive \r\n" );
            break;
        }
        case 4:
        {
            log_printf( &logger, " X negative \r\n" );
            break;
        }
        case 5:
        {
            log_printf( &logger, " Y negative \r\n" );
            break;
        }
        case 6:
        {
            log_printf( &logger, " Z negative \r\n" );
            break;
        }
    }
    log_printf( &logger, " -------------------------------- \r\n" );
    Delay_ms( 1500 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel12

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
