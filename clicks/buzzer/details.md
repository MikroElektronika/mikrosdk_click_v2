
---
# Buzzer click

> Buzzer Click is a compact add-on board for generating sound signals in various electronic applications. This board features the CPT-7502-65-SMT-TR, a piezoelectric buzzer transducer from CUI Devices, known for its efficient sound output and compact surface-mount design. The buzzer offers a sound pressure level of 65dB and consumes only 1mA of current, making it ideal for battery-powered devices. The board also features the MIKROE 'Click Snap' function, allowing for flexible installation and autonomous operation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/buzzer_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/buzzer-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2024.
- **Type**          : PWM type


# Software Support

We provide a library for the Buzzer Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Buzzer Click driver.

#### Standard key functions :

- `buzzer_cfg_setup` Config Object Initialization function.
```c
void buzzer_cfg_setup ( buzzer_cfg_t *cfg );
```

- `buzzer_init` Initialization function.
```c
err_t buzzer_init ( buzzer_t *ctx, buzzer_cfg_t *cfg );
```

#### Example key functions :

- `buzzer_play_sound` This function plays sound on the buzzer.
```c
err_t buzzer_play_sound ( buzzer_t *ctx, uint16_t freq, uint8_t level, uint16_t duration );
```

## Example Description

> This example demonstrates the use of Buzzer click board by playing the Imperial March melody on the buzzer.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buzzer_cfg_t buzzer_cfg;  /**< Click config object. */

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
    buzzer_cfg_setup( &buzzer_cfg );
    BUZZER_MAP_MIKROBUS( buzzer_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == buzzer_init( &buzzer, &buzzer_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Plays the Imperial March melody. Also logs an appropriate message on the USB UART.

```c
void application_task ( void )
{
    log_printf( &logger, " Playing the Imperial March melody...\r\n" );
    buzzer_imperial_march( BUZZER_VOLUME_MAX ); 
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

## Note

> The minimal PWM Clock frequency required for this example is the frequency of tone C6 - 1047 Hz. 
So, in order to run this example and play all tones correctly, the user will need to decrease 
the MCU's main clock frequency in MCU Settings for the certain architectures
in order to get the required PWM clock frequency.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Buzzer

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
