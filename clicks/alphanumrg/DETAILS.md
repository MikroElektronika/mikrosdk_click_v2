
---
# Alpha Num RG click

AlphaNumRG click is a simple solution for adding 14-segment alphanumeric display to your device. The board carries two TLC5926 16-bit Constant-Current LED sink Drivers as well as a dual character red LED 14-segment display (with two additional segments for commas). AlphaNum click communicates with the target board through mikroBUS RST, CS, SCK, MISO, MOSI, PWM and INT pins (marked here as LE2, LE1, CLK, DOUT, DIN, NUMSEL and NUMSEL# respectively).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/grupe/alphanumrg-click-group.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/alphanum-r-click>)
[click Product page](<https://www.mikroe.com/alphanum-g-click>)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

We provide a library for the AlphaNumRG Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for AlphaNumRG Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void alphanumrg_cfg_setup ( alphanumrg_cfg_t *cfg ); 
 
- Initialization function.
> ALPHANUMRG_RETVAL alphanumrg_init ( alphanumrg_t *ctx, alphanumrg_cfg_t *cfg );

- Click Default Configuration function.
> void alphanumrg_default_cfg ( alphanumrg_t *ctx );

#### Example key functions :

- This function sets the time interval at which the symbols are displayed.
> void alphanumrg_set_display_interval ( alphanumrg_t *ctx, uint16_t delay_char_display );
 
- This function displays characters on the left and right LED segments.
> void aplhanumrg_write_character ( alphanumrg_t *ctx, uint8_t left_char, uint8_t right_char );

- This function displays numbers on the left and right LED segments.
> void alphanumrg_write_number ( alphanumrg_t *ctx, uint8_t left_char, uint8_t right_char );

## Examples Description

> This example showcases the initialization and configuration of the logger and click modules
  and shows how to display characters and numbers on both LED segments of the click. 

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the logger and click modules.

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    alphanumrg_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    alphanumrg_cfg_setup( &cfg );
    ALPHANUMRG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    alphanumrg_init( &alphanumrg, &cfg );
    Delay_100ms( );
}
  
```

### Application Task

> This function sets the time interval at which the symbols are displayed on the LED 
  segments and shows a few characters and numbers.

```c

void application_task ( )
{
    alphanumrg_set_display_interval( &alphanumrg, 1000 );

    aplhanumrg_write_character( &alphanumrg, 'M', 'E' );
    aplhanumrg_write_character( &alphanumrg, '@', '?' );

    alphanumrg_write_number( &alphanumrg, 0,  1 );
    alphanumrg_write_number( &alphanumrg, 1,  2 );
    alphanumrg_write_number( &alphanumrg, 2,  3 );
    alphanumrg_write_number( &alphanumrg, 3,  4 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.AlphaNumRG

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
