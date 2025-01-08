
---
# Proximity Click

> [Proximity Click](https://www.mikroe.com/?pid_product=MIKROE-1445) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1445&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> Measures proximity data and ambient light.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity

### Example Key Functions

- `proximity_cfg_setup` Config Object Initialization function. 
```c
void proximity_cfg_setup ( proximity_cfg_t *cfg );
``` 
 
- `proximity_init` Initialization function. 
```c
err_t proximity_init ( proximity_t *ctx, proximity_cfg_t *cfg );
```

- `proximity_default_cfg` Click Default Configuration function. 
```c
void proximity_default_cfg ( proximity_t *ctx );
```

- `proximity_write_data` Functions for write data. 
```c
void proximity_write_data ( proximity_t *ctx, uint8_t w_addr, uint8_t* wr_data, uint8_t n_len );
```
 
- `proximity_read_prox_data` Functions for reads Proximity data. 
```c
uint16_t proximity_read_prox_data ( proximity_t *ctx );
```

- `proximity_read_ambient_light` Functions for reads Ambient light. 
```c
uint16_t proximity_read_ambient_light ( proximity_t *ctx );
```

### Application Init

> Initialization driver init and sets chip on the default mode 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity_cfg_t cfg;

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

    proximity_cfg_setup( &cfg );
    PROXIMITY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity_init( &proximity, &cfg );
    proximity_set_default_mode( &proximity );
}
```

### Application Task

> Reads Proximity data and Ambient light data and logs data to USBUART every 500 ms.

```c
void application_task ( void )
{
    //  Task implementation.

    proximity_ambi_value = proximity_read_ambient_light( &proximity );
    proximity_proxi_value = proximity_read_prox_data( &proximity );

    log_printf( &logger, "Proximity:   %u\r\n", proximity_proxi_value);
    log_printf( &logger, " Ambient:   %u LUX\r\n ", proximity_ambi_value);

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
