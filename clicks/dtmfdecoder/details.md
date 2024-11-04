
---
# DTMF Decoder Click

DTMF Decoder Click is a compact add-on board that contains an integrated DTMF receiver with enhanced sensitivity. This board features the MT8870D, a complete DTMF receiver integrating the band-split filter and digital decoder functions from Microchip Technology.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dtmf_decoder_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/dtmf-decoder-click)

---


#### Click library

- **Author**        : Stefan Nikolic
- **Date**          : jan 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the DTMFDecoder Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DTMFDecoder Click driver.

#### Standard key functions :

- `dtmfdecoder_cfg_setup` Config Object Initialization function.
```c
void dtmfdecoder_cfg_setup ( dtmfdecoder_cfg_t *cfg );
```

- `dtmfdecoder_init` Initialization function.
```c
DTMFDECODER_RETVAL dtmfdecoder_init ( dtmfdecoder_t *ctx, dtmfdecoder_cfg_t *cfg );
```

- `dtmfdecoder_default_cfg` Click Default Configuration function.
```c
void dtmfdecoder_default_cfg ( dtmfdecoder_t *ctx );
```

#### Example key functions :

- `dtmfdecoder_tone_read` This function reads a last registered tone and returns decoded data in character format.
```c
uint8_t dtmfdecoder_tone_read ( dtmfdecoder_t *ctx );
```

- `dtmfdecoder_delayed_steering_check` This function checks the state of the StD pin.
```c
uint8_t dtmfdecoder_delayed_steering_check ( dtmfdecoder_t *ctx );
```

- `dtmfdecoder_powerdown_off` This function powers up the device and along with the oscillator.
```c
void dtmfdecoder_powerdown_off ( dtmfdecoder_t *ctx );
```

## Example Description

> This example shows the basic tone capture of DTMF frequencies, decoding and representing them on the UART LOG.

**The demo application is composed of two sections :**

### Application Init

> Initializes I2C and UART LOG drivers and powers on the device.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;                  /**< Logger config object. */
    dtmfdecoder_cfg_t dtmfdecoder_cfg;  /**< Click config object. */

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

    dtmfdecoder_cfg_setup( &dtmfdecoder_cfg );
    DTMFDECODER_MAP_MIKROBUS( dtmfdecoder_cfg, MIKROBUS_1 );
    err_t init_flag = dtmfdecoder_init( &dtmfdecoder, &dtmfdecoder_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    dtmfdecoder_default_cfg ( &dtmfdecoder );
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Checks the delayed steering for incoming tones and decoding them on the UART LOG. Holding the same key will recognize multiple tone generation, the tone register delay constant can be set to adjust the tolerance.

```c

void application_task ( void ) {
    uint8_t result;
    
    if ( dtmfdecoder_delayed_steering_check( &dtmfdecoder ) ) {
        result = dtmfdecoder_tone_read( &dtmfdecoder );
        log_printf( &logger, " Detected key tone:\t%c\r\n", result );
        Delay_ms ( tone_register_delay );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DTMFDecoder

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
