import urllib
import requests
from bs4 import BeautifulSoup
import tesserocr
import pytesseract
from PIL import Image
from io import StringIO,BytesIO

stuurl = "http://mis.sse.ustc.edu.cn/homepage/StuDefault.aspx"
baseurl = "http://mis.sse.ustc.edu.cn"
validimg_url= "http://mis.sse.ustc.edu.cn/ValidateCode.aspx?ValidateCodeType=1&0.011150883024061309"
user_agent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.138 Safari/537.36"
headers = {"Accept": "*/*",
        "Accept-Encoding": "gzip, deflate",
        "Accept-Language": "zh-CN,zh;q=0.9,en;q=0.8,ru;q=0.7,zh-TW;q=0.6",
        "Connection": "keep-alive",
        "Content-Length": "1166",
        "Content-Type": "application/x-www-form-urlencoded; charset=UTF-8",
        "Cookie": "",
        "Host": "mis.sse.ustc.edu.cn",
        "Origin": "http://mis.sse.ustc.edu.cn",
        "Referer": "http://mis.sse.ustc.edu.cn/",
        "User-Agent":user_agent,
        "X-Requested-With": "XMLHttpRequest"}
tt = "true"
ff = "false"
data = {"__EVENTTARGET": "winLogin$sfLogin$ContentPanel1$btnLogin",
        "__EVENTARGUMENT": "",
        "__VIEWSTATE": "",
        "X_CHANGED": tt,
        "winLogin$sfLogin$txtUserLoginID": "SA17225071",
        "winLogin$sfLogin$txtPassword": "keys",
        "winLogin$sfLogin$txtValidate": "21",
        "winLogin_Hidden": ff,
        "WndModal_Hidden": tt,
        "X_TARGET": "winLogin_sfLogin_ContentPanel1_btnLogin",
        "winLogin_sfLogin_ctl00_Collapsed": ff,
        "winLogin_sfLogin_ContentPanel3_Collapsed": ff,
        "winLogin_sfLogin_ContentPanel1_Collapsed": ff,
        "winLogin_sfLogin_Collapsed": ff,
        "winLogin_Collapsed": ff,
        "WndModal_Collapsed": ff,
        "X_STATE": "",
        "X_AJAX": tt}
headers1 = {"Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9",
        "Accept-Encoding": "gzip, deflate",
        "Accept-Language": "zh-CN,zh;q=0.9,en;q=0.8,ru;q=0.7,zh-TW;q=0.6",
        "Cache-Control": "max-age=0",
        "Connection": "keep-alive",
        "Host": "mis.sse.ustc.edu.cn",
        "Upgrade-Insecure-Requests": "1",
        "Cookie": "",
        "User-Agent":user_agent}
data1 = {
        "winLogin$sfLogin$txtUserLoginID": "SA17225071",
        "winLogin$sfLogin$txtPassword": "211385(F)?",
        "winLogin$sfLogin$txtValidate": "21",
        }
teststr1="eyJ3aW5Mb2dpbl9zZkxvZ2luX2N0bDAwX2xiTXNnIjp7IlRleHQiOiLluJDlj7flr4bnoIHkuI3og73kuLrnqboifSwid2luTG9naW5fc2ZMb2dpbl90eHRVc2VyTG9naW5JRCI6eyJUZXh0IjoiIn0sIndpbkxvZ2luX3NmTG9naW5fdHh0UGFzc3dvcmQiOnsiVGV4dCI6IiJ9LCJ3aW5Mb2dpbl9zZkxvZ2luX3R4dFZhbGlkYXRlIjp7IlRleHQiOiIifSwid2luTG9naW5fc2ZMb2dpbl9Db250ZW50UGFuZWwzX2ltZ1ZhbGlkYXRlQ29kZSI6eyJJbWFnZVVybCI6Ii9WYWxpZGF0ZUNvZGUuYXNweD9WYWxpZGF0ZUNvZGVUeXBlPTEmMC41OTcxNjY4OTY2MTAxMzMifX0%3D"
teststr2="eyJ3aW5Mb2dpbl9zZkxvZ2luX2N0bDAwX2xiTXNnIjp7IlRleHQiOiLpqozor4HlpLHotKUifSwid2luTG9naW5fc2ZMb2dpbl90eHRVc2VyTG9naW5JRCI6eyJUZXh0IjoiU0ExNzIyNTA3MSJ9LCJ3aW5Mb2dpbl9zZkxvZ2luX3R4dFBhc3N3b3JkIjp7IlRleHQiOiIyMTEzODUzMTJmdDAxNSJ9LCJ3aW5Mb2dpbl9zZkxvZ2luX3R4dFZhbGlkYXRlIjp7IlRleHQiOiIifSwid2luTG9naW5fc2ZMb2dpbl9Db250ZW50UGFuZWwzX2ltZ1ZhbGlkYXRlQ29kZSI6eyJJbWFnZVVybCI6Ii9WYWxpZGF0ZUNvZGUuYXNweD9WYWxpZGF0ZUNvZGVUeXBlPTEmMC4yODg4OTM1OTU0NzIzOTQifX0="
teststr3="e30="

class validcode_recog(object):
    def __init__(self):
        pass
    def getimg(self, imgfile):
        try:
            self.imgfp = Image.open(BytesIO(imgfile))
            self.img = self.imgfp.convert("L") # 转灰度
        except:
            print("get validcode image faild")
            return -1
        return 0
    def turn_white(self, thred, flag):
        #flag=0: turn which blacker than thred to white
        #     1  turn which white than thred to white
        pixdata = self.img.load()
        w, h = self.img.size
        for y in range(h):
            for x in range(w):
                if flag == 0 and pixdata[x, y] < 10:
                    pixdata[x, y] = 255
                if flag == 1 and pixdata[x, y] > 100:
                    pixdata[x, y] = 255

    def turn_frame(self):
        pixdata = self.img.load()
        w, h = self.img.size
        for y in range(h):
            for x in range(10):
                pixdata[x, y] = 255
                pixdata[w-x-1, y] = 255
        for y in range(3):
            for x in range(w):
                pixdata[x, y] = 255
                pixdata[x, h-y-1] = 255

    def binarizing(self, threshold):
        """传入image对象进行灰度、二值处理"""
        pixdata = self.img.load()
        w, h = self.img.size
        # 遍历所有像素，大于阈值的为黑色
        for y in range(h):
            for x in range(w):
                if pixdata[x, y] < threshold:
                    pixdata[x, y] = 0
                elif pixdata[x, y] > 256-threshold:
                    pixdata[x, y] = 255

    def depoint(self, val, point):
        """传入二值化后的图片进行降噪"""
        pixdata = self.img.load()
        w,h = self.img.size
        for y in range(1,h-1):
            for x in range(1,w-1):
                count = 0
                if pixdata[x,y-1] > val:#上
                    count = count + 1
                if pixdata[x,y+1] > val:#下
                    count = count + 1
                if pixdata[x-1,y] > val:#左
                    count = count + 1
                if pixdata[x+1,y] > val:#右
                    count = count + 1
                if pixdata[x-1,y-1] > val:#左上
                    count = count + 1
                if pixdata[x-1,y+1] > val:#左下
                    count = count + 1
                if pixdata[x+1,y-1] > val:#右上
                    count = count + 1
                if pixdata[x+1,y+1] > val:#右下
                    count = count + 1
                if count > point:
                    pixdata[x,y] = 255

    def depoint_bl(self, bl, point):
        """传入二值化后的图片进行降噪"""
        pixdata = self.img.load()
        w,h = self.img.size
        for y in range(1,h-1):
            for x in range(1,w-1):
                count = 0
                if pixdata[x,y-1] < bl:#上
                    count = count + 1
                if pixdata[x,y+1] < bl:#下
                    count = count + 1
                if pixdata[x-1,y] < bl:#左
                    count = count + 1
                if pixdata[x+1,y] < bl:#右
                    count = count + 1
                if pixdata[x-1,y-1] < bl:#左上
                    count = count + 1
                if pixdata[x-1,y+1] < bl:#左下
                    count = count + 1
                if pixdata[x+1,y-1] < bl:#右上
                    count = count + 1
                if pixdata[x+1,y+1] < bl:#右下
                    count = count + 1
                if count > point:
                    pixdata[x,y] = 0

    def getcode(self):
        val_wt = 120
        val_bl = 20
        self.turn_white(10, 0)
        self.turn_frame()
        self.binarizing(val_wt)
        #img = depoint_bl(img, val_wt, 5)
        self.depoint(100, 6)
        #img = self.depoint_bl(img, 50, 6)
        self.turn_white(10, 1)
        #img = binarizing(img, 100)

        #with open('kk.jpg', 'wb') as k:
        #    self.img.save(k)
        #result0 = tesserocr.image_to_text(self.img)
        result1 = pytesseract.image_to_string(self.img)
        #print("pytesserocr len:", len(result1), "valid code:", result1)

        return result1

class sse_connect():
    def __init__(self):
        self.test = 0
    def check_validcode(self):
        if self.str_validcode.isnumeric() and len(self.str_validcode) == 4:
            return True
        else:
            return False
    def get_validimg(self, session):
        validpg = session.get(validimg_url, headers=headers1)
        #with open('valid.jpg', 'wb') as pf:
        #        pf.write(validpg.content)
        #validcode = validcode_recog("valid.jpg")
        validcode = validcode_recog()
        if not validcode or validcode.getimg(validpg.content) == -1:
            return None
        self.str_validcode = validcode.getcode()

        return self.check_validcode()

    def refound_param(self, session, pw):
        req = session.get(self.url, headers=headers1)
        if not self.get_validimg(session):
            return -1
        #if not validcode:
        #    validcode = input("input valuecode:")
        int_validcode = list(map(int,list(self.str_validcode)))
        data["winLogin$sfLogin$txtValidate"] = str(sum(int_validcode))

        soup = BeautifulSoup(req.text, 'lxml')
        __VIEWSTATE = soup.find('input', id='__VIEWSTATE')['value']
        data["__VIEWSTATE"] = __VIEWSTATE

        x = session.cookies.items()
        ck = x[0][0]+'='+x[0][1] + '; ' + "UM_distinctid=170a8c3153a0-0cc37e63dd969d-b383f66-e1000-170a8c3153c120; " + x[1][0]+'='+x[1][1]
        headers["Cookie"] = ck
        data["X_STATE"] = teststr3
        data["winLogin$sfLogin$txtPassword"] = pw
        print("pw: ", pw, end=" ")

        return 0

    def create_session(self, url):
        self.url = url
        session = requests.Session()
        return session

    def sse_login(self, session):
        st = session.post(baseurl, data = data, headers = headers)
        #print(st.content.decode('utf-8'))
        #req2 = session.get(stuurl, headers=headers1)
        if st.content.decode('utf-8').find("密码错误") >=0:
            print("pw err")
            return -1
        elif st.content.decode('utf-8').find("验证失败") >= 0:
            print("valid fail")
            return -2
        else:
            print("login success!")
            with open('pw', 'w') as k:
                f.write(data["winLogin$sfLogin$txtPassword"])
            return 0

    def close_session(self, session):
        session.close()

def gen_password(a):
    with open("tmpfile", "w") as f:
        dfs(a, f, "")
def dfs(a, f, tmp):
    #res.append(tmp)
    f.write(tmp+'\n')
    for i in range(len(a)):
        dfs(a[:i]+a[i+1:], f, tmp+(a[i]))

if __name__ == "__main__":
    #bak_pw = ['(',  'F', ')',  '<']# 'T', 't', '>', "?", ',', '.']
    #res = gen_password(bak_pw)
    pw_pre = "123456"

    ret, i= 0, 1
    conn = sse_connect()
    f = open("tmpfile", "r")
    for line in f.readlines():
        print(i, end=" ")
        i += 1
        pw = pw_pre + line.strip()
        while True:
            session = conn.create_session(baseurl)
            if conn.refound_param(session, pw) == -1:
                conn.close_session(session)
                continue
            ret = conn.sse_login(session)
            conn.close_session(session)
            if ret == 0 or ret == -1:
                break
        if ret == 0:
            break
    if f:
        f.close()
