
---
# Environment 6 Click

> [Environment 6 Click](https://www.mikroe.com/?pid_product=MIKROE-6536) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6536&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2025.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of the Environment 6 Click board, which integrates 
a high-precision environmental sensor for measuring temperature, humidity, pressure, 
and gas resistance. The application initializes the device and periodically reads 
and logs all available environmental parameters via UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Environment6

### Example Key Functions

- `environment6_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void environment6_cfg_setup ( environment6_cfg_t *cfg );
```

- `environment6_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t environment6_init ( environment6_t *ctx, environment6_cfg_t *cfg );
```

- `environment6_default_cfg` This function executes a default configuration of Environment 6 Click board.
```c
err_t environment6_default_cfg ( environment6_t *ctx );
```

- `environment6_set_sensor_conf` This function configures the sensor oversampling, filter, and data rate.
```c
err_t environment6_set_sensor_conf ( environment6_t *ctx, environment6_sen_conf_t *conf );
```

- `environment6_set_gas_conf` This function sets the heater temperature, duration, and enables gas measurements.
```c
err_t environment6_set_gas_conf ( environment6_t *ctx, environment6_gas_conf_t *conf );
```

- `environment6_get_data` This function triggers a measurement and reads temperature, pressure, humidity, and gas resistance data.
```c
err_t environment6_get_data ( environment6_t *ctx, environment6_data_t *data_out );
```

### Application Init

> Initializes the logger and configures the Environment 6 Click. It sets up communication and applies the default configuration to the sensor.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    environment6_cfg_t environment6_cfg;  /**< Click config object. */

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
    environment6_cfg_setup( &environment6_cfg );
    ENVIRONMENT6_MAP_MIKROBUS( environment6_cfg, MIKROBUS_1 );
    err_t init_flag = environment6_init( &environment6, &environment6_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ENVIRONMENT6_ERROR == environment6_default_cfg ( &environment6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Continuously reads temperature (degC), humidity (%RH), pressure (mBar), and gas resistance (Ohms) if enabled, then logs the measured values every second.

```c
void application_task ( void )
{
    environment6_data_t meas_res;
    if ( ENVIRONMENT6_OK == environment6_get_data ( &environment6, &meas_res ) )
    {
        log_printf( &logger, " Temperature : %.2f degC\r\n", meas_res.temperature );
        log_printf( &logger, " Humidity : %.2f %%\r\n", meas_res.humidity );
        log_printf( &logger, " Pressure : %.1f mBar\r\n", meas_res.pressure );
        if ( environment6.gas_conf.enable )
        {
            log_printf( &logger, " Gas Resistance : %.1f Ohms\r\n", meas_res.gas_resistance );
        }
        log_printf( &logger, "--------------------------------\r\n" );
        Delay_ms ( 1000 );
    }
}
```

### Note

> The BME690 sensor on this Click board provides raw gas resistance data only.
To calculate indoor air quality (IAQ), VOC index, CO2 equivalents, and similar
environmental parameters, Bosch Sensortec BSEC (Bosch Software Environmental Cluster) 
algorithm must be integrated separately.

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
