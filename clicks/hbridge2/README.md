\mainpage Main Page
 
 

---
# H BRIDGE 2 click

< H-Bridge 2 click can be used to drive a motor by utilizing a specific configuration of the output stage MOSFETs, known as the H-bridge. This configuration enables H-Bridge 2 click to drive a motor with up to 1.2A and 15V, providing control of the speed and direction, as well as the dynamic (rheostatic) braking capability >

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hbridge2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/h-bridge-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the HBridge2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for HBridge2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void hbridge2_cfg_setup ( hbridge2_cfg_t *cfg ); 
 
- Initialization function.
> HBRIDGE2_RETVAL hbridge2_init ( hbridge2_t *ctx, hbridge2_cfg_t *cfg );

#### Example key functions :

- Output Set function.
> uint8_t hbridge2_set_output ( hbridge2_t *ctx, uint8_t out_state );
 
- Enable function.
> void hbridge2_enable ( hbridge2_t *ctx, uint8_t state );

- GOUT Set function.
> void hbridge2_set_gout ( hbridge2_t *ctx, uint8_t state );

## Examples Description

> This application controls the speed and direction of motor.

**The demo application is composed of two sections :**

### Application Init 

> Initializes GPIO driver and puts the device to enable state, and the GPIO pin to logic high state.


```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    hbridge2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    hbridge2_cfg_setup( &cfg );
    HBRIDGE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hbridge2_init( &hbridge2, &cfg );

    hbridge2_enable( &hbridge2, HBRIDGE2_ENABLE );
    hbridge2_set_gout( &hbridge2, HBRIDGE2_GOUT_HIGH );
    log_printf( &logger, "H-Bridge 2 is intialized\r\n" );
    Delay_ms( 200 );
}
}
  
```

### Application Task

> Demonstrates the control of output pins by put output pins to different states. The outputs be changed after every 3 seconds.

```c

void application_task ( void )
{
    hbridge2_set_output( &hbridge2, HBRIDGE2_OUT1_H_OUT2_L );
    Delay_ms( 3000 );
    hbridge2_set_output( &hbridge2, HBRIDGE2_OUT1_L_OUT2_H );
    Delay_ms( 3000 );
    hbridge2_set_output( &hbridge2, HBRIDGE2_OUT1_Z_OUT2_Z );
    Delay_ms( 3000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge2

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
