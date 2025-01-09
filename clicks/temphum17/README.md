
---
# Temp&Hum 17 Click

> [TempHum 17 Click](https://www.mikroe.com/?pid_product=MIKROE-4702) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4702&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jun 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the Temp&Hum 17 Click driver.
> This demo application shows an example of 
> relative humidity and temperature measurement.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum17

### Example Key Functions

- `temphum17_cfg_setup` Config Object Initialization function.
```c
void temphum17_cfg_setup ( temphum17_cfg_t *cfg );
```

- `temphum17_init` Initialization function.
```c
err_t temphum17_init ( temphum17_t *ctx, temphum17_cfg_t *cfg );
```

- `temphum17_default_cfg` Click Default Configuration function.
```c
void temphum17_default_cfg ( temphum17_t *ctx );
```

- `temphum17_wake_up` Temp&Hum 17 wake up function.
```c
err_t temphum17_wake_up ( temphum17_t *ctx );
```

- `temphum17_get_raw_data` Temp&Hum 17 get raw data function.
```c
err_t temphum17_get_raw_data ( temphum17_t *ctx, uint8_t resolution, int16_t *temp, uint16_t *hum, uint8_t *status );
```

- `temphum17_get_temp_hum` Temp&Hum 17 get temperature and humidity function.
```c
err_t temphum17_get_temp_hum ( temphum17_t *ctx, uint8_t resolution, float *temperature, float *humidity );
```

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization and default settings, 
> the app display retrieves the sensor parameters 
> such as temperature and relative humidity.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;             /**< Logger config object. */
    temphum17_cfg_t temphum17_cfg;  /**< Click config object. */

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

    temphum17_cfg_setup( &temphum17_cfg );
    TEMPHUM17_MAP_MIKROBUS( temphum17_cfg, MIKROBUS_1 );
    err_t init_flag = temphum17_init( &temphum17, &temphum17_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    temphum17_default_cfg ( &temphum17 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that shows the use of a Temp&Hum 17 Click board&trade;.
> Logs the temperature [ degree Celsius ] and relative humidity [ % ] data.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    if ( temphum17_get_temp_hum( &temphum17, TEMPHUM17_RESOLUTION_14_BITS, &temperature, &humidity ) == TEMPHUM17_STATUS_VALID_DATA ) {
        log_printf( &logger, "  Temperature : %.02f C\r\n  Humidity    : %.02f %%\r\n", temperature, humidity );
    } else {
        log_printf( &logger, "     Measurement Error\r\n\tStale Data\r\n" );    
    }
    
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms ( 1000 );  
}
```

### Note

> Sequence of commands needed to enter the programming mode, 
which must be sent within 10ms after applying power to the sensor.

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
