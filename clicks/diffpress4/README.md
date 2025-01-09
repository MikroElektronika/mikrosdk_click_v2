
---
# Diff Press 4 Click

> [Diff Press 4 Click](https://www.mikroe.com/?pid_product=MIKROE-5868) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5868&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Diff Press 4 Click board&trade; 
> by reading and displaying the differential pressure and sensor temperature measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DiffPress4

### Example Key Functions

- `diffpress4_cfg_setup` Config Object Initialization function.
```c
void diffpress4_cfg_setup ( diffpress4_cfg_t *cfg );
```

- `diffpress4_init` Initialization function.
```c
err_t diffpress4_init ( diffpress4_t *ctx, diffpress4_cfg_t *cfg );
```

- `diffpress4_get_measurement_data` Diff Press 4 gets the raw data function.
```c
err_t diffpress4_get_measurement_data ( diffpress4_t *ctx, float *diff_press, float *temperature );
```

- `diffpress4_get_status` Diff Press 4 get status function.
```c
err_t diffpress4_get_status ( diffpress4_t *ctx, diffpress4_status_t *status );
```

- `diffpress4_get_raw_data` Diff Press 4 gets the raw data function.
```c
err_t diffpress4_get_raw_data ( diffpress4_t *ctx, int16_t *temp_data, int16_t *press_data );
```

### Application Init

> The initialization of I2C module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    diffpress4_cfg_t diffpress4_cfg;  /**< Click config object. */

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
    diffpress4_cfg_setup( &diffpress4_cfg );
    DIFFPRESS4_MAP_MIKROBUS( diffpress4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == diffpress4_init( &diffpress4, &diffpress4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, " _______________________ \r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application reads and displays the Differential Pressure [Pa] 
> and sensor Temperature [degree Celsius] data measurements.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    static float diff_press = 0, temperature = 0;
    diffpress4_status_t status;
    diffpress4_get_status( &diffpress4, &status );
    if ( ( DIFFPRESS4_OK == diffpress4_get_measurement_data( &diffpress4, &diff_press, &temperature ) ) &&
         ( DIFFPRESS4_STATUS_DSP_S_UPDATED == status.dsp_s_up ) && 
         ( DIFFPRESS4_STATUS_DSP_T_UPDATED == status.dsp_t_up ) )
    {
        log_printf( &logger, " Diff Pressure : %.2f [Pa] \r\n", diff_press );
        log_printf( &logger, " Temperature   : %.2f [degC] \r\n", temperature );
        log_printf( &logger, " _______________________ \r\n" );
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
