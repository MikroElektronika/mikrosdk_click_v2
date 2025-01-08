
---
# UVB Click

> [UVB Click](https://www.mikroe.com/?pid_product=MIKROE-4145) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4145&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Mikroe Team
- **Date**          : Sep 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This Click is ultraviolet sensing board, capable of measuring UV index between 0 to 16. UVB Click supports integrated functions of ultraviolet light sensors.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.UVB

### Example Key Functions

- `uvb_cfg_setup` Config Object Initialization function.
```c
void uvb_cfg_setup ( uvb_cfg_t *cfg );
```

- `uvb_init` Initialization function.
```c
err_t uvb_init ( uvb_t *ctx, uvb_cfg_t *cfg );
```

- `uvb_default_cfg` Click Default Configuration function.
```c
err_t uvb_default_cfg ( uvb_t *ctx );
```

- `uvb_configuration` Configuration register.
```c
void uvb_configuration ( uvb_t *ctx, uint8_t reg, uint8_t cfg );
```

- `uvb_read_byte` Read one byte data from register.
```c
uint8_t uvb_read_byte ( uvb_t *ctx, uint8_t reg );
```

- `uvb_get_uv_data` Get UVB data.
```c
uint16_t uvb_get_uv_data ( uvb_t *ctx );
```

### Application Init

> Initialization driver init, check communication and configuration module for measurement.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    uvb_cfg_t uvb_cfg;  /**< Click config object. */

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
    uvb_cfg_setup( &uvb_cfg );
    UVB_MAP_MIKROBUS( uvb_cfg, MIKROBUS_1 );
    err_t init_flag = uvb_init( &uvb, &uvb_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    uvb_default_cfg ( &uvb );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------------\r\n" );
}
```

### Application Task

> Reads UVB data and logs to the USBUART every 1500ms.

```c
void application_task ( void ) 
{
    uvb_data = uvb_get_uv_data( &uvb );

    log_printf( &logger, ">> UVB data: %d\r\n", uvb_data );

    log_printf( &logger, "--------------------------\r\n" );
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
