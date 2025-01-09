
---
# 6DOF IMU 17 Click

> [6DOF IMU 17 Click](https://www.mikroe.com/?pid_product=MIKROE-4785) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4785&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2021.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This library contains API for 6DOF IMU 17 Click driver.
> The library initializes and defines the I2C or SPI bus drivers 
> to write and read data from registers. 
> The library also includes a function for reading 
> accelerometer and gyroscope X-axis, Y-axis, and Z-axis data 
> as well as the temperature in degrees Celsius.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.6DOFIMU17

### Example Key Functions

- `c6dofimu17_cfg_setup` Config Object Initialization function.
```c
void c6dofimu17_cfg_setup ( c6dofimu17_cfg_t *cfg );
```

- `c6dofimu17_init` Initialization function.
```c
err_t c6dofimu17_init ( c6dofimu17_t *ctx, c6dofimu17_cfg_t *cfg );
```

- `c6dofimu17_default_cfg` Click Default Configuration function.
```c
err_t c6dofimu17_default_cfg ( c6dofimu17_t *ctx );
```

- `c6dofimu17_get_accel_data` 6DOF IMU 17 get accel data function.
```c
err_t c6dofimu17_get_accel_data ( c6dofimu17_t *ctx, c6dofimu17_axis_t *accel_data );
```

- `c6dofimu17_get_gyro_data` 6DOF IMU 17 get gyroscope data function.
```c
err_t c6dofimu17_get_gyro_data ( c6dofimu17_t *ctx, c6dofimu17_axis_t *gyro_data );
```

- `c6dofimu17_get_temperature` 6DOF IMU 17 get temperature data function.
```c
err_t c6dofimu17_get_temperature ( c6dofimu17_t *ctx, float *temperature );
```

### Application Init

> The initialization of I2C or SPI module, log UART, and additional pins. 
> After the driver init, the app checks communication, 
> sensor ID, and then executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;                /**< Logger config object. */
    c6dofimu17_cfg_t c6dofimu17_cfg;  /**< Click config object. */
    uint8_t device_id;

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
    c6dofimu17_cfg_setup( &c6dofimu17_cfg );
    C6DOFIMU17_MAP_MIKROBUS( c6dofimu17_cfg, MIKROBUS_1 );
    err_t init_flag  = c6dofimu17_init( &c6dofimu17, &c6dofimu17_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

       for ( ; ; );
    }

    c6dofimu17_default_cfg ( &c6dofimu17 );
    Delay_ms ( 100 );
    
    c6dofimu17_get_device_id( &c6dofimu17, &device_id );
    Delay_ms ( 100 );
    if ( device_id == C6DOFIMU17_CHIP_ID ) 
    {
        log_printf( &logger, "\t\t  Communication OK\r\n" );
    }
    else 
    {
        log_printf( &logger, "\t\tCommunication ERROR\r\n" );
        log_printf( &logger, "\t\t  Reset the device\r\n" );

        for ( ; ; );
    }
    
    log_printf( &logger, "\t--------------------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that shows the use of a 6DOF IMU 17 Click board&trade;.
> Measures and displays acceleration and gyroscope data for X-axis, Y-axis, and Z-axis
> and the temperature in degrees Celsius. 
> Results are being sent to the USART terminal where the user can track their changes. 
> This task repeats every 100 ms.

```c
void application_task ( void )
{   
    c6dofimu17_axis_t accel_data;
    c6dofimu17_axis_t gyro_data;
    float temperature;
    if ( ( C6DOFIMU17_OK == c6dofimu17_get_accel_data( &c6dofimu17, &accel_data ) ) &&  
         ( C6DOFIMU17_OK == c6dofimu17_get_gyro_data( &c6dofimu17, &gyro_data ) ) &&  
         ( C6DOFIMU17_OK == c6dofimu17_get_temperature( &c6dofimu17, &temperature ) ) )
    {
        log_printf( &logger, "\t Accel X: %d\t|\tGyro X: %d\r\n", accel_data.x, gyro_data.x );
        log_printf( &logger, "\t Accel Y: %d\t|\tGyro Y: %d\r\n", accel_data.y, gyro_data.y );
        log_printf( &logger, "\t Accel Z: %d\t|\tGyro Z: %d\r\n", accel_data.z, gyro_data.z );
        log_printf( &logger, "\t- - - - - - - - - -  - - - - - - - - -\r\n" );
        log_printf( &logger, "\t\t Temperature: %.2f C\r\n", temperature );
        log_printf( &logger, "\t--------------------------------------\r\n" );
    }
    Delay_ms ( 100 );
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
