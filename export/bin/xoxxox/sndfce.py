import argparse
import threading
import requests
import cv2
from xoxxox.shared import Custom

#---------------------------------------------------------------------------

parser = argparse.ArgumentParser()
parser.add_argument("--urlcam", type=str) # default: cnffig
parser.add_argument("--urlfrm", type=str) # default: cnffig
parser.add_argument("--urlfce", type=str) # default: cnffig
objarg = parser.parse_args()

cnffig = "xoxxox/cnffig"
dicfig = Custom.update(cnffig, {k: v for k, v in vars(objarg).items() if v is not None})
dicprm = {k: v for k, v in vars(objarg).items() if v is not None}

urlcam = dicfig["urlcam"]
urlfrm = dicfig["urlfrm"]
urlfce = dicfig["urlfce"]

#---------------------------------------------------------------------------

clsfce = cv2.CascadeClassifier(cv2.data.haarcascades + "haarcascade_frontalface_default.xml") # 顔検出用カスケード分類器（Haar Cascades / OpenCV）
capvdo = cv2.VideoCapture(urlcam) # 映像ストリームのキャプチャ

def sndfrm(w, h):
  def s():
    dicvdo = {"w": w, "h": h}
    requests.post(urlfrm, json=dicvdo, timeout=1.0)
  thread = threading.Thread(target=s, daemon=True)
  thread.start()

def sndfce(x, y, w, h):
  def s():
    dicfce = {"x": x, "y": y, "w": w, "h": h}
    requests.post(urlfce, json=dicfce, timeout=1.0)
  thread = threading.Thread(target=s, daemon=True)
  thread.start()

flgfst = True
while capvdo.isOpened():
  r, vdofrm = capvdo.read()
  if r:
    if flgfst:
      h, w, _ = vdofrm.shape
      sndfrm(w, h)
      flgfst = False
    g = cv2.cvtColor(vdofrm, cv2.COLOR_BGR2GRAY) # グレースケールに変換（顔検出の精度向上）
    lstfce = clsfce.detectMultiScale(g, scaleFactor=1.1, minNeighbors=5, minSize=(50, 50))
    if len(lstfce) > 0:
      x, y, w, h = lstfce[0]
      sndfce(int(x), int(y), int(w), int(h))
    else:
      pass
  else:
    break

capvdo.release()
