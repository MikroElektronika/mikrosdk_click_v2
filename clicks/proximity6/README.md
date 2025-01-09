
---
# Proximity 6 Click

> [Proximity 6 Click](https://www.mikroe.com/?pid_product=MIKROE-3048) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3048&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application demonstrates the use of Proximity 6 Click board by reading and displaying the raw data measurements from 4 photodiode channels.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity6

### Example Key Functions

- `proximity6_cfg_setup` Config Object Initialization function.
```c
void proximity6_cfg_setup ( proximity6_cfg_t *cfg ); 
```

- `proximity6_init` Initialization function.
```c
err_t proximity6_init ( proximity6_t *ctx, proximity6_cfg_t *cfg );
```

- `proximity6_default_cfg` Click Default Configuration function.
```c
err_t proximity6_default_cfg ( proximity6_t *ctx );
```

- `proximity6_read_data` Function reads proximity data when one or more data register is updated.
```c
err_t proximity6_read_data( proximity6_t *ctx, proximity6_data_t *axis_out );
```

- `proximity6_generic_write` This function writes data to the desired register.
```c
err_t proximity6_generic_write ( proximity6_t *ctx, uint8_t reg, uint16_t *data_buf, uint8_t len );
```

- `proximity6_generic_read` This function reads data from the desired register.
```c
err_t proximity6_generic_read ( proximity6_t *ctx, uint8_t reg, uint16_t *data_out, uint8_t len );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity6_cfg_t proximity6_cfg;  /**< Click config object. */

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
    proximity6_cfg_setup( &proximity6_cfg );
    PROXIMITY6_MAP_MIKROBUS( proximity6_cfg, MIKROBUS_1 );
    if ( PROXIMITY6_ERROR == proximity6_init( &proximity6, &proximity6_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY6_ERROR == proximity6_default_cfg ( &proximity6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the raw data measurements from 4 photodiode channels and displays the results on the USB UART every 200ms approximately.

```c
void application_task ( void )
{
    proximity6_data_t axis_data;
    if ( PROXIMITY6_OK == proximity6_read_data( &proximity6, &axis_data ) )
    {
        log_printf( &logger, " X1: %u\r\n", axis_data.val_x1 );
        log_printf( &logger, " X2: %u\r\n", axis_data.val_x2 );
        log_printf( &logger, " Y1: %u\r\n", axis_data.val_y1 );
        log_printf( &logger, " Y2: %u\r\n\n", axis_data.val_y2 );
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
