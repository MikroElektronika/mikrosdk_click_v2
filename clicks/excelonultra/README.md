\mainpage Main Page

---
# Excelon-Ultra Click

> Excelon-Ultra Click is a compact add-on board that contains the most reliable nonvolatile memory. This board features the CY15B116QSN, a high-performance 16-Mbit nonvolatile memory that employs an advanced ferroelectric process from Infineon Technologies.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/excelonultra_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/excelon-ultra-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Jun 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the ExcelonUltra Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ExcelonUltra Click driver.

#### Standard key functions :

- `excelonultra_cfg_setup` Config Object Initialization function.
```c
void excelonultra_cfg_setup ( excelonultra_cfg_t *cfg );
```

- `excelonultra_init` Initialization function.
```c
err_t excelonultra_init ( excelonultra_t *ctx, excelonultra_cfg_t *cfg );
```

- `excelonultra_default_cfg` Click Default Configuration function.
```c
err_t excelonultra_default_cfg ( excelonultra_t *ctx );
```

#### Example key functions :

- `excelonultra_write_data_to_memory` Write data starting from specified memory address.
```c
err_t excelonultra_write_data_to_memory 
( excelonultra_t *ctx, uint32_t mem_adr, uint8_t *mem_data, uint32_t mem_data_len );
```

- `excelonultra_read_data_from_memory` Read data starting from specified memory address.
```c
err_t excelonultra_read_data_from_memory 
( excelonultra_t *ctx, uint32_t mem_adr, uint8_t *mem_data, uint32_t mem_data_len );
```

- `excelonultra_clear_data_from_memory` Clears data starting from specified memory address.
```c
err_t excelonultra_clear_data_from_memory 
( excelonultra_t *ctx, uint32_t mem_adr, uint32_t mem_data_len );
```

## Example Description

> This example is showcase of device and it's library abillity.
  In this example is shown device ID, ability to manipulate with memory.
  After default configuration device IDs are logged. After that application
  Writes data to memory, reads data from memory, clears data from memory and
  checks if data is cleard by reading that same memory address.

**The demo application is composed of two sections :**

### Application Init

> Initializes MCU modules for communication used in this application (UART, SPI).
Calls default configuration that resets device, reads IDs, and enables writing to
memory and sets all RAM memory to be free for conrol.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    excelonultra_cfg_t excelonultra_cfg;  /**< Click config object. */

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
    excelonultra_cfg_setup( &excelonultra_cfg );
    EXCELONULTRA_MAP_MIKROBUS( excelonultra_cfg, MIKROBUS_1 );
    err_t init_flag  = excelonultra_init( &excelonultra, &excelonultra_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    excelonultra_default_cfg ( &excelonultra );
    
    log_printf( &logger, " > Manufacturer ID: 0x%.4X\r\n", excelonultra.manufacturer_id );
    log_printf( &logger, " > Product ID: 0x%.4X\r\n", excelonultra.product_id );
    log_printf( &logger, " > Density ID: 0x%.2X\r\n", excelonultra.density_id );
    log_printf( &logger, " > Die Rev: 0x%.2X\r\n", excelonultra.die_rev );
    
    log_printf( &logger, " > Unique ID: 0x%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X\r\n"
    , excelonultra.unique_id[ 7 ], excelonultra.unique_id[ 6 ], excelonultra.unique_id[ 5 ],
    excelonultra.unique_id[ 4 ], excelonultra.unique_id[ 3 ], excelonultra.unique_id[ 2 ],
    excelonultra.unique_id[ 1 ], excelonultra.unique_id[ 0 ] );
    
    Delay_ms ( 1000 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Write data to memory, read data from memory. After that clears that memory address,
and checks if it's cleared by reading data. On every iteration of the fucntion 
writing data is changed between "MikroE" and "Excelon-Ultra Click"

```c

void application_task ( void ) 
{
    static uint32_t memory_address = 0x00000055;
    static uint8_t data_selection = 1;
    static uint8_t write_len;
    char to_write[ 50 ] = { 0 };
    char read_from[ 50 ] = { 0 };
    
    if (data_selection)
    {
        strcpy( to_write, MIKROE_DATA );
        data_selection = !data_selection;
    }
    else
    {
        strcpy( to_write, CLICK_DATA );
        data_selection = !data_selection;
    }
    write_len = strlen( to_write );
    
    log_printf( &logger, " > Writing data to memory: %s\r\n", to_write );
    excelonultra_write_data_to_memory( &excelonultra, memory_address, to_write, write_len );
    
    Delay_ms ( 500 );
    
    excelonultra_read_data_from_memory( &excelonultra, memory_address, read_from, write_len );
    log_printf( &logger, " > Read data from memory: %s\r\n", read_from );

    Delay_ms ( 500 );

    log_printf( &logger, " > Clearing data from memory\r\n" );
    excelonultra_clear_data_from_memory( &excelonultra, memory_address, write_len );
    
    Delay_ms ( 500 );
    
    excelonultra_read_data_from_memory( &excelonultra, memory_address, read_from, write_len );
    log_printf( &logger, " > Read data from memory: %s\r\n", read_from );

    log_printf( &logger, "***********************************\r\n" );
    Delay_ms ( 500 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ExcelonUltra

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
