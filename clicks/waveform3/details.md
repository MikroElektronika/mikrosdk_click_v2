---
# Waveform 3 click

> Waveform 3 Click is a compact add-on board that represents a high-performance signal generator. This board features the AD9837, a low-power programmable waveform generator capable of producing sine, triangular, and square wave outputs from Analog Devices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/waveform3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/waveform-3-click)

---


#### Click library

- **Author**        : Stefan Nikolic
- **Date**          : jan 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the Waveform3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Waveform3 Click driver.

#### Standard key functions :

- `waveform3_cfg_setup` Config Object Initialization function.
```c
void waveform3_cfg_setup ( waveform3_cfg_t *cfg );
```

- `waveform3_init` Initialization function.
```c
WAVEFORM3_RETVAL waveform3_init ( waveform3_t *ctx, waveform3_cfg_t *cfg );
```

- `waveform3_default_cfg` Click Default Configuration function.
```c
void waveform3_default_cfg ( waveform3_t *ctx );
```

#### Example key functions :

- `waveform3_set_mode` This function sets output mode, freq and phase channels of AD9837 waveform generator.
```c
void waveform3_set_mode ( waveform3_t *ctx, uint8_t mode, uint8_t freq_reg, uint8_t phase_reg );
```

- `waveform3_set_freq` This function sets desired frequency ( in Hz ) on desired freq channel.
```c
uint32_t waveform3_set_freq ( waveform3_t *ctx, uint32_t frequency, uint8_t freq_reg );
```

- `waveform3_set_phase` This function sets desired phase shift ( in degrees ) on desired phase channel.
```c
uint16_t waveform3_set_phase ( waveform3_t *ctx, float phase, uint8_t phase_reg );
```

## Example Description

> This demo app shows the basic capabilities of Waveform 3
click board. First, the sinusoidal wave is incremented
to targeted frequency for visually pleasing introduction
after which it changes between 4 modes of output.

**The demo application is composed of two sections :**

### Application Init

> Application initializes the UART LOG and SPI drivers,
resets the device and sets frequency and phase shift to
default values. In the end, the mode is set with the 
preferred freq and phase channel.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;              /**< Logger config object. */
    waveform3_cfg_t waveform3_cfg;  /**< Click config object. */

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

    waveform3_cfg_setup( &waveform3_cfg );
    WAVEFORM3_MAP_MIKROBUS( waveform3_cfg, MIKROBUS_1 );
    err_t init_flag  = waveform3_init( &waveform3, &waveform3_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    waveform3_default_cfg( &waveform3 );
    Delay_ms ( 500 );
    log_info( &logger, " Application Task " );
    waveform3_set_mode( &waveform3, WAVEFORM3_CFG_MODE_SINUSOIDAL, WAVEFORM3_CFG_FREQ_REG0, WAVEFORM3_CFG_PHASE_REG0 );
}

```

### Application Task

> Task commences with the start frequency rising up to
the targeted one. When it reaches desired frequency,
the mode changes every 5 seconds which includes: 
sinusoidal, triangular, DAC divided by 2 and DAC
outputs respectively.

```c

void application_task ( void ) {
    uint8_t cfg_mode_switch;
    
    if ( start_frequency < target_frequency ) {
        if ( start_frequency / rising_factor < 100 ) {
            start_frequency += rising_factor;
            waveform3_set_freq( &waveform3, start_frequency, WAVEFORM3_CFG_FREQ_REG0 );
            Delay_ms ( 5 );
        } else {
            rising_factor += 10;
        }
    } else {
        for ( cfg_mode_switch = 0 ; cfg_mode_switch < 4 ; cfg_mode_switch++ ) {
        waveform3_set_mode( &waveform3, cfg_mode_switch, WAVEFORM3_CFG_FREQ_REG0, WAVEFORM3_CFG_PHASE_REG0 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        }
    }
}

```

## Note

> Waveform 3 click might not provide a high enough peak to peak signal on higher frequencies.
The user can freely implement custom buffer for the output stage.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Waveform3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
