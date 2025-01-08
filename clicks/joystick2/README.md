
---
# Joystick 2 Click

> [Joystick 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3711) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3711&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> The demo application shows reading the joistick position ..

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Joystick2

### Example Key Functions

- `joystick2_cfg_setup` Config Object Initialization function. 
```c
void joystick2_cfg_setup ( joystick2_cfg_t *cfg );
``` 
 
- `joystick2_init` Initialization function. 
```c
err_t joystick2_init ( joystick2_t *ctx, joystick2_cfg_t *cfg );
```

- `joystick2_default_cfg` Click Default Configuration function. 
```c
void joystick2_default_cfg ( joystick2_t *ctx );
```

- `joystick2_set_cfg_register` Functions for configuration joystick. 
```c
void joystick2_set_cfg_register ( joystick2_t *ctx, uint8_t cfg_data );
```
 
- `joystick2_get_position` Functions for get Joystick position. 
```c
uint8_t joystick2_get_position ( joystick2_t *ctx );
```

- `joystick2_get_interrupt_state` Functions for read interrupt state. 
```c
uint8_t joystick2_get_interrupt_state ( joystick2_t *ctx );
```

### Application Init

> Configuring Clicks and log objects.
> Reset device and settings the Click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    joystick2_cfg_t cfg;

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

    joystick2_cfg_setup( &cfg );
    JOYSTICK2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    joystick2_init( &joystick2, &cfg );

    joystick2_reset( &joystick2 );
    joystick2_default_cfg( &joystick2 );
    log_info( &logger, "---- JOYSTICK START ----" );
}
```

### Application Task

> It reads the position of the joystick,
> if it detects that the joystick has moved from the zero position,
> it prints a message about the current position.

```c
void application_task ( void )
{
    uint8_t joystick_pos;

    //  Task implementation.

    joystick_pos = joystick2_get_position( &joystick2 );

    switch ( joystick_pos )
    {
        case JOYSTICK2_BUTTON_ACTIVE:
        {
            log_info( &logger, "--- Button is pressed!!! ---" );
            Delay_ms ( 300 );
            break;
        }
        case JOYSTICK2_POSITION_RIGHT:
        {
            log_info( &logger, "--- Joystick position [RIGHT] ---" );
            Delay_ms ( 300 );
            break;
        }
        case JOYSTICK2_POSITION_LEFT:
        {
            log_info( &logger, "--- Joystick position [LEFT] ---" );
            Delay_ms ( 300 );
            break;
        }
        case JOYSTICK2_POSITION_UP:
        {
            log_info( &logger, "--- Joystick position [UP] ---" );
            Delay_ms ( 300 );
            break;
        }
        case JOYSTICK2_POSITION_DOWN:
        {
            log_info( &logger, "--- Joystick position [DOWN] ---" );
            Delay_ms ( 300 );
            break;
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
