
---
# Ambient 6 Click

> [Ambient 6 Click](https://www.mikroe.com/?pid_product=MIKROE-3444) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3444&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application measurement ambient light

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient6

### Example Key Functions

- `ambient6_cfg_setup` Config Object Initialization function. 
```c
void ambient6_cfg_setup ( ambient6_cfg_t *cfg );
``` 
 
- `ambient6_init` Initialization function. 
```c
err_t ambient6_init ( ambient6_t *ctx, ambient6_cfg_t *cfg );
```

- `ambient6_default_cfg` Click Default Configuration function. 
```c
void ambient6_default_cfg ( ambient6 *ctx );
```

- `ambient6_get_ambient_data` Functions for read 16bit Ambient Data (ALS). 
```c
uint16_t ambient6_get_ambient_data( ambient6_t *ctx );
```
 
- `ambient6_configuration` Functions for configuration device for measurement. 
```c
void ambient6_configuration (  ambient6_t *ctx, uint16_t config_data );
```

- `ambient6_get_ambient_light` Functions for get Ambient Light Data. 
```c
float ambient6_get_ambient_light( ambient6_t *ctx );
```

### Application Init

> Initialization driver init and default configuration device for measurement

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient6_cfg_t cfg;

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

    ambient6_cfg_setup( &cfg );
    AMBIENT6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient6_init( &ambient6, &cfg );
    ambient6_default_cfg( &ambient6 );    
}
```

### Application Task

> Read Ambient Light in lux[lx] and this data logs to USBUART every 1sec.

```c
void application_task ( )
{
    float ambient_light;
    
    ambient_light = ambient6_get_ambient_light( &ambient6 );
    log_printf( &logger, "Ambient Light: %f lx \r\n", ambient_light );
    Delay_1sec( );
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
