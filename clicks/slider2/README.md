\mainpage Main Page
 
 

---
# Slider 2 Click

The Slider 2 Click is a very accurate potentiometer Click Board, featuring a high-quality mechanical slide-action potentiometer (slider), which in conjunction with the accurate voltage reference IC, provides very precise analog control voltage (CV) at its output. Featuring an accurate voltage reference IC, the output of the Click board™ can be directly sampled by the A/D peripheral of the microcontroller (MCU).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/slider2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/slider-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : ADC type


# Software Support

We provide a library for the Slider2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Slider2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void slider2_cfg_setup ( slider2_cfg_t *cfg ); 
 
- Initialization function.
> SLIDER2_RETVAL slider2_init ( slider2_t *ctx, slider2_cfg_t *cfg );

- Click Default Configuration function.
> void slider2_default_cfg ( slider2_t *ctx );


#### Example key functions :

- This function sets desired state to EN pin.
> void slider2_enable ( slider2_t *ctx, uint8_t state );
 
- This function sets desired reference to RSL pin.
> void slider2_set_reference ( slider2_t *ctx, uint8_t ref );


## Examples Description

> This Click utilizes potentiometer with long travel distance of the wiper 
> witch allows more accurate movements and combined with the high-quality 
> manufacturing process it allows to dial-in the desired voltage with ease.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init and ADC init.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    slider2_cfg_t cfg;

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

    slider2_cfg_setup( &cfg );
    SLIDER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    slider2_init( &slider2, &cfg );
    slider2_default_cfg( &slider2);

}
  
```

### Application Task

> Read Slider data value and this data logs to terminal every 500ms.

```c

void application_task ( void )
{
    slider2_data_t tmp;
        
    tmp = slider2_generic_read ( &slider2 );
    log_printf( &logger, "** ADC value : [DEC]- %d, [HEX]- 0x%x \r\n", tmp, tmp );
    
    Delay_ms ( 500 );

}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Slider2

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
