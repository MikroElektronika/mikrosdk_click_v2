\mainpage Main Page

---
# Waveform 4 click

> Waveform 4 Click is a compact add-on board that represents a high-performance signal generator. This board features the AD9106, a quad-channel, 12-bit, 180MSPS waveform generator, integrating on-chip static random access memory (SRAM) and direct digital synthesis (DDS) for complex waveform generation from Analog Devices. The DDS is up to a 180 MHz master clock sinewave generator with a 24-bit tuning word allowing 10.8 Hz/LSB frequency resolution.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/waveform4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/waveform-4-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the Waveform4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Waveform4 Click driver.

#### Standard key functions :

- `waveform4_cfg_setup` Config Object Initialization function.
```c
void waveform4_cfg_setup ( waveform4_cfg_t *cfg );
```

- `waveform4_init` Initialization function.
```c
err_t waveform4_init ( waveform4_t *ctx, waveform4_cfg_t *cfg );
```

- `waveform4_default_cfg` Click Default Configuration function.
```c
err_t waveform4_default_cfg ( waveform4_t *ctx );
```

#### Example key functions :

- `waveform4_set_frequency` This function sets the sine and cosine (DDS) waves output frequency.
```c
err_t waveform4_set_frequency ( waveform4_t *ctx, uint32_t freq );
```

- `waveform4_set_gain` This function sets the gain level of a desired channel.
```c
err_t waveform4_set_gain ( waveform4_t *ctx, uint8_t channel, float gain );
```

- `waveform4_set_wave_output` This function sets a desired output signal wave to the selected channel.
```c
err_t waveform4_set_wave_output ( waveform4_t *ctx, uint8_t channel, uint8_t wave );
```

## Example Description

> This example demonstrates the use of Waveform 4 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration which resets the registers and sets the sine wave output with default gain and 
> default frequency for all channels. After that it displays the list of supported commands on the USB UART.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    waveform4_cfg_t waveform4_cfg;  /**< Click config object. */

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
    waveform4_cfg_setup( &waveform4_cfg );
    WAVEFORM4_MAP_MIKROBUS( waveform4_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == waveform4_init( &waveform4, &waveform4_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( WAVEFORM4_ERROR == waveform4_default_cfg ( &waveform4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    waveform4_display_commands ( );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Depending on the command character received from USB UART it changes the signal frequency, gain or wave of the selected channel.

```c

void application_task ( void )
{
    uint8_t command = 0;
    if ( log_read ( &logger, &command, 1 ) > 0 ) 
    {
        waveform4_parse_command ( command );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Waveform4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
