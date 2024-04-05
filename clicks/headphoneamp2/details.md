
---
# Headphone AMP 2 click

> Headphone AMP 2 Click is a compact add-on board that contains a stereo headphone amplifier. 
> This board features the MAX9723, a stereo DirectDrive headphone amplifier with BassMax, volume control, 
> and I2C from Analog Devices. The amplifier delivers 62mW into a 16Ω load, 
> and features a high 90dB PSRR at 1KHz and a low 0.006% THD+N. 
> It also features an integrated 32-level volume control, click-and-pop suppression, 
> ±8kV HBM ESD-protected headphone outputs, short-circuit and thermal-overload protection, and more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/headphoneamp2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/headphone-amp-2-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jun 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Headphone AMP 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Headphone AMP 2 Click driver.

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
err_t headphoneamp2_default_cfg ( headphoneamp2_t *ctx );
```

#### Example key functions :

- `headphoneamp2_set_command` Headphone AMP 2 set the command function.
```c
err_t headphoneamp2_set_command ( headphoneamp2_t *ctx, headphoneamp2_cmd_t cmd_ctrl );
```

- `headphoneamp2_enable` Headphone AMP 2 enable the device function.
```c
void headphoneamp2_enable ( headphoneamp2_t *ctx );
```

- `headphoneamp2_disable` Headphone AMP 2 disable the device function.
```c
void headphoneamp2_disable ( headphoneamp2_t *ctx );
```

## Example Description

> This example demonstrates the use of the Headphone AMP 2 Click board™, 
> the headphone amplifier with BassMax and volume control.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C module and log UART.
> After driver initialization, the app sets the default configuration.

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
    if ( I2C_MASTER_ERROR == headphoneamp2_init( &headphoneamp2, &headphoneamp2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HEADPHONEAMP2_ERROR == headphoneamp2_default_cfg ( &headphoneamp2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the Headphone AMP 2 Click board™.
> The application wakes up the device, enables BassMax and Maximum Gain modes, 
> and switches the sound volume from level 1 to the max level.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    static headphoneamp2_cmd_t cmd_ctrl;
    cmd_ctrl.wakes_up = HEADPHONEAMP2_CMD_ENABLE;
    cmd_ctrl.bass_max = HEADPHONEAMP2_CMD_ENABLE;
    cmd_ctrl.gain_max = HEADPHONEAMP2_CMD_ENABLE;
    cmd_ctrl.volume   = HEADPHONEAMP2_VOL_MUTE;
    
    log_printf( &logger, " Volume : " );
    for ( uint8_t volume = HEADPHONEAMP2_VOL_LVL_1; volume <= HEADPHONEAMP2_VOL_LVL_MAX; volume++ )
    {
        cmd_ctrl.volume = volume;
        if ( HEADPHONEAMP2_OK == headphoneamp2_set_command( &headphoneamp2, cmd_ctrl ) )
        {
            log_printf( &logger, "|" );
        }
        Delay_ms ( 1000 );
    }
    log_printf( &logger, "\r\n-------------------------\r\n" );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HeadphoneAMP2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
