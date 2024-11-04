
---
# Brushless 10 Click

> Brushless 10 Click is a compact add-on board that provides precise control over brushless DC motors. This board features the TC78B016FTG, a 3-phase sine-wave PWM driver from Toshiba Semiconductor. The TC78B016FTG features Intelligent Phase Control (InPAC) for automatic motor phase adjustment, eliminating manual calibration, supporting an external power supply from 6V to 30V, and adjusting current output up to 3A. It also includes various control and diagnostic features such as rotational speed output, brake function, speed command, and safety detections with visual indicators. The onboard DAC also offers additional tunability for motor control enhancements like lead angle control, output duty cycle, motor lockout, and PWM frequency selection.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/brushless10_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/brushless-10-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2024.
- **Type**          : PWM type


# Software Support

We provide a library for the Brushless 10 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Brushless 10 Click driver.

#### Standard key functions :

- `brushless10_cfg_setup` Config Object Initialization function.
```c
void brushless10_cfg_setup ( brushless10_cfg_t *cfg );
```

- `brushless10_init` Initialization function.
```c
err_t brushless10_init ( brushless10_t *ctx, brushless10_cfg_t *cfg );
```

- `brushless10_default_cfg` Click Default Configuration function.
```c
err_t brushless10_default_cfg ( brushless10_t *ctx );
```

#### Example key functions :

- `brushless10_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t brushless10_set_duty_cycle ( brushless10_t *ctx, float duty_cycle );
```

- `brushless10_pull_brake` This function pulls brake by setting the BRAKE pin to high logic state.
```c
void brushless10_pull_brake ( brushless10_t *ctx );
```

- `brushless10_release_brake` This function releases brake by setting the BRAKE pin to low logic state.
```c
void brushless10_release_brake ( brushless10_t *ctx );
```

## Example Description

> This example demonstrates the use of the Brushless 10 Click board by driving the motor at different speeds.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless10_cfg_t brushless10_cfg;  /**< Click config object. */

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
    brushless10_cfg_setup( &brushless10_cfg );
    BRUSHLESS10_MAP_MIKROBUS( brushless10_cfg, MIKROBUS_1 );
    if ( BRUSHLESS10_OK != brushless10_init( &brushless10, &brushless10_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS10_OK != brushless10_default_cfg ( &brushless10 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Controls the motor speed by changing the PWM duty cycle every 2 seconds.
The duty cycle ranges from 20% to 100%. Each step will be logged on the USB UART
where you can track the program flow.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 2;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    brushless10_set_duty_cycle ( &brushless10, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    duty_cnt += duty_inc;
    if ( duty_cnt > 10 ) 
    {        
        duty_cnt = 9;
        duty_inc = -1;
    }
    else if ( duty_cnt < 2 ) 
    {
        duty_cnt = 2;
        duty_inc = 1;
        log_printf( &logger, " Pull brake\r\n" );
        brushless10_pull_brake ( &brushless10 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        log_printf( &logger, " Release brake\r\n" );
        brushless10_release_brake ( &brushless10 );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless10

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
