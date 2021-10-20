
---
# OLED W click

OLED W click carries a 96 x 39px white monochrome passive matrix OLED display. The display is bright, has a wide viewing angle and low power consumption.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/oled_w_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/oled-w-click)

---


#### Click library

- **Author**        : Stefan  Ilic
- **Date**          : Jun 2021.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the OLEDW Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for OLEDW Click driver.

#### Standard key functions :

- `oledw_cfg_setup` Config Object Initialization function.
```c
void oledw_cfg_setup ( oledw_cfg_t *cfg );
```

- `oledw_init` Initialization function.
```c
err_t oledw_init ( oledw_t *ctx, oledw_cfg_t *cfg );
```

#### Example key functions :

- `oledw_send` This function sends commands or data to OLED W click.
```c
err_t oledw_send( oledw_t *ctx, oledw_data_t tx_data, oledw_data_mode_t data_mode );
```

- `oledw_display_picture` This function allows user to display picture for page addressing mode.
```c
void oledw_display_picture( oledw_t *ctx, oledw_resources_t *pic );
```

- `oledw_set_contrast` This function sets the display contrast level (0 to 255).
```c
void oledw_set_contrast( oledw_t *ctx, oledw_data_t value );
```

## Example Description

> This example demonstrates the use (control) of the OLED W display.

**The demo application is composed of two sections :**

### Application Init

> Configures the microcontroller for communication and initializes the click board to default state.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    oledw_cfg_t oledw_cfg;  /**< Click config object. */

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
    Delay_ms( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.
    oledw_cfg_setup( &oledw_cfg );
    OLEDW_MAP_MIKROBUS( oledw_cfg, MIKROBUS_1 );
    err_t init_flag  = oledw_init( &oledw, &oledw_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    oledw_default_cfg ( &oledw );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This section contains the main program that is executed showing a practical example on how to use the implemented functions.

```c

void application_task ( void ) {
    uint8_t i;

    oledw_display_picture( &oledw, oledw_img );
    Delay_ms( 500 );
    oledw_send( &oledw, OLEDW_INVERTDISPLAY, OLEDW_COMMAND );
    Delay_ms( 500 );
    oledw_send( &oledw, OLEDW_NORMALDISPLAY, OLEDW_COMMAND );
    Delay_ms( 500 );
    oledw_send( &oledw, OLEDW_INVERTDISPLAY, OLEDW_COMMAND );
    Delay_ms( 500 );
    oledw_send( &oledw, OLEDW_NORMALDISPLAY, OLEDW_COMMAND );
    Delay_ms( 300 );

    for (i = 0xAF; i > 0x00; i--) {
        oledw_set_contrast( &oledw, i );
        Delay_ms( 5 );
    }

    for (i = 0x00; i < 0xAF; i++) {
        oledw_set_contrast( &oledw, i );
        Delay_ms( 5 );
    }

    oledw_scroll_right( &oledw, 0x00, 0x05 );
    Delay_ms( 1000 );
    oledw_stop_scroll( &oledw );
    oledw_display_picture( &oledw, oledw_img );

    oledw_scroll_left( &oledw, 0x00, 0x05 );
    Delay_ms( 1000 );
    oledw_stop_scroll( &oledw );
    oledw_display_picture( &oledw, oledw_img );

    oledw_scroll_diag_right( &oledw, 0x00, 0x05 );
    Delay_ms( 1000 );
    oledw_stop_scroll( &oledw );
    oledw_display_picture( &oledw, oledw_img );

    oledw_scroll_diag_left( &oledw, 0x00, 0x05 );
    Delay_ms( 1000 );
    oledw_stop_scroll( &oledw );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.OLEDW

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
