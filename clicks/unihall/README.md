\mainpage Main Page
 
 

---
# UNI HALL Click

UNI HALL Click is a simple solution for adding an unipolar Hall switch to your design. It carries the Melexis US5881 unipolar Hall-effect switch and a 74LVC1T45 single bit, dual supply translating transceiver.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/unihall_click.png" height=300px>
</p>


[Click Product page](https://www.mikroe.com/uni-hall-click)

---


#### Click library 

- **Author**        : Mikroe Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the UniHall Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for UniHall Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void unihall_cfg_setup ( unihall_cfg_t *cfg ); 
 
- Initialization function.
> UNIHALL_RETVAL unihall_init ( unihall_t *ctx, unihall_cfg_t *cfg );

- Click Default Configuration function.
> void unihall_default_cfg ( unihall_t *ctx );


#### Example key functions :

- Detecting north pole magnetic fields status function.
> uint8_t unihall_detecting_magnetic_fields ( unihall_t *ctx );

## Examples Description

> 
> This is a example which demonstrates the use of UNI HALL Click board.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Initialization driver enable's - GPIO and start write log.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    unihall_cfg_t cfg;

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
    log_printf(&logger, " --- Application Init ---\r\n");

    //  Click initialization.

    unihall_cfg_setup( &cfg );
    UNIHALL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    unihall_init( &unihall, &cfg );

    unihall_state = UNIHALL_NORTH_POLE_DETECTED;
    unihall_state_old = UNIHALL_NORTH_POLE_DETECTED;

    log_printf(&logger, "---------------------------\r\n");
    log_printf(&logger, "        Initialization     \r\n");
    log_printf(&logger, "---------------------------\r\n");
    log_printf(&logger, " Detecting magnetic fields \r\n");
    log_printf(&logger, "---------------------------\r\n");

    Delay_ms ( 100 );
}
  
```

### Application Task

>
> Detect the north pole magnetic fields near the UNI HALL Click.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs on usb uart when magnetic field is detected.
> 

```c

void application_task ( void )
{
    unihall_state = unihall_detecting_magnetic_fields( &unihall );

    if ( ( unihall_state == UNIHALL_NORTH_POLE_NOT_DETECTED ) && ( unihall_state_old == UNIHALL_NORTH_POLE_DETECTED ) )
    {
        unihall_state_old = UNIHALL_NORTH_POLE_NOT_DETECTED;
        log_printf(&logger, "      ~ NOT DETECTED ~\r\n");
    }

    if ( ( unihall_state == UNIHALL_NORTH_POLE_DETECTED ) && ( unihall_state_old == UNIHALL_NORTH_POLE_NOT_DETECTED ) )
    {
        
        log_printf(&logger, "        ~ DETECTED ~\r\n");
        unihall_state_old = UNIHALL_NORTH_POLE_DETECTED;
    }
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.UniHall

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
