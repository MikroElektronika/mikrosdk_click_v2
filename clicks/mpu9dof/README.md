
---
# MPU 9DOF Click

> [MPU 9DOF Click](https://www.mikroe.com/?pid_product=MIKROE-1719) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1719&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : maj 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> MPU 9DOF Click carries the world’s first 9-axis Motion Tracking device. It comprises two chips: one that contains 
> a 3-axis accelerometer, a 3-axis gyroscope, and a DMP (digital motion processor); 
> the other is a 3-axis digital compass. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Mpu9Dof

### Example Key Functions

- `mpu9dof_cfg_setup` Config Object Initialization function. 
```c
void mpu9dof_cfg_setup ( mpu9dof_cfg_t *cfg );
``` 
 
- `mpu9dof_init` Initialization function. 
```c
err_t mpu9dof_init ( mpu9dof_t *ctx, mpu9dof_cfg_t *cfg );
```

- `mpu9dof_default_cfg` Click Default Configuration function. 
```c
void mpu9dof_default_cfg ( mpu9dof_t *ctx );
```

- `mpu9dof_read_accel` Function read Gyro X-axis, Y-axis and Z-axis axis. 
```c
void mpu9dof_read_accel ( mpu9dof_t *ctx, int16_t *accel_x, int16_t *accel_y, int16_t *accel_z );
```
 
- `mpu9dof_read_gyro` Function read Gyro X-axis, Y-axis and Z-axis axis. 
```c
void mpu9dof_read_gyro ( mpu9dof_t *ctx, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z );
```

- `mpu9dof_read_mag` Function read Magnetometar X-axis, Y-axis and Z-axis axis. 
```c
void mpu9dof_read_mag ( mpu9dof_t *ctx, int16_t *mag_x, int16_t *mag_y, int16_t *mag_z );
```

### Application Init

> Initialization driver enable's - I2C, initialize MPU-9150 XL G & MPU-9150 MAG and start write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    mpu9dof_cfg_t cfg;

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

    mpu9dof_cfg_setup( &cfg );
    MPU9DOF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mpu9dof_init( &mpu9dof, &cfg );

    Delay_10ms( );
    mpu9dof_default_cfg ( &mpu9dof );
}
```

### Application Task

> This is a example which demonstrates the use of MPU 9DOF Click board.
> Measured accel, gyro and magnetometar coordinates values ( X, Y, Z )
> and temperature value in degrees celsius [ �C ] are being sent to the uart where you can track their changes.
> All data logs on usb uart for aproximetly every 1 sec. 

```c
void application_task ( void )
{
    mpu9dof_read_accel( &mpu9dof, &accel_x, &accel_y, &accel_z );
    Delay_10ms( );
    mpu9dof_read_gyro( &mpu9dof, &gyro_x,  &gyro_y, &gyro_z );
    Delay_10ms( );
    mpu9dof_read_mag( &mpu9dof, &mag_x,  &mag_y, &mag_z );
    Delay_10ms( );
    temperature = mpu9dof_read_temperature( &mpu9dof );
    Delay_10ms( );

    log_printf( &logger, " Accel X : %d   |   Gyro X : %d   |   Mag X : %d \r\n", accel_x, gyro_x, mag_x );
    log_printf( &logger, " Accel Y : %d   |   Gyro Y : %d   |   Mag Y : %d \r\n", accel_y, gyro_y, mag_y );
    log_printf( &logger, " Accel Z : %d   |   Gyro Z : %d   |   Mag Z : %d \r\n", accel_z, gyro_z, mag_z );
    Delay_10ms( );
    log_printf( &logger, "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\r\n" );
    Delay_10ms( );
    log_printf( &logger, "Temperature: %.2f C\r\n", temperature );
    Delay_100ms( );
    log_printf( &logger, "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "\r\n");
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
