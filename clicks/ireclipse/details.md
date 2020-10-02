

---
# Ir Eclipse click

IR eclipse click carries an EE-SX198 photo interrupter sensor. This sensor consists of an infrared transmitter and receiver facing each other and spaced apart by a 3mm slit.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ireclipse_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/ir-eclipse-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the IrEclipse Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for IrEclipse Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ireclipse_cfg_setup ( ireclipse_cfg_t *cfg ); 
 
- Initialization function.
> IRECLIPSE_RETVAL ireclipse_init ( ireclipse_t *ctx, ireclipse_cfg_t *cfg );

- Click Default Configuration function.
> void ireclipse_default_cfg ( ireclipse_t *ctx );


#### Example key functions :

- Detecting states of IR beam from EE-SX198 photo interrupter sensor.
> uint8_t ireclipse_int_status ( ireclipse_t *ctx );

## Examples Description

> 
> This is an example of IR ECLIPSE click board.
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
    ireclipse_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_printf(&logger, "- Application Init -\r\n");

    //  Click initialization.

    ireclipse_cfg_setup( &cfg );
    IRECLIPSE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ireclipse_init( &ireclipse, &cfg );
    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, "   Start counting:  \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    
    n_cnt = IRECLIPSE_START_CNT_VAL;
    state_old = IRECLIPSE_LOW;
    state_new = IRECLIPSE_LOW;
}
  
```

### Application Task

>
> This is a example which demonstrates the use of IR eclipse Click board.
> When the beam from the transmitter is eclipsed by placing an object in
> the gap ( like a piece of paper ), when the sensor is triggered, the 
> counter is incremented by one. Results are being sent to the Usart 
> Terminal where you can track their changes. Data logs on usb uart 
> when the sensor is triggered.
> 

```c

void application_task ( void )
{
    state_new = ireclipse_int_status( &ireclipse );

    if ( ( state_new == IRECLIPSE_HIGH ) && ( state_old == IRECLIPSE_LOW ) )
    {
        state_old = IRECLIPSE_HIGH;
        log_printf( &logger, "  Counter = %d \r\n", n_cnt );
    
        n_cnt++;
    }

    if ( ( state_new == IRECLIPSE_LOW ) && ( state_old == IRECLIPSE_HIGH ) )
    {
        log_printf( &logger, "--------------------\r\n" );
        state_old = IRECLIPSE_LOW;
    }
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.IrEclipse

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
