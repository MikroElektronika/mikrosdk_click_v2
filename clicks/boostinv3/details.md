
---
# Boost-INV 3 click

> Boost-INV 3 Click is a compact add-on board designed to supply positive/negative-driven applications. This board features the TPS65132, a dual-output power supply from Texas Instruments. The TPS65132 uses a single inductor scheme for both outputs to provide the user with the smallest solution size and high efficiency. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/boostinv3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/boost-inv-3-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : May 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Boost-INV 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Boost-INV 3 Click driver.

#### Standard key functions :

- `boostinv3_cfg_setup` Config Object Initialization function.
```c
void boostinv3_cfg_setup ( boostinv3_cfg_t *cfg );
```

- `boostinv3_init` Initialization function.
```c
err_t boostinv3_init ( boostinv3_t *ctx, boostinv3_cfg_t *cfg );
```

- `boostinv3_default_cfg` Click Default Configuration function.
```c
err_t boostinv3_default_cfg ( boostinv3_t *ctx );
```

#### Example key functions :

- `boostinv3_set_enp` Boost-INV 3 set ENP pin state function.
```c
void boostinv3_set_enp ( boostinv3_t *ctx, uint8_t out_state );
```

- `boostinv3_set_pos_out` Boost-INV 3 set positive output voltage function.
```c
err_t boostinv3_set_pos_out ( boostinv3_t *ctx, uint8_t out_val );
```

- `boostinv3_set_neg_out` Boost-INV 3 set negative output voltage function.
```c
err_t boostinv3_set_neg_out ( boostinv3_t *ctx, uint8_t out_val );
```

## Example Description

> This library contains API for the Boost-INV 3 Click driver.
  This driver provides the functions to set the output voltage treshold.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
  After driver initialization, default settings enable the positive and 
  negative output and sets the output voltage to 4 V.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    boostinv3_cfg_t boostinv3_cfg;  /**< Click config object. */

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
    boostinv3_cfg_setup( &boostinv3_cfg );
    BOOSTINV3_MAP_MIKROBUS( boostinv3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == boostinv3_init( &boostinv3, &boostinv3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms( 100 );
    
    if ( BOOSTINV3_ERROR == boostinv3_default_cfg ( &boostinv3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> This example demonstrates the use of the Boost-INV 3 Click board by changing 
 * output voltage every 5 seconds starting from 4 V up to 6 V.

```c
void application_task ( void ) 
{
    for ( uint8_t n_cnt = BOOSTINV3_OUT_VOLTAGE_4V; n_cnt <= BOOSTINV3_OUT_VOLTAGE_6V; n_cnt++ )
    {
        err_t error_flag = boostinv3_set_pos_out( &boostinv3, n_cnt );
        error_flag |= boostinv3_set_neg_out( &boostinv3, n_cnt );
        if ( BOOSTINV3_OK == error_flag )
        {
            log_printf( &logger, " Set positive and negative voltage to %.1f V \r\n", 
                        ( BOOSTINV3_MIN_VOL_LVL + n_cnt * BOOSTINV3_INCREMENT ) );
        }
        else
        {
            log_printf( &logger, " Error has occurred!!! \r\n" );
        }
        Delay_ms( 5000 );
    }
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.BoostINV3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
