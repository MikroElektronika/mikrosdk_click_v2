
---
# MPU IMU Click

> [MPU IMU Click](https://www.mikroe.com/?pid_product=MIKROE-1577) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1577&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Mihajlo Djordjevic
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> 
> Example code performs acceleration, angular rate (gyroscopic), and temperature measurement.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MpuImu

### Example Key Functions

- `mpuimu_cfg_setup` Config Object Initialization function. 
```c
void mpuimu_cfg_setup ( mpuimu_cfg_t *cfg );
``` 
 
- `mpuimu_init` Initialization function. 
```c
err_t mpuimu_init ( mpuimu_t *ctx, mpuimu_cfg_t *cfg );
```

- `mpuimu_default_cfg` Click Default Configuration function. 
```c
void mpuimu_default_cfg ( mpuimu_t *ctx );
```

- `mpuimu_read_accel` This function read Accel X-axis, Y-axis and Z-axis. 
```c
void mpuimu_read_accel ( mpuimu_t *ctx, mpuimu_accel_data_t *accel_data );
```
 
- `mpuimu_read_gyro` This function read Gyro X-axis, Y-axis and Z-axis. 
```c
void mpuimu_read_gyro ( mpuimu_t *ctx, mpuimu_gyro_data_t *gyro_data );
```

- `mpuimu_read_temperature` This function reads temperature data. 
```c
float mpuimu_read_temperature ( mpuimu_t *ctx );
```

### Application Init

>
> Application Init performs Logger and Click initialization.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    mpuimu_cfg_t cfg;

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
    Delay_ms ( 100 );

    //  Click initialization.

    mpuimu_cfg_setup( &cfg );
    MPUIMU_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mpuimu_init( &mpuimu, &cfg );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " ----  MPU IMU Click ----\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    
    mpuimu_default_cfg ( &mpuimu );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " ---- Initialization ---\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

>
> Measured Accel and Gyro coordinates (X,Y,Z) and Temperature in degrees C 
> which are being sent to the UART where you can track their changes. 
> All data logs on USB UART for every 1 sec.
> 

```c
void application_task ( void )
{
    mpuimu_read_accel( &mpuimu, &accel_data );
    Delay_ms ( 100 );
    mpuimu_read_gyro( &mpuimu, &gyro_data );
    Delay_ms ( 100 );
    temperature = mpuimu_read_temperature( &mpuimu );
    Delay_ms ( 100 );
    
    log_printf( &logger, "    Accel    |    Gyro    \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " X = %d  | X = %d \r\n", accel_data.accel_x, gyro_data.gyro_x );
    log_printf( &logger, " Y = %d  | Y = %d \r\n", accel_data.accel_y, gyro_data.gyro_y );
    log_printf( &logger, " Z = %d  | Z = %d \r\n", accel_data.accel_z, gyro_data.gyro_z );
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "      TEMP = %0.2f C\r\n", temperature );
    log_printf( &logger, "--------------------------\r\n" ); 
    
    software_reset ( &mpuimu );
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
