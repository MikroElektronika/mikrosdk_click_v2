
---
# Compass 2 Click

> [Compass 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2264) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2264&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> The example prepares the device for a new measurement and reads and displays data from all three axes.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Compass2

### Example Key Functions

- `compass2_cfg_setup` Config Object Initialization function. 
```c
void compass2_cfg_setup ( compass2_cfg_t *cfg );
``` 
 
- `compass2_init` Initialization function. 
```c
err_t compass2_init ( compass2_t *ctx, compass2_cfg_t *cfg );
```

- `compass2_default_cfg` Click Default Configuration function. 
```c
void compass2_default_cfg ( compass2_t *ctx );
```

- `compass2_get_axis_data` This function gets the data from one specified axis. 
```c
int16_t compass2_get_axis_data ( compass2_t *ctx, uint8_t axis );
```
 
- `compass2_new_measurement` This function prepares the device for a new measurement. 
```c
void compass2_new_measurement ( compass2_t *ctx );
```

- `compass2_reset` This function does a hardware reset of the device. 
```c
void compass2_reset ( compass2_t *ctx );
``` 

### Application Init

> Initializes and configures the Click and logger modules.

```c
void application_init ( )
{
    log_cfg_t log_cfg;
    compass2_cfg_t cfg;

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

    compass2_cfg_setup( &cfg );
    COMPASS2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    compass2_init( &compass2, &cfg );
    compass2_default_cfg( &compass2 );
}
```

### Application Task

> Reads and displays data from all three axes every two seconds.

```c
void application_task ( )
{
    int16_t x_axis;
    int16_t y_axis;
    int16_t z_axis;
    
    compass2_new_measurement( &compass2 );
    
    log_printf( &logger, " --- Axis ---\r\n" );

    x_axis = compass2_get_axis_data( &compass2, COMPASS2_X_AXIS );
    y_axis = compass2_get_axis_data( &compass2, COMPASS2_Y_AXIS );
    z_axis = compass2_get_axis_data( &compass2, COMPASS2_Z_AXIS );
    
    log_printf( &logger, "X: %d\r\n", x_axis );
    log_printf( &logger, "Y: %d\r\n", y_axis );
    log_printf( &logger, "Z: %d\r\n", z_axis );

    log_printf( &logger, "----------------\r\n" );
    
    Delay_ms ( 1000 );
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
