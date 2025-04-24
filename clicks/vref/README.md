
---
# VREF Click

> [VREF Click](https://www.mikroe.com/?pid_product=MIKROE-6593) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6593&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2025.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of the VREF Click board by enabling and disabling
its 2.5V reference output periodically. The application toggles the output every
3 seconds and logs the current state via UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.VREF

### Example Key Functions

- `vref_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void vref_cfg_setup ( vref_cfg_t *cfg );
```

- `vref_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t vref_init ( vref_t *ctx, vref_cfg_t *cfg );
```

- `vref_enable_output` This function enables VREF output by setting the EN pin to high logic state.
```c
void vref_enable_output ( vref_t *ctx );
```

- `vref_disable_output` This function disables VREF output by setting the EN pin to low logic state.
```c
void vref_disable_output ( vref_t *ctx );
```

### Application Init

> Initializes the logger and configures the VREF Click driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    vref_cfg_t vref_cfg;  /**< Click config object. */

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
    vref_cfg_setup( &vref_cfg );
    VREF_MAP_MIKROBUS( vref_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == vref_init( &vref, &vref_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Alternately enables and disables the voltage reference output with a 3-second delay, displaying the output state on the UART terminal.

```c
void application_task ( void )
{
    log_printf( &logger, " VREF Output: Enabled\r\n" );
    vref_enable_output ( &vref );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " VREF Output: Disabled\r\n\n" );
    vref_disable_output ( &vref );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
