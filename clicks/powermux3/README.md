
---
# Power MUX 3 Click

> [Power MUX 3 Click](https://www.mikroe.com/?pid_product=MIKROE-6622) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6622&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2025.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of the Power MUX 3 Click board. It enables automatic 
selection between three power sources, selecting the highest voltage as the input source. 
The demo toggles the output ON and OFF at regular intervals, allowing observation of
the output control functionality.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PowerMUX3

### Example Key Functions

- `powermux3_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void powermux3_cfg_setup ( powermux3_cfg_t *cfg );
```

- `powermux3_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t powermux3_init ( powermux3_t *ctx, powermux3_cfg_t *cfg );
```

- `powermux3_enable_device` This function enables the device by setting the SHD pin to HIGH on the Power MUX 3 Click board.
```c
void powermux3_enable_device ( powermux3_t *ctx );
```

- `powermux3_disable_device` This function disables the device by setting the SHD pin to LOW on the Power MUX 3 Click board.
```c
void powermux3_disable_device ( powermux3_t *ctx );
```

- `powermux3_enable_output` This function enables the output by setting the EN pin to HIGH on the Power MUX 3 Click board.
```c
void powermux3_enable_output ( powermux3_t *ctx );
```

- `powermux3_disable_output` This function disables the output by setting the EN pin to LOW on the Power MUX 3 Click board.
```c
void powermux3_disable_output ( powermux3_t *ctx );
```

### Application Init

> Initializes the logger and the Power MUX 3 Click driver, then enables the device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    powermux3_cfg_t powermux3_cfg;  /**< Click config object. */

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
    powermux3_cfg_setup( &powermux3_cfg );
    POWERMUX3_MAP_MIKROBUS( powermux3_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == powermux3_init( &powermux3, &powermux3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    powermux3_enable_device ( &powermux3 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Alternates enabling and disabling the output in 5-second intervals while logging the status.

```c
void application_task ( void )
{
    log_printf( &logger, " Output enabled\r\n\n" );
    powermux3_enable_output ( &powermux3 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Output disabled\r\n\n" );
    powermux3_disable_output ( &powermux3 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
