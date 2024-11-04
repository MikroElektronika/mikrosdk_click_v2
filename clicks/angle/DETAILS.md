

---
# Angle Click

Angle Click is a precise Hall-effect angle sensing Click board that can be used to measure the rotational angle of the magnetic field in the X-Y plane above it (parallel to the surface of the Click), through the whole range of 360°. The Click yields very precise results for both off-axis and axis operation, which make it a perfect choice for precise measuring of the rotational angle in a wide range of different high-speed applications, for example in the automotive industry: electronic power steering, transmission, torsion bar, or the motor shaft rotation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/angle_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/angle-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Angle Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Angle Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void angle_cfg_setup ( angle_cfg_t *cfg ); 
 
- Initialization function.
> ANGLE_RETVAL angle_init ( angle_t *ctx, angle_cfg_t *cfg );

- Click Default Configuration function.
> void angle_default_cfg ( angle_t *ctx );


#### Example key functions :

- This function reads angle value.
> uint16_t angle_get_angle ( angle_t *ctx );
 
- This function reads temperature value.
> uint16_t angle_get_temperature ( angle_t *ctx );

- This function reads magnetics value.
> uint16_t angle_get_magnetics ( angle_t *ctx );


## Examples Description

> Angle Click is a precise Hall-effect angle sensing Click board that can be used to measure 
> the rotational angle of the magnetic field in the X-Y plane above it.

**The demo application is composed of two sections :**

### Application Init 

> Driver intialization and Angle settings mode

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    angle_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    angle_cfg_setup( &cfg );
    ANGLE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    angle_init( &angle, &cfg );
    angle_default_cfg ( &angle );
}
  
```

### Application Task

> Reads angle and magnetics data values and displays it in the terminal.

```c

void application_task ( void )
{
    angle_val = angle_get_angle( &angle );
    log_printf( &logger, "Angle :%d \r\n", angle_val );
    
    magnetics_val = angle_get_magnetics( &angle );
    log_printf( &logger, "Magnetics :%d \r\n", magnetics_val );
    
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Angle

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
