
---
# Environment 5 Click

> [Environment 5 Click](https://www.mikroe.com/?pid_product=MIKROE-6573) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6573&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Environment 5 Click board, which provides 
temperature, humidity, and CO2 concentration measurements. The example initializes 
the device, reads sensor IDs, and continuously logs environmental data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Environment5

### Example Key Functions

- `environment5_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void environment5_cfg_setup ( environment5_cfg_t *cfg );
```

- `environment5_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t environment5_init ( environment5_t *ctx, environment5_cfg_t *cfg );
```

- `environment5_default_cfg` This function executes a default configuration of Environment 5 Click board.
```c
err_t environment5_default_cfg ( environment5_t *ctx );
```

- `environment5_sht_read_meas_hp` This function reads the temperature and humidity measurements with high precision from SHT40 device.
```c
err_t environment5_sht_read_meas_hp ( environment5_t *ctx, float *temp, float *hum );
```

- `environment5_stc_set_hum` This function sets the relative humidity compensation value on the STC31-C device.
```c
err_t environment5_stc_set_hum ( environment5_t *ctx, float humidity );
```

- `environment5_stc_read_meas` This function reads gas concentration and temperature data from the STC31-C device.
```c
err_t environment5_stc_read_meas ( environment5_t *ctx, float *gas, float *temp );
```

### Application Init

> Initializes the logger and configures the Environment 5 Click board. It also retrieves and logs the product and serial numbers of the onboard sensors.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    environment5_cfg_t environment5_cfg;  /**< Click config object. */

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
    environment5_cfg_setup( &environment5_cfg );
    ENVIRONMENT5_MAP_MIKROBUS( environment5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == environment5_init( &environment5, &environment5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ENVIRONMENT5_ERROR == environment5_default_cfg ( &environment5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint32_t stc_prod_num = 0;
    uint32_t stc_serial_msb = 0;
    uint32_t stc_serial_lsb = 0;
    if ( ENVIRONMENT5_OK == environment5_stc_read_id ( &environment5, &stc_prod_num, &stc_serial_msb, &stc_serial_lsb ) )
    {
        log_printf ( &logger, " STC31-C Product number: 0x%.8LX\r\n", stc_prod_num );
        log_printf ( &logger, " STC31-C Serial number: 0x%.8LX%.8LX\r\n", stc_serial_msb, stc_serial_lsb );
    }

    uint32_t sht_serial = 0;
    if ( ENVIRONMENT5_OK == environment5_sht_read_serial ( &environment5, &sht_serial ) )
    {
        log_printf ( &logger, " SHT40 Serial number: 0x%.8LX\r\n", sht_serial );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Continuously reads and logs temperature (degC) and humidity (%RH), and CO2 concentration (vol%) from sensors.

```c
void application_task ( void )
{
    float temperature = 0;
    float humidity = 0;
    float co2_concentration = 0;

    err_t error_flag = environment5_sht_read_meas_hp ( &environment5, &temperature, &humidity );
    if ( ENVIRONMENT5_OK == error_flag )
    {
        error_flag |= environment5_stc_set_temp ( &environment5, temperature );
        error_flag |= environment5_stc_set_hum ( &environment5, humidity );
        error_flag |= environment5_stc_read_meas ( &environment5, &co2_concentration, NULL );
    }

    if ( ENVIRONMENT5_OK == error_flag )
    {
        log_printf ( &logger, " Temperature: %.2f degC\r\n", temperature );
        log_printf ( &logger, " Humidity: %.2f %%RH\r\n", humidity );
        log_printf ( &logger, " CO2 in air [0-40]: %.2f vol%%\r\n\n", co2_concentration );
    }

    Delay_ms ( 500 );
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
