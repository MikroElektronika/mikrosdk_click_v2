\mainpage Main Page
 
 

---
# DIGI POT click

DIGI POT Click is an accessory board in mikroBUS form factor.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/grupe/digi-pot-click-group.png" height=300px>
</p>

> - [Product page - DIGI POT click](<https://www.mikroe.com/digipot-click>)
> - [Product page - DIGI POT 2 click](<https://www.mikroe.com/digipot-2-click>)

---


#### Click library 

- **Author**        : Nenad Filipovic
- **Date**          : nov 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the DigiPot Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for DigiPot Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void digipot_cfg_setup ( digipot_cfg_t *cfg ); 
 
- Initialization function.
> DIGIPOT_RETVAL digipot_init ( digipot_t *ctx, digipot_cfg_t *cfg );

#### Example key functions :

- Set wiper position
> void digipot_set_wiper_positions ( digipot_t *ctx, uint8_t wiper_pos );
 
- Convert ADC value to volatage
> float digipot_convert_output ( uint16_t adc_val, float v_ref );

## Examples Description

> The demo application changes the resistance using DIGIPOT Click.

**The demo application is composed of two sections :**

### Application Init 

> Initializes SPI and LOG modules.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    digipot_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    digipot_cfg_setup( &cfg );
    DIGIPOT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    digipot_init( &digipot, &cfg );

    log_printf( &logger, "     DIGI POT Click\r\n" );
    log_printf( &logger, "------------------------\r\n" );
}
```

### Application Task

> This is an example which demonstrates the use of DIGI POT Click board.
> Increments the wiper position by 10 positions every 5 seconds.

```c
void application_task ( void )
{
    //  Task implementation.

    for ( n_cnt = 127; n_cnt < 255; n_cnt += 10 )
    {
        wiper_pos = ( uint8_t ) n_cnt;
        digipot_set_wiper_positions( &digipot, wiper_pos );
        Delay_ms( 5000 );
    }
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.DigiPot

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
