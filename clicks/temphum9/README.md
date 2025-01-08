
---
# Temp-Hum 9 Click

> [TempHum 9 Click](https://www.mikroe.com/?pid_product=MIKROE-3331) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3331&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of TempHum 9 Click board by reading and displaying the temperature and humidity measurement results.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum9

### Example Key Functions

- `temphum9_cfg_setup` Config Object Initialization function.
```c
void temphum9_cfg_setup ( temphum9_cfg_t *cfg ); 
```

- `temphum9_init` Initialization function.
```c
err_t temphum9_init ( temphum9_t *ctx, temphum9_cfg_t *cfg );
```

- `temphum9_get_temperature` Calculating temperature
```c
float temphum9_get_temperature ( temphum9_t *ctx, uint8_t data_mode );
```
 
- `temphum9_get_humidity` Calculating relative humidity
```c
float temphum9_get_humidity ( temphum9_t *ctx, uint8_t data_mode );
```

- `temhum9_get_data` Calculating temperature and relative humidity
```c
void temhum9_get_data ( temphum9_t *ctx, uint8_t data_mode, float *temp, float *hum );
```

### Application Init

> Initializes I2C driver and sends SLEEP and WAKEUP commands.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum9_cfg_t cfg;

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

    //  Click initialization.
    temphum9_cfg_setup( &cfg );
    TEMPHUM9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum9_init( &temphum9, &cfg );
    Delay_ms ( 100 );

    temphum9_send_command( &temphum9, TEMPHUM9_SLEEP );
    Delay_ms ( 500 );
    temphum9_send_command( &temphum9, TEMPHUM9_WAKEUP );
    Delay_ms ( 500 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Performs simultaneous temperature and relative humidity measurements and logs both values on the USB UART once per second.

```c
void application_task( )
{
    float temperature = 0;
    float humidity = 0;
    
    temhum9_get_data ( &temphum9, TEMPHUM9_NORMAL_MODE, &temperature, &humidity );
    
    log_printf( &logger, " Temperature: %.2f degC\r\n", temperature );

    log_printf( &logger, " Relative humidity: %.2f %%\r\n", humidity );
    
    log_printf( &logger, "-----------------------------\r\n" );
    
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
