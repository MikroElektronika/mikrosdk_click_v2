\mainpage Main Page

---
# eFuse 2 click

> eFuse 2 Click is a compact add-on board that contains an integrated FET hot-swap device. This board features the TPS259631, a highly integrated circuit protection and power management solution from Texas Instruments. It provides multiple protection modes against overloads, short circuits, voltage surges, and excessive inrush current.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/efuse2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/efuse-2-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the eFuse2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for eFuse2 Click driver.

#### Standard key functions :

- `efuse2_cfg_setup` Config Object Initialization function.
```c
void efuse2_cfg_setup ( efuse2_cfg_t *cfg );
```

- `efuse2_init` Initialization function.
```c
err_t efuse2_init ( efuse2_t *ctx, efuse2_cfg_t *cfg );
```

- `efuse2_default_cfg` Click Default Configuration function.
```c
err_t efuse2_default_cfg ( efuse2_t *ctx );
```

#### Example key functions :

- `efuse2_set_operating_voltage` Set operating voltage function.
```c
void efuse2_set_operating_voltage ( efuse2_t *ctx, float voltage, float *min_voltage, float *max_voltage );
```

- `efuse2_set_current_limit` Set operating current function.
```c
void efuse2_set_current_limit ( efuse2_t *ctx, float current );
```

- `efuse2_get_fault` Get fault function.
```c
uint8_t efuse2_get_fault ( efuse2_t *ctx );
```

## Example Description

> This is an example that demonstrate the use of the eFuse 2 click board.

**The demo application is composed of two sections :**

### Application Init

> Initialization driver enables - I2C,  
> AD5175: enable write, set the normal operating mode and operating  current to the 1,2 A;  
> AD5241: set operating voltage to the 12,0 V; 
> Display diagnostic states.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    efuse2_cfg_t efuse2_cfg;  /**< Click config object. */

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
    efuse2_cfg_setup( &efuse2_cfg );
    EFUSE2_MAP_MIKROBUS( efuse2_cfg, MIKROBUS_1 );
    err_t init_flag = efuse2_init( &efuse2, &efuse2_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    efuse2_default_cfg ( &efuse2 );
    Delay_ms( 100 );
    op_current = 1.2;
    op_voltage = 12.0;

    log_printf( &logger, "-----------------------------\r\n" );
    log_printf( &logger, "    Set operating  value:    \r\n" );
    log_printf( &logger, "       Voltage: 12.0 V       \r\n" );
    efuse2_set_operating_voltage( &efuse2, op_voltage, &min_voltage, &max_voltage );
    Delay_ms( 1000 );

    log_printf( &logger, "       Current:  1.2 A       \r\n" );
    log_printf( &logger, "-----------------------------\r\n" );
    efuse2_set_current_limit( &efuse2, op_current );
    Delay_ms( 1000 );

    log_printf( &logger, "    Turn ON Power Supply     \r\n" );
    log_printf( &logger, "-----------------------------\r\n" );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> eFuse 2 click board uses USB UART log to display operating voltage, OVLO, UVLO and current limit condition. This firmware provides the functions to set the operating voltage and current limiting conditions in order to provide the threshold of the fault conditions.
> When one of the fault conditions is met, the microcontroller is notified via INT pin which is checked by the app to initiate a shutdown mode. All data logs write on USB UART changes every 2000 milliseconds.

```c

void application_task ( void ) {
    if ( EFUSE2_FAULT == efuse2_get_fault( &efuse2 ) ) {
        efuse2_operating_mode( &efuse2, EFUSE2_AD5175_SHUTDOWN_MODE );
        Delay_ms( 1000 );

        log_printf( &logger, "        Shutdown Mode        \r\n" );
        log_printf( &logger, "-----------------------------\r\n" );
        for ( ; ; );
    }

    log_printf( &logger, " Oper. Voltage : %.3f V \r\n", op_voltage );
    log_printf( &logger, " Undervoltage  : %.3f V \r\n", min_voltage );
    log_printf( &logger, " Overvoltage   : %.3f V \r\n", max_voltage );
    log_printf( &logger, " Current Limit : %.3f A \r\n", op_current );
    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms( 2000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.eFuse2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
