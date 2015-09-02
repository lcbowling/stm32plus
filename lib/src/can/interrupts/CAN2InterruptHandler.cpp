/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013,2014 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "config/stm32plus.h"

#if (defined(STM32PLUS_F1) and defined(STM32PLUS_F1_CL)) and !defined(STM32PLUS_F0)

#include "config/can.h"


using namespace stm32plus;


// static initialisers for the hack that forces the IRQ handlers to be linked

template<> CANInterruptFeatureEnabler<2>::FPTR CANInterruptFeatureEnabler<2>::_forceLinkageRX=nullptr;
template<> CANInterruptFeatureEnabler<2>::FPTR CANInterruptFeatureEnabler<2>::_forceLinkageTX=nullptr;

#if defined(USE_CAN2_INTERRUPT)

extern "C" {

	void __attribute__ ((interrupt("IRQ"))) CAN2_RX0_IRQHandler(void)
    {
      CANInterruptFeature<1>::_canInstance->CANInterruptEventSender.raiseEvent(CANEventType::EVENT_RECEIVE_RX0);
      __DSB();      // prevent erroneous recall of this handler due to delayed memory write
    }

	void __attribute__ ((interrupt("IRQ"))) CAN2_TX_IRQHandler(void)
    {
      CANInterruptFeature<2>::_canInstance->CANInterruptEventSender.raiseEvent(CANEventType::EVENT_TRANSMIT_TME);
      __DSB();      // prevent erroneous recall of this handler due to delayed memory write
    }

}

#endif

#endif // extern "C"

