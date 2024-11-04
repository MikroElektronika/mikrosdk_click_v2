
---
# Tamper 2 Click

Tamper 2 Click contains a levered D2HW-A221D switch by Omron, which outputs signal in both positions - pressed and released.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/tamper2_click.png" height=300px>
</p>


[Click Product page](https://www.mikroe.com/tamper-2-click)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the Tamper2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Tamper2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void tamper2_cfg_setup ( tamper2_cfg_t *cfg ); 
 
- Initialization function.
> TAMPER2_RETVAL tamper2_init ( tamper2_t *ctx, tamper2_cfg_t *cfg );


#### Example key functions :

- Switch ON detect
> uint8_t tamper2_get_on_state ( tamper2_t *ctx );
 
- Switch OFF detect
> uint8_t tamper2_get_off_state ( tamper2_t *ctx );

## Examples Description

> This application sets switch on ON or OFF.

**The demo application is composed of two sections :**

### Application Init 

> Sends HAL pointers

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    tamper2_cfg_t cfg;

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

    tamper2_cfg_setup( &cfg );
    TAMPER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    tamper2_init( &tamper2, &cfg );
}
```

### Application Task

> Detects whether the state of switch on Tamper 2 Click is ON or OFF.

```c
void application_task ( )
{
    uint8_t on_state;
    uint8_t off_state;

    on_state = tamper2_get_on_state( &tamper2 );
    off_state = tamper2_get_off_state( &tamper2 );

    if ( on_state == 1 )
    {
        log_printf( &logger, "Tamper 2 Click is in ON state.\r\n" );
		
    }

    if ( off_state == 1 )
    {
       log_printf( &logger, "Tamper 2 Click is in OFF state.\r\n" );
		
    }

    Delay_ms ( 200 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Tamper2

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
