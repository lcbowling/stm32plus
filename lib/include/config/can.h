#pragma once

/**
 * @file
 * This file provides access to the I2C peripheral. All the peripherals are exposed with multiple pin configurations
 * available. DMA and interrupt-driven access are both supported.
 */

// CAN depends on rcc, gpio, event, interrupts, dma, timing

#include "config/rcc.h"
#include "config/gpio.h"
#include "config/event.h"
#include "config/timing.h"

// device-specific pin initialiser

#if defined(STM32PLUS_F4)

  #include "can/f4/CANAlternateFunctionMapper.h"
  #include "can/f4/CANPinInitialiser.h"

#endif

#include "can/CANDeviceIo.h"

// generic peripheral includes

#include "can/CANEventSource.h"
#include "can/CAN.h"
#include "can/CANPeripheral.h"

// generic feature includes

#include "can/features/CANFeatureBase.h"
#include "can/features/CANInterruptFeature.h"

// generic peripheral includes

#include "can/CAN1.h"

// enable all interrupts

#define USE_CAN1_INTERRUPT
#define USE_CAN2_INTERRUPT

// device specific includes



