
---
# Brushless 12 Click

Brushless 12 Click is a compact add-on board suitable for controlling BLDC motors with any MCU. This board features the L6235, DMOS fully integrated 3-phase motor driver with overcurrent protection from STMicroelectronics.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/brushless12_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/brushless-12-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2021.
- **Type**          : GPIO type


# Software Support

We provide a library for the Brushless12 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Brushless12 Click driver.

#### Standard key functions :

- `brushless12_cfg_setup` Config Object Initialization function.
```c
void brushless12_cfg_setup ( brushless12_cfg_t *cfg );
```

- `brushless12_init` Initialization function.
```c
BRUSHLESS12_RETVAL brushless12_init ( brushless12_t *ctx, brushless12_cfg_t *cfg );
```

- `brushless12_default_cfg` Click Default Configuration function.
```c
void brushless12_default_cfg ( brushless12_t *ctx );
```

#### Example key functions :

- `brushless12_set_brake` This function sets the BRK pin to the desired state.
```c
void brushless12_set_brake ( brushless12_t *ctx, uint8_t state );
```

- `brushless12_set_direction` This function sets the F/R pin to the desired state.
```c
void brushless12_set_direction ( brushless12_t *ctx, uint8_t state );
```

- `brushless12_set_enable` This function sets the EN pin to the desired state.
```c
void brushless12_set_enable ( brushless12_t *ctx, uint8_t state );
```

## Example Description

> This example demonstrates the use of Brushless 12 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and sets the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    brushless12_cfg_t brushless12_cfg;  /**< Click config object. */

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

    brushless12_cfg_setup( &brushless12_cfg );
    BRUSHLESS12_MAP_MIKROBUS( brushless12_cfg, MIKROBUS_1 );
    
    if ( brushless12_init( &brushless12, &brushless12_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    brushless12_default_cfg( &brushless12 );
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Drives the motor in the forward direction for 5 seconds, then pulls brake for 2 seconds, 
> and after that drives it in the reverse direction for 5 seconds, and pulls brake for 2 seconds.
> Each step will be logged on the USB UART where you can track the program flow.

```c

void application_task ( void )
{
    log_printf( &logger, "The motor turns forward! \r\n" );
    brushless12_set_direction ( &brushless12, BRUSHLESS12_DIR_FORWARD );
    brushless12_set_brake ( &brushless12, BRUSHLESS12_START );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "Pull brake! \r\n" );
    brushless12_set_brake ( &brushless12, BRUSHLESS12_BRAKE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "The motor turns in reverse! \r\n" );
    brushless12_set_direction ( &brushless12, BRUSHLESS12_DIR_REVERSE );
    brushless12_set_brake ( &brushless12, BRUSHLESS12_START );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "Pull brake! \r\n" );
    brushless12_set_brake ( &brushless12, BRUSHLESS12_BRAKE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless12

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
