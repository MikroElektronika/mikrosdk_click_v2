\mainpage Main Page

---
# Matrix G click

Matrix G click is a mikroBUS add-on board with two green 5x7 matrices driven by two MAX7219 8-bit LED Display Drivers. The active area of each matrix is 7.62mm high and 5.08 mm wide. 7x5 is a standard resolution for displaying ASCII characters, so the click is essentially a dual-character display capable of showing letters in more readable typefaces compared to a 14-segment display. The click communicates with the target MCU through the mikroBUS SPI interface with two separate Chip Select lines for each matrix (CSL for the left, CSR for the right). This board is designed to use a 5V power supply.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/matrixg_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/matrix-g-click)

---


#### Click library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jun 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the MatrixG Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for MatrixG Click driver.

#### Standard key functions :

- `matrixg_cfg_setup` Config Object Initialization function.
```c
void matrixg_cfg_setup ( matrixg_cfg_t *cfg );
```

- `matrixg_init` Initialization function.
```c
MATRIXG_RETVAL matrixg_init ( matrixg_t *ctx, matrixg_cfg_t *cfg );
```

- `matrixg_default_cfg` Click Default Configuration function.
```c
void matrixg_default_cfg ( matrixg_t *ctx );
```

#### Example key functions :

- `matrixg_display_characters` This function displays the specified characters on the L/R segments of the click.
```c
void matrixg_display_characters ( matrixg_t *ctx, uint8_t left_char, uint8_t right_char );
```

- `matrixg_set_csn_high` This function sets the CSN pin output to high.
```c
void matrixg_set_csn_high ( matrixg_t *ctx );
```

- `matrixg_set_csn_low` This function sets the CSN pin output to low.
```c
void matrixg_set_csn_low ( matrixg_t *ctx );
```

## Example Description

> This example showcases how to prepare the logger and click modules for use and how to display ASCII characters on both of the LED segments of the click.

**The demo application is composed of two sections :**

### Application Init

> This function initializes and configures the logger and click modules. After the initialization of the logger module, communication, mikrobus and pin setup, some of the registers are configured in order for the click module to work properly.

```c

void application_init ( ) {
   
    log_cfg_t log_cfg;
    matrixg_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    matrixg_cfg_setup( &cfg );
    MATRIXG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    matrixg_init( &matrixg, &cfg );
    Delay_ms( 100 );
    matrixg_default_cfg( &matrixg );
    Delay_ms( 100 );
}

```

### Application Task

> This function displays two strings on each of the LED segments, showing one character every second. It should display " Mikroelektronika" on the left one and "Mikroelektronika " on the right.

```c

void application_task ( ) {
   
    matrixg_display_characters( &matrixg, ' ', 'M' );
    Delay_ms( 1000 );
    matrixg_display_characters( &matrixg, 'M', 'i' );
    Delay_ms( 1000 );
    matrixg_display_characters( &matrixg, 'i', 'k' );
    Delay_ms( 1000 );
    matrixg_display_characters( &matrixg, 'k', 'r' );
    Delay_ms( 1000);
    matrixg_display_characters( &matrixg, 'r', 'o' );
    Delay_ms( 1000 );
    matrixg_display_characters( &matrixg, 'o', 'E' );
    Delay_ms( 1000 );
    matrixg_display_characters( &matrixg, 'E', 'l' );
    Delay_ms( 1000 );
    matrixg_display_characters( &matrixg, 'l', 'e' );
    Delay_ms( 1000 );
    matrixg_display_characters( &matrixg, 'e', 'k' );
    Delay_ms( 1000 );
    matrixg_display_characters( &matrixg, 'k', 't' );
    Delay_ms( 1000 );
    matrixg_display_characters( &matrixg, 't', 'r' );
    Delay_ms( 1000 );
    matrixg_display_characters( &matrixg, 'r', 'o' );
    Delay_ms( 1000 );
    matrixg_display_characters( &matrixg, 'o', 'n' );
    Delay_ms( 1000 );
    matrixg_display_characters( &matrixg, 'n', 'i' );
    Delay_ms( 1000 );
    matrixg_display_characters( &matrixg, 'i', 'k' );
    Delay_ms( 1000 );
    matrixg_display_characters( &matrixg, 'k', 'a' );
    Delay_ms( 100 );
    matrixg_display_characters( &matrixg, 'a', ' ' );
    Delay_ms( 100 );
}

```

## Note

> The click has two chips, each controlling one of the LED segments, on and requires you to write data to both at the same time. Writing to one specific chip will not work. If you wish to display characters on a single segment, you have to send ' ' characters to the other segment.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.MatrixG

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
