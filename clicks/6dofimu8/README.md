
---
# 6DOF IMU 8 Click

> [6DOF IMU 8 Click](https://www.mikroe.com/?pid_product=MIKROE-3447) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3447&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This app gets three-axis gyroscope value, three-axis accelerometer value and temperature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.6DofImu8

### Example Key Functions

- `c6dofimu8_cfg_setup` Config Object Initialization function. 
```c
void c6dofimu8_cfg_setup ( c6dofimu8_cfg_t *cfg );
``` 
 
- `c6dofimu8_init` Initialization function. 
```c
err_t c6dofimu8_init ( c6dofimu8_t *ctx, c6dofimu8_cfg_t *cfg );
```

- `c6dofimu8_default_cfg` Click Default Configuration function. 
```c
void c6dofimu8_default_cfg ( c6dofimu8_t *ctx );
```

- `c6dofimu8_get_int_1_pin` This function checks does interrupt generated on the INT1 pin. 
```c
uint8_t c6dofimu8_get_int_1_pin ( c6dofimu8_t *ctx );
```
 
- `c6dofimu8_get_drdy_status` This function checks a data ready status for all measurements. 
```c
uint8_t c6dofimu8_get_drdy_status ( c6dofimu8_t *ctx, uint8_t bit_mask );
```

- `c6dofimu8_get_magnetometer_data` This function performs a magnetometer data reading. 
```c
void c6dofimu8_get_magnetometer_data ( c6dofimu8_t *ctx, t_c6dofimu8_axis *magneto_out );
```

### Application Init

> Initializes device and performs a device software reset and configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu8_cfg_t cfg;

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

    c6dofimu8_cfg_setup( &cfg );
    C6DOFIMU8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu8_init( &c6dofimu8, &cfg );

    Delay_ms ( 500 );
    
    c6dofimu8_default_cfg( &c6dofimu8 );

    log_printf( &logger, "** 6DOF IMU 8 is initialized **\r\n" );
    Delay_ms ( 300 );
}
```

### Application Task

> Waits until any new data is entered to the data registers and then reads the accelerometer,
> gyroscope and temperature data which will be converted and calculated to the properly units each second.

```c
void application_task ( void )
{
    uint8_t data_ready;
    int8_t temperature;
    t_c6dofimu8_axis  accel_data;
    t_c6dofimu8_axis  gyro_data;

    data_ready = c6dofimu8_get_drdy_status( &c6dofimu8, C6DOFIMU8_TEMP_DRDY_MASK | 
                                                        C6DOFIMU8_G_DRDY_MASK | 
                                                        C6DOFIMU8_XL_DRDY_MASK );
    while ( data_ready == C6DOFIMU8_EVENT_NOT_DETECTED )
    {
        data_ready = c6dofimu8_get_drdy_status( &c6dofimu8, C6DOFIMU8_TEMP_DRDY_MASK | 
                                                            C6DOFIMU8_G_DRDY_MASK | 
                                                            C6DOFIMU8_XL_DRDY_MASK );
    }

    c6dofimu8_get_data( &c6dofimu8, &accel_data, &gyro_data, &temperature );

    log_printf( &logger, "** Accelerometer values : \r\n" );
    log_axis( &accel_data );

    log_printf( &logger, "** Gyroscope values : \r\n" );
    log_axis( &gyro_data );

    log_printf( &logger, "** Temperature value : %d degC \r\n", ( int16_t )temperature );
    log_printf( &logger, "-------------------------------------------------\r\n" );

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
