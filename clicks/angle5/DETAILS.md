
---
# Angle 5 Click

Angle 5 Click is a compact add-on board that detects the absolute angular position of a permanent magnet, typically a diametrically magnetized cylinder on a rotating shaft.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/angle5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/angle-5-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : sep 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Angle5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Angle5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void angle5_cfg_setup ( angle5_cfg_t *cfg ); 
 
- Initialization function.
> ANGLE5_RETVAL angle5_init ( angle5_t *ctx, angle5_cfg_t *cfg );

#### Example key functions :

- Use this function to read raw angle data
> uint16_t angle5_read_raw_angle ( angle5_t *ctx );
 
- Use this function to read angle data
> float angle5_read_angle_deg ( angle5_t *ctx );

## Examples Description

> Angle 5 Click is a magnetic rotational sensor. 
> It communicates with the target microcontroller over SPI interface.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    angle5_cfg_t cfg;

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

    angle5_cfg_setup( &cfg );
    ANGLE5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    angle5_init( &angle5, &cfg );
}
  
```

### Application Task

> Reads the angle position of the magnet and displays the results on the USB UART.

```c

void application_task ( void )
{
    float new_angle = 0;
    
    new_angle = angle5_read_angle_deg( &angle5 );
    log_printf( &logger, "Angle: %.2f\r\n", new_angle );

    Delay_ms ( 100 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Angle5

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
