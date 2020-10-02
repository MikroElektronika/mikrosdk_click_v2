

---
# CapSense click

CapSense click add-on board features a capacitive sensing module CY8C201A0 which takes human body capacitance as an input and directly provides the real time sensor information via I2C output.


<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/capsense_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/capsense-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the CapSense Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for CapSense Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void capsense_cfg_setup ( capsense_cfg_t *cfg ); 
 
- Initialization function.
> CAPSENSE_RETVAL capsense_init ( capsense_t *ctx, capsense_cfg_t *cfg );

- Click Default Configuration function.
> void capsense_default_cfg ( capsense_t *ctx );


#### Example key functions :

- This function gets slider level.
> uint16_t capsense_get_slider_lvl ( capsense_t *ctx );
 

## Examples Description

> This example waits user to press top and bottom button to turn click's LEDs ON or OFF.

**The demo application is composed of two sections :**

### Application Init 

Initialize CapSense click and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    capsense_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    capsense_cfg_setup( &cfg );
    CAPSENSE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    capsense_init( &capsense, &cfg );
    capsense_default_cfg( &capsense );
}
  
```

### Application Task

> Press top and bottom button and turn it ON or OFF button LED's.

```c

void application_task ( void )
{

    uint8_t current_led_state;
    uint8_t button_select;
    uint8_t slider_value;
    uint16_t slider_lvl;
    
    button_select = capsense_read_data( &capsense, CAPSENSE_CS_READ_STATUS0 );
    slider_value = capsense_read_data_bytes( &capsense, CAPSENSE_CS_READ_RAW );
    capsense_write_data( &capsense, CAPSENSE_OUTPUT_PORT0, current_led_state );
    Delay_ms( 100 );

    if ( button_select == 8 )
    {
        current_led_state ^= 0x01;
        Delay_ms( 100 );
    }
    if ( button_select == 16 )
    {
        current_led_state ^= 0x02;
        Delay_ms( 100 );
    }
    if ( button_select == 24 )
    {
        current_led_state = ~current_led_state;
        Delay_ms( 100 );
    }

    slider_lvl = capsense_get_slider_lvl( &capsense );

    if ( slider_value != 0 )
    {
        log_printf( &logger, "Slider lvl. %u \r\n", slider_lvl );
        log_printf( &logger, "Slider value: %u \r\n", slider_value );
        
        Delay_ms( 100 );
    }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.CapSense

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
