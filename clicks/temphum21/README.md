
---
# TempHum 21 Click

> [TempHum 21 Click](https://www.mikroe.com/?pid_product=MIKROE-5240) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5240&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Temp & Hum 21 Click board by reading the temperature and humidity data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum21

### Example Key Functions

- `temphum21_cfg_setup` Config Object Initialization function.
```c
void temphum21_cfg_setup ( temphum21_cfg_t *cfg );
```

- `temphum21_init` Initialization function.
```c
err_t temphum21_init ( temphum21_t *ctx, temphum21_cfg_t *cfg );
```

- `temphum21_read_measurement` This function requests measurement and waits for a measurement to complete and after that reads temperature in Celsius and relative humidity in percents.
```c
err_t temphum21_read_measurement ( temphum21_t *ctx, float *temperature, float *humidity );
```

- `temphum21_get_all_pin` This function returns the alarm low (ALL) pin logic state.
```c
uint8_t temphum21_get_all_pin ( temphum21_t *ctx );
```

- `temphum21_get_alh_pin` This function returns the alarm high (ALH) pin logic state.
```c
uint8_t temphum21_get_alh_pin ( temphum21_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    temphum21_cfg_t temphum21_cfg;  /**< Click config object. */

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
    temphum21_cfg_setup( &temphum21_cfg );
    TEMPHUM21_MAP_MIKROBUS( temphum21_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == temphum21_init( &temphum21, &temphum21_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TEMPHUM21_ERROR == temphum21_default_cfg ( &temphum21 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the temperature (Celsius) and humidity (Percents) data and displays the results on the USB UART approximately once per second.
It also checks if any alarm is detected on the humidity measurement.

```c
void application_task ( void )
{
    float temperature = 0;
    float humidity = 0;
    if ( TEMPHUM21_STATUS_NORMAL_OP == temphum21_read_measurement ( &temphum21, &temperature, &humidity ) )
    {
        if ( temphum21_get_all_pin ( &temphum21 ) )
        {
            log_info ( &logger, " Alarm LOW detected " );
        }
        else if ( temphum21_get_alh_pin ( &temphum21 ) )
        {
            log_info ( &logger, " Alarm HIGH detected " );
        }
        
        log_printf ( &logger, " Temperature: %.2f C\r\n", temperature );
        log_printf ( &logger, " Humidity: %.2f %%\r\n\n", humidity );
        
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
