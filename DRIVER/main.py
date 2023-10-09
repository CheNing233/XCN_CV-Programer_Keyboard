import logging

from array import array

from USB.ctrler import USB_Controller
from USB.msgtrans import CMD_Index, Form_Usercfg, Form_Keycfg, DataTrans_Utils


if __name__ == "__main__":
    logging.basicConfig(
        format="[%(asctime)s|%(levelname)s] %(funcName)s : %(message)s",
        level=logging.DEBUG,
    )

    logging.info("Log start")

    ctrler = USB_Controller()
    ctrler.get_target_device()

    # r_data = ctrler.write(CMD_Index.r_usercfg.value)
    # data = DataTrans_Utils.parse(r_data, Form_Usercfg)
    # data[Form_Usercfg.Index.KeyIn_Debouncing_DelayCircle_Cnt.value] = 1
    # data_change = DataTrans_Utils.unparse(data, Form_Usercfg)
    # ctrler.write(CMD_Index.w_usercfg.value, data_change)

    r_data = ctrler.write(CMD_Index.r_keycfg.value, array("B", (0, 0)))
    data = DataTrans_Utils.parse(r_data, Form_Keycfg)

    data[1][2] = 27

    data_change = DataTrans_Utils.flatten_list(data)
    data_change = DataTrans_Utils.unparse(data_change, Form_Keycfg)
    msg_w = array("B", (0, 0)) + data_change
    ctrler.write(CMD_Index.w_keycfg.value, msg_w)

    print("OK")
