\mainpage Main Page

---
# Matrix RG click

Matrix RG click is a mikroBUS add-on board with two red 5x7 matrices driven by two MAX7219 8-bit LED Display Drivers. The active area of each matrix is 7.62mm high and 5.08 mm wide.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/grupe/matrixgr-click-group.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/matrix-r-click>)

[click Product page](<https://www.mikroe.com/matrix-g-click>)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the MatrixRG Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for MatrixRG Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void matrixrg_cfg_setup ( matrixrg_cfg_t *cfg ); 
 
- Initialization function.
> MATRIXRG_RETVAL matrixrg_init ( matrixrg_t *ctx, matrixrg_cfg_t *cfg );

- Click Default Configuration function.
> void matrixrg_default_cfg ( matrixrg_t *ctx );


#### Example key functions :

- This function displays the specified characters on the L/R segments of the click.
> void matrixrg_display_characters ( matrixrg_t *ctx, uint8_t left_char, uint8_t right_char );
 
- This function sets the CSN pin output to high.
> void matrixrg_set_csn_high ( matrixrg_t *ctx );

- This function sets the CSN pin output to low.
> void matrixrg_set_csn_low ( matrixrg_t *ctx );

## Examples Description

> This example showcases how to prepare the logger and click modules for use and how to display ASCII characters on both of the LED segments of the click.

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the logger and click modules. After the initialization
of the logger module, communication, mikrobus and pin setup, some of the registers are configured in order for the click module to work properly.

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    matrixrg_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    matrixrg_cfg_setup( &cfg );
    MATRIXRG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    matrixrg_init( &matrixrg, &cfg );
    Delay_100ms( );
    matrixrg_default_cfg( &matrixrg );
    Delay_100ms( );
}
  
```

### Application Task

> This function displays two strings on each of the LED segments, showing one character every
second. It should display " Mikroelektronika" on the left one and "Mikroelektronika " on the 
right. 

```c

void application_task ( )
{
    matrixrg_display_character( &matrixrg, ' ', 'M' );
    Delay_1sec( );
    matrixrg_display_character( &matrixrg, 'M', 'i' );
    Delay_1sec( );
    matrixrg_display_character( &matrixrg, 'i', 'k' );
    Delay_1sec( );
    matrixrg_display_character( &matrixrg, 'k', 'r' );
    Delay_1sec( );
    matrixrg_display_character( &matrixrg, 'r', 'o' );
    Delay_1sec( );
    matrixrg_display_character( &matrixrg, 'o', 'E' );
    Delay_1sec( );
    matrixrg_display_character( &matrixrg, 'E', 'l' );
    Delay_1sec( );
    matrixrg_display_character( &matrixrg, 'l', 'e' );
    Delay_1sec( );
    matrixrg_display_character( &matrixrg, 'e', 'k' );
    Delay_1sec( );
    matrixrg_display_character( &matrixrg, 'k', 't' );
    Delay_1sec( );
    matrixrg_display_character( &matrixrg, 't', 'r' );
    Delay_1sec( );
    matrixrg_display_character( &matrixrg, 'r', 'o' );
    Delay_1sec( );
    matrixrg_display_character( &matrixrg, 'o', 'n' );
    Delay_1sec( );
    matrixrg_display_character( &matrixrg, 'n', 'i' );
    Delay_1sec( );
    matrixrg_display_character( &matrixrg, 'i', 'k' );
    Delay_1sec( );
    matrixrg_display_character( &matrixrg, 'k', 'a' );
    Delay_1sec( );
    matrixrg_display_character( &matrixrg, 'a', ' ' );
    Delay_1sec( );
} 

```

## Note

> The click has two chips, each controlling one of the LED segments, on and requires you to write
data to both at the same time. Writing to one specific chip will not work. If you wish to display
characters on a single segment, you have to send ' ' characters to the other segment.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.MatrixRG

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
