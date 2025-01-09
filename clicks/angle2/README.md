
---
# Angle 2 Click

> [Angle 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2338) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2338&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This example showcases how to configure and use the Angle 2 Click. This Click senses
  the magnetic field along the horizontal plane using an array of Hal effect sensors.
  The module uses advanced Spinaxis technology based on a direct angle sampling app-
  roach in order to provide reliable data quickly. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Angle2

### Example Key Functions

- `angle2_cfg_setup` Config Object Initialization function. 
```c
void angle2_cfg_setup ( angle2_cfg_t *cfg );
``` 
 
- `angle2_init` Initialization function. 
```c
err_t angle2_init ( angle2_t *ctx, angle2_cfg_t *cfg );
```

- `angle2_default_cfg` Click Default Configuration function. 
```c
void angle2_default_cfg ( angle2_t *ctx );
```

- `angle2_get_angle` This function reads angle data from the Click module. 
```c
double angle2_get_angle ( angle2_t *ctx );
```
 
- `angle2_get_angle_with_time_index` This function reads angle and time index data from the Click module. 
```c
double angle2_get_angle_with_time_index ( angle2_t *ctx, uint8_t *time_index );
```

- `angle2_set_zero_scale` This function sets the zero scale value. 
```c
void angle2_set_zero_scale ( angle2_t *ctx, double zero_deg );
```

### Application Init

> This function initializes and configures the Click and logger modules. Additional con-
  figuring is done in the default_cfg(...) function. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    angle2_cfg_t cfg;

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
    Delay_ms ( 100 );

    //  Click initialization.

    angle2_cfg_setup( &cfg );
    ANGLE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    angle2_init( &angle2, &cfg );

    Delay_ms ( 300 );
    angle2_default_cfg( &angle2 );
    Delay_ms ( 200 );

    log_printf( &logger, " * Angle 2 initialized * \r\n" );
}
```

### Application Task

> This function reads angle data from the Click module and displays that data using the
  UART console every 200 miliseconds.

```c
void application_task ( void )
{
    double angle;

    angle = angle2_get_angle( &angle2 );

    log_printf( &logger, " Angle: %.2f deg\r\n", angle );

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
