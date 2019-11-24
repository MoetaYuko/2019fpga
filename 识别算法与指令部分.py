# -*- coding: utf-8 -*-
"""
Created on Wed Nov 20 17:39:21 2019

@author: Hp
"""

from pynq.overlays.base import BaseOverlay
from pynq.lib.video import *
import cv2
from matplotlib import pyplot as plt
import numpy as np
import time
base = BaseOverlay("base.bit")
from pynq.lib.arduino import Arduino_IO

J = Arduino_IO(base.ARDUINO,4,'out')
Dd = Arduino_IO(base.ARDUINO,5,'out')
Fd = Arduino_IO(base.ARDUINO,6,'out')
# monitor configuration: 640*480 @ 60Hz,在此我们设置HDMI输出为640*480
Mode = VideoMode(640,480,24)
#hdmi_out = base.video.hdmi_out
#hdmi_out.configure(Mode,PIXEL_BGR)
#hdmi_out.start()

# camera (input) configuration
frame_in_w = 640
frame_in_h = 480

videoIn = cv2.VideoCapture(0)
videoIn.set(cv2.CAP_PROP_FRAME_WIDTH, frame_in_w);
videoIn.set(cv2.CAP_PROP_FRAME_HEIGHT, frame_in_h);
print("capture device is open: " + str(videoIn.isOpened()))

num_frames = 50
readError = 0

def findcircle():
    circles = circle1[0, :, :]  # 提取为二维
    circles = np.uint16(np.around(circles))  # 四舍五入
    for i in circles[:]:
        cv2.circle(frame, (i[0], i[1]), i[2], color=[255, 0, 0], thickness=6)  # 画圆
        cv2.circle(frame, (i[0], i[1]), 2, color=[255, 0, 0], thickness=6)  # 画圆心
    plt.subplot(122), plt.imshow(frame)
    plt.title('circle')
    plt.xticks([]), plt.yticks([])
    plt.show()
    print('发现目标')
    J.write(1)
    target=max(circles[:,2])#最大半径检测
    maxindex = np.argmax(circles[:,2])#对应位置
    x_0=circles[maxindex,0]#最大圆对应的水平
            #circles[maxindex]
    print(circles)#输出所有数据
    print(x_0)#最大数据水平位置
    print(target)#最大数据半径
    d=x_0-center_x#水平偏差
    print(center_x)
    print(d)#输出水平偏差
    if d>30:
        print("偏右")
        Dd.write(0)
        Fd.write(0)
    elif d<-30:
        print("偏左")
        Dd.write(1)
        Fd.write(0)
    else:
        print("前进")
        Fd.write(1)
#globalimage=np.zeros((640,480,3), np.uint8) 

#while True: 
    # read next image
#    globalimage=frame_vga
while True:
    start = time.time()
    ret, frame = videoIn.read()
#    img = frame.array
    (h1, w1) = frame.shape[:2]
    center_x=w1/2
    center_y=h1/2
#    img = cv2.imread('1.jpg')
#    img=cv2.resize(img,(640,480),interpolation=cv2.INTER_CUBIC)
#    print(center_x, center_y)
#    print(gray.shape)
    if (ret):
        (b,g,r)=cv2.split(frame)#转换通道
        frame=cv2.merge([r,g,b])
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        plt.imshow(frame, cmap = 'gray')
        plt.title('Input Image')
        plt.xticks([]), plt.yticks([])
        plt.show()
        circle1 = cv2.HoughCircles(gray, cv2.HOUGH_GRADIENT, 1, 100, param1=100, param2=30, minRadius=20, maxRadius=60)  #把半径范围缩小点，检测内圆，瞳孔
        try:                             # 如果上一步没有检测到。执行try内容，就会报错。可以修改尝试看下。
            findcircle()
        except TypeError:
            print ('NULL')
            J.write(0)
            print('继续前进')
            plt.show()
        plt.show()
        print("test ok")
    else:
        readError += 1
        
    end = time.time()
    seconds=end-start
    num_frames -=1
    if num_frames<10:
        break