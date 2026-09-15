/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file stepper31.h
 * @brief This file contains API for Stepper 31 Click Driver.
 */

#ifndef STEPPER31_H
#define STEPPER31_H

#ifdef __cplusplus
extern "C"{
#endif

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
    #if MikroCCoreVersion >= 1
        #include "delays.h"
    #endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup stepper31 Stepper 31 Click Driver
 * @brief API for configuring and manipulating Stepper 31 Click driver.
 * @{
 */

/**
 * @defgroup stepper31_reg Stepper 31 Registers List
 * @brief List of registers of Stepper 31 Click driver.
 */

/**
 * @addtogroup stepper31_reg
 * @{
 */

/**
 * @brief Stepper 31 register addresses.
 * @details MCP23S17 register map with IOCON.BANK cleared. The TB67S531FTG
 * motor driver is controlled through the expander outputs and has no SPI registers.
 */
#define STEPPER31_REG_IODIRA                    0x00
#define STEPPER31_REG_IODIRB                    0x01
#define STEPPER31_REG_IPOLA                     0x02
#define STEPPER31_REG_IPOLB                     0x03
#define STEPPER31_REG_GPINTENA                  0x04
#define STEPPER31_REG_GPINTENB                  0x05
#define STEPPER31_REG_DEFVALA                   0x06
#define STEPPER31_REG_DEFVALB                   0x07
#define STEPPER31_REG_INTCONA                   0x08
#define STEPPER31_REG_INTCONB                   0x09
#define STEPPER31_REG_IOCON                     0x0A
#define STEPPER31_REG_IOCON_ALIAS               0x0B
#define STEPPER31_REG_GPPUA                     0x0C
#define STEPPER31_REG_GPPUB                     0x0D
#define STEPPER31_REG_INTFA                     0x0E
#define STEPPER31_REG_INTFB                     0x0F
#define STEPPER31_REG_INTCAPA                   0x10
#define STEPPER31_REG_INTCAPB                   0x11
#define STEPPER31_REG_GPIOA                     0x12
#define STEPPER31_REG_GPIOB                     0x13
#define STEPPER31_REG_OLATA                     0x14
#define STEPPER31_REG_OLATB                     0x15
#define STEPPER31_REG_COUNT                     0x16

/*! @} */ // stepper31_reg

/**
 * @defgroup stepper31_set Stepper 31 Registers Settings
 * @brief Settings for registers of Stepper 31 Click driver.
 */

/**
 * @addtogroup stepper31_set
 * @{
 */

/**
 * @brief Stepper 31 SPI command settings.
 * @details The MCP23S17 opcode contains the read/write bit and three hardware
 * address bits selected by JP2 (A0), JP3 (A1), and JP4 (A2).
 */
#define STEPPER31_SPI_WRITE                     0x40
#define STEPPER31_SPI_READ                      0x41
#define STEPPER31_SPI_ADDRESS_MASK              0x07
#define STEPPER31_SPI_ADDRESS_A2                0x04
#define STEPPER31_SPI_DUMMY_DATA                0x00

/**
 * @brief Stepper 31 SPI hardware address options.
 * @details Unshifted address selected by JP2 (A0), JP3 (A1), and JP4 (A2).
 * GND selects zero and VCC selects one; all GND selects address 0.
 */
#define STEPPER31_SPI_ADDRESS_0                 0x00
#define STEPPER31_SPI_ADDRESS_1                 0x01
#define STEPPER31_SPI_ADDRESS_2                 0x02
#define STEPPER31_SPI_ADDRESS_3                 0x03
#define STEPPER31_SPI_ADDRESS_4                 0x04
#define STEPPER31_SPI_ADDRESS_5                 0x05
#define STEPPER31_SPI_ADDRESS_6                 0x06
#define STEPPER31_SPI_ADDRESS_7                 0x07
#define STEPPER31_SPI_ADDRESS_DEFAULT           STEPPER31_SPI_ADDRESS_0

/**
 * @brief Stepper 31 port register bit masks.
 * @details Each bit selects the corresponding pin in IODIR, IPOL, GPINTEN,
 * DEFVAL, INTCON, GPPU, INTF, INTCAP, GPIO, or OLAT. IODIR bits select input
 * when set; IPOL inverts input reads; GPINTEN and GPPU enable interrupts and
 * pull-ups. INTCON selects comparison against DEFVAL when set, or the previous
 * input value when cleared. GPIO and OLAT contain pin and output-latch levels.
 */
#define STEPPER31_PORT_PIN0                     0x01
#define STEPPER31_PORT_PIN1                     0x02
#define STEPPER31_PORT_PIN2                     0x04
#define STEPPER31_PORT_PIN3                     0x08
#define STEPPER31_PORT_PIN4                     0x10
#define STEPPER31_PORT_PIN5                     0x20
#define STEPPER31_PORT_PIN6                     0x40
#define STEPPER31_PORT_PIN7                     0x80
#define STEPPER31_PORT_ALL                      0xFF
#define STEPPER31_PORT_NONE                     0x00

/**
 * @brief Stepper 31 IOCON register settings.
 * @details Controls register banking, interrupt routing, sequential addressing,
 * SDA slew rate (I2C variant only), SPI hardware addressing, and interrupt
 * output polarity/type. Keep BANK and SEQOP cleared when using this driver.
 * ODR overrides INTPOL when open-drain interrupt outputs are selected.
 */
#define STEPPER31_IOCON_BANK_MASK               0x80
#define STEPPER31_IOCON_BANK_INTERLEAVED        0x00
#define STEPPER31_IOCON_BANK_SEPARATE           0x80
#define STEPPER31_IOCON_MIRROR_MASK             0x40
#define STEPPER31_IOCON_INT_SEPARATE            0x00
#define STEPPER31_IOCON_INT_MIRRORED            0x40
#define STEPPER31_IOCON_SEQOP_MASK              0x20
#define STEPPER31_IOCON_SEQUENTIAL_ON           0x00
#define STEPPER31_IOCON_SEQUENTIAL_OFF          0x20
#define STEPPER31_IOCON_DISSLW_MASK             0x10
#define STEPPER31_IOCON_SLEW_ON                 0x00
#define STEPPER31_IOCON_SLEW_OFF                0x10
#define STEPPER31_IOCON_HAEN_MASK               0x08
#define STEPPER31_IOCON_ADDRESS_OFF             0x00
#define STEPPER31_IOCON_ADDRESS_ON              0x08
#define STEPPER31_IOCON_ODR_MASK                0x04
#define STEPPER31_IOCON_INT_PUSH_PULL           0x00
#define STEPPER31_IOCON_INT_OPEN_DRAIN          0x04
#define STEPPER31_IOCON_INTPOL_MASK             0x02
#define STEPPER31_IOCON_INT_ACTIVE_LOW          0x00
#define STEPPER31_IOCON_INT_ACTIVE_HIGH         0x02

/**
 * @brief Stepper 31 port A signal masks.
 * @details TRQ is connected to the torque switch, LO1/LO2 are active-low motor
 * fault outputs, and SEL selects the phase input multiplexers. SEL high routes
 * PHA_SPI/PHB_SPI to the driver; SEL low routes the mikroBUS PHA/PHB pins.
 */
#define STEPPER31_PA_TRQ                        STEPPER31_PORT_PIN0
#define STEPPER31_PA_LO1                        STEPPER31_PORT_PIN1
#define STEPPER31_PA_LO2                        STEPPER31_PORT_PIN2
#define STEPPER31_PA_SEL                        STEPPER31_PORT_PIN3
#define STEPPER31_PA_FAULT_MASK                 ( STEPPER31_PA_LO1 | STEPPER31_PA_LO2 )
#define STEPPER31_PA_UNUSED_MASK                0xF0

/**
 * @brief Stepper 31 port B signal masks.
 * @details Port B controls both winding current levels, decay mode, and phase
 * polarity. Updating OLATB changes the complete motor excitation pattern in
 * one port write. PHASE high selects current from OUT1 to OUT2.
 */
#define STEPPER31_PB_IN_B2                      STEPPER31_PORT_PIN0
#define STEPPER31_PB_IN_B1                      STEPPER31_PORT_PIN1
#define STEPPER31_PB_IN_A2                      STEPPER31_PORT_PIN2
#define STEPPER31_PB_IN_A1                      STEPPER31_PORT_PIN3
#define STEPPER31_PB_DECAY2                     STEPPER31_PORT_PIN4
#define STEPPER31_PB_DECAY1                     STEPPER31_PORT_PIN5
#define STEPPER31_PB_PHA                        STEPPER31_PORT_PIN6
#define STEPPER31_PB_PHB                        STEPPER31_PORT_PIN7
#define STEPPER31_PB_CURRENT_A_MASK             ( STEPPER31_PB_IN_A1 | STEPPER31_PB_IN_A2 )
#define STEPPER31_PB_CURRENT_B_MASK             ( STEPPER31_PB_IN_B1 | STEPPER31_PB_IN_B2 )
#define STEPPER31_PB_DECAY_MASK                 ( STEPPER31_PB_DECAY1 | STEPPER31_PB_DECAY2 )

/**
 * @brief Stepper 31 winding current settings.
 * @details IN1/IN2 select 100%, 71%, 38%, or zero current. Zero current places
 * that winding in high impedance. VR1 sets VREF at TP1; at 100% torque and
 * 100% winding current, IOUT [A] = VREF [V] x 0.556. Software cannot set VREF.
 */
#define STEPPER31_CURRENT_A_OFF                 0x00
#define STEPPER31_CURRENT_A_38                  STEPPER31_PB_IN_A2
#define STEPPER31_CURRENT_A_71                  STEPPER31_PB_IN_A1
#define STEPPER31_CURRENT_A_100                 STEPPER31_PB_CURRENT_A_MASK
#define STEPPER31_CURRENT_B_OFF                 0x00
#define STEPPER31_CURRENT_B_38                  STEPPER31_PB_IN_B2
#define STEPPER31_CURRENT_B_71                  STEPPER31_PB_IN_B1
#define STEPPER31_CURRENT_B_100                 STEPPER31_PB_CURRENT_B_MASK

/**
 * @brief Stepper 31 current decay modes.
 * @details DECAY2/DECAY1 select mixed (00), slow (01), fast (10), or advanced
 * dynamic mixed decay (11). Values are aligned to the port B decay bits.
 */
#define STEPPER31_DECAY_MIXED                   0x00
#define STEPPER31_DECAY_SLOW                    STEPPER31_PB_DECAY1
#define STEPPER31_DECAY_FAST                    STEPPER31_PB_DECAY2
#define STEPPER31_DECAY_ADMD                    STEPPER31_PB_DECAY_MASK

/**
 * @brief Stepper 31 step resolution settings.
 * @details Full, half, and quarter stepping use 4, 8, and 16 states per
 * electrical cycle. Full stepping energizes both windings at 100%; half
 * stepping alternates one and two windings. Quarter stepping uses the
 * driver's 38%, 71%, and 100% current levels. Physical direction depends on
 * winding polarity and motor wiring, not only the direction constant.
 */
#define STEPPER31_MODE_FULL_STEP                0x00
#define STEPPER31_MODE_HALF_STEP                0x01
#define STEPPER31_MODE_QUARTER_STEP             0x02

/**
 * @brief Stepper 31 direction settings.
 * @details Selects forward or reverse traversal of the excitation table.
 * Actual shaft direction depends on the motor winding connections.
 */
#define STEPPER31_DIR_CW                        0
#define STEPPER31_DIR_CCW                       1

/**
 * @brief Stepper 31 motor speed settings.
 * @details Selects the delay after each step: 10 ms, 5 ms, 2.5 ms, 1 ms, or
 * 0.5 ms. The actual step interval also includes SPI transfers and fault checks.
 * These presets do not specify RPM or provide acceleration control.
 */
#define STEPPER31_SPEED_VERY_SLOW               0
#define STEPPER31_SPEED_SLOW                    1
#define STEPPER31_SPEED_MEDIUM                  2
#define STEPPER31_SPEED_FAST                    3
#define STEPPER31_SPEED_VERY_FAST               4

/**
 * @brief Stepper 31 torque selection.
 * @details TRQ low selects 100% current and TRQ high selects 50%. SWITCH
 * releases GPA0 to an input so SW1 controls TRQ through its series resistor.
 */
#define STEPPER31_TORQUE_100                    0
#define STEPPER31_TORQUE_50                     1
#define STEPPER31_TORQUE_SWITCH                 2

/**
 * @brief Stepper 31 motor fault states.
 * @details LO1 low indicates overcurrent or thermal shutdown; LO2 low
 * identifies thermal shutdown. Fault recovery requires removing the cause
 * before calling the default configuration function to cycle SLEEP_X.
 */
#define STEPPER31_FAULT_NONE                    0
#define STEPPER31_FAULT_OVERCURRENT             1
#define STEPPER31_FAULT_OVERTEMPERATURE         2

/**
 * @brief Stepper 31 default expander configuration.
 * @details Uses hardware SPI addressing and active-low mirrored interrupts.
 * Only SEL is an output on port A; SW1 controls torque. All port B pins are
 * outputs, with ADMD selected and both windings off. LO1/LO2 interrupt when low.
 */
#define STEPPER31_DEFAULT_IOCON                 ( STEPPER31_IOCON_INT_MIRRORED | STEPPER31_IOCON_ADDRESS_ON )
#define STEPPER31_DEFAULT_IODIRA                ( STEPPER31_PA_UNUSED_MASK | STEPPER31_PA_FAULT_MASK | STEPPER31_PA_TRQ )
#define STEPPER31_DEFAULT_IODIRB                STEPPER31_PORT_NONE
#define STEPPER31_DEFAULT_OLATA                 STEPPER31_PA_SEL
#define STEPPER31_DEFAULT_OLATB                 STEPPER31_DECAY_ADMD
#define STEPPER31_DEFAULT_GPPUA                 ( STEPPER31_PA_UNUSED_MASK | STEPPER31_PA_FAULT_MASK )
#define STEPPER31_DEFAULT_GPINTENA              STEPPER31_PA_FAULT_MASK
#define STEPPER31_DEFAULT_DEFVALA               STEPPER31_PA_FAULT_MASK
#define STEPPER31_DEFAULT_INTCONA               STEPPER31_PA_FAULT_MASK

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b stepper31_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define STEPPER31_SET_DATA_SAMPLE_EDGE          SET_SPI_DATA_SAMPLE_EDGE
#define STEPPER31_SET_DATA_SAMPLE_MIDDLE        SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // stepper31_set

/**
 * @defgroup stepper31_map Stepper 31 MikroBUS Map
 * @brief MikroBUS pin mapping of Stepper 31 Click driver.
 */

/**
 * @addtogroup stepper31_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stepper 31 Click to the selected MikroBUS.
 */
#define STEPPER31_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.pha  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.spx  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.phb  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepper31_map
/*! @} */ // stepper31

/**
 * @brief Stepper 31 Click context object.
 * @details Context object definition of Stepper 31 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t pha;          /**< Direct winding A phase output, held low in SPI phase mode. */
    digital_out_t spx;          /**< Shared active-low motor sleep and expander reset output. */
    digital_out_t phb;          /**< Direct winding B phase output, held low in SPI phase mode. */

    // Input pins
    digital_in_t int_pin;       /**< Active-low expander interrupt input for LO1/LO2 faults. */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t chip_select;     /**< Chip select pin descriptor (used for SPI driver). */

    uint8_t spi_address;        /**< MCP23S17 address selected by JP2, JP3, and JP4 (0-7). */
    uint8_t step_mode;          /**< Full, half, or quarter-step resolution setting. */
    uint8_t direction;          /**< Direction used by the blocking motor drive function. */
    uint8_t step_index;         /**< Current position in the selected excitation sequence. */
    uint8_t decay_mode;         /**< Current decay setting aligned to port B. */

} stepper31_t;

/**
 * @brief Stepper 31 Click configuration object.
 * @details Configuration object definition of Stepper 31 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t pha;             /**< Direct winding A phase pin descriptor. */
    pin_name_t spx;             /**< Motor sleep and expander reset pin descriptor (active low). */
    pin_name_t phb;             /**< Direct winding B phase pin descriptor. */
    pin_name_t int_pin;         /**< Active-low expander interrupt pin descriptor. */

    // static variable
    uint8_t                           spi_address;  /**< Hardware address selected by JP2-JP4 (0-7). */
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} stepper31_cfg_t;

/**
 * @brief Stepper 31 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPPER31_OK = 0,
    STEPPER31_ERROR = -1

} stepper31_return_value_t;

/*!
 * @addtogroup stepper31 Stepper 31 Click Driver
 * @brief API for configuring and manipulating Stepper 31 Click driver.
 * @{
 */

/**
 * @brief Stepper 31 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepper31_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepper31_cfg_setup ( stepper31_cfg_t *cfg );

/**
 * @brief Stepper 31 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #stepper31_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepper31_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note SPX stays low until default_cfg. Match spi_address to JP2-JP4.
 */
err_t stepper31_init ( stepper31_t *ctx, stepper31_cfg_t *cfg );

/**
 * @brief Stepper 31 default configuration function.
 * @details This function resets and verifies the expander, then applies the
 * default motor and fault settings with both windings off.
 * @param[in] ctx : Click context object.
 * See #stepper31_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Required before motor use. Set VR1 and remove any fault cause before
 * calling; this function clears latched shutdown faults.
 */
err_t stepper31_default_cfg ( stepper31_t *ctx );

/**
 * @brief Stepper 31 communication check function.
 * @details This function verifies SPI using unused OLATA bits and restores the latch.
 * @param[in] ctx : Click context object.
 * See #stepper31_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Communication or verification error.
 * See #err_t definition for detailed explanation.
 * @note Requires BANK = 0 and GPA4-GPA7 configured as inputs, as in default_cfg.
 */
err_t stepper31_check_com ( stepper31_t *ctx );

/**
 * @brief Stepper 31 write register function.
 * @details This function writes a single byte to the selected MCP23S17 register.
 * @param[in] ctx : Click context object.
 * See #stepper31_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Requires BANK = 0. Avoid direct output writes during motion.
 */
err_t stepper31_write_reg ( stepper31_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Stepper 31 write registers function.
 * @details This function writes consecutive MCP23S17 registers with CS held low.
 * @param[in] ctx : Click context object.
 * See #stepper31_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Pointer to the input data buffer.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Requires BANK = 0 and SEQOP = 0. Avoid direct output writes during motion.
 */
err_t stepper31_write_regs ( stepper31_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Stepper 31 read register function.
 * @details This function reads a single byte from the selected MCP23S17 register.
 * @param[in] ctx : Click context object.
 * See #stepper31_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Requires BANK = 0. GPIO/INTCAP reads acknowledge captured interrupts.
 */
err_t stepper31_read_reg ( stepper31_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Stepper 31 read registers function.
 * @details This function reads consecutive MCP23S17 registers with CS held low.
 * @param[in] ctx : Click context object.
 * See #stepper31_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Pointer to the output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Requires BANK = 0 and SEQOP = 0. GPIO/INTCAP reads acknowledge interrupts.
 */
err_t stepper31_read_regs ( stepper31_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Stepper 31 drive motor function.
 * @details This function drives the requested steps, then releases both windings.
 * Faults and SPI errors stop the move; the excitation index is retained.
 * @param[in] ctx : Click context object.
 * See #stepper31_t object definition for detailed explanation.
 * @param[in] steps : Number of full, half, or quarter-step advances. Zero is a no-op.
 * @param[in] speed : Motor rotation speed:
 *                    @li @c 0 - Very slow,
 *                    @li @c 1 - Slow,
 *                    @li @c 2 - Medium,
 *                    @li @c 3 - Fast,
 *                    @li @c 4 - Very fast.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid setting, motor fault, or communication error.
 * See #err_t definition for detailed explanation.
 * @note Blocking call with a 10 ms startup delay and no acceleration ramp.
 * Check faults before retrying a failed move.
 */
err_t stepper31_drive_motor ( stepper31_t *ctx, uint32_t steps, uint8_t speed );

/**
 * @brief Stepper 31 step mode selection function.
 * @details This function selects the step resolution and resets the sequence index.
 * @param[in] ctx : Click context object.
 * See #stepper31_t object definition for detailed explanation.
 * @param[in] mode : Step resolution:
 *                   @li @c 0 - Full step,
 *                   @li @c 1 - Half step,
 *                   @li @c 2 - Quarter step.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid mode; the previous setting is retained.
 * See #err_t definition for detailed explanation.
 * @note Stop the motor before changing mode; this function does not drive outputs.
 */
err_t stepper31_set_step_mode ( stepper31_t *ctx, uint8_t mode );

/**
 * @brief Stepper 31 direction setting function.
 * @details This function stores the direction for the next drive_motor call.
 * @param[in] ctx : Click context object.
 * See #stepper31_t object definition for detailed explanation.
 * @param[in] dir : STEPPER31_DIR_CW or STEPPER31_DIR_CCW.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid direction; the previous setting is retained.
 * See #err_t definition for detailed explanation.
 * @note A direct call to stepper31_step uses its own direction argument.
 */
err_t stepper31_set_direction ( stepper31_t *ctx, uint8_t dir );

/**
 * @brief Stepper 31 direction switching function.
 * @details This function toggles the stored clockwise/counter-clockwise direction.
 * @param[in] ctx : Click context object.
 * See #stepper31_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - The stored direction is invalid.
 * See #err_t definition for detailed explanation.
 * @note The new direction takes effect on the next drive_motor call.
 */
err_t stepper31_switch_direction ( stepper31_t *ctx );

/**
 * @brief Stepper 31 decay mode setting function.
 * @details This function changes decay mode while preserving current and phase bits.
 * @param[in] ctx : Click context object.
 * See #stepper31_t object definition for detailed explanation.
 * @param[in] mode : STEPPER31_DECAY_MIXED, STEPPER31_DECAY_SLOW,
 * STEPPER31_DECAY_FAST, or STEPPER31_DECAY_ADMD.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid setting or communication error.
 * See #err_t definition for detailed explanation.
 * @note Select a decay mode appropriate for the motor inductance and speed.
 */
err_t stepper31_set_decay ( stepper31_t *ctx, uint8_t mode );

/**
 * @brief Stepper 31 torque setting function.
 * @details This function selects software torque control or returns control to SW1.
 * @param[in] ctx : Click context object.
 * See #stepper31_t object definition for detailed explanation.
 * @param[in] mode : STEPPER31_TORQUE_100, STEPPER31_TORQUE_50, or STEPPER31_TORQUE_SWITCH.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid setting or communication error.
 * See #err_t definition for detailed explanation.
 * @note The scale applies to the current limit set by VREF, not motor speed.
 */
err_t stepper31_set_torque ( stepper31_t *ctx, uint8_t mode );

/**
 * @brief Stepper 31 enable device function.
 * @details This function energizes the current excitation state after checking faults.
 * @param[in] ctx : Click context object.
 * See #stepper31_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid excitation state, motor fault, or communication error.
 * See #err_t definition for detailed explanation.
 * @note Applies holding current without advancing the sequence; set VREF first.
 */
err_t stepper31_enable_device ( stepper31_t *ctx );

/**
 * @brief Stepper 31 single step function.
 * @details This function checks faults and advances one excitation state.
 * @param[in] ctx : Click context object.
 * See #stepper31_t object definition for detailed explanation.
 * @param[in] direction : STEPPER31_DIR_CW or STEPPER31_DIR_CCW.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid direction or step mode, motor fault, or communication error.
 * See #err_t definition for detailed explanation.
 * @note No delay is added; the caller sets the step interval. This call can
 * re-energize windings after disable_device.
 */
err_t stepper31_step ( stepper31_t *ctx, uint8_t direction );

/**
 * @brief Stepper 31 disable device function.
 * @details This function releases both windings and retains the excitation index.
 * @param[in] ctx : Click context object.
 * See #stepper31_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Communication error.
 * See #err_t definition for detailed explanation.
 * @note No holding torque. An SPI failure forces SPX low; rerun default_cfg before motion.
 */
err_t stepper31_disable_device ( stepper31_t *ctx );

/**
 * @brief Stepper 31 fault status reading function.
 * @details This function reads LO1/LO2 and reports the motor fault state.
 * @param[in] ctx : Click context object.
 * See #stepper31_t object definition for detailed explanation.
 * @param[out] fault : STEPPER31_FAULT_NONE, STEPPER31_FAULT_OVERCURRENT,
 * or STEPPER31_FAULT_OVERTEMPERATURE.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid output pointer or communication error; fault is unchanged.
 * See #err_t definition for detailed explanation.
 * @note Check the fault value; reading acknowledges interrupts but does not reset motor faults.
 */
err_t stepper31_get_fault ( stepper31_t *ctx, uint8_t *fault );

/**
 * @brief Stepper 31 interrupt pin reading function.
 * @details This function reads the active-low INT pin without accessing SPI.
 * @param[in] ctx : Click context object.
 * See #stepper31_t object definition for detailed explanation.
 * @return @li @c 0 - Interrupt asserted,
 *         @li @c 1 - Interrupt not asserted.
 * @note Read the fault status to determine the interrupt source.
 */
uint8_t stepper31_get_int_pin ( stepper31_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // STEPPER31_H

/*! @} */ // stepper31

// ------------------------------------------------------------------------ END
