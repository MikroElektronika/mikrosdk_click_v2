
---
# Tilt 2 click

Tilt 2 click is a tilt sensor switch, which breaks the circuit when tilted to an angle of 45° or when shaken. It is a single-pole-double-throw type of switch (SPDT), which can be operated with up to 24V.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/tilt2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/tilt-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the Tilt2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Tilt2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void tilt2_cfg_setup ( tilt2_cfg_t *cfg ); 
 
- Initialization function.
> TILT2_RETVAL tilt2_init ( tilt2_t *ctx, tilt2_cfg_t *cfg );

- Click Default Configuration function.
> void tilt2_default_cfg ( tilt2_t *ctx );


#### Example key functions :

- This function detection tilt.
> uint8_t tilt2_tilt_detection ( tilt2_t *ctx );
 
## Examples Description

> This app detection tilt.

**The demo application is composed of two sections :**

### Application Init 

> Initialization device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    tilt2_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----\r\n");

    //  Click initialization.

    tilt2_cfg_setup( &cfg );
    TILT2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    tilt2_init( &tilt2, &cfg );
}
  
```

### Application Task

> Tilt detection, if the tilt is detected, the message is logs on USBUART.

```c

void application_task ( void )
{
    uint8_t tilt;
    
    tilt = tilt2_tilt_detection( &tilt2 );
    if ( tilt == TILT2_TILT_DETECTION )
    {
        log_printf( &logger, " Tilt detection.. \r\n" );
        Delay_ms( 300 );
    }
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Tilt2

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
