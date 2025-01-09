
---
# Buck 23 Click

> [Buck 23 Click](https://www.mikroe.com/?pid_product=MIKROE-5536) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5536&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Buck 23 Click by changing the output voltage.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck23

### Example Key Functions

- `buck23_cfg_setup` Config Object Initialization function.
```c
void buck23_cfg_setup ( buck23_cfg_t *cfg );
```

- `buck23_init` Initialization function.
```c
err_t buck23_init ( buck23_t *ctx, buck23_cfg_t *cfg );
```

- `buck23_default_cfg` Click Default Configuration function.
```c
err_t buck23_default_cfg ( buck23_t *ctx );
```

- `buck23_set_vstep` This function sets the voltage output step to 10mV or 12.5mV.
```c
err_t buck23_set_vstep ( buck23_t *ctx, uint8_t vstep );
```

- `buck23_set_vout` This function sets the voltage output.
```c
err_t buck23_set_vout ( buck23_t *ctx, uint16_t vout_mv );
```

- `buck23_get_pg_pin` This function returns the PG (power good) pin logic state.
```c
uint8_t buck23_get_pg_pin ( buck23_t *ctx );
```

### Application Init

> Initializes the driver and performs the device default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buck23_cfg_t buck23_cfg;  /**< Click config object. */

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
    buck23_cfg_setup( &buck23_cfg );
    BUCK23_MAP_MIKROBUS( buck23_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == buck23_init( &buck23, &buck23_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BUCK23_ERROR == buck23_default_cfg ( &buck23 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes the output voltage once per second and displays on the USB UART the currently set
voltage output value as well as its range and resolution. It also checks and displays the status
register content and the power good pin indication.

```c
void application_task ( void )
{
    uint16_t vout_mv;
    uint8_t status;
    if ( BUCK23_OK == buck23_set_vstep ( &buck23, BUCK23_VSTEP_10 ) )
    {
        log_printf ( &logger, " ------------------------------------\r\n" );
        log_printf ( &logger, " VOUT resolution: 10mV\r\n VOUT range: 500mV to 1270mV\r\n" );
        log_printf ( &logger, " ------------------------------------" );
    }
    for ( vout_mv = BUCK23_VOUT_MIN_VSTEP_10; vout_mv <= BUCK23_VOUT_MAX_VSTEP_10; vout_mv += 50 )
    {
        if ( BUCK23_OK == buck23_read_register ( &buck23, BUCK23_REG_STATUS, &status ) )
        {
            log_printf ( &logger, "\r\n STATUS: 0x%.2X\r\n", ( uint16_t ) status );
        }
        if ( BUCK23_OK == buck23_set_vout ( &buck23, vout_mv ) )
        {
            log_printf ( &logger, " VOUT: %u mV\r\n", vout_mv );
        }
        if ( !buck23_get_pg_pin ( &buck23 ) )
        {
            log_printf ( &logger, " ERROR: No power good\r\n" );
            log_printf ( &logger, " Restarting device\r\n" );
            buck23_restart_device ( &buck23 );
            vout_mv -= 50;
        }
        Delay_ms ( 1000 );
    }
    if ( BUCK23_OK == buck23_set_vstep ( &buck23, BUCK23_VSTEP_12_5 ) )
    {
        log_printf ( &logger, " ------------------------------------\r\n" );
        log_printf ( &logger, " VOUT resolution: 12.5mV\r\n VOUT range: 625mV to 1587.5mV\r\n" );
        log_printf ( &logger, " ------------------------------------" );
    }
    for ( vout_mv = BUCK23_VOUT_MIN_VSTEP_12_5; vout_mv <= BUCK23_VOUT_MAX_VSTEP_12_5; vout_mv += 50 )
    {
        if ( BUCK23_OK == buck23_read_register ( &buck23, BUCK23_REG_STATUS, &status ) )
        {
            log_printf ( &logger, "\r\n STATUS: 0x%.2X\r\n", ( uint16_t ) status );
        }
        if ( BUCK23_OK == buck23_set_vout ( &buck23, vout_mv ) )
        {
            log_printf ( &logger, " VOUT: %u mV\r\n", vout_mv );
        }
        if ( !buck23_get_pg_pin ( &buck23 ) )
        {
            log_printf ( &logger, " ERROR: No power good\r\n" );
            log_printf ( &logger, " Restarting device\r\n" );
            buck23_restart_device ( &buck23 );
            vout_mv -= 50;
        }
        Delay_ms ( 1000 );
    }
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
