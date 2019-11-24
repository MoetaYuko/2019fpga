# 改变图片尺寸为统一大小,在当前目录创建一个名为pos的文件夹，文件名最好不要出现中文
# 把需要统一尺寸的正样本放到里面，写上尺寸，运行程序就可以了，一般来说建议长宽在100像素一下，不然训练会很慢
import cv2
import os

w = 80
h = 80


def getimage(file_dir):
    images = {}
    for root, dirs, files in os.walk(file_dir):
        for name in files:
            images[name] = os.path.join(root, name)
    return images


if __name__ == '__main__':
    n = -1
    aa = os.getcwd()
    dirpath = os.path.join(aa, 'pic2')
    imagedic = getimage(dirpath)

    try:
        for key, value in imagedic.items():
            img = cv2.imread(value)
            print(value)
            img1 = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
            #img2 = cv2.resize(img1, (w, h))
            cv2.imwrite('neg'+'/'+'neg' + str(n + 1).rjust(3, '0') + '.jpg', img1)
            n += 1
    except KeyboardInterrupt:
        print('暂停一下')
