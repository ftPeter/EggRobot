"""
PS4 Controller via Bluetooth debugging environment.
Peter F. Klemperer
July 6, 2024

See 
https://blog.thea.codes/talking-to-gamepads-without-pygame/
for how this works.
"""
import hid

for device in hid.enumerate():
    print(f"0x{device['vendor_id']:04x}:0x{device['product_id']:04x} {device['product_string']}")

gamepad = hid.device()
""" read the output of the for loop above to get the
    magic numbers for the open command below.
    """
gamepad.open(0x054c, 0x05c4)
gamepad.set_nonblocking(True)

while True:
    report = gamepad.read(64)
    if report:
        print(report)

