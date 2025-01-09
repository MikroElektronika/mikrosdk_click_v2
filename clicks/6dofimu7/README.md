
---
# 6DOF IMU 7 Click

> [6DOF IMU 7 Click](https://www.mikroe.com/?pid_product=MIKROE-3776) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3776&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This example showcases how to initialize and configure the logger and Click modules and read
  and display temperature measurements and axis data from the gyroscope and accelerometer. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.6DofImu7

### Example Key Functions

- `c6dofimu7_cfg_setup` Config Object Initialization function. 
```c
void c6dofimu7_cfg_setup ( c6dofimu7_cfg_t *cfg );
``` 
 
- `c6dofimu7_init` Initialization function. 
```c
err_t c6dofimu7_init ( c6dofimu7_t *ctx, c6dofimu7_cfg_t *cfg );
```

- `c6dofimu7_default_cfg` Click Default Configuration function. 
```c
void c6dofimu7_default_cfg ( c6dofimu7_t *ctx );
```

- `c6dofimu7_get_gyro_data` This function reads gyroscope axis data and configures the gyro axis struct. 
```c
void c6dofimu7_get_gyro_data ( c6dofimu7_t *ctx, c6dofimu7_axis_t *gyro, float sensitivity );
```
 
- `c6dofimu7_get_accel_data` This function reads accelerometer axis data and configures the accel axis struct. 
```c
void c6dofimu7_get_accel_data ( c6dofimu7_t *ctx, c6dofimu7_axis_t *accel, float sensitivity );
```

- `c6dofimu7_get_temp_data` This function reads and returns temperature data. 
```c
float c6dofimu7_get_temp_data ( c6dofimu7_t *ctx, float temp_sensitivity, float temp_offset );
```

### Application Init

> This function initializes and configures the logger and Click modules. 

```c
void application_init ( )
{
    log_cfg_t log_cfg;
    c6dofimu7_cfg_t cfg;

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

    c6dofimu7_cfg_setup( &cfg );
    C6DOFIMU7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu7_init( &c6dofimu7, &cfg );
    c6dofimu7_default_cfg( &c6dofimu7 );
}
```

### Application Task

> This function reads and displays accelerometer, gyroscope and temperature data every second. 

```c
void application_task ( )
{
    float temperature;

    c6dofimu7_get_gyro_data( &c6dofimu7, &gyro, C6DOFIMU7_GYRO_SENSITIVITY );

    log_printf( &logger, " * Gyro_X: %.5f * \r\n", gyro.x_axis );
    log_printf( &logger, " * Gyro_Y: %.5f * \r\n", gyro.y_axis );
    log_printf( &logger, " * Gyro_Z: %.5f * \r\n", gyro.z_axis );
    log_printf( &logger, " ---------------------------- \r\n" );

    c6dofimu7_get_accel_data( &c6dofimu7, &accel, C6DOFIMU7_ACCEL_SENSITIVITY );

    log_printf( &logger, " * Accel_X: %.5f * \r\n", accel.x_axis );
    log_printf( &logger, " * Accel_Y: %.5f * \r\n", accel.y_axis );
    log_printf( &logger, " * Accel_Z: %.5f * \r\n", accel.z_axis );
    log_printf( &logger, " ---------------------------- \r\n" );

    temperature = c6dofimu7_get_temp_data( &c6dofimu7, C6DOFIMU7_TEMPERATURE_SENSITIVITY,
                                                       C6DOFIMU7_TEMPERATURE_OFFSET );

    log_printf( &logger, " * Temperature: %.5f C * \r\n\r\n", temperature );
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
