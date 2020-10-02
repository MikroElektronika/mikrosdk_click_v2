 
---
# Accel 7 click

The Accel 7 click is a tri-axis acceleration sensing Click board™ powered by the KXTJ3-1057 14-bit tri-axis digital accelerometer from Kionix.  This sensor was developed using proprietary Kionix micromachining technology, resulting in high accuracy and excellent noise immunity.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/accel7_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/accel-7-click>)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Accel7 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Accel7 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void accel7_cfg_setup ( accel7_cfg_t *cfg ); 
 
- Initialization function.
> ACCEL7_RETVAL accel7_init ( accel7_t *ctx, accel7_cfg_t *cfg );

- Click Default Configuration function.
> void accel7_default_cfg ( accel7_t *ctx, uint8_t resolution, uint8_t range );


#### Example key functions :

- This function reads two bytes of data from the desired axis register.
> int16_t accel7_get_axis ( accel7_t *ctx, uint8_t axis );
 
- This function calculates the resolution and range values which are used
  in the default_cfg() function.
> void accel7_res_range_cfg ( accel7_t *ctx, uint8_t *resolution, uint8_t *range );

- This function reads the state of the interrupt pin.
> uint8_t accel7_get_interrupt_state ( accel7_t *ctx );

## Examples Description

> This example shows how data from all three axes is collected, processed and later
> displayed in the logger module.

**The demo application is composed of two sections :**

### Application Init 

> Initializes and configures the click and logger modules.

```c

void application_init (  )
{
    log_cfg_t log_cfg;
    accel7_cfg_t cfg;

    uint8_t resolution = ACCEL7_DATA_RESP_14bit;
    uint8_t range = ACCEL7_RANGE_8g;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    accel7_cfg_setup( &cfg );
    ACCEL7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel7_init( &accel7, &cfg );

    accel7_res_range_cfg( &accel7, &resolution, &range );
    accel7_default_cfg( &accel7, resolution, range );

    delay_ms( 100 );
}
  
```

### Application Task

> Reads and displays data from all three axes every second.

```c

void application_task (  )
{
    int16_t x_axis;
    int16_t y_axis;
    int16_t z_axis;

    x_axis = accel7_get_axis( &accel7, ACCEL7_AXIS_X );
    y_axis = accel7_get_axis( &accel7, ACCEL7_AXIS_Y );
    z_axis = accel7_get_axis( &accel7, ACCEL7_AXIS_Z );

    log_printf( &logger, "X axis: %d\r\n", x_axis );
    log_printf( &logger, "Y axis: %d\r\n", y_axis );
    log_printf( &logger, "Z axis: %d\r\n", z_axis );   
    
    log_printf( &logger, "------------------\r\n" );

    delay_ms( 1000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel7

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
