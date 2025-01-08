
---
# Tilt Click

> [Tilt Click](https://www.mikroe.com/?pid_product=MIKROE-1834) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1834&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : GPIO type

# Software Support

## Example Description

> 
> This is a example which demonstrates the use of Tilt Click board.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Tilt

### Example Key Functions

- `tilt_cfg_setup` Config Object Initialization function. 
```c
void tilt_cfg_setup ( tilt_cfg_t *cfg );
``` 
 
- `tilt_init` Initialization function. 
```c
err_t tilt_init ( tilt_t *ctx, tilt_cfg_t *cfg );
```

- `tilt_default_cfg` Click Default Configuration function. 
```c
void tilt_default_cfg ( tilt_t *ctx );
```

- `tilt_direction` Check the tilt movement's direction function. 
```c
uint8_t tilt_direction ( tilt_t *ctx );
```
 
### Application Init

>
> Configuring Clicks and log objects.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    tilt_cfg_t cfg;

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
    log_printf(&logger, "---- Application Init ----\r\n");

    //  Click initialization.

    tilt_cfg_setup( &cfg );
    TILT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    tilt_init( &tilt, &cfg );
    
    tilt_direction_old = 0;
    
    log_printf(&logger, "-------------\r\n");
    log_printf(&logger, " Tilt  Click \r\n");
    log_printf(&logger, "-------------\r\n");
    Delay_ms ( 100 );
}
```

### Application Task

>
> Detect the movement's direction 
> of RPI-1035 Surface Mount Type 4-Direction Detector on Tilt Click board.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs on usb uart when the movement's direction is changed.
> 

```c
void application_task ( void )
{
    tilt_direction = tilt_direction( &tilt );

    if ( tilt_direction_old != tilt_direction )
    {
        if ( tilt_direction == TILT_LEFT_DETECTION )
        {
            log_printf(&logger, "    LEFT     \r\n");
        }

        if ( tilt_direction == TILT_RIGHT_DETECTION )
        {
            log_printf(&logger, "    RIGHT    \r\n");
        }

        if ( tilt_direction == TILT_UP_DETECTION )
        {
            log_printf(&logger, "     UP      \r\n");
        }

        if ( tilt_direction == TILT_DOWN_DETECTION )
        {
            log_printf(&logger, "    DOWN     \r\n");
        }

        tilt_direction_old = tilt_direction;
        log_printf(&logger, "-------------\r\n");
    }
}
```

### Note


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
