
---
# Touchpad Click

> [Touchpad Click](https://www.mikroe.com/?pid_product=MIKROE-1995) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1995&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> Demo application shows reading of current event:
>   - touch event (Touch Coordinates)
>   - Gesture event (gesture type)

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Touchpad

### Example Key Functions

- `touchpad_cfg_setup` Config Object Initialization function. 
```c
void touchpad_cfg_setup ( touchpad_cfg_t *cfg );
``` 
 
- `touchpad_init` Initialization function. 
```c
err_t touchpad_init ( touchpad_t *ctx, touchpad_cfg_t *cfg );
```

- `touchpad_default_cfg` Click Default Configuration function. 
```c
void touchpad_default_cfg ( touchpad_t *ctx );
```

- `touchpad_get_touch_coordinate` Get touch coordinate. 
```c
void touchpad_get_touch_coordinate ( touchpad_t *ctx, touchpad_cord_t *cord );
```
 
- `touchpad_get_event_state` Get event state. 
```c
uint8_t touchpad_get_event_state ( touchpad_t *ctx );
```

- `touchpad_get_gesture_type` Gesture type. 
```c
uint8_t touchpad_get_gesture_type ( touchpad_t *ctx );
```

### Application Init

> Configuring Clicks and log objects.
> Setting the Click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    touchpad_cfg_t cfg;

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

    touchpad_cfg_setup( &cfg );
    TOUCHPAD_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    touchpad_init( &touchpad, &cfg );

    touchpad_default_cfg( &touchpad );

    log_info( &logger, "---- Waiting for a new touch or gesure event ----" );
    Delay_ms ( 500 );
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

    Delay_ms ( 50 );
    state = touchpad_get_event_state( &touchpad );
    if ( state == TOUCHPAD_EVENT_TOUCH )
    {
        touchpad_get_touch_coordinate( &touchpad, &cord );

        log_printf( &logger, "\r\n>> Touch coordinate <<" );
        log_printf( &logger, "\r\n>> ........... <<\r\n" );
        log_printf( &logger, "** X cord: %d \r\n** Y cord: %d \r\n", cord.x, cord.y );
        log_printf( &logger, ">> ........... <<\r\n" );
        Delay_ms ( 50 );
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

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
