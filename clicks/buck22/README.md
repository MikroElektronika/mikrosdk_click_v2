\mainpage Main Page

---
# Buck 22 Click

> Buck 22 Click is a compact add-on board that steps down the voltage from its input (supply) to its output (load). This board features the TPS62869, a high-frequency synchronous step-down converter with an I2C interface from Texas Instruments, providing an efficient, adaptive, and high power-density solution. The TPS62869 operates in PWM mode at medium to heavy loads (also for the slightest output voltage ripple), and it automatically enters Power-Save Mode operation at light load to maintain high efficiency over the entire output load current range. With its DCS-Control™ architecture, excellent load transient performance and tight output voltage accuracy are achieved alongside adjustable output voltage range from 0.8V to 3.35V with a 10mV step size.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/buck22_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/buck-22-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Buck 22 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Buck 22 Click driver.

#### Standard key functions :

- `buck22_cfg_setup` Config Object Initialization function.
```c
void buck22_cfg_setup ( buck22_cfg_t *cfg );
```

- `buck22_init` Initialization function.
```c
err_t buck22_init ( buck22_t *ctx, buck22_cfg_t *cfg );
```

#### Example key functions :

- `buck22_set_vout` This function sets the output voltage by using I2C serial interface.
```c
err_t buck22_set_vout ( buck22_t *ctx, uint16_t vout_mv );
```

- `buck22_read_vout` This function reads the output voltage by using I2C serial interface.
```c
err_t buck22_read_vout ( buck22_t *ctx, uint16_t *vout_mv );
```

- `buck22_get_pg_pin` This function returns the power good (PG) pin logic state.
```c
uint8_t buck22_get_pg_pin ( buck22_t *ctx );
```

## Example Description

> This example demonstrates the use of Buck 22 Click by changing the output voltage.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and sets the control settings.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buck22_cfg_t buck22_cfg;  /**< Click config object. */

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
    buck22_cfg_setup( &buck22_cfg );
    BUCK22_MAP_MIKROBUS( buck22_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == buck22_init( &buck22, &buck22_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BUCK22_ERROR == buck22_set_control ( &buck22, BUCK22_CONTROL_DEFAULT_SETTING ) )
    {
        log_error( &logger, " Set control." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Changes the output voltage every 3 seconds and displays on the USB UART the currently set voltage output value. It also checks the power good pin indicator.

```c
void application_task ( void )
{
    if ( !buck22_get_pg_pin ( &buck22 ) )
    {
        log_info ( &logger, " Device is shut down. " );
        while ( !buck22_get_pg_pin ( &buck22 ) );
        log_info ( &logger, " Device is powered up. " );
    }
    static uint16_t vout_mv = BUCK22_VOUT_MIN;
    if ( BUCK22_OK == buck22_set_vout ( &buck22, vout_mv ) )
    {
        if ( BUCK22_OK == buck22_read_vout ( &buck22, &vout_mv ) )
        {
            log_printf ( &logger, " Vout: %u mV\r\n", vout_mv );
        }
    }
    vout_mv += 100;
    if ( vout_mv > BUCK22_VOUT_MAX )
    {
        vout_mv = BUCK22_VOUT_MIN;
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck22

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
