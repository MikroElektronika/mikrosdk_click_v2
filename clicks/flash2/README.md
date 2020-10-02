\mainpage Main Page
 
---
# Flash 2 click

Flash 2 click features a 64 Mbit Flash memory IC, manufactured by using the proprietary high-performance CMOS Super-Flash® technology, which allows the Flash 2 click to withstand up to 100,000 write cycles, with the data retention period of 100 years, which is considerably longer than any other memory module of this type. The flash memory IC used on this Click board™ features Serial Flash Discoverable Parameters (SFDP) mode, used to retrieve the advanced information from the device, such as the operating characteristics, structure and vendor specified information, memory size, operating voltage, timing information, and more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/flash2_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/flash-2-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Flash2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Flash2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void flash2_cfg_setup ( flash2_cfg_t *cfg ); 
 
- Initialization function.
> FLASH2_RETVAL flash2_init ( flash2_t *ctx, flash2_cfg_t *cfg );

- Click Default Configuration function.
> void flash2_default_cfg ( flash2_t *ctx );


#### Example key functions :

- The Global Block-Protection Unlock instruction clears all
- write-protection bits in the Block-Protection register,
- except for those bits that have been locked down with the
- nVWLDR command.
> void flash2_global_block_unlock( flash2_t *ctx )
 
- The Chip-Erase instruction clears all bits in the device
- to ‘1.’ The Chip-Erase instruction is ignored if any of the
- memory area is protected.
> void flash2_chip_erase( flash2_t *ctx )

- The Read instruction, 03H, is supported in SPI bus pro-
- tocol only with clock frequencies up to 40 MHz. This
- command is not supported in SQI bus protocol. The
- device outputs the data starting from the specified
- address location, theand Configuration n continuously streams the data
- output through all addresses until terminated by a low-
- to-high transition on CE#. The internal address pointer
- will automatically increment until the highest memory
- address is reached. Once the highest memory address
- is reached, the address pointer will automatically return
- to the beginning (wrap-around) of the address space.
> void flash2_read_generic( flash2_t *ctx, uint32_t address, uint8_t *buffer, uint32_t data_count )

## Examples Description

> This example demonstrates the process of writing and reading data from Flash 2 click memory.

**The demo application is composed of two sections :**

### Application Init 

> Flash Driver Initialization, initialization of click by setting mikorBUS to
> approprieate logic levels, performing global block unlock and chip erase functions.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    flash2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    flash2_cfg_setup( &cfg );
    FLASH2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    flash2_init( &flash2, &cfg );
    Delay_ms( 300 );
    flash2_global_block_unlock( &flash2 );
    Delay_ms( 400 );
    flash2_chip_erase( &flash2 );
    Delay_ms( 300 );
}
  
```

### Application Task

> Writing data to click memory and displaying the read data via UART.  

```c

void application_task ( void )
{
    log_printf( &logger, "Writing MikroE to flash memory, from address 0x015015:\r\n" );
    flash2_write_generic( &flash2, 0x015015, &wr_data[ 0 ], 9 );
    log_printf( &logger, "Reading 9 bytes of flash memory, from address 0x015015:\r\n" );
    flash2_read_generic( &flash2, 0x015015, &rd_data[ 0 ], 9 );
    log_printf( &logger, "Data read: %s\r\n", rd_data );
    Delay_ms( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Flash2

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
