\mainpage Main Page
 
 

---
# EVC Click

EVC Click is a six-channel digital volume controller, equipped with an integrated electronic volume control circuit, which can be controlled over the I2C interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/evc_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/evc-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the EVC Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for EVC Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void evc_cfg_setup ( evc_cfg_t *cfg ); 
 
- Initialization function.
> EVC_RETVAL evc_init ( evc_t *ctx, evc_cfg_t *cfg );

- Click Default Configuration function.
> void evc_default_cfg ( evc_t *ctx );


#### Example key functions :

- This function sets the volume for the selected channel, uses two variables.
> void evc_set_volume_part ( evc_t *ctx, uint8_t channel, uint8_t volume1, uint8_t volume2 );
 
- This function sets the volume for the selected channel, uses one volume variables.
> void evc_set_volume_full ( evc_t *ctx, uint8_t channel, int8_t volume );

- This function mute and unmute the sound.
> void evc_mute ( evc_t *ctx, uint8_t mute );


## Examples Description
 
> This application allows manipulation of 6 channel volume control .

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init, default configuration and sets first volume.

```c

void application_init ( void )
{
log_cfg_t log_cfg;
    evc_cfg_t cfg;

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

    evc_cfg_setup( &cfg );
    EVC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    evc_init( &evc, &cfg );

    evc_default_cfg( &evc );
    log_printf( &logger, " \\-/-\\-/ START EQUALIZER \\-/-\\-/ ");
}
  
```

### Application Task

> Emulates user input and exectuyrd functions based on set of valid commands.

```c

void application_task ( void )
{
 //  Task implementation.

    test_change( &evc );

    play( &evc );
}

```

## Note
 
> Additional Functions : 
> void test_change ( )               - Emulates user input to change parameters.
> void mute( )                       - Mute nad 
> void play ( )                      - Start new settings of the cahnnel
> uint8_t get_current_channel ( )    - Return current channel.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.EVC

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
