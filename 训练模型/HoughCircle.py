# encoding:utf-8
import cv2
import numpy as np
import matplotlib.pyplot as plt

#img = cv2.imread('eye-color-blue-z-c-660x440.jpg')
#img = cv2.imread('go-498x448.jpg')
img = cv2.imread('tennis-499x331.jpg')
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)  # 灰度图像

plt.subplot(121), plt.imshow(img, cmap='gray')
plt.title('img'), plt.xticks([]), plt.yticks([])
# hough transform  规定检测的圆的最大最小半径，不能盲目的检测，否则浪费时间空间
#circle1 = cv2.HoughCircles(gray, cv2.HOUGH_GRADIENT, dp=1, minDist=100, param1=100, param2=30, minRadius=200, maxRadius=300)
circle1 = cv2.HoughCircles(gray, cv2.HOUGH_GRADIENT, dp=1, minDist=120, param1=100, param2=30, minRadius=39, maxRadius=75)
circles = circle1[0, :, :]  # 提取为二维
circles = np.uint16(np.around(circles))  # 四舍五入，取整
for i in circles[:]:
    cv2.circle(img, (i[0], i[1]), i[2], (255, 0, 0), 5)  # 画圆
    cv2.circle(img, (i[0], i[1]), 2, (255, 0, 0), 10)  # 画圆心

plt.subplot(122), plt.imshow(img)
plt.title('circle'), plt.xticks([]), plt.yticks([])
plt.show()
