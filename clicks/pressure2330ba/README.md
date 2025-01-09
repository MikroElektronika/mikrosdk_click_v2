
---
# Pressure 23 30BA Click

> [Pressure 23 30BA Click](https://www.mikroe.com/?pid_product=MIKROE-5768) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5768&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2023.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of Pressure 23 30BA Click board&trade; by reading and displaying
> the pressure and temperature measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure2330BA

### Example Key Functions

- `pressure2330ba_cfg_setup` Config Object Initialization function.
```c
void pressure2330ba_cfg_setup ( pressure2330ba_cfg_t *cfg );
```

- `pressure2330ba_init` Initialization function.
```c
err_t pressure2330ba_init ( pressure2330ba_t *ctx, pressure2330ba_cfg_t *cfg );
```

- `pressure2330ba_default_cfg` Click Default Configuration function.
```c
err_t pressure2330ba_default_cfg ( pressure2330ba_t *ctx );
```

- `pressure2330ba_get_measurement_data` Pressure 23 30BA gets the measurement data function.
```c
err_t pressure2330ba_get_measurement_data ( pressure2330ba_t *ctx, float *pressure, float *temperature );
```

- `pressure2330ba_get_calibration_data` Pressure 23 30BA gets the calibration data function.
```c
err_t pressure2330ba_get_calibration_data ( pressure2330ba_t *ctx );
```

- `pressure2330ba_read_adc` Pressure 23 30BA ADC data reading function.
```c
err_t pressure2330ba_read_adc ( pressure2330ba_t *ctx, uint8_t sel_data, uint32_t *adc_data );
```

### Application Init

> The initialization of I2C or SPI module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure2330ba_cfg_t pressure2330ba_cfg;  /**< Click config object. */

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
    pressure2330ba_cfg_setup( &pressure2330ba_cfg );
    PRESSURE2330BA_MAP_MIKROBUS( pressure2330ba_cfg, MIKROBUS_1 );
    err_t init_flag = pressure2330ba_init( &pressure2330ba, &pressure2330ba_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRESSURE2330BA_ERROR == pressure2330ba_default_cfg ( &pressure2330ba ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, " _______________________ \r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application reads and displays the Pressure [mBar] 
> and Temperature [degree Celsius] data.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    static float temperature, pressure;
    if ( PRESSURE2330BA_OK == pressure2330ba_get_measurement_data( &pressure2330ba, &pressure, &temperature ) )
    {
        log_printf( &logger, " Pressure    : %.2f mBar \r\n", pressure );
        log_printf( &logger, " Temperature : %.2f degC \r\n", temperature );
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
