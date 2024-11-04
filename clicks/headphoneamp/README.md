\mainpage Main Page

---
# Headphone AMP Click

Headphone Amp Click is a compact add-on board that contains a stereo headphone amplifier. This board features the LM4811, Boomer® audio power amplifier capable of delivering 105mW per channel with digital volume control from Texas Instruments. The Boomer® amplifiers are specifically designed to provide high-quality output power with a minimal amount of external components. Since the LM4811 does not require bootstrap capacitors or snubber networks, it is optimally suited for low-power portable systems. It features a digital volume control that sets the amplifier's gain from +12dB to −33dB in 16 discrete steps, in addition to a micro-power consumption Shutdown mode.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/headphoneamp_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/headphone-amp-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2021.
- **Type**          : GPIO type


# Software Support

We provide a library for the HeadphoneAMP Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for HeadphoneAMP Click driver.

#### Standard key functions :

- `headphoneamp_cfg_setup` Config Object Initialization function.
```c
void headphoneamp_cfg_setup ( headphoneamp_cfg_t *cfg );
```

- `headphoneamp_init` Initialization function.
```c
HEADPHONEAMP_RETVAL headphoneamp_init ( headphoneamp_t *ctx, headphoneamp_cfg_t *cfg );
```

- `headphoneamp_default_cfg` Click Default Configuration function.
```c
void headphoneamp_default_cfg ( headphoneamp_t *ctx );
```

#### Example key functions :

- `headphoneamp_set_sound_volume` Headphone AMP set sound volume function.
```c
HEADPHONEAMP_RETVAL headphoneamp_set_sound_volume ( headphoneamp_t *ctx, uint8_t sound_volume );
```

- `headphoneamp_volume_up` Headphone AMP set sound volume up function.
```c
HEADPHONEAMP_RETVAL headphoneamp_volume_up ( headphoneamp_t *ctx );
```

- `headphoneamp_volume_down` Headphone AMP set sound volume down function.
```c
HEADPHONEAMP_RETVAL headphoneamp_volume_down ( headphoneamp_t *ctx );
```

## Example Description

> This library contains API for the Headphone AMP Click driver.
> This demo application shows use of a Headphone AMP Click board™.

**The demo application is composed of two sections :**

### Application Init

> Initialization of GPIO module and log UART.
> After driver initialization the app set default settings, 
> performs power-up sequence, sets a the sound volume of -12 dB.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;                    /**< Logger config object. */
    headphoneamp_cfg_t headphoneamp_cfg;  /**< Click config object. */

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

    headphoneamp_cfg_setup( &headphoneamp_cfg );
    HEADPHONEAMP_MAP_MIKROBUS( headphoneamp_cfg, MIKROBUS_1 );
    if ( headphoneamp_init( &headphoneamp, &headphoneamp_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    headphoneamp_default_cfg ( &headphoneamp );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
    
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "    Performs Power-up\r\n" );
    headphoneamp_power_up( &headphoneamp );
    Delay_ms ( 100 );
    
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "  Set volume gain -12dB\r\n", HEADPHONEAMP_SOUND_VOLUME_NEG_12_dB );
    headphoneamp_set_sound_volume( &headphoneamp, HEADPHONEAMP_SOUND_VOLUME_NEG_12_dB ); 
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

### Application Task

> This is an example that shows the use of Headphone AMP Click board™.
> The app performs circles the volume from -12 dB to 3 dB back and forth,
> increase/decrement by 3dB.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) 
{
    for ( uint8_t n_cnt = 0; n_cnt < 5; n_cnt++ ) {
        log_printf( &logger, "    Turning volume up\r\n" );
        headphoneamp_volume_up ( &headphoneamp ); 
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );    
    }
    
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    for ( uint8_t n_cnt = 0; n_cnt < 5; n_cnt++ ) {
        log_printf( &logger, "   Turning volume down\r\n" );
        headphoneamp_volume_down ( &headphoneamp ); 
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );    
    }
       
    log_printf( &logger, "-------------------------\r\n" );
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
- Click.HeadphoneAMP

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
