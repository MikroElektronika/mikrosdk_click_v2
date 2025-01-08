
---
# 6DOF IMU 14 Click

> [6DOF IMU 14 Click](https://www.mikroe.com/?pid_product=MIKROE-4237) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4237&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2021.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of 6DOF IMU 14 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.6DOFIMU14

### Example Key Functions

- `c6dofimu14_cfg_setup` Config Object Initialization function.
```c
void c6dofimu14_cfg_setup ( c6dofimu14_cfg_t *cfg );
```

- `c6dofimu14_init` Initialization function.
```c
err_t c6dofimu14_init ( c6dofimu14_t *ctx, c6dofimu14_cfg_t *cfg );
```

- `c6dofimu14_default_cfg` Click Default Configuration function.
```c
void c6dofimu14_default_cfg ( c6dofimu14_t *ctx );
```

- `c6dofimu14_get_data` This function reads accel and gyro data for all three axis.
```c
err_t c6dofimu14_get_data ( c6dofimu14_t *ctx, c6dofimu14_axis_t *acc_axis, c6dofimu14_axis_t *gyro_axis );
```

- `c6dofimu14_get_temperature` This function reads the raw temperature data and converts it to Celsius.
```c
err_t c6dofimu14_get_temperature ( c6dofimu14_t *ctx, float *temp );
```

- `c6dofimu14_software_reset` This function performs the device software reset.
```c
err_t c6dofimu14_software_reset ( c6dofimu14_t *ctx );
```

### Application Init

> Initializes the driver and configures the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c6dofimu14_cfg_t c6dofimu14_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    c6dofimu14_cfg_setup( &c6dofimu14_cfg );
    C6DOFIMU14_MAP_MIKROBUS( c6dofimu14_cfg, MIKROBUS_1 );
    err_t init_flag = c6dofimu14_init( &c6dofimu14, &c6dofimu14_cfg );
    if ( ( init_flag == I2C_MASTER_ERROR ) || ( init_flag == SPI_MASTER_ERROR ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms ( 100 );

    if ( c6dofimu14_default_cfg ( &c6dofimu14 ) != C6DOFIMU14_OK ) 
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads accel, gyro, and temperature data and displays the results on the USB UART approximately every 500ms.

```c
void application_task ( void )
{
    float temperature;
    c6dofimu14_axis_t accel;
    c6dofimu14_axis_t gyro;
    
    c6dofimu14_get_data( &c6dofimu14, &accel, &gyro );
    c6dofimu14_get_temperature( &c6dofimu14, &temperature );
        
    log_printf( &logger, " Accel X: %d | Gyro X: %d\r\n", accel.x, gyro.x );
    log_printf( &logger, " Accel Y: %d | Gyro Y: %d\r\n", accel.y, gyro.y );
    log_printf( &logger, " Accel Z: %d | Gyro Z: %d\r\n", accel.z, gyro.z );
    log_printf( &logger, " Temperature: %.2f C\r\n", temperature );
    log_printf( &logger, "----------------------------------\r\n");
        
    Delay_ms ( 500 );
}
```

### Note

> In the case of I2C, the example doesn't work properly on some of the 8-bit PICs (ex. PIC18F97J94).

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
