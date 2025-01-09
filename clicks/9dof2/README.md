
---
# 9DOF 2 Click

> [9DOF 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4128) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4128&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of 9DOF 2 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.9dof2

### Example Key Functions

- `c9dof2_cfg_setup` Config Object Initialization function. 
```c
void c9dof2_cfg_setup ( c9dof2_cfg_t *cfg );
``` 
 
- `c9dof2_init` Initialization function. 
```c
err_t c9dof2_init ( c9dof2_t *ctx, c9dof2_cfg_t *cfg );
```

- `c9dof2_default_cfg` Click Default Configuration function. 
```c
void c9dof2_default_cfg ( c9dof2_t *ctx );
```

- `c9dof2_power` Turns the device on or off. 
```c
void c9dof2_power ( c9dof2_t *ctx, uint8_t on_off );
```
 
- `c9dof2_read_gyroscope` Function is used to read gyroscope data. 
```c
void c9dof2_read_gyroscope ( c9dof2_t *ctx, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z );
```

- `c9dof2_read_accelerometer` Function is used to read accelerometer data. 
```c
void c9dof2_read_accelerometer ( c9dof2_t *ctx, int16_t *accel_x, int16_t *accel_y, int16_t *accel_z );
```

### Application Init

> Initalizes SPI and device drivers, performs safety check, applies default configuration and writes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c9dof2_cfg_t cfg;

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

    c9dof2_cfg_setup( &cfg );
    C9DOF2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c9dof2_init( &c9dof2, &cfg );

    c9dof2_dev_rst( &c9dof2 );
    Delay_ms ( 1000 );

    id_val = c9dof2_read_byte ( &c9dof2, C9DOF2_WHO_AM_I_ICM20948 );
     
    if ( id_val == C9DOF2_WHO_AM_I_ICM20948_VAL )
    {
        log_printf( &logger, "--------------------\r\n" );
        log_printf( &logger, "   9DOF  2  Click   \r\n" );
        log_printf( &logger, "--------------------\r\n" );
        c9dof2_power ( &c9dof2, C9DOF2_POWER_ON );
    }
    else
    {
        log_printf(  &logger, "--------------------\r\n" );
        log_printf(  &logger, "   FATAL ERROR!!!   \r\n" );
        log_printf(  &logger, "--------------------\r\n" );
        for ( ; ; );
    }
    
    c9dof2_def_settings( &c9dof2 );

    log_printf(  &logger, "--- Initialised ---\r\n" );
    log_printf(  &logger, "--------------------\r\n" );

    Delay_ms ( 1000 );
}
```

### Application Task

> Reads the angular and acceleration rates and displays the values of X, Y, and Z axis on the USB UART each second.

```c
void application_task ( void )
{
    //  Task implementation.
    
    c9dof2_angular_rate( &c9dof2, &x_gyro, &y_gyro, &z_gyro );

    log_printf( &logger, "Angular rate: \r\n" );

    log_printf( &logger, "X-axis: %.2f \r\n", x_gyro );

    log_printf( &logger, "Y-axis: %.2f \r\n", y_gyro );

    log_printf( &logger, "Z-axis: %.2f \r\n", z_gyro );

    log_printf( &logger, "---------------------\r\n" );

    c9dof2_acceleration_rate( &c9dof2, &x_accel, &y_accel, &z_accel );

    log_printf( &logger, "Acceleration rate: \r\n" );

    log_printf( &logger, "X-axis: %.2f \r\n", x_accel );

    log_printf( &logger, "Y-axis: %.2f \r\n", y_accel );

    log_printf( &logger, "Z-axis: %.2f \r\n", z_accel );

    log_printf( &logger, "---------------------\r\n" );

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
