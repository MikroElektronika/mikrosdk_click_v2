\mainpage Main Page
 
---
# Motion 2 click

Motion 2 Click is a Click board™ based on EKMC1607112, PIR motion sensor from Panasonic Corporation that's used as human motion detector. Also featured on Motion 2 Click bord is TLP241A photorelay from Toshiba that is used to provide a reinforced galvanic isolation for the external signals used to drive some external high power electronic equipment when motion is detected. 

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}">
</p>

[click Product page](https://www.mikroe.com/motion-2-click)

---


#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : jan 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the Motion2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Motion2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void motion2_cfg_setup ( motion2_cfg_t *cfg ); 
 
- Initialization function.
> MOTION2_RETVAL motion2_init ( motion2_t *ctx, motion2_cfg_t *cfg );

#### Example key functions :

- Functions for active motion sensors
> void motion2_active ( uint8_t status );
 
- Gets detection state
>  uint8_t motion2_detect_state ( void )

## Examples Description

> Demo example shows the detection of object movement near the sensor.

**The demo application is composed of two sections :**

### Application Init 

> Initializes all necessary GPIO pins and activates the motion sensor

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    motion2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    motion2_cfg_setup( &cfg );
    MOTION2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    motion2_init( &motion2, &cfg );

    motion2_active( &motion2, MOTION2_MODULE_ENABLE );
    log_info( &logger, "--- Motion sensor is enabled... ----\r\n" );
    Delay_100ms( );
}
```

### Application Task

> Checks if an object is detected. 
> Prints a message about the object detection and
> whether the sensor has stabilized after object detection. 

```c
void application_task ( void )
{
    uint8_t motion_state;
    
    motion_state = motion2_detect_state( &motion2 );
    
    if ( ( motion_detect_flag == 0 ) &&
         ( motion_state == MOTION2_DETECT_OBJECT ) )
    {
        log_info( &logger, ">>> Object is detected...\r\n" );
        motion_detect_flag = 1;
        Delay_ms( 500 );
    }
    
    if ( ( motion_detect_flag == 1 ) && 
         ( motion_state != MOTION2_DETECT_OBJECT ) )
    {
        log_info( &logger, ">>> Sensor has stabilized..\r\n" );
        log_info( &logger, ">>> Ready for new detection...\r\n" );
        log_info( &logger, ">>> --------------------------\r\n" );
        motion_detect_flag = 0;
    }
}
```

## Note

> The sensor needs a maximum of 30s to stabilize. 
> See the sensor technical documentation for more information.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Motion2

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
