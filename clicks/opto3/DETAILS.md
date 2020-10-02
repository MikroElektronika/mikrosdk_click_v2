
---
# Opto 3 click

Opto 3 click is a relay Click board™, equipped with two pairs of optically isolated solid-state relays (SSR).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/opto3_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/opto-3-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the Opto3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Opto3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void opto3_cfg_setup ( opto3_cfg_t *cfg ); 
 
- Initialization function.
> OPTO3_RETVAL opto3_init ( opto3_t *ctx, opto3_cfg_t *cfg );


#### Example key functions :

- Gets input
> OPTO3_STATE opto3_get_in1 ( opto3_t *ctx );
 
- Gets input
> OPTO3_STATE opto3_get_in2 ( opto3_t *ctx );

- Gets output
>  void opto3_set_out1 ( opto3_t *ctx, OPTO3_SWITCH state );

- Gets output
>  void opto3_set_out2 ( opto3_t *ctx, OPTO3_SWITCH state );

## Examples Description

> Opto 3 click to be used in applications that require reinforced galvanic 
> isolation for both their input and output stages.

**The demo application is composed of two sections :**

### Application Init 

> Initializes GPIO interface.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    opto3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    opto3_cfg_setup( &cfg );
    OPTO3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    opto3_init( &opto3, &cfg );

    log_printf( &logger, "** Opto 3 is initialized **\r\n" );
}
```

### Application Task

> Switches ON or switches OFF the both outputs depending on the
> states of the inputs, respectively.

```c
void application_task ( void )
{
    OPTO3_STATE state_in1;
    OPTO3_STATE state_in2;
    OPTO3_SWITCH state_out1;
    OPTO3_SWITCH state_out2;

    state_in1 = opto3_get_in1( &opto3 );
    state_in2 = opto3_get_in2( &opto3 );
    
    state_out1 = state_in1 ^ 1;
    state_out2 = state_in2 ^ 1;
    
    log_printf( &logger, "** Opto 3 out1 is**\r\n" );
    opto3_set_out1( &opto3, state_out1 );
    log_printf( &logger, "** Opto 3 out2 is **\r\n" );
    opto3_set_out2( &opto3, state_out2 );
}
```

## Note

> Input state is active low, and output state is active high.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Opto3

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
