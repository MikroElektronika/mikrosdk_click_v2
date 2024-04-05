\mainpage Main Page

---
# LED Driver 17 click

> LED Driver 17 Click is a compact add-on board that offers a simple solution for controlling multiple LEDs, making it an ideal choice for various applications. This board features the LTR3755, a highly efficient DC/DC controller from Analog Devices that operates as a constant-current source. It can easily drive high current LEDs and features onboard low-side external N-channel power MOSFETs driven from an internal regulated supply. The LED Driver 17 Click is capable of stable operation over a wide supply range and offers several LED protection features, including overvoltage and overcurrent protection. Additionally, the frequency adjust pin allows users to program the switching frequency from 100kHz to 1MHz, optimizing efficiency and performance.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/leddriver17_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/led-driver-17-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2023.
- **Type**          : PWM type


# Software Support

We provide a library for the LED Driver 17 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LED Driver 17 Click driver.

#### Standard key functions :

- `leddriver17_cfg_setup` Config Object Initialization function.
```c
void leddriver17_cfg_setup ( leddriver17_cfg_t *cfg );
```

- `leddriver17_init` Initialization function.
```c
err_t leddriver17_init ( leddriver17_t *ctx, leddriver17_cfg_t *cfg );
```

- `leddriver17_default_cfg` Click Default Configuration function.
```c
err_t leddriver17_default_cfg ( leddriver17_t *ctx );
```

#### Example key functions :

- `leddriver17_get_fault_pin` This function returns the fault (FLT) pin logic state.
```c
uint8_t leddriver17_get_fault_pin ( leddriver17_t *ctx );
```

- `leddriver17_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t leddriver17_set_duty_cycle ( leddriver17_t *ctx, float duty_cycle );
```

## Example Description

> This example demonstrates the use of LED Driver 17 click board by changing the LEDs dimming level.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    leddriver17_cfg_t leddriver17_cfg;  /**< Click config object. */

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
    leddriver17_cfg_setup( &leddriver17_cfg );
    LEDDRIVER17_MAP_MIKROBUS( leddriver17_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == leddriver17_init( &leddriver17, &leddriver17_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LEDDRIVER17_ERROR == leddriver17_default_cfg ( &leddriver17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Changes the LEDs dimming level by setting the PWM duty cycle every 500ms. The duty cycle percentage will be displayed on the USB UART.
It also checks the fault indication pin and displays it accordingly.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    if ( !leddriver17_get_fault_pin ( &leddriver17 ) )
    {
        log_printf( &logger, " Fault detected!\r\n" );
    }
    leddriver17_set_duty_cycle ( &leddriver17, duty );
    log_printf( &logger, " Duty: %u%%\r\n\n", ( uint16_t ) ( duty_cnt * 10 ) );
    
    Delay_ms ( 500 );
    
    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
    }
    duty_cnt += duty_inc;
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LEDDriver17

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
