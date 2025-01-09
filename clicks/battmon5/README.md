
---
# BATT-MON 5 Click

> [BATT-MON 5 Click](https://www.mikroe.com/?pid_product=MIKROE-6448) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6448&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of BATT-MON 5 Click board by reading the battery cell voltage and the relative state of charge (RSOC).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BATTMON5

### Example Key Functions

- `battmon5_cfg_setup` Config Object Initialization function.
```c
void battmon5_cfg_setup ( battmon5_cfg_t *cfg );
```

- `battmon5_init` Initialization function.
```c
err_t battmon5_init ( battmon5_t *ctx, battmon5_cfg_t *cfg );
```

- `battmon5_default_cfg` Click Default Configuration function.
```c
err_t battmon5_default_cfg ( battmon5_t *ctx );
```

- `battmon5_write_reg` This function writes a data word starting to the selected register by using I2C serial interface.
```c
err_t battmon5_write_reg ( battmon5_t *ctx, uint8_t reg, uint16_t data_in )
```

- `battmon5_read_reg` This function reads a data word from the selected register by using I2C serial interface.
```c
err_t battmon5_read_reg ( battmon5_t *ctx, uint8_t reg, uint16_t *data_out );
```

- `battmon5_get_alarm_pin` This function returns the ALARM pin logic state.
```c
uint8_t battmon5_get_alarm_pin ( battmon5_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    battmon5_cfg_t battmon5_cfg;  /**< Click config object. */

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
    battmon5_cfg_setup( &battmon5_cfg );
    BATTMON5_MAP_MIKROBUS( battmon5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == battmon5_init( &battmon5, &battmon5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BATTMON5_ERROR == battmon5_default_cfg ( &battmon5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the battery cell voltage and the relative state of charge (RSOC) and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    uint16_t voltage = 0;
    uint16_t rsoc = 0;
    if ( BATTMON5_OK == battmon5_read_reg ( &battmon5, BATTMON5_REG_CELL_V, &voltage ) )
    {
        log_printf ( &logger, " Voltage: %u mV\r\n", voltage ); // Battery Cell Voltage
    }
    if ( BATTMON5_OK == battmon5_read_reg ( &battmon5, BATTMON5_REG_RSOC, &rsoc ) )
    {
        log_printf ( &logger, " RSOC: %u %%\r\n\n", rsoc ); // Relative State Of Charge
    }
    Delay_ms ( 1000 );
}
```

### Note

> For the communication with the Click board to work, the battery needs to be connected.
The Click board is configured by default for a 2000 mAh battery pack capacity.

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
