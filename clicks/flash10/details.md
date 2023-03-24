
---
# Flash 10 click

> Flash 10 Click is a compact add-on board representing a highly reliable memory solution. This board features the AT25FF321A, an SPI configurable 32Mbit (2Mx16) serial Flash memory solution from Dialog Semiconductor. The AT25FF321A is an ideal solution for systems in which program code is shadowed from Flash memory into embedded or external RAM (code shadow) for execution and where small amounts of data are stored and updated locally in the Flash memory. It has a flexible and optimized erase architecture for code and data storage applications, non-volatile protection, and four specialized 128-byte OTP security registers to store a unique device ID and locked key storage. This memory can withstand many write cycles (minimum 100k) and has a data retention period greater than 20 years.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/flash10_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/flash-10-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2022.
- **Type**          : SPI type


# Software Support

We provide a library for the Flash 10 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Flash 10 Click driver.

#### Standard key functions :

- `flash10_cfg_setup` Config Object Initialization function.
```c
void flash10_cfg_setup ( flash10_cfg_t *cfg );
```

- `flash10_init` Initialization function.
```c
err_t flash10_init ( flash10_t *ctx, flash10_cfg_t *cfg );
```

#### Example key functions :

- `flash10_erase_memory` This function erases the selected amount of memory which contains the selected address.
```c
err_t flash10_erase_memory ( flash10_t *ctx, uint8_t erase_cmd, uint32_t address );
```

- `flash10_memory_write` This function writes a desired number of data bytes starting from the selected memory address.
```c
err_t flash10_memory_write ( flash10_t *ctx, uint32_t address, uint8_t *data_in, uint32_t len );
```

- `flash10_memory_read` This function reads a desired number of data bytes starting from the selected memory address.
```c
err_t flash10_memory_read ( flash10_t *ctx, uint32_t address, uint8_t *data_out, uint32_t len );
```

## Example Description

> This example demonstrates the use of Flash 10 click board by writing specified data to the memory and reading it back.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and checks the communication by reading and verifying the device ID.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    flash10_cfg_t flash10_cfg;  /**< Click config object. */

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
    flash10_cfg_setup( &flash10_cfg );
    FLASH10_MAP_MIKROBUS( flash10_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == flash10_init( &flash10, &flash10_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( FLASH10_ERROR == flash10_check_communication ( &flash10 ) )
    {
        log_error( &logger, " Check communication." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Writes a desired number of bytes to the memory and then verifies if it is written correctly
by reading from the same memory location and displaying the memory content on the USB UART.
The whole 4KB block of memory that contains the STARTING_ADDRESS will be erased before writing data.

```c
void application_task ( void )
{
    uint8_t data_buf[ 128 ] = { 0 };
    log_printf ( &logger, " Memory address: 0x%.6LX\r\n", ( uint32_t ) STARTING_ADDRESS );
    if ( FLASH10_OK == flash10_erase_memory ( &flash10, FLASH10_CMD_BLOCK_ERASE_4KB, STARTING_ADDRESS ) )
    {
        log_printf ( &logger, " Erase memory block (4KB)\r\n" );
    }
    memcpy ( data_buf, DEMO_TEXT_MESSAGE_1, strlen ( DEMO_TEXT_MESSAGE_1 ) );
    if ( FLASH10_OK == flash10_memory_write ( &flash10, STARTING_ADDRESS, 
                                              data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( FLASH10_OK == flash10_memory_read ( &flash10, STARTING_ADDRESS, 
                                             data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Read data: %s\r\n\n", data_buf );
        Delay_ms ( 3000 );
    }
    log_printf ( &logger, " Memory address: 0x%.6LX\r\n", ( uint32_t ) STARTING_ADDRESS );
    if ( FLASH10_OK == flash10_erase_memory ( &flash10, FLASH10_CMD_BLOCK_ERASE_4KB, STARTING_ADDRESS ) )
    {
        log_printf ( &logger, " Erase memory block (4KB)\r\n" );
    }
    memcpy ( data_buf, DEMO_TEXT_MESSAGE_2, strlen ( DEMO_TEXT_MESSAGE_2 ) );
    if ( FLASH10_OK == flash10_memory_write ( &flash10, STARTING_ADDRESS, 
                                              data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( FLASH10_OK == flash10_memory_read ( &flash10, STARTING_ADDRESS, 
                                             data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Read data: %s\r\n\n", data_buf );
        Delay_ms ( 3000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Flash10

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
