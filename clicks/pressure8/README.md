
---
# Pressure 8 Click

> [Pressure 8 Click](https://www.mikroe.com/?pid_product=MIKROE-3338) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3338&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : nov 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application reads pressure data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure8

### Example Key Functions

- `pressure8_cfg_setup` Config Object Initialization function.
```c
void pressure8_cfg_setup ( pressure8_cfg_t *cfg ); 
```

- `pressure8_init` Initialization function.
```c
err_t pressure8_init ( pressure8_t *ctx, pressure8_cfg_t *cfg );
```

- `pressure8_get_pressure` Functions for get Pressure data
```c
float pressure8_get_pressure ( pressure8_t *ctx, uint8_t press_format );
```

- `pressure8_get_device_status` Functions for get device status
```c
uint8_t pressure8_get_device_status ( pressure8_t *ctx );
```

- `pressure8_set_psi_range` Functions for set PSI range
```c
void pressure8_set_psi_range ( pressure8_t *ctx, float psi_min, float psi_max );
```

### Application Init

> Initialization device and logger module, reset device and set PSI range.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure8_cfg_t cfg;

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
    log_info( &logger, " Application Init " );

    //  Click initialization.
    pressure8_cfg_setup( &cfg );
    PRESSURE8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure8_init( &pressure8, &cfg );

    pressure8_device_reset( &pressure8 );
    pressure8_set_psi_range( &pressure8, 0, 25 );
    Delay_ms ( 1000 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads pressure data in mBar and logs it on the USB UART once per second.

```c
void application_task ( void )
{
    float pressure = 0;
    
    pressure = pressure8_get_pressure( &pressure8, PRESSURE8_DATA_IN_MBAR );
    log_printf( &logger, " Pressure: %.1f mBar\r\n", pressure );

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
