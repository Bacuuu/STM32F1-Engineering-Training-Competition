import sensor, image, time
from pyb import UART

sensor.reset() # 初始化摄像头
sensor.set_pixformat(sensor.RGB565) # 格式为 RGB565.
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(10) # 跳过10帧，使新设置生效
sensor.set_auto_whitebal(False)               # Create a clock object to track the FPS.

ROI_L=(65,75,15,19)             #L  58-->75      A   -6-->2     B   -1-->15
ROI_M=(163,76,15,17)            #L  68-->75      A   5-->10     B   -25-->-15
ROI_R=(259,76,14,19)            #L  58-->64      A   44-->48    B   -2-->2

colorList = [0,0,0]
'''
def isGreen(l,a,b):
    if(abs(a+3)<=4):
        return True
    else:
        return False

def isBlue(l,a,b):
    if(abs(a-8)<10 and abs(a+20)<5):
        return True
    else:
        return False

def isRed(l,a,b):
    if(abs(a-44)<=4):
        return True
    else:
        return False
'''


def whichColor(aLeft,aMiddle,aRight):
    if((aLeft-aMiddle)*(aLeft-aRight)>0):
        if(aLeft>aMiddle):
            colorList[0] = 'Red'
            if(aMiddle>aRight):
                colorList[1] = 'Blue'
                colorList[2] = 'Green'              #RBG
                return '1'
            else:
                colorList[1] = 'Green'
                colorList[2] = 'Blue'               #RGB
                return '0'
        else:
            colorList[0] = 'Green'
            if(aMiddle>aRight):
                colorList[1] = 'Red'
                colorList[2] = 'Blue'               #GRB
                return '4'
            else:
                colorList[1] = 'Blue'
                colorList[2] = 'Red'                #GBR
                return '5'
    else:
        colorList[0] = "Blue"
        if(aMiddle>aRight):
            colorList[1] = 'Red'
            colorList[2] = 'Green'                  #BRG
            return '2'
        else:
            colorList[1] = 'Green'
            colorList[2] = 'Red'                    #BGR
            return '3'






while(1):
    uart = UART(3, 9600, timeout_char=1000)
    img = sensor.snapshot()         # Take a picture and return the image.
    #print('waiting for host')
    #print(uart.readchar())

    statistics=img.get_statistics(roi=ROI_L)
    #color_l=statistics.l_mode()
    colorLeft_a=statistics.a_mode()
    #color_b=statistics.b_mode()
    #print("left area:")
    #print(color_l,color_a,color_b)
    #print(colorLeft_a)
    img.draw_rectangle(ROI_L)


    statistics=img.get_statistics(roi=ROI_M)
    #color_l=statistics.l_mode()
    colorMiddle_a=statistics.a_mode()
    #color_b=statistics.b_mode()
    #print("center area:")
    #print(color_l,color_a,color_b)
    #print(colorMiddle_a)
    img.draw_rectangle(ROI_M)

    statistics=img.get_statistics(roi=ROI_R)
    #color_l=statistics.l_mode()
    colorRight_a=statistics.a_mode()
    #color_b=statistics.b_mode()
    #print("right area:")
    #print(color_l,color_a,color_b)
    #print(colorRight_a)
    img.draw_rectangle(ROI_R)

    if(uart.readchar()==83):
        time.sleep(1000)
        print('ok')
        img = sensor.snapshot()         # Take a picture and return the image.
        #print('waiting for host')
        #print(uart.readchar())

        statistics=img.get_statistics(roi=ROI_L)
        #color_l=statistics.l_mode()
        colorLeft_a=statistics.a_mode()
        #color_b=statistics.b_mode()
        #print("left area:")
        #print(color_l,color_a,color_b)
        #print(colorLeft_a)
        img.draw_rectangle(ROI_L)


        statistics=img.get_statistics(roi=ROI_M)
        #color_l=statistics.l_mode()
        colorMiddle_a=statistics.a_mode()
        #color_b=statistics.b_mode()
        #print("center area:")
        #print(color_l,color_a,color_b)
        #print(colorMiddle_a)
        img.draw_rectangle(ROI_M)

        statistics=img.get_statistics(roi=ROI_R)
        #color_l=statistics.l_mode()
        colorRight_a=statistics.a_mode()
        #color_b=statistics.b_mode()
        #print("right area:")
        #print(color_l,color_a,color_b)
        #print(colorRight_a)
        img.draw_rectangle(ROI_R)
        uart.write(whichColor(colorLeft_a,colorMiddle_a,colorRight_a))
