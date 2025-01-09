
---
# 6DOF IMU 5 Click

> [6DOF IMU 5 Click](https://www.mikroe.com/?pid_product=MIKROE-4089) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4089&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of 6DOF IMU 5 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.6DofImu5

### Example Key Functions

- `c6dofimu5_cfg_setup` Config Object Initialization function. 
```c
void c6dofimu5_cfg_setup ( c6dofimu5_cfg_t *cfg );
``` 
 
- `c6dofimu5_init` Initialization function. 
```c
err_t c6dofimu5_init ( c6dofimu5_t *ctx, c6dofimu5_cfg_t *cfg );
```

- `c6dofimu5_default_cfg` Click Default Configuration function. 
```c
void c6dofimu5_default_cfg ( c6dofimu5_t *ctx );
```

- `c6dofimu5_power` This function turns the device on or off. 
```c
void c6dofimu5_power ( c6dofimu5_t *ctx, uint8_t on_off );
```
 
- `c6dofimu5_read_gyroscope` This function is used to read gyroscope data. 
```c
void c6dofimu5_read_gyroscope ( c6dofimu5_t *ctx, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z );
```

- `c6dofimu5_read_accelerometer` This function is used to read accelerometer data. 
```c
void c6dofimu5_read_accelerometer ( c6dofimu5_t *ctx, int16_t *accel_x, int16_t *accel_y, int16_t *accel_z );
```

### Application Init

> Initializes the driver, checks the communication and sets the device default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu5_cfg_t cfg;
    uint8_t id_val;

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

    c6dofimu5_cfg_setup( &cfg );
    C6DOFIMU5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu5_init( &c6dofimu5, &cfg );
    
    c6dofimu5_read_bytes ( &c6dofimu5, C6DOFIMU5_WHO_AM_I, &id_val, 1 );
    if ( id_val == C6DOFIMU5_WHO_AM_I_VAL )
    {
        log_printf( &logger, "-------------------------\r\n " );
        log_printf( &logger, "   6DOF  IMU  5  Click   \r\n " );
        log_printf( &logger, "-------------------------\r\n " );
        c6dofimu5_power ( &c6dofimu5, C6DOFIMU5_POWER_ON );
    }
    else
    {   
        log_printf( &logger, "-------------------------\r\n " );
        log_printf( &logger, "     FATAL  ERROR!!!     \r\n " );
        log_printf( &logger, "-------------------------\r\n " );
        for ( ; ; );
    }

    c6dofimu5_default_cfg( &c6dofimu5 );
    c6dofimu5_baro_settings( &c6dofimu5 );

    log_printf( &logger, "    ---Initialised---    \r\n " );
    log_printf( &logger, "-------------------------\r\n " );

    Delay_ms ( 100 );
}
```

### Application Task

> Measures acceleration, gyroscope, temperature and pressure data and displays the results on USB UART each second.

```c
void application_task ( void )
{
    float x_gyro;
    float y_gyro;
    float z_gyro;
    float x_accel;
    float y_accel;
    float z_accel;
    uint32_t raw_pres;
    uint16_t raw_temp;
    c6dofimu5_process_data_t process_data;

    c6dofimu5_acceleration_rate( &c6dofimu5, &x_accel, &y_accel, &z_accel );
    c6dofimu5_angular_rate( &c6dofimu5, &x_gyro, &y_gyro, &z_gyro );

    log_printf( &logger, " Accel X: %.2f \t Gyro X: %.2f\r\n", x_accel, x_gyro );
    log_printf( &logger, " Accel Y: %.2f \t Gyro Y: %.2f\r\n", y_accel, y_gyro );
    log_printf( &logger, " Accel Z: %.2f \t Gyro Z: %.2f\r\n", z_accel, z_gyro );
    
    log_printf( &logger, "-------------------------\r\n " );

    c6dofimu5_read_raw_data( &c6dofimu5, &raw_pres, &raw_temp );

    process_data.p_raw = raw_pres;
    process_data.t_raw = raw_temp;

    c6dofimu5_process_data( &c6dofimu5, &process_data );

    log_printf( &logger, "Pressure: %.2f mBar\r\n " , process_data.pressure * 0.01 );
    log_printf( &logger, "Temperature: %.2f Celsius\r\n " , process_data.temperature );

    log_printf( &logger, "-------------------------\r\n" );
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
