# -*- coding: utf-8 -*-

import cv2

# 加载检测器
classPath = 'TrainCascadeClassification/cascade.xml'
face_cascade = cv2.CascadeClassifier(classPath)
print("加载检测器")
# 读取图片并灰度化
img = cv2.imread('testimg.jpg')
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
print("读取图片灰度化")
cv2.imshow('show', gray)
# 框出并加上文字说明
faces = face_cascade.detectMultiScale(
    gray,
    scaleFactor=1.08,
    minNeighbors=50,
    minSize=(70, 70),
    flags=cv2.CASCADE_SCALE_IMAGE
)

for (x, y, w, h) in faces:
    cv2.rectangle(img, (x, y), (x + w, y + h), (0, 0, 255), 2)
    cv2.putText(img, 'tennis', (x, y - 7), 3, 1.2, (0, 255, 0), 2, cv2.LINE_AA)
print("显示效果")
cv2.imshow('tennis', img)
cv2.imwrite("testimg_dealed.png", img)
c = cv2.waitKey(0)
