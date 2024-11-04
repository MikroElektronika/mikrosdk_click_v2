\mainpage Main Page

---
# BATT Boost 2 Click

> BATT Boost 2 Click is a compact add-on board designed to extend the battery life of non-rechargeable, primary batteries in low-voltage, low-power applications. This board features the NBM7100A, a coin-cell battery-life booster with adaptive power optimization from Nexperia. The NBM7100A integrates two high-efficiency DC-DC conversion stages and an intelligent learning algorithm to optimize energy usage, allowing it to handle bursts of current up to 200mA without depleting the battery. It features two output terminals: VDH for high pulse load applications and VDP for powering 'Always-ON' components. Communication with the host MCU is achieved via the I2C interface, supporting up to 1MHz clock frequencies.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/battboost2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/batt-boost-2-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Feb 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the BATT Boost 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for BATT Boost 2 Click driver.

#### Standard key functions :

- `battboost2_cfg_setup` Config Object Initialization function.
```c
void battboost2_cfg_setup ( battboost2_cfg_t *cfg );
```

- `battboost2_init` Initialization function.
```c
err_t battboost2_init ( battboost2_t *ctx, battboost2_cfg_t *cfg );
```

- `battboost2_default_cfg` Click Default Configuration function.
```c
err_t battboost2_default_cfg ( battboost2_t *ctx );
```

#### Example key functions :

- `battboost2_set_vset` This function is used to control the output voltage levels of the NBM7100ABQX, Coin cell battery life booster with adaptive power optimization on the BATT Boost 2 Click board. 
```c
err_t battboost2_set_vset ( battboost2_t *ctx, float vset );
```

- `battboost2_high_impedance_mode` This function is used to configures the VDH high-impedance mode in Standby and Active states of the NBM7100ABQX, Coin cell battery life booster  with adaptive power optimization on the BATT Boost 2 Click board. 
```c
err_t battboost2_high_impedance_mode ( battboost2_t *ctx );
```

- `battboost2_set_on_pin_state` This function sets the desired states of the ON (RST) pin of the NBM7100ABQX, Coin cell battery life booster with adaptive power optimization on the BATT Boost 2 Click board. 
```c
void battboost2_set_on_pin_state ( battboost2_t *ctx, uint8_t start );
```

## Example Description

> This library contains API for the BATT Boost 2 Click driver.
  This driver provides the functions to control battery energy management 
  device designed to maximize usable capacity from non-rechargeable.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
  After driver initialization, the app executes a default configuration, 
  sets the output voltage to 1.8V, charge current to 16mA, 
  and early warning voltage to 2.6V.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    battboost2_cfg_t battboost2_cfg;  /**< Click config object. */

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
    battboost2_cfg_setup( &battboost2_cfg );
    BATTBOOST2_MAP_MIKROBUS( battboost2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == battboost2_init( &battboost2, &battboost2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BATTBOOST2_ERROR == battboost2_default_cfg ( &battboost2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the BATT Boost 2 Click board. 
  The demo application uses two operations in two states: 
  the charging state and the active state. First, when the device is in a Charge state, 
  the external storage capacitor is charging from VBT using a constant current 
  and displays storage capacitor voltage levels and charge cycle count.
  Upon completion of a Charge state, the device transitions to the Active state 
  at which time VDH becomes a regulated voltage output of 1.8V (default configuration), 
  displays storage capacitor voltage level, and monitors alarms 
  for low output voltage (below 1.8V) and early warning (below 2.4V). 
  Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    float vcap = 0;
    uint8_t status = 0;
    uint32_t chenergy = 0;

    if ( BATTBOOST2_STATUS_READY != battboost2_get_ready( &battboost2 ) )
    {
        if ( BATTBOOST2_OK == battboost2_set_op_mode( &battboost2, BATTBOOST2_OP_MODE_CHARGE ) )
        {
            log_printf( &logger, "\nOperating state: Charge\r\n" );
        }

        if ( BATTBOOST2_OK == battboost2_get_vcap( &battboost2, &vcap ) )
        {
            log_printf( &logger, " Capacitor Voltage: %.2f V \r\n", vcap );
        }

        if ( BATTBOOST2_OK == battboost2_get_chenergy( &battboost2, &chenergy ) )
        {
            log_printf( &logger, " Charge cycle count: %lu \r\n", chenergy );
        }
        Delay_ms ( 1000 );
    }
    else
    {
        if ( BATTBOOST2_OK == battboost2_set_op_mode( &battboost2, BATTBOOST2_OP_MODE_ACTIVE ) )
        {
            log_printf( &logger, "\nOperating state: Active\r\n" );
            if ( BATTBOOST2_OK == battboost2_get_vcap( &battboost2, &vcap ) )
            {
                log_printf( &logger, " Capacitor Voltage: %.2f V \r\n", vcap );
            }

            if ( BATTBOOST2_OK == battboost2_get_status( &battboost2, &status ) )
            {
                if ( BATTBOOST2_STATUS_EW & status )
                {
                    log_printf( &logger, " Status: Early warning.\r\n" );
                }

                if ( BATTBOOST2_STATUS_ALRM & status )
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
- Click.BATTBoost2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
