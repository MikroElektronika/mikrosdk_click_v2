
---
# NO 2 Click

> [NO2 Click](https://www.mikroe.com/?pid_product=MIKROE-3098) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3098&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This application measures NO2.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.No2

### Example Key Functions

- `no2_cfg_setup` Config Object Initialization function. 
```c
void no2_cfg_setup ( no2_cfg_t *cfg );
``` 
 
- `no2_init` Initialization function. 
```c
err_t no2_init ( no2_t *ctx, no2_cfg_t *cfg );
```

- `no2_default_cfg` Click Default Configuration function. 
```c
void no2_default_cfg ( no2_t *ctx );
```

- `no2_enable` Device Enable function. 
```c
void no2_enable ( no2_t *ctx, uint8_t state );
```
 
- `no2_read_adc` Function for read ADC sensor data. 
```c
uint16_t no2_read_adc ( no2_t *ctx );
```

- `no2_get_no_2_ppm` Get NO2 Data function. 
```c
float no2_get_no_2_ppm ( no2_t *ctx );
```

### Application Init

> Initializes I2C driver and device configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    no2_cfg_t cfg;

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

    no2_cfg_setup( &cfg );
    NO2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    no2_init( &no2, &cfg );

    no2_default_cfg( &no2 );

    log_printf( &logger, "NO2 is initialized \r\n" );
    Delay_ms ( 300 );
}
```

### Application Task

> Gets NO2 (Nitrogen dioxide) data as ppm value and logs to USBUART every 500ms.

```c
void application_task ( void )
{
    float no2_value;

    no2_value = no2_get_no_2_ppm( &no2 );
    log_printf( &logger, "NO2 value : %.2f ppm \r\n", no2_value );
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
