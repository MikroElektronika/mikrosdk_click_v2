
---
# PMIC Click

> [PMIC Click](https://www.mikroe.com/?pid_product=MIKROE-6201) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6201&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of PMIC Click board by enabling battery charging and displaying the charging status.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PMIC

### Example Key Functions

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

### Application Init

> Initializes the driver and performs the Click default configuration which enables charging.

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

### Note

> A charged battery or a USB at VBUS must be connected to communicate with the Click board.

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
