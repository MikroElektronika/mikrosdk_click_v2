\mainpage Main Page

---
# Hall Switch 3 click

> Hall Switch 3 Click is a compact add-on board representing a magnetic field-activated switch. This board features the NMH1000, a Hall-effect magnetic switch from NXP Semiconductor. It is a low-voltage, low-current, and low-output data rate device with a very small size. The switch is most sensitive to a vertical field passing through the top-bottom surfaces, orthogonal to the plane of the Hall Switch 3 Click board™.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hallswitch3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/hall-switch-3-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Hall Switch 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Hall Switch 3 Click driver.

#### Standard key functions :

- `hallswitch3_cfg_setup` Config Object Initialization function.
```c
void hallswitch3_cfg_setup ( hallswitch3_cfg_t *cfg );
```

- `hallswitch3_init` Initialization function.
```c
err_t hallswitch3_init ( hallswitch3_t *ctx, hallswitch3_cfg_t *cfg );
```

- `hallswitch3_default_cfg` Click Default Configuration function.
```c
err_t hallswitch3_default_cfg ( hallswitch3_t *ctx );
```

#### Example key functions :

- `hallswitch3_get_mag_data` This function is used to indicates a relative magnetic field strength.
```c
err_t hallswitch3_get_mag_data ( hallswitch3_t *ctx, int8_t *mag_data );
```

- `hallswitch3_set_out_data_rate` This function provides the capability for the user to override the fixed sample rate controlling the sleep-compare-Vout cycle time.
```c
err_t hallswitch3_set_out_data_rate ( hallswitch3_t *ctx, uint8_t odr );
```

- `hallswitch3_get_status` This function reads a status reporting of modes and selections.
```c
err_t hallswitch3_get_status ( hallswitch3_t *ctx, uint8_t *status );
```

## Example Description

> This example demonstrates the use of Hall Switch 3 Click board 
> by reading and displaying the magnetic field strength value.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hallswitch3_cfg_t hallswitch3_cfg;  /**< Click config object. */

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
    hallswitch3_cfg_setup( &hallswitch3_cfg );
    HALLSWITCH3_MAP_MIKROBUS( hallswitch3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == hallswitch3_init( &hallswitch3, &hallswitch3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HALLSWITCH3_ERROR == hallswitch3_default_cfg ( &hallswitch3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example demonstrates the use of the Hall Switch 3 Click board.
> The demo application reads and displays the relative magnetic field strength value [Gaussian units] 
> and detects when the magnetic field strength is not in the configured range. 
> The results are sent to the UART terminal, where you can monitor their changes.

```c
void application_task ( void ) 
{
    int8_t mag_data = 0;
    if ( HALLSWITCH3_OK == hallswitch3_get_mag_data( &hallswitch3, &mag_data ) )
    {
        log_printf( &logger, " Magnetic Field: %d [Gs]\r\n", ( int16_t ) mag_data );
        if ( HALLSWITCH3_OUT_STATE_LOW == hallswitch3_check_mag_field( &hallswitch3 ) )
        {
            log_printf( &logger, " The switch is open.\r\n" );
        }
    }
    Delay_ms( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HallSwitch3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
