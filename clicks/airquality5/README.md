
---
# Air quality 5 Click

> [Air quality 5 Click](https://www.mikroe.com/?pid_product=MIKROE-3056) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3056&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application can detect gas pollution for a number of different gases.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Airquality5

### Example Key Functions

- `airquality5_cfg_setup` Config Object Initialization function. 
```c
void airquality5_cfg_setup ( airquality5_cfg_t *cfg );
``` 
 
- `airquality5_init` Initialization function. 
```c
err_t airquality5_init ( airquality5_t *ctx, airquality5_cfg_t *cfg );
```

- `airquality5_default_cfg` Click Default Configuration function. 
```c
void airquality5_default_cfg ( airquality5_t *ctx );
```

- `airq5_write_data` Functions for write data in register. 
```c
void airq5_write_data ( airquality5_t *ctx, uint8_t reg, uint16_t data_b );
```
 
- `airq5_read_data` Functions for read data from register. 
```c
uint16_t airq5_read_data ( airquality5_t *ctx, uint8_t reg );
```

- `airq5_set_configuration` Functions for configuration. 
```c
void airq5_set_configuration ( airquality5_t *ctx, uint16_t config );
```

### Application Init

> Initializes device and configuration chip. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    airquality5_cfg_t cfg;
    airquality5.data_config = 0x8583;

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

    airquality5_cfg_setup( &cfg );
    AIRQUALITY5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    airquality5_init( &airquality5, &cfg );
}
```

### Application Task

> Reads the values of CO, NH3 and NO2 sensor and logs data on USBUART every 500ms. 

```c
void application_task ( void )
{
    uint16_t NO2_sensor_data;
    uint16_t NH3_sensor_data;
    uint16_t CO_sensor_data;
 
    CO_sensor_data = airq5_read_sensor_data( &airquality5, AIRQ5_DATA_CHANNEL_CO );
      
    NO2_sensor_data = airq5_read_sensor_data( &airquality5, AIRQ5_DATA_CHANNEL_NO2 );
    log_printf( &logger, " NO2 data: %d\r\n", NO2_sensor_data );
      
    NH3_sensor_data = airq5_read_sensor_data( &airquality5, AIRQ5_DATA_CHANNEL_NH3 );
    log_printf( &logger, " NH3 data: %d\r\n", NH3_sensor_data );
     
    CO_sensor_data = airq5_read_sensor_data( &airquality5, AIRQ5_DATA_CHANNEL_CO );
    log_printf( &logger," CO data: %d\r\n", CO_sensor_data );
     
    log_printf( &logger, " -------- ");
    Delay_ms ( 200 );
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
