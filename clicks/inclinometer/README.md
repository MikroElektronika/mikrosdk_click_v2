
---
# Inclinometer Click

> [Inclinometer Click](https://www.mikroe.com/?pid_product=MIKROE-4753) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4753&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Jun 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example showcases ability of device to configure it for 
resolution and read Axis/Angle/Temperature data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Inclinometer

### Example Key Functions

- `inclinometer_cfg_setup` Config Object Initialization function.
```c
void inclinometer_cfg_setup ( inclinometer_cfg_t *cfg );
```

- `inclinometer_init` Initialization function.
```c
err_t inclinometer_init ( inclinometer_t *ctx, inclinometer_cfg_t *cfg );
```

- `inclinometer_default_cfg` Click Default Configuration function.
```c
err_t inclinometer_default_cfg ( inclinometer_t *ctx );
```

- `inclinometer_get_axes` Axes reading.
```c
err_t inclinometer_get_axes ( inclinometer_t *ctx, inclinometer_accel_t *axes_data );
```

- `inclinometer_get_angle` Angle reading.
```c
err_t inclinometer_get_angle ( inclinometer_t *ctx, inclinometer_accel_t *angle_data );
```

- `inclinometer_get_temperature` Temperature reading.
```c
err_t inclinometer_get_temperature ( inclinometer_t *ctx, float *temperature );
```

### Application Init

> Initialization of the Host communication modules(UART, SPI). 
Sets default configuration where powe-up sequence is done with 
selecting MODE1 and enabling output on Angle channels. 
Read status and checks WhoAmI register. In the end example type
is selected( for reading Axes, Angles or Temperature data ).

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    inclinometer_cfg_t inclinometer_cfg;  /**< Click config object. */

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
    inclinometer_cfg_setup( &inclinometer_cfg );
    INCLINOMETER_MAP_MIKROBUS( inclinometer_cfg, MIKROBUS_1 );
    err_t init_flag  = inclinometer_init( &inclinometer, &inclinometer_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    //Powerup
    init_flag = inclinometer_default_cfg ( &inclinometer );
    if ( INCLINOMETER_ERROR == init_flag )
    {
        log_error( &logger, " Default configuration. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    example_type = EXAMPLE_AXIS;
    Delay_ms ( 1000 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Depending on the example type selected task is reading different data.
If EXAMPLE_AXIS selected it reads 3 axes values in range of -1<->1g. 
If EXAMPLE_ANGLE is slected it reads 3 angle values in range of 
-90<->90deg. EXAMPLE_TEMP reads temperature data from device in degC.

```c
void application_task ( void )
{
    switch ( example_type )
    {
        case EXAMPLE_AXIS:
        {
            inclinometer_accel_t axes_data;
            inclinometer_get_axes( &inclinometer, &axes_data );
            log_printf( &logger, "> ACCEL X[g]: %.2f\r\n", axes_data.x );
            log_printf( &logger, "> ACCEL Y[g]: %.2f\r\n", axes_data.y );
            log_printf( &logger, "> ACCEL Z[g]: %.2f\r\n", axes_data.z );
            break;
        }
        case EXAMPLE_ANGLE:
        {
            inclinometer_accel_t angle_data;
            inclinometer_get_angle( &inclinometer, &angle_data );
            log_printf( &logger, "> ANGLE X[deg]: %.2f\r\n", angle_data.x );
            log_printf( &logger, "> ANGLE Y[deg]: %.2f\r\n", angle_data.y );
            log_printf( &logger, "> ANGLE Z[deg]: %.2f\r\n", angle_data.z );
            break;
        }
        case EXAMPLE_TEMP:
        {
            float temp_data = 0;
            inclinometer_get_temperature( &inclinometer, &temp_data );
            log_printf( &logger, "> Temperature[degC]: %.2f\r\n", temp_data );
            break;
        }
        default:
        {
            log_error( &logger, " Example type." );
            break;
        }
    }
    log_printf( &logger, "*************************************\r\n" );
    Delay_ms ( 100 );
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
