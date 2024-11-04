\mainpage Main Page

---
# Vibra Sense 2 Click

> Vibra Sense 2 Click is a compact add-on board that contains a piezo sensor suitable for vibration measurements. This board features the LDT0-028K, a flexible 28 μm thick piezoelectric PVDF polymer film with screen-printed silver ink electrodes, laminated to a 0.125 mm polyester substrate, and fitted with two crimped contacts from TE Connectivity.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/vibrasense2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/vibra-sense-2-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the VibraSense2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for VibraSense2 Click driver.

#### Standard key functions :

- `vibrasense2_cfg_setup` Config Object Initialization function.
```c
void vibrasense2_cfg_setup ( vibrasense2_cfg_t *cfg );
```

- `vibrasense2_init` Initialization function.
```c
err_t vibrasense2_init ( vibrasense2_t *ctx, vibrasense2_cfg_t *cfg );
```

#### Example key functions :

- `vibrasense2_read_data` Read data function.
```c
uint16_t vibrasense2_read_data ( vibrasense2_t *ctx );
```

- `vibrasense2_read_voltage` Read voltage function.
```c
uint16_t vibrasense2_read_voltage ( vibrasense2_t *ctx, uint16_t v_ref );
```

- `vibrasense2_vibration_level` Get Vibration Level function.
```c
int8_t vibrasense2_vibration_level ( vibrasense2_t *ctx );
```

## Example Description

> This example shows capabilities of Vibra Sense 2 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initalizes I2C driver and makes an initial log.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    vibrasense2_cfg_t vibrasense2_cfg;  /**< Click config object. */

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
    vibrasense2_cfg_setup( &vibrasense2_cfg );
    VIBRASENSE2_MAP_MIKROBUS( vibrasense2_cfg, MIKROBUS_1 );
    err_t init_flag = vibrasense2_init( &vibrasense2, &vibrasense2_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    old_val = VIBRASENSE2_ERROR;
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------------------------\r\n" );
}

```

### Application Task

> Demonstrates use of Vibra Sense 2 Click board by checking vibration levels and displaying changes via USART terminal.

```c

void application_task ( void ) {
    new_val = vibrasense2_vibration_level( &vibrasense2 );
    Delay_ms ( 100 );
    if ( new_val != old_val ) {
        switch ( new_val ) {
            case VIBRASENSE2_VIBRA_LVL_0: {
                log_printf( &logger, "            No Vibration \r\n" );
                log_printf( &logger, "-------------------------------------\r\n" );
                break;
            }
            case VIBRASENSE2_VIBRA_LVL_1: {
                log_printf( &logger, " Vibration level : Marginal Vibration \r\n" );
                log_printf( &logger, "-------------------------------------\r\n" );
                break;
            }
            case VIBRASENSE2_VIBRA_LVL_2: {
                log_printf( &logger, " Vibration level : Slight Vibration \r\n" );
                log_printf( &logger, "-------------------------------------\r\n" );
                break;
            }
            case VIBRASENSE2_VIBRA_LVL_3: {
                log_printf( &logger, " Vibration level : Enhanced Vibration \r\n" );
                log_printf( &logger, "-------------------------------------\r\n" );
                break;
            }
            case VIBRASENSE2_VIBRA_LVL_4: {
                log_printf( &logger, " Vibration level : Moderate Vibration \r\n" );
                log_printf( &logger, "-------------------------------------\r\n" );
                break;
            }
            case VIBRASENSE2_VIBRA_LVL_5: {
                log_printf( &logger, " Vibration level : High Vibration \r\n" );
                log_printf( &logger, "-------------------------------------\r\n" );
                break;
            }
            case VIBRASENSE2_VIBRA_LVL_6: {
                log_printf( &logger, " Vibration level : Severe Vibration \r\n" );
                log_printf( &logger, "-------------------------------------\r\n" );
                break;
            }
            default: {
                log_printf( &logger, "Error occured!" );
                log_printf( &logger, "-------------------------------------\r\n" );
            }
        }
        old_val = new_val;
    }
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.VibraSense2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
