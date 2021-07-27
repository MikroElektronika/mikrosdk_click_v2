 

---
# DIGI POT 5 click

DIGI POT 5 click is a digitally controlled quad potentiometer, with the resistance of 10KΩ.
It has an 8bit wiper step resolution, which allows the wiper to take 257 different discrete positions (across 256 internal resistors).
The digital wiper position can be controlled via the SPI interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/digipot5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/digipot-5-click)

---


#### Click library

- **Author**        : Nemanja Medakovic
- **Date**          : Nov 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the DigiPot5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers).
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account.

## Library Description

> This library contains API for DIGI POT 5 Click driver.

#### Standard key functions :

- Configuration Object Setup function.
> void digipot5_cfg_setup( digipot5_cfg_t *cfg );
 
- Click Initialization function.
> digipot5_err_t digipot5_init( digipot5_t *ctx, digipot5_cfg_t *cfg );

- Click Default Configuration function.
> void digipot5_default_cfg( digipot5_t *ctx );

#### Example key functions :

- Generic Write function.
> digipot5_err_t digipot5_generic_write( digipot5_t *ctx, digipot5_reg_t reg_addr, uint16_t data_in );
 
- Generic Read function.
> digipot5_err_t digipot5_generic_read( digipot5_t *ctx, digipot5_reg_t reg_addr, uint16_t *data_out );

- Increment Wiper function.
> digipot5_reg_t digipot5_increment_wiper( digipot5_t *ctx, digipot5_reg_t reg_addr );

## Examples Description

>
> This example demonstrates the use of the DIGI POT 5 click board.
>

**The demo application is composed of two sections :**

### Application Init

>
> Initializes all necessary peripherals and pins used for the DIGI POT 5 click.
> Also allows the device to be reset and configured to enable all wipers (4).
> UART console module will be initialized also in this function.
>

```c

void application_init( void )
{
    digipot5_cfg_t digipot5_cfg;
    log_cfg_t console_cfg;

    //  Click initialization.
    digipot5_cfg_setup( &digipot5_cfg );
    DIGIPOT5_MAP_MIKROBUS( digipot5_cfg, MIKROBUS_1 );
    digipot5_init( &digipot5, &digipot5_cfg );
    digipot5_reset( &digipot5 );
    digipot5_default_cfg( &digipot5 );

    //  Console module initialization.
    LOG_MAP_USB_UART( console_cfg );
    console_cfg.baud = 57600;
    log_init( &console, &console_cfg );
    log_write( &console, "***  DIGI POT 5 Initialization Done  ***",
               LOG_FORMAT_LINE );
    log_write( &console, "****************************************",
               LOG_FORMAT_LINE );
}

```

### Application Task

>
> Demonstrates the use of click driver functions by performing a control of
> the all wipers positions. By checking the uart console, user can be informed
> about the all current wipers positions.
>

```c

void application_task( void )
{
    log_write( &console, "* Setting wiper 0 to zero scale.", LOG_FORMAT_LINE );
    digipot5_generic_write( &digipot5, DIGIPOT5_REG_WIPER0_VOL,
                            DIGIPOT5_RES_ZEROSCALE );
    log_write( &console, "* Setting wiper 1 to 3k Ohm.", LOG_FORMAT_LINE );
    digipot5_generic_write( &digipot5, DIGIPOT5_REG_WIPER1_VOL,
                            DIGIPOT5_RES_3KOHM );
    log_write( &console, "* Setting wiper 2 to half scale (5k Ohm).",
               LOG_FORMAT_LINE );
    digipot5_generic_write( &digipot5, DIGIPOT5_REG_WIPER2_VOL,
                            DIGIPOT5_RES_5KOHM_HALFSCALE );
    log_write( &console, "* Setting wiper 3 to full scale (10k Ohm).",
               LOG_FORMAT_LINE );
    digipot5_generic_write( &digipot5, DIGIPOT5_REG_WIPER3_VOL,
                            DIGIPOT5_RES_10KOHM_FULLSCALE );

    Delay_ms( 3000 );
    log_write( &console, "* Decrementing wiper 3 by 5 steps.",
               LOG_FORMAT_LINE );
    for ( i = 0; i < 5; i++ )
    {
        digipot5_decrement_wiper( &digipot5, DIGIPOT5_REG_WIPER3_VOL );
    }

    Delay_ms( 3000 );
    log_write( &console, "* Incrementing wiper 0 by 10 steps.",
               LOG_FORMAT_LINE );
    for ( i = 0; i < 10; i++ )
    {
        digipot5_increment_wiper( &digipot5, DIGIPOT5_REG_WIPER0_VOL );
    }

    Delay_ms( 3000 );
    log_write( &console, "* Setting wiper 0 to 2k Ohm.", LOG_FORMAT_LINE );
    digipot5_generic_write( &digipot5, DIGIPOT5_REG_WIPER0_VOL,
                            DIGIPOT5_RES_2KOHM );
    log_write( &console, "* Setting wiper 1 to 2k Ohm.", LOG_FORMAT_LINE );
    digipot5_generic_write( &digipot5, DIGIPOT5_REG_WIPER1_VOL,
                            DIGIPOT5_RES_2KOHM );
    log_write( &console, "* Setting wiper 2 to 2k Ohm.", LOG_FORMAT_LINE );
    digipot5_generic_write( &digipot5, DIGIPOT5_REG_WIPER2_VOL,
                            DIGIPOT5_RES_2KOHM );
    log_write( &console, "* Setting wiper 3 to 2k Ohm.", LOG_FORMAT_LINE );
    digipot5_generic_write( &digipot5, DIGIPOT5_REG_WIPER3_VOL,
                            DIGIPOT5_RES_2KOHM );

    Delay_ms( 3000 );
    log_write( &console, "****************************************",
               LOG_FORMAT_LINE );
}

```

## Note

>
> Increment/decrement command can be issued only to volatile wiper locations.
>

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DigiPot5

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
