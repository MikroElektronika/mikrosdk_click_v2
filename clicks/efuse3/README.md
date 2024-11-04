\mainpage Main Page

---
# e Fuse 3 Click

eFuse 3 Click is a compact add-on board that contains an electronic eFuse. This board features the NIS6150, a resettable fuse that can significantly enhance the reliability of a USB application from both catastrophic and shutdown failures from ON Semiconductor. It is designed to buffer the load device from the excessive input voltage, which can damage sensitive circuits and protect the input side from reverse currents. It includes an over-voltage clamp circuit that limits the output voltage during transients but doesn’t shut the unit down, allowing the load circuit to continue its operation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/efuse3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/efuse-3-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the eFuse3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for eFuse3 Click driver.

#### Standard key functions :

- `efuse3_cfg_setup` Config Object Initialization function.
```c
void efuse3_cfg_setup ( efuse3_cfg_t *cfg );
```

- `efuse3_init` Initialization function.
```c
EFUSE3_RETVAL efuse3_init ( efuse3_t *ctx, efuse3_cfg_t *cfg );
```

- `efuse3_default_cfg` Click Default Configuration function.
```c
void efuse3_default_cfg ( efuse3_t *ctx );
```

#### Example key functions :

- `efuse3_get_current` e Fuse 3 get current function.
```c
err_t efuse3_get_current ( efuse3_t *ctx, float *current );
```

- `efuse3_get_flag` e Fuse 3 get flag function.
```c
uint8_t efuse3_get_flag ( efuse3_t *ctx );
```

- `efuse3_reset` e Fuse 3 reset function.
```c
void efuse3_reset ( efuse3_t *ctx );
```

## Example Description

> This library contains API for the eFuse 3 Click driver.
> The library contains drivers to enable/disable the device, 
> for reading ADC voltage, overflow status, output and current value [ A ].

**The demo application is composed of two sections :**

### Application Init

> Initializes SPI driver and set default configuration.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;        /**< Logger config object. */
    efuse3_cfg_t efuse3_cfg;  /**< Click config object. */

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

    efuse3_cfg_setup( &efuse3_cfg );
    EFUSE3_MAP_MIKROBUS( efuse3_cfg, MIKROBUS_1 );
    err_t init_flag  = efuse3_init( &efuse3, &efuse3_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    efuse3_default_cfg ( &efuse3 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 100 );
}

```

### Application Task

> This is an example that demonstrates the use of the eFuse 3 Click board. 
> Read and display device status information and current value [ A ].
> The eFuse 3 includes an overvoltage clamp the circuit that limits the output voltage
> during transients but does not shut the unit down, 
> thereby allowing the load circuit to continue its operation.
> The Electronic Fuse is to limit current and current limit 
> Current limit ( 0.1 A - 1.8 A ) depends on the choice of resistor wired 
> on the Rlimit ( 1 Ohm - 15 Ohm ) connector.
> For example, for Rlimit resistance of 1 Ohm, current limit is 1 A 
> ( 3.5 Ohm - 0.5 A, 7 Ohm - 0.25 A ). 
> Read details from the ON Semiconductor NIS6150 datasheets.   
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) {
    log_printf( &logger, " Status  :" );    
    
    if ( efuse3_get_flag( &efuse3 ) == EFUSE3_FLAG_NORMAL_OPERATION ) {
        log_printf( &logger, " Normal operation \r\n" );
    } else {
        log_printf( &logger, " Device OFF \r\n" );

        if ( overflow_status == EFUSE3_OVERFLOW_HIGH ) {
            log_printf( &logger, " Overflow high in the analog input voltage.\r\n" );    
        } else if ( overflow_status == EFUSE3_OVERFLOW_LOW ) {
            log_printf( &logger, " Overflow low in the analog input voltage.\r\n" ); 
        }
        
        efuse3_reset( &efuse3 );
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, "- - - - - - - - - - - - - - \r\n" );
    efuse3_get_current( &efuse3, &current );
    log_printf( &logger, " Current : %.5f A\r\n", current );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.eFuse3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](https:///shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](https:///shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
