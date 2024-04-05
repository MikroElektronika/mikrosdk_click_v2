\mainpage Main Page
 
---
# Bargraph 2 click

BarGraph 2 click is a 10-segment bar graph display click, which uses a high-quality, multicolor bar graph LED display. The bar graph display is a very popular device for displaying various properties, whether it be an audio level, current/voltage level, position of the encoder, and generally any property that can be displayed in a form of a bar graph.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/bargraph2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/bargraph-2-click)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Bargraph2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Bargraph2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void bargraph2_cfg_setup ( bargraph2_cfg_t *cfg ); 
 
- Initialization function.
> BARGRAPH2_RETVAL bargraph2_init ( bargraph2_t *ctx, bargraph2_cfg_t *cfg );

#### Example key functions :

- This function turns on the green LED diode of the chosen segment.
> void bargraph2_led_green ( bargraph2_t *ctx, uint8_t index );
 
- This function turns on green LED diodes from the starting index to the end index.
> void bargraph2_leds_green ( bargraph2_t *ctx, int start_index, int end_index );

- This function turns off all the LED diodes.
> void bargraph2_lights_out ( bargraph2_t *ctx );

## Examples Description

> The example starts off with the initalisation and configuration of the logger and click modules and later on showcases different ways of lighting LED diodes on the click.

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the logger and click modules.

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    bargraph2_cfg_t cfg;

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

    bargraph2_cfg_setup( &cfg );
    BARGRAPH2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    bargraph2_init( &bargraph2, &cfg );
}
  
```

### Application Task

> This function shows the user how to light single and multiple LED diodes.

```c
void application_task ( )
{
    uint8_t cnt; 
        
    // Single LED switch
    
    for ( cnt = 1; cnt <= 10 ; cnt++ )
    {
        bargraph2_led_green( &bargraph2, cnt );
        Delay_ms ( 200 );
        bargraph2_led_red( &bargraph2, 10 - ( cnt - 1 ) );
        Delay_ms ( 200 );
    }
    
    bargraph2_lights_out ( &bargraph2 );

    // Multiple LED switch

    bargraph2_leds_green ( &bargraph2, 1, 10 );
    Delay_ms ( 1000 );
    bargraph2_leds_red ( &bargraph2, 1, 10 );
    Delay_ms ( 1000 );
    bargraph2_leds_yellow ( &bargraph2, 1, 10 );
    Delay_ms ( 1000 );
}
``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Bargraph2

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
