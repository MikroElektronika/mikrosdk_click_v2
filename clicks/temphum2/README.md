
---
# Temp&Hum 2 Click

> [TempHum 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3085) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3085&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This application measures temperature and humidity. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum2

### Example Key Functions

- `temphum2_cfg_setup` Config Object Initialization function. 
```c
void temphum2_cfg_setup ( temphum2_cfg_t *cfg );
``` 
 
- `temphum2_init` Initialization function. 
```c
err_t temphum2_init ( temphum2_t *ctx, temphum2_cfg_t *cfg );
```

- `temphum2_default_cfg` Click Default Configuration function. 
```c
void temphum2_default_cfg ( temphum2_t *ctx );
```

- `temhum2_get_eletronic_id` This function for reads Eletronic ID. 
```c
void temhum2_get_eletronic_id ( temphum2_t *ctx, uint8_t *electronic_id );
```
 
- `temphum2_set_mode` Functions for set measurement mode. 
```c
void temphum2_set_mode ( uint8_t select_mode, uint8_t speed_mode );
```

- `temphum2_get_measurement` Functions for mesurement. 
```c
void temphum2_get_measurement ( temphum2_t *ctx, float *data_buffer );
```

### Application Init

> Initializes driver init, set work mode and Heater

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum2_cfg_t cfg;

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

    temphum2_cfg_setup( &cfg );
    TEMPHUM2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum2_init( &temphum2, &cfg );

    temphum2_default_cfg( &temphum2 );
}
```

### Application Task

> Reads temperature and humidity and logs values on usbuart for every 500ms. 

```c
void application_task ( void )
{
    float data_buffer[ 2 ];
    
    temphum2_get_measurement( &temphum2, &data_buffer[ 0 ] );
    
    log_printf( &logger, " --- Temperature : %.2f C \r\n ", data_buffer[ 0 ] );
    log_printf( &logger, " --- Humidity : %.2f RH \r\n ", data_buffer[ 1 ] );
    
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
