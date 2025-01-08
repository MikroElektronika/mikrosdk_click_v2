
---
# Light Ranger 3 Click

> [LightRanger 3 Click](https://www.mikroe.com/?pid_product=MIKROE-3103) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3103&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This app precisely measure distance without making actual contact.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LightRanger3

### Example Key Functions

- `lightranger3_cfg_setup` Config Object Initialization function. 
```c
void lightranger3_cfg_setup ( lightranger3_cfg_t *cfg );
``` 
 
- `lightranger3_init` Initialization function. 
```c
err_t lightranger3_init ( lightranger3_t *ctx, lightranger3_cfg_t *cfg );
```

- `lightranger3_default_cfg` Click Default Configuration function. 
```c
void lightranger3_default_cfg ( lightranger3_t *ctx );
```

- `lightranger3_set_measurement_mode` This function go to measurement mode. 
```c
uint8_t lightranger3_set_measurement_mode ( lightranger3_t *ctx );
```
 
- `lightranger3_get_distance` This function reads distance. 
```c
uint16_t lightranger3_get_distance ( lightranger3_t *ctx );
```

- `lightranger3_get_confidence_value` This function reads confidence value. 
```c
uint16_t lightranger3_get_confidence_value ( lightranger3_t *ctx );
```

### Application Init

> Initializes driver init and configuration chip.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    lightranger3_cfg_t cfg;
    uint8_t init_status;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    lightranger3_cfg_setup( &cfg );
    LIGHTRANGER3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lightranger3_init( &lightranger3, &cfg );

    init_status = lightranger3_device_init( &lightranger3 );

    if ( init_status == 0 )
    {
        log_printf( &logger, " --- Device init successfully --- \r\n " );
    }
    else
    {
        log_printf( &logger, " ---  Device init error --- \r\n " );
    }
}
```

### Application Task

> Includes measurements, reads distance, and logs distance to USBUART for every 300 ms.
> Distance measurement at distances ranging from 100 mm to 2000 mm. 

```c
void application_task ( void )
{
    uint16_t distance;

    lightranger3_take_single_measurement( &lightranger3 );
    
    distance = lightranger3_get_distance( &lightranger3 );

    log_printf( &logger, "Distance = %u mm \r\n ", distance );

    Delay_ms ( 300 );
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
