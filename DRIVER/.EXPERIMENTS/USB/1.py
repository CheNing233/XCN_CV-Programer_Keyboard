import hid

# for device_dict in hid.enumerate(0x413D, 0x2107):
for device_dict in hid.enumerate():
    keys = list(device_dict.keys())
    keys.sort()
    for key in keys:
        print("%s : %s" % (key, device_dict[key]))

print("\n========\n")

try:
    print("Opening the device")

    h = hid.device()
    h.open(12815, 20565)  # TREZOR VendorID/ProductID

    print("STATE: " + h.error())

    print("Manufacturer: %s" % h.get_manufacturer_string())
    print("Product: %s" % h.get_product_string())
    print("Serial No: %s" % h.get_serial_number_string())

    # enable non-blocking mode
    # h.set_nonblocking(1)

    # # write some to the device
    # print("Write the data")
    # h.write([0, 63, 35, 35] + [0] * 61)

    # # wait

    # read back the answer
    print("Read the data")
    # while True:
    #     d = h.read(64)

    #     if d:
    #         print(d)
    #     else:
    #         break

    print(h.get_input_report(1, 64))

    print("Closing the device")
    h.close()

except IOError as ex:
    print("ERROR: " + str(ex))
    # print("You probably don't have the hard-coded device.")
    # print("Update the h.open() line in this script with the one")
    # print("from the enumeration list output above and try again.")

print("Done")
