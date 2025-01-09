
---
# Temp&Hum 7 Click

> [TempHum 7 Click](https://www.mikroe.com/?pid_product=MIKROE-3272) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3272&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Nov 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application measurement temperature and humidity data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum7

### Example Key Functions

- `temphum7_cfg_setup` Config Object Initialization function. 
```c
void temphum7_cfg_setup ( temphum7_cfg_t *cfg );
``` 
 
- `temphum7_init` Initialization function. 
```c
err_t temphum7_init ( temphum7_t *ctx, temphum7_cfg_t *cfg );
```

- `temphum7_default_cfg` Click Default Configuration function. 
```c
void temphum7_default_cfg ( temphum7_t *ctx );
```

- `temphum7_get_relative_humidity` Relative humidity. 
```c
float temphum7_get_relative_humidity ( temphum7_t *ctx, uint8_t mode_data );
```
 
- `temphum7_get_temperature` Get temerature. 
```c
float temphum7_get_temperature ( temphum7_t *ctx, uint8_t mode_data );
```

- `temphum7_get_firmware_revision` Firmware revision. 
```c
uint8_t temphum7_get_firmware_revision ( temphum7_t *ctx );
```

### Application Init

> Initializes device and logger module and sets default configuration for measurements.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum7_cfg_t cfg;
    
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
    log_init ( &logger, &log_cfg );
    log_info ( &logger, "---- Application Init ----" );

    //  Click initialization.

    temphum7_cfg_setup ( &cfg );
    TEMPHUM7_MAP_MIKROBUS ( cfg, MIKROBUS_1 );
    temphum7_init ( &temphum7, &cfg );

    temphum7_default_cfg( &temphum7 );
} 
```

### Application Task

> Calculates and Logs temperature and relative humidity

```c
void application_task ( void )
{
    
    temperature = temphum7_get_temperature ( &temphum7, TEMPHUM7_HOLD_MASTER_MODE );
    mikrobus_printf ( "-> Temperature: %f C/r/n", temperature );

    relative_humidity = temphum7_get_relative_humidity ( &temphum7, TEMPHUM7_HOLD_MASTER_MODE );
    mikrobus_printf ( "-> Relative humidity: %f %%RH/r/n ", relative_humidity );

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
