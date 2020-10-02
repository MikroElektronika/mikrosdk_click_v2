\mainpage Main Page
 
---
# Semper Flash 2 click

Semper Flash 2 Click is a Click board™ which features the S25HL512T from Cypress, a perfect solution for the mass storage option in various embedded applications. With fast performance being one of its key features, Semper Flash 2 click can also be used for the code shadowing, execute-in-place (XIP), and data storage.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/semperflash2_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/semper-flash-2-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the SemperFlash2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for SemperFlash2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void semperflash2_cfg_setup ( semperflash2_cfg_t *cfg ); 
 
- Initialization function.
> SEMPERFLASH2_RETVAL semperflash2_init ( semperflash2_t *ctx, semperflash2_cfg_t *cfg );

- Click Default Configuration function.
> void semperflash2_default_cfg ( semperflash2_t *ctx );


#### Example key functions :

- This function writes data to the flash memory.
> uint8_t semperflash2_write_memory 
( 
    semperflash2_t *ctx,
    uint32_t addr,
    uint8_t *data_buf,
    uint16_t buf_size
);
 
- This function reads data from the flash memory.
> uint8_t semperflash2_read_memory 
(   
    semperflash2_t *ctx,
    uint32_t addr,
    uint8_t *data_buf,
    uint16_t buf_size
);

- This function stores the device ID in the specified buffer.
> uint8_t semperflash2_get_device_id ( semperflash2_t *ctx, uint8_t *id_buf );

## Examples Description

> This example showcases how to initialize and use the Semper Flash 2 click. The click
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
    semperflash2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    Delay_ms( 100 );

    //  Click initialization.

    semperflash2_cfg_setup( &cfg );
    SEMPERFLASH2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    semperflash2_init( &semperflash2, &cfg );
    semperflash2_default_cfg( &semperflash2 );
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
    char write_data_clk[ 15 ] = "Semper Flash 2";
    char read_buf_data[ 15 ] = { 0 };

    semperflash2_send_cmd( &semperflash2, SEMPERFLASH2_WRITE_ENABLE );
    semperflash2_erase_memory( &semperflash2, ADRESS_MEMORY );
    
    if ( COMPANY_FLAG == txt_flag )
    {
       semperflash2_send_cmd( &semperflash2, SEMPERFLASH2_WRITE_ENABLE );
       error_handler( semperflash2_write_memory( &semperflash2, ADRESS_MEMORY, write_data_com, 6 ) );
       error_handler( semperflash2_read_memory( &semperflash2, ADRESS_MEMORY, read_buf_data, 6 ) );
       log_printf( &logger, "%s\r\n", read_buf_data );
       txt_flag = CLICK_FLAG;       
    }
    else if ( CLICK_FLAG == txt_flag )
    {
       semperflash2_send_cmd( &semperflash2, SEMPERFLASH2_WRITE_ENABLE );
       error_handler( semperflash2_write_memory( &semperflash2, ADRESS_MEMORY, write_data_clk, 14 ) );
       error_handler( semperflash2_read_memory( &semperflash2, ADRESS_MEMORY, read_buf_data, 14 ) );
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
- Click.SemperFlash2

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
