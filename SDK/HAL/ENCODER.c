#include "ENCODER.h"

static uint32_t _Encoder_A;
static uint32_t _Encoder_B;
static void (*_SpinEventCB)(int8_t DeltaValue);
static uint8_t _TriggerInterval;

int8_t _delta_value = 0;

void Encoder_Init(Encoder_InitTypeDef *Encoder_InitStructure) {
    _Encoder_A = Encoder_InitStructure->Encoder_A;
    _Encoder_B = Encoder_InitStructure->Encoder_B;
    _SpinEventCB = Encoder_InitStructure->SpinEventCB;
    _TriggerInterval = Encoder_InitStructure->TriggerInterval;
}

void Encoder_Spin() {
    if (!GPIOA_ReadPortPin(_Encoder_A)) {
        if (GPIOA_ReadPortPin(_Encoder_B)) {
            _delta_value = 1;
        } else {
            _delta_value = 2;
        }
    } else if (!GPIOA_ReadPortPin(_Encoder_B)) {
        if (GPIOA_ReadPortPin(_Encoder_A)) {
            _delta_value = 2;
        } else {
            _delta_value = 1;
        }
    }

//    if(_delta_value - old_value > _TriggerInterval){
//        _SpinEventCB(1);
//        old_value = _delta_value;
//    }
//    else if(old_value - _delta_value > _TriggerInterval){
//        _SpinEventCB(-1);
//        old_value = _delta_value;
//    }
//
////    if ((_delta_value % _TriggerInterval) == 0 && _delta_value != 0) {
//        _SpinEventCB(_delta_value);
//        _delta_value %= 120;
//        old_value = 0;
////    }

}
