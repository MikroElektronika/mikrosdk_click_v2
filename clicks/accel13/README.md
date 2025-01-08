
---
# Accel 13 Click

> [Accel 13 Click](https://www.mikroe.com/?pid_product=MIKROE-3742) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3742&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This application enables reading acceleration and tapping data on all 3 axes,
> using I2C or SPI communication.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel13

### Example Key Functions

- `accel13_cfg_setup` Config Object Initialization function. 
```c
void accel13_cfg_setup ( accel13_cfg_t *cfg );
``` 
 
- `accel13_init` Initialization function. 
```c
err_t accel13_init ( accel13_t *ctx, accel13_cfg_t *cfg );
```

- `accel13_default_cfg` Click Default Configuration function. 
```c
void accel13_default_cfg ( accel13_t *ctx );
```

- `accel13_get_status ` This function reads the status data and stores it in the status object. 
```c
void accel13_get_status  ( accel13_t *ctx, accel13_status_t *status );
```
 
- `accel13_get_tap_status` This function reads the tap status data and stores it in the tap_status object. 
```c
void accel13_get_tap_status ( accel13_t *ctx, accel13_tap_t *tap_status );
```

- `accel13_get_6d_status` This function reads the 6D status data and stores it in the sixd_status object. 
```c
void accel13_get_6d_status ( accel13_t *ctx, accel13_6d_t *sixd_status );
```

### Application Init

> Initializes driver init, Test communication, 
> starts chip configuration for measurement and Temperature reads.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    accel13_cfg_t cfg;
    uint8_t device_id;
    float temperature;

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

    accel13_cfg_setup( &cfg );
    ACCEL13_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel13_init( &accel13, &cfg );

    accel13_generic_read_bytes( &accel13, ACCEL13_REG_WHO_AM_I, &device_id, 1 );

    if ( device_id != ACCEL13_DEF_WHO_AM_I )
    {
        log_printf( &logger, "*\\*/*\\*/ Communication ERROR !!! \\*/*\\*/*" );
        for ( ; ; );
    }
    log_printf( &logger, "---- Communication OK!!! ----\r\n" );
    Delay_100ms( );

    // Configuration

    accel13_default_cfg ( &accel13 );

    accel13_generic_write_single_byte( &accel13, ACCEL13_REG_CTRL_6, ACCEL13_CTRL6_BW_FILT_ODR_2 |
                                                                     ACCEL13_CTRL6_FULL_SCALE_2g |
                                                                     ACCEL13_CTRL6_FDS_LOW_PASS |
                                                                     ACCEL13_CTRL6_LOW_NOISE_ENABLE );

    // Temperature

    temperature = accel13_get_temperature( &accel13 );
    log_printf( &logger, " Temperature : %f.2 \r\n", temperature);
}
```

### Application Task

> Reads Accelerometer data and detects tap on the axis

```c
void application_task ( void )
{
    //  Task implementation.

    // Reads Accel data
    accel13_get_axis_data( &accel13, &axis );

    log_printf( &logger, "---- Accel axis data ----\r\n\n" );
    
    log_printf( &logger, "* X : %d \r\n", axis.x );
   
    log_printf( &logger, "* Y : %d \r\n", axis.y);

    log_printf( &logger, "* Z : %d \r\n", axis.z);
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms ( 300 );
    
    // Detections Tap on the axis
    accel13_get_tap_status( &accel13, &tap );

    if ( tap.tap_x == 0x01 )
    {
        log_printf( &logger, "---- Tap on the X axis ----\r\n" );
    }

    if( tap.tap_y == 0x01 )
    {
        log_printf( &logger,"---- Tap on the Y axis ----\r\n" );
    }

    if( tap.tap_z == 0x01 )
    {
        log_printf( &logger,"---- Tap on the Z axis ----\r\n" );
    }
}
```

### Note
 
> The example is the basic functionality of the IIS2DLPC sensor, 
> it is possible to read the acceleration data and detect Tap on all 3 axes.
> For other settings and improvements in reading accuracy, 
> you need to further set up the registers and set the sensor to your conditions. 

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
