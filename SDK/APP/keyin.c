#include "config.h"
#include "keyin.h"
#include "protocol.h"
#include "hiddev.h"
#include "usercfg.h"

static uint8_t Keymap = 0x00;
static uint8_t Keymap_o = 0x00;

uint8_t Key_x_encnt = 0;
uint8_t Key_c_encnt = 0;
uint8_t Key_v_encnt = 0;
uint8_t Key_ctrl_encnt = 0;
uint8_t Key_enter_encnt = 0;
uint8_t Key_rbt_encnt = 0;
uint8_t Key_rl_encnt = 0;
uint8_t Key_rr_encnt = 0;

uint8_t Key_x_decnt = 0;
uint8_t Key_c_decnt = 0;
uint8_t Key_v_decnt = 0;
uint8_t Key_ctrl_decnt = 0;
uint8_t Key_enter_decnt = 0;
uint8_t Key_rbt_decnt = 0;
uint8_t Key_rl_decnt = 0;
uint8_t Key_rr_decnt = 0;

uint32_t Key_x_tricnt = 0;
uint32_t Key_c_tricnt = 0;
uint32_t Key_v_tricnt = 0;
uint32_t Key_ctrl_tricnt = 0;
uint32_t Key_enter_tricnt = 0;
uint32_t Key_rbt_tricnt = 0;
uint32_t Key_rl_tricnt = 0;
uint32_t Key_rr_tricnt = 0;

uint8_t enco_left = 0;
uint8_t enco_right = 0;

uint8_t enco_finish_flg = TRUE;
uint8_t finish_upload = TRUE;

static uint8_t TMOS_Keys_Debounce_ID = INVALID_TASK_ID;
static uint16_t TMOS_Keys_Debounce(uint8_t task_id, uint16_t events);

static uint8_t TMOS_Enco_Debounce_ID = INVALID_TASK_ID;
static uint16_t TMOS_Enco_Debounce(uint8_t task_id, uint16_t events);

static uint8_t TMOS_Keys_TaskManager_ID = INVALID_TASK_ID;
static uint16_t TMOS_Keys_TaskManager(uint8_t task_id, uint16_t events);

static uint8_t TMOS_Keys_TransMacro_ID = INVALID_TASK_ID;
static uint16_t TMOS_Keys_TransMacro(uint8_t task_id, uint16_t events);

void Keyin_Init() {

    // KEY INIT
    GPIOA_ModeCfg(KEY_LEFT_CTRL | ROLLER_BUTTON | ROLLER_A | ROLLER_B,
            GPIO_ModeIN_PU);
    GPIOB_ModeCfg(KEY_RIGHT_ENTER | KEY_X | KEY_C | KEY_V, GPIO_ModeIN_PU);

    TMOS_Keys_Debounce_ID = TMOS_ProcessEventRegister(TMOS_Keys_Debounce);
    TMOS_Enco_Debounce_ID = TMOS_ProcessEventRegister(TMOS_Enco_Debounce);
    TMOS_Keys_TaskManager_ID = TMOS_ProcessEventRegister(TMOS_Keys_TaskManager);
    TMOS_Keys_TransMacro_ID = TMOS_ProcessEventRegister(TMOS_Keys_TransMacro);

    tmos_start_reload_task(TMOS_Keys_Debounce_ID, 0x0001, 4);
    tmos_start_reload_task(TMOS_Enco_Debounce_ID, 0x0001, 4);
    tmos_start_reload_task(TMOS_Keys_TaskManager_ID, 0x001, 8);
    tmos_start_reload_task(TMOS_Keys_TransMacro_ID, 0x0001, 8);
}

uint16_t TMOS_Keys_Debounce(uint8_t task_id, uint16_t events) {

    static uint8_t dbc_push_cnt_x = 0;
    static uint8_t dbc_release_cnt_x = 0;

    static uint8_t dbc_push_cnt_c = 0;
    static uint8_t dbc_release_cnt_c = 0;

    static uint8_t dbc_push_cnt_v = 0;
    static uint8_t dbc_release_cnt_v = 0;

    static uint8_t dbc_push_cnt_ctrl = 0;
    static uint8_t dbc_release_cnt_ctrl = 0;

    static uint8_t dbc_push_cnt_enter = 0;
    static uint8_t dbc_release_cnt_enter = 0;

    static uint8_t dbc_push_cnt_rbt = 0;
    static uint8_t dbc_release_cnt_rbt = 0;

    if (!GPIOB_ReadPortPin(KEY_X)) {
        dbc_release_cnt_x = 0;

        if (dbc_push_cnt_x == UserCfg_RAM.KeyIn_Debouncing_DelayCircle_Cnt) {

            Keymap |= (0x01 << MAP_X);

            dbc_push_cnt_x = 0;
        } else {
            dbc_push_cnt_x++;
        }

    } else {
        dbc_push_cnt_x = 0;

        if (dbc_release_cnt_x == UserCfg_RAM.KeyIn_Debouncing_DelayCircle_Cnt) {

            Keymap &= ~(0x01 << MAP_X);

            dbc_release_cnt_x = 0;
        } else {
            dbc_release_cnt_x++;
        }
    }

    if (!GPIOB_ReadPortPin(KEY_C)) {
        dbc_release_cnt_c = 0;

        if (dbc_push_cnt_c == UserCfg_RAM.KeyIn_Debouncing_DelayCircle_Cnt) {

            Keymap |= (0x01 << MAP_C);

            dbc_push_cnt_c = 0;
        } else {
            dbc_push_cnt_c++;
        }

    } else {
        dbc_push_cnt_c = 0;

        if (dbc_release_cnt_c == UserCfg_RAM.KeyIn_Debouncing_DelayCircle_Cnt) {

            Keymap &= ~(0x01 << MAP_C);

            dbc_release_cnt_c = 0;
        } else {
            dbc_release_cnt_c++;
        }
    }

    if (!GPIOB_ReadPortPin(KEY_V)) {
        dbc_release_cnt_v = 0;

        if (dbc_push_cnt_v == UserCfg_RAM.KeyIn_Debouncing_DelayCircle_Cnt) {
            Keymap |= (0x01 << MAP_V);
            dbc_push_cnt_v = 0;
        } else {
            dbc_push_cnt_v++;
        }
    } else {
        dbc_push_cnt_v = 0;

        if (dbc_release_cnt_v == UserCfg_RAM.KeyIn_Debouncing_DelayCircle_Cnt) {
            Keymap &= ~(0x01 << MAP_V);
            dbc_release_cnt_v = 0;
        } else {
            dbc_release_cnt_v++;
        }
    }

    if (!GPIOA_ReadPortPin(KEY_LEFT_CTRL)) {
        dbc_release_cnt_ctrl = 0;

        if (dbc_push_cnt_ctrl == UserCfg_RAM.KeyIn_Debouncing_DelayCircle_Cnt) {
            Keymap |= (0x01 << MAP_CTRL);
            dbc_push_cnt_ctrl = 0;
        } else {
            dbc_push_cnt_ctrl++;
        }
    } else {
        dbc_push_cnt_ctrl = 0;

        if (dbc_release_cnt_ctrl
                == UserCfg_RAM.KeyIn_Debouncing_DelayCircle_Cnt) {
            Keymap &= ~(0x01 << MAP_CTRL);
            dbc_release_cnt_ctrl = 0;
        } else {
            dbc_release_cnt_ctrl++;
        }
    }

    if (!GPIOB_ReadPortPin(KEY_RIGHT_ENTER)) {
        dbc_release_cnt_enter = 0;

        if (dbc_push_cnt_enter
                == UserCfg_RAM.KeyIn_Debouncing_DelayCircle_Cnt) {
            Keymap |= (0x01 << MAP_ENTER);
            dbc_push_cnt_enter = 0;
        } else {
            dbc_push_cnt_enter++;
        }
    } else {
        dbc_push_cnt_enter = 0;

        if (dbc_release_cnt_enter
                == UserCfg_RAM.KeyIn_Debouncing_DelayCircle_Cnt) {
            Keymap &= ~(0x01 << MAP_ENTER);
            dbc_release_cnt_enter = 0;
        } else {
            dbc_release_cnt_enter++;
        }
    }

    if (!GPIOA_ReadPortPin(ROLLER_BUTTON)) {
        dbc_release_cnt_rbt = 0;

        if (dbc_push_cnt_rbt == UserCfg_RAM.KeyIn_Debouncing_DelayCircle_Cnt) {
            Keymap |= (0x01 << MAP_RBT);
            dbc_push_cnt_rbt = 0;
        } else {
            dbc_push_cnt_rbt++;
        }
    } else {
        dbc_push_cnt_rbt = 0;

        if (dbc_release_cnt_rbt
                == UserCfg_RAM.KeyIn_Debouncing_DelayCircle_Cnt) {
            Keymap &= ~(0x01 << MAP_RBT);
            dbc_release_cnt_rbt = 0;
        } else {
            dbc_release_cnt_rbt++;
        }
    }

    return 0;
}

uint16_t TMOS_Enco_Debounce(uint8_t task_id, uint16_t events) {

    static uint8_t dbc_push_cnt_left = 0;
    static uint8_t dbc_release_cnt_left = 0;

    static uint8_t dbc_push_cnt_right = 0;
    static uint8_t dbc_release_cnt_right = 0;

    if (!GPIOA_ReadPortPin(ROLLER_A)) {
        dbc_release_cnt_left = 0;

        if (dbc_push_cnt_left == UserCfg_RAM.KeyIn_Debouncing_DelayCircle_Cnt) {
            Keymap |= (0x01 << MAP_RL);
            dbc_push_cnt_left = 0;
        } else {
            dbc_push_cnt_left++;
        }
    } else {
        dbc_push_cnt_left = 0;

        if (dbc_release_cnt_left
                == UserCfg_RAM.KeyIn_Debouncing_DelayCircle_Cnt) {
            Keymap &= ~(0x01 << MAP_RL);
            dbc_release_cnt_left = 0;
        } else {
            dbc_release_cnt_left++;
        }
    }

    if (!GPIOA_ReadPortPin(ROLLER_B)) {
        dbc_release_cnt_right = 0;

        if (dbc_push_cnt_right
                == UserCfg_RAM.KeyIn_Debouncing_DelayCircle_Cnt) {
            Keymap |= (0x01 << MAP_RR);
            dbc_push_cnt_right = 0;
        } else {
            dbc_push_cnt_right++;
        }
    } else {
        dbc_push_cnt_right = 0;

        if (dbc_release_cnt_right
                == UserCfg_RAM.KeyIn_Debouncing_DelayCircle_Cnt) {
            Keymap &= ~(0x01 << MAP_RR);
            dbc_release_cnt_right = 0;
        } else {
            dbc_release_cnt_right++;
        }
    }

    return 0;
}

uint16_t TMOS_Keys_TaskManager(uint8_t task_id, uint16_t events) {

    if (((Keymap & (0x01 << MAP_X)) > 0)
            && ((Keymap_o & (0x01 << MAP_X)) == 0)) {
        // push
        Key_x_encnt++;
    } else if (((Keymap & (0x01 << MAP_X)) == 0)
            && ((Keymap_o & (0x01 << MAP_X)) > 0)) {
        // release
        Key_x_decnt++;
    }

    if (((Keymap & (0x01 << MAP_C)) > 0)
            && ((Keymap_o & (0x01 << MAP_C)) == 0)) {
        // push
        Key_c_encnt++;
    } else if (((Keymap & (0x01 << MAP_C)) == 0)
            && ((Keymap_o & (0x01 << MAP_C)) > 0)) {
        // release
        Key_c_decnt++;
    }

    if (((Keymap & (0x01 << MAP_V)) > 0)
            && ((Keymap_o & (0x01 << MAP_V)) == 0)) {
        // push
        Key_v_encnt++;
    } else if (((Keymap & (0x01 << MAP_V)) == 0)
            && ((Keymap_o & (0x01 << MAP_V)) > 0)) {
        // release
        Key_v_decnt++;
    }

    if (((Keymap & (0x01 << MAP_CTRL)) > 0)
            && ((Keymap_o & (0x01 << MAP_CTRL)) == 0)) {
        // push
        Key_ctrl_encnt++;
    } else if (((Keymap & (0x01 << MAP_CTRL)) == 0)
            && ((Keymap_o & (0x01 << MAP_CTRL)) > 0)) {
        // release
        Key_ctrl_decnt++;
    }

    if (((Keymap & (0x01 << MAP_ENTER)) > 0)
            && ((Keymap_o & (0x01 << MAP_ENTER)) == 0)) {
        // push
        Key_enter_encnt++;
    } else if (((Keymap & (0x01 << MAP_ENTER)) == 0)
            && ((Keymap_o & (0x01 << MAP_ENTER)) > 0)) {
        // release
        Key_enter_decnt++;
    }

    if (((Keymap & (0x01 << MAP_RBT)) > 0)
            && ((Keymap_o & (0x01 << MAP_RBT)) == 0)) {
        // push
        Key_rbt_encnt++;
    } else if (((Keymap & (0x01 << MAP_RBT)) == 0)
            && ((Keymap_o & (0x01 << MAP_RBT)) > 0)) {
        // release
        Key_rbt_decnt++;
    }

    if (((Keymap & (0x01 << MAP_RL)) > 0)
            && ((Keymap_o & (0x01 << MAP_RL)) == 0)
            && ((Keymap & (0x01 << MAP_RR)) == 0)) {
        // push rl
        Key_rl_encnt++;
    } else if (((Keymap & (0x01 << MAP_RR)) > 0)
            && ((Keymap_o & (0x01 << MAP_RR)) == 0)
            && ((Keymap & (0x01 << MAP_RL)) == 0)) {
        // push rr
        Key_rr_encnt++;
    } else if ((((Keymap & (0x01 << MAP_RL)) > 0)
            && ((Keymap & (0x01 << MAP_RR)) > 0))
            || (((Keymap & (0x01 << MAP_RL)) == 0)
                    && ((Keymap & (0x01 << MAP_RR)) == 0))) {

        if (((Keymap & (0x01 << MAP_RL)) != (Keymap_o & (0x01 << MAP_RL)))) {
            Key_rl_decnt++;
        }
        if (((Keymap & (0x01 << MAP_RR)) != (Keymap_o & (0x01 << MAP_RR)))) {
            Key_rr_decnt++;
        }

    }

    Keymap_o = Keymap;

    return 0;
}

uint16_t TMOS_Keys_TransMacro(uint8_t task_id, uint16_t events) {

    uint8_t i = 0;

    if((!finish_upload) && (Protocol_SW == Board_Use_BLE)){
        return 0;
    }

    // X
    if (Key_x_tricnt >= KeyCfg_RAM_X.SwitchKeys_DelayCnt
            && KeyCfg_RAM_X.SwitchKeys_DelayCnt != 0) {
        // Switch key
        KeyCfg_JumpNext(KEYCFG_ROM_X, &KeyCfg_RAM_X);
    }

    if (Key_x_encnt > 0) {
        // Hold Task
        for (i = 0; i < 8; i++) {
            ReportBuf_Keyboard[i] |= KeyCfg_RAM_X.Set_Keys[i];
        }
        for (i = 0; i < 4; i++) {
            ReportBuf_Consumer[i] |= KeyCfg_RAM_X.Set_Csms[i];
        }
        Key_x_tricnt++;
    }

    if ((Key_x_encnt >= KeyCfg_RAM_X.FinishTsk_PushCnt
            && KeyCfg_RAM_X.FinishTsk_PushCnt != 0)
            || (Key_x_decnt >= KeyCfg_RAM_X.FinishTsk_RlseCnt
                    && KeyCfg_RAM_X.FinishTsk_RlseCnt != 0)
            || (Key_x_tricnt >= KeyCfg_RAM_X.FinishTsk_HoldCnt
                    && KeyCfg_RAM_X.FinishTsk_HoldCnt != 0)) {
        // finish task
        for (i = 0; i < 8; i++) {
            ReportBuf_Keyboard[i] &= KeyCfg_RAM_X.Reset_Keys[i];
        }
        for (i = 0; i < 4; i++) {
            ReportBuf_Consumer[i] &= KeyCfg_RAM_X.Reset_Csms[i];
        }

        Key_x_encnt = 0;
        Key_x_decnt = 0;
        Key_x_tricnt = 0;

        if (KeyCfg_RAM_X.Reset_Flag) {
            KeyCfg_Reset(KEYCFG_ROM_X, &KeyCfg_RAM_X);
        }
    }

    // C
    if (Key_c_tricnt >= KeyCfg_RAM_C.SwitchKeys_DelayCnt
            && KeyCfg_RAM_C.SwitchKeys_DelayCnt != 0) {
        // Switch key
        KeyCfg_JumpNext(KEYCFG_ROM_C, &KeyCfg_RAM_C);
    }

    if (Key_c_encnt > 0) {
        // Hold Task
        for (i = 0; i < 8; i++) {
            ReportBuf_Keyboard[i] |= KeyCfg_RAM_C.Set_Keys[i];
        }
        for (i = 0; i < 4; i++) {
            ReportBuf_Consumer[i] |= KeyCfg_RAM_C.Set_Csms[i];
        }
        Key_c_tricnt++;
    }

    if ((Key_c_encnt >= KeyCfg_RAM_C.FinishTsk_PushCnt
            && KeyCfg_RAM_C.FinishTsk_PushCnt != 0)
            || (Key_c_decnt >= KeyCfg_RAM_C.FinishTsk_RlseCnt
                    && KeyCfg_RAM_C.FinishTsk_RlseCnt != 0)
            || (Key_c_tricnt >= KeyCfg_RAM_C.FinishTsk_HoldCnt
                    && KeyCfg_RAM_C.FinishTsk_HoldCnt != 0)) {
        // finish task
        for (i = 0; i < 8; i++) {
            ReportBuf_Keyboard[i] &= KeyCfg_RAM_C.Reset_Keys[i];
        }
        for (i = 0; i < 4; i++) {
            ReportBuf_Consumer[i] &= KeyCfg_RAM_C.Reset_Csms[i];
        }

        Key_c_encnt = 0;
        Key_c_decnt = 0;
        Key_c_tricnt = 0;

        if (KeyCfg_RAM_C.Reset_Flag) {
            KeyCfg_Reset(KEYCFG_ROM_C, &KeyCfg_RAM_C);
        }
    }

    // V
    if (Key_v_tricnt >= KeyCfg_RAM_V.SwitchKeys_DelayCnt
            && KeyCfg_RAM_V.SwitchKeys_DelayCnt != 0) {
        // Switch key
        KeyCfg_JumpNext(KEYCFG_ROM_V, &KeyCfg_RAM_V);
    }

    if (Key_v_encnt > 0) {
        // Hold Task
        for (i = 0; i < 8; i++) {
            ReportBuf_Keyboard[i] |= KeyCfg_RAM_V.Set_Keys[i];
        }
        for (i = 0; i < 4; i++) {
            ReportBuf_Consumer[i] |= KeyCfg_RAM_V.Set_Csms[i];
        }
        Key_v_tricnt++;
    }

    if ((Key_v_encnt >= KeyCfg_RAM_V.FinishTsk_PushCnt
            && KeyCfg_RAM_V.FinishTsk_PushCnt != 0)
            || (Key_v_decnt >= KeyCfg_RAM_V.FinishTsk_RlseCnt
                    && KeyCfg_RAM_V.FinishTsk_RlseCnt != 0)
            || (Key_v_tricnt >= KeyCfg_RAM_V.FinishTsk_HoldCnt
                    && KeyCfg_RAM_V.FinishTsk_HoldCnt != 0)) {
        // finish task
        for (i = 0; i < 8; i++) {
            ReportBuf_Keyboard[i] &= KeyCfg_RAM_V.Reset_Keys[i];
        }
        for (i = 0; i < 4; i++) {
            ReportBuf_Consumer[i] &= KeyCfg_RAM_V.Reset_Csms[i];
        }

        Key_v_encnt = 0;
        Key_v_decnt = 0;
        Key_v_tricnt = 0;

        if (KeyCfg_RAM_V.Reset_Flag) {
            KeyCfg_Reset(KEYCFG_ROM_V, &KeyCfg_RAM_V);
        }
    }

    // CTRL
    if (Key_ctrl_tricnt >= KeyCfg_RAM_CTRL.SwitchKeys_DelayCnt
            && KeyCfg_RAM_CTRL.SwitchKeys_DelayCnt != 0) {
        // Switch key
        KeyCfg_JumpNext(KEYCFG_ROM_CTRL, &KeyCfg_RAM_CTRL);
    }

    if (Key_ctrl_encnt > 0) {
        // Hold Task
        for (i = 0; i < 8; i++) {
            ReportBuf_Keyboard[i] |= KeyCfg_RAM_CTRL.Set_Keys[i];
        }
        for (i = 0; i < 4; i++) {
            ReportBuf_Consumer[i] |= KeyCfg_RAM_CTRL.Set_Csms[i];
        }
        Key_ctrl_tricnt++;
    }

    if ((Key_ctrl_encnt >= KeyCfg_RAM_CTRL.FinishTsk_PushCnt
            && KeyCfg_RAM_CTRL.FinishTsk_PushCnt != 0)
            || (Key_ctrl_decnt >= KeyCfg_RAM_CTRL.FinishTsk_RlseCnt
                    && KeyCfg_RAM_CTRL.FinishTsk_RlseCnt != 0)
            || (Key_ctrl_tricnt >= KeyCfg_RAM_CTRL.FinishTsk_HoldCnt
                    && KeyCfg_RAM_CTRL.FinishTsk_HoldCnt != 0)) {
        // finish task
        for (i = 0; i < 8; i++) {
            ReportBuf_Keyboard[i] &= KeyCfg_RAM_CTRL.Reset_Keys[i];
        }
        for (i = 0; i < 4; i++) {
            ReportBuf_Consumer[i] &= KeyCfg_RAM_CTRL.Reset_Csms[i];
        }

        Key_ctrl_encnt = 0;
        Key_ctrl_decnt = 0;
        Key_ctrl_tricnt = 0;

        if (KeyCfg_RAM_CTRL.Reset_Flag) {
            KeyCfg_Reset(KEYCFG_ROM_CTRL, &KeyCfg_RAM_CTRL);
        }
    }

    // ENTER
    if (Key_enter_tricnt >= KeyCfg_RAM_ENTER.SwitchKeys_DelayCnt
            && KeyCfg_RAM_ENTER.SwitchKeys_DelayCnt != 0) {
        // Switch key
        KeyCfg_JumpNext(KEYCFG_ROM_ENTER, &KeyCfg_RAM_ENTER);
    }

    if (Key_enter_encnt > 0) {
        // Hold Task
        for (i = 0; i < 8; i++) {
            ReportBuf_Keyboard[i] |= KeyCfg_RAM_ENTER.Set_Keys[i];
        }
        for (i = 0; i < 4; i++) {
            ReportBuf_Consumer[i] |= KeyCfg_RAM_ENTER.Set_Csms[i];
        }
        Key_enter_tricnt++;
    }

    if ((Key_enter_encnt >= KeyCfg_RAM_ENTER.FinishTsk_PushCnt
            && KeyCfg_RAM_ENTER.FinishTsk_PushCnt != 0)
            || (Key_enter_decnt >= KeyCfg_RAM_ENTER.FinishTsk_RlseCnt
                    && KeyCfg_RAM_ENTER.FinishTsk_RlseCnt != 0)
            || (Key_enter_tricnt >= KeyCfg_RAM_ENTER.FinishTsk_HoldCnt
                    && KeyCfg_RAM_ENTER.FinishTsk_HoldCnt != 0)) {
        // finish task
        for (i = 0; i < 8; i++) {
            ReportBuf_Keyboard[i] &= KeyCfg_RAM_ENTER.Reset_Keys[i];
        }
        for (i = 0; i < 4; i++) {
            ReportBuf_Consumer[i] &= KeyCfg_RAM_ENTER.Reset_Csms[i];
        }

        Key_enter_encnt = 0;
        Key_enter_decnt = 0;
        Key_enter_tricnt = 0;

        if (KeyCfg_RAM_ENTER.Reset_Flag) {
            KeyCfg_Reset(KEYCFG_ROM_ENTER, &KeyCfg_RAM_ENTER);
        }
    }

    // RBT
    if (Key_rbt_tricnt >= KeyCfg_RAM_RBT.SwitchKeys_DelayCnt
            && KeyCfg_RAM_RBT.SwitchKeys_DelayCnt != 0) {
        // Switch key
        KeyCfg_JumpNext(KEYCFG_ROM_RBT, &KeyCfg_RAM_RBT);
    }

    if (Key_rbt_encnt > 0) {
        // Hold Task
        for (i = 0; i < 8; i++) {
            ReportBuf_Keyboard[i] |= KeyCfg_RAM_RBT.Set_Keys[i];
        }
        for (i = 0; i < 4; i++) {
            ReportBuf_Consumer[i] |= KeyCfg_RAM_RBT.Set_Csms[i];
        }
        Key_rbt_tricnt++;
    }

    if ((Key_rbt_encnt >= KeyCfg_RAM_RBT.FinishTsk_PushCnt
            && KeyCfg_RAM_RBT.FinishTsk_PushCnt != 0)
            || (Key_rbt_decnt >= KeyCfg_RAM_RBT.FinishTsk_RlseCnt
                    && KeyCfg_RAM_RBT.FinishTsk_RlseCnt != 0)
            || (Key_rbt_tricnt >= KeyCfg_RAM_RBT.FinishTsk_HoldCnt
                    && KeyCfg_RAM_RBT.FinishTsk_HoldCnt != 0)) {
        // finish task
        for (i = 0; i < 8; i++) {
            ReportBuf_Keyboard[i] &= KeyCfg_RAM_RBT.Reset_Keys[i];
        }
        for (i = 0; i < 4; i++) {
            ReportBuf_Consumer[i] &= KeyCfg_RAM_RBT.Reset_Csms[i];
        }

        Key_rbt_encnt = 0;
        Key_rbt_decnt = 0;
        Key_rbt_tricnt = 0;

        if (KeyCfg_RAM_RBT.Reset_Flag) {
            KeyCfg_Reset(KEYCFG_ROM_RBT, &KeyCfg_RAM_RBT);
        }
    }

    // RL
    if (Key_rl_tricnt >= KeyCfg_RAM_RL.SwitchKeys_DelayCnt
            && KeyCfg_RAM_RL.SwitchKeys_DelayCnt != 0) {
        // Switch key
        KeyCfg_JumpNext(KEYCFG_ROM_RL, &KeyCfg_RAM_RL);
    }

    if (Key_rl_encnt > 0) {
        // Hold Task
        enco_left++;
//        for (i = 0; i < 8; i++) {
//            ReportBuf_Keyboard[i] |= KeyCfg_RAM_RL.Set_Keys[i];
//        }
//        for (i = 0; i < 4; i++) {
//            ReportBuf_Consumer[i] |= KeyCfg_RAM_RL.Set_Csms[i];
//        }
        Key_rl_tricnt++;
    }

    if ((Key_rl_encnt >= KeyCfg_RAM_RL.FinishTsk_PushCnt
            && KeyCfg_RAM_RL.FinishTsk_PushCnt != 0)
            || (Key_rl_decnt >= KeyCfg_RAM_RL.FinishTsk_RlseCnt
                    && KeyCfg_RAM_RL.FinishTsk_RlseCnt != 0)
            || (Key_rl_tricnt >= KeyCfg_RAM_RL.FinishTsk_HoldCnt
                    && KeyCfg_RAM_RL.FinishTsk_HoldCnt != 0)) {
        // finish task
        switch(enco_left){
        case 0:
            break;
        default:
            enco_left--;
        }

        for (i = 0; i < 8; i++) {
            ReportBuf_Keyboard[i] &= KeyCfg_RAM_RL.Reset_Keys[i];
        }
        for (i = 0; i < 4; i++) {
            ReportBuf_Consumer[i] &= KeyCfg_RAM_RL.Reset_Csms[i];
        }

        Key_rl_encnt = 0;
        Key_rl_decnt = 0;
        Key_rl_tricnt = 0;

        if (KeyCfg_RAM_RL.Reset_Flag) {
            KeyCfg_Reset(KEYCFG_ROM_RL, &KeyCfg_RAM_RL);
        }
    }

    // RR
    if (Key_rr_tricnt >= KeyCfg_RAM_RR.SwitchKeys_DelayCnt
            && KeyCfg_RAM_RR.SwitchKeys_DelayCnt != 0) {
        // Switch key
        KeyCfg_JumpNext(KEYCFG_ROM_RR, &KeyCfg_RAM_RR);
    }

    if (Key_rr_encnt > 0) {
        // Hold Task
        enco_right++;
//        for (i = 0; i < 8; i++) {
//            ReportBuf_Keyboard[i] |= KeyCfg_RAM_RR.Set_Keys[i];
//        }
//        for (i = 0; i < 4; i++) {
//            ReportBuf_Consumer[i] |= KeyCfg_RAM_RR.Set_Csms[i];
//        }
        Key_rr_tricnt++;
    }

    if ((Key_rr_encnt >= KeyCfg_RAM_RR.FinishTsk_PushCnt
            && KeyCfg_RAM_RR.FinishTsk_PushCnt != 0)
            || (Key_rr_decnt >= KeyCfg_RAM_RR.FinishTsk_RlseCnt
                    && KeyCfg_RAM_RR.FinishTsk_RlseCnt != 0)
            || (Key_rr_tricnt >= KeyCfg_RAM_RR.FinishTsk_HoldCnt
                    && KeyCfg_RAM_RR.FinishTsk_HoldCnt != 0)) {
        // finish task
        switch(enco_right){
        case 0:
            break;
        default:
            enco_right--;
        }
        for (i = 0; i < 8; i++) {
            ReportBuf_Keyboard[i] &= KeyCfg_RAM_RR.Reset_Keys[i];
        }
        for (i = 0; i < 4; i++) {
            ReportBuf_Consumer[i] &= KeyCfg_RAM_RR.Reset_Csms[i];
        }

        Key_rr_encnt = 0;
        Key_rr_decnt = 0;
        Key_rr_tricnt = 0;

        if (KeyCfg_RAM_RR.Reset_Flag) {
            KeyCfg_Reset(KEYCFG_ROM_RR, &KeyCfg_RAM_RR);
        }
    }

    if(enco_left > enco_right){
        enco_right= 0;
    }else if(enco_right > enco_left){
        enco_left = 0;
    }

    if(enco_finish_flg){
        if(enco_left){
            // Hold Task
            enco_left--;
            for (i = 0; i < 8; i++) {
                ReportBuf_Keyboard[i] |= KeyCfg_RAM_RL.Set_Keys[i];
            }
            for (i = 0; i < 4; i++) {
                ReportBuf_Consumer[i] |= KeyCfg_RAM_RL.Set_Csms[i];
            }
            enco_finish_flg = FALSE;
        }
        else if (enco_right){
            // Hold Task
            enco_right--;
            for (i = 0; i < 8; i++) {
                ReportBuf_Keyboard[i] |= KeyCfg_RAM_RR.Set_Keys[i];
            }
            for (i = 0; i < 4; i++) {
                ReportBuf_Consumer[i] |= KeyCfg_RAM_RR.Set_Csms[i];
            }
            enco_finish_flg = FALSE;
        }
    }

    else {
        // finish task
        for (i = 0; i < 8; i++) {
            ReportBuf_Keyboard[i] &= KeyCfg_RAM_RR.Reset_Keys[i];
        }
        for (i = 0; i < 4; i++) {
            ReportBuf_Consumer[i] &= KeyCfg_RAM_RR.Reset_Csms[i];
        }
        enco_finish_flg = TRUE;
    }

    finish_upload = FALSE;

    return 0;
}

