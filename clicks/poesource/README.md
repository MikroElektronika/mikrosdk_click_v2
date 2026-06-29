
---
# PoE Source Click

> [PoE Source Click](https://www.mikroe.com/?pid_product=MIKROE-6958) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6958&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the PoE Source Click board for
Power over Ethernet (PoE) sourcing. The application reads detection
and classification results of the connected powered device (PD),
as well as voltage, current, and temperature measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PoESource

### Example Key Functions

- `poesource_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void poesource_cfg_setup ( poesource_cfg_t *cfg );
```

- `poesource_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t poesource_init ( poesource_t *ctx, poesource_cfg_t *cfg );
```

- `poesource_default_cfg` This function executes a default configuration of PoE Source Click board.
```c
err_t poesource_default_cfg ( poesource_t *ctx );
```

- `poesource_read_vin` This function reads and calculates the input voltage value.
```c
err_t poesource_read_vin ( poesource_t *ctx, float *voltage );
```

- `poesource_read_vout` This function reads and calculates the output voltage value.
```c
err_t poesource_read_vout ( poesource_t *ctx, float *voltage );
```

- `poesource_read_iout` This function reads and calculates the output current value in mA.
```c
err_t poesource_read_iout ( poesource_t *ctx, float *current );
```

### Application Init

> Initializes the logger and PoE Source Click driver, and applies the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    poesource_cfg_t poesource_cfg;  /**< Click config object. */

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
    poesource_cfg_setup( &poesource_cfg );
    POESOURCE_MAP_MIKROBUS( poesource_cfg, MIKROBUS_POSITION_POESOURCE );
    if ( I2C_MASTER_ERROR == poesource_init( &poesource, &poesource_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( POESOURCE_ERROR == poesource_default_cfg ( &poesource ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and parses detection/classification results, measures input
voltage, output voltage, output current, and die temperature, and
logs the results to the serial terminal.

```c
void application_task ( void )
{
    float vin = 0;
    float vout = 0;
    float iout = 0;
    float temperature = 0;
    uint8_t det_cls_res = 0;

    if ( POESOURCE_OK == poesource_read_reg ( &poesource, POESOURCE_REG_DET_CLS_RESULT, &det_cls_res ) )
    {
        poesource_parse_det_cls_result ( det_cls_res );
    }
    if ( POESOURCE_OK == poesource_read_vin ( &poesource, &vin ) )
    {
        log_printf ( &logger, " Vin: %.2f V\r\n", vin );
    }
    if ( POESOURCE_OK == poesource_read_vout ( &poesource, &vout ) )
    {
        log_printf ( &logger, " Vout: %.2f V\r\n", vout );
    }
    if ( POESOURCE_OK == poesource_read_iout ( &poesource, &iout ) )
    {
        log_printf ( &logger, " Iout: %.1f mA\r\n", iout );
    }
    if ( POESOURCE_OK == poesource_read_die_temp ( &poesource, &temperature ) )
    {
        log_printf ( &logger, " Die temperature: %.1f degC\r\n\n", temperature );
    }

    Delay_ms ( 1000 );
}
```

### Note

> Make sure to provide a stable 48V power supply to VIN connector.
The black RJ45 connector is for a data-only connection, and the inox one
has added power for PoE devices such as wireless access points (WAPs),
IP cameras and VoIP phones.

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
