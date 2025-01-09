
---
# Compass 3 Click

> [Compass 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4063) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4063&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jovan Stajkovic
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> 
> This demoapp measures the magnetic field surrounding the device.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Compass3

### Example Key Functions

- `compass3_cfg_setup` Config Object Initialization function. 
```c
void compass3_cfg_setup ( compass3_cfg_t *cfg );
``` 
 
- `compass3_init` Initialization function. 
```c
err_t compass3_init ( compass3_t *ctx, compass3_cfg_t *cfg );
```

- `compass3_default_cfg` Click Default Configuration function. 
```c
void compass3_default_cfg ( compass3_t *ctx );
```

- `compass3_full_measurement` Measures magnetic field surrounding the device. 
```c
void compass3_full_measurement ( compass3_t *ctx, float *x_val, float *y_val, float *z_val );
```
 
- `compass3_read_temp` Function is used to measure temperature. 
```c
float compass3_read_temp ( compass3_t *ctx );
```

- `compass3_check_int` Function checks interrupt occurence. 
```c
uint8_t compass3_check_int ( compass3_t *ctx );
```

### Application Init

>
> Initalizes I2C driver and Click driver, performs check, applies default 
> setup and writes an initial log.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    compass3_cfg_t cfg;

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
    log_printf( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    compass3_cfg_setup( &cfg );
    COMPASS3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    compass3_init( &compass3, &cfg );
    Delay_ms ( 100 );
    
    compass3_generic_read( &compass3, COMPASS3_DEVICE_ID, &test_val, 1 );

    if ( test_val == COMPASS3_DEVICE_ID_NUM )
    {
        log_printf( &logger, "--------------------\r\n" );
        log_printf( &logger, "   Compass 3 Click  \r\n" );
        log_printf( &logger, "--------------------\r\n" );
    }
    else
    {
        log_printf( &logger, "   Fatal error!!!   \r\n" );
        for ( ; ; );
    }

    compass3_default_cfg ( &compass3 );
    Delay_ms ( 100 );
}
```

### Application Task

>
> This example demonstrates the use of 
> Compass 3 Click board by measuring the magnetic field surrounding the device.
> 

```c
void application_task ( void )
{
    if ( compass3_check_int( &compass3 ) == COMPASS3_INTERRUPT )
    {
        compass3_full_measurement ( &compass3, &x_val, &y_val, &z_val );

        log_printf( &logger,"  X-axis : %2.f mG\r\n", x_val );
        log_printf( &logger,"  Y-axis : %2.f mG\r\n", y_val );
        log_printf( &logger,"  Z-axis : %2.f mG\r\n", z_val );

        Delay_ms ( 1000 );
        log_printf( &logger, "--------------------\r\n" );
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
