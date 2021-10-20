
---
# SRAM 4 click

> SRAM 4 Click is a compact add-on board that contains highly reliable nonvolatile memory. This board features the CY14B512Q, a 512Kbit SRAM with a nonvolatile element in each memory cell from Cypress Semiconductor, now part of Infineon.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/sram_4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/sram-4-click)

---


#### Click library

- **Author**        : Luka FIlipovic
- **Date**          : Aug 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the SRAM4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for SRAM4 Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This example application showcases ability of device
ability to manipulate with memory( writing and reading data ).

**The demo application is composed of two sections :**

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
    
    Delay_ms( 3000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SRAM4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
