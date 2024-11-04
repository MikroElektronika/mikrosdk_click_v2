\mainpage Main Page

---
# Flash 9 Click

> Flash 9 Click is a compact add-on board that contains a highly reliable memory solution. This board features the W25Q02JV, an SPI configurable serial Flash memory solution from Winbond Electronics. It represents a four 512Mb stack die supporting linear addressing for the full 2Gb memory address range, offering flexibility and performance well beyond ordinary Serial Flash devices. The W25Q02JV array is organized into 1,048,576 programmable pages of 256-bytes each, where up to 256 bytes can be programmed at a time. This memory also has advanced security features, can withstand many write cycles (minimum 100k), and has a data retention period greater than 20 years.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/flash9_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/flash-9-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the Flash 9 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Flash 9 Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This example demonstrates the use of Flash 9 Click board by writing specified data to the memory and reading it back.

**The demo application is composed of two sections :**

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

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Flash9

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
