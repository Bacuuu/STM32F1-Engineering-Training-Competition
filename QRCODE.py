# QRCode Example
#
# 这个例子展示了OpenMV Cam的功能，可以在不需要镜头校正的情况下检测QR码。
import sensor, image, time

sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_framesize(sensor.VGA)
sensor.set_windowing((240, 240)) # look at center 240x240 pixels of the VGA resolution.
sensor.skip_frames(30)
sensor.set_auto_gain(False) # must turn this off to prevent image washout...
clock = time.clock()

while(True):
    clock.tick()
    img = sensor.snapshot()
    for code in img.find_qrcodes():
        print(code)
    print(clock.fps())
