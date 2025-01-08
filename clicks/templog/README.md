
---
# Temp-Log Click

> [Temp-Log Click](https://www.mikroe.com/?pid_product=MIKROE-2886) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2886&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This example returns values of the temperature from the sensor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempLog

### Example Key Functions

- `templog_cfg_setup` Config Object Initialization function. 
```c
void templog_cfg_setup ( templog_cfg_t *cfg );
``` 
 
- `templog_init` Initialization function. 
```c
err_t templog_init ( templog_t *ctx, templog_cfg_t *cfg );
```

- `templog_default_cfg` Click Default Configuration function. 
```c
void templog_default_cfg ( templog_t *ctx );
```

- `temp_log_read_temp_dec ` This function reads decimal value of temp. 
```c
uint16_t temp_log_read_temp_dec  ( templog_t *ctx, uint16_t resolution );
```
 
- `temp_log_convert_to_celsius ` This function converts temperature data to celsius value. 
```c
float temp_log_convert_to_celsius  ( uint16_t temperature_data );
```

- `temp_log_get_alert ` This function alerts user if temperature limit is alarming. 
```c
uint8_t temp_log_get_alert  ( templog_t *ctx );
```

### Application Init

> Initializes Click driver. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    templog_cfg_t cfg;

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
    templog_cfg_setup ( &cfg );    
    TEMPLOG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    if ( TEMPLOG_OK != templog_init ( &templog, &cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    templog_default_cfg ( &templog );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads temperature from temperature register in decimal value in 9-bit resolution,
> converts that decimal value in celsius value and checks Alert pin witch goes active (low)
> if the measured temperature meets or exceeds the high temperature limit.

```c
void application_task ( void )
{
    uint16_t temp_in_dec = 0;
    float temp_in_cels = 0;
    
    temp_in_dec = temp_log_read_temp_dec(&templog, TEMP_LOG_RESOLUTION_9_BITS);
    temp_in_cels = temp_log_convert_to_celsius(temperature);
    
    log_printf(&logger, "Temperature in decimal value is: %d\n", temp_in_dec);
    log_printf(&logger, "Temperature in celsius value is: %f\n", temp_in_cels);

    if(temp_log_get_alert(&templog) == 0)
    {
        log_printf( &logger, "TEMPERATURE LIMIT ALARMING!\r\n" );
    }
    
    Delay_ms ( 1000 );
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
