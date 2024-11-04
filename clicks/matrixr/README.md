\mainpage Main Page

---
# Matrix R Click

Matrix R Click is a mikroBUS add-on board with two red 5x7 matrices driven by two MAX7219 8-bit LED Display Drivers. The active area of each matrix is 7.62mm high and 5.08 mm wide. 7x5 is a standard resolution for displaying ASCII characters, so the Click is essentially a dual-character display capable of showing letters in more readable typefaces compared to a 14-segment display. The Click communicates with the target MCU through the mikroBUS:tm: SPI interface with two separate Chip Select lines for each matrix (CSL for the left, CSR for the right). This board is designed to use a 5V power supply.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/matrixr_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/matrix-r-click)

---


#### Click library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jun 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the MatrixR Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for MatrixR Click driver.

#### Standard key functions :

- `matrixr_cfg_setup` Config Object Initialization function.
```c
void matrixr_cfg_setup ( matrixr_cfg_t *cfg );
```

- `matrixr_init` Initialization function.
```c
MATRIXR_RETVAL matrixr_init ( matrixr_t *ctx, matrixr_cfg_t *cfg );
```

- `matrixr_default_cfg` Click Default Configuration function.
```c
void matrixr_default_cfg ( matrixr_t *ctx );
```

#### Example key functions :

- `matrixr_display_characters` This function displays the specified characters on the L/R segments of the Click.
```c
void matrixr_display_characters ( matrixr_t *ctx, uint8_t left_char, uint8_t right_char );
```

- `matrixr_set_csn_high` This function sets the CSN pin output to high.
```c
void matrixr_set_csn_high ( matrixr_t *ctx );
```

- `matrixr_set_csn_low` This function sets the CSN pin output to low.
```c
void matrixr_set_csn_low ( matrixr_t *ctx );
```

## Example Description

> This example showcases how to prepare the logger and Click modules for use and how to display ASCII characters on both of the LED segments of the Click.

**The demo application is composed of two sections :**

### Application Init

> This function initializes and configures the logger and Click modules. After the initialization of the logger module, communication, mikrobus and pin setup, some of the registers are configured in order for the Click module to work properly.

```c

void application_init ( ) {
   
    log_cfg_t log_cfg;
    matrixr_cfg_t cfg;

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

    matrixr_cfg_setup( &cfg );
    MATRIXR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    matrixr_init( &matrixr, &cfg );
    Delay_ms ( 100 );
    matrixr_default_cfg( &matrixr );
    Delay_ms ( 100 );
}

```

### Application Task

> This function displays two strings on each of the LED segments, showing one character every second. It should display " Mikroelektronika" on the left one and "Mikroelektronika " on the right.

```c

void application_task ( ) {
   
    matrixr_display_characters( &matrixr, ' ', 'M' );
    Delay_ms ( 1000 );
    matrixr_display_characters( &matrixr, 'M', 'i' );
    Delay_ms ( 1000 );
    matrixr_display_characters( &matrixr, 'i', 'k' );
    Delay_ms ( 1000 );
    matrixr_display_characters( &matrixr, 'k', 'r' );
    Delay_ms ( 1000);
    matrixr_display_characters( &matrixr, 'r', 'o' );
    Delay_ms ( 1000 );
    matrixr_display_characters( &matrixr, 'o', 'E' );
    Delay_ms ( 1000 );
    matrixr_display_characters( &matrixr, 'E', 'l' );
    Delay_ms ( 1000 );
    matrixr_display_characters( &matrixr, 'l', 'e' );
    Delay_ms ( 1000 );
    matrixr_display_characters( &matrixr, 'e', 'k' );
    Delay_ms ( 1000 );
    matrixr_display_characters( &matrixr, 'k', 't' );
    Delay_ms ( 1000 );
    matrixr_display_characters( &matrixr, 't', 'r' );
    Delay_ms ( 1000 );
    matrixr_display_characters( &matrixr, 'r', 'o' );
    Delay_ms ( 1000 );
    matrixr_display_characters( &matrixr, 'o', 'n' );
    Delay_ms ( 1000 );
    matrixr_display_characters( &matrixr, 'n', 'i' );
    Delay_ms ( 1000 );
    matrixr_display_characters( &matrixr, 'i', 'k' );
    Delay_ms ( 1000 );
    matrixr_display_characters( &matrixr, 'k', 'a' );
    Delay_ms ( 100 );
    matrixr_display_characters( &matrixr, 'a', ' ' );
    Delay_ms ( 100 );
}

```

## Note

> The Click has two chips, each controlling one of the LED segments, on and requires you to write data to both at the same time. Writing to one specific chip will not work. If you wish to display characters on a single segment, you have to send ' ' characters to the other segment.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.MatrixR

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
