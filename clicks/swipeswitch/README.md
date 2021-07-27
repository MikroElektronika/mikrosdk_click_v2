\mainpage Main Page
 
 

---
# SwipeSwitch click

SwipeSwitch click is capacitive touch, gesture, and proximity sensing Click board™, which is equipped with the IQS266, an integrated trackpad controller circuit which features ProxSense® and IQ Switch® technologies. This IC consists of a 2x3-channel capacitive trackpad controller, and a single self-capacitive proximity sensor, which can be used to wake up the device. This ensures very low power consumption, as the device is able to stay in the Sleep mode when not used. The IQS266 can detect a number of various configurable swipe and tap gestures. An Automatic Tuning Implementation (ATI) feature ensures an optimized performance in various conditions.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/swipeswitch_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/swipeswitch-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the SwipeSwitch Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for SwipeSwitch Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void swipeswitch_cfg_setup ( swipeswitch_cfg_t *cfg ); 
 
- Initialization function.
> SWIPESWITCH_RETVAL swipeswitch_init ( swipeswitch_t *ctx, swipeswitch_cfg_t *cfg );


#### Example key functions :

- This function reads Gestures
> uint8_t swipeswitch_read_gestures ( swipeswitch_t *ctx );
 
- This function reads X coordinate.
> uint8_t swipeswitch_read_x_coordinate ( swipeswitch_t *ctx );

- This function reads Y coordinate.
> uint8_t swipeswitch_read_y_coordinate ( swipeswitch_t *ctx );

## Examples Description

> Click board is able to sense several different swipe gestures. 

**The demo application is composed of two sections :**

### Application Init 

> Initialization and configuration of the chip for measurement.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    swipeswitch_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    swipeswitch_cfg_setup( &cfg );
    SWIPESWITCH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    swipeswitch_init( &swipeswitch, &cfg );
    Delay_ms( 300 );
    
    display_mode = SWIPESWITCH_GESTURE_MODE;
    
    if ( display_mode == SWIPESWITCH_GESTURE_MODE)
    {
        log_printf( &logger, "<<< GESTURE MODE >>> \r\n" ); 
    }
    else if ( display_mode == SWIPESWITCH_POSITION_MODE)
    {
        log_printf( &logger, "<<< POSITION MODE >>> \r\n" ); 
    }
}
  
```

### Application Task

> Display message on a terminal when new event occurs ( TAP or SWIPE ) along with the X and Y coordinates depending on the display_mode value.

```c

void application_task ( void )
{
    if ( display_mode == SWIPESWITCH_GESTURE_MODE)
    {
        events = swipeswitch_read_events( &swipeswitch );
        gestures = swipeswitch_read_gestures( &swipeswitch );

        
        if ( ( events & ( SWIPESWITCH_EVENT_SWIPE ) ) != 0 )
        {
            if ( ( gestures & SWIPESWITCH_GESTURE_SWIPE_UP ) != 0 )
            {
                log_printf( &logger, "SWIPE UP \r\n" );
            }
            if ( ( gestures & SWIPESWITCH_GESTURE_SWIPE_DOWN ) != 0 )
            {
                log_printf( &logger, "SWIPE DOWN \r\n" );
            }
            if ( ( gestures & SWIPESWITCH_GESTURE_SWIPE_LEFT ) != 0 )
            {
                log_printf( &logger, "SWIPE LEFT \r\n" );
            }
            if ( ( gestures & SWIPESWITCH_GESTURE_SWIPE_RIGHT ) != 0 )
            {
                log_printf( &logger, "SWIPE RIGHT \r\n" );
            }
        }
        
        else if ( ( events & ( SWIPESWITCH_EVENT_TAP ) ) != 0 )
        {
            log_printf( &logger,"TAP \r\n" );
        }
    }
    else if ( display_mode == SWIPESWITCH_POSITION_MODE)
    {
        x_coordinate = swipeswitch_read_x_coordinate( &swipeswitch );
        y_coordinate = swipeswitch_read_y_coordinate( &swipeswitch );

        if ( ( x_coordinate != old_x_coordinate) || ( y_coordinate != old_y_coordinate ) )
        {
            log_printf( &logger,"Coordinate : (%u , %u)\r\n", (uint16_t) x_coordinate, (uint16_t) y_coordinate );

            old_x_coordinate = x_coordinate;
            old_y_coordinate = y_coordinate;
        }
    }
    Delay_ms( 300 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.SwipeSwitch

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
