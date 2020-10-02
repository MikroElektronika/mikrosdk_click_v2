
---
# Flash 6 click

The Flash 6 Click based on W25Q128JV (128M-bit) flash memory from Winbond provides a storage solution for systems with limited space, pins and power.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/flash6_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/flash-6-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Flash6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Flash6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void flash6_cfg_setup ( flash6_cfg_t *cfg ); 
 
- Initialization function.
> FLASH6_RETVAL flash6_init ( flash6_t *ctx, flash6_cfg_t *cfg );

#### Example key functions :

- Function used for writing in memory
> void flash6_write_memory_data ( flash6_t *ctx, uint32_t addr, uint8_t *data_buf, uint16_t buf_size );
 
- Function used for reading from memory
> void flash6_read_memory_data ( flash6_t *ctx, uint32_t addr, uint8_t *data_buf, uint16_t buf_size );

- Function for eraseing segment
> void flash6_erase_memory_segment( flash6_t *ctx, uint8_t segment, uint32_t start_addr );

## Examples Description

> This application writes in memory and reads from memory.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver, resets device and tests communication.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    flash6_cfg_t cfg;

    uint8_t manufacture_id;
    uint8_t device_id;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    flash6_cfg_setup( &cfg );
    FLASH6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    flash6_init( &flash6, &cfg );

    flash6_software_reset( &flash6 );
    Delay_ms( 100 );

    flash6_get_manufacture_device_id( &flash6, &manufacture_id, &device_id );
    log_printf( &logger, "\r\n ------> MANUFACTURE ID: 0x%x \r\n", manufacture_id );
    log_printf( &logger, " ------> DEVICE ID: 0x%x \r\n \r\n", device_id );
    Delay_ms( 1000 );
}
  
```

### Application Task

> Clears the memory sector, writes "MikroE" to device memory
> and then reads it and sends it to log every 2 sec.

```c

void application_task ( void )
{
    uint32_t start_addr;
    char read_buff[ 50 ];
    uint8_t cnt;
    
    start_addr = 0x002000;

    log_printf( &logger, " ---> Erase sector  \r\n" );
    flash6_erase_memory_segment( &flash6, FLASH6_CMD_SECTOR_ERASE_4KB, start_addr );
    Delay_ms( 500 );
    
    log_printf( &logger, " ---> Write in memory ... \r\n" );
    flash6_write_memory_data( &flash6, start_addr, &write_buf[ 0 ], 9 );
    log_printf( &logger, " ---> Read from memory \r\n" );
    flash6_read_memory_data( &flash6, start_addr, read_buff, 9 );

    log_printf( &logger, "---->>>> " );
    
    log_printf( &logger, "%s ", read_buff );
    Delay_ms( 100 );
    log_printf( &logger, "----------------------------------\r\n" );
    
    Delay_ms( 2000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Flash6

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
