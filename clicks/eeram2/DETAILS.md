
---
# EERAM 2 click

EERAM 2 Click is a standalone serial SRAM memory that includes shadow non-volatile backup. EERAM uses a small external capacitor to provide the energy needed to move the contents of the SRAM to the non-volatile cells when system power is lost.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/eeram2_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/eeram-2-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Eeram2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Eeram2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void eeram2_cfg_setup ( eeram2_cfg_t *cfg ); 
 
- Initialization function.
> EERAM2_RETVAL eeram2_init ( eeram2_t *ctx, eeram2_cfg_t *cfg );

#### Example key functions :

- Set On-hold status function.
> void eeram2_set_on_hold_status ( eeram2_t *ctx, uint8_t en_hold );
 
- Set command function.
> void eeram2_set_command ( eeram2_t *ctx, uint8_t command );

- Set write status function.
> void eeram2_set_write_status ( eeram2_t *ctx, uint8_t en_write );

## Examples Description

> 
> <EXAMPLE_DESCRIPTION>
> 

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - SPI. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    eeram2_cfg_t cfg;

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    eeram2_cfg_setup( &cfg );
    EERAM2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    eeram2_init( &eeram2, &cfg );

    eeram2_set_on_hold_status( &eeram2, EERAM2_HOLD_DISABLE );
    Delay_ms( 100 );

    eeram2_set_write_status( &eeram2, EERAM2_WRITE_ENABLE );
    Delay_ms( 100 );
}
  
```

### Application Task

> This is an example that demonstrates the use of the EERAM 2 Click board.
 In this example, we write and then read data from SRAM memory.
 Results are being sent to the Usart Terminal where you can track their changes.
 All data logs write on USB uart changes approximately for every 1 sec. 

```c

void application_task ( void )
{
    check_status = eeram2_write_continuous( &eeram2, 0x00543210, &demo_data[ 0 ], 9 );

    if ( check_status == EERAM2_ERROR )
    {
        log_printf( &logger, "   ERROR Writing    \r\n" );
        log_printf( &logger, "--------------------\r\n" );
        for ( ; ; );
    }

    log_printf( &logger, "     Writing...     \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms( 100 );

    check_status = eeram2_read_continuous( &eeram2, 0x00543210, &read_data[ 0 ], 9 );

    if ( check_status == EERAM2_ERROR )
    {
        log_printf( &logger, "   Reading ERROR    \r\n" );
        log_printf( &logger, "--------------------\r\n" );
        for ( ; ; );
    }

    log_printf( &logger, " Read data : \r\n" );

    log_printf( &logger, "%s", read_data );
    
    Delay_ms( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Eeram2

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
