
---
# Flash 4 Click

> [Flash 4 Click](https://www.mikroe.com/?pid_product=MIKROE-3191) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3191&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Flash 4 Click board. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Flash4

### Example Key Functions

- `flash4_cfg_setup` Config Object Initialization function. 
```c
void flash4_cfg_setup ( flash4_cfg_t *cfg );
``` 
 
- `flash4_init` Initialization function. 
```c
err_t flash4_init ( flash4_t *ctx, flash4_cfg_t *cfg );
```

- `flash4_generic_transfer` Generic transfer function. 
```c
void flash4_generic_transfer ( flash4_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );
```

- `flash4_read_manufacturer_id` Function for read Manufacturer ID. 
```c
void flash4_read_manufacturer_id ( flash4_t *ctx, uint8_t *device_id );
```
 
- `flash4_write_command` Write command function. 
```c
void flash4_write_command ( flash4_t *ctx, uint8_t cmd );
```

- `flash4_read_flash_4` Read Flash with 4 byte address function. 
```c
void flash4_read_flash_4 ( flash4_t *ctx, uint8_t *out_data, uint32_t addr, uint8_t n_data );
```

### Application Init

> Initializes the driver and enables the Click board, then checks the communication by reading the device and manufacturer IDs.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    flash4_cfg_t cfg;

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

    flash4_cfg_setup( &cfg );
    FLASH4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    flash4_init( &flash4, &cfg );
    
    flash4_reset( &flash4 );
    
    Delay_ms ( 1000 );
    
    flash4_read_manufacturer_id( &flash4, device_id );
    
    if ( device_id[ 0 ] != FLASH4_MANUFACTURER_ID || device_id[ 1 ] != FLASH4_DEVICE_ID )
    {
        log_error( &logger, "WRONG ID READ" );
        log_printf( &logger, "Please restart your system.\r\n" );
        for( ; ; );
    }
    Delay_ms ( 1000 );
}
```

### Application Task

> Erases sector memory starting from 0x00001234 address, then writes a desired message
> to the same address. After that, verifies if the message is written correctly by reading 
> it back and displaying it to the USB UART every 5 seconds.

```c
void application_task ( void )
{
    char read_buffer[ 10 ] = { 0 };

    flash4_write_command( &flash4, FLASH4_CMD_WRITE_ENABLE_WREN );
    log_printf( &logger, "--- Erase chip --START-- \r\n" );
    flash4_sector_erase_4( &flash4,  0x00001234 );
    while ( flash4_check_wip( &flash4 ) );
    log_printf( &logger, "--- Erase chip --DONE-- \r\n" );
    
    flash4_write_command( &flash4, FLASH4_CMD_WRITE_ENABLE_WREN );
    flash4_page_program_4( &flash4, DEMO_MESSAGE, 0x00001234, strlen( DEMO_MESSAGE ) );
    while ( flash4_check_wip( &flash4 ) );
    Delay_100ms( );
    
    flash4_read_flash_4( &flash4, read_buffer, 0x00001234, strlen( DEMO_MESSAGE ) );
    while ( flash4_check_wip( &flash4 ) );
    
    log_printf( &logger, "--- Read buffer : %s\r\n", read_buffer );

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
