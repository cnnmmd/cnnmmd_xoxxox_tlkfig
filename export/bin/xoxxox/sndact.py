import argparse
import aiohttp
from aiohttp import web
from xoxxox.shared import Custom
from xoxxox.params_act import *

vdowth = 0
vdohgt = 0
angdfx = 0
angdfy = 0

async def sndang(angdfx, angdfy, mscdfx, mscdfy):
  dicrec = {"dfx": angdfx, "dfy": angdfy, "msx": mscdfx, "msy": mscdfy}
  print(f"dfx: {angdfx}, dfy: {angdfy}, msx: {mscdfx}, msy: {mscdfy}") # DBG
  async with aiohttp.ClientSession() as sssweb:
    async with sssweb.post(urlact, json=dicrec) as datres:
      dicres = await datres.text()
      return dicres

async def resfrm(datreq):
  global vdowth, vdohgt
  dicreq = await datreq.json()
  #print(dicreq, flush=True) # DBG
  vdowth = dicreq["w"]
  vdohgt = dicreq["h"]

async def resfce(datreq):
  global angdfx, angdfy
  dicreq = await datreq.json()
  #print(dicreq, flush=True) # DBG
  x = dicreq["x"]
  y = dicreq["y"]
  w = dicreq["w"]
  h = dicreq["h"]
  rcx = (x + w / 2) / vdowth
  rcy = (y + h / 2) / vdohgt
  print(f"rcx: {rcx:.2f}, rcy: {rcy:.2f}") # DBG
  # 顔が検出された範囲
  flgexe = False
  if 0.00 < rcx < mindfx:
    angdfx = + absdfx
    flgexe = True
  if maxdfx < rcx < 1.00:
    angdfx = - absdfx
    flgexe = True
  if 0.00 < rcy < mindfy:
    angdfy = - absdfy
    flgexe = True
  if maxdfy < rcy < 1.00:
    angdfy = + absdfy
    flgexe = True
  if flgexe:
    await sndang(angdfx, angdfy, mscdfx, mscdfy)

#---------------------------------------------------------------------------

parser = argparse.ArgumentParser()
parser.add_argument("--svport", type=int, default="80")
parser.add_argument("--urlact", type=str) # default: cnffig
objarg = parser.parse_args()

cnffig = "xoxxox/cnffig"
dicfig = Custom.update(cnffig, {k: v for k, v in vars(objarg).items() if v is not None})
dicprm = {k: v for k, v in vars(objarg).items() if v is not None}

svport = objarg.svport
urlact = dicfig["urlact"]

adrfrm = "/frm"
adrfce = "/fce"

#---------------------------------------------------------------------------

appweb = web.Application()
appweb.add_routes([web.post(adrfrm, resfrm)])
appweb.add_routes([web.post(adrfce, resfce)])
web.run_app(appweb, port=svport)
