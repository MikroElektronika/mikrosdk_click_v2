\mainpage Main Page

---
# EasyPull click

> EasyPull Click is a compact add-on board designed to easily configure mikroBUS™ signals into pull-up or pull-down states, perfect for various applications. It features a universal setup with 4.7kΩ resistors to ensure stable performance across vital communication lines such as SPI, UART, I2C, and standard mikroBUS™ signals (AN, RST, PWM, INT).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/easypull_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/easypull-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2023.
- **Type**          : GPIO type


# Software Support

We provide a library for the EasyPull Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for EasyPull Click driver.

#### Standard key functions :

- `easypull_cfg_setup` Config Object Initialization function.
```c
void easypull_cfg_setup ( easypull_cfg_t *cfg );
```

- `easypull_init` Initialization function.
```c
err_t easypull_init ( easypull_t *ctx, easypull_cfg_t *cfg );
```

#### Example key functions :

- `easypull_get_an_pin` This function reads the state of the AN pin of EasyPull click board.
```c
uint8_t easypull_get_an_pin ( easypull_t *ctx );
```

- `easypull_get_rst_pin` This function reads the state of the RST pin of EasyPull click board.
```c
uint8_t easypull_get_rst_pin ( easypull_t *ctx );
```

- `easypull_get_cs_pin` This function reads the state of the CS pin of EasyPull click board.
```c
uint8_t easypull_get_cs_pin ( easypull_t *ctx );
```

## Example Description

> This example demonstrates the use of EasyPull Click boards.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and USB UART logger.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    easypull_cfg_t easypull_cfg;  /**< Click config object. */

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
    easypull_cfg_setup( &easypull_cfg );
    EASYPULL_MAP_MIKROBUS( easypull_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == easypull_init( &easypull, &easypull_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> It checks the state of the pins and displays their state on the USB UART.

```c
void application_task ( void ) 
{
    if ( EASYPULL_PIN_STATE_HIGH == easypull_get_an_pin( &easypull ) )
    {
        log_printf( &logger, " AN pin state: HIGH \n" );
    }
    else
    {
        log_printf( &logger, " AN pin state: LOW \n" );
    }

    if ( EASYPULL_PIN_STATE_HIGH == easypull_get_rst_pin( &easypull ) )
    {
        log_printf( &logger, " RST pin state: HIGH \n" );
    }
    else
    {
        log_printf( &logger, " RST pin state: LOW \n" );
    }

    if ( EASYPULL_PIN_STATE_HIGH == easypull_get_cs_pin( &easypull ) )
    {
        log_printf( &logger, " CS pin state: HIGH \n" );
    }
    else
    {
        log_printf( &logger, " CS pin state: LOW \n" );
    }

    if ( EASYPULL_PIN_STATE_HIGH == easypull_get_pwm_pin( &easypull ) )
    {
        log_printf( &logger, " PWM pin state: HIGH \n" );
    }
    else
    {
        log_printf( &logger, " PWM pin state: LOW \n" );
    }

    if ( EASYPULL_PIN_STATE_HIGH == easypull_get_int_pin( &easypull ) )
    {
        log_printf( &logger, " INT pin state: HIGH \n" );
    }
    else
    {
        log_printf( &logger, " INT pin state: LOW \n" );
    }
    log_printf( &logger, "- - - - - - - - - - - - - \r\n" );
    Delay_ms ( 1000 );

}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.EasyPull

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
