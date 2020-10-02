

---
# Expand click

< Expand click is an accessory board in mikroBUS form factor. It includes a 16-bit I/O expander MCP23S17 with SPI clock speeds up to 10 MHz for higher throughput applications >

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/expand_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/expand-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Expand Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Expand Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void expand_cfg_setup ( expand_cfg_t *cfg ); 
 
- Initialization function.
> EXPAND_RETVAL expand_init ( expand_t *ctx, expand_cfg_t *cfg );


#### Example key functions :

- Set expander PORTA direction function.
> void expand_set_direction_port_a ( expand_t *ctx, uint8_t mod_cmd, uint8_t write_data );
 
- Write one byte of data to register for PORTA function.
> void expand_write_port_a ( expand_t *ctx, uint8_t mod_cmd, uint8_t write_data );

- Reset function.
> void expand_reset ( expand_t *ctx );

## Examples Description

> This applicatioin use for expansion I/O lines.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - GPIO, reset MCP23S17 chip, set PORTA to be output and PORTB to be input, set default configuration and start write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    expand_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    expand_cfg_setup( &cfg );
    EXPAND_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    expand_init( &expand, &cfg );


    expand_reset( &expand );
    Delay_ms( 1000 );

    expand_set_direction_port_a( &expand, EXPAND_SPI_MODULE_POSITION_0, EXPAND_PORT_DIRECTION_OUTPUT );
    
    expand_set_direction_port_b( &expand, EXPAND_SPI_MODULE_POSITION_0, EXPAND_PORT_DIRECTION_INPUT );

    log_printf( &logger, " Configuring... \r\n" );
    log_printf( &logger, "----------------\r\n" );
    expand_default_configuration( &expand, EXPAND_SPI_MODULE_POSITION_0 );
}
  
```

### Application Task

> This is a example which demonstrates the use of Expand Click board. Expand Click communicates with register via SPI protocol by write and read from register, set configuration and state and read configuration and state. Results are being sent to the Usart Terminal where you can track their changes. All data logs on usb uart for aproximetly every 3 sec.

```c

void application_task ( void )
{
    uint8_t port_status;
    uint8_t position;
    uint16_t pin_position;

    pin_position = 1;

    for ( position = 0; position < 8; position++ )
    {
        expand_write_port_a( &expand, EXPAND_SPI_MODULE_POSITION_0, pin_position );
        Delay_100ms();

        port_status = expand_read_port_b( &expand, EXPAND_SPI_MODULE_POSITION_0 );


        log_printf( &logger, " %d RA\r\n", position );
        
        log_printf( &logger, " %d PORTB \r\n",  port_status );
        
        pin_position <<= 1;

        Delay_ms( 3000 );
    
    }
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand

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
