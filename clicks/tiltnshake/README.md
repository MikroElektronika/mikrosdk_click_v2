
---
# TILT-n-SHAKE Click

> [TILT-n-SHAKE Click](https://www.mikroe.com/?pid_product=MIKROE-1853) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1853&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application is multifunctional 3-axis digital accelerometer that can also be configured as a 45-degree Tilt sensor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TiltNshake

### Example Key Functions

- `tiltnshake_cfg_setup` Config Object Initialization function.
```c
void tiltnshake_cfg_setup ( tiltnshake_cfg_t *cfg ); 
```

- `tiltnshake_init` Initialization function.
```c
err_t tiltnshake_init ( tiltnshake_t *ctx, tiltnshake_cfg_t *cfg );
```

- `tiltnshake_read_status_and_axis` Function for read status and axis
```c
void tiltnshake_read_status_and_axis ( tiltnshake_t *ctx, uint8_t *status, float *out_x, float *out_y, float *out_z )
```

- `tiltnshake_enable` Function for enabling chip
```c
void tiltnshake_enable ( tiltnshake_t *ctx );
```

- `tiltnshake_disable` Function for disabling chip
```c
void tiltnshake_disable ( tiltnshake_t *ctx );
```

### Application Init

> Initializes device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    tiltnshake_cfg_t cfg;

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

    // Click initialization.
    tiltnshake_cfg_setup( &cfg );
    TILTNSHAKE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    tiltnshake_init( &tiltnshake, &cfg );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads 3-axis accelerometer measurement and logs results on the USB UART.

```c
void application_task ( )
{
    uint8_t status = 0;
    float out_x = 0;
    float out_y = 0;
    float out_z = 0;

    tiltnshake_enable( &tiltnshake );
    tiltnshake_read_status_and_axis( &tiltnshake, &status, &out_x, &out_y, &out_z );
    tiltnshake_disable( &tiltnshake );

    if ( TILTNSHAKE_DATA_READY == status )
    {
        log_printf( &logger, " X: %.2f\r\n", out_x );
        log_printf( &logger, " Y: %.2f\r\n", out_y );
        log_printf( &logger, " Z: %.2f\r\n", out_z );
        log_printf( &logger, "----------\r\n");
        Delay_ms ( 500 );
    }
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
