
---
# Step Down 6 click

> Step Down 6 Click is a compact add-on board that converts higher voltages into lower ones. This board features the MPM54304, a quad-output power module from Monolithic Power Systems (MPS). It is a quad-output, DC/DC step-down power module with up to 3A per output on channels 1 and 2 and up to 2A per channels 3 and 4, providing continuous current on all four channels.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepdown6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/step-down-6-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : May 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Step Down 6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Step Down 6 Click driver.

#### Standard key functions :

- `stepdown6_cfg_setup` Config Object Initialization function.
```c
void stepdown6_cfg_setup ( stepdown6_cfg_t *cfg );
```

- `stepdown6_init` Initialization function.
```c
err_t stepdown6_init ( stepdown6_t *ctx, stepdown6_cfg_t *cfg );
```

- `stepdown6_default_cfg` Click Default Configuration function.
```c
err_t stepdown6_default_cfg ( stepdown6_t *ctx );
```

#### Example key functions :

- `stepdown6_set_en_pin` Step Down 6 set EN pin state function.
```c
void stepdown6_set_en_pin ( stepdown6_t *ctx, uint8_t pin_state );
```

- `stepdown6_write_reg` Step Down 6 Register writing function.
```c
err_t stepdown6_write_reg ( stepdown6_t *ctx, uint8_t reg, uint8_t data_in );
```

- `stepdown6_set_out_voltage` Step Down 6 Set output voltage function.
```c
err_t stepdown6_set_out_voltage ( stepdown6_t *ctx, uint8_t out_sel, uint16_t out_val );
```

## Example Description

> This library contains API for the Step Down 6 Click driver.
  This driver provides the functions to set the output voltage threshold.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
  After driver initialization, default settings sets output voltage to 550 mV.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepdown6_cfg_t stepdown6_cfg;  /**< Click config object. */

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
    stepdown6_cfg_setup( &stepdown6_cfg );
    STEPDOWN6_MAP_MIKROBUS( stepdown6_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepdown6_init( &stepdown6, &stepdown6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPDOWN6_ERROR == stepdown6_default_cfg ( &stepdown6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This example demonstrates the use of the Step Down 6 Click board™ by changing 
  output voltage every 5 seconds starting from 550 mV up to 1820 mV.

```c
void application_task ( void ) 
{
    err_t error_flag = STEPDOWN6_OK;
    for ( uint16_t n_cnt = STEPDOWN6_MIN_VOUT_VAL; n_cnt <= STEPDOWN6_MAX_VOUT_VAL; n_cnt += STEPDOWN6_INCREMENT_VOUT_VAL )
    {
        error_flag |= stepdown6_set_out_voltage( &stepdown6, STEPDOWN6_SELECT_VOUT1, n_cnt );
        error_flag |= stepdown6_set_out_voltage( &stepdown6, STEPDOWN6_SELECT_VOUT2, n_cnt );
        error_flag |= stepdown6_set_out_voltage( &stepdown6, STEPDOWN6_SELECT_VOUT3, n_cnt );
        error_flag |= stepdown6_set_out_voltage( &stepdown6, STEPDOWN6_SELECT_VOUT4, n_cnt );
        log_printf( &logger, "  Set voltage : %d mV \r\n", n_cnt );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.StepDown6

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
