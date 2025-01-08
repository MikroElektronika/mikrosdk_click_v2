
---
# Key Lock 2 Click

> [Key Lock 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3471) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3471&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Nov 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> Keylock 2 Click carries antistatic process sealed keylock mechanism that has three positions.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.KeyLock2

### Example Key Functions

- `keylock2_cfg_setup` Config Object Initialization function. 
```c
void keylock2_cfg_setup ( keylock2_cfg_t *cfg );
``` 
 
- `keylock2_init` Initialization function. 
```c
err_t keylock2_init ( keylock2_t *ctx, keylock2_cfg_t *cfg );
```

- `keylock2_default_cfg` Click Default Configuration function. 
```c
void keylock2_default_cfg ( keylock2_t *ctx );
```

- `keylock2_get_pin_state` This function gets states of pins out1, out2 and out3 on Key Lock 2 Click. 
```c
uint8_t keylock2_get_pin_state ( keylock2_t *ctx, uint8_t pin );
```
 
- This function gets Position (First, Second, Third) of pins 
out1, out2 and out3 on Key Lock 2 Click.
> uint8_t keylock2_get_position ( keylock2_t *ctx )


### Application Init

> Initialization driver init.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    keylock2_cfg_t cfg;

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

    keylock2_cfg_setup( &cfg );
    KEYLOCK2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    keylock2_init( &keylock2, &cfg );
}
```

### Application Task

> Checks the current key position and logs the current position on the USB UART.

```c
void application_task ( void )
{
    key_position = keylock2_get_position( &keylock2 );
    
    if ( old_position != key_position )
    {
        if ( key_position == KEYLOCK2_POSITION_1 )
        {
            log_printf( &logger, " -- FIRST position -- \r\n " );
        }
        else if ( key_position == KEYLOCK2_POSITION_2 )
        {
            log_printf( &logger, " -- SECOND position -- \r\n " );
        }
        else
        {
            log_printf( &logger, " -- THIRD position -- \r\n " );
        }
    }
    old_position = key_position;

    Delay_ms ( 500 );
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
