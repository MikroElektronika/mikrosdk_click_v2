\mainpage Main Page
 
 

---
# Touchpad click

Touchpad click is a capacitive touch input device driven by Microchip’s low-powered MTCH6102 controller. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/touchpad_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/touchpad-click>)

---


#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Touchpad Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Touchpad Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void touchpad_cfg_setup ( touchpad_cfg_t *cfg ); 
 
- Initialization function.
> TOUCHPAD_RETVAL touchpad_init ( touchpad_t *ctx, touchpad_cfg_t *cfg );

- Click Default Configuration function.
> void touchpad_default_cfg ( touchpad_t *ctx );


#### Example key functions :

- Get touch coordinate
> void touchpad_get_touch_coordinate ( touchpad_t *ctx, touchpad_cord_t *cord );
 
- Get event state
> uint8_t touchpad_get_event_state ( touchpad_t *ctx );

- Gesture type
> uint8_t touchpad_get_gesture_type ( touchpad_t *ctx );

## Examples Description

> Demo application shows reading of current event:
>   - touch event (Touch Coordinates)
>   - Gesture event (gesture type)

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
> Setting the click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    touchpad_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    touchpad_cfg_setup( &cfg );
    TOUCHPAD_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    touchpad_init( &touchpad, &cfg );

    touchpad_default_cfg( &touchpad );

    log_info( &logger, "---- Waiting for a new touch or gesure event ----" );
    Delay_ms( 500 );
} 
```

### Application Task

> Reads every touch and gesture and this data logs to USBUART.

```c
void application_task ( void )
{
    uint8_t state;
    uint8_t gesture;
    touchpad_cord_t cord;

    //  Task implementation.

    Delay_ms( 50 );
    state = touchpad_get_event_state( &touchpad );
    if ( state == TOUCHPAD_EVENT_TOUCH )
    {
        touchpad_get_touch_coordinate( &touchpad, &cord );

        log_printf( &logger, "\r\n>> Touch coordinate <<" );
        log_printf( &logger, "\r\n>> ........... <<\r\n" );
        log_printf( &logger, "** X cord: %d \r\n** Y cord: %d \r\n", cord.x, cord.y );
        log_printf( &logger, ">> ........... <<\r\n" );
        Delay_ms( 50 );
    }
    else if ( state == TOUCHPAD_EVENT_GESTURE )
    {
        gesture = touchpad_get_gesture_type( &touchpad );
        switch( gesture )
        {
            case TOUCHPAD_GS_CLICK_AND_HOLD :
            {
                log_printf( &logger, "**Gesture type: Click and Hold\r\n" );
                break;
            }
            case TOUCHPAD_GS_DOUBLE_CLICK :
            {
                log_printf( &logger, "\r\n**Gesture type: Double Click\r\n" );
                break;
            }
            case TOUCHPAD_GS_SINGLE_CLICK :
            {
                log_printf( &logger, "\r\n**Gesture type: Single Click\r\n" );
                break;
            }
            case TOUCHPAD_GS_DOWN_SWIPE :
            {
                log_printf( &logger, "\r\n**Gesture type: Down Swipe\r\n" );
                break;
            }
            case TOUCHPAD_GS_DOWN_SWIPE_AND_HOLD :
            {
                log_printf( &logger, "\r\n**Gesture type: Down Swipe and Hold\r\n" );
                break;
            }
            case TOUCHPAD_GS_RIGHT_SWIPE :
            {
                log_printf( &logger, "\r\n**Gesture type: Right Swipe\r\n" );
                break;
            }
            case TOUCHPAD_GS_RIGHT_SWIPE_AND_HOLD :
            {
                log_printf( &logger, "\r\n**Gesture type: Right Swipe and Hold\r\n" );
                break;
            }
            case TOUCHPAD_GS_UP_SWIPE :
            {
                log_printf( &logger, "\r\n**Gesture type: Up Swipe\r\n" );
                break;
            }
            case TOUCHPAD_GS_UP_SWIPE_AND_HOLD :
            {
                log_printf( &logger, "\r\n**Gesture type: Up Swipe and Hold\r\n" );
                break;
            }
            case TOUCHPAD_GS_LEFT_SWIPE :
            {
                log_printf( &logger, "\r\n**Gesture type: Left Swipe\r\n" );
                break;
            }
            case TOUCHPAD_GS_LEFT_SWIPE_AND_HOLD :
            {
                log_printf( &logger, "\r\n**Gesture type: Left Swipe and Hold\r\n" );
                break;
            }
       }
    }
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Touchpad

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
