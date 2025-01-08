
---
# 6DOF IMU 13 Click

> [6DOF IMU 13 Click](https://www.mikroe.com/?pid_product=MIKROE-4228) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4228&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of 6DOF IMU 13 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.6DOFIMU13

### Example Key Functions

- `c6dofimu13_cfg_setup` Config Object Initialization function.
```c
void c6dofimu13_cfg_setup ( c6dofimu13_cfg_t *cfg );
```

- `c6dofimu13_init` Initialization function.
```c
err_t c6dofimu13_init ( c6dofimu13_t *ctx, c6dofimu13_cfg_t *cfg );
```

- `c6dofimu13_default_cfg` Click Default Configuration function.
```c
void c6dofimu13_default_cfg ( c6dofimu13_t *ctx );
```

- `c6dofimu13_mag_get_data` This function reads magnetometer X, Y, and Z-Axis data.
```c
err_t c6dofimu13_mag_get_data ( c6dofimu13_t *ctx, float *mag_x, float *mag_y, float *mag_z );
```

- `c6dofimu13_accel_init` This function initializes accelerometer.
```c
err_t c6dofimu13_accel_init ( c6dofimu13_t *ctx, uint8_t samp_rate, uint8_t samp_range, uint8_t samp_res );
```

- `c6dofimu13_accel_get_data` This function reads accelerometer X, Y, and Z-Axis data.
```c
err_t c6dofimu13_accel_get_data ( c6dofimu13_t *ctx, float *accel_x, float *accel_y, float *accel_z );
```

### Application Init

> Initializes the driver, and sets the device default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c6dofimu13_cfg_t c6dofimu13_cfg;  /**< Click config object. */

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

    c6dofimu13_cfg_setup( &c6dofimu13_cfg );
    C6DOFIMU13_MAP_MIKROBUS( c6dofimu13_cfg, MIKROBUS_1 );
    err_t init_flag = c6dofimu13_init( &c6dofimu13, &c6dofimu13_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    c6dofimu13_default_cfg ( &c6dofimu13 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Measures acceleration and magnetometer data and displays the results on the USB UART every second.

```c
void application_task ( void )
{
    float acc_x, acc_y, acc_z;
    float mag_x, mag_y, mag_z;

    c6dofimu13_accel_get_data( &c6dofimu13, &acc_x, &acc_y, &acc_z );
    c6dofimu13_mag_get_data( &c6dofimu13, &mag_x, &mag_y, &mag_z );

    log_printf( &logger, " Accel X: %.3f g\t Mag X: %.2f uT\r\n", acc_x, mag_x );
    log_printf( &logger, " Accel Y: %.3f g\t Mag Y: %.2f uT\r\n", acc_y, mag_y );
    log_printf( &logger, " Accel Z: %.3f g\t Mag Z: %.2f uT\r\n", acc_z, mag_z );
    log_printf( &logger, "----------------------------------\r\n");

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
