
---
# c6DOF IMU 10 Click

> [6DOF IMU 10 Click](https://www.mikroe.com/?pid_product=MIKROE-3934) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3934&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This app reads the accelerometer and magnetometer axis data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.6DofImu10

### Example Key Functions

- `c6dofimu10_cfg_setup` Config Object Initialization function. 
```c
void c6dofimu10_cfg_setup ( c6dofimu10_cfg_t *cfg );
``` 
 
- `c6dofimu10_init` Initialization function. 
```c
err_t c6dofimu10_init ( c6dofimu10_t *ctx, c6dofimu10_cfg_t *cfg );
```

- `c6dofimu10_default_cfg` Click Default Configuration function. 
```c
void c6dofimu10_default_cfg ( c6dofimu10_t *ctx );
```

- `c6dofimu10_get_accel_axis` This function gets accelerometer axis data. 
```c
void c6dofimu10_get_accel_axis ( c6dofimu10_t *ctx, c6dofimu10_axis_t *axis );
```
 
- `c6dofimu10_get_mag_axis` This function gets magnetometer axis data. 
```c
void c6dofimu10_get_mag_axis ( c6dofimu10_t *ctx, c6dofimu10_axis_t *axis );
```

- `c6dofimu10_get_temperature` This function gets temperature data. 
```c
float c6dofimu10_get_temperature ( c6dofimu10_t *ctx, uint8_t temp_format );
```

### Application Init

> Initializes device and runs a communication test that reads device id (registry Who_I_AM).

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu10_cfg_t cfg;
    uint8_t com_test;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    c6dofimu10_cfg_setup( &cfg );
    c6DOFIMU10_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu10_init( &c6dofimu10, &cfg );

    // TEST COMMUNICATION
    com_test = c6dofimu10_communication_test( &c6dofimu10 );
    if ( com_test != C6DOFIMU10_DEVICE_OK )
    {
        log_printf( &logger, "-- Device communication ERROR --\r\n" );
        for( ; ; );
    }
    log_printf( &logger, "-- Device communication OK --\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    c6dofimu10_default_cfg ( &c6dofimu10 );
    log_printf( &logger, "-- Device configuration --\r\n" );
    Delay_ms ( 500 );
}
```

### Application Task

> Reads the accelerometer and magnetometer axis data.
> And reads temperature values. All data logs on the USBUART.

```c
void application_task ( void )
{
    c6dofimu10_axis_t accel_axis;
    c6dofimu10_axis_t mag_axis;
    float temperature;

    c6dofimu10_get_accel_axis ( &c6dofimu10, &accel_axis );
    c6dofimu10_get_mag_axis ( &c6dofimu10, &mag_axis );
    temperature = c6dofimu10_get_temperature( &c6dofimu10, C6DOFIMU10_TEMP_FORMAT_CELSIUS );

    log_printf( &logger, "-- Accelerometer axis --\r\n" );
    app_display_axis_data( &accel_axis );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "-- Magnetometer axis --\r\n" );
    app_display_axis_data( &mag_axis );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "-- Temperature data --\r\n" );
    app_display_temp_data( temperature );
    Delay_ms ( 1000 );
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
