
---
# SolidSwitch 2 Click

> SolidSwitch 2 Click is a compact add-on board that contains a load switching device. This board features the L9026, an automotive eight-channel relay driver from STMicroelectronics. The L9026 incorporates two high-side drivers and six configurable high-side/low-side drivers driven by an SPI interface or by two dedicated parallel inputs. Operating from an external power supply from 3V up to 18V, it provides a maximum current of 1A on its output terminals. It also offers advanced diagnostic and protection features such as short-to-ground, open load, overcurrent, and overtemperature detections.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/solidswitch2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/solidswitch-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : SPI type


# Software Support

We provide a library for the SolidSwitch 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for SolidSwitch 2 Click driver.

#### Standard key functions :

- `solidswitch2_cfg_setup` Config Object Initialization function.
```c
void solidswitch2_cfg_setup ( solidswitch2_cfg_t *cfg );
```

- `solidswitch2_init` Initialization function.
```c
err_t solidswitch2_init ( solidswitch2_t *ctx, solidswitch2_cfg_t *cfg );
```

- `solidswitch2_default_cfg` Click Default Configuration function.
```c
err_t solidswitch2_default_cfg ( solidswitch2_t *ctx );
```

#### Example key functions :

- `solidswitch2_write_register` This function writes a desired data to the selected register by using SPI serial interface.
```c
err_t solidswitch2_write_register ( solidswitch2_t *ctx, uint8_t reg, uint8_t data_in );
```

- `solidswitch2_toggle_in0_pin` This function toggles the IN0 pin logic state.
```c
void solidswitch2_toggle_in0_pin ( solidswitch2_t *ctx );
```

- `solidswitch2_toggle_in1_pin` This function toggles the IN1 pin logic state.
```c
void solidswitch2_toggle_in1_pin ( solidswitch2_t *ctx );
```

## Example Description

> This example demonstrates the use of SolidSwitch 2 Click board by controlling the output state.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration which maps outputs as follows:
> - OUT2   - IN0,
> - OUT3   - IN1,
> - OUT4-5 - PWM GEN,
> - OUT6-7 - PWM LED.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    solidswitch2_cfg_t solidswitch2_cfg;  /**< Click config object. */

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
    solidswitch2_cfg_setup( &solidswitch2_cfg );
    SOLIDSWITCH2_MAP_MIKROBUS( solidswitch2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == solidswitch2_init( &solidswitch2, &solidswitch2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SOLIDSWITCH2_ERROR == solidswitch2_default_cfg ( &solidswitch2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Changes the PWM GEN (max to min) and PWM LED (min to max) duty cycle and toggles the IN0 and IN1
pins every 250ms. The duty cycle values and INx toggle messages will be displayed on the USB UART.

```c
void application_task ( void )
{
    for ( uint16_t duty_cycle = SOLIDSWITCH2_MIN_DUTY_CYCLE; duty_cycle <= SOLIDSWITCH2_MAX_DUTY_CYCLE; duty_cycle += 5 )
    {
        if ( SOLIDSWITCH2_OK == solidswitch2_write_register ( &solidswitch2, SOLIDSWITCH2_REG_PWM_GEN_DC, 
                                                              ( uint8_t ) ( SOLIDSWITCH2_MAX_DUTY_CYCLE - duty_cycle ) ) )
        {
            log_printf ( &logger, " PWM GEN DC: %u\r\n", ( SOLIDSWITCH2_MAX_DUTY_CYCLE - duty_cycle ) );
        }
        if ( SOLIDSWITCH2_OK == solidswitch2_write_register ( &solidswitch2, SOLIDSWITCH2_REG_PWM_LED_DC, ( uint8_t ) duty_cycle ) )
        {
            log_printf ( &logger, " PWM LED DC: %u\r\n", duty_cycle );
        }
        solidswitch2_toggle_in0_pin ( &solidswitch2 );
        log_printf ( &logger, " Toggle IN0 pin\r\n" );
        solidswitch2_toggle_in1_pin ( &solidswitch2 );
        log_printf ( &logger, " Toggle IN1 pin\r\n\n" );
        Delay_ms ( 250 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SolidSwitch2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
