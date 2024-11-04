\mainpage Main Page

---
# Speed Sense Click

> Speed Sense Click is a compact add-on board that allows you to measure the speed and rotation of a spinning object. This board features the A17501, a dual output differential speed and direction sensor from Allegro Microsystems. It has a high-speed switching bandwidth of up to 40kHz for two different signals. The sensor has two independent output channels with options for high-resolution XOR speed, pulse, and direction protocol.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/speedsense_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/speed-sense-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2023.
- **Type**          : GPIO type


# Software Support

We provide a library for the Speed Sense Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Speed Sense Click driver.

#### Standard key functions :

- `speedsense_cfg_setup` Config Object Initialization function.
```c
void speedsense_cfg_setup ( speedsense_cfg_t *cfg );
```

- `speedsense_init` Initialization function.
```c
err_t speedsense_init ( speedsense_t *ctx, speedsense_cfg_t *cfg );
```

#### Example key functions :

- `speedsense_get_speed` This function reads the state of the CHA pin used for speed output protocols.
```c
uint8_t speedsense_get_speed ( speedsense_t *ctx );
```

- `speedsense_get_direction` This function reads the state of the CHB pin used for direction output protocols.
```c
uint8_t speedsense_get_direction ( speedsense_t *ctx );
```

## Example Description

> This library contains the API for the Speed Sense Click driver 
> for the speed and direction signal state detection for every magnetic pole pair.

**The demo application is composed of two sections :**

### Application Init

> Initialization of GPIO and log UART.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    speedsense_cfg_t speedsense_cfg;  /**< Click config object. */

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
    speedsense_cfg_setup( &speedsense_cfg );
    SPEEDSENSE_MAP_MIKROBUS( speedsense_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == speedsense_init( &speedsense, &speedsense_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, "-----------------------\r\n" );
}
```

### Application Task

> This example demonstrates the use of the Speed Sense Click board. 
> The demo application displays the direction of movement and rotation speed (rotations per minute) 
> of the ring magnet with three pairs of rotating poles positioned in the sensor operating range.

```c
void application_task ( void ) 
{
    uint8_t direction = 0, speed = 0;
    speed = speedsense_get_speed( &speedsense );
    direction = speedsense_get_direction( &speedsense );

    if ( start_measure & speed )
    {
        signal_duration = time_cnt - start_timer;
        start_timer = time_cnt;
        
        if ( SPEEDSENSE_DIR_STATE_FWD == direction )
        {
            log_printf( &logger, " Direction: Forward\r\n" );
        }
        else
        {
            log_printf( &logger, " Direction: Reverse\r\n" );
        }
        log_printf( &logger, " Speed: %.2f rpm\r\n", SPEEDSENSE_CALC_RMP / signal_duration );
        log_printf( &logger, " Duration: %lu ms\r\n", signal_duration );
        log_printf( &logger, " Time: %lu  ms\r\n", time_cnt );
        log_printf( &logger, "-----------------------\r\n" );
        start_measure = SPEEDSENSE_STOP_MEASURE;
    }
    else if ( ( !start_measure ) & ( !speed ) )
    {
        start_measure = SPEEDSENSE_START_NEW_MEASURE;
    }

    time_cnt++;
    Delay_ms ( 1 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SpeedSense

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
