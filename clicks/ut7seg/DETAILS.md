
 

---
# UT 7-SEG click

UT 7-SEG R click carries two SMD ultra thin LED 7-SEG displays and the MAX6969 constant-current LED driver from Maxim Integrated.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/grupe/ut-7-seg-group-click.png" height=300px>
</p>

> - [Product page - UT S 7-SEG R click](<https://www.mikroe.com/ut-s-7-seg-r-click>)
> - [Product page - UT M 7-SEG R click](<https://www.mikroe.com/ut-m-7-seg-r-click>)
> - [Product page - UT L 7-SEG R click](<https://www.mikroe.com/ut-l-7-seg-r-click>)

---

#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : nov 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Ut7Seg Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ut7Seg Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ut7seg_cfg_setup ( ut7seg_cfg_t *cfg ); 
 
- Initialization function.
> UT7SEG_RETVAL ut7seg_init ( ut7seg_t *ctx, ut7seg_cfg_t *cfg );

- Click Default Configuration function.
> void ut7seg_default_cfg ( ut7seg_t *ctx );


#### Example key functions :

- Display number
> void utl7segr_display_number ( ut7seg_t *ctx, uint8_t number, uint8_t dot_pos );
 
- Display state
> void ut7seg_display_state ( ut7seg_t *ctx, uint8_t state );

- Generic transfer function
> void ut7seg_generic_transfer ( ut7seg_t *ctx, spi_master_transfer_data_t *block );

## Examples Description

> The demo application shows basic usage of the UT 7 SEG display.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
> Settings the click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ut7seg_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ut7seg_cfg_setup( &cfg );
    UT7SEG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ut7seg_init( &ut7seg, &cfg );

    ut7seg_default_cfg( &ut7seg );
}
```

### Application Task

> Draws numbers from 0 to 99 on the screen.

```c
void application_task ( void )
{
    uint8_t cnt;

    //  Task implementation.

    log_info( &logger, "---- Number counter ----" );

    for ( cnt = 0; cnt < 100; cnt++ )
    {
        utl7segr_display_number( &ut7seg, cnt, UT7SEG_DOT_LEFT_RIGHT );
        Delay_ms( 500 );
    }
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ut7Seg

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
