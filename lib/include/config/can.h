#pragma once

#if !defined(STM32PLUS_F0) or defined(STM32PLUS_F0_91)
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

#if defined(STM32PLUS_F0) and defined(STM32PLUS_F0_91)

#include "can/f0/CANAlternateFunctionMapper.h"
#include "can/f0/CANPinInitialiser.h"

#elif defined(STM32PLUS_F4)

  #include "can/f4/CANAlternateFunctionMapper.h"
  #include "can/f4/CANPinInitialiser.h"

#elif defined(STM32PLUS_F1)
  #include "can/f1/CANPinInitialiser.h"
#endif

// generic peripheral includes

#include "can/CANEventSource.h"
#include "can/CAN.h"
#include "can/CANPeripheral.h"

// generic feature includes

#include "can/features/CANFeatureBase.h"

#if defined(STM32PLUS_F0) and defined(STM32PLUS_F0_91)
#include "can/features/f0/CANInterruptFeature.h"
#elif defined(STM32PLUS_F4)
#include "can/features/f4/CANInterruptFeature.h"
#elif defined(STM32PLUS_F1)
#include "can/features/f1/CANInterruptFeature.h"
#endif

// generic peripheral includes

#if defined(STM32PLUS_F0) and defined(STM32PLUS_F0_91)
  #include "can/f0/CAN.h"
#elif defined(STM32PLUS_F4)
  #include "can/f4/CAN1.h"
  #include "can/f4/CAN2.h"
#elif defined(STM32PLUS_F1)
  #include "can/f1/CAN1.h"
  #include "can/f1/CAN2.h"
#endif

// enable all interrupts

#define USE_CAN_INTERRUPT
#define USE_CAN1_INTERRUPT
#define USE_CAN2_INTERRUPT

// device specific includes


#endif
