
---
# EEG click

> EEG Click is a Click board™ that allows monitoring of brain activity. Although not suitable for clinical examination, it is quite sufficient to allow some insight into brain activity. EEG click is equipped with a high-sensitivity circuit which amplifies faint electrical signals from the brain, allowing them to be sampled by a host MCU.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/eeg_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/eeg-click)

---


#### Click library

- **Author**        : Jelena Milosavljevic
- **Date**          : Aug 2021.
- **Type**          : ADC type


# Software Support

We provide a library for the EEG Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for EEG Click driver.

#### Standard key functions :

- `eeg_cfg_setup` Config Object Initialization function.
```c
void eeg_cfg_setup ( eeg_cfg_t *cfg );
```

- `eeg_init` Initialization function.
```c
err_t eeg_init ( eeg_t *ctx, eeg_cfg_t *cfg );
```

#### Example key functions :

- `eeg_read_an_pin_value` This function reads results of AD conversion of the AN pin.
```c
err_t eeg_read_an_pin_value ( eeg_t *ctx, uint16_t *data_out );
```

- `eeg_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t eeg_read_an_pin_voltage ( eeg_t *ctx, float *data_out );
```

## Example Description

> This example demonstrates the use of EEG Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes Click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    eeg_cfg_t eeg_cfg;  /**< Click config object. */

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
    log_printf( &logger, " ----------------------------------------------\r\n" );
    log_printf( &logger, "                ***EEG click***               \r\n" );
    log_printf( &logger, "----------------------------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    // Click initialization.
    eeg_cfg_setup( &eeg_cfg );
    EEG_MAP_MIKROBUS( eeg_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == eeg_init( &eeg, &eeg_cfg ) ){
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads ADC value and sends results on serial plotter every 5 ms.

```c

void application_task ( void ) 
{
    uint16_t eeg_an_value = 0;
        
    if ( eeg_read_an_pin_value( &eeg, &eeg_an_value ) != ADC_ERROR ) {
        log_printf( &logger, " %u,%lu\r\n", eeg_an_value, time );
        Delay_ms ( 5 );
        time += 5;
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.EEG

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
