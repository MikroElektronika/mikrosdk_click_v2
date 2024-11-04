
---
# Opto Encoder 5 Click

> Opto Encoder 5 Click is a compact add-on board that offers non-contact switching with unparalleled accuracy and precision. This board features the OPB666N, a Photologic® slotted optical switch from TT Electronics, ensuring top-notch performance and reliability. It integrates an 890nm infrared LED and a monolithic integrated circuit with a photodiode, linear amplifier, and Schmitt trigger, all powered effectively by a 5V supply from the mikroBUS™ power rail. The board features an NPN open-collector output configuration and is TTI/LST TL compatible, highlighting its ease of use and versatility.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/optoencoder5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/opto-encoder-5-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2023.
- **Type**          : GPIO type


# Software Support

We provide a library for the Opto Encoder 5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Opto Encoder 5 Click driver.

#### Standard key functions :

- `optoencoder5_cfg_setup` Config Object Initialization function.
```c
void optoencoder5_cfg_setup ( optoencoder5_cfg_t *cfg );
```

- `optoencoder5_init` Initialization function.
```c
err_t optoencoder5_init ( optoencoder5_t *ctx, optoencoder5_cfg_t *cfg );
```

#### Example key functions :

- `optoencoder5_enable` This function enables the slotted optical switch of Opto Encoder 5 Click board.
```c
void optoencoder5_enable ( optoencoder5_t *ctx );
```

- `optoencoder5_disable` This function disables the slotted optical switch of Opto Encoder 5 Click board.
```c
void optoencoder5_disable ( optoencoder5_t *ctx );
```

- `optoencoder5_get_out_state` This function detecting slotted optical switch states of Opto Encoder 5 Click board.
```c
uint8_t optoencoder5_get_out_state ( optoencoder5_t *ctx );
```

## Example Description

> This example demonstrates the use of the Opto Encoder 5 Click board by detecting eclipse states.

**The demo application is composed of two sections :**

### Application Init

> Initialization of GPIO module, log UART and enables the slotted optical switch.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;                      /**< Logger config object. */
    optoencoder5_cfg_t optoencoder5_cfg;    /**< Click config object. */

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
    optoencoder5_cfg_setup( &optoencoder5_cfg );
    OPTOENCODER5_MAP_MIKROBUS( optoencoder5_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == optoencoder5_init( &optoencoder5, &optoencoder5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    optoencoder5_enable( &optoencoder5 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> When the beam from the slotted optical switch is broken by placing an object in
  the gap ( like a piece of paper ), the counter is incremented by one 
  when the sensor is triggered.

```c
void application_task ( void ) 
{
    out_state = optoencoder5_get_out_state( &optoencoder5 );
    if ( cmp_state != out_state )
    {
        if ( OPTOENCODER5_OUT_STATE_SWITCH_CLOSED == out_state )
        {
            log_printf( &logger, " Counter: %u \r\n", cnt );
            cnt++;
        }
        cmp_state = out_state;
    }
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.OptoEncoder5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
