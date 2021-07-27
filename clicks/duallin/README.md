\mainpage Main Page
 
---
# Dual LIN click

The Dual LIN click is a Click board™ based on the TLE7268SKXUMA1, a Dual LIN transceiver from Infineon.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/duallin_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/dual-lin-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the DualLin Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for DualLin Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void duallin_cfg_setup ( duallin_cfg_t *cfg ); 
 
- Initialization function.
> DUALLIN_RETVAL duallin_init ( duallin_t *ctx, duallin_cfg_t *cfg );

#### Example key functions :

- Sets state of RST pin
> void duallin_bus1_status ( duallin_t *ctx, uint8_t state );
 
- Sets state of  CS pin
> void duallin_bus2_status ( duallin_t *ctx, uint8_t state );

- Send command.
> void duallin_send_command ( duallin_t *ctx, char *command );

## Examples Description

> This example reads and processes data from Dual LIN clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver, and sets bus.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    duallin_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    duallin_cfg_setup( &cfg );
    DUALLIN_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    duallin_init( &duallin, &cfg );

    duallin_bus1_status( &duallin, DUALLIN_PIN_STATE_HIGH );
    duallin_bus2_status( &duallin, DUALLIN_PIN_STATE_LOW );
    Delay_ms( 100 );
}
  
```

### Application Task

> Reads the received data.

```c

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    duallin_process( );
#endif    

#ifdef DEMO_APP_TRANSMITER
    duallin_process( );

    if ( send_data_cnt = 2 )
    {
        duallin_send_command( &duallin, TEXT_TO_SEND );
        duallin_process( );
        send_data_cnt = 0;
    }
    else
    {
        send_data_cnt++;
    }    
#endif
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.DualLin

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
