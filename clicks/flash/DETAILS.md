

---
# Flash click

Flash Click is 8,388,608 bits (8 Mbit) on a Click board, organized into 1,048,576 bytes (1 MB).
In other words, this Click board is a Flash memory medium with the capacity of 1 MB.
The used Flash module has very good endurance and it can withstand up to 100,000 write cycles, with the data retention period of about 20 years.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/flash_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/flash-click>)

---


#### Click library

- **Author**        : Nemanja Medakovic
- **Date**          : Nov 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Flash Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers).
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account.

## Library Description

> This library contains API for Flash Click driver.

#### Standard key functions :

- Config Object Setup function.
> void flash_cfg_setup( flash_cfg_t *cfg );
 
- Click Initialization function.
> flash_err_t flash_init( flash_t *ctx, flash_cfg_t *cfg );

- Click Default Configuration function.
> void flash_default_cfg( flash_t *ctx );

#### Example key functions :

- Page Write function.
> flash_err_t flash_write_page( flash_t *ctx, uint32_t mem_addr, spi_master_data_t *data_tx, uint16_t n_data );
 
- Page Read function.
> flash_err_t flash_read_page( flash_t *ctx, uint32_t mem_addr, spi_master_data_t *data_rx, uint16_t n_data );

- Sector Erase function.
> flash_err_t flash_erase_sector( flash_t *ctx, uint32_t mem_addr );

## Examples Description

>
> This example demonstrates the use (control) of the FLASH memory.
>

**The demo application is composed of two sections :**

### Application Init

>
> Initializes all necessary peripherals and pins used by Flash click and also
> initializes uart logger to show results.
>

```c

void application_init( void )
{
    flash_cfg_t flash_cfg;
    log_cfg_t log_cfg;

    //  Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
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

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Flash

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
