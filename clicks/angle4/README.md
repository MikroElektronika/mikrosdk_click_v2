\mainpage Main Page
 
 

---
# Angle 4 click

Angle 4 click is an angular magnetic rotary sensor, which can be used as a rotary encoder.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/angle4_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/angle-4-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Angle4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Angle4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void angle4_cfg_setup ( angle4_cfg_t *cfg ); 
 
- Initialization function.
> ANGLE4_RETVAL angle4_init ( angle4_t *ctx, angle4_cfg_t *cfg );

- Click Default Configuration function.
> void angle4_default_cfg ( angle4_t *ctx );


#### Example key functions :

- function used to start measurement mode.
> void angle4_start_mesuremenet ( angle4_t *ctx );
 
- This function is used to retrieve Angle value depending on the given resolution.
> uint8_t angle4_get_new_angle ( angle4_t *ctx, uint16_t *data_out );

- This function is used to read single byte of Data on the desired address.
> uint8_t angle4_read_byte ( angle4_t *ctx, uint8_t addr );

## Examples Description
 
> This application enables use of angular magnetic rotary sensor, which can be used as a rotary 
> encoder.

**The demo application is composed of two sections :**

### Application Init 

> Driver intialization, standard configurations and start measurement

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    angle4_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    angle4_cfg_setup( &cfg );
    ANGLE4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    angle4_init( &angle4, &cfg );

    angle4_default_cfg( &angle4, ANGLE4_CCFG2_DIR_COUNTER_CLOCKWISE_ROTATION,\
                                 ANGLE4_CCFG2_ABS_RESOLUTION_14bit );
    log_printf( &logger, " --- Start measurement \r\n");

    angle4_start_mesuremenet( &angle4 );
}
  
```

### Application Task

> Reads Angle in degreeses and logs data to USBUART every 200 ms.

```c

void application_task ( void )
{
    //  Task implementation.

    uint16_t angle_value;

    angle4_get_new_angle( &angle4, &angle_value );
    log_printf( &logger, " Angle : %d deg\r\n", angle_value );
    Delay_ms( 200 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Angle4

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
