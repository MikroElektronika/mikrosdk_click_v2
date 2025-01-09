
---
# Temp&Hum 8 Click

> [TempHum 8 Click](https://www.mikroe.com/?pid_product=MIKROE-3263) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3263&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This demo-app shows the temperature measurement procedure using Temp&Hum 8 Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum8

### Example Key Functions

- `temphum8_cfg_setup` Config Object Initialization function. 
```c
void temphum8_cfg_setup ( temphum8_cfg_t *cfg );
``` 
 
- `temphum8_init` Initialization function. 
```c
err_t temphum8_init ( temphum8_t *ctx, temphum8_cfg_t *cfg );
```

- `temphum8_default_cfg` Click Default Configuration function. 
```c
void temphum8_default_cfg ( temphum8_t *ctx );
```

- `temphum8_get_temperature_data` Temperature data. 
```c
float temphum8_get_temperature_data ( temphum8_t *ctx, uint8_t temp_format );
```
 
- `temphum8_get_humidity_data` Relative Huminidy data. 
```c
float temphum8_get_humidity_data ( temphum8_t *ctx );
```

- `temphum8_set_cfg_register` Configuration device for measurement. 
```c
void temphum8_set_cfg_register ( temphum8_t *ctx, uint8_t cfg );
```

### Application Init

> Configuring Clicks and log objects. 
> Setting the Click in the default configuration to start the measurement, 
> and before that call function software_reset().

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum8_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    temphum8_cfg_setup( &cfg );
    TEMPHUM8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum8_init( &temphum8, &cfg );

    temphum8_software_reset( &temphum8 );
    temphum8_default_cfg( &temphum8 ); 
}
```

### Application Task

> Reads ambient temperature data and Relative Huminidy data, 
> this data logs to USBUART every 1500ms.

```c
void application_task ( void )
{
    float temperature;
    float humidity;

    //  Task implementation.
    
    log_printf( &logger, "\r\n ---- Ambient data ----\r\n" );

    temperature = temphum8_get_temperature_data( &temphum8, TEMPHUM8_TEMPERATURE_IN_CELSIUS );
    log_printf( &logger, "** Temperature: %.2f °C \r\n", temperature );
    
    humidity = temphum8_get_humidity_data( &temphum8 );
    log_printf( &logger, "** Humidity: %.2f %%RH \r\n", humidity );

    Delay_ms ( 1000 );
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
