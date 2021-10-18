\mainpage Main Page
 
---
# Microwave 2 click

Microwave 2 click is an accurate and reliable short to medium range motion detection Click board™, based on a Doppler radar principle.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/microwave2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/microwave-2-eu-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : UART type


# Software Support

We provide a library for the Microwave2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Microwave2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void microwave2_cfg_setup ( microwave2_cfg_t *cfg ); 
 
- Initialization function.
> MICROWAVE2_RETVAL microwave2_init ( microwave2_t *ctx, microwave2_cfg_t *cfg );

#### Example key functions :

- Set pin DL 
> uint8_t microwave2_dl_state ( microwave2_t *ctx );
 
- Set pin DA
> uint8_t microwave2_da_state ( microwave2_t *ctx );

## Examples Description

> This application is an accurate and reliable short to medium range motion detection.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the click board for communication.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    microwave2_cfg_t cfg;

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

    microwave2_cfg_setup( &cfg );
    MICROWAVE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    microwave2_init( &microwave2, &cfg );
}
  
```

### Application Task

> Data sent from the click board is captured and different actions are applied.

```c

void application_task ( void )
{
    microwave2_process();
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Microwave2

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
