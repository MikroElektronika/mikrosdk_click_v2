
---
# Button 2 Click

> [Button 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6275) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6275&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of Button 2 Click board by toggling the button LED and switch state on button press.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Button2

### Example Key Functions

- `button2_cfg_setup` Config Object Initialization function.
```c
void button2_cfg_setup ( button2_cfg_t *cfg );
```

- `button2_init` Initialization function.
```c
err_t button2_init ( button2_t *ctx, button2_cfg_t *cfg );
```

- `button2_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t button2_get_int_pin ( button2_t *ctx );
```

- `button2_toggle_led` This function toggles the button LED state by toggling the LED pin logic state.
```c
void button2_toggle_led ( button2_t *ctx );
```

- `button2_enable_led` This function enables button LED by setting the LED pin to the high logic state.
```c
void button2_enable_led ( button2_t *ctx );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    button2_cfg_t button2_cfg;  /**< Click config object. */

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
    button2_cfg_setup( &button2_cfg );
    BUTTON2_MAP_MIKROBUS( button2_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == button2_init( &button2, &button2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf ( &logger, " Press button to change switch state\r\n\n" );
    log_printf ( &logger, " SWITCH OFF\r\n\n" );
}
```

### Application Task

> Toggles the button LED and switch state on button press and displays the state on the USB UART.

```c
void application_task ( void )
{
    static uint8_t switch_state = BUTTON2_SWITCH_OFF;
    
    if ( BUTTON2_BUTTON_PRESSED == button2_get_int_pin ( &button2 ) )
    {
        button2_toggle_led ( &button2 );
        switch_state ^= BUTTON2_SWITCH_ON;
        if ( BUTTON2_SWITCH_ON == switch_state )
        {
            log_printf ( &logger, " SWITCH ON\r\n\n" );
        }
        else
        {
            log_printf ( &logger, " SWITCH OFF\r\n\n" );
        }
        Delay_ms ( 1000 );
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
