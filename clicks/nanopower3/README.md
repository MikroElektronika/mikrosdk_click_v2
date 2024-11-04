\mainpage Main Page

---
# Nano Power 3 Click

> Nano Power 3 Click is a compact add-on board that steps down voltages from its input (supply) to output (load). This board features the RPL-3.0-R, a buck converter with an integrated inductor from Recom Power. This thermally-enhanced converter uses, as input, voltage from 4 up to 18VDC, thus allowing 5V and 12V supply rails to be used.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/nanopower3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/nano-power-3-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Nano Power 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Nano Power 3 Click driver.

#### Standard key functions :

- `nanopower3_cfg_setup` Config Object Initialization function.
```c
void nanopower3_cfg_setup ( nanopower3_cfg_t *cfg );
```

- `nanopower3_init` Initialization function.
```c
err_t nanopower3_init ( nanopower3_t *ctx, nanopower3_cfg_t *cfg );
```

- `nanopower3_default_cfg` Click Default Configuration function.
```c
err_t nanopower3_default_cfg ( nanopower3_t *ctx );
```

#### Example key functions :

- `nanopower3_set_ctr_pin` Nano Power 3 set CTRL pin state function.
```c
void nanopower3_set_ctr_pin ( nanopower3_t *ctx, uint8_t pin_state );
```

- `nanopower3_set_wiper_pos` Nano Power 3 set wiper position function.
```c
err_t nanopower3_set_wiper_pos ( nanopower3_t *ctx, uint8_t wiper_pos );
```

- `nanopower3_set_voltage` Nano Power 3 set output voltage function.
```c
err_t nanopower3_set_voltage ( nanopower3_t *ctx, uint8_t out_vol );
```

## Example Description

> This library contains API for the Nano Power 3 Click driver.
  This driver provides the functions to set the output voltage treshold.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
  After driver initialization, default settings sets output voltage to 1 V.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nanopower3_cfg_t nanopower3_cfg;  /**< Click config object. */

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
    nanopower3_cfg_setup( &nanopower3_cfg );
    NANOPOWER3_MAP_MIKROBUS( nanopower3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == nanopower3_init( &nanopower3, &nanopower3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( NANOPOWER3_ERROR == nanopower3_default_cfg ( &nanopower3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This example demonstrates the use of the Nano Power 3 Click board™ by changing 
  output voltage every 5 seconds starting from 1 V up to 4.5 V.

```c
void application_task ( void ) 
{
    for ( uint8_t n_cnt = NANOPOWER3_1V_OUT_VOLTAGE; n_cnt <= NANOPOWER3_4V5_OUT_VOLTAGE; n_cnt++ )
    {
        nanopower3_set_voltage( &nanopower3, n_cnt );
        log_printf( &logger, " Selected output is:" );
        print_selected_output_level ( n_cnt );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.NanoPower3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
