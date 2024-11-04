\mainpage Main Page

---
# Smart Mic Click

> Smart Mic Click is a compact add-on board that provides wake-on-voice capabilities with secured privacy without compromising performance. This board features the IA611, an “Always-On” voice-wake acoustic processor from Knowles Electronics. The IA611 offers flexibility by supporting the most relevant audio and data interfaces and enables ultra-low-power voice and event detection, including voice UI supporting keywords, voice commands, and acoustic event detection. Its integrated programmable DSP is made available to 3rd party algorithms with 168kB of RAM, enabling unlimited creativity.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/smartmic_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/smart-mic-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Smart Mic Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Smart Mic Click driver.

#### Standard key functions :

- `smartmic_cfg_setup` Config Object Initialization function.
```c
void smartmic_cfg_setup ( smartmic_cfg_t *cfg );
```

- `smartmic_init` Initialization function.
```c
err_t smartmic_init ( smartmic_t *ctx, smartmic_cfg_t *cfg );
```

- `smartmic_default_cfg` Click Default Configuration function.
```c
err_t smartmic_default_cfg ( smartmic_t *ctx );
```

#### Example key functions :

- `smartmic_wait_keyword` This function waits for a keyword event and then reads it and returns the keyword ID number.
```c
err_t smartmic_wait_keyword ( smartmic_t *ctx );
```

- `smartmic_download_keyword` This function downloads keyword models to the module.
```c
err_t smartmic_download_keyword ( smartmic_t *ctx, uint16_t *data_in, uint16_t len );
```

- `smartmic_voice_make` This function performs voice make feature. It stops the route, then sets digital gain to 20db, sample rate to 16K, frame size to 16 ms, and finally it selects route 6 and configures algorithm parameters.
```c
err_t smartmic_voice_make ( smartmic_t *ctx );
```

## Example Description

> This example demonstrates the use of Smart Mic Click board by programming it with 4 different keywords, and then waiting for a keyword event,
parsing it and displaying on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration which programs the device with system config, firmware, and 4 keywords
("Hello VoiceQ","Switch The Light","Next Song","Baidu Yixia") binaries.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartmic_cfg_t smartmic_cfg;  /**< Click config object. */

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
    smartmic_cfg_setup( &smartmic_cfg );
    SMARTMIC_MAP_MIKROBUS( smartmic_cfg, MIKROBUS_1 );
    if ( SMARTMIC_OK != smartmic_init( &smartmic, &smartmic_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Configuring device... \r\n" );
    
    if ( SMARTMIC_OK != smartmic_default_cfg ( &smartmic ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for a keyword event, parses it and displays on the USB UART an appropriate message for the detected keyword.

```c
void application_task ( void )
{
    switch ( smartmic_wait_keyword ( &smartmic ) )
    {
        case SMARTMIC_OEM1_KWD_DETECTED:
        {
            log_printf ( &logger, " Hello VoiceQ keyword detected!\r\n" );
            break;
        }
        case SMARTMIC_OEM2_KWD_DETECTED:
        {
            log_printf ( &logger, " Switch The Light keyword detected!\r\n" );
            break;
        }
        case SMARTMIC_OEM3_KWD_DETECTED:
        {
            log_printf ( &logger, " Next Song keyword detected!\r\n" );
            break;
        }
        case SMARTMIC_OEM4_KWD_DETECTED:
        {
            log_printf ( &logger, " Baidu YiXia keyword detected!\r\n" );
            break;
        } 
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SmartMic

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
