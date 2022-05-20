
---
# BATT-MON 4 click

> BATT-MON 4 Click is a compact add-on board representing an advanced battery monitoring solution. This board features the LTC3337, a primary battery state of health (SOH) monitor with a built-in precision coulomb counter from Analog Devices. The LTC3337 is designed to be placed in series with a primary battery with minimal associated series voltage drop. The patented infinite dynamic range coulomb counter tallies all accumulated battery discharge and stores it in an internal register accessible via an I2C interface. In addition, this Click board™ also can set the input current limit and has an additional discharge alarm interrupt and SOH monitoring which measures and reports via an I2C interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/battmon4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/batt-mon-4-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the BATT-MON 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for BATT-MON 4 Click driver.

#### Standard key functions :

- `battmon4_cfg_setup` Config Object Initialization function.
```c
void battmon4_cfg_setup ( battmon4_cfg_t *cfg );
```

- `battmon4_init` Initialization function.
```c
err_t battmon4_init ( battmon4_t *ctx, battmon4_cfg_t *cfg );
```

#### Example key functions :

- `battmon4_get_die_temperature` This function reads the chip DIE temperature in Celsius.
```c
err_t battmon4_get_die_temperature ( battmon4_t *ctx, float *temperature );
```

- `battmon4_get_batt_in_voltage` This function reads the voltage from BATT IN when Ipeak is ON and OFF.
```c
err_t battmon4_get_batt_in_voltage ( battmon4_t *ctx, float *v_ipeak_on, float *v_ipeak_off );
```

- `battmon4_get_batt_out_voltage` This function reads the voltage from BATT OUT when Ipeak is ON and OFF.
```c
err_t battmon4_get_batt_out_voltage ( battmon4_t *ctx, float *v_ipeak_on, float *v_ipeak_off );
```

## Example Description

> This example demonstrates the use of BATT-MON 4 click board by reading the battery voltage and the chip internal temperature.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    battmon4_cfg_t battmon4_cfg;  /**< Click config object. */

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
    battmon4_cfg_setup( &battmon4_cfg );
    BATTMON4_MAP_MIKROBUS( battmon4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == battmon4_init( &battmon4, &battmon4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the chip DIE temperature and voltage from BATT IN and BATT OUT and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    float die_temperature, batt_in_v_ipeak_on, batt_in_v_ipeak_off, batt_out_v_ipeak_on, batt_out_v_ipeak_off;

    if ( BATTMON4_OK == battmon4_get_die_temperature ( &battmon4, &die_temperature ) )
    {
        log_printf ( &logger, " Die Temperature: %.2f C \r\n\n", die_temperature );
    }
    
    if ( BATTMON4_OK == battmon4_get_batt_in_voltage ( &battmon4, &batt_in_v_ipeak_on, &batt_in_v_ipeak_off ) )
    {
        log_printf ( &logger, " BATT IN \r\n Ipeak ON: %.1f mV \r\n Ipeak OFF: %.1f mV \r\n\n", 
                     batt_in_v_ipeak_on, batt_in_v_ipeak_off );
    }
    
    if ( BATTMON4_OK == battmon4_get_batt_out_voltage ( &battmon4, &batt_out_v_ipeak_on, &batt_out_v_ipeak_off ) )
    {
        log_printf ( &logger, " BATT OUT \r\n Ipeak ON: %.1f mV \r\n Ipeak OFF: %.1f mV \r\n\n", 
                     batt_out_v_ipeak_on, batt_out_v_ipeak_off );
    }
    
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.BATTMON4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
