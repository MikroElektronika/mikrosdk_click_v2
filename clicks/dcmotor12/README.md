\mainpage Main Page

---
# DC Motor 12 click

> DC Motor 12 Click is a compact add-on board with a brushed DC motor driver. This board features the TB9054FTG, 
> a PWM-type, dual-channel, H-bridge, brushed DC motor driver from Toshiba Semiconductor. 
> The TB9054FTG is rated for an operating voltage range from 4.5V to 28V, 
> with the motor controlled directly through a PWM signal or SPI serial interface. 
> In addition, this driver allows a dual configuration with two motors with 5A current ratings per channel 
> or one 10A channel drive in a Parallel mode of operation. It also has complete diagnostic 
> and protection capabilities supporting robust and reliable operation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dcmotor12_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/dc-motor-12-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2022.
- **Type**          : SPI type


# Software Support

We provide a library for the DC Motor 12 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DC Motor 12 Click driver.

#### Standard key functions :

- `dcmotor12_cfg_setup` Config Object Initialization function.
```c
void dcmotor12_cfg_setup ( dcmotor12_cfg_t *cfg );
```

- `dcmotor12_init` Initialization function.
```c
err_t dcmotor12_init ( dcmotor12_t *ctx, dcmotor12_cfg_t *cfg );
```

- `dcmotor12_default_cfg` Click Default Configuration function.
```c
err_t dcmotor12_default_cfg ( dcmotor12_t *ctx );
```

#### Example key functions :

- `dcmotor12_get_motor_current` DC Motor 12 get motor current function.
```c
err_t dcmotor12_get_motor_current ( dcmotor12_t *ctx, float *current );
```

- `dcmotor12_set_ch1_operation_mode` DC Motor 12 set ch1 operation mode function.
```c
err_t dcmotor12_set_ch1_operation_mode ( dcmotor12_t *ctx, uint8_t mode );
```

- `dcmotor12_set_cm_sel_pin` DC Motor 12 set cm sel pin function.
```c
err_t dcmotor12_set_cm_sel_pin ( dcmotor12_t *ctx, uint8_t state );
```

## Example Description

> This example demonstrates the use of DC Motor 12 click board by controlling the speed
> of DC motor over PWM duty cycle as well as displaying the motor current consumption.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor12_cfg_t dcmotor12_cfg;  /**< Click config object. */

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
    dcmotor12_cfg_setup( &dcmotor12_cfg );
    DCMOTOR12_MAP_MIKROBUS( dcmotor12_cfg, MIKROBUS_1 );
    if ( DCMOTOR12_OK != dcmotor12_init( &dcmotor12, &dcmotor12_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DCMOTOR12_OK != dcmotor12_default_cfg ( &dcmotor12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Changes the operation mode and motor speed by setting the PWM duty cycle and then calculates
> the motor current consumption for that speed. All data is being logged on the USB UART
> where you can track changes.

```c
void application_task ( void )
{
    if ( DCMOTOR12_OK == dcmotor12_set_ch1_operation_mode ( &dcmotor12, DCMOTOR12_MODE_OUTPUT_OFF ) )
    {
        log_printf ( &logger, " MODE: OFF\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    if ( DCMOTOR12_OK == dcmotor12_set_ch1_operation_mode ( &dcmotor12, DCMOTOR12_MODE_FORWARD ) )
    {
        dcmotor12_set_cm_sel_pin ( &dcmotor12, DCMOTOR12_PIN_LOW_LEVEL );
        for ( uint16_t duty = 0; duty <= DCMOTOR12_CONFIG56_DUTY_PERIOD_MAX; duty += 100 )
        {
            float current;
            log_printf ( &logger, " MODE: FORWARD\r\n" );
            if ( DCMOTOR12_OK == dcmotor12_set_ch1_duty_period ( &dcmotor12, duty ) )
            {
                log_printf ( &logger, " Duty: %u\r\n", duty );
            }
            if ( DCMOTOR12_OK == dcmotor12_get_motor_current ( &dcmotor12, &current ) )
            {
                log_printf ( &logger, " Current: %.3f A\r\n\n", current );
            }
            Delay_ms ( 500 );
        }
    }
    if ( DCMOTOR12_OK == dcmotor12_set_ch1_operation_mode ( &dcmotor12, DCMOTOR12_MODE_BRAKE ) )
    {
        log_printf ( &logger, " MODE: BRAKE\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    if ( DCMOTOR12_OK == dcmotor12_set_ch1_operation_mode ( &dcmotor12, DCMOTOR12_MODE_REVERSE ) )
    {
        dcmotor12_set_cm_sel_pin ( &dcmotor12, DCMOTOR12_PIN_HIGH_LEVEL );
        for ( uint16_t duty = 0; duty <= DCMOTOR12_CONFIG56_DUTY_PERIOD_MAX; duty += 100 )
        {
            float current;
            log_printf ( &logger, " MODE: REVERSE\r\n" );
            if ( DCMOTOR12_OK == dcmotor12_set_ch1_duty_period ( &dcmotor12, duty ) )
            {
                log_printf ( &logger, " Duty: %u\r\n", duty );
            }
            if ( DCMOTOR12_OK == dcmotor12_get_motor_current ( &dcmotor12, &current ) )
            {
                log_printf ( &logger, " Current: %.3f A\r\n\n", current );
            }
            Delay_ms ( 500 );
        }
    }
}
```

## Note

> The click board swiches should be set as follows: SW 1-2-3-4 : H-H-L-L
> This sets the click board as a SPI controlled single-channel device so 
> the motor should be connected to OUT1/2 and OUT3/4.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor12

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
