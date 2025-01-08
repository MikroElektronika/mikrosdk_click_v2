
---
# Compass Click

> [Compass Click](https://www.mikroe.com/?pid_product=MIKROE-1386) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1386&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application measures magnetic and accelerometer axes data and shows them over USBUART

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Compass

### Example Key Functions

- `compass_cfg_setup` Config Object Initialization function. 
```c
void compass_cfg_setup ( compass_cfg_t *cfg );
``` 
 
- `compass_init` Initialization function. 
```c
err_t compass_init ( compass_t *ctx, compass_cfg_t *cfg );
```

- `compass_default_cfg` Click Default Configuration function. 
```c
void compass_default_cfg ( compass_t *ctx );
```

- `compass_read_magnet_axis` This function reads data for megnetic axes. 
```c
void compass_read_magnet_axis ( compass_t *ctx, int16_t *x_axis, int16_t *y_axis, int16_t *z_axis );
```
 
- `compass_read_accel_axis` This function reads data for accelerometer axes. 
```c
void compass_read_accel_axis ( compass_t *ctx, int16_t *x_axis, int16_t *y_axis, int16_t *z_axis );
```

- `compass_magnet_generic_write` This function writes magnet data to the desired register. 
```c
void compass_magnet_generic_write ( compass_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```

### Application Init

> Initialization driver init and init chip

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    compass_cfg_t cfg;

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

    compass_cfg_setup( &cfg );
    COMPASS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    compass_init( &compass, &cfg );
    compass_default_config( &compass );
}
```

### Application Task

> Read magnet axis data and accel axis data and logs data on USBUART every 1 sec. 

```c
void application_task ( void )
{
    int16_t accel_axis[ 3 ];
    int16_t magnet_axis[ 3 ];
    
    compass_read_magnet_axis( &compass, &magnet_axis[ 0 ], &magnet_axis[ 1 ], &magnet_axis[ 2 ] );
    log_printf( &logger, "Magnet axis -- X: %d Y: %d  Z: %d \r\n", magnet_axis[ 0 ], magnet_axis[ 1 ], magnet_axis[ 2 ] );
  
    compass_read_accel_axis ( &compass, &accel_axis[ 0 ], &accel_axis[ 1 ], &accel_axis[ 2 ] );
    log_printf( &logger, "Magnet axis -- X: %d Y: %d  Z: %d \r\n", accel_axis[ 0 ], accel_axis[ 1 ], accel_axis[ 2 ] );
   
    log_printf( &logger, " \r\n");
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
