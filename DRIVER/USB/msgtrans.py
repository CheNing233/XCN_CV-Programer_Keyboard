import logging
import struct
from array import array
from enum import Enum, auto


class CMD_Index(Enum):
    check_valid = 0
    w_usercfg = auto()
    r_usercfg = auto()
    w_keycfg = auto()
    r_keycfg = auto()


class Form_Usercfg:
    size = 15
    pack_format = "<BIBBBBBBBBBB"
    unpack_format = "<BIBBBBBBBBBB"

    class Index(Enum):
        Init_Flag = 0

        Proto_FreshState_Interval = auto()
        Proto_USBBuffer_PushInterval = auto()
        Proto_BLEBuffer_PushInterval = auto()

        KeyIn_Key_Debouncing_Sampling_Interval = auto()
        KeyIn_Enco_Debouncing_Sampling_Interval = auto()

        KeyIn_Debouncing_DelayCircle_Cnt = auto()

        KeyIn_TaskFlgManager_Circle_Interval = auto()
        KeyIn_TransMacro_Circle_Interval = auto()

        USB_UploadRate = auto()
        BLE_Conn_Interval = auto()

        BLE_Uplaod_PackCnt = auto()

    @staticmethod
    def array_process(target_lst: list):
        pass


class Form_Keycfg:
    size = 34
    pack_format = "<B8B4B8B4BBBBIH"
    unpack_format = "<B8s4s8s4sBBBIH"

    class Index(Enum):
        Init_Flag = 0

        Set_Keys = auto()
        Set_Csms = auto()
        Reset_Keys = auto()
        Reset_Csms = auto()

        FinishTsk_PushCnt = auto()
        FinishTsk_RlseCnt = auto()
        FinishTsk_HoldCnt = auto()

        SwitchNext_DelayCnt = auto()
        NextPos = auto()

    @staticmethod
    def array_process(target_lst: list):
        """
        修改外部实参
        """
        target_lst[1] = list(target_lst[1])
        target_lst[2] = list(target_lst[2])
        target_lst[3] = list(target_lst[3])
        target_lst[4] = list(target_lst[4])


class DataTrans_Utils:
    @staticmethod
    def parse(raw_data: array, form: any) -> list:
        if raw_data[0] != form.size:
            logging.warning("数据大小不匹配，可能导致参数设置出错")

        try:
            data = struct.unpack(form.unpack_format, raw_data)
        except:
            logging.error("对下位机数据解析出错")
            return None

        logging.info("解析结果 = %s" % (DataTrans_Utils.build_dict(data, form)))

        data = list(data)
        form.array_process(data)

        return data

    @staticmethod
    def unparse(data: list, form: any) -> array:
        if data[0] != form.size:
            logging.warning("数据大小不匹配，可能导致参数设置出错")

        try:
            bytestream = struct.pack(form.pack_format, *data)
        except:
            logging.error("数据打包失败")

        barray = array("B", bytestream)

        return barray

    @staticmethod
    def flatten_list(lst) -> list:
        flattened_lst = []
        for item in lst:
            if isinstance(item, list):
                flattened_lst.extend(DataTrans_Utils.flatten_list(item))
            else:
                flattened_lst.append(item)
        return flattened_lst

    @staticmethod
    def build_dict(data: array, form: any):
        data_dict = dict()
        for item in form.Index:
            data_dict[item._name_] = data[item.value]
        return data_dict
