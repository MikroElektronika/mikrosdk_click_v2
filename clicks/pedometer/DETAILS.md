

---
# Pedometer click

Pedometer Click is designed to sense movement, more precisely, to sense and count steps taken by its user.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pedometer_click.png" height=300px>
</p>


[click Product page](<https://www.mikroe.com/pedometer-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Pedometer Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Pedometer Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void pedometer_cfg_setup ( pedometer_cfg_t *cfg ); 
 
- Initialization function.
> PEDOMETER_RETVAL pedometer_init ( pedometer_t *ctx, pedometer_cfg_t *cfg );

- Click Default Configuration function.
> void pedometer_default_cfg ( pedometer_t *ctx );


#### Example key functions :

- Functions for get Interrupt state on the INT pin.
> uint8_t pedometer_get_interrupt_state ( pedometer_t *ctx );
 
- Functions for get step counter.
> uint32_t pedometer_get_step_counter ( pedometer_t *ctx );

- Generic read function.
> void pedometer_generic_read ( pedometer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );


## Examples Description

> This application detected steps. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init and sets step counter on 0.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    pedometer_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ---- \r\n " );
  
```

### Application Task

>It checks if a new step is detected, if detected new step - reads the current number of steps made and logs data to the USBUART. 

```c

void application_task ( void )
{
    //  Task implementation.

    uint8_t new_step;
    uint32_t s_counter;
    char demoText[ 50 ];
    
    new_step = pedometer_process( &pedometer );

    if ( new_step == PEDOMETER_NEW_STEP_DETECTED )
    {
        s_counter = pedometer_get_step_counter( &pedometer );
        log_printf( &logger, " Step Counter : %d \r\n ", s_counter );
       
        Delay_ms( 50 );
    }

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Pedometer

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
