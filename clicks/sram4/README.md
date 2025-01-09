
---
# SRAM 4 Click

> [SRAM 4 Click](https://www.mikroe.com/?pid_product=MIKROE-4835) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4835&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka FIlipovic
- **Date**          : Aug 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example application showcases ability of device
ability to manipulate with memory( writing and reading data ).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SRAM4

### Example Key Functions

- `sram4_cfg_setup` Config Object Initialization function.
```c
void sram4_cfg_setup ( sram4_cfg_t *cfg );
```

- `sram4_init` Initialization function.
```c
err_t sram4_init ( sram4_t *ctx, sram4_cfg_t *cfg );
```

- `sram4_default_cfg` Click Default Configuration function.
```c
err_t sram4_default_cfg ( sram4_t *ctx );
```

- `sram4_memory_read` Read data from memory.
```c
err_t sram4_memory_read ( sram4_t *ctx, uint16_t memory_adr, uint8_t *read_data, uint8_t read_len );
```

- `sram4_memory_write` Write data to memory.
```c
err_t sram4_memory_write ( sram4_t *ctx, uint16_t memory_adr, uint8_t *write_data, uint8_t write_len );
```

- `sram4_generic_command` Command writing function.
```c
err_t sram4_generic_command ( sram4_t *ctx, uint8_t cmd );
```

### Application Init

> Initialization of communication modules(SPI, UART) and additional 
pins. Reads ID and checks if it matches with SRAM4_DEVICE_ID to 
check communication. Then clears protection from memory access.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    sram4_cfg_t sram4_cfg;  /**< Click config object. */

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
    sram4_cfg_setup( &sram4_cfg );
    SRAM4_MAP_MIKROBUS( sram4_cfg, MIKROBUS_1 );
    err_t init_flag  = sram4_init( &sram4, &sram4_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    if ( sram4_default_cfg ( &sram4 ) )
    {
        log_error( &logger, " Default configuration. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Writes 3 times to memory with length of data offset in memory addres.
Then reads 2 times first 2 data written should be read in one read,
and 3rd write should be read separately.

```c
void application_task ( void )
{
    char read_buf[ 100 ] = { 0 };
    char click_name[ ] = "SRAM 4";
    char company_name[ ] = "MikroE";
    char product_name[ ] = " Click board";
    static const uint16_t START_ADR = 0x0001;
    uint16_t mem_adr = START_ADR;
    
    //Write Data
    sram4_memory_write( &sram4, mem_adr, click_name, strlen( click_name ) );
    mem_adr += strlen( click_name );
    sram4_memory_write( &sram4, mem_adr, product_name, strlen( product_name ) );
    mem_adr += strlen( product_name );
    sram4_memory_write( &sram4, mem_adr, company_name, strlen( company_name ) );
    
    //Read Data
    mem_adr = START_ADR;
    sram4_memory_read( &sram4, mem_adr, read_buf, strlen( click_name ) + strlen( product_name ) );
    log_printf( &logger, " > Read Data from 0x%.4X memory address: %s\r\n", mem_adr, read_buf );
    memset( read_buf, 0, strlen( read_buf ) );
    mem_adr += strlen(click_name) + strlen( product_name );
    sram4_memory_read( &sram4, mem_adr, read_buf, strlen( company_name ) );
    log_printf( &logger, " > Read Data from 0x%.4X memory address: %s\r\n", mem_adr, read_buf );
    log_printf( &logger, "**********************************************************************\r\n" );
    
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
