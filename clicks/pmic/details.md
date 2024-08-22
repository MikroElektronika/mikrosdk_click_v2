
---
# PMIC click

> PMIC Click is a compact add-on board for efficient power management in rechargeable applications. This board features the nPM1300, an advanced Power Management Integrated Circuit (PMIC) from Nordic Semiconductor, offering integrated battery charging and advanced system power management features. The board includes an 800mA JEITA-compliant linear battery charger, two 200mA buck regulators, and configurable load switches, all housed in a compact QFN32 package.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pmic_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pmic-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the PMIC Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for PMIC Click driver.

#### Standard key functions :

- `pmic_cfg_setup` Config Object Initialization function.
```c
void pmic_cfg_setup ( pmic_cfg_t *cfg );
```

- `pmic_init` Initialization function.
```c
err_t pmic_init ( pmic_t *ctx, pmic_cfg_t *cfg );
```

- `pmic_default_cfg` Click Default Configuration function.
```c
err_t pmic_default_cfg ( pmic_t *ctx );
```

#### Example key functions :

- `pmic_get_vbat` This function reads the VBAT measurement results in millivolts.
```c
err_t pmic_get_vbat ( pmic_t *ctx, uint16_t *vbat );
```

- `pmic_get_vbus` This function reads the VBUS measurement results in millivolts.
```c
err_t pmic_get_vbus ( pmic_t *ctx, uint16_t *vbus );
```

- `pmic_get_vsys` This function reads the VSYS measurement results in millivolts.
```c
err_t pmic_get_vsys ( pmic_t *ctx, uint16_t *vsys );
```

## Example Description

> This example demonstrates the use of PMIC click board by enabling battery charging and displaying the charging status.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration which enables charging.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pmic_cfg_t pmic_cfg;  /**< Click config object. */

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
    pmic_cfg_setup( &pmic_cfg );
    PMIC_MAP_MIKROBUS( pmic_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == pmic_init( &pmic, &pmic_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PMIC_ERROR == pmic_default_cfg ( &pmic ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and displays the VBAT, VBUS, and VSYS voltage and the battery charging status on the USB UART approximately once per second.

```c
void application_task ( void )
{
    uint16_t vbat = 0, vbus = 0, vsys = 0;
    if ( PMIC_OK == pmic_get_vbat ( &pmic, &vbat ) )
    {
        log_printf( &logger, " VBAT : %u mV\r\n", vbat );
    }
    if ( PMIC_OK == pmic_get_vbus ( &pmic, &vbus ) )
    {
        log_printf( &logger, " VBUS : %u mV\r\n", vbus );
    }
    if ( PMIC_OK == pmic_get_vsys ( &pmic, &vsys ) )
    {
        log_printf( &logger, " VSYS : %u mV\r\n\n", vsys );
    }
    pmic_display_charger_status ( &pmic );
    Delay_ms ( 1000 );
}
```

## Note

> A charged battery or a USB at VBUS must be connected to communicate with the click board.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.PMIC

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
