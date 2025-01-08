
---
# Pressure 22 Click

> [Pressure 22 Click](https://www.mikroe.com/?pid_product=MIKROE-5774) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5774&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : May 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for Pressure 22 Click driver.
> The demo application reads and calculate pressure and temperature data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure22

### Example Key Functions

- `pressure22_cfg_setup` Config Object Initialization function.
```c
void pressure22_cfg_setup ( pressure22_cfg_t *cfg );
```

- `pressure22_init` Initialization function.
```c
err_t pressure22_init ( pressure22_t *ctx, pressure22_cfg_t *cfg );
```

- `pressure22_default_cfg` Click Default Configuration function.
```c
err_t pressure22_default_cfg ( pressure22_t *ctx );
```

- `pressure22_get_measurement_data` Pressure 22 get the measurement data function.
```c
err_t pressure22_get_measurement_data ( pressure22_t *ctx, float *temperature, float *pressure );
```

- `pressure22_get_calibration_data` Pressure 22 gets the calibration data function.
```c
err_t pressure22_get_calibration_data ( pressure22_t *ctx );
```

- `pressure22_get_adc_data` Pressure 22 gets the ADC data function.
```c
err_t pressure22_get_adc_data ( pressure22_t *ctx, uint32_t *adc );
```

### Application Init

> The initialization of I2C module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure22_cfg_t pressure22_cfg;  /**< Click config object. */

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
    pressure22_cfg_setup( &pressure22_cfg );
    PRESSURE22_MAP_MIKROBUS( pressure22_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == pressure22_init( &pressure22, &pressure22_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRESSURE22_ERROR == pressure22_default_cfg ( &pressure22 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ____________________ \r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the Pressure 22 Click board&trade;.
> The demo application reads and displays the Pressure [mBar] 
> and Temperature [degree Celsius] data.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{   
    static float temperature, pressure;
    if ( PRESSURE22_OK == pressure22_get_measurement_data( &pressure22, &temperature, &pressure ) )
    {
        log_printf( &logger, " Temperature : %.2f degC \r\n", temperature );
        log_printf( &logger, " Pressure    : %.2f mBar \r\n", pressure );
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
