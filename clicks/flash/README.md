
---
# Flash Click

> [Flash Click](https://www.mikroe.com/?pid_product=MIKROE-1199) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1199&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nemanja Medakovic
- **Date**          : Nov 2019.
- **Type**          : SPI type

# Software Support

## Example Description

>
> This example demonstrates the use (control) of the FLASH memory.
>

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Flash

### Example Key Functions

- `flash_cfg_setup` Config Object Setup function. 
```c
void flash_cfg_setup ( flash_cfg_t *cfg );
```
 
- `flash_init` Click Initialization function. 
```c
flash_err_t flash_init ( flash_t *ctx, flash_cfg_t *cfg );
```

- `flash_default_cfg` Click Default Configuration function. 
```c
void flash_default_cfg ( flash_t *ctx );
```

- `flash_write_page` Page Write function. 
```c
flash_err_t flash_write_page ( flash_t *ctx, uint32_t mem_addr, spi_master_data_t *data_tx, uint16_t n_data );
```
 
- `flash_read_page` Page Read function. 
```c
flash_err_t flash_read_page ( flash_t *ctx, uint32_t mem_addr, spi_master_data_t *data_rx, uint16_t n_data );
```

- `flash_erase_sector` Sector Erase function. 
```c
flash_err_t flash_erase_sector ( flash_t *ctx, uint32_t mem_addr );
```

### Application Init

>
> Initializes all necessary peripherals and pins used by Flash Click and also
> initializes uart logger to show results.
>

```c
void application_init( void )
{
    flash_cfg_t flash_cfg;
    log_cfg_t log_cfg;

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
    flash_cfg_setup( &flash_cfg );
    FLASH_MAP_MIKROBUS( flash_cfg, MIKROBUS_1 );
    flash_init( &flash, &flash_cfg );

    //  Click reset and default configuration.
    flash_reset( &flash );
    flash_default_cfg( &flash );

    log_printf( &logger, "***  Flash Initialization Done.  ***\r\n" );
    log_printf( &logger, "************************************\r\n" );
}
```

### Application Task

>
> Executes memory data writing, reading from the memory to verify data writing
> operation and sector erasing to clear memory.
>

```c
void application_task( void )
{
    enter_data( "Mikroelektronika (MikroE)" );

    log_printf( &logger, "> Data content to be written: %s\r\n", data_buf );
    log_printf( &logger, "> Data writing to memory...\r\n" );
    flash_write_page( &flash, FLASH_MEM_ADDR_FIRST_PAGE_START, data_buf, n_data );
    log_printf( &logger, "> Done.\r\n" );

    memset( data_buf, 0, sizeof( data_buf ) );
    process_wait( );

    log_printf( &logger, "> Data reading from memory...\r\n" );
    flash_read_page( &flash, FLASH_MEM_ADDR_FIRST_PAGE_START, data_buf, n_data );
    log_printf( &logger, "> Done.\r\n> Read data content: %s\r\n", data_buf );

    process_wait( );

    log_printf( &logger, "> Sector erasing...\r\n" );
    flash_erase_sector( &flash, FLASH_MEM_ADDR_FIRST_SECTOR_START );
    log_printf( &logger, "> Done.\r\n" );

    process_wait( );
}
```

### Additional Functions

>
> - Enter Data / Allows user to enter a desired data.
> - Process Wait / Makes a delay to wait while some process be done.
>

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
