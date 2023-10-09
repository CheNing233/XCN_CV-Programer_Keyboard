import os
import logging
from array import array

import usb.core
import usb.util
import usb.backend.libusb1


class USB_Controller:
    pyusb_backend_path = ""
    pyusb_backend = None

    pyusb_device: usb.core.Device = None

    xcnkb_idVendor = 0x413D
    xcnkb_idProduct = 0x2107

    xcnkb_bulkin_addr = 0x83
    xcnkb_bulkout_addr = 0x4

    def __init__(self) -> None:
        self.pyusb_backend_path = os.path.join(
            os.path.dirname(os.path.abspath(__file__)), "libusb-1.0.dll"
        )

        self.pyusb_backend = usb.backend.libusb1.get_backend(
            find_library=lambda x: self.pyusb_backend_path
        )

        logging.info("pyusb.backend = %s" % (self.pyusb_backend))

    def get_target_device(self) -> int | None:
        self.pyusb_device = usb.core.find(
            idVendor=self.xcnkb_idVendor,
            idProduct=self.xcnkb_idProduct,
            backend=self.pyusb_backend,
        )

        if self.pyusb_device == None:
            logging.error("目标设备查找失败")
            return None

        # logging.debug("Target device info:\n%s" % (self.pyusb_device))

        self.pyusb_device.set_configuration()

        return self.pyusb_device.get_active_configuration()

    def check_valid(self) -> list | None:
        if self.pyusb_device == None:
            logging.error("设备句柄为空，停止该操作")
            return None

        msg = array("B")
        msg.append(0)

        logging.info("MSG = %s" % (msg))

        self.pyusb_device.write(self.xcnkb_bulkout_addr, msg, 3000)

        response = None

        try:
            response = self.pyusb_device.read(self.xcnkb_bulkin_addr, 64, 3000)
        except:
            logging.error("self.pyusb_device.read 失败")
            return None

        if not response[0] == 233:
            logging.error("self.pyusb_device.read 下位机响应异常")
            return None

        logging.info("MSG = %s" % (response))

        return [response[1], response[2], response[3]]

    def write(self, cmd_key, msg_data: array = None) -> array:
        if self.check_valid() == None:
            logging.error("操作取消")
            return None

        msg = array("B")
        msg.append(cmd_key)

        if msg_data:
            msg += msg_data
            logging.info(
                "即将向 0x%x 发送 %d 请求，附加数据 = %s"
                % (self.xcnkb_bulkout_addr, cmd_key, msg_data),
            )

        try:
            self.pyusb_device.write(self.xcnkb_bulkout_addr, msg, 3000)
        except:
            logging.error("self.pyusb_device.write 失败")
            return None

        logging.info("成功向 0x%x 发送 %d 请求" % (self.xcnkb_bulkout_addr, cmd_key))

        try:
            response = self.pyusb_device.read(self.xcnkb_bulkin_addr, 64, 3000)
        except:
            logging.error("self.pyusb_device.read 失败")
            return None

        logging.info("0x%x 返回 = %s" % (self.xcnkb_bulkin_addr, response))

        return response


if __name__ == "__main__":
    logging.basicConfig(
        format="[%(asctime)s|%(levelname)s] %(funcName)s : %(message)s",
        level=logging.DEBUG,
    )

    logging.info("LOG OK")

    ctrler = USB_Controller()

    ctrler.get_target_device()

    print(ctrler.check_valid())

    # print(pyu.pyusb_device.product)
    # print(type(pyu.pyusb_device))
    # print(pyu.pyusb_device.get_active_configuration())
