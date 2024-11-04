\mainpage Main Page

---
# Balancer 4 Click

> Balancer 4 Click is a compact add-on board optimized for overvoltage protection balancing the voltage of serially connected batteries. This board features the MP2672A, a highly integrated, flexible switch-mode battery charger for Lithium-Ion batteries with two cells in series from Monolithic Power Systems (MPS). The MP2672A has a narrow voltage DC (NVDC) power structure and monitors the voltage across each cell, equalizing the cell’s voltages if the difference between the two cells exceeds the mismatch threshold. It also has two selective operating modes with configurable output current up to 2A via register setting via I2C serial interface, alongside selectable MP2672A power supply, LED indication, and protection features allowing a reliable operation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/balancer4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/balancer-4-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Balancer 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Balancer 4 Click driver.

#### Standard key functions :

- `balancer4_cfg_setup` Config Object Initialization function.
```c
void balancer4_cfg_setup ( balancer4_cfg_t *cfg );
```

- `balancer4_init` Initialization function.
```c
err_t balancer4_init ( balancer4_t *ctx, balancer4_cfg_t *cfg );
```

- `balancer4_default_cfg` Click Default Configuration function.
```c
err_t balancer4_default_cfg ( balancer4_t *ctx );
```

#### Example key functions :

- `balancer4_write_register` This function writes a desired data byte to the selected register by using I2C serial interface.
```c
err_t balancer4_write_register ( balancer4_t *ctx, uint8_t reg, uint8_t data_in );
```

- `balancer4_write_and_verify_register` This function writes a desired data byte to the selected register and verifies if is is written correctly by reading it.
```c
err_t balancer4_write_and_verify_register ( balancer4_t *ctx, uint8_t reg, uint8_t data_in );
```

- `balancer4_read_register` This function reads a data byte from the selected register by using I2C serial interface.
```c
err_t balancer4_read_register ( balancer4_t *ctx, uint8_t reg, uint8_t *data_out );
```

## Example Description

> This example demonstrates the use of Balancer 4 Click board by configuring the Click board for charging and then reading the status and fault registers.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and configures the Click board for charging.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    balancer4_cfg_t balancer4_cfg;  /**< Click config object. */

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
    balancer4_cfg_setup( &balancer4_cfg );
    BALANCER4_MAP_MIKROBUS( balancer4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == balancer4_init( &balancer4, &balancer4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BALANCER4_ERROR == balancer4_default_cfg ( &balancer4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and displays the status and fault registers on the USB UART every 500ms approximately.

```c
void application_task ( void )
{
    uint8_t status, fault;
    if ( BALANCER4_OK == balancer4_read_register ( &balancer4, BALANCER4_REG_STATUS, &status ) )
    {
        log_printf ( &logger, "\r\n - STATUS - \r\n", status );
        log_printf ( &logger, " Battery status: " );
        if ( status & BALANCER4_STATUS_BATTERY_MISSING )
        {
            log_printf ( &logger, "missing\r\n" );
        }
        else
        {
            log_printf ( &logger, "present\r\n" );
            log_printf ( &logger, " Charging status: " );
            switch ( status & BALANCER4_STATUS_CHG_STAT_MASK )
            {
                case BALANCER4_STATUS_NOT_CHARGING:
                {
                    log_printf ( &logger, "not charging\r\n" );
                    break;
                }
                case BALANCER4_STATUS_PRE_CHARGE:
                {
                    log_printf ( &logger, "pre-charge\r\n" );
                    break;
                }
                case BALANCER4_STATUS_CONSTANT_CHARGE:
                {
                    log_printf ( &logger, "constant current or constant voltage charge\r\n" );
                    break;
                }
                case BALANCER4_STATUS_CHARGING_COMPLETE:
                {
                    log_printf ( &logger, "charging complete\r\n" );
                    break;
                }
            }
        }
    }
    if ( BALANCER4_OK == balancer4_read_register ( &balancer4, BALANCER4_REG_FAULT, &fault ) )
    {
        if ( fault )
        {
            log_printf ( &logger, "\r\n - FAULT - \r\n" );
            if ( fault & BALANCER4_FAULT_WD )
            {
                log_printf ( &logger, " The watchdog timer has expired\r\n" );
            }
            if ( fault & BALANCER4_FAULT_INPUT )
            {
                log_printf ( &logger, " Input OVP has occured\r\n" );
            }
            if ( fault & BALANCER4_FAULT_THERMAL_SD )
            {
                log_printf ( &logger, " Thermal shutdown\r\n" );
            }
            if ( fault & BALANCER4_FAULT_TIMER )
            {
                log_printf ( &logger, " The safety timer has expired\r\n" );
            }
            if ( fault & BALANCER4_FAULT_BAT )
            {
                log_printf ( &logger, " Battery OVP has occured\r\n" );
            }
            switch ( fault & BALANCER4_FAULT_NTC_MASK )
            {
                case BALANCER4_FAULT_NTC_COLD:
                {
                    log_printf ( &logger, " An NTC cold fault has occured\r\n" );
                    break;
                }
                case BALANCER4_FAULT_NTC_COOL:
                {
                    log_printf ( &logger, " An NTC cool fault has occured\r\n" );
                    break;
                }
                case BALANCER4_FAULT_NTC_WARM:
                {
                    log_printf ( &logger, " An NTC warm fault has occured\r\n" );
                    break;
                }
                case BALANCER4_FAULT_NTC_HOT:
                {
                    log_printf ( &logger, " An NTC hot fault has occured\r\n" );
                    break;
                }
            }
        }
    }
    Delay_ms ( 500 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Balancer4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
