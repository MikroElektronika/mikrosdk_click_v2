\mainpage Main Page
 
---
# Angle 2 Click

Angle 2 Click is a magnetic rotational sensor which relies on the ultra-fast MA700 angular sensor IC. Due to a high data output rate of 500kHz, the MA700 IC is able to provide a reliable absolute angular positional data at speeds up to 100,000 RPM.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/angle2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/angle-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Angle2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Angle2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void angle2_cfg_setup ( angle2_cfg_t *cfg ); 
 
- Initialization function.
> ANGLE2_RETVAL angle2_init ( angle2_t *ctx, angle2_cfg_t *cfg );

- Click Default Configuration function.
> void angle2_default_cfg ( angle2_t *ctx );


#### Example key functions :

- This function reads angle data from the Click module.
> double angle2_get_angle ( angle2_t *ctx );
 
- This function reads angle and time index data from the Click module.
> double angle2_get_angle_with_time_index ( angle2_t *ctx, uint8_t *time_index );

- This function sets the zero scale value.
> void angle2_set_zero_scale ( angle2_t *ctx, double zero_deg );

## Examples Description

> This example showcases how to configure and use the Angle 2 Click. This Click senses
  the magnetic field along the horizontal plane using an array of Hal effect sensors.
  The module uses advanced Spinaxis technology based on a direct angle sampling app-
  roach in order to provide reliable data quickly. 

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the Click and logger modules. Additional con-
  figuring is done in the default_cfg(...) function. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    angle2_cfg_t cfg;

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
    Delay_ms ( 100 );

    //  Click initialization.

    angle2_cfg_setup( &cfg );
    ANGLE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    angle2_init( &angle2, &cfg );

    Delay_ms ( 300 );
    angle2_default_cfg( &angle2 );
    Delay_ms ( 200 );

    log_printf( &logger, " * Angle 2 initialized * \r\n" );
}
  
```

### Application Task

> This function reads angle data from the Click module and displays that data using the
  UART console every 200 miliseconds.

```c

void application_task ( void )
{
    double angle;

    angle = angle2_get_angle( &angle2 );

    log_printf( &logger, " Angle: %.2f deg\r\n", angle );

    Delay_ms ( 200 );
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Angle2

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
