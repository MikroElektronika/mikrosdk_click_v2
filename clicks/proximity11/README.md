
---
# Proximity 11 Click

> [Proximity 11 Click](https://www.mikroe.com/?pid_product=MIKROE-3689) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3689&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This appication enables usage of the proximity and ambient light sensors

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity11

### Example Key Functions

- `proximity11_cfg_setup` Config Object Initialization function. 
```c
void proximity11_cfg_setup ( proximity11_cfg_t *cfg );
``` 
 
- `proximity11_init` Initialization function. 
```c
err_t proximity11_init ( proximity11_t *ctx, proximity11_cfg_t *cfg );
```

- `proximity11_default_cfg` Click Default Configuration function. 
```c
void proximity11_default_cfg ( proximity11_t *ctx );
```

- `proximity11_get` This function reads proximity values from the desired registers. 
```c
uint8_t proximity11_get ( proximity11_t *ctx, uint8_t register_address, uint8_t *output_buffer, uint8_t n_bytes );
```
 
- `proximity11_update` This function updates data used to calculate Lux. This function should be called if changing als measurement time and als gain. 
```c
void proximity11_update ( proximity11_t *ctx );
```

- `proximity11_set_als_threshold_high` This function sets High ALS threshold value. 
```c
void proximity11_set_als_threshold_high ( proximity11_t *ctx, uint16_t threshold_value );
```

### Application Init

> Initializes I2C driver and performs device initialization

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity11_cfg_t cfg;
    uint8_t init_status;

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

    proximity11_cfg_setup( &cfg );
    PROXIMITY11_MAP_MIKROBUS( cfg, MIKROBUS_4 );
    proximity11_init( &proximity11, &cfg );

    Delay_ms ( 500 );

    init_status = proximity11_default_cfg( &proximity11 );

    if ( init_status == 1 )
    {
        log_printf( &logger, "> app init fail\r\n" );
		while( 1 );
    }
    else if ( init_status == 0 )
    {
        log_printf( &logger, "> app init done\r\n" );
    }
}
```

### Application Task

> Gets ALS and PS values and logs those values

```c
void application_task ( void )
{
    //  Task implementation

    uint16_t ps_value;
    float als_value;

    proximity11_get_ps_als_values( &proximity11, &ps_value, &als_value );

    log_printf( &logger, "PS  : %ld [count]\r\n", ps_value );
    log_printf( &logger, "ALS : %.2f [Lx]\r\n\r\n", als_value );

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
