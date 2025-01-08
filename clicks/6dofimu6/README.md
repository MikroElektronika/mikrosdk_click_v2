
---
# 6DOF IMU 6 Click

> [6DOF IMU 6 Click](https://www.mikroe.com/?pid_product=MIKROE-4044) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4044&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : sep 2020.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> 6DOF IMU 6 Click features a 6-axis MotionTracking device that combines a 3-axis gyroscope, 
> a 3-axis accelerometer, and a Digital Motion Processor. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.6DofImu6

### Example Key Functions

- `c6dofimu6_cfg_setup` Config Object Initialization function. 
```c
void c6dofimu6_cfg_setup ( c6dofimu6_cfg_t *cfg );
``` 
 
- `c6dofimu6_init` Initialization function. 
```c
err_t c6dofimu6_init ( c6dofimu6_t *ctx, c6dofimu6_cfg_t *cfg );
```

- `c6dofimu6_default_cfg` Click Default Configuration function. 
```c
void c6dofimu6_default_cfg ( c6dofimu6_t *ctx );
```

- `c6dofimu6_default_cfg` This function executes default configuration for 6DOF IMU 6 Click. 
```c
void c6dofimu6_default_cfg ( c6dofimu6_t *ctx );
```
 
- `c6dofimu6_angular_rate` Function is used to calculate angular rate. 
```c
void c6dofimu6_angular_rate ( c6dofimu6_t *ctx, float *x_ang_rte, float *y_ang_rte, float *z_ang_rte );
```

- `c6dofimu6_acceleration_rate` Function is used to calculate acceleration rate. 
```c
void c6dofimu6_acceleration_rate ( c6dofimu6_t *ctx, float *x_accel_rte, float *y_accel_rte, float *z_accel_rte );
```

### Application Init

> Initalizes SPI and I2C drivers, performs safety check, applies default 
> settings and writes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu6_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    c6dofimu6_cfg_setup( &cfg );
    C6DOFIMU6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu6_init( &c6dofimu6, &cfg );

    Delay_ms ( 100 );
    c6dofimu6_generic_read ( &c6dofimu6, C6DOFIMU6_WHO_AM_I, &id_val, 1 );
    if ( id_val == C6DOFIMU6_WHO_AM_I_VAL )
    {
        log_printf( &logger, "-------------------------\r\n" );
        log_printf( &logger, "   6DOF  IMU  6  Click   \r\n" );
        log_printf( &logger, "-------------------------\r\n" );
        c6dofimu6_power ( &c6dofimu6, C6DOFIMU6_POWER_ON );
    }
    else
    {
        log_printf( &logger, "-------------------------\r\n" );
        log_printf( &logger, "     FATAL  ERROR!!!     \r\n" );
        log_printf( &logger, "-------------------------\r\n" );
        for ( ; ; );
    }

    c6dofimu6_default_cfg( &c6dofimu6 );

    log_printf( &logger, "    ---Initialised---    \r\n" );
    log_printf( &logger, "-------------------------\r\n" );

    Delay_ms ( 100 );
}
```

### Application Task

> Demonstrates the use of 6DOF IMU 6 Click board by reading angular rate, acceleration rate 
> and displaying data to USB UART.

```c
void application_task ( void )
{
    c6dofimu6_angular_rate( &c6dofimu6, &x_gyro, &y_gyro, &z_gyro );

    log_printf( &logger, "Gyro \r\n" );

    log_printf( &logger, "X-axis: %.2f\r\n", x_gyro );
    log_printf( &logger, "Y-axis: %.2f\r\n", y_gyro );
    log_printf( &logger, "Z-axis: %.2f\r\n", z_gyro );
    log_printf( &logger, "---------------------\r\n" );

    c6dofimu6_acceleration_rate( &c6dofimu6, &x_accel, &y_accel, &z_accel );

    log_printf( &logger, "Accel \r\n" );

    log_printf( &logger, "X-axis: %.2f\r\n", x_accel );
    log_printf( &logger, "Y-axis: %.2f\r\n", y_accel );
    log_printf( &logger, "Z-axis: %.2f\r\n", z_accel );
    log_printf( &logger, "---------------------\r\n\r\n" );
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
