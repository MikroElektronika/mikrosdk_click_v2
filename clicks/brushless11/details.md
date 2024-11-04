
---
# Brushless 11 Click

> Brushless 11 Click is a compact add-on board that controls brushless DC motors with any MCU. This board features the A4931, a 3-phase brushless DC motor pre-driver from Allegro Microsystems. It drives six onboard N-channel power MOSFETs and supplies the motor with 8V up to 30V voltages. This pre-driver offers enable, direction, and brake inputs that can control motor functions and logic outputs for measuring motor rotation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/brushless11_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/brushless-11-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2023.
- **Type**          : PWM type


# Software Support

We provide a library for the Brushless 11 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Brushless 11 Click driver.

#### Standard key functions :

- `brushless11_cfg_setup` Config Object Initialization function.
```c
void brushless11_cfg_setup ( brushless11_cfg_t *cfg );
```

- `brushless11_init` Initialization function.
```c
err_t brushless11_init ( brushless11_t *ctx, brushless11_cfg_t *cfg );
```

- `brushless11_default_cfg` Click Default Configuration function.
```c
err_t brushless11_default_cfg ( brushless11_t *ctx );
```

#### Example key functions :

- `brushless11_get_fg1_pin` Brushless 11 get FG1 pin state function.
```c
uint8_t brushless11_get_fg1_pin ( brushless11_t *ctx );
```

- `brushless11_set_brake` Brushless 11 set motor brake state function.
```c
void brushless11_set_brake ( brushless11_t *ctx, uint8_t brake_state );
```

- `brushless11_set_speed` Brushless 11 set motor speed.
```c
err_t brushless11_set_speed ( brushless11_t *ctx, uint8_t speed );
```

## Example Description

> This example demonstrates the use of the Brushless 11 Click board by driving the 
  motor at different speeds.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless11_cfg_t brushless11_cfg;  /**< Click config object. */

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
    brushless11_cfg_setup( &brushless11_cfg );
    BRUSHLESS11_MAP_MIKROBUS( brushless11_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == brushless11_init( &brushless11, &brushless11_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS11_ERROR == brushless11_default_cfg ( &brushless11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Controls the motor speed by changing the PWM duty cycle every second.
  The duty cycle ranges from 10% to 100%.
  Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void ) 
{
    log_printf( &logger, " Motor brake is off \r\n" );
    brushless11_set_brake( &brushless11, BRUSHLESS11_BRAKE_OFF );
    for ( uint8_t speed_cnt = 10; speed_cnt <= 100; speed_cnt += 10 )
    {
        brushless11_set_speed( &brushless11, speed_cnt );
        log_printf( &logger, " Speed is: %d%% \r\n", ( uint16_t ) speed_cnt );
        Delay_ms ( 1000 );
    }
    log_printf( &logger, " Motor brake is on \r\n" );
    brushless11_set_brake( &brushless11, BRUSHLESS11_BRAKE_ON );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless11

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
