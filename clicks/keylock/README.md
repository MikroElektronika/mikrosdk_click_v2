
---
# Keylock Click

> [Keylock Click](https://www.mikroe.com/?pid_product=MIKROE-2564) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2564&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application monitors key position in its lock mechanism.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Keylock

### Example Key Functions

- `keylock_cfg_setup` Config Object Initialization function. 
```c
void keylock_cfg_setup ( keylock_cfg_t *cfg );
``` 
 
- `keylock_init` Initialization function. 
```c
err_t keylock_init ( keylock_t *ctx, keylock_cfg_t *cfg );
```

- `keylock_check_pin` Checks pin state. 
```c
uint8_t keylock_check_pin ( keylock_t *ctx, uint8_t pin );
```
 
- `keylock_get_position` Gets key position. 
```c
uint8_t keylock_get_position ( keylock_t *ctx );
```

### Application Init

> Initialization driver enables GPIO and also writes log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    keylock_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    keylock_cfg_setup( &cfg );
    KEYLOCK_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    keylock_init( &keylock, &cfg );
    Delay_ms ( 100 );
    log_printf( &logger, "--------------- \r\n" );
    log_printf( &logger, " Keylock Click \r\n" );
    log_printf( &logger, "--------------- \r\n" );
}
```

### Application Task

> Detects the position in which the key currently is.
  Results are being sent to the Terminal, where you can track changes.

```c
void application_task ( void )
{
    uint8_t new_state;
    uint8_t old_state = 0;

    new_state = keylock_get_position( &keylock );

    if ( old_state != new_state )
    {
        if ( new_state == KEYLOCK_KEY_POS_1 )
        {
            log_printf( &logger, " Position ONE \r\n" );
        }
        else if ( new_state == KEYLOCK_KEY_POS_2 )
        {
            log_printf( &logger, " Position TWO \r\n" );
        }
        else if ( new_state == KEYLOCK_KEY_POS_3 )
        {
            log_printf( &logger, " Position THREE \r\n" );
        }
        else
        {
            log_printf( &logger, " ERROR!!! \r\n" );
        }
    old_state = new_state;
    log_printf( &logger, "---------------- \r\n" );
    }

    Delay_ms ( 500 );
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
