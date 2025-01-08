
---
# LightRanger 9 Click

> [LightRanger 9 Click](https://www.mikroe.com/?pid_product=MIKROE-5237) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5237&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of LightRanger 9 Click board by reading and displaying all four sub-captures data measurements on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LightRanger9

### Example Key Functions

- `lightranger9_cfg_setup` Config Object Initialization function.
```c
void lightranger9_cfg_setup ( lightranger9_cfg_t *cfg );
```

- `lightranger9_init` Initialization function.
```c
err_t lightranger9_init ( lightranger9_t *ctx, lightranger9_cfg_t *cfg );
```

- `lightranger9_default_cfg` Click Default Configuration function.
```c
err_t lightranger9_default_cfg ( lightranger9_t *ctx );
```

- `lightranger9_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t lightranger9_get_int_pin ( lightranger9_t *ctx );
```

- `lightranger9_clear_interrupts` This function reads and clears the interrupt status register.
```c
err_t lightranger9_clear_interrupts ( lightranger9_t *ctx );
```

- `lightranger9_get_capture` This function reads and parses a single sub-capture block of 132 bytes.
```c
err_t lightranger9_get_capture ( lightranger9_t *ctx, lightranger9_capture_t *capture );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lightranger9_cfg_t lightranger9_cfg;  /**< Click config object. */

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
    lightranger9_cfg_setup( &lightranger9_cfg );
    LIGHTRANGER9_MAP_MIKROBUS( lightranger9_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == lightranger9_init( &lightranger9, &lightranger9_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LIGHTRANGER9_ERROR == lightranger9_default_cfg ( &lightranger9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads all four sub-captures data approximately every 500ms and logs them to the USB UART
in a form of two object 8x8 maps. Other data such as DIE temperature, ambient light, system tick, etc., are also being displayed.

```c
void application_task ( void )
{
    while ( lightranger9_get_int_pin ( &lightranger9 ) );

    lightranger9_capture_t capture;
    if ( ( LIGHTRANGER9_OK == lightranger9_clear_interrupts ( &lightranger9 ) ) && 
         ( LIGHTRANGER9_OK == lightranger9_get_capture ( &lightranger9, &capture ) ) )
    {
        lightranger9_log_results ( capture );
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
