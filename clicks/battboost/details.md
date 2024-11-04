
---
# BATT Boost Click

> BATT Boost Click is a compact add-on board that expands a coin battery cell's lifetime and current capability, like the CR2032 and lithium thionyl batteries. This board features the NBM5100A, a coin-cell battery life booster with adaptive power optimization from Nexperia. It is a battery energy management device designed to maximize usable capacity from non-rechargeable, primary batteries when used in low-voltage, low-power applications requiring burst current loads. The devices overcome voltage drop and battery life limitations associated with extracting high pulse currents.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/battboost_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/batt-boost-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the BATT Boost Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for BATT Boost Click driver.

#### Standard key functions :

- `battboost_cfg_setup` Config Object Initialization function.
```c
void battboost_cfg_setup ( battboost_cfg_t *cfg );
```

- `battboost_init` Initialization function.
```c
err_t battboost_init ( battboost_t *ctx, battboost_cfg_t *cfg );
```

- `battboost_default_cfg` Click Default Configuration function.
```c
err_t battboost_default_cfg ( battboost_t *ctx );
```

#### Example key functions :

- `battboost_get_vcap` This function is used to read the storage capacitor voltage status.
```c
err_t battboost_get_vcap ( battboost_t *ctx, float *vcap );
```

- `battboost_set_op_mode` This function is used to select the desired operating mode of the device.
```c
err_t battboost_set_op_mode ( battboost_t *ctx, uint8_t op_mode );
```

- `battboost_get_status` This function reads the the status information of low battery input, capacitor input voltage early warning, VDH output alarm and ready state.
```c
err_t battboost_get_status ( battboost_t *ctx, uint8_t *status );
```

## Example Description

> This library contains API for the BATT Boost Click driver.
> This driver provides the functions to controle battery energy management 
> device designed to maximize usable capacity from non-rechargeable.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, the app executes a default configuration, 
> sets the output voltage to 1.8V, charge current to 16mA, 
> and early warning voltage to 2.6V.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    battboost_cfg_t battboost_cfg;  /**< Click config object. */

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
    battboost_cfg_setup( &battboost_cfg );
    BATTBOOST_MAP_MIKROBUS( battboost_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == battboost_init( &battboost, &battboost_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BATTBOOST_ERROR == battboost_default_cfg ( &battboost ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the BATT Boost Click board. 
> The demo application uses two operations in two states: 
> the charging state and the active state. First, when the device is in a Charge state, 
> the external storage capacitor is charging from VBT using a constant current 
> and displays storage capacitor voltage levels and charge cycle count.
> Upon completion of a Charge state, the device transitions to the Active state 
> at which time VDH becomes a regulated voltage output of 1.8V (default configuration), 
> displays storage capacitor voltage level, and monitors alarms 
> for low output voltage (below 1.8V) and early warning (below 2.4V). 
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    float vcap = 0;
    uint8_t status = 0;
    uint32_t chenergy = 0;

    if ( BATTBOOST_STATUS_READY != battboost_get_ready( &battboost ) )
    {
        if ( BATTBOOST_OK == battboost_set_op_mode( &battboost, BATTBOOST_OP_MODE_CHARGE ) )
        {
            log_printf( &logger, "\nOperating state: Charge\r\n" );
        }

        if ( BATTBOOST_OK == battboost_get_vcap( &battboost, &vcap ) )
        {
            log_printf( &logger, " Capacitor Voltage: %.2f V \r\n", vcap );
        }

        if ( BATTBOOST_OK == battboost_get_chenergy( &battboost, &chenergy ) )
        {
            log_printf( &logger, " Charge cycle count: %lu \r\n", chenergy );
        }
        Delay_ms ( 1000 );
    }
    else
    {
        if ( BATTBOOST_OK == battboost_set_op_mode( &battboost, BATTBOOST_OP_MODE_ACTIVE ) )
        {
            log_printf( &logger, "\nOperating state: Active\r\n" );
            if ( BATTBOOST_OK == battboost_get_vcap( &battboost, &vcap ) )
            {
                log_printf( &logger, " Capacitor Voltage: %.2f V \r\n", vcap );
            }

            if ( BATTBOOST_OK == battboost_get_status( &battboost, &status ) )
            {
                if ( BATTBOOST_STATUS_EW & status )
                {
                    log_printf( &logger, " Status: Early warning.\r\n" );
                }

                if ( BATTBOOST_STATUS_ALRM & status )
                {
                    log_printf( &logger, " Status: Low output voltage in the Active state.\r\n" );
                }
            }
        }
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.BATTBoost

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
