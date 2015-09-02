/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013,2014 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "config/stm32plus.h"

#if defined(STM32PLUS_F0) and defined(STM32PLUS_F0_91)

#include "config/can.h"


using namespace stm32plus;


// static initialisers for the hack that forces the IRQ handlers to be linked

template<> CANInterruptFeatureEnabler<1>::FPTR CANInterruptFeatureEnabler<1>::_forceLinkageRX0=nullptr;

#if defined(USE_CAN_INTERRUPT)

extern "C" {

	void __attribute__ ((interrupt("IRQ"))) CEC_CAN_IRQHandler(void)
    {
      CANInterruptFeature<1>::_canInstance->CANInterruptEventSender.raiseEvent(CANEventType::EVENT_RECEIVE_RX0);
      __DSB();      // prevent erroneous recall of this handler due to delayed memory write
    }
}

#endif

#endif // extern "C"

