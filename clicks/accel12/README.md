
---
# Accel 12 Click

> [Accel 12 Click](https://www.mikroe.com/?pid_product=MIKROE-3464) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3464&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application allows acceleration measurement in three perpendicular axes.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel12

### Example Key Functions

- `accel12_cfg_setup` Config Object Initialization function. 
```c
void accel12_cfg_setup ( accel12_cfg_t *cfg );
``` 
 
- `accel12_init` Initialization function. 
```c
err_t accel12_init ( accel12_t *ctx, accel12_cfg_t *cfg );
```

- `accel12_default_cfg` Click Default Configuration function. 
```c
void accel12_default_cfg ( accel12_t *ctx );
```

- `accel12_configuration` Functions for configuration one register. 
```c
void accel12_configuration( accel12_t *ctx, uint8_t reg, uint8_t data_in );
```
 
- `accel12_get_one_axis` Functions for read one Accel axis data. 
```c
int16_t accel12_get_one_axis( accel12_t *ctx, uint8_t axis );
```

- `accel12_get_axis_data` Functions for read Accel axis data. 
```c
void accel12_get_axis_data (  accel12_t *ctx, int16_t *x_axis, int16_t *y_axis, int16_t *z_axis );
```

### Application Init

> Initialization driver init and configuration Accel measuremen and Tap detection interrupt

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    accel12_cfg_t cfg;
    uint8_t temp;

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

    accel12_cfg_setup( &cfg );
    ACCEL12_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel12_init( &accel12, &cfg );

    accel12_default_cfg( &accel12 );
    
    log_printf( &logger, "--- Start measurement --- \r\n" );
}
```

### Application Task

> Reads the acceleration data in 3 axis and detects the tap on the axes. All data logs on the USBUART every 1.5sec.

```c
void application_task ( void )
{
    int16_t X_Axis;
    int16_t Y_Axis;
    int16_t Z_Axis;
    uint8_t tap;

    /* Accelerometer measurement */
    accel12_get_axis_data( &accel12, &X_Axis, &Y_Axis, &Z_Axis );

    log_printf( &logger, " X axis : %d \r\n", X_Axis );

    log_printf( &logger, " Y axis : %d \r\n", Y_Axis );

    log_printf( &logger, " Z axis : %d \r\n", Z_Axis );

    /* TAP interrupt */
    tap = accel12_get_tap_detection( &accel12 );
    switch ( tap )
    {
        case 1:
        {
            log_printf( &logger, " X positive \r\n" );
            break;
        }
        case 2:
        {
            log_printf( &logger, " Y positive \r\n" );
            break;
        }
        case 3:
        {
            log_printf( &logger, " Z positive \r\n" );
            break;
        }
        case 4:
        {
            log_printf( &logger, " X negative \r\n" );
            break;
        }
        case 5:
        {
            log_printf( &logger, " Y negative \r\n" );
            break;
        }
        case 6:
        {
            log_printf( &logger, " Z negative \r\n" );
            break;
        }
    }
    log_printf( &logger, " -------------------------------- \r\n" );
    Delay_ms ( 1000 );
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
