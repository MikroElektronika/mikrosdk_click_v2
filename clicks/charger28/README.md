
---
# Charger 28 Click

> [Charger 28 Click](https://www.mikroe.com/?pid_product=MIKROE-6519) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6519&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Charger 28 Click board by monitoring various parameters
of the charging system, such as input voltage (VBUS), battery voltage (VBAT), system voltage (VSYS),
charging current (IBAT), and chip temperature (TDIE). Additionally, it reads and interprets the
charger status and fault registers to provide detailed status and error feedback during operation.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger28

### Example Key Functions

- `charger28_cfg_setup` Config Object Initialization function.
```c
void charger28_cfg_setup ( charger28_cfg_t *cfg );
```

- `charger28_init` Initialization function.
```c
err_t charger28_init ( charger28_t *ctx, charger28_cfg_t *cfg );
```

- `charger28_default_cfg` Click Default Configuration function.
```c
err_t charger28_default_cfg ( charger28_t *ctx );
```

- `charger28_get_vbus` This function reads and calculates the bus voltage in millivolts.
```c
err_t charger28_get_vbus ( charger28_t *ctx, uint16_t *vbus );
```

- `charger28_get_ibus` This function reads and calculates the input current in milliamperes.
```c
err_t charger28_get_ibus ( charger28_t *ctx, float *ibus );
```

- `charger28_get_vbat` This function reads and calculates the battery voltage in millivolts.
```c
err_t charger28_get_vbat ( charger28_t *ctx, float *vbat );
```

### Application Init

> Initializes the driver and performs the default configuration of the Charger 28 Click by disabling
charging, resetting registers, disabling the TS pin, configuring the ADC, and re-enabling charging.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger28_cfg_t charger28_cfg;  /**< Click config object. */

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
    charger28_cfg_setup( &charger28_cfg );
    CHARGER28_MAP_MIKROBUS( charger28_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == charger28_init( &charger28, &charger28_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CHARGER28_ERROR == charger28_default_cfg ( &charger28 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Periodically retrieves and logs charging parameters such as input voltage, battery voltage,
system voltage, charging current, and temperature. The application also reads the status and 
fault registers to determine the current charging state and logs the information for debugging 
or monitoring purposes.

```c
void application_task ( void )
{
    float ibus = 0, vbat = 0, vsys = 0, adcin = 0, tdie = 0;
    uint8_t status_0 = 0, status_1 = 0, fault = 0;
    uint16_t vbus = 0, vpmid = 0;
    int16_t ibat = 0;

    if ( CHARGER28_OK == charger28_get_vbus ( &charger28, &vbus ) )
    {
        log_printf ( &logger, "\r\n VBUS: %u mV\r\n", vbus );
    }

    if ( CHARGER28_OK == charger28_get_ibus ( &charger28, &ibus ) )
    {
        log_printf ( &logger, " IBUS: %.1f mA\r\n", ibus );
    }

    if ( CHARGER28_OK == charger28_get_vbat ( &charger28, &vbat ) )
    {
        log_printf ( &logger, " VBAT: %.2f mV\r\n", vbat );
    }

    if ( CHARGER28_OK == charger28_get_ibat ( &charger28, &ibat ) )
    {
        log_printf ( &logger, " IBAT: %d mA\r\n", ibat );
    }

    if ( CHARGER28_OK == charger28_get_vsys ( &charger28, &vsys ) )
    {
        log_printf ( &logger, " VSYS: %.2f mV\r\n", vsys );
    }

    if ( CHARGER28_OK == charger28_get_vpmid ( &charger28, &vpmid ) )
    {
        log_printf ( &logger, " VPMID: %u mV\r\n", vpmid );
    }

    if ( CHARGER28_OK == charger28_get_adcin ( &charger28, &adcin ) )
    {
        log_printf ( &logger, " ADCIN: %.2f mV\r\n", adcin );
    }

    if ( CHARGER28_OK == charger28_get_tdie ( &charger28, &tdie ) )
    {
        log_printf ( &logger, " TDIE: %.1f degC\r\n", tdie );
    }

    if ( CHARGER28_OK == charger28_read_reg_byte ( &charger28, CHARGER28_REG_CHARGER_STATUS_0, &status_0 ) )
    {
        log_printf ( &logger, " Status 0: 0x%.2X\r\n", ( uint16_t ) status_0 );
    }
    
    if ( CHARGER28_OK == charger28_read_reg_byte ( &charger28, CHARGER28_REG_CHARGER_STATUS_1, &status_1 ) )
    {
        log_printf ( &logger, " Status 1: 0x%.2X\r\n", ( uint16_t ) status_1 );
        charger28_parse_charge_status ( status_1 );
    }

    if ( CHARGER28_OK == charger28_read_reg_byte ( &charger28, CHARGER28_REG_FAULT_STATUS, &fault ) )
    {
        log_printf ( &logger, " Fault: 0x%.2X\r\n", ( uint16_t ) fault );
    }

    Delay_ms ( 1000 );
}
```

### Note

> The application is designed to continuously monitor the charging system, providing real-time 
feedback on its operation. The detailed charge status parsing includes states such as "Not Charging", 
"Trickle Charge", "Fast Charge", and "Charge Done", among others, to help track the charging process.

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
