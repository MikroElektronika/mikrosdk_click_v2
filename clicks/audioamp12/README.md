\mainpage Main Page

---
# AudioAMP 12 click

> AudioAMP 12 Click is a compact add-on board that can reproduce input signals with desired volume and 
> power levels at sound-producing output elements. This board features the TS2007FC, 
> a filter-free class-D audio amplifier from STMicroelectronics. 
> This amplifier can drive up to 1.4W into an 8Ω load at 5V, achieving better efficiency 
> than a typical class AB audio power amplifier. In addition, it can drive up to 2.3W 
> but into a 4Ω load at 3V and with a 1% THD+N at maximum. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/audioamp12_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/audioamp-12-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jun 2023.
- **Type**          : GPIO type


# Software Support

We provide a library for the AudioAMP 12 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for AudioAMP 12 Click driver.

#### Standard key functions :

- `audioamp12_cfg_setup` Config Object Initialization function.
```c
void audioamp12_cfg_setup ( audioamp12_cfg_t *cfg );
```

- `audioamp12_init` Initialization function.
```c
err_t audioamp12_init ( audioamp12_t *ctx, audioamp12_cfg_t *cfg );
```

- `audioamp12_default_cfg` Click Default Configuration function.
```c
void audioamp12_default_cfg ( audioamp12_t *ctx );
```

#### Example key functions :

- `audioamp12_change_gain`  AudioAMP 12 changes the gain function.
```c
void audioamp12_change_gain ( audioamp12_t *ctx );
```

- `audioamp12_gain_select` AudioAMP 12 select gain level function.
```c
void audioamp12_gain_select ( audioamp12_t *ctx, audioamp12_gain_select_t sel_gain );
```

- `audioamp12_set_mode_operation` AudioAMP 12 set operation mode function.
```c
void audioamp12_set_mode_operation ( audioamp12_t *ctx );
```

## Example Description

> This example demonstrates the use of AudioAMP 12 Click board™. 
> The library contains an API for switching between two gain settings 
> and device control selection between operation and standby mode.

**The demo application is composed of two sections :**

### Application Init

> Initialization of GPIO module and log UART. After driver initialization, 
> the app sets default settings performs a power-up sequence, and sets the sound volume to 6 dB.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    audioamp12_cfg_t audioamp12_cfg;    /**< Click config object. */

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
    audioamp12_cfg_setup( &audioamp12_cfg );
    AUDIOAMP12_MAP_MIKROBUS( audioamp12_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == audioamp12_init( &audioamp12, &audioamp12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    audioamp12_default_cfg ( &audioamp12 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> The app performs circles the volume switch between two gain settings, 
> 6 dB or 12 dB, every 5 seconds. 
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    audioamp12_gain_select( &audioamp12, AUDIOAMP12_GAIN_6_DB );
    log_printf( &logger, " Gain set to 6 dB.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    audioamp12_gain_select( &audioamp12, AUDIOAMP12_GAIN_12_DB );
    log_printf( &logger, " Gain set to 12 dB.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.AudioAMP12

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
