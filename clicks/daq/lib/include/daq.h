/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
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
 * @file daq.h
 * @brief This file contains API for DAQ Click Driver.
 */

#ifndef DAQ_H
#define DAQ_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"

/*!
 * @addtogroup daq DAQ Click Driver
 * @brief API for configuring and manipulating DAQ Click driver.
 * @{
 */

/**
 * @defgroup daq_reg DAQ Registers List
 * @brief List of registers of DAQ Click driver.
 */

/**
 * @addtogroup daq_reg
 * @{
 */

/**
 * @brief DAQ description register.
 * @details Specified register for description of DAQ Click driver.
 */
#define DAQ_REG_CHIP_TYPE           0x03
#define DAQ_REG_PRODUCT_ID_L        0x04
#define DAQ_REG_PRODUCT_ID_H        0x05
#define DAQ_REG_CHIP_GRADE          0x06
#define DAQ_REG_SCRATCH_PAD         0x0A
#define DAQ_REG_VENDOR_L            0x0C
#define DAQ_REG_VENDOR_H            0x0D
#define DAQ_REG_INTERFACE_FORMAT    0x14
#define DAQ_REG_POWER_CLOCK         0x15
#define DAQ_REG_ANALOG              0x16
#define DAQ_REG_ANALOG2             0x17
#define DAQ_REG_CONVERSION          0x18
#define DAQ_REG_DIGITAL_FILTER      0x19
#define DAQ_REG_SINC3_DEC_RATE_MSB  0x1A
#define DAQ_REG_SINC3_DEC_RATE_LSB  0x1B
#define DAQ_REG_DUTY_CYCLE_RATION   0x1C
#define DAQ_REG_SYNC_RESET          0x1D
#define DAQ_REG_GPIO_CONTROL        0x1E
#define DAQ_REG_GPIO_WRITE          0x1F
#define DAQ_REG_GPIO_READ           0x20
#define DAQ_REG_OFFSET_HI           0x21
#define DAQ_REG_OFFSET_MID          0x22
#define DAQ_REG_OFFSET_LO           0x23
#define DAQ_REG_GAIN_HI             0x24
#define DAQ_REG_GAIN_MID            0x25
#define DAQ_REG_GAIN_LO             0x26
#define DAQ_REG_BIST_CONTROL        0x27
#define DAQ_REG_SPI_DIAG_ENABLE     0x28
#define DAQ_REG_ADC_DIAG_ENABLE     0x29
#define DAQ_REG_DIG_DIAG_ENABLE     0x2A
#define DAQ_REG_ADC_DATA            0x2C
#define DAQ_REG_MASTER_STATUS       0x2D
#define DAQ_REG_SPI_DIAG_STATUS     0x2E
#define DAQ_REG_ADC_DIAG_STATUS     0x2F
#define DAQ_REG_DIG_DIAG_STATUS     0x30
#define DAQ_REG_MCLK_COUNTER        0x31
#define DAQ_REG_COEFF_CONTROL       0x32
#define DAQ_REG_COEFF_DATA          0x33
#define DAQ_REG_ACCESS_KEY          0x34


/*! @} */ // daq_reg

/**
 * @defgroup daq_set DAQ Registers Settings
 * @brief Settings for registers of DAQ Click driver.
 */

/**
 * @addtogroup daq_set
 * @{
 */

/**
 * @brief DAQ inteface format settings.
 * @details Specified settings for inteface format of DAQ Click driver.
 */
#define DAQ_INTERFACE_CRC_EN_MSK			(0x1 << 6)
#define DAQ_INTERFACE_CRC_EN(x)				(((x) & 0x1) << 6)
#define DAQ_INTERFACE_CRC_TYPE_MSK			(0x1 << 5)
#define DAQ_INTERFACE_CRC_TYPE(x)			(((x) & 0x1) << 5)
#define DAQ_INTERFACE_STATUS_EN_MSK			(0x1 << 4)
#define DAQ_INTERFACE_STATUS_EN(x)			(((x) & 0x1) << 4)
#define DAQ_INTERFACE_CONVLEN_MSK			(0x1 << 3)
#define DAQ_INTERFACE_CONVLEN(x)			(((x) & 0x1) << 3)
#define DAQ_INTERFACE_RDY_EN_MSK			(0x1 << 2)
#define DAQ_INTERFACE_RDY_EN(x)				(((x) & 0x1) << 3)
#define DAQ_INTERFACE_CONT_READ_MSK			(0x1 << 0)
#define DAQ_INTERFACE_CONT_READ_EN(x)		(((x) & 0x1) << 0)
#define DAQ_REG_COEFF_CONTROL				0x32
#define DAQ_REG_COEFF_DATA					0x33
#define DAQ_REG_ACCESS_KEY					0x34

/**
 * @brief DAQ power clock settings.
 * @details Specified settings for power clock of DAQ Click driver.
 */
#define DAQ_POWER_CLK_PWRMODE_MSK			0x3
#define DAQ_POWER_CLK_PWRMODE(x)			(((x) & 0x3) << 0)
#define DAQ_POWER_CLK_MOD_OUT_MSK			(0x1 << 2)
#define DAQ_POWER_CLK_MOD_OUT(x)			(((x) & 0x1) << 2)
#define DAQ_POWER_CLK_POWER_DOWN			0x08
#define DAQ_POWER_CLK_MCLK_DIV_MSK			(0x3 << 4)
#define DAQ_POWER_CLK_MCLK_DIV(x)			(((x) & 0x3) << 4)
#define DAQ_POWER_CLK_CLOCK_SEL_MSK			(0x3 << 6)
#define DAQ_POWER_CLK_CLOCK_SEL(x)			(((x) & 0x3) << 6)

/**
 * @brief DAQ conversion settings.
 * @details Specified settings for conversion of DAQ Click driver.
 */
#define DAQ_CONVERSION_DIAG_MUX_MSK			(0xF << 4)
#define DAQ_CONVERSION_DIAG_MUX_SEL(x)		(((x) & 0xF) << 4)
#define DAQ_CONVERSION_DIAG_SEL_MSK			(0x1 << 3)
#define DAQ_CONVERSION_DIAG_SEL(x)			(((x) & 0x1) << 3)
#define DAQ_CONVERSION_MODE_MSK				(0x7 << 0)
#define DAQ_CONVERSION_MODE(x)				(((x) & 0x7) << 0)

/**
 * @brief DAQ analog settings.
 * @details Specified settings for analog of DAQ Click driver.
 */
#define DAQ_ANALOG_REF_BUF_POS_MSK			(0x3 << 6)
#define DAQ_ANALOG_REF_BUF_POS(x)			(((x) & 0x3) << 6)
#define DAQ_ANALOG_REF_BUF_NEG_MSK			(0x3 << 4)
#define DAQ_ANALOG_REF_BUF_NEG(x)			(((x) & 0x3) << 4)
#define DAQ_ANALOG_AIN_BUF_POS_OFF_MSK		(0x1 << 1)
#define DAQ_ANALOG_AIN_BUF_POS_OFF(x)		(((x) & 0x1) << 1)
#define DAQ_ANALOG_AIN_BUF_NEG_OFF_MSK		(0x1 << 0)
#define DAQ_ANALOG_AIN_BUF_NEG_OFF(x)		(((x) & 0x1) << 0)
#define DAQ_ANALOG2_VCM_MSK					(0x7 << 0)
#define DAQ_ANALOG2_VCM(x)					(((x) & 0x7) << 0)

/**
 * @brief DAQ digital filter settings.
 * @details Specified settings for digital filter of DAQ Click driver.
 */
#define DAQ_DIGI_FILTER_60HZ_REJ_EN_MSK		(0x1 << 7)
#define DAQ_DIGI_FILTER_60HZ_REJ_EN(x)		(((x) & 0x1) << 7)
#define DAQ_DIGI_FILTER_FILTER_MSK			(0x7 << 4)
#define DAQ_DIGI_FILTER_FILTER(x)			(((x) & 0x7) << 4)
#define DAQ_DIGI_FILTER_DEC_RATE_MSK		(0x7 << 0)
#define DAQ_DIGI_FILTER_DEC_RATE(x)			(((x) & 0x7) << 0)

/**
 * @brief DAQ sinc3 decimal rate settings.
 * @details Specified settings for digital filter of DAQ Click driver.
 */
#define DAQ_SINC3_DEC_RATE_MSB_MSK			(0x0F << 0)
#define DAQ_SINC3_DEC_RATE_MSB(x)			(((x) & 0x0F) << 0)
#define DAQ_SINC3_DEC_RATE_LSB_MSK			(0xFF << 0)
#define DAQ_SINC3_DEC_RATE_LSB(x)			(((x) & 0xFF) << 0)

/**
 * @brief DAQ duty cycle ratio settings.
 * @details Specified settings for duty cycle ratio of DAQ Click driver.
 */
#define DAQ_DC_RATIO_IDLE_TIME_MSK			(0xFF << 0)
#define DAQ_DC_RATIO_IDLE_TIME(x)			(((x) & 0xFF) << 0)

/**
 * @brief DAQ sync reset settings.
 * @details Specified settings for sync reset of DAQ Click driver.
 */
#define DAQ_SYNC_RST_SPI_STARTB_MSK			(0x1 << 7)
#define DAQ_SYNC_RST_SPI_STARTB(x)			(((x) & 0x1) << 7)
#define DAQ_SYNC_RST_SYNCOUT_EDGE_MSK		(0x1 << 6)
#define DAQ_SYNC_RST_SYNCOUT_EDGE(x)		(((x) & 0x1) << 6)
#define DAQ_SYNC_RST_GPIO_START_EN_MSK		(0x1 << 3)
#define DAQ_SYNC_RST_GPIO_START_EN(x)		(((x) & 0x1) << 3)
#define DAQ_SYNC_RST_SPI_RESET_MSK			(0x3 << 0)
#define DAQ_SYNC_RST_SPI_RESET(x)			(((x) & 0x3) << 0)

/**
 * @brief DAQ gpio control settings.
 * @details Specified settings for gpio control of DAQ Click driver.
 */
#define DAQ_GPIO_CNTRL_UGPIO_EN_MSK			(0x1 << 7)
#define DAQ_GPIO_CNTRL_UGPIO_EN(x)			(((x) & 0x1) << 7)
#define DAQ_GPIO_CNTRL_GPIO2_OD_EN_MSK		(0x1 << 6)
#define DAQ_GPIO_CNTRL_GPIO2_OD_EN(x)		(((x) & 0x1) << 6)
#define DAQ_GPIO_CNTRL_GPIO1_OD_EN_MSK		(0x1 << 5)
#define DAQ_GPIO_CNTRL_GPIO1_OD_EN(x)		(((x) & 0x1) << 5)
#define DAQ_GPIO_CNTRL_GPIO0_OD_EN_MSK		(0x1 << 4)
#define DAQ_GPIO_CNTRL_GPIO0_OD_EN(x)		(((x) & 0x1) << 4)
#define DAQ_GPIO_CNTRL_ALL_GPIOS_OD_EN_MSK	(0x7 << 4)
#define DAQ_GPIO_CNTRL_ALL_GPIOS_OD_EN(x)	(((x) & 0x7) << 4)
#define DAQ_GPIO_CNTRL_GPIO3_OP_EN_MSK		(0x1 << 3)
#define DAQ_GPIO_CNTRL_GPIO3_OP_EN(x)		(((x) & 0x1) << 3)
#define DAQ_GPIO_CNTRL_GPIO2_OP_EN_MSK		(0x1 << 2)
#define DAQ_GPIO_CNTRL_GPIO2_OP_EN(x)		(((x) & 0x1) << 2)
#define DAQ_GPIO_CNTRL_GPIO1_OP_EN_MSK		(0x1 << 1)
#define DAQ_GPIO_CNTRL_GPIO1_OP_EN(x)		(((x) & 0x1) << 1)
#define DAQ_GPIO_CNTRL_GPIO0_OP_EN_MSK		(0x1 << 0)
#define DAQ_GPIO_CNTRL_GPIO0_OP_EN(x)		(((x) & 0x1) << 0)
#define DAQ_GPIO_CNTRL_ALL_GPIOS_OP_EN_MSK	(0xF << 0)
#define DAQ_GPIO_CNTRL_ALL_GPIOS_OP_EN(x)	(((x) & 0xF) << 0)
#define DAQ_GPIO_WRITE_3_MSK				(0x1 << 3)
#define DAQ_GPIO_WRITE_3(x)					(((x) & 0x1) << 3)
#define DAQ_GPIO_WRITE_2_MSK				(0x1 << 2)
#define DAQ_GPIO_WRITE_2(x)					(((x) & 0x1) << 2)
#define DAQ_GPIO_WRITE_1_MSK				(0x1 << 1)
#define DAQ_GPIO_WRITE_1(x)					(((x) & 0x1) << 1)
#define DAQ_GPIO_WRITE_0_MSK				(0x1 << 0)
#define DAQ_GPIO_WRITE_0(x)					(((x) & 0x1) << 0)
#define DAQ_GPIO_WRITE_ALL_MSK				(0xF << 0)
#define DAQ_GPIO_WRITE_ALL(x)				(((x) & 0xF))
#define DAQ_GPIO_READ_3_MSK					(0x1 << 3)
#define DAQ_GPIO_READ_2_MSK					(0x1 << 2)
#define DAQ_GPIO_READ_1_MSK					(0x1 << 1)
#define DAQ_GPIO_READ_0_MSK					(0x1 << 0)
#define DAQ_GPIO_READ_ALL_MSK				(0xF << 0)

/**
 * @brief DAQ offset settings.
 * @details Specified settings for offset of DAQ Click driver.
 */
#define DAQ_OFFSET_HI_MSK					(0xFF << 0)
#define	DAQ_OFFSET_HI(x)					(((x) & 0xFF) << 0)
#define DAQ_OFFSET_MID_MSK					(0xFF << 0)
#define	DAQ_OFFSET_MID(x)					(((x) & 0xFF) << 0)
#define DAQ_OFFSET_LO_MSK					(0xFF << 0)
#define	DAQ_OFFSET_LO(x)					(((x) & 0xFF) << 0)

/**
 * @brief DAQ gain settings.
 * @details Specified settings for gain of DAQ Click driver.
 */
#define DAQ_GAIN_HI_MSK						(0xFF << 0)
#define	DAQ_GAIN_HI(x)						(((x) & 0xFF) << 0)
#define DAQ_GAIN_MID_MSK					(0xFF << 0)
#define	DAQ_GAIN_MID(x)						(((x) & 0xFF) << 0)
#define DAQ_GAIN_LOW_MSK					(0xFF << 0)
#define	DAQ_GAIN_LOW(x)						(((x) & 0xFF) << 0)

/**
 * @brief DAQ spi diagnostic enable settings.
 * @details Specified settings for spi diagnostic enable of DAQ Click driver.
 */
#define DAQ_SPI_DIAG_ERR_SPI_IGNORE_MSK		(0x1 << 4)
#define DAQ_SPI_DIAG_ERR_SPI_IGNORE(x)		(((x) & 0x1) << 4)
#define DAQ_SPI_DIAG_ERR_SPI_CLK_CNT_MSK	(0x1 << 3)
#define DAQ_SPI_DIAG_ERR_SPI_CLK_CNT(x)		(((x) & 0x1) << 3)
#define DAQ_SPI_DIAG_ERR_SPI_RD_MSK			(0x1 << 2)
#define DAQ_SPI_DIAG_ERR_SPI_RD(x)			(((x) & 0x1) << 2)
#define DAQ_SPI_DIAG_ERR_SPI_WR_MSK			(0x1 << 1)
#define DAQ_SPI_DIAG_ERR_SPI_WR(x)			(((x) & 0x1) << 1)

/**
 * @brief DAQ adc diagnostic enable settings.
 * @details Specified settings for adc diagnostic enable of DAQ Click driver.
 */
#define DAQ_ADC_DIAG_ERR_DLDO_PSM_MSK		(0x1 << 5)
#define DAQ_ADC_DIAG_ERR_DLDO_PSM(x)		(((x) & 0x1) << 5)
#define DAQ_ADC_DIAG_ERR_ALDO_PSM_MSK		(0x1 << 4)
#define DAQ_ADC_DIAG_ERR_ALDO_PSM(x)		(((x) & 0x1) << 4)
#define DAQ_ADC_DIAG_ERR_FILT_SAT_MSK		(0x1 << 2)
#define DAQ_ADC_DIAG_ERR_FILT_SAT(x)			(((x) & 0x1) << 2)
#define DAQ_ADC_DIAG_ERR_FILT_NOT_SET_MSK	(0x1 << 1)
#define DAQ_ADC_DIAG_ERR_FILT_NOT_SET(x)		(((x) & 0x1) << 1)
#define DAQ_ADC_DIAG_ERR_EXT_CLK_QUAL_MSK	(0x1 << 0)
#define DAQ_ADC_DIAG_ERR_EXT_CLK_QUAL(x)	(((x) & 0x1) << 0)

/**
 * @brief DAQ diagnostic enable settings.
 * @details Specified settings for diagnostic enable of DAQ Click driver.
 */
#define DAQ_DIG_DIAG_ERR_MEMMAP_CRC_MSK		(0x1 << 4)
#define DAQ_DIG_DIAG_ERR_MEMMAP_CRC(x)		(((x) & 0x1) << 4)
#define DAQ_DIG_DIAG_ERR_RAM_CRC_MSK		(0x1 << 3)
#define DAQ_DIG_DIAG_ERR_RAM_CRC(x)			(((x) & 0x1) << 3)
#define DAQ_DIG_DIAG_ERR_FUSE_CRC_MSK		(0x1 << 2)
#define DAQ_DIG_DIAG_ERR_FUSE_CRC(x)		(((x) & 0x1) << 2)
#define DAQ_DIG_DIAG_FREQ_COUNT_EN_MSK		(0x1 << 0)
#define DAQ_DIG_DIAG_FREQ_COUNT_EN(x)		(((x) & 0x1) << 0)

/**
 * @brief DAQ master status.
 * @details Specified master status of DAQ Click driver.
 */
#define DAQ_MASTER_ERROR_MSK				(0x1 << 7)
#define DAQ_MASTER_ADC_ERROR_MSK			(0x1 << 6)
#define DAQ_MASTER_DIG_ERROR_MSK			(0x1 << 5)
#define DAQ_MASTER_DIG_ERR_EXT_CLK_MSK		(0x1 << 4)
#define DAQ_MASTER_FILT_SAT_MSK				(0x1 << 3)
#define DAQ_MASTER_FILT_NOT_SET_MSK			(0x1 << 2)
#define DAQ_MASTER_SPI_ERROR_MSK			(0x1 << 1)
#define DAQ_MASTER_POR_FLAG_MSK				(0x1 << 0)

/* DAQ_REG_SPI_DIAG_STATUS */
/**
 * @brief DAQ spi status.
 * @details Specified spi status of DAQ Click driver.
 */
#define DAQ_SPI_IGNORE_ERROR_MSK			(0x1 << 4)
#define DAQ_SPI_IGNORE_ERROR_CLR(x)			(((x) & 0x1) << 4)
#define DAQ_SPI_CLK_CNT_ERROR_MSK			(0x1 << 3)
#define DAQ_SPI_READ_ERROR_MSK				(0x1 << 2)
#define DAQ_SPI_READ_ERROR_CLR(x)			(((x) & 0x1) << 2)
#define DAQ_SPI_WRITE_ERROR_MSK				(0x1 << 1)
#define DAQ_SPI_WRITE_ERROR_CLR(x)			(((x) & 0x1) << 1)
#define DAQ_SPI_CRC_ERROR_MSK				(0x1 << 0)
#define DAQ_SPI_CRC_ERROR_CLR(x)			(((x) & 0x1) << 0)

/**
 * @brief DAQ adc status.
 * @details Specified adc status of DAQ Click driver.
 */
#define DAQ_ADC_DLDO_PSM_ERROR_MSK			(0x1 << 5)
#define DAQ_ADC_ALDO_PSM_ERROR_MSK			(0x1 << 4)
#define DAQ_ADC_REF_DET_ERROR_MSK           (0x1 << 3)
#define DAQ_ADC_FILT_SAT_MSK				(0x1 << 2)
#define DAQ_ADC_FILT_NOT_SET_MSK			(0x1 << 1)
#define DAQ_ADC_DIG_ERR_EXT_CLK_MSK			(0x1 << 0)

/**
 * @brief DAQ diagnostic status.
 * @details Specified diagnostic status of DAQ Click driver.
 */
#define DAQ_DIG_MEMMAP_CRC_ERROR_MSK		(0x1 << 4)
#define DAQ_DIG_RAM_CRC_ERROR_MSK			(0x1 << 3)
#define DAQ_DIG_FUS_CRC_ERROR_MSK			(0x1 << 2)

/**
 * @brief DAQ mclk counter settings.
 * @details Specified settings for mclk counter of DAQ Click driver.
 */
#define DAQ_MCLK_COUNTER_MSK				(0xFF << 0)
#define	DAQ_MCLK_COUNTER(x)					(((x) & 0xFF) << 0)

/**
 * @brief DAQ coefficient control settings.
 * @details Specified settings for coefficient control of DAQ Click driver.
 */
#define DAQ_COEF_CONTROL_COEFFACCESSEN_MSK	(0x1 << 7)
#define DAQ_COEF_CONTROL_COEFFACCESSEN(x)	(((x) & 0x1) << 7)
#define DAQ_COEF_CONTROL_COEFFWRITEEN_MSK	(0x1 << 6)
#define DAQ_COEF_CONTROL_COEFFWRITEEN(x)	(((x) & 0x1) << 6)
#define DAQ_COEF_CONTROL_COEFFADDR_MSK		(0x3F << 5)
#define DAQ_COEF_CONTROL_COEFFADDR(x)		(((x) & 0x3F) << 5)

/**
 * @brief DAQ coefficient data settings.
 * @details Specified settings for coefficient data of DAQ Click driver.
 */
#define DAQ_COEFF_DATA_USERCOEFFEN_MSK		(0x1 << 23)
#define	DAQ_COEFF_DATA_USERCOEFFEN(x)		(((x) & 0x1) << 23)
#define DAQ_COEFF_DATA_COEFFDATA_MSK		(0x7FFFFF << 22)
#define	DAQ_COEFF_DATA_COEFFDATA(x)			(((x) & 0x7FFFFF) << 22)

/**
 * @brief DAQ access settings.
 * @details Specified settings for access of DAQ Click driver.
 */
#define DAQ_ACCESS_KEY_MSK					(0xFF << 0)
#define	DAQ_ACCESS_KEY(x)					(((x) & 0xFF) << 0)
#define DAQ_ACCESS_KEY_CHECK_MSK			(0x1 << 0)

/**
 * @brief DAQ resolution settings.
 * @details Specified settings for resolution of DAQ Click driver.
 */
#define DAQ_RESOLUTION                      8388608

/**
 * @brief DAQ power clock values.
 * @details Specified values for power clock of DAQ Click driver.
 */
enum daq_power_mode
{
    DAQ_ECO                                 = 0,
    DAQ_MEDIAN                              = 2,
    DAQ_FAST                                = 3,
};

/**
 * @brief DAQ mclk divider values.
 * @details Specified values for mclk divider of DAQ Click driver.
 */
enum daq_mclk_div
{
    DAQ_MCLK_DIV_16                         = 0,
    DAQ_MCLK_DIV_8                          = 1,
    DAQ_MCLK_DIV_4                          = 2,
    DAQ_MCLK_DIV_2                          = 3
};

/**
 * @brief DAQ conversion mode values.
 * @details Specified values for conversion mode of DAQ Click driver.
 */
enum daq_conv_mode
{
    DAQ_CONV_CONTINUOUS                     = 0,
    DAQ_CONV_ONE_SHOT                       = 1,
    DAQ_CONV_SINGLE                         = 2,
    DAQ_CONV_PERIODIC                       = 3,
    DAQ_CONV_STANDBY                        = 4
};

/**
 * @brief DAQ conversion length values.
 * @details Specified values for conversion length of DAQ Click driver.
 */
enum daq_conv_len
{
    DAQ_CONV_24BIT                          = 0,
    DAQ_CONV_16BIT                          = 1
};

/**
 * @brief DAQ data ready enable values.
 * @details Specified values for data ready enable of DAQ Click driver.
 */
enum daq_rdy_dout
{
    DAQ_RDY_DOUT_EN,
    DAQ_RDY_DOUT_DIS
};

/**
 * @brief DAQ conversion mux values.
 * @details Specified values for conversion mux of DAQ Click driver.
 */
enum daq_conv_diag_mux
{
    DAQ_TEMP_SENSOR                         = 0x0,
    DAQ_AIN_SHORT                           = 0x8,
    DAQ_POSITIVE_FS                         = 0x9,
    DAQ_NEGATIVE_FS                         = 0xA
};

/**
 * @brief DAQ crc selection values.
 * @details Specified values for crc selection of DAQ Click driver.
 */
enum daq_crc_sel
{
    DAQ_CRC,
    DAQ_XOR,
    DAQ_NO_CRC
};

/**
 * @brief DAQ filter type selection values.
 * @details Specified values for filter type selection
 *           of DAQ Click driver.
 */
enum daq_filter_type
{
    DAQ_SINC5			                    = 0,
    DAQ_SINC5_DECx8		                    = 1,
    DAQ_SINC5_DECx16	                    = 2,
    DAQ_SINC3			                    = 3,
    DAQ_FIR				                    = 4
};

/**
 * @brief DAQ Decimation ratios for SINC5 and FIR values.
 * @details Specified values for decimation ratios for 
 *          SINC5 and FIR of DAQ Click driver.
 */
enum daq_sinc5_fir_decimate
{
    DAQ_SINC5_FIR_DECx32	                = 0,
    DAQ_SINC5_FIR_DECx64	                = 1,
    DAQ_SINC5_FIR_DECx128	                = 2,
    DAQ_SINC5_FIR_DECx256	                = 3,
    DAQ_SINC5_FIR_DECx512	                = 4,
    DAQ_SINC5_FIR_DECx1024	                = 5
};

/**
 * @brief DAQ power values.
 * @details Specified values for power of DAQ Click driver.
 */
enum daq_sleep_wake 
{
    DAQ_SLEEP                               = 1,
    DAQ_WAKE                                = 0
};

/**
 * @brief DAQ AIN precharge values.
 * @details Specified values for AIN precharge of DAQ Click driver.
 */
enum daq_ain_precharge 
{
    DAQ_AIN_ENABLED                         = 0,
    DAQ_AIN_DISABLED                        = 1
};

/**
 * @brief DAQ REF buffer values.
 * @details Specified values for REF buffer of DAQ Click driver.
 */
enum daq_ref_buffer 
{
	DAQ_BUF_ENABLED                         = 0,
	DAQ_BUF_DISABLED                        = 1,
	DAQ_BUF_FULL_BUFFER_ON                  = 2
};

/**
 * @brief DAQ VCM output voltage values.
 * @details Specified values for VCM output 
 *          voltage of DAQ Click driver.
 */
enum daq_vcm_out 
{
    DAQ_VCM_HALF_VCC	                    = 0,
    DAQ_VCM_2_5V		                    = 1,
    DAQ_VCM_2_05V   	                    = 2,
    DAQ_VCM_1_9V		                    = 3,
    DAQ_VCM_1_65V		                    = 4,
    DAQ_VCM_1_1V		                    = 5,
    DAQ_VCM_0_9V		                    = 6,
    DAQ_VCM_OFF  		                    = 7
};

/**
 * @brief DAQ global gpio values.
 * @details Specified values for global gpio of DAQ Click driver.
 */
enum daq_gobal_gpio_enable 
{
    DAQ_GLOBAL_GPIO_ENABLE		            = 1,
    DAQ_GLOBAL_GPIO_DISABLE		            = 0
};

/**
 * @brief DAQ global gpio numbering values.
 * @details Specified values for global gpio numbering
 *          of DAQ Click driver.
 */
enum daq_gpios 
{
    DAQ_GPIO0					            = 0,
    DAQ_GPIO1					            = 1,
    DAQ_GPIO2					            = 2,
    DAQ_GPIO3					            = 3,
    DAQ_ALL_GPIOS				            = 4
};

/**
 * @brief DAQ gpio state values.
 * @details Specified values for gpio state of DAQ Click driver.
 */
enum daq_gpio_write
{
    DAQ_GPIO_LOW		                    = 0,
    DAQ_GPIO_HIGH			                = 1
};

/**
 * @brief DAQ gpio output type values.
 * @details Specified values for gpio output type of DAQ Click driver.
 */
enum daq_gpio_output_type
{
    DAQ_GPIO_STRONG_DRIVER		            = 0,
    DAQ_GPIO_OPEN_DRAIN			            = 1
};

/**
 * @brief DAQ continuous adc read enable values.
 * @details Specified values for continuous adc read enable
 *          of DAQ Click driver.
 */
enum daq_continuous_read 
{
    DAQ_CONTINUOUS_READ_ENABLE              = 1,
    DAQ_CONTINUOUS_READ_DISABLE             = 0
};

/**
 * @brief DAQ GAIN configuration values.
 * @details Specified values for GAIN configuration of DAQ Click driver.
 */
typedef enum  
{
    DAQ_GAIN_12p603                         = 6,/*< Range: +-12.603*/
    DAQ_GAIN_6p302                          = 5,/*< Range: +-6.302*/
    DAQ_GAIN_3p151                          = 4,/*< Range: +-3.151*/
    DAQ_GAIN_1p575                          = 3,/*< Range: +-1.575*/
    DAQ_GAIN_p788                           = 2,/*< Range: +-0.788*/
    DAQ_GAIN_p394                           = 1,/*< Range: +-0.394*/
    DAQ_GAIN_p197                           = 0 /*< Range: +-0.197*/
}daq_gain;

/*! @} */ // daq_set

/**
 * @defgroup daq_map DAQ MikroBUS Map
 * @brief MikroBUS pin mapping of DAQ Click driver.
 */

/**
 * @addtogroup daq_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DAQ Click to the selected MikroBUS.
 */
#define DAQ_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.io3 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rdy = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // daq_map
/*! @} */ // daq

/**
 * @brief DAQ Click context object.
 * @details Context object definition of DAQ Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  rst;         /**< Reset. */

    // Input pins
    digital_in_t  rdy;          /**< Data ready. */
    // I/O
    digital_out_t  io3;         /**< I/O programmable. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */
    
    float gain;                 /**< Gain resolution. */

} daq_t;

/**
 * @brief DAQ Click configuration object.
 * @details Configuration object definition of DAQ Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;   /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;   /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;    /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;     /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  rst;    /**< Reset. */
    pin_name_t  io3;    /**< I/O programmable. */
    pin_name_t  rdy;    /**< Data ready. */

    // static variable
    uint32_t                           spi_speed;   /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;    /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity; /**< Chip select pin polarity. */
    //IO3 direction
    uint8_t io3direction;/**< IO3 pin direction 0->output, 1->input. */

} daq_cfg_t;

/**
 * @brief DAQ Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   DAQ_OK = 0,
   DAQ_ERROR = -1

} daq_return_value_t;

/*!
 * @addtogroup daq DAQ Click Driver
 * @brief API for configuring and manipulating DAQ Click driver.
 * @{
 */

/**
 * @brief DAQ configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #daq_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void daq_cfg_setup ( daq_cfg_t *cfg );

/**
 * @brief DAQ initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #daq_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #daq_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t daq_init ( daq_t *ctx, daq_cfg_t *cfg );

/**
 * @brief DAQ default configuration function.
 * @details This function executes a default configuration of DAQ
 * click board.
 * @param[in] ctx : Click context object.
 * See #daq_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t daq_default_cfg ( daq_t *ctx );

/**
 * @brief DAQ data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #daq_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t daq_generic_write ( daq_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief DAQ byte writing function.
 * @details This function writes a byte to the selected register.
 * @param[in] ctx : Click context object.
 * See #daq_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t daq_byte_write ( daq_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief DAQ byte writing function with mask.
 * @details This function writes a byte to the selected register by using mask.
 * @param[in] ctx : Click context object.
 * See #daq_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] mask : Mask.
 * @param[in] data_in : Register data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t daq_mask_write ( daq_t *ctx, uint8_t reg, uint8_t mask, uint8_t data_in );

/**
 * @brief DAQ data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #daq_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t daq_generic_read ( daq_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief DAQ byte reading function.
 * @details This function reads a byte from the selected register.
 * @param[in] ctx : Click context object.
 * See #daq_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t daq_byte_read ( daq_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief DAQ byte reading function with mask.
 * @details This function reads a byte from the selected register by using mask.
 * @param[in] ctx : Click context object.
 * See #daq_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] mask : Mask.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t daq_mask_read ( daq_t *ctx, uint8_t reg, uint8_t mask, uint8_t *data_out );

/**
 * @brief DAQ reading function.
 * @details This function reads a desired number of data bytes by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #daq_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t daq_raw_read ( daq_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief Reset function.
 * @details This function resets device by toggling rst pin.
 * @param[in] ctx : Click context object.
 * See #daq_t object definition for detailed explanation.
 * @return Nothing.
 */
void daq_reset ( daq_t *ctx );

/**
 * @brief Get data ready pin.
 * @details This function reads data ready pin state.
 * @param[in] ctx : Click context object.
 * See #daq_t object definition for detailed explanation.
 * @return Pin state.
 */
uint8_t daq_data_ready( daq_t *ctx );

/**
 * @brief Set io3 pin.
 * @details This function sets io3 pin state.
 * @param[in] ctx : Click context object.
 * See #daq_t object definition for detailed explanation.
 * @param[in] state : Pin state to set.
 * @return Nothing.
 */
void daq_set_io3 ( daq_t *ctx, uint8_t state );

/**
 * @brief Get io3 pin.
 * @details This function reads io3 pin state.
 * @param[in] ctx : Click context object.
 * See #daq_t object definition for detailed explanation.
 * @return Pin state.
 */
uint8_t daq_get_iot3 ( daq_t *ctx );

/**
 * @brief Set gain range.
 * @details This function sets gain pins and with that sets ADC range.
 * @param[in] ctx : Click context object.
 * See #daq_t object definition for detailed explanation.
 * @param[in] gain : Gain range.
 * See #daq_gain enum definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t daq_set_gain ( daq_t *ctx, daq_gain gain );

/**
 * @brief Reading adc data.
 * @details This function reads a ADC_DATA register using it with @b DAQ_CONV_ONE_SHOT conversion.
 * @param[in] ctx : Click context object.
 * See #daq_t object definition for detailed explanation.
 * @param[out] adc_data : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t daq_read_data ( daq_t *ctx, int32_t *adc_data );

/**
 * @brief Convert data from raw ADC to voltage.
 * @details This function calculates voltage data from raw adc_data and gain value from @b ctx object.
 * @param[in] ctx : Click context object.
 * See #daq_t object definition for detailed explanation.
 * @param[in] adc_data : ADC data from device.
 * @param[out] voltage : Calculated data in V.
 * @return Nothing.
 */
void daq_calculate_voltage ( daq_t *ctx, int32_t adc_data, float *voltage );

#ifdef __cplusplus
}
#endif
#endif // DAQ_H

/*! @} */ // daq

// ------------------------------------------------------------------------ END
