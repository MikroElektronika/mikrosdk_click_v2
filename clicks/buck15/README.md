
---
# Buck 15 Click

> [Buck 15 Click](https://www.mikroe.com/?pid_product=MIKROE-6044) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6044&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Buck 15 Click board by changing the output voltage.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck15

### Example Key Functions

- `buck15_cfg_setup` Config Object Initialization function.
```c
void buck15_cfg_setup ( buck15_cfg_t *cfg );
```

- `buck15_init` Initialization function.
```c
err_t buck15_init ( buck15_t *ctx, buck15_cfg_t *cfg );
```

- `buck15_default_cfg` Click Default Configuration function.
```c
err_t buck15_default_cfg ( buck15_t *ctx );
```

- `buck15_set_vout` This function sets the voltage output by using an I2C serial interface.
```c
err_t buck15_set_vout ( buck15_t *ctx, buck15_vout_t vout );
```

- `buck15_set_vset` This function sets the wiper position for the output voltage settings by using an I2C serial interface.
```c
err_t buck15_set_vset ( buck15_t *ctx, uint8_t vset_wp );
```

- `buck15_enable_device` This function enables the device by setting the EN pin to high logic state.
```c
void buck15_enable_device ( buck15_t *ctx );
```

### Application Init

> Initializes the driver and performs the device default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buck15_cfg_t buck15_cfg;  /**< Click config object. */

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
    buck15_cfg_setup( &buck15_cfg );
    BUCK15_MAP_MIKROBUS( buck15_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == buck15_init( &buck15, &buck15_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BUCK15_ERROR == buck15_default_cfg ( &buck15 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "____________\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application changes the output voltage and displays the currently set voltage output value.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    for ( buck15_vout_t vout = BUCK15_VOUT_0V6; vout <= BUCK15_VOUT_5V; vout++ )
    {
        if ( BUCK15_OK == buck15_set_vout( &buck15, vout ) )
        {
            log_printf( &logger, " Vout : %.1f [V]\r\n", vout_table[ vout ] );
            log_printf( &logger, "____________\r\n" );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
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
