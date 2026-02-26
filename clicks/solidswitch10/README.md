
---
# SolidSwitch 10 Click

> [SolidSwitch 10 Click](https://www.mikroe.com/?pid_product=MIKROE-6864) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6864&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the SolidSwitch 10 Click board for
controlling a low-side solid-state output channel. The application periodically
enables and disables the output, allowing verification of switching
behavior through the connected load.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SolidSwitch10

### Example Key Functions

- `solidswitch10_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void solidswitch10_cfg_setup ( solidswitch10_cfg_t *cfg );
```

- `solidswitch10_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t solidswitch10_init ( solidswitch10_t *ctx, solidswitch10_cfg_t *cfg );
```

- `solidswitch10_default_cfg` This function executes a default configuration of SolidSwitch 10 Click board.
```c
err_t solidswitch10_default_cfg ( solidswitch10_t *ctx );
```

- `solidswitch10_enable_output` This function sets the IN pin to high logic level, enabling the low-side switch output.
```c
void solidswitch10_enable_output ( solidswitch10_t *ctx );
```

- `solidswitch10_disable_output` This function sets the IN pin to low logic level, disabling the low-side switch output.
```c
void solidswitch10_disable_output ( solidswitch10_t *ctx );
```

### Application Init

> Initializes the logger and SolidSwitch 10 Click driver and applies the default device configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    solidswitch10_cfg_t solidswitch10_cfg;  /**< Click config object. */

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
    solidswitch10_cfg_setup( &solidswitch10_cfg );
    SOLIDSWITCH10_MAP_MIKROBUS( solidswitch10_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == solidswitch10_init( &solidswitch10, &solidswitch10_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SOLIDSWITCH10_ERROR == solidswitch10_default_cfg ( &solidswitch10 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Toggles the output state by enabling and disabling low-side switch output
at fixed time intervals and logs the current action to the serial terminal.

```c
void application_task ( void )
{
    log_printf( &logger, " Enable OUT\r\n\n" );
    solidswitch10_enable_output ( &solidswitch10 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Disable OUT\r\n\n" );
    solidswitch10_disable_output ( &solidswitch10 );
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
