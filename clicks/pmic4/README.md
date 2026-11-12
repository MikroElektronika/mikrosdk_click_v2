
---
# PMIC 4 Click

> [PMIC 4 Click](https://www.mikroe.com/?pid_product=MIKROE-7161) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7161&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of PMIC 4 Click board by monitoring
> storage voltage, charging paths, and relative load demand.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PMIC4

### Example Key Functions

- `pmic4_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void pmic4_cfg_setup ( pmic4_cfg_t *cfg );
```

- `pmic4_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t pmic4_init ( pmic4_t *ctx, pmic4_cfg_t *cfg );
```

- `pmic4_default_cfg` This function verifies the AEM13921 part number and selects the board's hardware configuration without programming charging thresholds.
```c
err_t pmic4_default_cfg ( pmic4_t *ctx );
```

- `pmic4_configure_apm` This function applies an I2C profile matching the default board settings and enables average power monitoring.
```c
err_t pmic4_configure_apm ( pmic4_t *ctx );
```

- `pmic4_get_currents` This function waits for a fresh APM window and reports storage voltage and transfer activity.
```c
err_t pmic4_get_currents ( pmic4_t *ctx, pmic4_current_cfg_t *cfg, pmic4_currents_t *currents );
```

- `pmic4_get_temperature` This function converts the latest onboard NTC measurement to degrees Celsius.
```c
err_t pmic4_get_temperature ( pmic4_t *ctx, float *temperature );
```

### Application Init

> Initializes the logger and I2C driver, verifies the AEM13921 part number,
> applies the default board APM profile, and displays the device revision.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pmic4_cfg_t pmic4_cfg;  /**< Click config object. */

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
    pmic4_cfg_setup( &pmic4_cfg );
    PMIC4_MAP_MIKROBUS( pmic4_cfg, MIKROBUS_POSITION_PMIC4 );
    if ( I2C_MASTER_ERROR == pmic4_init( &pmic4, &pmic4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    uint8_t revision;
    err_t error_flag;
    
    // Verify the module before applying the complete default board APM profile.
    error_flag = pmic4_default_cfg( &pmic4 );
    if ( PMIC4_OK != error_flag )
    {
        log_error( &logger, " Default configuration: %ld. Check source power and I2C EN.", error_flag );
        for ( ; ; );
    }

    error_flag = pmic4_configure_apm( &pmic4 );
    if ( PMIC4_OK != error_flag )
    {
        log_error( &logger, " APM configuration: %ld.", error_flag );
        for ( ; ; );
    }

    error_flag = pmic4_read_reg( &pmic4, PMIC4_REG_VERSION, &revision );
    if ( PMIC4_OK != error_flag )
    {
        log_error( &logger, " Device revision read: %ld.", error_flag );
        for ( ; ; );
    }

    log_printf( &logger, " AEM13921 revision: 0x%.2X\r\n", ( uint16_t ) revision );
    log_printf( &logger, " LOAD: 2.5 V | STO limits: 3.00 / 3.21 / 4.13 V\r\n" );
    log_printf( &logger, " Nominal 5 V CC current: %.0f mA (R10 = %.0f ohms; estimate only)\r\n",
                APP_CHARGER_NOMINAL_CURRENT_MA, APP_CHARGER_RESISTOR_OHM );
    log_printf( &logger, " LOAD APM is shown in millions of raw units, not mA.\r\n" );
    log_printf( &logger, " SRCx: disconnect mikroBUS 5 V; limit source current externally.\r\n" );
    log_printf( &logger, " NTC: set TH EN = 1; hardware updates about every 7.45 s.\r\n" );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Displays battery voltage, charging/discharging paths, relative load
> demand, onboard NTC temperature, and protection events.
> Optional calibrated currents are at STO.

```c
void application_task ( void ) 
{
    pmic4_status_t status;
    pmic4_currents_t currents;
    float ntc_temperature;
    uint16_t flags;
    err_t error_flag;
    err_t ntc_error;

    error_flag = pmic4_get_currents( &pmic4, &current_cfg, &currents );
    if ( PMIC4_OK == error_flag )
    {
        error_flag = pmic4_get_status( &pmic4, &status );
    }
    if ( PMIC4_OK == error_flag )
    {
        pmic4_log_measurements( &pmic4, &status, &currents );
        // Temperature is optional; an unavailable sample must not hide power data.
        ntc_error = pmic4_get_temperature( &pmic4, &ntc_temperature );
        if ( PMIC4_OK == ntc_error )
        {
            log_printf( &logger, "  NTC: %.1f C\r\n", ntc_temperature );
        }
        else if ( PMIC4_ERROR_SAMPLE == ntc_error )
        {
            log_printf( &logger, "  NTC: unavailable; allow first update and check TH EN = 1.\r\n" );
        }
        else
        {
            log_error( &logger, " NTC read error: %ld.", ntc_error );
        }
        if ( pmic4_get_int_pin( &pmic4 ) )
        {
            error_flag = pmic4_get_interrupt_flags( &pmic4, &flags );
        }
    }
    if ( PMIC4_OK != error_flag )
    {
        log_error( &logger, " Communication error: %ld.", error_flag );
    }

    Delay_ms( APP_TASK_INTERVAL_MS );
}
```

### Note

> Set I2C EN = 1 and TH EN = 1. Match VCC SEL to the host logic voltage.
> Cold-start from SRC1, SRC2, or 5V_IN. MikroBUS 5 V disables harvesting.
> Limit source current externally and use a battery rated for the 3.00/3.21/4.13 V profile.
> LOAD is set to 2.5 V. A low on mikroBUS AN indicates LOAD is ready.

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
