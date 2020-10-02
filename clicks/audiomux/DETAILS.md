

---
# AudioMUX click

AudioMUX click is a sound processing Click board™ with digital controls, based on the TDA7468D IC. It can be used to select one of four audio input channels, adjust its frequency response and volume, and send it to the output.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/audiomux_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/audiomux-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the AudioMUX Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for AudioMUX Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void audiomux_cfg_setup ( audiomux_cfg_t *cfg ); 
 
- Initialization function.
> AUDIOMUX_RETVAL audiomux_init ( audiomux_t *ctx, audiomux_cfg_t *cfg );

- Click Default Configuration function.
> void audiomux_default_cfg ( audiomux_t *ctx );


#### Example key functions :

- This function performs a input selection and control.
> T_AUDIOMUX_RETVAL audiomux_select_input ( audiomux_t *ctx, uint8_t input_sel, uint8_t mute_in,
>                                           uint8_t mic_gain, uint8_t mic_state );
 
- This function performs a left or right volume control.
> T_AUDIOMUX_RETVAL audiomux_set_volume ( audiomux_t *ctx, uint8_t volume1, uint8_t volume2,
>                                         uint8_t side_sel );

- This function performs a control of the treble and bass for EQ section.
> T_AUDIOMUX_RETVAL audiomux_set_treble_bass ( audiomux_t *ctx, uint8_t treble, uint8_t bass );

## Examples Description

The following demo shows basic click functionality:
Initializes AudioMUX device to work with the desired configurations and
shows a message on uart when playing is started. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes click and logger driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    audiomux_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    audiomux_cfg_setup( &cfg );
    AUDIOMUX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    audiomux_init( &audiomux, &cfg );

    init_check = 0;
    mess_cnt   = 0;

    log_info( &logger, "** AudioMUX initialized **\r\n" );
}
  
```

### Application Task

> Plays selected channel and shows output on the terminal.

```c

void application_task ( void )
{
    if (init_check == 0)
    {
        audiomux_default_cfg ( &audiomux );
        init_check = 1;

        log_printf( &logger, "Playing from IN1 " );
        Delay_ms( 1000 );
    }

    if (mess_cnt < 5)
    {
        log_printf( &logger, ". " );
        Delay_ms( 4000 );
        mess_cnt++;
    }
}

```
 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.AudioMUX

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
