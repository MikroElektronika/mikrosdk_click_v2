\mainpage Main Page

---
# Flash 11 Click

> Flash 11 Click is a compact add-on board representing a highly reliable memory solution. 
> This board features the AT25SF321B, a 32-Mbit SPI serial Flash memory with Dual I/O 
> and Quad I/O support from Dialog Semiconductor. It is designed for applications 
> in which the program code is shadowed from Flash memory into embedded or external RAM 
> for execution and where small amounts of data are stored and updated locally in the Flash memory. 
> It has a flexible and optimized erase architecture for code and data storage applications, 
> non-volatile protection, three specialized protected programmable 256-byte OTP security registers, 
> and a 64-bit factory programmable UID register.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/flash11_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/flash-11-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : May 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the Flash 11 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Flash 11 Click driver.

#### Standard key functions :

- `flash11_cfg_setup` Config Object Initialization function.
```c
void flash11_cfg_setup ( flash11_cfg_t *cfg );
```

- `flash11_init` Initialization function.
```c
err_t flash11_init ( flash11_t *ctx, flash11_cfg_t *cfg );
```

- `flash11_default_cfg` Click Default Configuration function.
```c
err_t flash11_default_cfg ( flash11_t *ctx );
```

#### Example key functions :

- `flash11_memory_write` Flash 11 memory write function.
```c
err_t flash11_memory_write ( flash11_t *ctx, uint32_t mem_addr, uint8_t *data_in, uint32_t len );
```

- `flash11_memory_read` Flash 11 memory read function.
```c
err_t flash11_memory_read ( flash11_t *ctx, uint32_t mem_addr, uint8_t *data_out, uint32_t len );
```

- `flash11_block_erase` Flash 11 block erase function.
```c
err_t flash11_block_erase ( flash11_t *ctx, uint8_t cmd_block_erase, uint32_t mem_addr );
```

## Example Description

> This example demonstrates the use of Flash 11 Click board 
> The demo app writes specified data to the memory and reads it back.

**The demo application is composed of two sections :**

### Application Init

> The initialization of SPI module, log UART, and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    flash11_cfg_t flash11_cfg;  /**< Click config object. */

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
    flash11_cfg_setup( &flash11_cfg );
    FLASH11_MAP_MIKROBUS( flash11_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == flash11_init( &flash11, &flash11_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( FLASH11_ERROR == flash11_default_cfg ( &flash11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, " ----------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the Flash 11 Click board™.
> The demo application writes a desired number of bytes to the memory 
> and then verifies if it is written correctly
> by reading from the same memory location and displaying the memory content.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    uint8_t data_buf[ 128 ] = { 0 };
    log_printf( &logger, " Memory address: 0x%.6LX\r\n", ( uint32_t ) STARTING_ADDRESS_1 );
    if ( FLASH11_OK == flash11_block_erase( &flash11, FLASH11_CMD_BLOCK_ERASE_4KB, STARTING_ADDRESS_1 ) )
    {
        log_printf( &logger, " Erase memory block (4KB)\r\n" );
    }
    
    memcpy( data_buf, DEMO_TEXT_MESSAGE_1, strlen( DEMO_TEXT_MESSAGE_1 ) );
    if ( FLASH11_OK == flash11_memory_write( &flash11, STARTING_ADDRESS_1, data_buf, sizeof( data_buf ) ) )
    {
       log_printf( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    
    memset( data_buf, 0, sizeof( data_buf ) );
    if ( FLASH11_OK == flash11_memory_read( &flash11, STARTING_ADDRESS_1, data_buf, sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Read data: %s\r\n", data_buf );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    log_printf( &logger, " ----------------------------\r\n" );
    
    log_printf( &logger, " Memory address: 0x%.6LX\r\n", ( uint32_t ) STARTING_ADDRESS_2 );
    if ( FLASH11_OK == flash11_block_erase( &flash11, FLASH11_CMD_BLOCK_ERASE_4KB, STARTING_ADDRESS_2 ) )
    {
        log_printf( &logger, " Erase memory block (4KB)\r\n" );
    }
    memcpy( data_buf, DEMO_TEXT_MESSAGE_2, strlen( DEMO_TEXT_MESSAGE_2 ) );
    if ( FLASH11_OK == flash11_memory_write( &flash11, STARTING_ADDRESS_2, data_buf, sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    
    memset( data_buf, 0, sizeof( data_buf ) );
    if ( FLASH11_OK == flash11_memory_read( &flash11, STARTING_ADDRESS_2, data_buf, sizeof( data_buf ) ) )
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
- Click.Flash11

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
