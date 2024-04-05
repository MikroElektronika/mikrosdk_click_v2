
---
# Audio DAC click

> Audio DAC Click is a compact add-on board perfect for upgrading your audio equipment. This board features the PCM5142, a 32-bit 384kHz audio stereo DAC with the DIR9001 digital audio receiver from Texas Instruments. The DIR9001 can receive 24-bit/96kHz signals at the highest via S/PDIF optical cable and complies with various digital audio standards, like IEC60958-3, JEITA CPR-1205, AES3, and EBUtech3250. The DIR9001's output is then processed via a stereo audio DAC, the PCM5142, with the latest generation of TI's advanced segment-DAC architecture to achieve excellent dynamic performance, detailed heights, and an exceptionally good sound stage.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/audiodac_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/audio-dac-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Audio DAC Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Audio DAC Click driver.

#### Standard key functions :

- `audiodac_cfg_setup` Config Object Initialization function.
```c
void audiodac_cfg_setup ( audiodac_cfg_t *cfg );
```

- `audiodac_init` Initialization function.
```c
err_t audiodac_init ( audiodac_t *ctx, audiodac_cfg_t *cfg );
```

- `audiodac_default_cfg` Click Default Configuration function.
```c
err_t audiodac_default_cfg ( audiodac_t *ctx );
```

#### Example key functions :

- `audiodac_get_gpio4_pin` This function returns the GPIO4 pin logic state. The GPIO4 pin is mapped to auto mute flag output for both L and R channels by default.
```c
uint8_t audiodac_get_gpio4_pin ( audiodac_t *ctx );
```

- `audiodac_volume_control` This function sets the volume level for the selected output channel.
```c
err_t audiodac_volume_control ( audiodac_t *ctx, uint8_t channel, uint8_t volume );
```

## Example Description

> This example demonstrates the use of Audio DAC click board by controling the volume level of both output channels.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    audiodac_cfg_t audiodac_cfg;  /**< Click config object. */

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
    audiodac_cfg_setup( &audiodac_cfg );
    AUDIODAC_MAP_MIKROBUS( audiodac_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == audiodac_init( &audiodac, &audiodac_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AUDIODAC_ERROR == audiodac_default_cfg ( &audiodac ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Checks if the auto mute flag is set and then changes the volume level of both output channels
every 100ms. All data is being displayed on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    static uint8_t volume = AUDIODAC_VOLUME_MUTE;
    if ( audiodac_get_gpio4_pin ( &audiodac ) )
    {
        log_printf ( &logger, " Auto mute flag (both L and R channels are auto muted)\r\n" );
        // Wait until the channels are auto unmuted, i.e. until a valid digital signal is received
        while ( audiodac_get_gpio4_pin ( &audiodac ) );
    }
    if ( AUDIODAC_OK == audiodac_volume_control ( &audiodac, AUDIODAC_CHANNEL_BOTH, volume ) )
    {
        log_printf ( &logger, "\r\n Volume: " );
        if ( AUDIODAC_VOLUME_MUTE == volume )
        {
            log_printf ( &logger, "MUTE\r\n" );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
        else if ( AUDIODAC_VOLUME_MAX == volume )
        {
            log_printf ( &logger, "MAX\r\n" );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
        else
        {
            log_printf ( &logger, "%u\r\n", ( uint16_t ) volume );
            Delay_ms ( 100 );
        }
        volume++; 
        if ( volume > AUDIODAC_VOLUME_MAX )
        {
            volume = AUDIODAC_VOLUME_MUTE;
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.AudioDAC

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
