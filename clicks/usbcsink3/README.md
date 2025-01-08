
---
# USB-C Sink 3 Click

> [USB-C Sink 3 Click](https://www.mikroe.com/?pid_product=MIKROE-5791) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5791&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jun 2023.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of USB-C Sink 3 Click board&trade; 
> by setting DC power requests and control for Type-C connector-equipped devices (TCD).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.USBCSink3

### Example Key Functions

- `usbcsink3_cfg_setup` Config Object Initialization function.
```c
void usbcsink3_cfg_setup ( usbcsink3_cfg_t *cfg );
```

- `usbcsink3_init` Initialization function.
```c
err_t usbcsink3_init ( usbcsink3_t *ctx, usbcsink3_cfg_t *cfg );
```

- `usbcsink3_default_cfg` Click Default Configuration function.
```c
err_t usbcsink3_default_cfg ( usbcsink3_t *ctx );
```

- `usbcsink3_set_voltage` USB-C Sink 3 set the voltage function.
```c
err_t usbcsink3_set_voltage ( usbcsink3_t *ctx, usbcsink3_vtg_sel_t voltage );
```

- `usbcsink3_set_power` USB-C Sink 3 set the power function.
```c
err_t usbcsink3_set_power ( usbcsink3_t *ctx, usbcsink3_pwr_sel_t power );
```

- `usbcsink3_get_vbus` USB-C Sink 3 get VBUS function.
```c
err_t usbcsink3_get_vbus ( usbcsink3_t *ctx, float *vbus );
```

### Application Init

> Initializes SPI, I2C and ADC modules and log UART.
> After driver initialization the app set default settings:
> Voltage Selection: 5 [V] and Power: 15.0 [W].

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbcsink3_cfg_t usbcsink3_cfg;  /**< Click config object. */

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
    usbcsink3_cfg_setup( &usbcsink3_cfg );
    USBCSINK3_MAP_MIKROBUS( usbcsink3_cfg, MIKROBUS_1 );
    err_t init_flag = usbcsink3_init( &usbcsink3, &usbcsink3_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    if ( USBCSINK3_ERROR == usbcsink3_default_cfg ( &usbcsink3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ------------------------\r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

> In this example, the app configures Power Data Objects (PDO) 
> highest priority profile and requests power from a standard USB PD source adapter.
> It interprets power input requirements (voltage/current and maximum power) from the TCD.
> The example uses two configurations: 
> - Voltage 5 [V] and Power 15.0 [W]
> - Voltage 9 [V] and Power 18.0 [W]
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void )
{
    static float voltage = 0.0;
    if ( ( USBCSINK3_OK == usbcsink3_set_voltage( &usbcsink3, USBCSINK3_VTG_SEL_5V ) ) &&
         ( USBCSINK3_OK == usbcsink3_set_power( &usbcsink3, USBCSINK3_PWR_SEL_15W ) ) )
    {
        log_printf( &logger, " Output:\r\nVoltage: 5.0 [V]\r\nPower: 15.0 [W]\r\n" );
        log_printf( &logger, " - - - - - -  - - - - - -\r\n" );
        Delay_ms ( 1000 );
        usbcsink3_get_vbus ( &usbcsink3, &voltage );
        log_printf( &logger, " VBUS : %.1f [V]\r\n", voltage );
        log_printf( &logger, " ------------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    
    if ( ( USBCSINK3_OK == usbcsink3_set_voltage( &usbcsink3, USBCSINK3_VTG_SEL_9V ) ) &&
         ( USBCSINK3_OK == usbcsink3_set_power( &usbcsink3, USBCSINK3_PWR_SEL_18W ) ) )
    {
        log_printf( &logger, " Output:\r\nVoltage: 9.0 [V]\r\nPower: 18.0 [W]\r\n" );
        log_printf( &logger, " - - - - - -  - - - - - -\r\n" );
        Delay_ms ( 1000 );
        usbcsink3_get_vbus ( &usbcsink3, &voltage );
        log_printf( &logger, " VBUS : %.1f [V]\r\n", voltage );
        log_printf( &logger, " ------------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
}
```

### Note

> FAULT LED flickering notified of the system status:
>  - Charging: Breathing light (2 sec dimming), 1 cycle is 4 sec.
>  - Fully charged: Continuously lit Charging current < 500mA.
>  - Mismatch: 1s flicker Voltage or power mismatch. Non-PD power source, 1 cycle is 2sec.
>  - Fault: 300ms flicker OVP, 1 cycle is 600ms.

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
