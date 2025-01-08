
---
# DHT22 Click

> [DHT22 Click](https://www.mikroe.com/?pid_product=MIKROE-1798) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1798&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : GPIO type

# Software Support

## Example Description

> This is a example which demonstrates the use of DHT22 Click board by measuring temperature and relative humidity.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Dht22

### Example Key Functions

- `dht22_cfg_setup` Config Object Initialization function.
```c
void dht22_cfg_setup ( dht22_cfg_t *cfg );
```

- `dht22_init` Initialization function.
```c
err_t dht22_init ( dht22_t *ctx, dht22_cfg_t *cfg );
```

- `dht22_get_measurement_data` DHT22 get measurement data from the sensor function.
```c
err_t dht22_get_measurement_data ( dht22_t *ctx, float *humidity, float *temperature );
``` 

- `dht22_start_signal` DHT22 sends start signal to the sensor function.
```c
void dht22_start_signal ( dht22_t *ctx );
```

- `dht22_check_sensor_response` DHT22 release the bus to wait the sensor response signal function.
```c
uint8_t dht22_check_sensor_response ( dht22_t *ctx );
``` 

### Application Init

> Initializes the SDA data pin depending on the selected GPIO pin (SDA1/SDA2) and log module.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dht22_cfg_t dht22_cfg;  /**< Click config object. */

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
    dht22_cfg_setup( &dht22_cfg );
    DHT22_MAP_MIKROBUS( dht22_cfg, MIKROBUS_1 );

   if ( DIGITAL_OUT_UNSUPPORTED_PIN == dht22_init( &dht22, &dht22_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, "---- Application Init done. ----" );
}
```

### Application Task

> Reads the temperature and humidity from the sensor and displays the values on the USB UART. 

```c
void application_task ( void )
{
    static float temperature = 0;
    static float humidity = 0;
    
    dht22_init_sda_output( &dht22 );
    if ( DHT22_OK == dht22_start_signal( &dht22 ) )
    {
        dht22_init_sda_input( &dht22 );
        if ( DHT22_OK == dht22_check_sensor_response( &dht22 ) )
        {
            if ( DHT22_OK == dht22_get_measurement_data( &dht22, &humidity, &temperature ) )
            {
                log_printf( &logger, " Humidity : %.2f %%\r\n", humidity );
                log_printf( &logger, " Temperature : %.2f degC\r\n", temperature );
                log_printf( &logger, " ---------------------------\r\n" );
                Delay_ms ( 1000 );
            }
        }
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
