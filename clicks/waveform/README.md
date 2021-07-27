\mainpage Main Page
 
 



---
# Waveform  click

Waveform Click is a precise sine/triangle/square waveform generator, capable of reproducing frequencies up to 12MHz.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/waveform_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/waveform-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Waveform Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Waveform Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void waveform_cfg_setup ( waveform_cfg_t *cfg ); 
 
- Initialization function.
> WAVEFORM_RETVAL waveform_init ( waveform_t *ctx, waveform_cfg_t *cfg );


#### Example key functions :

- Freqency function
> void waveform_write_freqency ( waveform_t *ctx, uint32_t f );
 
- Triangle output function
> void waveform_triangle_output ( waveform_t *ctx, uint32_t f );

- Square output function
> void waveform_square_output ( waveform_t *ctx, uint32_t f );

## Examples Description

> This program outputs wave forms.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the communication interface and configures the click board.

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    waveform_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    waveform_cfg_setup( &cfg );
    WAVEFORM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    waveform_init( &waveform, &cfg );

    freq = waveform_aprox_freqcalculation( 5000 );
    waveform_square_output( &waveform, freq );
    freq = 0;
}
  
```

### Application Task

> Predefined characters are inputed from the serial port.
> Changes the signal frequency, waveform or amplitude depending on the receiver character.

```c

void application_task ( )
{
    uint8_t rx_len = log_read ( &logger, rx_data_buffer, 1 );
    
    if ( rx_len > 0 ) 
    {
       switch( rx_data_buffer[ 0 ] )
       {
           case '+': {
                            waveform_digipot_inc( &waveform );
                            log_printf( &logger, "Increasing amplitude of the current wave.\r\n" );
                            break;
                        }
           case '-': {
                            waveform_digipot_dec( &waveform );
                            log_printf( &logger, "Decreasing amplitude of the current wave.\r\n" );
                            break;
                        }
           case 'S': {
                            frequency_increment( WAVEFORM_SINE_OUT );
                            log_printf( &logger, "Increasing frequency of the sine wave.\r\n" );
                            break;
                        }
           case 's': {
                            frequency_decrement( WAVEFORM_SINE_OUT );
                            log_printf( &logger, "Decreasing frequency of the sine wave.\r\n" );
                            break;
                        }
           case 'T': {
                            frequency_increment( WAVEFORM_TRIANGLE_OUT );
                            log_printf( &logger, "Increasing frequency of the triangle wave.\r\n" );
                            break;
                        }
           case 't': {
                            frequency_decrement( WAVEFORM_TRIANGLE_OUT );
                            log_printf( &logger, "Decreasing frequency of the triangle wave.\r\n" );
                            break;
                        }
           case 'Q': {
                            frequency_increment( WAVEFORM_SQUARE_OUT );
                            log_printf( &logger, "Increasing frequency of the square wave.\r\n" );
                            break;
                        }
           case 'q': {
                            frequency_decrement( WAVEFORM_SQUARE_OUT );
                            log_printf( &logger, "Decreasing frequency of the square wave.\r\n" );
                            break;
                        }
           default :{
                            break;
                        }
       }
       rx_data_buffer[ 0 ] = 0;
       rx_len = 0;
    }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Waveform

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
