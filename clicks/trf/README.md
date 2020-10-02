\mainpage Main Page
 
 

---
# tRF click

tRF click is a complete short-range RF communication solution, operating in the 868 MHz ISM license-free frequency band. The Click board™ is based on LE70-868 RF module, from Telit.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/trf_click.png" height=300px>
</p>


[click Product page](<https://www.mikroe.com/trf-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : UART type


# Software Support

We provide a library for the Trf Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Trf Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void trf_cfg_setup ( trf_cfg_t *cfg ); 
 
- Initialization function.
> TRF_RETVAL trf_init ( trf_t *ctx, trf_cfg_t *cfg );

- Click Default Configuration function.
> void trf_default_cfg ( trf_t *ctx );


#### Example key functions :

- Generic single read function.
> trf_data_t trf_generic_single_read ( trf_t *ctx );
 
- Generic single write function.
> void trf_generic_single_write ( trf_t *ctx, trf_data_t tx_data );

- Generic multi write function.
> void trf_generic_multi_write ( trf_t *ctx, trf_data_t *data_buf,  uart_length_t len );

## Examples Description

> 
> This is a example which demonstrates the use of Trf Click board.
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
    trf_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_printf( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    trf_cfg_setup( &cfg );
    TRF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    trf_init( &trf, &cfg );
}
  
```

### Application Task

>
> Checks if new data byte have received in rx buffer (ready for reading),
> and if ready than reads one byte from rx buffer. In second case aplication task writes
> message data via UART.
> 

```c

void application_task ( void )
{
    trf_data_t tmp;
    uint8_t cnt;
    
#ifdef DEMO_APP_RECEIVER

    // RECEIVER - UART polling

    tmp =  trf_generic_single_read( &trf );
    log_printf( &logger, " %c ", tmp );
    
#endif
#ifdef DEMO_APP_TRANSMITER

    // TRANSMITER - TX each 2 sec
       
    for ( cnt = 0; cnt < 9; cnt ++ )
    {
        trf_generic_single_write( &trf, demo_message[ cnt ] );
        Delay_ms( 100 );
    }
       
    Delay_ms( 2000 );
    
#endif
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Trf

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
