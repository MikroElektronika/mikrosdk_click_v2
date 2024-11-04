\mainpage Main Page
 

---
# Waveform  Click

> Waveform Click is a precise sine/triangle/square waveform generator, capable of reproducing frequencies up to 12MHz.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/waveform_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/waveform-click)

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

- `waveform_cfg_setup` Config Object Initialization function.
```c
void waveform_cfg_setup ( waveform_cfg_t *cfg ); 
```

- `waveform_init` Initialization function.
```c
err_t waveform_init ( waveform_t *ctx, waveform_cfg_t *cfg );
```

#### Example key functions :

- `waveform_sine_output` Sinusoide output function
```c
void waveform_sine_output ( waveform_t *ctx, uint32_t freq );
```

- `waveform_triangle_output` Triangle output function
```c
void waveform_triangle_output ( waveform_t *ctx, uint32_t freq );
```

- `waveform_square_output` Square output function
```c
void waveform_square_output ( waveform_t *ctx, uint32_t freq );
```

## Examples Description

> This example demonstrates the use of Waveform Click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the communication interface and configures the Click board.

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    waveform_cfg_t waveform_cfg;

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    waveform_cfg_setup( &waveform_cfg );
    WAVEFORM_MAP_MIKROBUS( waveform_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == waveform_init( &waveform, &waveform_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    waveform_sine_output( &waveform, frequency );
    log_printf( &logger, "Sine wave output set with approx. frequency: %lu Hz\r\n", frequency );
    waveform_display_commands ( );
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Predefined commands are inputed from the serial port.
> Changes the signal frequency, waveform or amplitude depending on the receiver command.

```c

void application_task ( )
{
    uint8_t command = 0;
    if ( 1 == log_read ( &logger, &command, 1 ) ) 
    {
        waveform_parse_command ( command );
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
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
