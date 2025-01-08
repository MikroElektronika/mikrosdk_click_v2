
---
# Button 3 Click

> [Button 3 Click](https://www.mikroe.com/?pid_product=MIKROE-6276) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6276&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Button 3 Click board by toggling a button LED and its switch state on a button press.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Button3

### Example Key Functions

- `button3_cfg_setup` Config Object Initialization function.
```c
void button3_cfg_setup ( button3_cfg_t *cfg );
```

- `button3_init` Initialization function.
```c
err_t button3_init ( button3_t *ctx, button3_cfg_t *cfg );
```

- `button3_default_cfg` Click Default Configuration function.
```c
err_t button3_default_cfg ( button3_t *ctx );
```

- `button3_toggle_red_led` This function toggles the red button LED by toggling the RK pin logic state.
```c
err_t button3_toggle_red_led ( button3_t *ctx );
```

- `button3_toggle_green_led` This function toggles the green button LED by toggling the GK pin logic state.
```c
err_t button3_toggle_green_led ( button3_t *ctx );
```

- `button3_toggle_blue_led` This function toggles the blue button LED by toggling the BK pin logic state.
```c
err_t button3_toggle_blue_led ( button3_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    button3_cfg_t button3_cfg;  /**< Click config object. */

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
    button3_cfg_setup( &button3_cfg );
    BUTTON3_MAP_MIKROBUS( button3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == button3_init( &button3, &button3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BUTTON3_ERROR == button3_default_cfg ( &button3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf ( &logger, " Press button to change switch state\r\n\n" );
    log_printf ( &logger, " RED SWITCH OFF\r\n\n" );
    log_printf ( &logger, " GREEN SWITCH OFF\r\n\n" );
    log_printf ( &logger, " BLUE SWITCH OFF\r\n\n" );
}
```

### Application Task

> Toggles a button LED and its switch state on a button press and displays the state on the USB UART.

```c
void application_task ( void )
{
    static uint8_t red_switch_state = BUTTON3_SWITCH_OFF;
    static uint8_t green_switch_state = BUTTON3_SWITCH_OFF;
    static uint8_t blue_switch_state = BUTTON3_SWITCH_OFF;
    uint8_t switch_state = BUTTON3_SWITCH_OFF;

    if ( BUTTON3_PIN_STATE_LOW == button3_get_int_pin ( &button3 ) )
    {
        if ( ( BUTTON3_OK == button3_get_red_button ( &button3, &switch_state ) ) && 
             ( BUTTON3_BUTTON_PRESSED == switch_state ) )
        {
            button3_toggle_red_led ( &button3 );
            red_switch_state ^= BUTTON3_SWITCH_ON;
            if ( BUTTON3_SWITCH_ON == red_switch_state )
            {
                log_printf ( &logger, " RED SWITCH ON\r\n\n" );
            }
            else
            {
                log_printf ( &logger, " RED SWITCH OFF\r\n\n" );
            }
        }
        if ( ( BUTTON3_OK == button3_get_green_button ( &button3, &switch_state ) ) && 
             ( BUTTON3_BUTTON_PRESSED == switch_state ) )
        {
            button3_toggle_green_led ( &button3 );
            green_switch_state ^= BUTTON3_SWITCH_ON;
            if ( BUTTON3_SWITCH_ON == green_switch_state )
            {
                log_printf ( &logger, " GREEN SWITCH ON\r\n\n" );
            }
            else
            {
                log_printf ( &logger, " GREEN SWITCH OFF\r\n\n" );
            }
        }
        if ( ( BUTTON3_OK == button3_get_blue_button ( &button3, &switch_state ) ) && 
             ( BUTTON3_BUTTON_PRESSED == switch_state ) )
        {
            button3_toggle_blue_led ( &button3 );
            blue_switch_state ^= BUTTON3_SWITCH_ON;
            if ( BUTTON3_SWITCH_ON == blue_switch_state )
            {
                log_printf ( &logger, " BLUE SWITCH ON\r\n\n" );
            }
            else
            {
                log_printf ( &logger, " BLUE SWITCH OFF\r\n\n" );
            }
        }
        Delay_ms ( 100 );
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
