\mainpage Main Page

 

---
# OLED BW click

OLED B/W click carries a 96 x 39px blue/white monochrome passive matrix OLED display.
The display is bright, has a wide viewing angle and low power consumption.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/grupe/oled-click-group.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/click-package/oled-click>)

---


#### Click library

- **Author**        : Nemanja Medakovic
- **Date**          : Nov 2019.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the OledBW Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers).
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account.

## Library Description

> This library contains API for OLED BW Click driver.

#### Standard key functions :

- Configuration Object Setup function.
> void oledbw_cfg_setup( oledbw_cfg_t *cfg );
 
- Click Initialization function.
> OLEDBW_RETVAL oledbw_init( oledbw_t *ctx, oledbw_cfg_t *cfg );

- Click Default Configuration function.
> void oledbw_default_cfg( oledbw_t *ctx );

#### Example key functions :

- Send function.
> OLEDBW_RETVAL oledbw_send( oledbw_t *ctx, oledbw_data_t tx_data, oledbw_data_mode_t data_mode );
 
- Display Picture function.
> void oledbw_display_picture( oledbw_t *ctx, oledbw_resources_t *pic );

- Scroll Diagonally Right function.
> void oledbw_scroll_diag_right( oledbw_t *ctx, oledbw_data_t start_page_addr, oledbw_data_t end_page_addr );

## Examples Description

>
> This example demonstrates the use (control) of the OLED B/W display.
>

**The demo application is composed of two sections :**

### Application Init

>
> Configures the microcontroller for communication and initializes the click board to default state.
>

```c

void application_init( void )
{
    oledbw_cfg_t oledbw_cfg;

    oledbw_cfg_setup( &oledbw_cfg );
    OLEDBW_MAP_MIKROBUS( oledbw_cfg, MIKROBUS_1 );
    oledbw_init( &oledbw, &oledbw_cfg );

    oledbw_default_cfg( &oledbw );
}

```

### Application Task

>
> This section contains the main program that is executed showing a practical
> example on how to use the implemented functions.
>

```c

void application_task( void )
{
    uint8_t i;

    oledbw_display_picture( &oledbw, oledbw_img );
    Delay_ms( 500 );
    oledbw_send( &oledbw, OLEDBW_INVERTDISPLAY, OLEDBW_COMMAND );
    Delay_ms( 500 );
    oledbw_send( &oledbw, OLEDBW_NORMALDISPLAY, OLEDBW_COMMAND );
    Delay_ms( 500 );
    oledbw_send( &oledbw, OLEDBW_INVERTDISPLAY, OLEDBW_COMMAND );
    Delay_ms( 500 );
    oledbw_send( &oledbw, OLEDBW_NORMALDISPLAY, OLEDBW_COMMAND );
    Delay_ms( 300 );

    for (i = 0xAF; i > 0x00; i--)
    {
        oledbw_set_contrast( &oledbw, i );
        Delay_ms( 5 );
    }

    for (i = 0x00; i < 0xAF; i++)
    {
        oledbw_set_contrast( &oledbw, i );
        Delay_ms( 5 );
    }

    oledbw_scroll_right( &oledbw, 0x00, 0x05 );
    Delay_ms( 1000 );
    oledbw_stop_scroll( &oledbw );
    oledbw_display_picture( &oledbw, oledbw_img );

    oledbw_scroll_left( &oledbw, 0x00, 0x05 );
    Delay_ms( 1000 );
    oledbw_stop_scroll( &oledbw );
    oledbw_display_picture( &oledbw, oledbw_img );

    oledbw_scroll_diag_right( &oledbw, 0x00, 0x05 );
    Delay_ms( 1000 );
    oledbw_stop_scroll( &oledbw );
    oledbw_display_picture( &oledbw, oledbw_img );

    oledbw_scroll_diag_left( &oledbw, 0x00, 0x05 );
    Delay_ms( 1000 );
    oledbw_stop_scroll( &oledbw );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- Click.OledBW

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
