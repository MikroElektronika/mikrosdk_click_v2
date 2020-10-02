\mainpage Main Page
 
---
# GeoMagnetic click

GeoMagnetic click is a digital magnetometric click board which can measure the geomagnetic field in three perpendicular axes. The onboard sensor uses FlipCore - a proprietary technology from Bosch, which results with a carefully tuned performance, tailored for demanding 3-axis mobile applications, such as a tilt-compensated electronic compass, gaming controllers, augmented reality applications and similar applications which require reliable and precise 3-axis magnetometric measurement.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/geomagnetic_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/geomagnetic-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Geomagnetic Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Geomagnetic Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void geomagnetic_cfg_setup ( geomagnetic_cfg_t *cfg ); 
 
- Initialization function.
> GEOMAGNETIC_RETVAL geomagnetic_init ( geomagnetic_t *ctx, geomagnetic_cfg_t *cfg );

- Click Default Configuration function.
> void geomagnetic_default_cfg ( geomagnetic_t *ctx );


#### Example key functions :

- This function sets the x/y/z axis and hall resolution value.
> void geomagnetic_read_axis_data ( geomagnetic_t *ctx, int16_t *data_x, int16_t *data_y, 
  int16_t *data_z, uint16_t *resolution_hall );
 
- This function gives feedback on whether the device is ready to measure or not.
> uint8_t geomagnetic_check_ready ( geomagnetic_t *ctx );

- This function configures some click module registers after the device has been reset.
> geomagnetic_power_on_reset ( geomagnetic_t *ctx );

## Examples Description

> This example showcases how to initialize and configure the logger and click modules and
  measure and display the data later on. 

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the logger and click modules. 

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    geomagnetic_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    geomagnetic_cfg_setup( &cfg );
    GEOMAGNETIC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    geomagnetic_init( &geomagnetic, &cfg );
    geomagnetic_default_cfg( &geomagnetic );
}
  
```

### Application Task

> This function first checks whether the device is ready to start measuring and after that
  collects and displays data from all three axes every half a second. 

```c

void application_task ( )
{
    GEOMAGNETIC_RETVAL ready_check;
    int16_t axis_x;
    int16_t axis_y;
    int16_t axis_z;
    int16_t resolution_hall;

    ready_check = geomagnetic_check_ready( &geomagnetic );

    while ( ready_check != GEOMAG_DATA_READY )
    {
        ready_check = geomagnetic_check_ready( &geomagnetic );
    }

    geomagnetic_read_axis_data( &geomagnetic, &axis_x, &axis_y, &axis_z, &resolution_hall );

    log_printf( &logger, "X axis: %d\r\n", axis_x );
    log_printf( &logger, "Y axis: %d\r\n", axis_y );
    log_printf( &logger, "Z axis: %d\r\n", axis_z );
    log_printf( &logger, "---------------------------------\r\n" );

    Delay_ms( 500 );
} 

```

## Note

> The Geomagnetic Click needs to initialize the SPI communication module first, because the
  communication interface selection ( on the click ) is locked on to SPI and we need to write
  some data to the registers in order to configure the click module.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Geomagnetic

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
