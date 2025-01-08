
---
# 6DOF IMU Click

> [6DOF IMU Click](https://www.mikroe.com/?pid_product=MIKROE-1941) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1941&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example showcases how to initalize and use the 6DOF IMU Click. The Click contains a 
  6-axis inertial measurement unit ( accelerometer + gyroscope ). After configuring the Click
  module for proper use, axis and temperature data will be measured every second. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.6DofImu

### Example Key Functions

- `c6dofimu_cfg_setup` Config Object Initialization function. 
```c
void c6dofimu_cfg_setup ( c6dofimu_cfg_t *cfg );
``` 
 
- `c6dofimu_init` Initialization function. 
```c
err_t c6dofimu_init ( c6dofimu_t *ctx, c6dofimu_cfg_t *cfg );
```

- `c6dofimu_default_cfg` Click Default Configuration function. 
```c
void c6dofimu_default_cfg ( c6dofimu_t *ctx );
```

- This function reads axis data for the gyroscope or the accelerometer from
  predefined data register addresses.
> void c6dofimu_read_axis_data ( c6dofimu_t *ctx, uint8_t read_mode );
 
- `c6dofimu_read_temperature` This function reads temperature data from predefined data registers. 
```c
float c6dofimu_read_temperature ( c6dofimu_t *ctx );
```

- `c6dofimu_digital_read_int` This function reads the digital signal from the INT pin. 
```c
uint8_t c6dofimu_digital_read_int ( c6dofimu_t *ctx );
```

### Application Init

> This function initializes and configures the Click and logger modules. In order for the 
  device to work well, proper data needs to be written to the measurement control
  registers as is done in the default_cfg(...) function. 

```c
void application_init ( )
{
    log_cfg_t log_cfg;
    c6dofimu_cfg_t cfg;

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
    Delay_100ms( );

    //  Click initialization.

    c6dofimu_cfg_setup( &cfg );
    C6DOFIMU_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu_init( &c6dofimu, &cfg );
    Delay_100ms( );
    c6dofimu_default_cfg( &c6dofimu );
}
```

### Application Task

> This function reads and displays temperature and accelerometer/gyroscope axis data from
  predefined registers. There is a 1 second delay between every read from the data output
  registers. 

```c
void application_task ( )
{
    float temperature; 

    c6dofimu_read_axis_data( &c6dofimu, C6DOFIMU_ACCEL_READ_MODE );
    Delay_1sec( );
    c6dofimu_read_axis_data( &c6dofimu, C6DOFIMU_GYRO_READ_MODE );
    Delay_1sec( );
    temperature = c6dofimu_read_temperature( &c6dofimu );

    log_printf( &logger, "--------------------------------------------\r\n" );
    log_printf( &logger, " * ACCEL * X: %6.d Y: %6.d Z: %6.d\r\n", c6dofimu.accel_axis.x,
                                                                   c6dofimu.accel_axis.y,
                                                                   c6dofimu.accel_axis.z );
    log_printf( &logger, " * GYRO * X: %6.d Y: %6.d Z: %6.d\r\n", c6dofimu.gyro_axis.x,
                                                                  c6dofimu.gyro_axis.y,
                                                                  c6dofimu.gyro_axis.z );
    log_printf( &logger, " * Temperature: %.3f C\r\n", temperature );
    Delay_1sec( );
}
```

### Note

> <WARNING> If you write data to any of the "reserved" register addresses, you can permanently
  damage the chip. If you are feeling adventurous, read the LSM6DS33 chip datasheet.

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
