
---
# Magneto 5 Click

> [Magneto 5 Click](https://www.mikroe.com/?pid_product=MIKROE-3050) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3050&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application is is a very accurate and reliable magnetic         sensor device. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Magneto5

### Example Key Functions

- `magneto5_cfg_setup` Config Object Initialization function. 
```c
void magneto5_cfg_setup ( magneto5_cfg_t *cfg );
``` 
 
- `magneto5_init` Initialization function. 
```c
err_t magneto5_init ( magneto5_t *ctx, magneto5_cfg_t *cfg );
```

- `magneto5_default_cfg` Click Default Configuration function. 
```c
void magneto5_default_cfg ( magneto5_t *ctx );
```

- `magneto5_get_axis_data` Functions reads axis data. 
```c
void magneto5_get_axis_data ( magneto5_t *ctx, int16_t *axis_buffer, uint8_t max_resolution );
```
 
- `magneto5_get_axis_value` Functions reads axis data value. 
```c
float magneto5_get_axis_value ( magneto5_t *ctx, uint8_t axis, uint8_t max_resolution );
```

- `magneto5_config_register_0` Functions sets configuration register 0. 
```c
void magneto5_config_register_0 ( magneto5_t *ctx, uint8_t config_data );
```

### Application Init

> Initializes driver init and set measurement mode and channel. 

```c
void application_init ( void )
{
 log_cfg_t log_cfg;
    magneto5_cfg_t cfg;

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

    magneto5_cfg_setup( &cfg );
    MAGNETO5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    magneto5_init( &magneto5, &cfg );
}
```

### Application Task

> Reads X / Y / Z data axis and logs to USBUART every 1 sec. 

```c
void application_task ( void )
{
//  Task implementation.

    x_axis = magneto5_get_axis_value( &magneto5, MAGNETO5_AXIS_X, MAGNETO5_CH3_12bits_1ms );
    log_printf ( &logger, "-- X axis : %d \r\n ", x_axis );

    y_axis = magneto5_get_axis_value( &magneto5, MAGNETO5_AXIS_Y, MAGNETO5_CH3_12bits_1ms );
    log_printf ( &logger, "-- Y axis : %d \r\n ",  y_axis );

    z_axis = magneto5_get_axis_value( &magneto5, MAGNETO5_AXIS_Z, MAGNETO5_CH3_12bits_1ms );
    log_printf ( &logger, "-- Z axis : %d \r\n ", z_axis );

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
