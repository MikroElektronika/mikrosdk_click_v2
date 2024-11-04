

---
# 7seg Click

7seg Click is an accessory board in mikroBUS form factor. 
It’s a compact and easy solution for adding 2-digit seven-segment display to your device.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/7seg_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/7seg-click)

---


#### Click library 

- **Author**        : Mihajlo Djordjevic
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the 7seg Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 7seg Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c7seg_cfg_setup ( c7seg_cfg_t *cfg ); 
 
- Initialization function.
> C7SEG_RETVAL c7seg_init ( c7seg_t *ctx, c7seg_cfg_t *cfg );

- Click Default Configuration function.
> void c7seg_default_cfg ( c7seg_t *ctx );

#### Example key functions :

- This function sets display state for 7seg Click.
> void c7seg_display_mode ( c7seg_t *ctx, uint8_t display_mode );
 
- This function writes left and right number on 7seg display.
> void c7seg_write_data_number ( c7seg_t *ctx, uint8_t left_number, uint8_t right_number );

- This function writes left and right character on 7seg display.
> void c7seg_write_data_character ( c7seg_t *ctx, char left_char, char right_char );

## Examples Description

> 
> Example code consist of two sections: AppInit and AppTask,
> and shows number or character on 7seg display.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Application Init performs Logger and Click Initialization.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c7seg_cfg_t cfg;

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
    log_printf( &logger, "-- Application  Init --\r\n" );
    Delay_ms ( 1000 );

    //  Click initialization.

    c7seg_cfg_setup( &cfg );
    C7SEG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c7seg_init( &c7seg, &cfg );
    
    c7seg_default_cfg ( &c7seg );
    Delay_ms ( 1000 );
}
  
```

### Application Task

>
> Application Task shows functionality of the 7seg Click,
> shows number or character on left and right display.
> 

```c

void application_task ( void )
{
    uint8_t counter;

    c7seg_display_mode( &c7seg, C7SEG_DISPLAY_ON );
    Delay_ms ( 1000 );
    
    for ( counter = 0; counter < 9; counter ++ )
    {
        c7seg_write_data_number( &c7seg, counter, counter + 1 );
        Delay_ms ( 1000 );
    }
    Delay_ms ( 1000 );

    for ( counter = 65; counter < 90; counter ++ )
    {
        c7seg_write_data_character( &c7seg, counter, counter + 1 );
        Delay_ms ( 1000 );
    }
    Delay_ms ( 1000 );

    c7seg_display_mode( &c7seg, C7SEG_DISPLAY_OFF );
    Delay_ms ( 1000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.7seg

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
