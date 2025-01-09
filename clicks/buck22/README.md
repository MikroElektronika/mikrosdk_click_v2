
---
# Buck 22 Click

> [Buck 22 Click](https://www.mikroe.com/?pid_product=MIKROE-5446) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5446&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Buck 22 Click by changing the output voltage.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck22

### Example Key Functions

- `buck22_cfg_setup` Config Object Initialization function.
```c
void buck22_cfg_setup ( buck22_cfg_t *cfg );
```

- `buck22_init` Initialization function.
```c
err_t buck22_init ( buck22_t *ctx, buck22_cfg_t *cfg );
```

- `buck22_set_vout` This function sets the output voltage by using I2C serial interface.
```c
err_t buck22_set_vout ( buck22_t *ctx, uint16_t vout_mv );
```

- `buck22_read_vout` This function reads the output voltage by using I2C serial interface.
```c
err_t buck22_read_vout ( buck22_t *ctx, uint16_t *vout_mv );
```

- `buck22_get_pg_pin` This function returns the power good (PG) pin logic state.
```c
uint8_t buck22_get_pg_pin ( buck22_t *ctx );
```

### Application Init

> Initializes the driver and sets the control settings.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buck22_cfg_t buck22_cfg;  /**< Click config object. */

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
    buck22_cfg_setup( &buck22_cfg );
    BUCK22_MAP_MIKROBUS( buck22_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == buck22_init( &buck22, &buck22_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BUCK22_ERROR == buck22_set_control ( &buck22, BUCK22_CONTROL_DEFAULT_SETTING ) )
    {
        log_error( &logger, " Set control." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes the output voltage every 3 seconds and displays on the USB UART the currently set voltage output value. It also checks the power good pin indicator.

```c
void application_task ( void )
{
    if ( !buck22_get_pg_pin ( &buck22 ) )
    {
        log_info ( &logger, " Device is shut down. " );
        while ( !buck22_get_pg_pin ( &buck22 ) );
        log_info ( &logger, " Device is powered up. " );
    }
    static uint16_t vout_mv = BUCK22_VOUT_MIN;
    if ( BUCK22_OK == buck22_set_vout ( &buck22, vout_mv ) )
    {
        if ( BUCK22_OK == buck22_read_vout ( &buck22, &vout_mv ) )
        {
            log_printf ( &logger, " Vout: %u mV\r\n", vout_mv );
        }
    }
    vout_mv += 100;
    if ( vout_mv > BUCK22_VOUT_MAX )
    {
        vout_mv = BUCK22_VOUT_MIN;
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
