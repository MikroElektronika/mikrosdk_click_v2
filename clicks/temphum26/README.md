
---
# TempHum 26 Click

> [TempHum 26 Click](https://www.mikroe.com/?pid_product=MIKROE-6688) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6688&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of TempHum 26 Click board by reading the temperature
and humidity values in periodic intervals. The device is initialized and placed into 
single-shot measurement mode, then both environmental values are read and logged to the USB UART.
Data is updated every 200 ms.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum26

### Example Key Functions

- `temphum26_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void temphum26_cfg_setup ( temphum26_cfg_t *cfg );
```

- `temphum26_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t temphum26_init ( temphum26_t *ctx, temphum26_cfg_t *cfg );
```

- `temphum26_default_cfg` This function executes a default configuration of TempHum 26 Click board.
```c
err_t temphum26_default_cfg ( temphum26_t *ctx );
```

- `temphum26_start_measurement` This function starts the measurement for temperature, humidity, or both depending on the selected flag.
```c
err_t temphum26_start_measurement ( temphum26_t *ctx, uint8_t flag );
```

- `temphum26_read_data` This function reads temperature and humidity data from the device with CRC check and data validity.
```c
err_t temphum26_read_data ( temphum26_t *ctx, float *temp, float *hum );
```

### Application Init

> Initializes the driver and performs the default configuration including device reset
and communication check. It then logs the DIE revision number and unique ID.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    temphum26_cfg_t temphum26_cfg;  /**< Click config object. */

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
    temphum26_cfg_setup( &temphum26_cfg );
    TEMPHUM26_MAP_MIKROBUS( temphum26_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == temphum26_init( &temphum26, &temphum26_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TEMPHUM26_ERROR == temphum26_default_cfg ( &temphum26 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_printf ( &logger, " DIE revision number: 0x%.4X\r\n", temphum26.info.die_rev );
    log_printf ( &logger, " Unique ID: 0x%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X\r\n", 
                 ( uint16_t ) temphum26.info.uid[ 0 ], ( uint16_t ) temphum26.info.uid[ 1 ],
                 ( uint16_t ) temphum26.info.uid[ 2 ], ( uint16_t ) temphum26.info.uid[ 3 ],
                 ( uint16_t ) temphum26.info.uid[ 4 ], ( uint16_t ) temphum26.info.uid[ 5 ],
                 ( uint16_t ) temphum26.info.uid[ 6 ], ( uint16_t ) temphum26.info.uid[ 7 ] );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Starts a new temperature and humidity measurement, waits for the results, and logs the readings to the terminal every 200 ms.

```c
void application_task ( void )
{
    float temperature = 0;
    float humidity = 0;
    if ( TEMPHUM26_OK == temphum26_start_measurement ( &temphum26, TEMPHUM26_FLAG_TEMP_HUM ) )
    {
        if ( TEMPHUM26_OK == temphum26_read_data ( &temphum26, &temperature, &humidity ) )
        {
            log_printf ( &logger, " Temperature: %.2f degC\r\n", temperature );
            log_printf ( &logger, " Humidity: %.2f %%RH\r\n\n", humidity );
            Delay_ms ( 200 );
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
