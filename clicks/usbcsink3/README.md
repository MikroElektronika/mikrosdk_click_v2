\mainpage Main Page

---
# USB-C Sink 3 click

> USB C Sink 3 Click is a compact add-on board with a standalone autonomous USB power delivery controller. 
> This board features the AP33771, a high-performance USB PD sink controller from Diodes Incorporated. 
> It supports dead battery mode to allow a system to be powered from an external source directly, 
> establishes a valid source-to-sink connection, and negotiates a USB power delivery (PD) 
> contract with a PD-capable source device. It also supports a flexible PD3.0 and 
> PPS for applications that require direct voltage and current requests, with fine-tuning capabilities.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/usbcsink3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/usb-c-sink-3-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jun 2023.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the USB-C Sink 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for USB-C Sink 3 Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This example demonstrates the use of USB-C Sink 3 Click board™ 
> by setting DC power requests and control for Type-C connector-equipped devices (TCD).

**The demo application is composed of two sections :**

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
    Delay_ms( 100 );
    
    if ( USBCSINK3_ERROR == usbcsink3_default_cfg ( &usbcsink3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ------------------------\r\n" );
    Delay_ms( 1000 );
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
        Delay_ms( 1000 );
        usbcsink3_get_vbus ( &usbcsink3, &voltage );
        log_printf( &logger, " VBUS : %.1f [V]\r\n", voltage );
        log_printf( &logger, " ------------------------\r\n" );
        Delay_ms( 5000 );
    }
    
    if ( ( USBCSINK3_OK == usbcsink3_set_voltage( &usbcsink3, USBCSINK3_VTG_SEL_9V ) ) &&
         ( USBCSINK3_OK == usbcsink3_set_power( &usbcsink3, USBCSINK3_PWR_SEL_18W ) ) )
    {
        log_printf( &logger, " Output:\r\nVoltage: 9.0 [V]\r\nPower: 18.0 [W]\r\n" );
        log_printf( &logger, " - - - - - -  - - - - - -\r\n" );
        Delay_ms( 1000 );
        usbcsink3_get_vbus ( &usbcsink3, &voltage );
        log_printf( &logger, " VBUS : %.1f [V]\r\n", voltage );
        log_printf( &logger, " ------------------------\r\n" );
        Delay_ms( 5000 );
    }
}
```

## Note

> FAULT LED flickering notified of the system status:
>  - Charging: Breathing light (2 sec dimming), 1 cycle is 4 sec.
>  - Fully charged: Continuously lit Charging current < 500mA.
>  - Mismatch: 1s flicker Voltage or power mismatch. Non-PD power source, 1 cycle is 2sec.
>  - Fault: 300ms flicker OVP, 1 cycle is 600ms.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.USBCSink3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
