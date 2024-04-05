
---
# MP3 2 click

MP3 2 Click is an audio decoder expansion board with on-board microSD card slot, that enables you to create your personal audio playback system. It holds the KT403A,a SOC chip solution with intergraded MCU, hardware audio MP3/WAV decoder and DSP, from Shenzhen Qianle Microelectronics Technology Co.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mp32_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/mp3-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type


# Software Support

We provide a library for the Mp32 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Mp32 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mp32_cfg_setup ( mp32_cfg_t *cfg ); 
 
- Initialization function.
> MP32_RETVAL mp32_init ( mp32_t *ctx, mp32_cfg_t *cfg );

#### Example key functions :

- Reset the device function.
> void mp32_hw_reset ( mp32_t *ctx );
 
- Received response data function.
> void mp32_rx_cmd ( mp32_t *ctx, uint8_t *rd_data, uint8_t len );

- Write command function.
> void mp32_tx_cmd ( mp32_t *ctx, uint8_t cmd, uint16_t spec_data );

## Examples Description

> This example demonstates the use of MP3 2 Click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and enables the click board.
> Then sets the device to play songs from SD Card, and after that sets volume, and equalizer.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    mp32_cfg_t cfg;

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

    mp32_cfg_setup( &cfg );
    MP32_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mp32_init( &mp32, &cfg );

    Delay_ms ( 500 );

    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "       MP3 2 click       \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_100ms( );

    mp32_hw_reset( &mp32 );
    Delay_ms ( 100 );
    
    mp32_set_device( &mp32, MP32_SDCARD );
    mp32_set_volume( &mp32, 50 );
    mp32_set_eq( &mp32, MP32_EQ_NORMAL );
    Delay_ms ( 100 );
}
  
```

### Application Task

> Demonstrates the use of play, play next, and pause modes.
> Each step will be logged on the USB UART where you can track the program flow.

```c

void application_task ( void )
{
    log_printf( &logger, " >>> Play\r\n" );
    mp32_play_mode( &mp32 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " >>> Next song\r\n" );
    mp32_play_next( &mp32 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " >>> Pause\r\n" );
    mp32_pause_mode( &mp32 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );        
}  

```

## Note

> A valid microSD Card that contains at least one mp3 sound on it needs to be inserted into the click board.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Mp32

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
