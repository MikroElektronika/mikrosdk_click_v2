
---
# Flash 9 Click

> [Flash 9 Click](https://www.mikroe.com/?pid_product=MIKROE-4987) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4987&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Flash 9 Click board by writing specified data to the memory and reading it back.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Flash9

### Example Key Functions

- `flash9_cfg_setup` Config Object Initialization function.
```c
void flash9_cfg_setup ( flash9_cfg_t *cfg );
```

- `flash9_init` Initialization function.
```c
err_t flash9_init ( flash9_t *ctx, flash9_cfg_t *cfg );
```

- `flash9_default_cfg` Click Default Configuration function.
```c
err_t flash9_default_cfg ( flash9_t *ctx );
```

- `flash9_erase_memory` This function erases the selected amount of memory which contains the selected address.
```c
err_t flash9_erase_memory ( flash9_t *ctx, uint8_t erase_cmd, uint32_t address );
```

- `flash9_memory_write` This function writes a desired number of data bytes to the memory starting from the selected address.
```c
err_t flash9_memory_write ( flash9_t *ctx, uint32_t address, uint8_t *data_in, uint16_t len );
```

- `flash9_memory_read_fast` This function reads a desired number of data bytes from the memory starting from the selected address performing the fast read command.
```c
err_t flash9_memory_read_fast ( flash9_t *ctx, uint32_t address, uint8_t *data_out, uint16_t len );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    flash9_cfg_t flash9_cfg;  /**< Click config object. */

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
    flash9_cfg_setup( &flash9_cfg );
    FLASH9_MAP_MIKROBUS( flash9_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == flash9_init( &flash9, &flash9_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( FLASH9_ERROR == flash9_default_cfg ( &flash9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Erases the memory sector and then writes a desired number of data bytes to the memory
and verifies that it is written correctly by reading from the same memory location and 
displaying the memory content on the USB UART.

```c
void application_task ( void )
{
    uint8_t data_buf[ 128 ] = { 0 };
    if ( FLASH9_OK == flash9_erase_memory ( &flash9, FLASH9_CMD_SECTOR_ERASE_WITH_4BYTE_ADDRESS, 
                                            STARTING_ADDRESS ) )
    {
        log_printf ( &logger, "Sector from address 0x%.8LX has been erased!\r\n", STARTING_ADDRESS );
    }
    Delay_ms ( 500 );
    
    if ( FLASH9_OK == flash9_memory_write ( &flash9, STARTING_ADDRESS, DEMO_TEXT_MESSAGE, 
                                            strlen ( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf ( &logger, "Data written to address 0x%.8LX: \"%s\"\r\n", STARTING_ADDRESS, 
                                                                  ( char * ) DEMO_TEXT_MESSAGE );
    }
    Delay_ms ( 500 );

    if ( FLASH9_OK == flash9_memory_read_fast ( &flash9, STARTING_ADDRESS, data_buf, 
                                                strlen ( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf ( &logger, "Data read from address 0x%.8LX: \"%s\"\r\n\n", STARTING_ADDRESS, 
                                                                              data_buf );
    }
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
