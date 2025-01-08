
---
# 6DOF IMU 3 Click

> [6DOF IMU 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4086) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4086&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of 6DOF IMU 3 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.6Dofimu3

### Example Key Functions

- `c6dofimu3_cfg_setup` Config Object Initialization function. 
```c
void c6dofimu3_cfg_setup ( c6dofimu3_cfg_t *cfg );
``` 
 
- `c6dofimu3_init` Initialization function. 
```c
err_t c6dofimu3_init ( c6dofimu3_t *ctx, c6dofimu3_cfg_t *cfg );
```

- `c6dofimu3_default_cfg` Click Default Configuration function. 
```c
void c6dofimu3_default_cfg ( c6dofimu3_t *ctx );
```

- Function check device ID by read ID value from the sensor ID register address
  of FXOS8700CQ 6-axis sensor with integrated linear
  accelerometer and magnetometer on 6DOF IMU 3 Click board.
err_t c6dofimu3_check_id ( c6dofimu3_t *ctx );
 
- Function read 16-bit ( signed ) Magnetometer
   X-axis, Y-axis data and Z-axis data from the 6
  targeted starts from C6DOFIMU3_M_OUT_X_MSB register address
  of FXOS8700CQ 6-axis sensor with integrated linear
  accelerometer and magnetometer on 6DOF IMU 3 Click board.
> void c6dofimu3_read_mag_data ( c6dofimu3_t *ctx, c6dofimu3_mag_t *mag_data );

- Function read 14-bit ( signed ) Accel
   X-axis, Y-axis data and Z-axis data from the 6
  targeted starts from C6DOFIMU3_OUT_X_MSB register address
  of FXOS8700CQ 6-axis sensor with integrated linear
  accelerometer and magnetometer on 6DOF IMU 3 Click board.
> void c6dofimu3_read_accel_data ( c6dofimu3_t *ctx, c6dofimu3_accel_t *accel_data );

### Application Init

> Initializes the driver and sets the device default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu3_cfg_t cfg;

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

    c6dofimu3_cfg_setup( &cfg );
    C6DOFIMU3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu3_init( &c6dofimu3, &cfg );

    c6dofimu3_default_cfg( &c6dofimu3 );
    Delay_ms ( 100 );
}
```

### Application Task

> Measures acceleration and magnetometer data and displays the results on USB UART each second.

```c
void application_task ( void )
{
    if ( c6dofimu3_check_data_ready( &c6dofimu3 ) )
    {
        c6dofimu3_get_data ( &c6dofimu3, &accel_data, &mag_data );

        log_printf( &logger, " Accel X : %.2f mg \t Mag X : %.2f uT\r\n", accel_data.x, mag_data.x );

        log_printf( &logger, " Accel Y : %.2f mg \t Mag Y : %.2f uT\r\n", accel_data.y, mag_data.y );
        
        log_printf( &logger, " Accel Z : %.2f mg \t Mag Z : %.2f uT\r\n", accel_data.z, mag_data.z );
        
        log_printf( &logger, "-------------------------------------\r\n" );

        Delay_ms ( 800 );
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
