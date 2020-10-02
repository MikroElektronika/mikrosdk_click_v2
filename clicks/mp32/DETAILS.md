
---
# MP3 2 click

MP3 2 Click is an audio decoder expansion board with on-board microSD card slot, that enables you to create your personal audio playback system. It holds the KT403A,a SOC chip solution with intergraded MCU, hardware audio MP3/WAV decoder and DSP, from Shenzhen Qianle Microelectronics Technology Co.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mp32_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/mp3-2-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the Mp32 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Mp32 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mp32_cfg_setup ( mp32_cfg_t *cfg ); 
 
- Initialization function.
> MP32_RETVAL mp32_init ( mp32_t *ctx, mp32_cfg_t *cfg );

- Click Default Configuration function.
> void mp32_default_cfg ( mp32_t *ctx );


#### Example key functions :

- Reset the device function.
> void mp32_hw_reset ( mp32_t *ctx );
 
- Received response data function.
> void mp32_rx_cmd ( mp32_t *ctx, uint8_t *rd_data, uint8_t len );

- Write command function.
> void mp32_tx_cmd ( mp32_t *ctx, uint8_t cmd, uint16_t spec_data );

## Examples Description

> This example reads and processes data from MP3 2 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - UART,
 reset the device, set specify a device play tracks inside ( SD Card ),
 set volume lvl ( 50% ), set equalizer to normal mode and
 set commmand for specifying a track to play.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    mp32_cfg_t cfg;

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    mp32_cfg_setup( &cfg );
    MP32_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mp32_init( &mp32, &cfg );

    Delay_ms( 500 );

    log_printf( &logger, "-------------------------/r/n" );
    log_printf( &logger, "       MP3 2 click       /r/n" );
    log_printf( &logger, "-------------------------/r/n" );
    Delay_100ms( );

    mp32_hw_reset( &mp32 );
    Delay_ms( 100 );
    mp32_hw_reset( &mp32 );
    mp32_set_device( &mp32, MP32_SDCARD );
    mp32_set_volume( &mp32, 50 );
    mp32_set_eq( &mp32, MP32_EQ_NORMAL );
    Delay_ms( 100 );
    
    mp32_play_specific ( &mp32, 1 );
}
  
```

### Application Task

> This is an example which demonstrates the use of MP3 2 click board.
 Waits for valid user input and executes functions based 
 on set of valid commands.
 Results are being sent to the Usart Terminal where you can track their changes. 

```c

void application_task ( void )
{
    char received_data;
     
    mp32_play_mode( &mp32 );
    log_printf( &logger, " >>> Play\r\n" );
    Delay_ms( 5000 );

    mp32_stop_mode( &mp32 );
    log_printf( &logger, " >>> Stop\r\n" );
    Delay_ms( 5000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Mp32

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
