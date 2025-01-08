
---
# CDC Click

> [CDC Click](https://www.mikroe.com/?pid_product=MIKROE-5985) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5985&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2023.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of CDC Click board by reading capacitance
measurements from C3/C2 and C5/C4 ports calculated from pure capacitance ratio
between those ports and port C1/C0 which is used as external C reference.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CDC

### Example Key Functions

- `cdc_cfg_setup` Config Object Initialization function.
```c
void cdc_cfg_setup ( cdc_cfg_t *cfg );
```

- `cdc_init` Initialization function.
```c
err_t cdc_init ( cdc_t *ctx, cdc_cfg_t *cfg );
```

- `cdc_default_cfg` Click Default Configuration function.
```c
err_t cdc_default_cfg ( cdc_t *ctx );
```

- `cdc_write_config` This function writes configuration data starting from the selected config address.
```c
err_t cdc_write_config ( cdc_t *ctx, uint8_t address, const uint8_t *data_in, uint8_t len );
```

- `cdc_send_opcode` This function sends a desired opcode command byte.
```c
err_t cdc_send_opcode ( cdc_t *ctx, uint8_t opcode );
```

- `cdc_read_results` This function reads all results and status registers.
```c
err_t cdc_read_results ( cdc_t *ctx, cdc_results_t *results );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    cdc_cfg_t cdc_cfg;  /**< Click config object. */

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
    cdc_cfg_setup( &cdc_cfg );
    CDC_MAP_MIKROBUS( cdc_cfg, MIKROBUS_1 );
    err_t init_flag = cdc_init( &cdc, &cdc_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CDC_ERROR == cdc_default_cfg ( &cdc ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Starts measurement and reads the results. The results data is displayed on the USB UART.

```c
void application_task ( void )
{
    cdc_results_t results;
    cdc_send_opcode ( &cdc, CDC_OPCODE_CDC_START );
    Delay_ms ( 200 );
    if ( CDC_OK == cdc_read_results ( &cdc, &results ) )
    {
        log_printf ( &logger, " C1/C0: %.1f pF\r\n", 
                     results.res_0 * CDC_REF - CDC_INT_CAP_PF );
        log_printf ( &logger, " C3/C2: %.1f pF\r\n", 
                     results.res_1 * CDC_REF - CDC_INT_CAP_PF );
        log_printf ( &logger, " C5/C4: %.1f pF\r\n\n", 
                     results.res_2 * CDC_REF - CDC_INT_CAP_PF );
        Delay_ms ( 1000 );
    }
}
```

### Note

> For better accuracy and higher measurement range, add 200pF external
capacitor between C1/C0 ports and set it below as CDC_EXT_CAP_C1_C0_PF macro
before running the application. This way you will be able to measure capacitance
in range from 1 to 2000pF.

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
