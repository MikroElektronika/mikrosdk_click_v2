\mainpage Main Page
 
---
# Semper Flash click

The Semper Flash Click is a Click board™ which features the S25HS512T, a perfect solution for the mass storage option in various embedded applications. With fast performance being one of its key features, Semper Flash click can also be used for the code shadowing, execute-in-place (XIP), data logging and data storage.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/semperflash_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/semper-flash-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the SemperFlash Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for SemperFlash Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void semperflash_cfg_setup ( semperflash_cfg_t *cfg ); 
 
- Initialization function.
> SEMPERFLASH_RETVAL semperflash_init ( semperflash_t *ctx, semperflash_cfg_t *cfg );

- Click Default Configuration function.
> void semperflash_default_cfg ( semperflash_t *ctx );


#### Example key functions :

- This function writes data to the flash memory.
> uint8_t semperflash_write_memory 
( 
    semperflash_t *ctx,
    uint32_t addr,
    uint8_t *data_buf,
    uint16_t buf_size
);
 
- This function reads data from the flash memory.
> uint8_t semperflash_read_memory 
(   
    semperflash_t *ctx,
    uint32_t addr,
    uint8_t *data_buf,
    uint16_t buf_size
);

- This function erases data from the flash memory.
> void semperflash_erase_memory ( semperflash_t *ctx, uint32_t addr );

## Examples Description

> This example showcases how to initialize and use the Semper Flash click. The click
  is a 512 Mbit SPI Flash memory module. Data can be stored in and read from the flash
  memory. There's also the option of erasing it's contents. Here's how to do it. 

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the click and logger modules. Additional con-
  figuring is done in the default_cfg(...) function. The device ID should appear in the 
  UART console if the setup finishes successfully.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    semperflash_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    Delay_ms( 100 );

    //  Click initialization.

    semperflash_cfg_setup( &cfg );
    SEMPERFLASH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    semperflash_init( &semperflash, &cfg );
    semperflash_default_cfg( &semperflash );
    id_check( );
    Delay_ms( 500 );
}
  
```

### Application Task

> This function first erases the contents of the flash memory and then writes, reads and
  prints two strings in the UART console. It does so every 2 seconds. 

```c

void application_task ( void )
{
    char write_data_com[ 7 ] = "MikroE";
    char write_data_clk[ 13 ] = "Semper Flash";
    char read_buf_data[ 13 ] = { 0 };

    semperflash_send_cmd( &semperflash, SEMPERFLASH_WRITE_ENABLE );
    semperflash_erase_memory( &semperflash, ADRESS_MEMORY );
    
    if ( COMPANY_FLAG == txt_flag )
    {
       semperflash_send_cmd( &semperflash, SEMPERFLASH_WRITE_ENABLE );
       error_handler( semperflash_write_memory( &semperflash, ADRESS_MEMORY, write_data_com, 6 ) );
       error_handler( semperflash_read_memory( &semperflash, ADRESS_MEMORY, read_buf_data, 6 ) );
       log_printf( &logger, "%s\r\n", read_buf_data );
       txt_flag = CLICK_FLAG;       
    }
    else if ( CLICK_FLAG == txt_flag )
    {
       semperflash_send_cmd( &semperflash, SEMPERFLASH_WRITE_ENABLE );
       error_handler( semperflash_write_memory( &semperflash, ADRESS_MEMORY, write_data_clk, 12 ) );
       error_handler( semperflash_read_memory( &semperflash, ADRESS_MEMORY, read_buf_data, 12 ) );
       log_printf( &logger, "%s\r\n", read_buf_data );
       txt_flag = COMPANY_FLAG;
    }

    log_printf( &logger, "....................\r\n" );
    Delay_ms( 2000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.SemperFlash

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
