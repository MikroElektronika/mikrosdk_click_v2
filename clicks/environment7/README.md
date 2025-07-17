
---
# Environment 7 Click

> [Environment 7 Click](https://www.mikroe.com/?pid_product=MIKROE-6600) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6600&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Environment 7 Click board, which provides 
temperature, humidity, and CO2 concentration measurements. The example initializes 
the device, reads sensor IDs, and continuously logs environmental data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Environment7

### Example Key Functions

- `environment7_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void environment7_cfg_setup ( environment7_cfg_t *cfg );
```

- `environment7_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t environment7_init ( environment7_t *ctx, environment7_cfg_t *cfg );
```

- `environment7_read_id` This function reads the product and serial numbers of the STCC4 device.
```c
err_t environment7_read_id ( environment7_t *ctx, uint32_t *prod_num, uint32_t *serial_num_msb, uint32_t *serial_num_lsb );
```

- `environment7_set_meas_mode` This function sets the measurement mode on the STCC4 device.
```c
err_t environment7_set_meas_mode ( environment7_t *ctx, uint8_t mode );
```

- `environment7_read_meas` This function reads gas concentration, temperature, and relative humidity data from the STCC4 device.
```c
err_t environment7_read_meas ( environment7_t *ctx, uint16_t *gas, float *temp, float *hum );
```

### Application Init

> Initializes the logger, retrieves and logs the product and serial numbers, and starts
the measurement in continuous mode with 1Hz sampling rate.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    environment7_cfg_t environment7_cfg;  /**< Click config object. */

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
    environment7_cfg_setup( &environment7_cfg );
    ENVIRONMENT7_MAP_MIKROBUS( environment7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == environment7_init( &environment7, &environment7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    uint32_t prod_num = 0;
    uint32_t serial_msb = 0;
    uint32_t serial_lsb = 0;
    if ( ENVIRONMENT7_OK != environment7_read_id ( &environment7, &prod_num, &serial_msb, &serial_lsb ) )
    {
        log_error( &logger, " Check communication." );
        for ( ; ; );
    }
    log_printf ( &logger, " Product number: 0x%.8LX\r\n", prod_num );
    log_printf ( &logger, " Serial number: 0x%.8LX%.8LX\r\n", serial_msb, serial_lsb );
    
    if ( ENVIRONMENT7_OK == environment7_set_meas_mode ( &environment7, ENVIRONMENT7_MEAS_MODE_START_CONTINUOUS ) )
    {
        log_printf ( &logger, " Continuous measurement started (1 Hz output)\r\n" );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Continuously reads and logs temperature (degC) and humidity (%RH), and CO2 concentration (ppm) from sensors.

```c
void application_task ( void )
{
    float temperature = 0;
    float humidity = 0;
    uint16_t co2_concentration = 0;

    if ( ENVIRONMENT7_OK == environment7_read_meas ( &environment7, &co2_concentration, &temperature, &humidity ) )
    {
        log_printf ( &logger, " Temperature: %.2f degC\r\n", temperature );
        log_printf ( &logger, " Humidity: %.2f %%RH\r\n", humidity );
        log_printf ( &logger, " CO2: %u ppm\r\n\n", co2_concentration );
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
