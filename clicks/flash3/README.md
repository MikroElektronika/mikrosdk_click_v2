
---
# Flash 3 Click

> [Flash 3 Click](https://www.mikroe.com/?pid_product=MIKROE-2374) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2374&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This applicaion adding more flash memory. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Flash3

### Example Key Functions

- `flash3_cfg_setup` Config Object Initialization function. 
```c
void flash3_cfg_setup ( flash3_cfg_t *cfg );
``` 
 
- `flash3_init` Initialization function. 
```c
err_t flash3_init ( flash3_t *ctx, flash3_cfg_t *cfg );
```

- `flash3_generic_transfer` Generic transfer function. 
```c
void flash3_generic_transfer ( flash3_t *ctx, spi_master_transfer_data_t *block );
```

- `flash3_pause` Pause function. 
```c
void flash3_pause ( flash3_t *ctx );
```
 
- `flash3_unpause` Unpause function. 
```c
void flash3_unpause ( flash3_t *ctx );
```

### Application Init

> Initalizes device, Flash 3 Click board and makes an initial log. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    flash3_cfg_t cfg;

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

    flash3_cfg_setup( &cfg );
    FLASH3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    flash3_init( &flash3, &cfg );

    Delay_ms ( 100 );
    log_printf( &logger, "------------------- \r\n" );
    log_printf( &logger, "  Flash  3  Click  \r\n" );
    log_printf( &logger, "-------------------\r\n" );
    flash3_setting( &flash3 );
    Delay_ms ( 100 );
    log_printf( &logger, "   Initialized     \r\n" );
    log_printf( &logger, "------------------- \r\n" );
}
```

### Application Task

> This is an example that shows the capabilities of the Flash 3 Click by
writing into memory array of a Flash 3 Click board and reading same data from memory array.

```c
void application_task ( void )
{
    char val_in[ 8 ] = { 0x4D, 0x49, 0x4B, 0x52, 0x4F, 0x45, 0x00 };
    char val_out[ 8 ] = { 0 };

    log_printf( &logger, "\r\n ____________________ \r\n" );
    log_printf( &logger, "Begin demonstration! \r\n\r\n" );
    
    flash3_write( &flash3, 0x000000, &val_in[ 0 ], 6 );
    log_printf( &logger, "Written : %s\r\n", val_in );
    log_printf( &logger, "------------------ \r\n" );
    Delay_ms ( 100 );

    flash3_normal_read( &flash3, 0x000000, &val_out[ 0 ], 6 );
    log_printf( &logger, "Read : %s\r\n", val_out );
    log_printf( &logger, "------------------ \r\n" );
    Delay_ms ( 100 );

    flash3_sector_erase( &flash3, 0x000000 );
    log_printf( &logger, "Erased!\r\n" );
    log_printf( &logger, "------------------ \r\n"  );
    Delay_ms ( 500 );

    flash3_fast_read( &flash3, 0x000000, &val_out[ 0 ], 6 );
    log_printf( &logger, "Read : %s\r\n", val_out );
    log_printf( &logger, "------------------ \r\n" );
    Delay_ms ( 100 );

    log_printf( &logger, "Demonstration over!" );
    log_printf( &logger, "\r\n ___________________ \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
