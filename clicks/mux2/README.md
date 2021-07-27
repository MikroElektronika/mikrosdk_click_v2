\mainpage Main Page
 
 

---
# MUX 2 click

MUX 2 click is a Click board™ that switches one of the eight inputs to one output. It employs the MUX508, a modern CMOS analog multiplexing integrated circuit, produced by Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mux2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/mux-2-click)

---


#### Click library 

- **Author**        : Luka Filipovic
- **Date**          : Nov 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the Mux2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Mux2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mux2_cfg_setup ( mux2_cfg_t *cfg ); 
 
- Initialization function.
> MUX2_RETVAL mux2_init ( mux2_t *ctx, mux2_cfg_t *cfg );

- Click Default Configuration function.
> void mux2_default_cfg ( mux2_t *ctx );


#### Example key functions :

- Seelect active MUX channel
> void mux2_active_mux_channel (  mux2_t *ctx, uint8_t sel_ch );
 
- Enable MUX device function.
> void mux2_device_disable ( mux2_t *ctx );

- Disable MUX device function.
> void mux2_device_enable ( mux2_t *ctx );

## Examples Description

> Sets the current active channel. Changes the channel every 5 sec.

**The demo application is composed of two sections :**

### Application Init 

> Initializes GPIO module and sets RST, CS, PWM and INT pins as OUTPUT.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    mux2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    mux2_cfg_setup( &cfg );
    MUX2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mux2_init( &mux2, &cfg );
    Delay_ms( 100 );
    
    log_printf( &logger, "       MUX 2 Click\r\n" );
    log_printf( &logger, "------------------------\r\n" );
    
    mux2_device_enable( &mux2 );
    log_printf( &logger, "    Enable MUX device\r\n" );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms( 100 );
}
  
```

### Application Task

> Changes currently active channel every 5 sec.

```c

void application_task ( void )
{
    uint8_t n_cnt;
    
    //  Task implementation.
    
    for ( n_cnt = MUX2_CHANNEL_S1; n_cnt < MUX2_CHANNEL_END; n_cnt++ )
    {
        log_printf( &logger, "      CHANNEL  S%d\r\n", n_cnt );
        log_printf( &logger, "------------------------\r\n" );
        
        mux2_active_mux_channel( &mux2, n_cnt );
        Delay_ms( 5000 );
    }
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Mux2

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
