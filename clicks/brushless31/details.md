
---
# Brushless 31 click

> Brushless 31 Click is a compact add-on board for precise and efficient brushless motor control. This board features the TB6605FTG, a three-phase full sine-wave brushless motor controller from Toshiba Semiconductor. The board features six onboard external N-channel MOSFETs for smooth motor operation, sine-wave PWM driving with 2-phase modulation for high efficiency and low noise, and includes essential functions like dead time, brake, and manual/auto lead-angle control. It supports clockwise and counterclockwise rotation and offers motor lock protection for added safety. Brushless 31 Click is ideal for home appliances, fans, and office equipment applications, where reliable and precise motor control is critical.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/brushless31_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/brushless-31-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2024.
- **Type**          : PWM type


# Software Support

We provide a library for the Brushless 31 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Brushless 31 Click driver.

#### Standard key functions :

- `brushless31_cfg_setup` Config Object Initialization function.
```c
void brushless31_cfg_setup ( brushless31_cfg_t *cfg );
```

- `brushless31_init` Initialization function.
```c
err_t brushless31_init ( brushless31_t *ctx, brushless31_cfg_t *cfg );
```

- `brushless31_default_cfg` Click Default Configuration function.
```c
err_t brushless31_default_cfg ( brushless31_t *ctx );
```

#### Example key functions :

- `brushless31_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t brushless31_set_duty_cycle ( brushless31_t *ctx, float duty_cycle );
```

- `brushless31_pull_brake` This function pulls brake by setting the BRAKE pin to low logic state.
```c
void brushless31_pull_brake ( brushless31_t *ctx );
```

- `brushless31_switch_direction` This function switches the direction of motor rotation by toggling the DIR pin logic state.
```c
void brushless31_switch_direction ( brushless31_t *ctx );
```

## Example Description

> This example demonstrates the use of the Brushless 31 click board by driving the motor in both directions at different speeds.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless31_cfg_t brushless31_cfg;  /**< Click config object. */

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
    brushless31_cfg_setup( &brushless31_cfg );
    BRUSHLESS31_MAP_MIKROBUS( brushless31_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == brushless31_init( &brushless31, &brushless31_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS31_ERROR == brushless31_default_cfg ( &brushless31 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Controls the motor speed by changing the PWM duty cycle every 500 milliseconds.
The duty cycle ranges from 80% to 0%. At the minimal speed, the motor switches direction.
Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 8;
    static int8_t duty_inc = -1;
    float duty = duty_cnt / 10.0;
    
    brushless31_set_duty_cycle ( &brushless31, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms ( 500 );

    duty_cnt += duty_inc;
    if ( duty_cnt > 8 ) 
    {        
        duty_cnt = 8;
        duty_inc = -1;
        log_printf( &logger, " Pull brake\r\n" );
        brushless31_pull_brake ( &brushless31 );
        Delay_ms ( 1000 );
        log_printf( &logger, " Switch direction\r\n" );
        brushless31_switch_direction ( &brushless31 );
        Delay_ms ( 1000 );
        log_printf( &logger, " Release brake\r\n" );
        brushless31_release_brake ( &brushless31 );
        Delay_ms ( 1000 );
    }
    else if ( duty_cnt < 0 ) 
    {
        duty_cnt = 1;
        duty_inc = 1;
    }
}
```

## Note

> This click board is designed for 5V systems but can also be controlled with 3V3 GPIO lines.
Ensure your MCU is 5V tolerant on mikroBUS GPIO lines before turning on the power supply.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless31

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
