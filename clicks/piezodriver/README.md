\mainpage Main Page

---
# Piezo Driver click

> Piezo Driver Click is a compact add-on board that allows you easy system configuration for driving a two-terminal or three-terminal piezo sounder with few external components. This board features the PAM8906, a piezo sounder driver with self-excitation mode from Diodes Incorporated. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/piezodriver_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/piezo-driver-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2023.
- **Type**          : PWM type


# Software Support

We provide a library for the Piezo Driver Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Piezo Driver Click driver.

#### Standard key functions :

- `piezodriver_cfg_setup` Config Object Initialization function.
```c
void piezodriver_cfg_setup ( piezodriver_cfg_t *cfg );
```

- `piezodriver_init` Initialization function.
```c
err_t piezodriver_init ( piezodriver_t *ctx, piezodriver_cfg_t *cfg );
```

- `piezodriver_default_cfg` Click Default Configuration function.
```c
err_t piezodriver_default_cfg ( piezodriver_t *ctx );
```

#### Example key functions :

- `piezodriver_pwm_stop` Piezo Driver stop PWM module.
```c
err_t piezodriver_pwm_stop ( piezodriver_t *ctx );
```

- `piezodriver_pwm_start` Piezo Driver start PWM module.
```c
err_t piezodriver_pwm_start ( piezodriver_t *ctx );
```

- `piezodriver_play_sound` Piezo Driver play sound function.
```c
void piezodriver_play_sound ( piezodriver_t *ctx, uint16_t freq, uint8_t level, uint16_t duration );
```

## Example Description

> This example demonstrates the use of Piezo Driver Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    piezodriver_cfg_t piezodriver_cfg;  /**< Click config object. */

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
    piezodriver_cfg_setup( &piezodriver_cfg );
    PIEZODRIVER_MAP_MIKROBUS( piezodriver_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == piezodriver_init( &piezodriver, &piezodriver_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PIEZODRIVER_ERROR == piezodriver_default_cfg ( &piezodriver ) )
    {
        log_error( &logger, " Default configuration." );
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
    log_printf( &logger, "Playing the Imperial March melody ...\r\n" );
    imperial_march( ); 
    Delay_ms( 10000 );
}
```

## Note

> The minimal PWM Clock frequency required for this example is the frequency of tone C6 - 1047 Hz. 
 In order to run this example and play all tones correctly, the user will need to decrease 
 the MCU's main clock frequency in MCU Settings for certain architectures
 in order to get the required PWM clock frequency.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.PiezoDriver

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
