
---
# DC Motor 26 click

> DC Motor 26 Click is a compact add-on board with a brushed DC motor driver. This board features the TB9053FTG, a PWM-type, dual-channel, H-bridge, brushed DC motor driver from Toshiba Semiconductor. The TB9053FTG is rated for an operating voltage range from 4.5V to 28V, with the motor controlled directly through a PWM signal or SPI serial interface. In addition, this driver allows a dual configuration with two motors with 5A current ratings per channel or one 10A channel drive in a Parallel mode of operation. It also has complete diagnostic and protection capabilities supporting robust and reliable operation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dcmotor26_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/dc-motor-26-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the DC Motor 26 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DC Motor 26 Click driver.

#### Standard key functions :

- `dcmotor26_cfg_setup` Config Object Initialization function.
```c
void dcmotor26_cfg_setup ( dcmotor26_cfg_t *cfg );
```

- `dcmotor26_init` Initialization function.
```c
err_t dcmotor26_init ( dcmotor26_t *ctx, dcmotor26_cfg_t *cfg );
```

- `dcmotor26_default_cfg` Click Default Configuration function.
```c
err_t dcmotor26_default_cfg ( dcmotor26_t *ctx );
```

#### Example key functions :

- `dcmotor26_get_motor_current` DC Motor 26 get motor current function.
```c
err_t dcmotor26_get_motor_current ( dcmotor26_t *ctx, float *current );
```

- `dcmotor26_set_ch1_operation_mode` DC Motor 26 set ch1 operation mode function.
```c
err_t dcmotor26_set_ch1_operation_mode ( dcmotor26_t *ctx, uint8_t mode );
```

- `dcmotor26_set_cm_sel_pin` DC Motor 26 set cm sel pin function.
```c
err_t dcmotor26_set_cm_sel_pin ( dcmotor26_t *ctx, uint8_t state );
```

## Example Description

> This example demonstrates the use of DC Motor 26 click board by controlling the speed
of DC motor over PWM duty cycle as well as displaying the motor current consumption.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor26_cfg_t dcmotor26_cfg;  /**< Click config object. */

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
    dcmotor26_cfg_setup( &dcmotor26_cfg );
    DCMOTOR26_MAP_MIKROBUS( dcmotor26_cfg, MIKROBUS_1 );
    if ( DCMOTOR26_OK != dcmotor26_init( &dcmotor26, &dcmotor26_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DCMOTOR26_OK != dcmotor26_default_cfg ( &dcmotor26 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Changes the operation mode and motor speed by setting the PWM duty cycle and then calculates
the motor current consumption for that speed. All data is being logged on the USB UART where you can track changes.

```c
void application_task ( void )
{
    if ( DCMOTOR26_OK == dcmotor26_set_ch1_operation_mode ( &dcmotor26, DCMOTOR26_MODE_OUTPUT_OFF ) )
    {
        log_printf ( &logger, " MODE: OFF\r\n" );
        Delay_ms ( 3000 );
    }
    if ( DCMOTOR26_OK == dcmotor26_set_ch1_operation_mode ( &dcmotor26, DCMOTOR26_MODE_FORWARD ) )
    {
        dcmotor26_set_cm_sel_pin ( &dcmotor26, DCMOTOR26_PIN_LOW_LEVEL );
        for ( uint16_t duty = 0; duty <= DCMOTOR26_CONFIG56_DUTY_PERIOD_MAX; duty += 100 )
        {
            float current;
            log_printf ( &logger, " MODE: FORWARD\r\n" );
            if ( DCMOTOR26_OK == dcmotor26_set_ch1_duty_period ( &dcmotor26, duty ) )
            {
                log_printf ( &logger, " Duty: %u\r\n", duty );
            }
            if ( DCMOTOR26_OK == dcmotor26_get_motor_current ( &dcmotor26, &current ) )
            {
                log_printf ( &logger, " Current: %.3f A\r\n\n", current );
            }
            Delay_ms ( 500 );
        }
    }
    if ( DCMOTOR26_OK == dcmotor26_set_ch1_operation_mode ( &dcmotor26, DCMOTOR26_MODE_BRAKE ) )
    {
        log_printf ( &logger, " MODE: BRAKE\r\n" );
        Delay_ms ( 3000 );
    }
    if ( DCMOTOR26_OK == dcmotor26_set_ch1_operation_mode ( &dcmotor26, DCMOTOR26_MODE_REVERSE ) )
    {
        dcmotor26_set_cm_sel_pin ( &dcmotor26, DCMOTOR26_PIN_HIGH_LEVEL );
        for ( uint16_t duty = 0; duty <= DCMOTOR26_CONFIG56_DUTY_PERIOD_MAX; duty += 100 )
        {
            float current;
            log_printf ( &logger, " MODE: REVERSE\r\n" );
            if ( DCMOTOR26_OK == dcmotor26_set_ch1_duty_period ( &dcmotor26, duty ) )
            {
                log_printf ( &logger, " Duty: %u\r\n", duty );
            }
            if ( DCMOTOR26_OK == dcmotor26_get_motor_current ( &dcmotor26, &current ) )
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
This sets the click board as a SPI controlled single-channel device so the motor should be connected to OUT1/2 and OUT3/4.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor26

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
