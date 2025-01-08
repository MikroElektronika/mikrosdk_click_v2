
---
# Smart DOF 4 Click

> [Smart DOF 4 Click](https://www.mikroe.com/?pid_product=MIKROE-6369) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6369&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2024.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of Smart DOF 4 Click board by reading the accelerometer, gyroscope, and magnetometer data measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SmartDOF4

### Example Key Functions

- `smartdof4_cfg_setup` Config Object Initialization function.
```c
void smartdof4_cfg_setup ( smartdof4_cfg_t *cfg );
```

- `smartdof4_init` Initialization function.
```c
err_t smartdof4_init ( smartdof4_t *ctx, smartdof4_cfg_t *cfg );
```

- `smartdof4_default_cfg` Click Default Configuration function.
```c
err_t smartdof4_default_cfg ( smartdof4_t *ctx );
```

- `smartdof4_read_pid` This function reads the product ID information.
```c
err_t smartdof4_read_pid ( smartdof4_t *ctx, smartdof4_pid_t *pid );
```

- `smartdof4_feature_set` This function sets a full feature report.
```c
err_t smartdof4_feature_set ( smartdof4_t *ctx, smartdof4_feature_t *feat );
```

- `smartdof4_read_data` This function reads the accelerometer (g), gyroscope (dps), and magnetometer (uT) 3-axis data from input report. 
```c
err_t smartdof4_read_data ( smartdof4_t *ctx, smartdof4_axis_t *accel, 
                            smartdof4_axis_t *gyro, smartdof4_axis_t *mag );
```

### Application Init

> Initializes the driver and performs the Click default configuration enabling
accelerometer, gyroscope, and magnetometer sensors with an output data rate of 10Hz.
After that, it reads the software version, part number, and build number information.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartdof4_cfg_t smartdof4_cfg;  /**< Click config object. */

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
    smartdof4_cfg_setup( &smartdof4_cfg );
    SMARTDOF4_MAP_MIKROBUS( smartdof4_cfg, MIKROBUS_1 );
    err_t init_flag = smartdof4_init( &smartdof4, &smartdof4_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SMARTDOF4_ERROR == smartdof4_default_cfg ( &smartdof4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    smartdof4_pid_t pid;
    if ( SMARTDOF4_OK == smartdof4_read_pid ( &smartdof4, &pid ) )
    {
        log_printf ( &logger, " SW Version: %u.%u.%u\r\n", ( uint16_t ) pid.sw_ver_major, 
                                                           ( uint16_t ) pid.sw_ver_minor, 
                                                           ( uint16_t ) pid.sw_ver_patch );
        log_printf ( &logger, " SW Part Number: %lu\r\n", pid.sw_part_num );
        log_printf ( &logger, " SW Build Number: %lu\r\n\n", pid.sw_build_num );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the accelerometer (g), gyroscope (dps), and magnetometer (uT) measurements and displays results on the USB UART every 100ms approximately.

```c
void application_task ( void )
{
    static smartdof4_axis_t accel, gyro, mag;
    if ( SMARTDOF4_OK == smartdof4_read_data ( &smartdof4, &accel, &gyro, &mag ) )
    {
        log_printf ( &logger, " Accel X: %.3f g\r\n", accel.x );
        log_printf ( &logger, " Accel Y: %.3f g\r\n", accel.y );
        log_printf ( &logger, " Accel Z: %.3f g\r\n", accel.z );
        log_printf ( &logger, " Gyro X: %.1f dps\r\n", gyro.x );
        log_printf ( &logger, " Gyro Y: %.1f dps\r\n", gyro.y );
        log_printf ( &logger, " Gyro Z: %.1f dps\r\n", gyro.z );
        log_printf ( &logger, " Mag X: %.1f uT\r\n", mag.x );
        log_printf ( &logger, " Mag Y: %.1f uT\r\n", mag.y );
        log_printf ( &logger, " Mag Z: %.1f uT\r\n\n", mag.z );
        Delay_ms ( 100 );
    }
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
