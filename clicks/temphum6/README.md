
---
# Temp Hum 6 Click

> [TempHum 6 Click](https://www.mikroe.com/?pid_product=MIKROE-3270) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3270&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application emasures temperature and humidity.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum6

### Example Key Functions

- `temphum6_cfg_setup` Config Object Initialization function. 
```c
void temphum6_cfg_setup ( temphum6_cfg_t *cfg );
``` 
 
- `temphum6_init` Initialization function. 
```c
err_t temphum6_init ( temphum6_t *ctx, temphum6_cfg_t *cfg );
```

- `temphum6_default_cfg` Click Default Configuration function. 
```c
void temphum6_default_cfg ( temphum6_t *ctx );
```

- `temphum6_read_temperature` This function returns read Temperature data. 
```c
float temphum6_read_temperature ( temphum6_t *ctx, uint8_t temp_in );
```
 
- `temphum6_read_relative_huminidy` This function returns read relative Humidity data. 
```c
float temphum6_read_relative_huminidy ( temphum6_t *ctx );
```

- `temphum6_get_part_id` This function returns the device part id. 
```c
uint16_t temphum6_get_part_id ( temphum6_t *ctx );
```

### Application Init

> Initialization driver init and reset device and read Part ID

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum6_cfg_t cfg;
    uint16_t part_id;

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

    temphum6_cfg_setup( &cfg );
    TEMPHUM6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum6_init( &temphum6, &cfg );

    temphum6_reset( &temphum6 );
    
    part_id = temphum6_get_part_id( &temphum6 );
    if ( part_id == TEMPHUM6_PART_ID )
    {
        log_printf( &logger, "Device OK - read ID is OK" );
    }
    else
    {
        log_printf( &logger, "Device ERROR - read ID is NOT OK" );
    }
}
```

### Application Task

> Reads Temperature and Huminidy data and logs this data to USBUART every 1sec.

```c
void application_task ( void )
{
    //  Task implementation.

    float temp;
    float hum;

    temp = temphum6_read_temperature( &temphum6, TEMPHUM6_TEMP_IN_CELSIUS );
    log_printf( &logger, "Temperature is %f C\r\n");
    
    hum = temphum6_read_relative_huminidy( &temphum6 );
    log_printf( &logger, "Huminidy is %f %%RH\r\n");
    
    log_printf( &logger, "------------------\r\n");
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
