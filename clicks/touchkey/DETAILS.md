

---
# TouchKey click

> Touchkey click has four capacitive pads powered by TTP224, a touchpad detector IC. Capacitive buttons like these can be toggled even when placed under a layer of glass or paper. The board outputs an interrupt signals for each pad: OUTA, OUTB,OUTC and OUTD (in place of default mikroBUS RST, AN, PWM and INT pins, respectively). The TTP224 IC has several operating modes which are accessed through onboard jumpers. Modes include Fast or low power (the response time is just 100mS at fast mode and 200mS at low power). Single-key or multi-key, direct or toggle buttons, and so on.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/touchkey_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/touchkey-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the TouchKey Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for TouchKey Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void touchkey_cfg_setup ( touchkey_cfg_t *cfg ); 
 
- Initialization function.
> TOUCHKEY_RETVAL touchkey_init ( touchkey_t *ctx, touchkey_cfg_t *cfg );

- Click Default Configuration function.
> void touchkey_default_cfg ( touchkey_t *ctx );


#### Example key functions :

- Function gets state of "a" (RST) pin on TouchKey Click board. 
> uint8_t touchkey_a ( touchkey_t *ctx );

- Function gets state of "b" (AN) pin on TouchKey Click board.
> uint8_t touchkey_b ( touchkey_t *ctx );

- Function gets state of "c" (PWM) pin on TouchKey Click board.
> uint8_t touchkey_c ( touchkey_t *ctx );

- Function gets state of "d" (INT) pin on TouchKey Click board.
> uint8_t touchkey_d ( touchkey_t *ctx );

## Examples Description

> This application has four capacitive pads powered by TTP224, a touchpad detector IC. 
> Capacitive buttons like these can be toggled even when placed under a layer of glass or paper.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables GPIO and also starts write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    touchkey_cfg_t cfg;

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

    touchkey_cfg_setup( &cfg );
    TOUCHKEY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    touchkey_init( &touchkey, &cfg );
}
  
```

### Application Task

> This example demonstrates the use of TouchKey Click board.
> Detects whether any of the keys is pressed. 
> Results are being sent to the Usart Terminal, where you can track changes.

```c

void application_task ( void )
{
    
    key_state = touchkey_a( &touchkey ) | touchkey_b( &touchkey ) | touchkey_c( &touchkey ) | touchkey_d( &touchkey );

    if( key_state == 1 && key_state_old == 0  )
    {
        log_info( &logger,"Pressed : " );

        if( touchkey_a( &touchkey ) )
        {
            log_info( &logger, "A " );
        }
        if( touchkey_b( &touchkey) )
        {
            log_info( &logger, "B " );
        }
        if( touchkey_c( &touchkey ) )
        {
            log_info( &logger, "C " );;
        }
        if( touchkey_d( &touchkey ) )
        {
            log_info( &logger, "D " );
        }

        log_info( &logger, "" );
        key_state_old = 1;
    }
    if ( key_state == 0 && key_state_old == 1 )
    {
        key_state_old = 0;
    }

}

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.TouchKey

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
