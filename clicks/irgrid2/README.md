
---
# IR Grid 2 Click

> [IR Grid 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3194) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3194&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> The demo application displays a reading of ambient temperature and a 32x24 pixel object temperature matrix.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IRGrid2

### Example Key Functions

- `irgrid2_cfg_setup` Config Object Initialization function.
```c
void irgrid2_cfg_setup ( irgrid2_cfg_t *cfg );
```

- `irgrid2_init` Initialization function.
```c
err_t irgrid2_init ( irgrid2_t *ctx, irgrid2_cfg_t *cfg );
```

- `irgrid2_default_cfg` Click Default Configuration function.
```c
void irgrid2_default_cfg ( irgrid2_t *ctx );
```

- `irgrid2_generic_write` This function reads a desired number of data bytes starting from the selected register by using I2C serial interface.
```c
void irgrid2_generic_write ( irgrid2_t *ctx, uint16_t reg, uint8_t *data_buf, uint16_t len );
```

- `irgrid2_get_frame_data` This function is used for getting frame data.
```c
uint16_t irgrid2_get_frame_data ( irgrid2_t *ctx, uint16_t *frame_data );
```

- `irgrid2_get_pixel_temperature` This function is used for getting pixels temperature.
```c
void irgrid2_get_pixel_temperature ( irgrid2_t *ctx, float *temp_ambient, float *pixel_temp );
```

### Application Init

> Configures the Click and log objects and sets the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irgrid2_cfg_t irgrid2_cfg;  /**< Click config object. */

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

    // Click initialization.
    irgrid2_cfg_setup( &irgrid2_cfg );
    IRGRID2_MAP_MIKROBUS( irgrid2_cfg, MIKROBUS_1 );
    err_t init_flag = irgrid2_init( &irgrid2, &irgrid2_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    irgrid2_default_cfg ( &irgrid2 );
    Delay_ms ( 1000 );
    log_info( &logger, "---- Start measurement ----" );
}
```

### Application Task

> Reads the temperature of all pixels every 500ms and displays it on USB UART in a form of a 32x24 matrix.

```c
void application_task ( void ) 
{
    float px_matrix[ 768 ];
    float temp_ambient;

    irgrid2_get_pixel_temperature( &irgrid2, &temp_ambient, px_matrix );

    log_printf( &logger, "\r\n>> Pixel temperature matrix 32x24 <<\r\n" );
    for ( uint16_t cnt = 1 ; cnt < 769 ; cnt++) {
        log_printf( &logger, "%.2f", px_matrix[ cnt - 1 ] );
        if ( ( ( cnt % 32 ) == 0 ) ) {
            log_printf( &logger, "\r\n" );
        } else {
            log_printf( &logger, " | " );
        }
    }
    log_printf( &logger, "\r\n** Ambient (sensor) temperature is %.2f Celsius\r\n", temp_ambient );
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
