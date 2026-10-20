
---
# BI Hall 2 47BN Click

> [BI Hall 2 47BN Click](https://www.mikroe.com/?pid_product=MIKROE-7053) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7053&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2026.
- **Type**          : ADC type

# Software Support

## Example Description

> This example demonstrates the use of the BI Hall 2 47BN Click board for
magnetic field detection. The application reads the sensor output and
converts it to magnetic field strength expressed in Gauss units.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BIHall247BN

### Example Key Functions

- `bihall247bn_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void bihall247bn_cfg_setup ( bihall247bn_cfg_t *cfg );
```

- `bihall247bn_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t bihall247bn_init ( bihall247bn_t *ctx, bihall247bn_cfg_t *cfg );
```

- `bihall247bn_default_cfg` This function executes a default configuration of BI Hall 2 47BN Click board.
```c
err_t bihall247bn_default_cfg ( bihall247bn_t *ctx );
```

- `bihall247bn_get_output` This function reads the OUT pin voltage level and calculates magnetic field strength in Gauss.
```c
err_t bihall247bn_get_output ( bihall247bn_t *ctx, float *output );
```

### Application Init

> Initializes the logger and BI Hall 2 47BN Click driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    bihall247bn_cfg_t bihall247bn_cfg;  /**< Click config object. */

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
    bihall247bn_cfg_setup( &bihall247bn_cfg );
    BIHALL247BN_MAP_MIKROBUS( bihall247bn_cfg, MIKROBUS_POSITION_BIHALL247BN );
    if ( ADC_ERROR == bihall247bn_init( &bihall247bn, &bihall247bn_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the magnetic field measurement and logs the calculated magnetic field strength in Gauss.

```c
void application_task ( void )
{
    float mag_field = 0;
    if ( BIHALL247BN_OK == bihall247bn_get_output ( &bihall247bn, &mag_field ) ) 
    {
        log_printf( &logger, " Magnetic field : %.2f Gauss\r\n\n", mag_field );
    }
}
```

### Note

> Bring a magnet close to the sensor to observe positive and negative magnetic field changes.

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
