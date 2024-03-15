
---
# Flash 12 click

> Flash 12 Click is a compact add-on board representing a highly reliable memory solution. This board features the AT25EU0041A, a 4Mbit serial flash memory from Renesas, known for its ultra-low power consumption. This Click board™ is specifically designed to address the needs of systems operating at the IoT network's edge, providing an optimal solution for program code storage and execution directly from NOR Flash memory. It stands out for its innovative erase architecture, offering short erase times and low power consumption across operations, including reading, programming, and erasing.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/flash12_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/flash-12-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the Flash 12 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Flash 12 Click driver.

#### Standard key functions :

- `flash12_cfg_setup` Config Object Initialization function.
```c
void flash12_cfg_setup ( flash12_cfg_t *cfg );
```

- `flash12_init` Initialization function.
```c
err_t flash12_init ( flash12_t *ctx, flash12_cfg_t *cfg );
```

- `flash12_default_cfg` Click Default Configuration function.
```c
err_t flash12_default_cfg ( flash12_t *ctx );
```

#### Example key functions :

- `flash12_memory_write` This function writes a desired number of data bytes starting to the selected memory address by using SPI serial interface.
```c
err_t flash12_memory_write ( flash12_t *ctx, uint32_t mem_addr, uint8_t *data_in, uint32_t len );
```

- `flash12_memory_read` This function reads a desired number of data bytes starting from the selected memory address by using SPI serial interface.
```c
err_t flash12_memory_read ( flash12_t *ctx, uint32_t mem_addr, uint8_t *data_out, uint32_t len );
```

- `flash12_erase_memory` This function erases the selected amount of memory which contains the selected address.
```c
err_t flash12_erase_memory ( flash12_t *ctx, uint8_t erase_cmd, uint32_t mem_addr );
```

## Example Description

> This example demonstrates the use of Flash 12 click board 
> by writing specified data to the memory and reading it back.

**The demo application is composed of two sections :**

### Application Init

> The initialization of SPI module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    flash12_cfg_t flash12_cfg;  /**< Click config object. */

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
    flash12_cfg_setup( &flash12_cfg );
    FLASH12_MAP_MIKROBUS( flash12_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == flash12_init( &flash12, &flash12_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( FLASH12_ERROR == flash12_default_cfg ( &flash12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task\r\n" );
}
```

### Application Task

> The demo application writes a desired number of bytes to the memory 
> and then verifies if it is written correctly by reading 
> from the same memory location and displaying the memory content.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    uint8_t data_buf[ 128 ] = { 0 };

    log_printf( &logger, " Memory address: 0x%.6LX\r\n", ( uint32_t ) STARTING_ADDRESS );
    if ( FLASH12_OK == flash12_erase_memory( &flash12, FLASH12_CMD_BLOCK_ERASE_4KB, STARTING_ADDRESS ) )
    {
        log_printf( &logger, " Erase memory block (4KB)\r\n" );
    }
    memcpy( data_buf, DEMO_TEXT_MESSAGE_1, strlen( DEMO_TEXT_MESSAGE_1 ) );
    if ( FLASH12_OK == flash12_memory_write( &flash12, STARTING_ADDRESS, 
                                                       data_buf, 
                                                       sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms( 100 );
    }

    memset( data_buf, 0, sizeof( data_buf ) );
    if ( FLASH12_OK == flash12_memory_read( &flash12, STARTING_ADDRESS, 
                                                      data_buf, 
                                                      sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Read data: %s\r\n\n", data_buf );
        Delay_ms( 3000 );
    }

    log_printf( &logger, " Memory address: 0x%.6LX\r\n", ( uint32_t ) STARTING_ADDRESS );
    if ( FLASH12_OK == flash12_erase_memory( &flash12, FLASH12_CMD_BLOCK_ERASE_4KB, STARTING_ADDRESS ) )
    {
        log_printf( &logger, " Erase memory block (4KB)\r\n" );
    }
    memcpy( data_buf, DEMO_TEXT_MESSAGE_2, strlen( DEMO_TEXT_MESSAGE_2 ) );
    if ( FLASH12_OK == flash12_memory_write( &flash12, STARTING_ADDRESS, 
                                             data_buf, sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms( 100 );
    }
    memset( data_buf, 0, sizeof ( data_buf ) );
    if ( FLASH12_OK == flash12_memory_read( &flash12, STARTING_ADDRESS, 
                                            data_buf, sizeof ( data_buf ) ) )
    {
        log_printf( &logger, " Read data: %s\r\n\n", data_buf );
        Delay_ms( 3000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Flash12

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
