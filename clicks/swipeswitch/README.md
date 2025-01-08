
---
# SwipeSwitch Click

> [SwipeSwitch Click](https://www.mikroe.com/?pid_product=MIKROE-3202) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3202&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> Click board is able to sense several different swipe gestures. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SwipeSwitch

### Example Key Functions

- `swipeswitch_cfg_setup` Config Object Initialization function. 
```c
void swipeswitch_cfg_setup ( swipeswitch_cfg_t *cfg );
``` 
 
- `swipeswitch_init` Initialization function. 
```c
err_t swipeswitch_init ( swipeswitch_t *ctx, swipeswitch_cfg_t *cfg );
```

- `swipeswitch_read_gestures` This function reads Gestures. 
```c
uint8_t swipeswitch_read_gestures ( swipeswitch_t *ctx );
```
 
- `swipeswitch_read_x_coordinate` This function reads X coordinate. 
```c
uint8_t swipeswitch_read_x_coordinate ( swipeswitch_t *ctx );
```

- `swipeswitch_read_y_coordinate` This function reads Y coordinate. 
```c
uint8_t swipeswitch_read_y_coordinate ( swipeswitch_t *ctx );
```

### Application Init

> Initialization and configuration of the chip for measurement.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    swipeswitch_cfg_t cfg;

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

    swipeswitch_cfg_setup( &cfg );
    SWIPESWITCH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    swipeswitch_init( &swipeswitch, &cfg );
    Delay_ms ( 300 );
    
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
    Delay_ms ( 300 );
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
