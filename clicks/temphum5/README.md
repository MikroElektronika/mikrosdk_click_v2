
---
# Temp&Hum 5 Click

> [TempHum 5 Click](https://www.mikroe.com/?pid_product=MIKROE-3425) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3425&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application measures temperature and humidity.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum5

### Example Key Functions

- `temphum5_cfg_setup` Config Object Initialization function. 
```c
void temphum5_cfg_setup ( temphum5_cfg_t *cfg );
``` 
 
- `temphum5_init` Initialization function. 
```c
err_t temphum5_init ( temphum5_t *ctx, temphum5_cfg_t *cfg );
```

- `temphum5_start_measurement` Functions for start measurement. 
```c
uint8_t temphum5_start_measurement ( temphum5_t *ctx );
```
 
- `temphum5_get_temperature` Functions for read Temperature data. 
```c
float temphum5_get_temperature ( temphum5_t *ctx, uint8_t temp_in );
```

- `temphum5_get_humidity` Functions for read Relative Huminidy data. 
```c
float temphum5_get_humidity ( temphum5_t *ctx );
```

### Application Init

> Initialization device init

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum5_cfg_t cfg;

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

    temphum5_cfg_setup( &cfg );
    TEMPHUM5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum5_init( &temphum5, &cfg );
}
```

### Application Task

> Reads Temperature and Humidity data and this data logs to USBUART every 1 sec.

```c
void application_task ( )
{
    float temperature;
    float humidity;
    
    temphum5_start_measurement( &temphum5 );
    
    temperature = temphum5_get_temperature( &temphum5, TEMPHUM5_TEMP_DATA_IN_CELSIUS );
                                        
    log_printf( &logger, "Temperature: %.2f C \r\n ", temperature );
    
    humidity = temphum5_get_humidity ( &temphum5 );
    log_printf( &logger, "Humidity: %f RH \r\n ", humidity );
    
    log_printf( &logger, "------------------------ \r\n " );
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
