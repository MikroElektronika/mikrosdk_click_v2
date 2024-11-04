\mainpage Main Page

---
# Charger 17 Click

> Charger 17 Click is a compact add-on board that provides a single-cell battery charging solution. This board features the RT9471, a 3A single-cell switching battery charger from Richtek. It is a highly-integrated battery charge and system power-path management device for single-cell Li-Ion and Li-Polymer batteries. The high-efficiency 1.5MHz synchronous switch-mode buck charger achieves up to 92% charge efficiency at 2A with 5V input and 3.8V battery.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/charger17_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/charger-17-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Charger 17 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Charger 17 Click driver.

#### Standard key functions :

- `charger17_cfg_setup` Config Object Initialization function.
```c
void charger17_cfg_setup ( charger17_cfg_t *cfg );
```

- `charger17_init` Initialization function.
```c
err_t charger17_init ( charger17_t *ctx, charger17_cfg_t *cfg );
```

- `charger17_default_cfg` Click Default Configuration function.
```c
err_t charger17_default_cfg ( charger17_t *ctx );
```

#### Example key functions :

- `charger17_enable_charging` This function enables charging by setting the CE pin to low logic state.
```c
void charger17_enable_charging ( charger17_t *ctx );
```

- `charger17_set_psel_2400mA` This function sets charging current to 2400mA by setting the PSEL pin to low logic state.
```c
void charger17_set_psel_2400mA ( charger17_t *ctx );
```

- `charger17_read_register` This function reads data from the selected register by using I2C serial interface.
```c
err_t charger17_read_register ( charger17_t *ctx, uint8_t reg, uint8_t *data_out );
```

## Example Description

> This example demonstrates the use of Charger 17 Click board by enabling battery charging and displaying the charging status.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration which enables charging.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger17_cfg_t charger17_cfg;  /**< Click config object. */

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
    charger17_cfg_setup( &charger17_cfg );
    CHARGER17_MAP_MIKROBUS( charger17_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == charger17_init( &charger17, &charger17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CHARGER17_ERROR == charger17_default_cfg ( &charger17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and displays the battery charging status (IC_STATUS and STAT0 regs) on the USB UART approximately once per second.

```c
void application_task ( void )
{
    uint8_t ic_status, status_0;
    if ( CHARGER17_OK == charger17_read_register ( &charger17, CHARGER17_REG_IC_STATUS, &ic_status ) )
    {
        charger17_parse_ic_status ( ic_status );
    }
    if ( CHARGER17_OK == charger17_read_register ( &charger17, CHARGER17_REG_STAT0, &status_0 ) )
    {
        charger17_parse_status_0 ( status_0 );
    }
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger17

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
