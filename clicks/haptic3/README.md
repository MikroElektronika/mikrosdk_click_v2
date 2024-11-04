\mainpage Main Page

---
# HAPTIC 3 Click

> Haptic 3 Click is a compact add-on board that uses advanced vibration patterns and waveforms to convey information to a user. This board features the DA7282, a linear resonant actuator (LRA), and an eccentric rotating mass (ERM) haptic driver from Dialog Semiconductor. The DA7282 features LRA or ERM drive capability with automatic closed-loop LRA resonant frequency tracking, guaranteeing consistency across LRA production tolerances. It also offers wideband operation that fully utilizes the capabilities of newer wideband and multi-directional LRAs, alongside three external general-purpose inputs for triggering up to six independent haptic sequences.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/haptic3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/haptic-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the HAPTIC 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for HAPTIC 3 Click driver.

#### Standard key functions :

- `haptic3_cfg_setup` Config Object Initialization function.
```c
void haptic3_cfg_setup ( haptic3_cfg_t *cfg );
```

- `haptic3_init` Initialization function.
```c
err_t haptic3_init ( haptic3_t *ctx, haptic3_cfg_t *cfg );
```

- `haptic3_default_cfg` Click Default Configuration function.
```c
err_t haptic3_default_cfg ( haptic3_t *ctx );
```

#### Example key functions :

- `haptic3_set_vibration_level` This function sets the motor vibration level.
```c
err_t haptic3_set_vibration_level ( haptic3_t *ctx, float level );
```

- `haptic3_get_vibration_level` This function reads the motor vibration level.
```c
err_t haptic3_get_vibration_level ( haptic3_t *ctx, float *level );
```

- `haptic3_write_register` This function writes a desired data to the selected register by using I2C serial interface.
```c
err_t haptic3_write_register ( haptic3_t *ctx, uint8_t reg, uint8_t data_in );
```

## Example Description

> This example demonstrates the use of HAPTIC 3 Click board by controlling the attached motor vibration level.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    haptic3_cfg_t haptic3_cfg;  /**< Click config object. */

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
    haptic3_cfg_setup( &haptic3_cfg );
    HAPTIC3_MAP_MIKROBUS( haptic3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == haptic3_init( &haptic3, &haptic3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HAPTIC3_ERROR == haptic3_default_cfg ( &haptic3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Changes the motor vibration level every 2 seconds from MAX to MIN, and displays the currently set level on the USB UART.

```c
void application_task ( void )
{
    float vibration_level;
    if ( HAPTIC3_OK == haptic3_set_vibration_level ( &haptic3, HAPTIC3_VIBRATION_LEVEL_MAX ) )
    {
        if ( HAPTIC3_OK == haptic3_get_vibration_level ( &haptic3, &vibration_level ) )
        {
            log_printf( &logger, " Vibration level: %.3f \r\n\n", vibration_level );
        }
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    if ( HAPTIC3_OK == haptic3_set_vibration_level ( &haptic3, HAPTIC3_VIBRATION_LEVEL_MIN ) )
    {
        if ( HAPTIC3_OK == haptic3_get_vibration_level ( &haptic3, &vibration_level ) )
        {
            log_printf( &logger, " Vibration level: %.3f \r\n\n", vibration_level );
        }
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HAPTIC3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
