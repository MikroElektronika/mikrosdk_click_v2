\mainpage Main Page
 
 

---
# REED click

REED click is a simple board that carries a standard (Single Pole Single Throw Normally Open) reed switch. A reed switch comprises of two thin magnetic contacts sealed inside a casing.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/reed_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/reed-click)

---


#### Click library 

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the Reed Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Reed Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void reed_cfg_setup ( reed_cfg_t *cfg ); 
 
- Initialization function.
> REED_RETVAL reed_init ( reed_t *ctx, reed_cfg_t *cfg );

- Click Default Configuration function.
> void reed_default_cfg ( reed_t *ctx );


#### Example key functions :

- Get magnetic detected status function.
> uint8_t reed_get_status ( reed_t *ctx );

## Examples Description

> 
> This is a example which demonstrates the use of REED Click board.
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
    reed_cfg_t cfg;

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

    reed_cfg_setup( &cfg );
    REED_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    reed_init( &reed, &cfg );

    reed_state = REED_NO_MAGNETIC_FIELD;
    reed_state_old = REED_NO_MAGNETIC_FIELD;

    log_printf(&logger, "--------------------\r\n");
    log_printf(&logger, "     REED click\r\n");
    log_printf(&logger, "--------------------\r\n");
    Delay_100ms();
}
  
```

### Application Task

>
> Detect the magnetic field near the REED Click.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs on usb uart when magnetic field is detected.
> 

```c

void application_task ( void )
{
    reed_state = reed_get_status( &reed );

    if ( ( reed_state == REED_MAGNETIC_FIELD_DETECTED ) && ( reed_state_old == REED_NO_MAGNETIC_FIELD ) )
    {
        reed_state_old = REED_MAGNETIC_FIELD_DETECTED;
        log_printf(&logger, "     ~ LOCKED ~\r\n");
        log_printf(&logger, "--------------------\r\n");
    }

    if ( ( reed_state == REED_NO_MAGNETIC_FIELD ) && ( reed_state_old == REED_MAGNETIC_FIELD_DETECTED ) )
    {
        log_printf(&logger, "    ~ UNLOCKED ~\r\n");
        log_printf(&logger, "--------------------\r\n");
        reed_state_old = REED_NO_MAGNETIC_FIELD;
    }
} 

```

## Note 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Reed

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
