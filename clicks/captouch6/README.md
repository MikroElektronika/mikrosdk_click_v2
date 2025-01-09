
---
# Cap Touch 6 Click

> [Cap Touch 6 Click](https://www.mikroe.com/?pid_product=MIKROE-5517) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5517&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2022.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of Cap Touch 6 Click board by reading and displaying the touch and proximity events.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CapTouch6

### Example Key Functions

- `captouch6_cfg_setup` Config Object Initialization function.
```c
void captouch6_cfg_setup ( captouch6_cfg_t *cfg );
```

- `captouch6_init` Initialization function.
```c
err_t captouch6_init ( captouch6_t *ctx, captouch6_cfg_t *cfg );
```

- `captouch6_get_tout_pin` This function returns the TOUT pin logic state.
```c
uint8_t captouch6_get_tout_pin ( captouch6_t *ctx );
```

- `captouch6_get_pout_pin` This function returns the POUT pin logic state.
```c
uint8_t captouch6_get_pout_pin ( captouch6_t *ctx );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    captouch6_cfg_t captouch6_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    captouch6_cfg_setup( &captouch6_cfg );
    CAPTOUCH6_MAP_MIKROBUS( captouch6_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == captouch6_init( &captouch6, &captouch6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the touch and proximity event pins state and displays them on the USB UART on changes.

```c
void application_task ( void )
{
    static uint8_t old_touch_state = 0, old_prox_state = 0;
    uint8_t touch_state = captouch6_get_tout_pin ( &captouch6 );
    uint8_t prox_state = captouch6_get_pout_pin ( &captouch6 );
    if ( ( old_touch_state != touch_state ) || ( old_prox_state != prox_state ) )
    {
        log_printf( &logger, " Touch: %s\r\n", ( char * ) ( !touch_state ? "detected" : "idle" ) );
        log_printf( &logger, " Proximity: %s\r\n\n", ( char * ) ( !prox_state ? "detected" : "idle" ) );
        old_touch_state = touch_state;
        old_prox_state = prox_state;
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
