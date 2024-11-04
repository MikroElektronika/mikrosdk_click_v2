\mainpage Main Page

---
# AudioAMP 11 Click

> AudioAmp 11 Click is a compact add-on board reproducing input audio signals with desired volume 
> and power levels at sound-producing output elements. 
> This board features the NAU8224, a high-performance stereo Class-D audio amplifier from Nuvoton Technology. 
> This flexible I2C configurable audio amplifier can drive a 4Ω load with up to 3.1W output power. 
> In addition to the possibility of digital control (using only one enable pin), 
> the NAU8224 also has many useful gain settings from 6dB to 24dB. Besides, 
> it is equipped with protection features, allowing a reliable operation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/audioamp11_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/audioamp-11-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the AudioAMP 11 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for AudioAMP 11 Click driver.

#### Standard key functions :

- `audioamp11_cfg_setup` Config Object Initialization function.
```c
void audioamp11_cfg_setup ( audioamp11_cfg_t *cfg );
```

- `audioamp11_init` Initialization function.
```c
err_t audioamp11_init ( audioamp11_t *ctx, audioamp11_cfg_t *cfg );
```

- `audioamp11_default_cfg` Click Default Configuration function.
```c
err_t audioamp11_default_cfg ( audioamp11_t *ctx );
```

#### Example key functions :

- `audioamp11_enable_device` AudioAMP 11 enable device function.
```c
void audioamp11_enable_device ( audioamp11_t *ctx );
```

- `audioamp11_check_gain` AudioAMP 11 check gain function.
```c
err_t audioamp11_check_gain ( audioamp11_t *ctx, uint8_t *gain );
```

- `audioamp11_set_output_volume_level` AudioAMP 11 set output volume level function.
```c
err_t audioamp11_set_output_volume_level ( audioamp11_t *ctx, uint8_t volume_data );
```

## Example Description

> This library contains API for the AudioAMP 11 Click driver.
> This demo application shows use of a AudioAMP 11 Click board™.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization the app set default settings, 
> performs power-up sequence, sets the volume level to 0.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    audioamp11_cfg_t audioamp11_cfg;  /**< Click config object. */

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
    audioamp11_cfg_setup( &audioamp11_cfg );
    AUDIOAMP11_MAP_MIKROBUS( audioamp11_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == audioamp11_init( &audioamp11, &audioamp11_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AUDIOAMP11_ERROR == audioamp11_default_cfg ( &audioamp11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "----------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the AudioAMP 11 Click board™.
> If GAIN SEL switches are set to 12dB, the app performs circles 
> switching the volume from -20.5 dB to 12 dB.
> If the GAIN SEL switches are different, the app sets the volume level to 31 (maximum).
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    uint8_t gain_level = 0;
    uint8_t volume_level = 0;
    
    audioamp11_check_gain( &audioamp11, &gain_level );
    log_printf( &logger, " Gain set to %d dB\r\n", AUDIOAMP11_CALC_GAIN_CONFIG( gain_level ) );
    
    if ( AUDIOAMP11_GAINDEC_12dB == gain_level )
    {
        float volume_table[ 32 ] = { OUTPUT_VOLUME_12dB };
        audioamp11_set_output_volume_level( &audioamp11, vol_ctrl );
        Delay_ms ( 100 );
        
        if ( vol_ctrl > AUDIOAMP11_GS_12dB_VOLCTRL_12dB )
        {
            vol_ctrl--;
        }
        else
        {
            vol_ctrl = AUDIOAMP11_GS_12dB_VOLCTRL_m20_5dB;
        }
        
        audioamp11_get_output_volume_level( &audioamp11, &volume_level );
        log_printf( &logger, " Volume set to  %.1f dB\r\n", volume_table[ volume_level ] );
    }
    else
    {
        audioamp11_set_output_volume_level( &audioamp11, AUDIOAMP11_VOLUME_LEVEL_31 );
        audioamp11_get_output_volume_level( &audioamp11, &volume_level );        
    }
    
    log_printf( &logger, " Volume Level %d: ", ( uint16_t ) ( AUDIOAMP11_VOLUME_LEVEL_0 - volume_level ) );
    for ( uint8_t n_cnt = 0; n_cnt < ( AUDIOAMP11_VOLUME_LEVEL_0 - volume_level ); n_cnt++ )
    {
        log_printf( &logger, "|" );    
    }
    log_printf( &logger, "\r\n----------------------\r\n" );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.AudioAMP11

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
