
---
# 2-Wire SPI ISO Click

> [2-Wire SPI ISO Click](https://www.mikroe.com/?pid_product=MIKROE-6778) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6778&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of a 2-Wire SPI ISO Click board by showing
the communication between the two Click boards (Slave and Master). That is performed by
sending commands to a 2-Wire SPI ISO Click (Slave) to read the device ID of a Accel 22
Click board connected to the 2-Wire SPI ISO Click (Master).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.2WireSPIISO

### Example Key Functions

- `c2wirespiiso_cfg_setup` Config Object Initialization function.
```c
void c2wirespiiso_cfg_setup ( c2wirespiiso_cfg_t *cfg );
```

- `c2wirespiiso_init` Initialization function.
```c
err_t c2wirespiiso_init ( c2wirespiiso_t *ctx, c2wirespiiso_cfg_t *cfg );
```

- `c2wirespiiso_default_cfg` Click Default Configuration function.
```c
void c2wirespiiso_default_cfg ( c2wirespiiso_t *ctx );
```

- `c2wirespiiso_write` This function writes a desired number of data bytes by using SPI serial interface.
```c
err_t c2wirespiiso_write ( c2wirespiiso_t *ctx, uint8_t *data_in, uint8_t in_len );
```

- `c2wirespiiso_read` This function reads a desired number of data bytes by using SPI serial interface.
```c
err_t c2wirespiiso_read ( c2wirespiiso_t *ctx, uint8_t *data_out, uint8_t out_len );
```

- `c2wirespiiso_get_bne_pin` This function returns the RX buffer not empty (BNE) pin logic state.
```c
uint8_t c2wirespiiso_get_bne_pin ( c2wirespiiso_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c2wirespiiso_cfg_t c2wirespiiso_cfg;  /**< Click config object. */

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
    c2wirespiiso_cfg_setup( &c2wirespiiso_cfg );
    C2WIRESPIISO_MAP_MIKROBUS( c2wirespiiso_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == c2wirespiiso_init( &c2wirespiiso, &c2wirespiiso_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    c2wirespiiso_default_cfg ( &c2wirespiiso );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and checks the device ID of a Accel 22 Click board connected to the 2-Wire SPI ISO
(Master) Click, and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    c2wirespiiso_get_accel22_id ( &c2wirespiiso );
    Delay_ms ( 1000 );
}
```

### Note

> The communication topology is as follows: 
- MCU <-> 2-Wire SPI ISO Click (Slave) <-> 2-Wire SPI ISO Click (Master) <-> Accel 22 Click

> The Master/Slave selection is done via on-board SMD jumpers.
> The Master Click board must be powered up with a 3V3 and 5V power supply externally.
> Also the DIS must be pulled down on Master Click board to enable the device.

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
