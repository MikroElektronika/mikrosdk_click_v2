
---
# Headphone Amp 2 click

> Headphone AMP 2 Click is a compact add-on board that contains a headphone amplifier. 
> This board features the TS2007FC, a class-D audio power amplifier from STMicroelectronics. 
> The TS2007FC can drive up to 2.3W into 4Ω load at 5V, achieving better efficiency 
> than typical class-AB audio power amplifiers. It can switch between two gain settings, 
> either 6 or 12dB, through one mikroBUS™ pin, has the pop and click reduction circuitry, 
> and a Standby mode for reduced power consumption. Besides, it is equipped with protection features, 
> allowing a reliable operation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/headphoneamp2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/headphone-amp-2-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2023.
- **Type**          : GPIO type


# Software Support

We provide a library for the Headphone Amp 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Headphone Amp 2 Click driver.

#### Standard key functions :

- `headphoneamp2_cfg_setup` Config Object Initialization function.
```c
void headphoneamp2_cfg_setup ( headphoneamp2_cfg_t *cfg );
```

- `headphoneamp2_init` Initialization function.
```c
err_t headphoneamp2_init ( headphoneamp2_t *ctx, headphoneamp2_cfg_t *cfg );
```

- `headphoneamp2_default_cfg` Click Default Configuration function.
```c
void headphoneamp2_default_cfg ( headphoneamp2_t *ctx );
```

#### Example key functions :

- `headphoneamp2_set_device_on` Headphone Amp 2 set device on function.
```c
void headphoneamp2_set_device_on ( headphoneamp2_t *ctx );
```

- `headphoneamp2_gain_select` Headphone Amp 2 select gain level function.
```c
void headphoneamp2_gain_select ( headphoneamp2_t *ctx, headphoneamp2_gain_select_value_t sel_gain );
```

- `headphoneamp2_change_gain` Headphone Amp 2 change gain function.
```c
void headphoneamp2_change_gain ( headphoneamp2_t *ctx ); 
```

## Example Description

> This library contains API for the Headphone AMP 2 click driver.
> This demo application shows use of a Headphone AMP 2 click board™.

**The demo application is composed of two sections :**

### Application Init

> Initialization of GPIO module and log UART.
> After driver initialization the app set default settings, 
> performs power-up sequence, sets a the sound volume of 6 dB.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    headphoneamp2_cfg_t headphoneamp2_cfg;  /**< Click config object. */

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
    headphoneamp2_cfg_setup( &headphoneamp2_cfg );
    HEADPHONEAMP2_MAP_MIKROBUS( headphoneamp2_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == headphoneamp2_init( &headphoneamp2, &headphoneamp2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    headphoneamp2_default_cfg ( &headphoneamp2 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example demonstrates the use of the Headphone AMP 2 click board™.
> The app performs circles the volume switch between two gain settings,
> 6 dB or 12 dB via a logic signal on the gain select pin.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    headphoneamp2_change_gain( &headphoneamp2 );
    log_printf( &logger, " The gain level has been changed.\r\n" );
    Delay_ms( 5000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HeadphoneAmp2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
