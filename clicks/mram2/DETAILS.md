
---
# MRAM 2 click

MRAM 2 Click is a compact add-on board for applications that must store and retrieve data and programs quickly using a small number of pins.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>

[click Product page](https://www.mikroe.com/mram-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Mram2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Mram2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mram2_cfg_setup ( mram2_cfg_t *cfg ); 
 
- Initialization function.
> MRAM2_RETVAL mram2_init ( mram2_t *ctx, mram2_cfg_t *cfg );

#### Example key functions :

- Write Enable function
> void mram2_wren ( mram2_t *ctx );
 
- Enter Sleep Mode function
> void mram2_sleep ( mram2_t *ctx );

- Write Data Bytes function
> void mram2_write ( mram2_t *ctx, uint32_t mem_adr, uint8_t *wr_data, uint8_t n_bytes );

## Examples Description

> This demo example writes and reads from memory.

**The demo application is composed of two sections :**

### Application Init 

> Initializes SPI module, LOG structure, sets CS, RTS and INT pins as output.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    mram2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mram2_cfg_setup( &cfg );
    MRAM2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mram2_init( &mram2, &cfg );

    log_printf( &logger, "------------------- \r\n" );
    log_printf( &logger, "   MRAM 2 Click     \r\n" );
    log_printf( &logger, "------------------- \r\n" );
    mram2_write_protect( &mram2, MRAM2_WP_ENABLE );
    mram2_hold( &mram2, MRAM2_HLD_DISABLE );
    log_printf( &logger, "   Initialized      \r\n" );
    log_printf( &logger, "------------------- \r\n" );
    Delay_ms( 100 );
}
  
```

### Application Task

> This example shows capabilities of MRAM 2 Click board
> by writting "MikroE" into first 6 memory locations, 
> and then reading it back.

```c

void application_task ( void )
{
    log_printf( &logger, "Write enable! \r\n" );
    mram2_wren( &mram2 );
    Delay_ms( 100 );
    log_printf( &logger, "Writing : %s \r\n", val_in );
    mram2_write( &mram2, 0x000000, &val_in[ 0 ], 9 );
    Delay_ms( 100 );
    log_printf( &logger, "Write disable! \r\n" );
    mram2_wrdi ( &mram2 );
    Delay_ms( 100 );
    log_printf( &logger, "Reading : \r\n" );
    mram2_read ( &mram2, 0x000000, &val_out[ 0 ], 9 );
    log_printf( &logger, " %s \r\n", val_out );
    
    log_printf( &logger, "------------------- \r\n" );
    Delay_ms( 5000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Mram2

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
