\mainpage Main Page

---
# Buck 23 click

> Buck 23 Click is a compact add-on board with a DC-DC power converter that steps down the voltage from its input to its output. This board features the MAX20010C, a fully-integrated, high-efficiency, synchronous, step-down converter from Analog Devices. The MAX20010C achieves 6A continuous output current over a wide input supply range from 3V to 5.5V. It offers ±2% output voltage accuracy and can operate efficiently over interface-configurable output voltage load range from 0.5V to 1.58V. The MAX20010C also offers programmable soft-start, overcurrent, and overtemperature protections.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/buck23_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/buck-23-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Buck 23 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Buck 23 Click driver.

#### Standard key functions :

- `buck23_cfg_setup` Config Object Initialization function.
```c
void buck23_cfg_setup ( buck23_cfg_t *cfg );
```

- `buck23_init` Initialization function.
```c
err_t buck23_init ( buck23_t *ctx, buck23_cfg_t *cfg );
```

- `buck23_default_cfg` Click Default Configuration function.
```c
err_t buck23_default_cfg ( buck23_t *ctx );
```

#### Example key functions :

- `buck23_set_vstep` This function sets the voltage output step to 10mV or 12.5mV.
```c
err_t buck23_set_vstep ( buck23_t *ctx, uint8_t vstep );
```

- `buck23_set_vout` This function sets the voltage output.
```c
err_t buck23_set_vout ( buck23_t *ctx, uint16_t vout_mv );
```

- `buck23_get_pg_pin` This function returns the PG (power good) pin logic state.
```c
uint8_t buck23_get_pg_pin ( buck23_t *ctx );
```

## Example Description

> This example demonstrates the use of Buck 23 click by changing the output voltage.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the device default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buck23_cfg_t buck23_cfg;  /**< Click config object. */

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
    buck23_cfg_setup( &buck23_cfg );
    BUCK23_MAP_MIKROBUS( buck23_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == buck23_init( &buck23, &buck23_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BUCK23_ERROR == buck23_default_cfg ( &buck23 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Changes the output voltage once per second and displays on the USB UART the currently set
voltage output value as well as its range and resolution. It also checks and displays the status
register content and the power good pin indication.

```c
void application_task ( void )
{
    uint16_t vout_mv;
    uint8_t status;
    if ( BUCK23_OK == buck23_set_vstep ( &buck23, BUCK23_VSTEP_10 ) )
    {
        log_printf ( &logger, " ------------------------------------\r\n" );
        log_printf ( &logger, " VOUT resolution: 10mV\r\n VOUT range: 500mV to 1270mV\r\n" );
        log_printf ( &logger, " ------------------------------------" );
    }
    for ( vout_mv = BUCK23_VOUT_MIN_VSTEP_10; vout_mv <= BUCK23_VOUT_MAX_VSTEP_10; vout_mv += 50 )
    {
        if ( BUCK23_OK == buck23_read_register ( &buck23, BUCK23_REG_STATUS, &status ) )
        {
            log_printf ( &logger, "\r\n STATUS: 0x%.2X\r\n", ( uint16_t ) status );
        }
        if ( BUCK23_OK == buck23_set_vout ( &buck23, vout_mv ) )
        {
            log_printf ( &logger, " VOUT: %u mV\r\n", vout_mv );
        }
        if ( !buck23_get_pg_pin ( &buck23 ) )
        {
            log_printf ( &logger, " ERROR: No power good\r\n" );
            log_printf ( &logger, " Restarting device\r\n" );
            buck23_restart_device ( &buck23 );
            vout_mv -= 50;
        }
        Delay_ms ( 1000 );
    }
    if ( BUCK23_OK == buck23_set_vstep ( &buck23, BUCK23_VSTEP_12_5 ) )
    {
        log_printf ( &logger, " ------------------------------------\r\n" );
        log_printf ( &logger, " VOUT resolution: 12.5mV\r\n VOUT range: 625mV to 1587.5mV\r\n" );
        log_printf ( &logger, " ------------------------------------" );
    }
    for ( vout_mv = BUCK23_VOUT_MIN_VSTEP_12_5; vout_mv <= BUCK23_VOUT_MAX_VSTEP_12_5; vout_mv += 50 )
    {
        if ( BUCK23_OK == buck23_read_register ( &buck23, BUCK23_REG_STATUS, &status ) )
        {
            log_printf ( &logger, "\r\n STATUS: 0x%.2X\r\n", ( uint16_t ) status );
        }
        if ( BUCK23_OK == buck23_set_vout ( &buck23, vout_mv ) )
        {
            log_printf ( &logger, " VOUT: %u mV\r\n", vout_mv );
        }
        if ( !buck23_get_pg_pin ( &buck23 ) )
        {
            log_printf ( &logger, " ERROR: No power good\r\n" );
            log_printf ( &logger, " Restarting device\r\n" );
            buck23_restart_device ( &buck23 );
            vout_mv -= 50;
        }
        Delay_ms ( 1000 );
    }
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck23

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
