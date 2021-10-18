
---
# StereoAmp click

This is an example which demonstrates the use of StereoAmp Click board - stereo amplifier and is ideal for battery operated devices or as a lab amplifier.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stereoamp_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/stereoamp-click)

---


#### Click library 

- **Author**        : Mihajlo Djordjevic
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the StereoAmp Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly from compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for StereoAmp Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void stereoamp_cfg_setup ( stereoamp_cfg_t *cfg ); 
 
- Initialization function.
> STEREOAMP_RETVAL stereoamp_init ( stereoamp_t *ctx, stereoamp_cfg_t *cfg );

- Click Default Configuration function.
> void stereoamp_default_cfg ( stereoamp_t *ctx );


#### Example key functions :

- This function set the power On of both channels by write to the Mode Control register address of LM48100Q-Q1 chip on StereoAmp click board.
> void stereoamp_set_power_on ( stereoamp_t *ctx );
 
- This function set the volume of both channels to the Volume Control register address of LM48100Q-Q1 chip on StereoAmp click board.
> void stereoamp_set_volume ( stereoamp_t *ctx, uint8_t volume );

## Examples Description

> 
> This example shows how to initialize amplifiers and set volume control registers on the fly.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Application Init perfroms Logger and Click initialization.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    stereoamp_cfg_t cfg;

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
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "     Application  Init\r\n" );
    Delay_ms ( 500 );

    //  Click initialization.

    stereoamp_cfg_setup( &cfg );
    STEREOAMP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    stereoamp_init( &stereoamp, &cfg );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " ---  StereoAmp Click --- \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    
    stereoamp_default_cfg( &stereoamp );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "         Power  On        \r\n" );
    stereoamp_set_power_on( &stereoamp );
    Delay_ms ( 1000 );
    log_printf( &logger, "--------------------------\r\n" );
    
    log_printf( &logger, "     Set Volume: -80dB    \r\n" );
    stereoamp_set_volume( &stereoamp, STEREOAMP_GAIN_NEG_80dB );
    Delay_ms ( 1000 );
    log_printf( &logger, "--------------------------\r\n" );
    
    log_printf( &logger, "       Enable Fault       \r\n" );
    stereoamp_enable_fault( &stereoamp );
    Delay_ms ( 1000 );
    log_printf( &logger, "--------------------------\r\n" );
    
    log_printf( &logger, "     Enable Diagnostic    \r\n" );
    stereoamp_enable_diagnostic( &stereoamp );
    Delay_ms ( 1000 );
    log_printf( &logger, "--------------------------\r\n" );
    
    log_printf( &logger, " -- Initialization done --\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 500 );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " -----  Play  Music ----- \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 500 );
}
  
```

### Application Task

>
> This examples first set volume level 20 of 31 ( gain: 1,5 dB ) for 10 seconds. 
> After that, we increase the volume to level 10 ( gain: -13,5 dB ) for the next 10 seconds. 
> Results are being sent to the UART Terminal where you can track their changes.
> 

```c

void application_task ( void )
{
    log_printf( &logger, "        Gain 1.5 dB        \r\n" );
    stereoamp_set_volume( &stereoamp, STEREOAMP_GAIN_1_5dB );
    Delay_ms ( 10000 );
    log_printf( &logger, "--------------------------\r\n" );
    
    log_printf( &logger, "        Gain -13.5 dB      \r\n" );
    stereoamp_set_volume( &stereoamp, STEREOAMP_GAIN_NEG_13_5dB );
    Delay_ms ( 10000 );
    log_printf( &logger, "--------------------------\r\n" );
}  

```

The full application code, and ready to use projects can be  installed directly from compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.StereoAmp

**Additional notes and infromations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
