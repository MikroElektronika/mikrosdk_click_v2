\mainpage Main Page

---
# EMG click

> EMG click measures the electrical activity produced by the skeletal muscles. It carries MCP609 operational amplifier and MAX6106 micropower voltage reference.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/emg_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/emg-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : ADC type


# Software Support

We provide a library for the EMG Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for EMG Click driver.

#### Standard key functions :

- `emg_cfg_setup` Config Object Initialization function.
```c
void emg_cfg_setup ( emg_cfg_t *cfg );
```

- `emg_init` Initialization function.
```c
err_t emg_init ( emg_t *ctx, emg_cfg_t *cfg );
```

#### Example key functions :

- `emg_read_an_pin_value` EMG read AN pin value function.
```c
err_t emg_read_an_pin_value ( emg_t *ctx, uint16_t *data_out );
```

- `emg_read_an_pin_voltage` EMG read AN pin voltage level function.
```c
err_t emg_read_an_pin_voltage ( emg_t *ctx, float *data_out );
```

## Example Description

> This is an example which demonstrates the use of EMG Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes ADC and timer counter.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    emg_cfg_t emg_cfg;  /**< Click config object. */

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
    emg_cfg_setup( &emg_cfg );
    EMG_MAP_MIKROBUS( emg_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == emg_init( &emg, &emg_cfg ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    time = 0;
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads ADC value and sends results on serial plotter every 5 ms.

```c

void application_task ( void )  {
    uint16_t emg_an = 0;
    if ( emg_read_an_pin_value( &emg, &emg_an ) == ADC_SUCCESS ){
        log_printf( &logger, " %u,%lu\r\n ", emg_an, time );
    }
    time += 5;
    Delay_ms( 5 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.EMG

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
