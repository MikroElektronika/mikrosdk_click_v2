
---
# MRAM 4 Click

> MRAM 4 Click is a compact add-on board representing a magneto-resistive random-access memory solution. This board features the EM064LX, an industrial STT-MRAM persistent memory from Everspin Technologies. It is a 64Mb MRAM IC RAM and can achieve up to 200MHz as a single and double data rate (STR/DTR). The MRAM technology is analog to Flash technology with SRAM-compatible read/write timings (Persistent SRAM, P-SRAM), where data is always non-volatile. It also has a hardware write-protection feature and performs read and write operations with data retention for ten years and unlimited read, write, and erase operations for the supported life of the chip.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mram4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/mram-4-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the MRAM 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for MRAM 4 Click driver.

#### Standard key functions :

- `mram4_cfg_setup` Config Object Initialization function.
```c
void mram4_cfg_setup ( mram4_cfg_t *cfg );
```

- `mram4_init` Initialization function.
```c
err_t mram4_init ( mram4_t *ctx, mram4_cfg_t *cfg );
```

- `mram4_default_cfg` Click Default Configuration function.
```c
err_t mram4_default_cfg ( mram4_t *ctx );
```

#### Example key functions :

- `mram4_memory_write` MRAM 4 memory write function.
```c
err_t mram4_memory_write ( mram4_t *ctx, uint32_t mem_addr, uint8_t *data_in, uint8_t len );
```

- `mram4_memory_read` MRAM 4 memory read function.
```c
err_t mram4_memory_read ( mram4_t *ctx, uint32_t mem_addr, uint8_t *data_out, uint8_t len );
```

- `mram4_block_erase` MRAM 4 block erase function.
```c
err_t mram4_block_erase ( mram4_t *ctx, uint8_t cmd_block_erase, uint32_t mem_addr );
```

## Example Description

> This example demonstrates the use of MRAM 4 Click board.
> The demo app writes specified data to the memory and reads it back.

**The demo application is composed of two sections :**

### Application Init

> The initialization of SPI module, log UART, and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mram4_cfg_t mram4_cfg;  /**< Click config object. */

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
    mram4_cfg_setup( &mram4_cfg );
    MRAM4_MAP_MIKROBUS( mram4_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == mram4_init( &mram4, &mram4_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MRAM4_ERROR == mram4_default_cfg ( &mram4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application writes a desired number of bytes to the memory 
> and then verifies if it is written correctly
> by reading from the same memory location and displaying the memory content.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    uint8_t data_buf[ 128 ] = { 0 };
    log_printf( &logger, " Memory address: 0x%.6LX\r\n", ( uint32_t ) STARTING_ADDRESS );
    if ( MRAM4_OK == mram4_block_erase( &mram4, MRAM4_CMD_ERASE_4KB, STARTING_ADDRESS ) )
    {
        log_printf( &logger, " Erase memory block (4KB)\r\n" );
        Delay_ms ( 100 );
    }
    
    memcpy( data_buf, DEMO_TEXT_MESSAGE_1, strlen( DEMO_TEXT_MESSAGE_1 ) );    
    if ( MRAM4_OK == mram4_memory_write( &mram4, STARTING_ADDRESS, data_buf, sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    
    memset( data_buf, 0, sizeof( data_buf ) );
    if ( MRAM4_OK == mram4_memory_read( &mram4, STARTING_ADDRESS, data_buf, sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Read data: %s\r\n", data_buf );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    log_printf( &logger, " ----------------------------\r\n" );
    
    log_printf( &logger, " Memory address: 0x%.6LX\r\n", ( uint32_t ) STARTING_ADDRESS );
    if ( MRAM4_OK == mram4_block_erase( &mram4, MRAM4_CMD_ERASE_4KB, STARTING_ADDRESS ) )
    {
        log_printf( &logger, " Erase memory block (4KB)\r\n" );
    }
    
    memcpy( data_buf, DEMO_TEXT_MESSAGE_2, strlen( DEMO_TEXT_MESSAGE_2 ) );
    if ( MRAM4_OK == mram4_memory_write( &mram4, STARTING_ADDRESS, data_buf, sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    
    memset( data_buf, 0, sizeof( data_buf ) );
    if ( MRAM4_OK == mram4_memory_read( &mram4, STARTING_ADDRESS, data_buf, sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Read data: %s\r\n", data_buf );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    log_printf ( &logger, " ----------------------------\r\n" );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.MRAM4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
