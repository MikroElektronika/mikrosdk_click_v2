
---
# Motion EKMC click

Motion 2, 3, 4 Click is a Click board™ based on EKMC, PIR motion sensor from Panasonic Corporation that's used as human motion detector.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/grupe/motion-click-group.png" height=300px>
</p>


[click Product page - Motion 2](<https://www.mikroe.com/motion-2-click>)

[click Product page - Motion 3](<https://www.mikroe.com/motion-3-click>)

[click Product page - Motion 4](<https://www.mikroe.com/motion-4-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the MotionEKMC Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for MotionEKMC Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void motionekmc_cfg_setup ( motionekmc_cfg_t *cfg ); 
 
- Initialization function.
> MOTIONEKMC_RETVAL motionekmc_init ( motionekmc_t *ctx, motionekmc_cfg_t *cfg );

- Click Default Configuration function.
> void motionekmc_default_cfg ( motionekmc_t *ctx );


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
    motionekmc_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    motionekmc_cfg_setup( &cfg );
    MOTIONEKMC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    motionekmc_init( &motionekmc, &cfg );
    
    motionekmc_default_cfg( &motionekmc );
}

  
```

### Application Task

 Checks if an object is detected. 
> Prints a message about the object detection and
> whether the sensor has stabilized after object detection. 

```c

void application_task ( void )
{
    uint8_t int_status;

    int_status = motionekmc_detect_state( &motionekmc );

    if ( int_status == MOTIONEKMC_DETECT_OBJECT )
    {
        log_printf( &logger, "Motion detected \r\n" );
        while ( int_status == MOTIONEKMC_DETECT_OBJECT )
        {
            int_status = motionekmc_detect_state( &motionekmc );
        }
        log_printf( &logger, "Motion wait \r\n" );
        Delay_ms( 100 );
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
- Click.MotionEKMC

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
