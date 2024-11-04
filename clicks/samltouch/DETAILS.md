
---
# SAML Touch Click

SAML Touch Click is a Click board™ equipped with two capacitive touch pads and one capacitive slider.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/samltouch_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/saml-touch-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the SamlTouch Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for SamlTouch Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void samltouch_cfg_setup ( samltouch_cfg_t *cfg ); 
 
- Initialization function.
> SAMLTOUCH_RETVAL samltouch_init ( samltouch_t *ctx, samltouch_cfg_t *cfg );

#### Example key functions :

- Generic write function.
> void samltouch_generic_write ( samltouch_t *ctx, char *data_buf, uint16_t len );
 
- Generic read function.
> uint16_t samltouch_generic_read ( samltouch_t *ctx, char *data_buf, uint16_t max_len );

- Generic parser function.
> void samltouch_parser ( char *data_in, samltouch_state_t *state );

## Examples Description

> This example reads and processes data from SAML Touch clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    samltouch_cfg_t cfg;

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

    samltouch_cfg_setup( &cfg );
    SAMLTOUCH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    samltouch_init( &samltouch, &cfg );
    
    Delay_ms ( 500 );
}
  
```

### Application Task

> Reads the received data and parses it.

```c

void application_task ( void )
{
    parser_application( );
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.SamlTouch

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
