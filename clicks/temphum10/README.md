
---
# Temp&Hum 10 Click

> [TempHum 10 Click](https://www.mikroe.com/?pid_product=MIKROE-3342) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3342&image=1" height=300px>
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
- Click.TempHum10

### Example Key Functions

- `temphum10_cfg_setup` Config Object Initialization function. 
```c
void temphum10_cfg_setup ( temphum10_cfg_t *cfg );
``` 
 
- `temphum10_init` Initialization function. 
```c
err_t temphum10_init ( temphum10_t *ctx, temphum10_cfg_t *cfg );
```

- `temphum10_get_temperature` Functions for read Temperature data. 
```c
float temphum10_get_temperature ( temphum10_t *ctx );
```
 
- `temphum10_set_device_mode` Functions for sets Device mode. 
```c
void temphum10_set_device_mode ( temphum10_t *ctx, uint8_t mode );
```

- `temphum10_repeat_measurement` Functions for repeat measurement. 
```c
void temphum10_repeat_measurement ( temphum10_t *ctx, uint8_t average );
```

### Application Init

> Initialization driver init and sets device mode

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum10_cfg_t cfg;
    uint8_t tmp;

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

    temphum10_cfg_setup( &cfg );
    TEMPHUM10_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum10_init( &temphum10, &cfg );

    log_info( &logger, "---- Device config ----" );
    
    temphum10_set_device_mode( &temphum10, TEMPHUM10_MODE_STANDBY );
    Delay_ms ( 100 );
    
    tmp = TEMPHUM10_RST_NORMAL_OPERATION;
    temphum10_generic_write( &temphum10, TEMPHUM10_REG_DEVICE_RESET, &tmp, 1 );
    Delay_ms ( 100 );
    log_info( &logger, "---- Device calibration ----" );
    tmp = TEMPHUM10_AM_TIMES_AVERAGE_MODE_8 | TEMPHUM10_AM_TEMP_AVERAGE_MODE_TIMES_16;
    temphum10_repeat_measurement( &temphum10, tmp );
    temphum10_get_temperature( &temphum10 );
    temphum10_get_humidity( &temphum10 );
    Delay_ms ( 100 );
    temphum10_repeat_measurement( &temphum10, tmp );
    temphum10_get_temperature( &temphum10 );
    temphum10_get_humidity( &temphum10 );
    log_info( &logger, "---- Application Task ----" );
}
```

### Application Task

> Reads Temperature and Humidity data and logs this data to USBUART every 1 sec.

```c
void application_task ( )
{
    float temperature = 0;
    float humidity = 0;
    uint8_t tmp;
    
    tmp = TEMPHUM10_AM_TIMES_AVERAGE_MODE_8 | TEMPHUM10_AM_TEMP_AVERAGE_MODE_TIMES_16;
    temphum10_repeat_measurement( &temphum10, tmp );
    temperature = temphum10_get_temperature( &temphum10 );
    humidity = temphum10_get_humidity( &temphum10 );
    
    log_printf( &logger, " Temperature : %.2f \r\n", temperature );
    log_printf( &logger, " Humidity :  %.2f \r\n", humidity );
    log_printf( &logger, "---------------------\r\n" );

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
