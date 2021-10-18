\mainpage Main Page
 
 

---
# Vibra sense click

Vibra Sense click is a low cost micro shock vibration sensor with a digital output which can be set as an Interrupt (mikroBUS INT pin) An onboard potentiometer lets you set the interrupt threshold.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/vibrasense_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/vibra-sense-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the VibraSense Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for VibraSense Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void vibrasense_cfg_setup ( vibrasense_cfg_t *cfg ); 
 
- Initialization function.
> VIBRASENSE_RETVAL vibrasense_init ( vibrasense_t *ctx, vibrasense_cfg_t *cfg );

- Click Default Configuration function.
> void vibrasense_default_cfg ( vibrasense_t *ctx );


#### Example key functions :

- Check interrupt function.
> uint8_t vibrasense_check_interrupt ( vibrasense_t *ctx ) ;
 
- Reset vibra sense function.
> void vibrasense_reset ( vibrasense_t *ctx );

## Examples Description

> 
> This is a example which demonstrates the use of Vibra sense Click board.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Configuring clicks and log objects.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    vibrasense_cfg_t cfg;

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
    log_printf(&logger, "- Application Init -\r\n");

    //  Click initialization.

    vibrasense_cfg_setup( &cfg );
    VIBRASENSE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    vibrasense_init( &vibrasense, &cfg );
    Delay_ms( 100 );
    
    log_printf(&logger, "--------------------\r\n");
    log_printf(&logger, "  Vibra sense Click \r\n");
    log_printf(&logger, "--------------------\r\n");

    vibrasense_set_mode( &vibrasense, VIBRASENSE_ENABLE );
    Delay_ms( 100 );
}
  
```

### Application Task

>
> It detects vibrations and enables PWM and writes log according to them.
> 

```c

void application_task ( void )
{
    if ( vibrasense_check_interrupt( &vibrasense ) )
    {
        log_printf(&logger, "       TILT !!!     \r\n");
        log_printf(&logger, "--------------------\r\n");
        Delay_ms( 100 );
    }
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.VibraSense

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
