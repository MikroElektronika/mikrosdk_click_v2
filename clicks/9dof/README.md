
---
# 9 DOF Click

> [9DOF Click](https://www.mikroe.com/?pid_product=MIKROE-1996) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1996&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> 
> This application shows accelerometer, gyroscope
> and magnetometer axes values.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.9Dof

### Example Key Functions

- `c9dof_cfg_setup` Config Object Initialization function. 
```c
void c9dof_cfg_setup ( c9dof_cfg_t *cfg );
``` 
 
- `c9dof_init` Initialization function. 
```c
err_t c9dof_init ( c9dof_t *ctx, c9dof_cfg_t *cfg );
```

- `c9dof_default_cfg` Click Default Configuration function. 
```c
void c9dof_default_cfg ( c9dof_t *ctx );
```

- `c9dof_read_accel` Generic accelerometer read function. 
```c
void c9dof_read_accel ( c9dof_t *ctx, c9dof_accel_data_t *accel_data );
```
 
- `c9dof_read_gyro` Get gyroscope data function. 
```c
void c9dof_read_gyro ( c9dof_t *ctx, c9dof_gyro_data_t *gyro_data );
```

- `c9dof_read_mag` Get magnetometer data function. 
```c
void c9dof_read_mag ( c9dof_t *ctx, c9dof_mag_data_t *mag_data );
```

### Application Init

>
> Initializes GPIO pins, I2C, LOG modules and
> sets default configuration.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c9dof_cfg_t cfg;

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
    log_printf( &logger, "----       Application Init       ----\r\n" );
    log_printf( &logger, "--------------------------------------\r\n" );

    //  Click initialization.

    c9dof_cfg_setup( &cfg );
    C9DOF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c9dof_init( &c9dof, &cfg );
    
    c9dof_default_cfg ( &c9dof );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "              9DOF Click\r\n" );
    log_printf( &logger, "--------------------------------------\r\n" );
}
```

### Application Task

>
> Gets accelerometer, gyroscope
> and magnetometer axes data and LOGs those values.
> 

```c
void application_task ( void )
{
    c9dof_read_accel( &c9dof, &accel_data );
    Delay_ms ( 10 );
    
    c9dof_read_gyro( &c9dof, &gyro_data );
    Delay_ms ( 10 );
    
    c9dof_read_mag( &c9dof, &mag_data );
    Delay_ms ( 10 );
    
    log_printf( &logger, "   Accel    |    Gyro    |    Mag\r\n" );
    log_printf( &logger, "--------------------------------------\r\n" );
    log_printf( &logger, " X = %6d | X = %6d | X = %6d\r\n", accel_data.x, gyro_data.x, mag_data.x );
    log_printf( &logger, " Y = %6d | Y = %6d | Y = %6d\r\n", accel_data.y, gyro_data.y, mag_data.y );
    log_printf( &logger, " Z = %6d | Z = %6d | Z = %6d\r\n", accel_data.z, gyro_data.z, mag_data.z );
    log_printf( &logger, "--------------------------------------\r\n" );
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
