\mainpage Main Page
 
 

---
# Slider click

Slider click features a mechanical slide action potentiometer - a slider, which gives a nice feeling when actuating, along with 16 SMD LEDs, that can be used for any kind of visual feedback. The onboard high-resolution 22-bit ADC can detect even the smallest move, faithfully capturing the smoothness of the slider movement, while digitizing its position. The 16 onboard SMD LEDs can give a nice visual feedback of the slider position, but those LEDs can also be used for other purposes since they are not hardwired to the slider.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/slider_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/slider-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Slider Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Slider Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void slider_cfg_setup ( slider_cfg_t *cfg ); 
 
- Initialization function.
> SLIDER_RETVAL slider_init ( slider_t *ctx, slider_cfg_t *cfg );

- Click Default Configuration function.
> void slider_default_cfg ( slider_t *ctx );


#### Example key functions :

- Function calls slider_readADC function, but first checks is ADC conversion finished.
> uint32_t slider_read_adc_and_ready ( slider_t *ctx );
 
- Function enables LED output to shows output laches when state is low, and disables LED output when state is high.
> void slider_enable_led_output ( slider_t *ctx, uint8_t state );

- Function enables output laches to monitor converted ADC value, when state is high.
> void slider_enable_output_laches ( slider_t *ctx, uint8_t state );

## Examples Description

> This example detect even the smallest move, faithfully capturing the smoothness of the slider movement, while digitizing its position. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes click driver

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    slider_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    slider_cfg_setup( &cfg );
    SLIDER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    slider_init( &slider, &cfg );
    slider_default_cfg( &slider );
}
  
```

### Application Task

> Converts analog input voltage (VCC), witch value depends on the slider position, to digital output value, shows result of conversion on LED and logs result on USB UART. 

```c

void application_task ( void )
{
    adc_value = slider_write_output( &slider );
    log_printf( &logger, "%.0f\r\n", adc_value );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Slider

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
