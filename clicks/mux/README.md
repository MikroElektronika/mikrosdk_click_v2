\mainpage Main Page
 
 

---
# MUX Click

MUX Click is a Click board™ that switches one of the four differential inputs to one differential output. It employs the MUX509, a modern CMOS analog multiplexing integrated circuit, produced by Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mux_click.png" height=300px>
</p>


[Click Product page](https://www.mikroe.com/mux-click)

---


#### Click library 

- **Author**        : Luka Filipovic
- **Date**          : Nov 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the Mux Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Mux Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mux_cfg_setup ( mux_cfg_t *cfg ); 
 
- Initialization function.
> MUX_RETVAL mux_init ( mux_t *ctx, mux_cfg_t *cfg );

- Click Default Configuration function.
> void mux_default_cfg ( mux_t *ctx );


#### Example key functions :

- Seelect active MUX channel
> void mux_active_mux_channel ( mux_t *ctx, uint8_t sel_ch );
 
- Disable MUX device function.
> void mux_device_disable ( mux_t *ctx );

- Enable MUX device function.
> void mux_device_enable ( mux_t *ctx );

## Examples Description

> Sets the current active channel. Changes the channel every 5 sec.

**The demo application is composed of two sections :**

### Application Init 

> Initializes GPIO module and sets RST, CS and PWM pins as OUTPUT.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    mux_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    mux_cfg_setup( &cfg );
    MUX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mux_init( &mux, &cfg );
    Delay_ms ( 100 );
    
    log_printf( &logger, "        MUX Click\r\n" );
    log_printf( &logger, "------------------------\r\n" );
    
    mux_device_enable( &mux );
    log_printf( &logger, "    Enable MUX device\r\n" );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 100 );
}
  
```

### Application Task

> Changes currently active channel every 5 sec.

```c

void application_task ( void )
{
    uint16_t n_cnt;
    
    for ( n_cnt = MUX_CHANNEL_1A_AND_1B; n_cnt < MUX_CHANNEL_END; n_cnt++ )
    {
        log_printf( &logger, "      CHANNEL  S%u\r\n", n_cnt );
        log_printf( &logger, "------------------------\r\n" );
        
        mux_active_mux_channel( &mux, n_cnt );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
}  

```

## Note

> 
> <NOTE>
> 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Mux

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
