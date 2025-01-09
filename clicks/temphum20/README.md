
---
# TempHum 20 Click

> [TempHum 20 Click](https://www.mikroe.com/?pid_product=MIKROE-4907) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4907&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Temp & Hum 20 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum20

### Example Key Functions

- `temphum20_cfg_setup` Config Object Initialization function.
```c
void temphum20_cfg_setup ( temphum20_cfg_t *cfg );
```

- `temphum20_init` Initialization function.
```c
err_t temphum20_init ( temphum20_t *ctx, temphum20_cfg_t *cfg );
```

- `temphum20_default_cfg` Click Default Configuration function.
```c
err_t temphum20_default_cfg ( temphum20_t *ctx );
```

- `temphum20_write_command` This function writes a desired command data to the selected command byte.
```c
err_t temphum20_write_command ( temphum20_t *ctx, uint8_t cmd_byte, uint16_t cmd_data );
```

- `temphum20_get_measurement` This function waits for the data to be ready, and then reads the temperature and humidity data and converts them to Celsius and Percents, respectively.
```c
err_t temphum20_get_measurement ( temphum20_t *ctx, float *temp, float *hum );
```

- `temphum20_set_operating_mode` This function sets the device operating mode.
```c
err_t temphum20_set_operating_mode ( temphum20_t *ctx, uint8_t op_mode );
```

### Application Init

> Initializes the driver and logger and performs the Click default configuration which resets the device and sets it to normal operating mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    temphum20_cfg_t temphum20_cfg;  /**< Click config object. */

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
    temphum20_cfg_setup( &temphum20_cfg );
    TEMPHUM20_MAP_MIKROBUS( temphum20_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == temphum20_init( &temphum20, &temphum20_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TEMPHUM20_ERROR == temphum20_default_cfg ( &temphum20 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> When the new data is ready, this function reads the temperature and humidity data and displays the results on the USB UART.

```c
void application_task ( void )
{
    float humidity, temperature = 0;
    
    if ( TEMPHUM20_OK == temphum20_get_measurement ( &temphum20, &temperature, &humidity ) )
    {
        log_printf ( &logger, " Temperature: %.3f C\r\n", temperature );
        log_printf ( &logger, " Humidity: %.3f %%\r\n\n", humidity );
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
