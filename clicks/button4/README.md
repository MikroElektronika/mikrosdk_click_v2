
---
# Button 4 Click

> [Button 4 Click](https://www.mikroe.com/?pid_product=MIKROE-6620) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6620&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2025.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of the Button 4 Click board by initializing
the device and detecting the button state changes. It logs whether the button
is pressed (active) or released (reset).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Button4

### Example Key Functions

- `button4_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void button4_cfg_setup ( button4_cfg_t *cfg );
```

- `button4_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t button4_init ( button4_t *ctx, button4_cfg_t *cfg );
```

- `button4_get_out_pin` This function returns the OUT pin logic state.
```c
uint8_t button4_get_out_pin ( button4_t *ctx );
```

### Application Init

> Initializes the logger and the Button 4 Click driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    button4_cfg_t button4_cfg;  /**< Click config object. */

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
    button4_cfg_setup( &button4_cfg );
    BUTTON4_MAP_MIKROBUS( button4_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == button4_init( &button4, &button4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Monitors the button state and logs whether the button is active (pressed) or reset (released) when a state change is detected.

```c
void application_task ( void )
{
    static uint8_t button_state_old = BUTTON4_BUTTON_RESET;
    uint8_t button_state = button4_get_out_pin ( &button4 );
    if ( button_state_old != button_state )
    {
        button_state_old = button_state;
        if ( BUTTON4_BUTTON_ACTIVE == button_state )
        {
            log_printf ( &logger, " BUTTON ACTIVE\r\n\n" );
        }
        else
        {
            log_printf ( &logger, " BUTTON RESET\r\n\n" );
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
