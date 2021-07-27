

---
# Compass 2 click

Compass 2 click carries the AK8963 3-axis electronic compass. The AK8963 sensor is based on the Hall effect.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/compass2_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/compass-2-click)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Compass2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Compass2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void compass2_cfg_setup ( compass2_cfg_t *cfg ); 
 
- Initialization function.
> COMPASS2_RETVAL compass2_init ( compass2_t *ctx, compass2_cfg_t *cfg );

- Click Default Configuration function.
> void compass2_default_cfg ( compass2_t *ctx );


#### Example key functions :

- This function gets the data from one specified axis.
> int16_t compass2_get_axis_data ( compass2_t *ctx, uint8_t axis );
 
- This function prepares the device for a new measurement.
> void compass2_new_measurement ( compass2_t *ctx );

- This function does a hardware reset of the device.
> void compass2_reset ( compass2_t *ctx ); 

## Examples Description

> The example prepares the device for a new measurement and reads and displays data from all three axes.

**The demo application is composed of two sections :**

### Application Init 

> Initializes and configures the click and logger modules.

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    compass2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    compass2_cfg_setup( &cfg );
    COMPASS2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    compass2_init( &compass2, &cfg );
    compass2_default_cfg( &compass2 );
}
  
```

### Application Task

> Reads and displays data from all three axes every two seconds.

```c

void application_task ( )
{
    int16_t x_axis;
    int16_t y_axis;
    int16_t z_axis;
    
    compass2_new_measurement( &compass2 );
    
    log_printf( &logger, " --- Axis ---\r\n" );

    x_axis = compass2_get_axis_data( &compass2, COMPASS2_X_AXIS );
    y_axis = compass2_get_axis_data( &compass2, COMPASS2_Y_AXIS );
    z_axis = compass2_get_axis_data( &compass2, COMPASS2_Z_AXIS );
    
    log_printf( &logger, "X: %d\r\n", x_axis );
    log_printf( &logger, "Y: %d\r\n", y_axis );
    log_printf( &logger, "Z: %d\r\n", z_axis );

    log_printf( &logger, "----------------\r\n" );
    
    Delay_ms( 2000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Compass2

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
