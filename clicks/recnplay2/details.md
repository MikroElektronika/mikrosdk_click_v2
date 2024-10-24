
---
# Rec N Play 2 click

> Rec&Play 2 Click is a compact add-on board for voice recording and playback applications. It is based on the ISD1616B, a single-message voice record and playback IC from Nuvoton. The board features an on-chip oscillator, a microphone preamplifier with Automatic Gain Control (AGC), an omnidirectional microphone, and a speaker driver for high-quality audio recording and playback. Voice data is stored in onboard Flash memory without digital compression, ensuring clear and reliable sound. It supports both manual and digital control, as well as flexible message durations from 10 to 26 seconds.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/recplay2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/recplay-2-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jan 2024.
- **Type**          : GPIO type


# Software Support

We provide a library for the Rec N Play 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Rec N Play 2 Click driver.

#### Standard key functions :

- `recnplay2_cfg_setup` Config Object Initialization function.
```c
void recnplay2_cfg_setup ( recnplay2_cfg_t *cfg );
```

- `recnplay2_init` Initialization function.
```c
err_t recnplay2_init ( recnplay2_t *ctx, recnplay2_cfg_t *cfg );
```

- `recnplay2_default_cfg` Click Default Configuration function.
```c
void recnplay2_default_cfg ( recnplay2_t *ctx );
```

#### Example key functions :

- `recnplay2_set_pl_pin` This function sets the PL pin on the selected level of Rec N Play 2 click board.
```c
void recnplay2_set_pl_pin ( recnplay2_t *ctx, uint8_t pin_state );
```

- `recnplay2_record_sound` This function is used to record sound with Rec N Play 2 click board.
```c
err_t recnplay2_record_sound ( recnplay2_t *ctx, uint16_t rec_len );
```

- `recnplay2_play_sound` This function is used to play recorded sounds with Rec N Play 2 click board.
```c
err_t recnplay2_play_sound ( recnplay2_t *ctx, uint16_t play_len );
```

## Example Description

> This example demonstrates the use of Rec N Play 2 Click board by 
 recording and then playing recorded sound.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, performs the click default configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    recnplay2_cfg_t recnplay2_cfg;  /**< Click config object. */

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
    recnplay2_cfg_setup( &recnplay2_cfg );
    RECNPLAY2_MAP_MIKROBUS( recnplay2_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == recnplay2_init( &recnplay2, &recnplay2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    recnplay2_default_cfg ( &recnplay2 );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Recording sound for 5 seconds, then playing it back.

```c
void application_task ( void ) 
{
    log_printf( &logger, " Recording... \r\n" );
    recnplay2_record_sound( &recnplay2, RECORDING_LEN );
    Delay_ms ( 1000 );

    log_printf( &logger, " Playing... \r\n" );
    recnplay2_play_sound( &recnplay2, RECORDING_LEN );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RecNPlay2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
