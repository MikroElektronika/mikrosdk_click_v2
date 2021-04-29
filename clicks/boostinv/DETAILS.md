 

---
# Boost-INV click

Boost-INV click is a very useful DC/DC voltage converter device, as can output both positive and negative voltage, boosted up to 12.78V and -13.95, from a single fixed voltage input.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/boostinv_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/boost-inv-click)

---


#### Click library 

- **Author**        : Luka FIlipovic
- **Date**          : Nov 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the BoostInv Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for BoostInv Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void boostinv_cfg_setup ( boostinv_cfg_t *cfg ); 
 
- Initialization function.
> BOOSTINV_RETVAL boostinv_init ( boostinv_t *ctx, boostinv_cfg_t *cfg );

- Click Default Configuration function.
> void boostinv_default_cfg ( boostinv_t *ctx );


#### Example key functions :

- Functions for enable chip.
> void boostinv_enable ( boostinv_t *ctx );
 
- Functions for set positive output voltage
> void boostinv_set_positive_voltage ( boostinv_t *ctx, uint16_t voltage );

- Functions for set negative output voltage
> void boostinv_set_negative_voltage ( boostinv_t *ctx, int16_t voltage );

## Examples Description

> Changes the positive and negative output voltage. Input Voltage 3.3V.
> Positive output voltage goes from 3200mV, 7750mV, 12000mV and 7750mV.
> Negative output voltage goes from -1450mV, -6700mV, -11050mV and -6700mV.

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C module and sets EN ( RST ) pin as output.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    boostinv_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    boostinv_cfg_setup( &cfg );
    BOOSTINV_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    boostinv_init( &boostinv, &cfg );
    
    boostinv_default_cfg ( &boostinv );
    log_printf( &logger, "     Boost INV Click\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms( 100 );
}
  
```

### Application Task

> Changes the positive and negative output voltage every 5 sec.

```c

void application_task ( void )
{
    //  Task implementation.
    
    // Sets Positive output voltage
    
    log_printf( &logger, " Positive output voltage \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "          3200 mV\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    boostinv_set_positive_voltage( &boostinv, BOOSTINV_VOLTAGE_POSITIVE_3200_mV );
    Delay_ms( 5000 );
    
    log_printf( &logger, "          7750 mV\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    boostinv_set_positive_voltage( &boostinv, BOOSTINV_VOLTAGE_POSITIVE_7750_mV );
    Delay_ms( 5000 );
    
    log_printf( &logger, "        12000 mV\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    boostinv_set_positive_voltage( &boostinv, BOOSTINV_VOLTAGE_POSITIVE_12000_mV );
    Delay_ms( 5000 );
    
    log_printf( &logger, "         7750 mV\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    boostinv_set_positive_voltage( &boostinv, BOOSTINV_VOLTAGE_POSITIVE_7750_mV );
    Delay_ms( 5000 );
    
    // Sets Negative output voltage
    
    log_printf( &logger, " Negative output voltage \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "        -1450 mV\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    boostinv_set_negative_voltage( &boostinv, BOOSTINV_VOLTAGE_NEGATIVE_1450_mV );
    Delay_ms( 5000 );
    
    log_printf( &logger, "       - 6700 mV\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    boostinv_set_negative_voltage( &boostinv, BOOSTINV_VOLTAGE_NEGATIVE_6700_mV );
    Delay_ms( 5000 );
    
    log_printf( &logger, "       - 11050 mV\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    boostinv_set_negative_voltage( &boostinv, BOOSTINV_VOLTAGE_NEGATIVE_11050_mV );
    Delay_ms( 5000 );
    
    log_printf( &logger, "       - 6700 mV\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    boostinv_set_negative_voltage( &boostinv, BOOSTINV_VOLTAGE_NEGATIVE_6700_mV );
    Delay_ms( 5000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.BoostInv

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
