\mainpage Main Page

---
# eFuse click

Fuse Click is a compact add-on board that contains a programmable electronic power breaker. This board features the STPW12, an integrated electronic power breaker optimized to monitor the input power from STMicroelectronics. Connected in series to the power rail, it can disconnect the electronic circuitry on its output if the power consumption overcomes the programmed limit. The intervention of the protection is communicated to the MCU through a signal on the fault pin. The device can also be enabled/disabled through a dedicated Enable pin with a direct PWM mode, which can be achieved through an external PWM signal.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/efuse_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/efuse-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jun 2021.
- **Type**          : GPIO type


# Software Support

We provide a library for the eFuse Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for eFuse Click driver.

#### Standard key functions :

- `efuse_cfg_setup` Config Object Initialization function.
```c
void efuse_cfg_setup ( efuse_cfg_t *cfg );
```

- `efuse_init` Initialization function.
```c
EFUSE_RETVAL efuse_init ( efuse_t *ctx, efuse_cfg_t *cfg );
```

- `efuse_default_cfg` Click Default Configuration function.
```c
void efuse_default_cfg ( efuse_t *ctx );
```

#### Example key functions :

- `efuse_enable_device` eFuse enable the device function.
```c
void efuse_enable_device ( efuse_t *ctx );
```

- `efuse_disable_device` eFuse disable the device function.
```c
void efuse_disable_device ( efuse_t *ctx );
```

- `efuse_disable_pwm` eFuse disable the device function.
```c
void efuse_disable_pwm ( efuse_t *ctx);
```

## Example Description

> This library contains API for the eFuse Click driver.
> This demo application shows use of a eFuse Click board™.

**The demo application is composed of two sections :**

### Application Init

> Initialization of GPIO module and log UART.
> After driver initialization the app set default settings.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    efuse_cfg_t efuse_cfg;  /**< Click config object. */

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

    efuse_cfg_setup( &efuse_cfg );
    EFUSE_MAP_MIKROBUS( efuse_cfg, MIKROBUS_1 );
    if ( efuse_init( &efuse, &efuse_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    efuse_default_cfg ( &efuse );
    Delay_ms ( 100 );
    
    log_printf( &logger, " Disable PWM \r\n" );
    efuse_disable_pwm( &efuse );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

```

### Application Task

> This is an example that shows the use of an eFuse Click board™.
> The Electronic Fuse is an electrical safety device that operates to 
> provide overcurrent protection of an electrical circuit.
> The intervention threshold is programmed by the Rs resistor.
> The device disconnects the load if the power overcomes the pre-set threshold, 
> for example, if Vset = 3.9 kOhm, Vin = 12 V, 
> the intervention threshold is set approximately to 875 mA.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) 
{
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "\t Active \r\n" );
    efuse_enable_device( &efuse );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "\tInactive \r\n" );
    efuse_disable_device( &efuse );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

## Note

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.eFuse

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
