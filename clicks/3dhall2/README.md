
---
# 3D Hall 2 Click

> [3D Hall 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3190) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3190&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This example reads X/Y/Z hall axis and temperature data and converts it to human readable format.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.3dHall2

### Example Key Functions

- `c3dhall2_cfg_setup` Config Object Initialization function.
```c
void c3dhall2_cfg_setup ( c10x10rgb_cfg_t *cfg );
```

- `c3dhall2_init` Initialization function.
```c
err_t c3dhall2_init ( c3dhall2_t *ctx, c3dhall2_cfg_t *cfg );
```

- `c3dhall2_default_cfg` Default configuration initialization function.
```c
err_t c3dhall2_default_cfg( c3dhall2_t *ctx );
```

- `c3dhall2_read_data` This function reads data from register.
```c
err_t c3dhall2_read_data ( c3dhall2_t *ctx, uint8_t *data_buf, uint16_t len );
```

- `c3dhall2_get_axis_temp_data` This function gets temperature and axis data.
```c
err_t c3dhall2_get_axis_temp_data ( c3dhall2_t *ctx, float *axis_data, float *temp_data );
```

- `c3dhall2_configuration` This function configures the chip for measurement.
```c
err_t c3dhall2_configuration ( c3dhall2_t *ctx, uint8_t settings1, uint8_t settings2 );
```

### Application Init

> Initializes the driver and configures the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c3dhall2_cfg_t cfg;

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
    c3dhall2_cfg_setup( &cfg );
    C3DHALL2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3dhall2_init( &c3dhall2, &cfg );
    c3dhall2_default_cfg( &c3dhall2 );
}
```

### Application Task

> Reads X/Y/Z hall axis and Temperature data. All data logs on the USBUART every 200ms.

```c
void application_task ( void )
{
    float xyz_axis[ 3 ] = { 0 };
    float temperature = 0;
    if ( C3DHALL2_OK == c3dhall2_get_axis_temp_data( &c3dhall2, &xyz_axis[ 0 ], &temperature ) )
    {
        log_printf( &logger, " Axis X: %.2f mT\r\n", xyz_axis[ 0 ] );
        log_printf( &logger, " Axis Y: %.2f mT\r\n", xyz_axis[ 1 ] );
        log_printf( &logger, " Axis Z: %.2f mT\r\n", xyz_axis[ 2 ] );
        log_printf( &logger, " Temperature: %.2f C\r\n\n", temperature );
        Delay_ms ( 200 );
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
