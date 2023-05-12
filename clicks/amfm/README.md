\mainpage Main Page
 
---
# AMFM click

AM/FM Click is a RADIO RECEIVER click board™ that can be used to listen to music from the AM and FM radio bands.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/amfm_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/amfm-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the AmFm Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for AmFm Click driver.

#### Standard key functions :

- `amfm_cfg_setup` Config Object Initialization function.
```c
void amfm_cfg_setup ( amfm_cfg_t *cfg );
```
 
- `amfm_init` Initialization function.
```c
err_t amfm_init ( amfm_t *ctx, amfm_cfg_t *cfg );
```

- `amfm_default_cfg` Click Default Configuration function.
```c
void amfm_default_cfg ( amfm_t *ctx );
```

#### Example key functions :

- `amfm_tune_up` This function increments current frequency for 10 KHz.
```c
uint8_t amfm_tune_up ( amfm_t *ctx );
```
 
- `amfm_set_volume` This function sets volume level in range: 0 - 63.
```c
uint8_t amfm_set_volume ( amfm_t *ctx, uint8_t volume );
```

- `amfm_get_stc` This function checks STC bit state.
```c
uint8_t amfm_get_stc ( amfm_t *ctx );
```

## Examples Description

> This app simulate RADIO RECEIVER.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    amfm_cfg_t cfg;

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

    amfm_cfg_setup( &cfg );
    AMFM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    amfm_init( &amfm, &cfg );

    Delay_ms( 100 );
    status = amfm_init_device( &amfm );
    if ( 0 == status )
    {
        log_printf( &logger, "> > > app init done < < <\r\n" );
    }
    else if ( 1 == status )
    {
        log_printf( &logger, "> > >    timeout    < < <\r\n" );
    }
    Delay_ms ( 1000 );
    
    amfm_case_seek( &amfm );
    amfm_case_memorize( );
    Delay_ms( 1000 );
    
    amfm_case_seek( &amfm );
    amfm_case_memorize( );
    Delay_ms( 1000 );
    
    amfm_case_seek( &amfm );
    amfm_case_memorize( );
    Delay_ms( 1000 );
    
    amfm_case_seek( &amfm );
    amfm_case_memorize( );
    Delay_ms( 1000 );
    
    amfm_case_seek( &amfm );
    amfm_case_memorize( );
    Delay_ms( 1000 );
    
    amfm_case_plus( &amfm );
    Delay_ms( 1000 );
}
  
```

### Application Task

> Several additional functions are executed and printed over the terminal.

```c

void application_task ( void )
{
    amfm_case_station_1( &amfm );
    Delay_ms( 10000 );
       
    amfm_case_station_2( &amfm );
    Delay_ms( 10000 );
    
    amfm_case_station_3( &amfm );
    Delay_ms( 10000 );
    
    amfm_case_station_4( &amfm );
    Delay_ms( 10000 );
    
    amfm_case_station_5( &amfm );
    Delay_ms( 10000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.AmFm

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
