
---
# Charger 6 Click

> [Charger 6 Click](https://www.mikroe.com/?pid_product=MIKROE-4576) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4576&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the Charger 6 Click driver.
> The library contains drivers to enable/disable battery charging, 
> set current limit, set system min voltage, set fast charge current,
> set charge voltage, etc.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger6

### Example Key Functions

- `charger6_cfg_setup` Config Object Initialization function.
```c
void charger6_cfg_setup ( charger6_cfg_t *cfg );
```

- `charger6_init` Initialization function.
```c
err_t charger6_init ( charger6_t *ctx, charger6_cfg_t *cfg );
```

- `charger6_default_cfg` Click Default Configuration function.
```c
void charger6_default_cfg ( charger6_t *ctx );
```

- `charger6_set_system_minimum_voltage` Charger 6 set system minimum voltage function.
```c
err_t charger6_set_system_minimum_voltage ( charger6_t *ctx, uint16_t sys_min_voltage );
```

- `charger6_set_fast_charge_current` Charger 6 set fast charge current function.
```c
err_t charger6_set_fast_charge_current ( charger6_t *ctx, uint16_t fast_chg_current );
```

- `charger6_get_status` Charger 6 get status function.
```c
err_t charger6_get_status ( charger6_t *ctx, charger6_status_t *chg_status );
```

### Application Init

> Initializes I2C driver and set default configuration:
> input current limit set to 500 mA, system minimum voltage to 3500 mV,
> fast charge current set to 360 mA, charge voltage to 4112 mV and
> enable battery charging. 

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    charger6_cfg_t charger6_cfg;  /**< Click config object. */

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

    charger6_cfg_setup( &charger6_cfg );
    CHARGER6_MAP_MIKROBUS( charger6_cfg, MIKROBUS_1 );
    err_t init_flag = charger6_init( &charger6, &charger6_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    charger6_default_cfg ( &charger6 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 1000 );

    log_printf( &logger, "-------------------------------\r\n" );
    log_printf( &logger, " Set Current Limit   :  500 mA \r\n" );
    charger6_set_input_current_limit( &charger6, 500 );
    Delay_ms ( 100 );
    
    log_printf( &logger, " Set Sys Min Voltage : 3500 mV \r\n" );
    charger6_set_system_minimum_voltage( &charger6, 3500 );
    Delay_ms ( 100 );
    
    log_printf( &logger, " Set Fast Chg Current:  360 mA \r\n" );
    charger6_set_fast_charge_current( &charger6, 360 );
    Delay_ms ( 100 );
    
    log_printf( &logger, " Set Charge Voltage  : 4112 mV \r\n" );
    charger6_set_charge_voltage( &charger6, 4112 );
    Delay_ms ( 100 );
    
    log_printf( &logger, " >> Enable Battery Charging << \r\n" );
    charger6_enable_battery_charging( &charger6 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "-------------------------------\r\n" );
    log_printf( &logger, "       >>>   Status   <<<      \r\n" );
    log_printf( &logger, "-------------------------------\r\n" );
}
```

### Application Task

> This example monitors the operation of the Charger 6 Click and all its charging states. 
 * The user can observe information such as charging status, selected mode, 
 * charging current value, and the momentary value 
 * of the supply voltage relative to the battery voltage.
 * Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    charger6_get_status( &charger6, &chg_status );
    Delay_ms ( 100 );
    
    display_power_good_status( );
    Delay_ms ( 100 );
    
    display_chrg_status( );
    Delay_ms ( 100 );
    
    display_bat_status( );
    Delay_ms ( 100 );
    
    display_chrg_fault_status( );
    Delay_ms ( 100 );
    
    display_vsys_status( );
    log_printf( &logger, "-------------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
