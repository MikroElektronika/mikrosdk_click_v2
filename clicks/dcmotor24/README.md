\mainpage Main Page

---
# DC Motor 24 click

> DC Motor 24 Click is a compact add-on board with a brushed DC motor driver. This board features the L9958, an SPI-controlled H-bridge from STMicroelectronics. The L9958 is rated for an operating voltage range from 4V to 28V, with direct PWM motor control and current regulation threshold set by the SPI interface from 2.5A to 8.6A. It also has complete diagnostic and protection capabilities supporting the robust and reliable operation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dcmotor24_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/dc-motor-24-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2023.
- **Type**          : SPI/PWM type


# Software Support

We provide a library for the DC Motor 24 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DC Motor 24 Click driver.

#### Standard key functions :

- `dcmotor24_cfg_setup` Config Object Initialization function.
```c
void dcmotor24_cfg_setup ( dcmotor24_cfg_t *cfg );
```

- `dcmotor24_init` Initialization function.
```c
err_t dcmotor24_init ( dcmotor24_t *ctx, dcmotor24_cfg_t *cfg );
```

- `dcmotor24_default_cfg` Click Default Configuration function.
```c
err_t dcmotor24_default_cfg ( dcmotor24_t *ctx );
```

#### Example key functions :

- `dcmotor24_read_diag` This function reads a diagnostics word by using SPI serial interface.
```c
err_t dcmotor24_read_diag ( dcmotor24_t *ctx, uint16_t *diag );
```

- `dcmotor24_switch_direction` This function switches the direction by toggling the DIR pin state.
```c
void dcmotor24_switch_direction ( dcmotor24_t *ctx );
```

- `dcmotor24_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t dcmotor24_set_duty_cycle ( dcmotor24_t *ctx, float duty_cycle );
```

## Example Description

> This example demonstrates the use of the DC Motor 24 Click board by driving the motor in both directions at different speeds.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor24_cfg_t dcmotor24_cfg;  /**< Click config object. */

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
    dcmotor24_cfg_setup( &dcmotor24_cfg );
    DCMOTOR24_MAP_MIKROBUS( dcmotor24_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == dcmotor24_init( &dcmotor24, &dcmotor24_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DCMOTOR24_ERROR == dcmotor24_default_cfg ( &dcmotor24 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Controls the motor speed by changing the PWM duty cycle every 500ms.
The duty cycle ranges from 0% to 100%. At the minimal speed, the motor switches direction.
It also reads and parses the diagnostics word register. Each step will be logged on
the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    static int8_t duty_pct = 10;
    static int8_t duty_step = 10;
    uint16_t diag;
    if ( DCMOTOR24_OK == dcmotor24_set_duty_cycle ( &dcmotor24, ( float ) duty_pct / 100 ) )
    {
        log_printf( &logger, "\r\n Duty: %u%%\r\n", ( uint16_t ) duty_pct );
    }
    if ( DCMOTOR24_OK == dcmotor24_read_diag ( &dcmotor24, &diag ) )
    {
        dcmotor24_display_diag ( diag );
    }
    Delay_ms( 500 );
    if ( ( 100 == duty_pct ) || ( 0 == duty_pct ) ) 
    {
        duty_step = -duty_step;
        if ( 0 == duty_pct )
        {
            log_printf( &logger, "\r\n Switch direction\r\n" );
            dcmotor24_switch_direction ( &dcmotor24 );
            Delay_ms ( 500 );
        }
    }
    duty_pct += duty_step;
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor24

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
