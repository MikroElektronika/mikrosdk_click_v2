 

---
# Dual EE click

Dual EE Click contains two AT24CM02 EEPROM ICs onboard which gives total of 4MB of memory. Each memory IC can be addressed through the I2C interface with the transfer speed of 400KHz. 

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/dualee_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/dual-ee-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the DualEE Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for DualEE Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void dualee_cfg_setup ( dualee_cfg_t *cfg ); 
 
- Initialization function.
> DUALEE_RETVAL dualee_init ( dualee_t *ctx, dualee_cfg_t *cfg );

#### Example key functions :

- Generic write data function
> uint8_t dualee_read ( dualee_t *ctx, uint32_t reg_address, uint8_t *data_buff, uint8_t n_bytes );
 
- Generic write data function
> uint8_t dualee_write ( dualee_t *ctx, uint32_t reg_address, uint8_t *data_buff, uint8_t n_bytes);

## Examples Description

> This application writes data im memory and reads data from memory.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device init

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    dualee_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    dualee_cfg_setup( &cfg );
    DUALEE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dualee_init( &dualee, &cfg );

    log_printf( &logger, "*********** APPLICATION INIT ***********\r\n" );
    Delay_ms( 100 );
}
```

### Application Task

> Reads your command and then execute it

```c
void application_task ( )
{
    uint8_t write_dual;
    uint8_t read_dual;
    char demo_text[ 255 ];

    log_printf( &logger, "Writing data [MikroE]....\r\n" );
    write_dual = dualee_write( &dualee, page_address, write_data, 7 );
  
    if ( write_dual == DUALEE_ERROR_RW )
    {
        log_printf( &logger, "Error writing data!!!\r\n" );
        Delay_ms( 1000 );
        return;
    }
    Delay_ms( 100 );

    log_printf( &logger, "Reading data...\r\n" );
    read_dual = dualee_read( &dualee, page_address, demo_text, 7 );

    if ( read_dual == 0 )
    {
        log_printf( &logger, "Error reading data!!!\r\n" );
        Delay_ms( 1000 );
        return;
    }
    Delay_ms( 100 );
    log_printf( &logger, "Data from read page is: %s \r\n", demo_text );
    
    log_printf( &logger, "__________________________________\r\n" );
    Delay_ms( 1000 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.DualEE

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
