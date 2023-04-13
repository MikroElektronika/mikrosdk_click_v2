\mainpage Main Page

---
# AudioAmp 9 click

> AudioAMP 9 Click is a compact add-on board reproducing input audio signals with desired volume and power levels at sound-producing output elements. This board features the PAM8124, a 10W efficient, Class-D audio power amplifier from Diodes Incorporated for driving stereo speakers in a single-ended configuration. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/audioamp9_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/audioamp-9-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jan 2023.
- **Type**          : GPIO type


# Software Support

We provide a library for the AudioAmp 9 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for AudioAmp 9 Click driver.

#### Standard key functions :

- `audioamp9_cfg_setup` Config Object Initialization function.
```c
void audioamp9_cfg_setup ( audioamp9_cfg_t *cfg );
```

- `audioamp9_init` Initialization function.
```c
err_t audioamp9_init ( audioamp9_t *ctx, audioamp9_cfg_t *cfg );
```

- `audioamp9_default_cfg` Click Default Configuration function.
```c
void audioamp9_default_cfg ( audioamp9_t *ctx );
```

#### Example key functions :

- `audioamp9_shutdown_on` AudioAmp 9 shutdown on function.
```c
void audioamp9_shutdown_on ( audioamp9_t *ctx );
```

- `audioamp9_mute_off` AudioAmp 9 mute off function.
```c
void audioamp9_mute_off ( audioamp9_t *ctx );
```

- `audioamp9_set_gain_level` AudioAmp 9 set gain function.
```c
err_t audioamp9_set_gain_level ( audioamp9_t *ctx, uint8_t gain_level );
```

## Example Description

> This example demonstrates the use of the AudioAmp 9 Click board by 
 changing the gain level.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs default configuration putting AudioAmp 9 Click 
 into Gain 1 mode with unmuted output.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    audioamp9_cfg_t audioamp9_cfg;  /**< Click config object. */

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
    audioamp9_cfg_setup( &audioamp9_cfg );
    AUDIOAMP9_MAP_MIKROBUS( audioamp9_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == audioamp9_init( &audioamp9, &audioamp9_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    audioamp9_default_cfg ( &audioamp9 );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Controlling the volume of the speaker by setting the gain level, and increasing it 
 every 5 seconds until the maximum level is reached, then the sound is muted for 5 seconds.

```c
void application_task ( void ) 
{
    for ( uint8_t vol_lvl = AUDIOAMP9_GAIN_LEVEL1; vol_lvl <= AUDIOAMP9_GAIN_LEVEL4; vol_lvl++ )
    {
        audioamp9_set_gain_level( &audioamp9, vol_lvl );
        log_printf( &logger, " Volume gain level %d \r\n ", vol_lvl );
        Delay_ms( 5000 );
    }
    
    log_printf( &logger, " Sound is muted \r\n " );
    audioamp9_mute_on( &audioamp9 );
    Delay_ms( 5000 );
    
    log_printf( &logger, " Sound is unmuted \r\n " );
    audioamp9_mute_off( &audioamp9 );
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.AudioAmp9

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
