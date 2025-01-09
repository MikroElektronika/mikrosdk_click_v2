
---
# Grid Eye Click

> [Grid-Eye Click](https://www.mikroe.com/?pid_product=MIKROE-2539) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2539&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> 64 individual thermal sensors build an image on a display. The detecting distance is 5m.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Grideye

### Example Key Functions

- `grideye_cfg_setup` Config Object Initialization function. 
```c
void grideye_cfg_setup ( grideye_cfg_t *cfg );
``` 
 
- `grideye_init` Initialization function. 
```c
err_t grideye_init ( grideye_t *ctx, grideye_cfg_t *cfg );
```

- `grideye_default_cfg` Click Default Configuration function. 
```c
void grideye_default_cfg ( grideye_t *ctx );
```

- `grideye_generic_write` Generic write function. 
```c
void grideye_generic_write ( grideye_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```
 
- `grideye_generic_read` Generic read function. 
```c
void grideye_generic_read ( grideye_t *ctx,  uint8_t reg, uint8_t *data_buf, uint8_t len );
```

- `grideye_write_data` Write data function. 
```c
void grideye_write_data ( grideye_t *ctx, uint8_t wr_addr, uint16_t wr_data );
```

### Application Init

> Initalizes I2C driver, applies default settings, and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    grideye_cfg_t cfg;

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

    grideye_cfg_setup( &cfg );
    
    GRIDEYE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    grideye_init( &grideye, &cfg );

    grideye_default_cfg ( &grideye );
}
```

### Application Task

> This example demonstrates the use of Grid-EYE Click board by reading full grid and displaying values via USART terminal.

```c
void application_task ( void )
{
    uint8_t i;
    uint8_t j;
    uint16_t grid_array[ 64 ];
    uint16_t grid_array_tmp;

    grideye_read_grid( &grideye, &grid_array );

    for( i = 1; i < 9; i++ )
    {
        for( j = 1; j < 9; j++ )
        {
            log_printf( &logger, "| " );
            grid_array_tmp = grid_array[ i * j ];
            
            log_printf( &logger, "%d ", grid_array_tmp );
        }
        log_printf( &logger, " \r\n" );
        log_printf( &logger, "-------------------------------------- \r\n" );
    }
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
