
---
# Push Button Click

> [Push Button Click](https://www.mikroe.com/?pid_product=MIKROE-6811) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6811&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2025.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of the Push Button Click board by reading the output and interrupt pin states.
The OUT pin state is logged whenever it changes, and if the output remains active longer than the timeout period, it is automatically cleared.
If the button is pressed and held longer than 8 seconds, the output shuts down.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PushButton

### Example Key Functions

- `pushbutton_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void pushbutton_cfg_setup ( pushbutton_cfg_t *cfg );
```

- `pushbutton_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t pushbutton_init ( pushbutton_t *ctx, pushbutton_cfg_t *cfg );
```

- `pushbutton_clear_output` This function clears the output by toggling the CLR pin.
```c
void pushbutton_clear_output ( pushbutton_t *ctx );
```

- `pushbutton_get_out_pin` This function returns the OUT pin logic state.
```c
uint8_t pushbutton_get_out_pin ( pushbutton_t *ctx );
```

- `pushbutton_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t pushbutton_get_int_pin ( pushbutton_t *ctx );
```

### Application Init

> Initializes the log interface and the Push Button Click driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pushbutton_cfg_t pushbutton_cfg;  /**< Click config object. */

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
    pushbutton_cfg_setup( &pushbutton_cfg );
    PUSHBUTTON_MAP_MIKROBUS( pushbutton_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == pushbutton_init( &pushbutton, &pushbutton_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Monitors the OUT pin state, logs changes, resets the timeout counter when the button is pressed, and clears the output after
a timeout period or if the button is pressed longer than 8 seconds.

```c
void application_task ( void )
{
    static uint32_t time_cnt = 0;
    static uint8_t out_state_old = 0xFF;
    uint8_t out_state = pushbutton_get_out_pin ( &pushbutton );
    if ( out_state_old != out_state )
    {
        log_printf( &logger, " OUT state: %u\r\n", ( uint16_t ) out_state );
        out_state_old = out_state;
        time_cnt = 0;
    }
    if ( out_state_old && ( time_cnt > 10000 ) )
    {
        log_printf( &logger, " TIMEOUT: clearing output\r\n" );
        pushbutton_clear_output ( &pushbutton );
    }
    if ( !pushbutton_get_int_pin ( &pushbutton ) )
    {
        time_cnt = 0;
    }
    Delay_ms ( 1 );
    time_cnt++;
}
```

### Note

> The timeout period in this example is set to approximately 10 seconds, and button press longer than 8 seconds will also shut down the output.

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
