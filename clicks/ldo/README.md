\mainpage Main Page

---
# LDO click

> LDO Click is a compact add-on board designed to regulate the output voltage of a power supply to a lower level with a very low dropout voltage. This board features the TPS7A83A, a low-noise, low-dropout linear regulator (LDO) from Texas Instruments capable of sourcing 2A with only 200mV of maximum dropout. The TPS7A8300A has a pin-programmable output voltage from 0.8V-3.95V with a 50mV resolution, or it can be adjustable from 0.8V-5.2V using an external resistor divider.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ldo_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ldo-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the LDO Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LDO Click driver.

#### Standard key functions :

- `ldo_cfg_setup` Config Object Initialization function.
```c
void ldo_cfg_setup ( ldo_cfg_t *cfg );
```

- `ldo_init` Initialization function.
```c
err_t ldo_init ( ldo_t *ctx, ldo_cfg_t *cfg );
```

- `ldo_default_cfg` Click Default Configuration function.
```c
err_t ldo_default_cfg ( ldo_t *ctx );
```

#### Example key functions :

- `ldo_enable_device` This function enables the device by setting the EN pin to HIGH logic state.
```c
void ldo_enable_device ( ldo_t *ctx );
```

- `ldo_disable_device` This function disables the device by setting the EN pin to LOW logic state.
```c
void ldo_disable_device ( ldo_t *ctx );
```

- `ldo_set_vout` This function sets the voltage output.
```c
err_t ldo_set_vout ( ldo_t *ctx, uint16_t vout );
```

## Example Description

> This example demonstrates the use of LDO click by changing the output voltage.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the device default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ldo_cfg_t ldo_cfg;  /**< Click config object. */

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
    ldo_cfg_setup( &ldo_cfg );
    LDO_MAP_MIKROBUS( ldo_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ldo_init( &ldo, &ldo_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LDO_ERROR == ldo_default_cfg ( &ldo ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Changes the output voltage every 3 seconds and displays on the USB UART the currently set voltage output value.

```c
void application_task ( void )
{
    static uint16_t vout = LDO_VOUT_MIN;
    if ( LDO_OK == ldo_set_vout ( &ldo, vout ) )
    {
        log_printf ( &logger, " VOUT: %u mV\r\n\n", vout );
    }
    vout += LDO_VOUT_STEP;
    if ( vout > LDO_VOUT_MAX )
    {
        vout = LDO_VOUT_MIN;
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

## Note

> In order to have up to 3950mV at VOUT you will need to move the VIN SEL on-board jumper
to the VEXT position and provide at least 3950mV voltage input at the VEXT terminal.
Otherwise, the maximum level of VOUT will be limited to 3.3V system voltage.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LDO

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
