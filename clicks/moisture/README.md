
---
# Moisture Click

> [Moisture Click](https://www.mikroe.com/?pid_product=MIKROE-3084) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3084&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jovan Stajkovic
- **Date**          : nov 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> The demo application displays relative moisture measurement using Moisture Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Moisture

### Example Key Functions

- `moisture_cfg_setup` Config Object Initialization function. 
```c
void moisture_cfg_setup ( moisture_cfg_t *cfg );
``` 
 
- `moisture_init` Initialization function. 
```c
err_t moisture_init ( moisture_t *ctx, moisture_cfg_t *cfg );
```

- `moisture_default_cfg` Click Default Configuration function. 
```c
void moisture_default_cfg ( moisture_t *ctx );
```

- `moisture_get_data` Measurement data function. 
```c
uint8_t moisture_get_data ( moisture_t *ctx );
```
 
- `moisture_cfg` Configure device function. 
```c
void  moisture_cfg ( moisture_t *ctx, uint16_t gain, uint16_t offset, uint16_t clk_div );
```

- `moisture_soft_reset` Soft reset function. 
```c
void moisture_soft_reset ( moisture_t *ctx );
```

### Application Init

> Initializes Driver and sets moisture gain, offset data and clock divider
> and performs calibration of the device. We advise you not to touch,
> or expose sensor to moisture during the calibration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    moisture_cfg_t cfg;

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

    moisture_cfg_setup( &cfg );
    MOISTURE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    moisture_init( &moisture, &cfg );
    Delay_ms ( 100 );

    data_res = moisture_read_word( &moisture, MOISTURE_REG_DEVICE_ID );

    if ( ( data_res != MOISTURE_FDC2112_ID ) && ( data_res != MOISTURE_FDC2212_ID ) )
    {
        log_printf( &logger, "---- Comunication ERROR!!! ---- \r\n" );
        for ( ; ; );
    }
    else
    {
        log_printf( &logger, "---- Comunication OK!!! ---- \r\n" );
    }

    moisture_soft_reset( &moisture );
    moisture_default_cfg( &moisture );

    log_printf( &logger, " --- Calibration start --- \r\n" );
    moisture_cal( &moisture );
    Delay_ms ( 1000 );

    log_printf( &logger, " --- Calibration finishing --- \r\n" );
}
```

### Application Task

> The device measure moisture and displays data in percentage every 500ms.

```c
void application_task ( void )
{
    moisture_data = moisture_get_data( &moisture  );
    log_printf( &logger, " Moisture data : %d \r\n", moisture_data );
    Delay_ms ( 500 );
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
