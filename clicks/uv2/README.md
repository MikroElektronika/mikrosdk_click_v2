
---
# UV 2  Click

> [UV 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2378) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2378&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This app measures UVA and UVB data and calculates UV index level.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.UV2

### Example Key Functions

- `uv2_cfg_setup` Config Object Initialization function. 
```c
void uv2_cfg_setup ( uv2_cfg_t *cfg );
``` 
 
- `uv2_init` Initialization function. 
```c
err_t uv2_init ( uv2_t *ctx, uv2_cfg_t *cfg );
```

- `uv2_default_cfg` Click Default Configuration function. 
```c
void uv2_default_cfg ( uv2_t *ctx );
```

- `uv2_set_active_force_mode` This function set active force mode by write force mode UV_AF bit to config register of VEML6075 sesnor on UV 2 Click. 
```c
void uv2_set_active_force_mode ( uv2_t *ctx, uint8_t force_mode );
```
 
- `uv2_get_uva` This function get UVA data by read UVA register value of VEML6075 sesnor on UV 2 Click. 
```c
uint16_t uv2_get_uva ( uv2_t *ctx );
```

- `uv2_get_uvb` This function get UVB data by read UVB register value of VEML6075 sesnor on UV 2 Click. 
```c
uint16_t uv2_get_uvb ( uv2_t *ctx );
```

### Application Init

> Initializes device and sets default cinfiguration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    uv2_cfg_t cfg;

    uint8_t state_id;

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

    uv2_cfg_setup( &cfg );
    UV2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uv2_init( &uv2, &cfg );

    Delay_ms ( 100 );

    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, "       UV 2  Click      \r\n" );
    log_printf( &logger, "------------------------\r\n" );

    uv2_default_cfg( &uv2 );

    state_id = uv2_check_id( &uv2 );
    
    if ( state_id )
    {
        log_printf( &logger, "       Configured       \r\n" );
    }
    else
    {
        log_printf( &logger, "         ERROR          \r\n" );
    }

    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This is a example which demonstrates the use of UV 2 Click board.
> UV 2 Click communicates with VEML6075 sesnor via I2C by write to register and read from register.
> This example measures UVA and UVB data, calculates UV index level and writes log.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on usb uart changes for every 2 sec.

```c
void application_task ( void )
{
    uint16_t val_uva;
    uint16_t val_uvb;
    float uv_index;

    val_uva = uv2_get_uva( &uv2 );
    log_printf( &logger, " UVA data = %u \r\n", val_uva );

    val_uvb = uv2_get_uvb( &uv2 );
    log_printf( &logger, " UVB data = %u \r\n", val_uvb );

    uv_index = uv2_get_uv_index( &uv2 );
    log_printf( &logger, " UV Index = %f \r\n", uv_index );

    log_printf( &logger, "------------------------\r\n" );
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
