
---
# Boost-inv 2 click

Boost-INV 2 click is a very useful DC/DC voltage converter device, as can output both positive and negative voltage, boosted up to 15V and inverted to -15V, from a single fixed voltage input.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/boostinv2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/boost-inv-2-click)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the boostinv2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for boostinv2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void boostinv2_cfg_setup ( boostinv2_cfg_t *cfg ); 
 
- Initialization function.
> BOOSTONV2_RETVAL boostinv2_init ( boostinv2_t *ctx, boostinv2_cfg_t *cfg );

- Click Default Configuration function.
> void boostinv2_default_cfg ( boostinv2_t *ctx );


#### Example key functions :

- Functions for set positive output voltage.
> void boostinv2_set_positive_voltage ( boostinv2_t *ctx, uint16_t voltage );
 
- Functions for set negative output voltage.
> void boostinv2_set_negative_voltage ( boostinv2_t *ctx, uint16_t voltage );

- Generic transfer function.
> void boostinv2_generic_transfer ( boostinv2_t *ctx, spi_master_transfer_data_t *block );

## Examples Description

> First increse positiv voltage by 2V every 3 seconda, 
> then decrese negative value for -2v every 3 seconds.

**The demo application is composed of two sections :**

### Application Init 

> Initializes Driver init and enable chip

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    boostinv2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    boostinv2_cfg_setup( &cfg );
    BOOSTONV2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    boostinv2_init( &boostinv2, &cfg );
    
    boostinv2_enable( &boostinv2 ); 
} 
```

### Application Task

> Changes the positive and negative output voltage. 
> Positive output voltage goes from 5V to 15V. 
> Negative output voltage goes from -5V to -15V

```c
void application_task ( void )
{
     // Positive output voltage 
     log_printf( &logger, "VOUT = 6V\r\n");
     boostinv2_set_positive_voltage( &boostinv2, BOOSTINV2_POS_VOUT_6V );
     Delay_ms( 3000 );
     log_printf( &logger, "VOUT = 8V\r\n");
     boostinv2_set_positive_voltage( &boostinv2, BOOSTINV2_POS_VOUT_8V );
     Delay_ms( 3000 );
     log_printf( &logger, "VOUT = 12V\r\n");
     boostinv2_set_positive_voltage( &boostinv2, BOOSTINV2_POS_VOUT_12V );
     Delay_ms( 3000 );
     log_printf( &logger, "VOUT = 14V\r\n");
     boostinv2_set_positive_voltage( &boostinv2, BOOSTINV2_POS_VOUT_14V );
     Delay_ms( 3000 );
     log_printf( &logger, "VOUT = 12V\r\n");
     boostinv2_set_positive_voltage( &boostinv2, BOOSTINV2_POS_VOUT_12V );
     Delay_ms( 3000 );
     log_printf( &logger, "VOUT = 8V\r\n");
     boostinv2_set_positive_voltage( &boostinv2, BOOSTINV2_POS_VOUT_8V );
     Delay_ms( 3000 );
     
     // Negative output voltage 
     
     log_printf( &logger, "VOUT = -5V\r\n");
     boostinv2_set_negative_voltage( &boostinv2, BOOSTINV2_NEG_VOUT_5V );
     Delay_ms( 3000 );
     log_printf( &logger, "VOUT = -7V\r\n");
     boostinv2_set_negative_voltage( &boostinv2, BOOSTINV2_NEG_VOUT_7V );
     Delay_ms( 3000 );
     log_printf( &logger, "VOUT = -13V\r\n");
     boostinv2_set_negative_voltage( &boostinv2, BOOSTINV2_NEG_VOUT_13V );
     Delay_ms( 3000 );
     log_printf( &logger, "VOUT = -7V\r\n");
     boostinv2_set_negative_voltage( &boostinv2, BOOSTINV2_NEG_VOUT_7V );
     Delay_ms( 3000 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.boostinv2

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
