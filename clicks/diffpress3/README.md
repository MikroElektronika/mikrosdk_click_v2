
---
# Diff Press 3 Click

> [Diff Press 3 Click](https://www.mikroe.com/?pid_product=MIKROE-5771) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5771&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : May 2023.
- **Type**          : ADC/I2C type

# Software Support

## Example Description

> This library contains API for the Diff Press 3 Click driver.
> This demo application shows an example of 
> differential pressure and temperature measurement.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DiffPress3

### Example Key Functions

- `diffpress3_cfg_setup` Config Object Initialization function.
```c
void diffpress3_cfg_setup ( diffpress3_cfg_t *cfg );
```

- `diffpress3_init` Initialization function.
```c
err_t diffpress3_init ( diffpress3_t *ctx, diffpress3_cfg_t *cfg );
```

- `diffpress3_get_pressure` Diff Press 3 get pressure function.
```c
err_t diffpress3_get_pressure ( diffpress3_t *ctx, float *pressure );
```

- `diffpress3_get_temperature` Diff Press 3 get temperature function.
```c
err_t diffpress3_get_temperature ( diffpress3_t *ctx, float *temperature );
```

- `diffpress3_read_raw_adc` Diff Press 3 read raw ADC value function.
```c
err_t diffpress3_read_raw_adc ( diffpress3_t *ctx, uint16_t *raw_adc, diffpress3_d_sel_t data_sel );
```

### Application Init

> Initialization of I2C and ADC module and log UART.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    diffpress3_cfg_t diffpress3_cfg;  /**< Click config object. */

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
    diffpress3_cfg_setup( &diffpress3_cfg );
    DIFFPRESS3_MAP_MIKROBUS( diffpress3_cfg, MIKROBUS_1 );
    err_t init_flag = diffpress3_init( &diffpress3, &diffpress3_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the Diff Press 3 Click board&trade;.
> The demo application measures and display the Differential Pressure [kPa]
> and Temperature [degree Celsius] data.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    float pressure, temperature;
    if ( DIFFPRESS3_OK == diffpress3_get_pressure( &diffpress3, &pressure ) )
    {
        log_printf( &logger, " Diff Pressure: %.3f [kPa]\r\n", pressure );
        Delay_ms ( 100 );
    }
    if ( DIFFPRESS3_OK == diffpress3_get_temperature( &diffpress3, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.2f [C]\r\n", temperature );
        Delay_ms ( 100 );
    }
    log_printf( &logger, "---------------------\r\n" );
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
