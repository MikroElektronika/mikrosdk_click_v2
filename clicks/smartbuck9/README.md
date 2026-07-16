
---
# Smart Buck 9 Click

> [Smart Buck 9 Click](https://www.mikroe.com/?pid_product=MIKROE-6982) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6982&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Smart Buck 9 Click board for
output voltage control. The application periodically sets the output
voltage across the supported range and monitors the device status register
for fault conditions.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SmartBuck9

### Example Key Functions

- `smartbuck9_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void smartbuck9_cfg_setup ( smartbuck9_cfg_t *cfg );
```

- `smartbuck9_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t smartbuck9_init ( smartbuck9_t *ctx, smartbuck9_cfg_t *cfg );
```

- `smartbuck9_default_cfg` This function executes a default configuration of Smart Buck 9 Click board.
```c
err_t smartbuck9_default_cfg ( smartbuck9_t *ctx );
```

- `smartbuck9_set_vout` This function sets the VOUT output voltage.
```c
err_t smartbuck9_set_vout ( smartbuck9_t *ctx, uint16_t voltage_mv );
```

- `smartbuck9_get_pg_pin` This function returns the PG pin logic state.
```c
uint8_t smartbuck9_get_pg_pin ( smartbuck9_t *ctx );
```

- `smartbuck9_read_reg` This function reads a single byte of data from the selected register.
```c
err_t smartbuck9_read_reg ( smartbuck9_t *ctx, uint8_t reg, uint8_t *data_out );
```

### Application Init

> Initializes the logger and Smart Buck 9 Click driver, and applies the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartbuck9_cfg_t smartbuck9_cfg;  /**< Click config object. */

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
    smartbuck9_cfg_setup( &smartbuck9_cfg );
    SMARTBUCK9_MAP_MIKROBUS( smartbuck9_cfg, MIKROBUS_POSITION_SMARTBUCK9 );
    if ( I2C_MASTER_ERROR == smartbuck9_init( &smartbuck9, &smartbuck9_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SMARTBUCK9_ERROR == smartbuck9_default_cfg ( &smartbuck9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Steps the output voltage from minimum to maximum value, reads the status
register, and logs detected faults such as input overvoltage, output
overvoltage, overcurrent, thermal shutdown, and power-not-good state.

```c
void application_task ( void )
{
    static uint16_t voltage_mv = SMARTBUCK9_VOUT_MIN_MV;
    uint8_t status = 0;

    if ( SMARTBUCK9_OK == smartbuck9_set_vout ( &smartbuck9, voltage_mv ) )
    {
        log_printf( &logger, " Set voltage : %u mV\r\n", voltage_mv );

        if ( SMARTBUCK9_OK == smartbuck9_read_reg( &smartbuck9, SMARTBUCK9_REG_STATUS, &status ) )
        {
            if ( status & SMARTBUCK9_STATUS_TSHDN )
            {
                log_error( &logger, " Thermal shutdown, junction temperature over 150 degC" );
            }

            if ( status & SMARTBUCK9_STATUS_VI_OVP )
            {
                log_error( &logger, " Input voltage over 6.5V" );
            }

            if ( status & SMARTBUCK9_STATUS_VO_OVP )
            {
                log_error( &logger, " Output voltage over 110 percents of VOUT set" );
            }

            if ( status & SMARTBUCK9_STATUS_OCP )
            {
                log_error( &logger, " Overcurrent fault" );
            }
        }

        if ( !smartbuck9_get_pg_pin ( &smartbuck9 ) )
        {
            log_error( &logger, " Power not good" );
        }

        log_printf( &logger, "-----------------------------\r\n" );
    }

    voltage_mv += SMARTBUCK9_VOUT_STEP_MV;

    if ( voltage_mv > SMARTBUCK9_VOUT_MAX_MV )
    {
        voltage_mv = SMARTBUCK9_VOUT_MIN_MV;
    }

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
