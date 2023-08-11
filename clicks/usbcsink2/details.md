
---
# USB-C Sink 2 click

> USB-C Sink 2 Click is a compact add-on board with a standalone autonomous USB power delivery controller. 
> This board features the AP33772, a high-performance USB PD sink controller from Diodes Incorporated. 
> It supports dead battery mode to allow a system to be powered from an external source directly, 
> establishes a valid source-to-sink connection, and negotiates a USB power delivery (PD) contract 
> with a PD-capable source device. It also supports a flexible PD3.0 and PPS for applications 
> that require direct voltage and current requests, with fine-tuning capabilities.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/usbcsink2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/usb-c-sink-2-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jun 2023.
- **Type**          : ADC/I2C type


# Software Support

We provide a library for the USB-C Sink 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for USB-C Sink 2 Click driver.

#### Standard key functions :

- `usbcsink2_cfg_setup` Config Object Initialization function.
```c
void usbcsink2_cfg_setup ( usbcsink2_cfg_t *cfg );
```

- `usbcsink2_init` Initialization function.
```c
err_t usbcsink2_init ( usbcsink2_t *ctx, usbcsink2_cfg_t *cfg );
```

- `usbcsink2_default_cfg` Click Default Configuration function.
```c
err_t usbcsink2_default_cfg ( usbcsink2_t *ctx );
```

#### Example key functions :

- `usbcsink2_write_rdo` USB-C Sink 2 write the RDO function.
```c
err_t usbcsink2_write_rdo ( usbcsink2_t *ctx, uint8_t *rdo );
```

- `usbcsink2_get_pdo_voltage` USB-C Sink 2 get the voltage function.
```c
err_t usbcsink2_get_pdo_voltage ( usbcsink2_t *ctx, float *voltage_mv );
```

- `usbcsink2_get_pdo_current` USB-C Sink 2 get the current function.
```c
err_t usbcsink2_get_pdo_current ( usbcsink2_t *ctx, float *current_ma );
```

## Example Description

> This example demonstrates the use of the USB-C Sink 2 Click board™ 
> by setting DC power requests and control for Type-C connector-equipped devices (TCD).

**The demo application is composed of two sections :**

### Application Init

> Initializes I2C and ADC modules and log UART.
> After driver initialization the app set default settings.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbcsink2_cfg_t usbcsink2_cfg;  /**< Click config object. */

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
    usbcsink2_cfg_setup( &usbcsink2_cfg );
    USBCSINK2_MAP_MIKROBUS( usbcsink2_cfg, MIKROBUS_1 );
    err_t init_flag = usbcsink2_init( &usbcsink2, &usbcsink2_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( USBCSINK2_ERROR == usbcsink2_default_cfg ( &usbcsink2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms( 100 );
}
```

### Application Task

> In this example, the app configures Power Data Objects (PDO) 
> highest priority profile and requests power from a standard USB PD source adapter.
> After connecting the PD source and USB-C Sink 2 Click with the Type-C cable,
> the app gets the total number of valid PDO's 
> and switches all PDO configurations every 10 seconds.
> When the PD source accepts the request, the app displays information about 
> VOUT Voltage [mV] and Current [mA] and the temperature [degree Celsius] of the USB-C connector.

```c
void application_task ( void ) 
{
    static float voltage_mv = 0, current_ma = 0;
    static uint8_t temperature = 0;
    for ( uint8_t pdo_num = 0; pdo_num < usbcsink2.number_of_valid_pdo; pdo_num++ )
    {
        usbcsink2.pdo_data[ pdo_num * 4 + 3 ] = ( pdo_num + 1 ) << 4;
        if ( USBCSINK2_OK == usbcsink2_write_rdo( &usbcsink2, &usbcsink2.pdo_data[ pdo_num * 4 ] ) )
        {
            log_printf( &logger, " --- PDO[ %d ] ---\r\n", ( uint16_t ) pdo_num );
        }
        
        if ( USBCSINK2_OK == usbcsink2_wait_rdo_req_success( &usbcsink2 ) )
        {
            if ( USBCSINK2_OK == usbcsink2_get_pdo_voltage( &usbcsink2, &voltage_mv ) )
            {
                log_printf( &logger, " Voltage : %.2f mV\r\n", voltage_mv );
            }
            
            if ( USBCSINK2_OK == usbcsink2_get_pdo_current( &usbcsink2, &current_ma ) )
            {
                log_printf( &logger, " Current : %.2f mA\r\n", current_ma );
            }
            
            if ( USBCSINK2_OK == usbcsink2_get_temperature( &usbcsink2, &temperature ) )
            {
                log_printf( &logger, " Temperature : %d C\r\n", ( uint16_t ) temperature );
            }
            log_printf( &logger, "---------------------------\r\n" );
            Delay_ms( 10000 );
        }
    }
}
```
## Note

> FAULT LED flickering notified of the system status:
>   - Charging: Breathing light (2 sec dimming), 1 cycle is 4 sec.
>   - Fully charged: Continuously lit Charging current < 500mA.
>   - Mismatch: 1s flicker Voltage or power mismatch. Non-PD power source, 1 cycle is 2sec.
>   - Fault: 300ms flicker OVP, 1 cycle is 600ms.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.USBCSink2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
