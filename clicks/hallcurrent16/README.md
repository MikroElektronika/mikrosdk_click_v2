
---
# Hall Current 16 Click

> [Hall Current 16 Click](https://www.mikroe.com/?pid_product=MIKROE-5784) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5784&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jun 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Hall Current 16 Click board 
> by reading and displaying the current measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent16

### Example Key Functions

- `hallcurrent16_cfg_setup` Config Object Initialization function.
```c
void hallcurrent16_cfg_setup ( hallcurrent16_cfg_t *cfg );
```

- `hallcurrent16_init` Initialization function.
```c
err_t hallcurrent16_init ( hallcurrent16_t *ctx, hallcurrent16_cfg_t *cfg );
```

- `hallcurrent16_default_cfg` Click Default Configuration function.
```c
err_t hallcurrent16_default_cfg ( hallcurrent16_t *ctx );
```

- `hallcurrent16_get_current` Hall Current 16 get current function.
```c
err_t hallcurrent16_get_current ( hallcurrent16_t *ctx, float *current );
```

- `hallcurrent16_get_voltage`  Hall Current 16 get voltage function.
```c
err_t hallcurrent16_get_voltage ( hallcurrent16_t *ctx, float *voltage );
```

- `hallcurrent16_get_ovc_fault` Hall Current 16 get overcurrent fault function.
```c
uint8_t hallcurrent16_get_ovc_fault ( hallcurrent16_t *ctx );
```

### Application Init

> The initialization of SPI module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hallcurrent16_cfg_t hallcurrent16_cfg;  /**< Click config object. */

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
    hallcurrent16_cfg_setup( &hallcurrent16_cfg );
    HALLCURRENT16_MAP_MIKROBUS( hallcurrent16_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == hallcurrent16_init( &hallcurrent16, &hallcurrent16_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HALLCURRENT16_ERROR == hallcurrent16_default_cfg ( &hallcurrent16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " -------------------- \r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The app reads the current measurements [A] and displays the results.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    static float current;
    if ( HALLCURRENT16_OK == hallcurrent16_get_current( &hallcurrent16, &current ) )
    {
        log_printf( &logger, " Current : %.3f A \r\n", current );
    }
    log_printf( &logger, " -------------------- \r\n" );
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
