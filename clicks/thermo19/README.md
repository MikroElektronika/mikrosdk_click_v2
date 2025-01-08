
---
# Thermo 19 Click

> [Thermo 19 Click](https://www.mikroe.com/?pid_product=MIKROE-4295) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4295&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nikola Citakovic
- **Date**          : Feb 2022.
- **Type**          : PWM type

# Software Support

## Example Description

> This example demonstrates the use of Thermo 19 Click board by reading and displaying the temperature in Celsius.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo19

### Example Key Functions

- `thermo19_cfg_setup` Config Object Initialization function.
```c
void thermo19_cfg_setup ( thermo19_cfg_t *cfg );
```

- `thermo19_init` Initialization function.
```c
err_t thermo19_init ( thermo19_t *ctx, thermo19_cfg_t *cfg );
```

- `thermo19_default_cfg` Click Default Configuration function.
```c
err_t thermo19_default_cfg ( thermo19_t *ctx );
```

- `thermo19_write_scratchpad` This function writes the temperature thresholds and configuration byte to the scratchpad.
```c
err_t thermo19_write_scratchpad ( thermo19_t *ctx, uint16_t temp_high, uint16_t temp_low, uint8_t config );
```

- `thermo19_read_scratchpad` This function reads the scratchpad bytes.
```c
err_t thermo19_read_scratchpad ( thermo19_t *ctx, uint8_t *scratchpad );
```

- `thermo19_read_temperature` This function reads the temperature value in Celsius.
```c
err_t thermo19_read_temperature ( thermo19_t *ctx, float *temperature );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo19_cfg_t thermo19_cfg;  /**< Click config object. */

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
    thermo19_cfg_setup( &thermo19_cfg );
    THERMO19_MAP_MIKROBUS( thermo19_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == thermo19_init( &thermo19, &thermo19_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMO19_ERROR == thermo19_default_cfg ( &thermo19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and displays the temperature measured by the Click board on the USB UART
approximately every 400ms as this matches the required conversion time for 12-bit temperature resolution.

```c
void application_task ( void )
{
    float temperature;
    if ( THERMO19_OK == thermo19_read_temperature ( &thermo19, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.2f C\r\n\n", temperature );
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
