
---
# Gyro 8 Click

> [Gyro 8 Click](https://www.mikroe.com/?pid_product=MIKROE-5471) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5471&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2022.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Gyro 8 Click board by reading and displaying the temperature and angular rate measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Gyro8

### Example Key Functions

- `gyro8_cfg_setup` Config Object Initialization function.
```c
void gyro8_cfg_setup ( gyro8_cfg_t *cfg );
```

- `gyro8_init` Initialization function.
```c
err_t gyro8_init ( gyro8_t *ctx, gyro8_cfg_t *cfg );
```

- `gyro8_default_cfg` Click Default Configuration function.
```c
err_t gyro8_default_cfg ( gyro8_t *ctx );
```

- `gyro8_read_serial_id` This function reads the serial ID which is laser marked on the sensor lid.
```c
err_t gyro8_read_serial_id ( gyro8_t *ctx, uint32_t *serial_id );
```

- `gyro8_read_temperature` This function reads the temperature measurement in Celsius.
```c
err_t gyro8_read_temperature ( gyro8_t *ctx, float *temperature );
```

- `gyro8_read_angular_rate` This function reads the angular rate of X-axis in dps.
```c
err_t gyro8_read_angular_rate ( gyro8_t *ctx, float *rate );
```

### Application Init

> Initializes the driver and the Click board, and reads the serial ID number which is marked on the sensor lid.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gyro8_cfg_t gyro8_cfg;  /**< Click config object. */

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
    gyro8_cfg_setup( &gyro8_cfg );
    GYRO8_MAP_MIKROBUS( gyro8_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == gyro8_init( &gyro8, &gyro8_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( GYRO8_ERROR == gyro8_default_cfg ( &gyro8 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint32_t serial_id;
    if ( GYRO8_OK == gyro8_read_serial_id ( &gyro8, &serial_id ) )
    {
        log_printf ( &logger, " Serial ID: %lu\r\n", serial_id );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the temperature and angular rate measurements every 100ms and displays the results on the USB UART.

```c
void application_task ( void )
{
    float temperature, angular_rate;
    if ( GYRO8_OK == gyro8_read_temperature ( &gyro8, &temperature ) )
    {
        log_printf ( &logger, " Temperature: %.2f degC\r\n", temperature );
    }
    if ( GYRO8_OK == gyro8_read_angular_rate ( &gyro8, &angular_rate ) )
    {
        log_printf ( &logger, " Angular rate: %.2f dps\r\n\n", angular_rate );
    }
    Delay_ms ( 100 );
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
