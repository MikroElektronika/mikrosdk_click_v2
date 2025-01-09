
---
# ECG 4 Click

> [ECG 4 Click](https://www.mikroe.com/?pid_product=MIKROE-3427) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3427&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from ECG 4 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ecg4

### Example Key Functions

- `ecg4_cfg_setup` Config Object Initialization function. 
```c
void ecg4_cfg_setup ( ecg4_cfg_t *cfg );
``` 
 
- `ecg4_init` Initialization function. 
```c
err_t ecg4_init ( ecg4_t *ctx, ecg4_cfg_t *cfg );
```

- `ecg4_module_reset` Reset module function. 
```c
void ecg4_module_reset ( ecg4_t *ctx );
```

- `ecg4_uart_isr` Function performs the uart interrupt routine, reads a data from uart rx buffer and makes a response from the BMD101 device. 
```c
void ecg4_uart_isr ( ecg4_t *ctx, uint8_t rx_dat );
```
 
- `ecg4_enable_ldo_ctrl` Function powers up or down control of LDO (Low Drop Out). 
```c
void ecg4_enable_ldo_ctrl ( ecg4_t *ctx, uint8_t state );
```

- `ecg4_generic_read` Generic read function. 
```c
int32_t ecg4_generic_read ( ecg4_t *ctx, char *data_buf, uint16_t max_len );
```

### Application Init

> Initializes the driver, sets the driver handler and enables the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ecg4_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ecg4_cfg_setup( &cfg );
    ECG4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ecg4_init( &ecg4, &cfg );

    ecg4.driver_hdl = make_response;
    Delay_ms ( 500 );

    ecg4_module_reset ( &ecg4 );
    ecg4_enable_ldo_ctrl ( &ecg4, ECG4_ENABLE_LDO_CTRL );

    Delay_ms ( 1000 );
}
```

### Application Task

> Reads the received data and parses it on the USB UART if the response buffer is ready.

```c
void application_task ( void )
{
    ecg4_process(  );
    if ( ecg4_responseReady( &ecg4 ) )
    {
        process_response( );
    }
}
```

### Note

> Use the Serial Plot application for data plotting.

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
