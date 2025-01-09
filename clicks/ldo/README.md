
---
# LDO Click

> [LDO Click](https://www.mikroe.com/?pid_product=MIKROE-5645) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5645&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of LDO Click by changing the output voltage.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LDO

### Example Key Functions

- `ldo_cfg_setup` Config Object Initialization function.
```c
void ldo_cfg_setup ( ldo_cfg_t *cfg );
```

- `ldo_init` Initialization function.
```c
err_t ldo_init ( ldo_t *ctx, ldo_cfg_t *cfg );
```

- `ldo_default_cfg` Click Default Configuration function.
```c
err_t ldo_default_cfg ( ldo_t *ctx );
```

- `ldo_enable_device` This function enables the device by setting the EN pin to HIGH logic state.
```c
void ldo_enable_device ( ldo_t *ctx );
```

- `ldo_disable_device` This function disables the device by setting the EN pin to LOW logic state.
```c
void ldo_disable_device ( ldo_t *ctx );
```

- `ldo_set_vout` This function sets the voltage output.
```c
err_t ldo_set_vout ( ldo_t *ctx, uint16_t vout );
```

### Application Init

> Initializes the driver and performs the device default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ldo_cfg_t ldo_cfg;  /**< Click config object. */

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
    ldo_cfg_setup( &ldo_cfg );
    LDO_MAP_MIKROBUS( ldo_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ldo_init( &ldo, &ldo_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LDO_ERROR == ldo_default_cfg ( &ldo ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes the output voltage every 3 seconds and displays on the USB UART the currently set voltage output value.

```c
void application_task ( void )
{
    static uint16_t vout = LDO_VOUT_MIN;
    if ( LDO_OK == ldo_set_vout ( &ldo, vout ) )
    {
        log_printf ( &logger, " VOUT: %u mV\r\n\n", vout );
    }
    vout += LDO_VOUT_STEP;
    if ( vout > LDO_VOUT_MAX )
    {
        vout = LDO_VOUT_MIN;
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> In order to have up to 3950mV at VOUT you will need to move the VIN SEL on-board jumper
to the VEXT position and provide at least 3950mV voltage input at the VEXT terminal.
Otherwise, the maximum level of VOUT will be limited to 3.3V system voltage.

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
