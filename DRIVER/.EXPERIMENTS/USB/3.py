import pywinusb.hid as hid

# 枚举所有连接的USB设备
# all_devices = hid.HidDeviceFilter().get_devices()
# print(all_devices)

# 定义要筛选的条件
device_name = "XCN Keyboard V573USB"
vendor_id = 0x413D
product_id = 0x2107
interface_number = 2

# 创建设备过滤器并应用筛选条件
filter = hid.HidDeviceFilter(vendor_id=vendor_id, product_id=product_id)
all_devices = filter.get_devices()

# print(all_devices)

# 遍历符合筛选条件的设备
for device in all_devices:
    if device.product_name == device_name:
        # 这里可以对符合筛选条件的设备进行进一步操作
        print("Found device:", device)

# print(all_devices)
# # 根据设备特征选择要操作的USB设备
# # 请根据实际情况修改以下代码指定你要操作的设备
selected_device = all_devices[0]

# # 打开选定的设备
selected_device.open()

# # 安装WinUSB驱动
selected_device.set_raw_data_handler(lambda data: None)
selected_device.set_driver(0)  # 0表示WinUSB驱动

# # 关闭设备连接
selected_device.close()

