
---
# SQI FLASH Click

> [SQI FLASH Click](https://www.mikroe.com/?pid_product=MIKROE-2828) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2828&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This is an example that demonstrates the use of the SQI FLASH Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SqiFlash

### Example Key Functions

- `sqiflash_cfg_setup` Config Object Initialization function.
```c
void sqiflash_cfg_setup ( sqiflash_cfg_t *cfg );
```

- `sqiflash_init` Initialization function.
```c
err_t sqiflash_init ( sqiflash_t *ctx, sqiflash_cfg_t *cfg );
```

- `sqiflash_write_generic` SQI FLASH Write.
```c
void sqiflash_write_generic( sqiflash_t *ctx, uint32_t address, uint8_t *buffer, uint32_t data_count );
```

- `sqiflash_read_generic` SQI FLASH Read.
```c
void sqiflash_read_generic( sqiflash_t *ctx, uint32_t address, uint8_t *buffer, uint32_t data_count );
```

- `sqiflash_global_block_unlock` SQI FLASH Global Block Unlock.
```c
void sqiflash_global_block_unlock( sqiflash_t *ctx );
```

### Application Init

> SQI FLASH Driver Initialization, initializes the Click by setting mikroBUS to
> approprieate logic levels, performing global block unlock and chip erase functions,
> reads manufacturer ID, memory type and device ID and logs it on USB UART terminal.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    sqiflash_cfg_t sqiflash_cfg;  /**< Click config object. */

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
    sqiflash_cfg_setup( &sqiflash_cfg );
    SQIFLASH_MAP_MIKROBUS( sqiflash_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == sqiflash_init( &sqiflash, &sqiflash_cfg ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    Delay_ms ( 300 );
    sqiflash_global_block_unlock( &sqiflash );
    Delay_ms ( 400 );
    sqiflash_chip_erase( &sqiflash );
    Delay_ms ( 300 );
    
    device_manufac = sqiflash_device_manufac( &sqiflash );
    log_printf( &logger, " Manufacturer ID: 0x%.2X\r\n", ( uint16_t ) device_manufac );
    device_type = sqiflash_device_type( &sqiflash );
    log_printf( &logger, " Memory Type: 0x%.2X\r\n", ( uint16_t ) device_type );
    device_id = sqiflash_device_id( &sqiflash );
    log_printf( &logger, " Device ID: 0x%.2X\r\n", ( uint16_t ) device_id );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Writing data to Click memory and displaying the read data via UART.

```c
void application_task ( void ) 
{
    log_printf( &logger, " Writing data to address: 0x%.6LX\r\n", address );
    sqiflash_write_generic( &sqiflash, address, wr_data, 9 );
    log_printf( &logger, " Written data: %s", wr_data );
    log_printf( &logger, "\r\n Reading data from address: 0x%.6LX\r\n", address );
    sqiflash_read_generic( &sqiflash, address, rd_data, 9 );
    log_printf( &logger, " Read data: %s", rd_data );
    log_printf( &logger, "-------------------------------------\r\n" );
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
