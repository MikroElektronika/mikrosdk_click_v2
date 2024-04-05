
---

# Hall Current 9 click

Hall Current 9 Click is a compact add-on board that contains the coreless current sensor corresponding to the safety standards. This board features the CQ3300, a high-speed response coreless current sensor using a Hall sensor that outputs the analog voltage proportional to the AC/DC from AKM Semiconductor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hall_current_9_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/hall-current-9-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the HallCurrent9 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

```
> This library contains API for Hall Current 9 Click driver.

```

#### Standard key functions :

- `hallcurrent9_cfg_setup` Config Object Initialization function.
```
void hallcurrent9_cfg_setup ( hallcurrent9_cfg_t *cfg );
```

- `hallcurrent9_init` Initialization function.
```
HALLCURRENT9_RETVAL hallcurrent9_init ( hallcurrent9_t *ctx, hallcurrent9_cfg_t *cfg );
```

- `hallcurrent9_default_cfg` Click Default Configuration function.
```
void hallcurrent9_default_cfg ( hallcurrent9_t *ctx );
```

#### Example key functions :

- `hallcurrent9_read_adc` Hall Current 9 I2C ADC reading function.
```
err_t hallcurrent9_read_adc ( hallcurrent9_t *ctx, uint16_t *read_adc );
```

- `hallcurrent9_set_calibration` Hall Current 9 set calibration function.
```
err_t hallcurrent9_set_calibration ( hallcurrent9_t *ctx, hallcurrent9_calibration_data_t *adc_val );
```

- `hallcurrent9_get_current` Hall Current 9 get current function.
```
float hallcurrent9_get_current ( hallcurrent9_t *ctx, hallcurrent9_calibration_data_t *adc_val );
```

## Examples Description

> This library contains API for Hall Current 9 Click driver.
> The library contains drivers for measuring ADC values 
> and for calculation current.

**The demo application is composed of two sections :**

### Application Init

> Initializes I2C driver and triggers the built-in calibration.

```
void application_init ( void ) {
    log_cfg_t log_cfg;                    /**< Logger config object. */
    hallcurrent9_cfg_t hallcurrent9_cfg;  /**< Click config object.  */

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
    log_printf( &logger, "\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "   Hall Current 9 click   \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    hallcurrent9_cfg_setup( &hallcurrent9_cfg );
    HALLCURRENT9_MAP_MIKROBUS( hallcurrent9_cfg, MIKROBUS_1 );
    err_t init_flag = hallcurrent9_init( &hallcurrent9, &hallcurrent9_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_printf( &logger, "---------------------------\r\n" );
    log_printf( &logger, "        Calibration        \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "> Turn OFF the Power unit <\r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "  In the following 5 sec.  \r\n" );
    log_printf( &logger, " turn OFF the Power Supply \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "    Start calibration    \r\n" );
    
    if ( hallcurrent9_set_calibration( &hallcurrent9, &avg_adc_data ) == HALLCURRENT9_OK ) {
        log_printf( &logger, "---------------------------\r\n" );
        log_printf( &logger, "    Calibration  Done    \r\n" );
        Delay_ms ( 1000 );    
    }
    
    log_printf( &logger, "---------------------------\r\n" );
    log_printf( &logger, "    Start measurements :   \r\n" );
    log_printf( &logger, "---------------------------\r\n" );
}
```

### Application Task

> This is an example that demonstrates the use of the Hall Current 9 click board.
> In this example, we read and display the ADC and current ( mA ) data.
> Results are being sent to the Usart Terminal where you can track their changes.

```
void application_task ( void ) {   
    log_printf( &logger, "--------------------------\r\n", adc_data );
    hallcurrent9_read_adc( &hallcurrent9, &adc_data );
    log_printf( &logger, "   ADC     : %d \r\n", adc_data );

    current = hallcurrent9_get_current( &hallcurrent9, &avg_adc_data );
    log_printf( &logger, "   Current : %.2f mA \r\n", current );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent9

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
