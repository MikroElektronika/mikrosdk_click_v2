
---
# c6DOF IMU 4 Click

> [6DOF IMU 4 Click](https://www.mikroe.com/?pid_product=MIKROE-3410) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3410&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This application measures gyroscopic, accelerometer, and temperature data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.6DofImu4

### Example Key Functions

- `c6dofimu4_cfg_setup` Config Object Initialization function. 
```c
void c6dofimu4_cfg_setup ( c6dofimu4_cfg_t *cfg );
``` 
 
- `c6dofimu4_init` Initialization function. 
```c
err_t c6dofimu4_init ( c6dofimu4_t *ctx, c6dofimu4_cfg_t *cfg );
```

- `c6dofimu4_default_cfg` Click Default Configuration function. 
```c
void c6dofimu4_default_cfg ( c6dofimu4_t *ctx );
```

- `c6dofimu4_set_sync_pin` Sync Pin Setting function. 
```c
void c6dofimu4_set_sync_pin( c6dofimu4_t *ctx, uint8_t state );
```
 
- `c6dofimu4_get_data` Data Get function. 
```c
void c6dofimu4_get_data( c6dofimu4_t *ctx, c6dofimu4_axis_t *accel_out, c6dofimu4_axis_t *gyro_out, int8_t *temp_out );
```

- `c6dofimu4_set_fsr` Full Scale Setting function. 
```c
uint8_t c6dofimu4_set_fsr( c6dofimu4_t *ctx, uint8_t gyro_resol, uint8_t accel_resol );
```

### Application Init

> Initializes I2C interface and performs a device reset and configurations.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu4_cfg_t cfg;

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

    c6dofimu4_cfg_setup( &cfg );
    C6DOFIMU4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu4_init( &c6dofimu4, &cfg );
    c6dofimu4_reset( &c6dofimu4 );

    c6dofimu4_default_cfg( &c6dofimu4 );
    Delay_ms ( 200 );

    log_printf( &logger, "** 6DOF IMU 4 is initialized **\r\n" );
}
```

### Application Task

> Waits until data is ready and then reads the all data registers,
> accelerometer, gyroscope and temperature data, and shows results to the uart terminal every 500ms.

```c
void application_task ( void )
{
    c6dofimu4_axis_t  accel_data;
    c6dofimu4_axis_t  gyro_data;
    uint8_t data_ready;
    int8_t temperature;

    data_ready = c6dofimu4_get_status( &c6dofimu4, C6DOFIMU4_DATA_RDY_INT_MASK );

    while ( data_ready != C6DOFIMU4_DATA_RDY_INT_OCCURED )
    {
        data_ready = c6dofimu4_get_status( &c6dofimu4, C6DOFIMU4_DATA_RDY_INT_MASK );
    }
    
    c6dofimu4_get_data( &c6dofimu4, &accel_data, &gyro_data, &temperature );
    
    log_printf( &logger,"** Accelerometer values :\r\n" );
    log_printf( &logger, "* X-axis : %.2lf g ", accel_data.x );
    log_printf( &logger, "* Y-axis : %.2lf g ", accel_data.y );
    log_printf( &logger, "* Z-axis : %.2lf g ", accel_data.z );
    log_printf( &logger,"\r\n" );
    
    log_printf( &logger,"** Gyroscope values :\r\n" );
    log_printf( &logger, "* X-axis : %.2lf dps ", gyro_data.x );
    log_printf( &logger, "* Y-axis : %.2lf dps ", gyro_data.y );
    log_printf( &logger, "* Z-axis : %.2lf dps ", gyro_data.z );
    log_printf( &logger,"\r\n" );
    
    log_printf( &logger, "** Temperature value : %d C\r\n", temperature );
    log_printf( &logger,"------------------------------------------------- \r\n" );
    
    Delay_ms ( 500 );
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
