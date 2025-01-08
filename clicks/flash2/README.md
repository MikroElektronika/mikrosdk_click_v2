
---
# Flash 2 Click

> [Flash 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2267) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2267&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the process of writing and reading data from Flash 2 Click memory.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Flash2

### Example Key Functions

- `flash2_cfg_setup` Config Object Initialization function. 
```c
void flash2_cfg_setup ( flash2_cfg_t *cfg );
``` 
 
- `flash2_init` Initialization function. 
```c
err_t flash2_init ( flash2_t *ctx, flash2_cfg_t *cfg );
```

- `flash2_default_cfg` Click Default Configuration function. 
```c
void flash2_default_cfg ( flash2_t *ctx );
```

- `flash2_global_block_unlock` The Global Block-Protection Unlock instruction. 
```c
void flash2_global_block_unlock ( flash2_t *ctx  );
```
 
- `flash2_chip_erase` The Chip-Erase instruction clears all bits. 
```c
void flash2_chip_erase ( flash2_t *ctx  );
```

- `flash2_read_generic` The Read instruction, 03H, is supported in SPI bus protocol only with clock frequencies up to 40 MHz. 
```c
void flash2_read_generic ( flash2_t *ctx, uint32_t address, uint8_t *buffer, uint32_t data_count  );
```

### Application Init

> Flash Driver Initialization, initialization of Click by setting mikorBUS to
> approprieate logic levels, performing global block unlock and chip erase functions.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    flash2_cfg_t cfg;

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

    flash2_cfg_setup( &cfg );
    FLASH2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    flash2_init( &flash2, &cfg );
    Delay_ms ( 300 );
    flash2_global_block_unlock( &flash2 );
    Delay_ms ( 400 );
    flash2_chip_erase( &flash2 );
    Delay_ms ( 300 );
}
```

### Application Task

> Writing data to Click memory and displaying the read data via UART.  

```c
void application_task ( void )
{
    log_printf( &logger, "Writing MikroE to flash memory, from address 0x015015:\r\n" );
    flash2_write_generic( &flash2, 0x015015, &wr_data[ 0 ], 9 );
    log_printf( &logger, "Reading 9 bytes of flash memory, from address 0x015015:\r\n" );
    flash2_read_generic( &flash2, 0x015015, &rd_data[ 0 ], 9 );
    log_printf( &logger, "Data read: %s\r\n", rd_data );
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
