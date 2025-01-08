
---
# TempHum 25 Click

> [TempHum 25 Click](https://www.mikroe.com/?pid_product=MIKROE-6241) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6241&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of TempHum 25 Click board by reading the temperature and humidity data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum25

### Example Key Functions

- `temphum25_cfg_setup` Config Object Initialization function.
```c
void temphum25_cfg_setup ( temphum25_cfg_t *cfg );
```

- `temphum25_init` Initialization function.
```c
err_t temphum25_init ( temphum25_t *ctx, temphum25_cfg_t *cfg );
```

- `temphum25_read_serial_num` This function reads the 4-bytes unique serial number by using I2C serial interface.
```c
err_t temphum25_read_serial_num ( temphum25_t *ctx, uint32_t *serial_num );
```

- `temphum25_start_measurement` This function starts the measurement by sending the selected measurement command.
```c
err_t temphum25_start_measurement ( temphum25_t *ctx, uint16_t meas_cmd );
```

- `temphum25_read_measurement` This function reads the temperature and humidity measurements results.
```c
err_t temphum25_read_measurement ( temphum25_t *ctx, float *temperature, float *humidity );
```

### Application Init

> Initializes the driver, performs the device reset, reads and displays the sensor unique serial number, and then starts the measurements with 1 MPS.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    temphum25_cfg_t temphum25_cfg;  /**< Click config object. */

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
    temphum25_cfg_setup( &temphum25_cfg );
    TEMPHUM25_MAP_MIKROBUS( temphum25_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == temphum25_init( &temphum25, &temphum25_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    temphum25_reset_device ( &temphum25 );

    uint32_t serial_num = 0;
    if ( TEMPHUM25_OK == temphum25_read_serial_num ( &temphum25, &serial_num ) )
    {
        log_printf ( &logger, " Serial number: 0x%.8LX\r\n", serial_num );
    }

    temphum25_start_measurement ( &temphum25, TEMPHUM25_CMD_MEAS_CONT_REP_HIGH_MPS_1 );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the temperature (degC) and the relative humidity (%RH) data and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    float temperature = 0;
    float humidity = 0;
    if ( TEMPHUM25_OK == temphum25_read_measurement ( &temphum25, &temperature, &humidity ) )
    {
        log_printf ( &logger, " Temperature: %.2f degC\r\n", temperature );
        log_printf ( &logger, " Humidity: %.2f %%RH\r\n\n", humidity );
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
