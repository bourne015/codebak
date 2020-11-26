import urllib
from urllib.request import urlopen
from bs4 import BeautifulSoup
import re

baseurl = "http://t66y.com/thread0806.php?fid=22&search=&page="
user_agent = 'Mozilla/4.0 (compatible; MSIE 5.5; Windows NT)'
headers = { 'User-Agent' : user_agent }
page_cnt = 300

def output_all(title):
    aaa = "name"
    for i in title:
        txt = i.get_text()
        if aaa in txt:
            print("--------------------------------------")
            print(txt)
            print("http://t66y.com/"+i.get("href"))

def get_page(bs_obj):
    title = bs_obj.findAll("a",{"target":{"_blank"}, "id":{""}}, href=True)
    output_all(title)

#状态  |文章   |作者  |回复  |最后发表
#td[0] |td[1]  |td[2] |td[3] |
def get_page2(bs_obj):
    target = "somekeyword"
    for idx, tr in enumerate(bs_obj.find_all('tr')):
        tds = tr.find_all('td')
        try:
            title = tds[1].contents[1].text.strip()
            addr  = tds[1].contents[1].find('a')['href']
            reply = tds[3].contents[0]
            if target in title:
                print("---------------------------------------")
                print(title, reply)
                print("http://t66y.com/"+addr+"\n")
        except:
            pass

if __name__ == "__main__":
    for i in range(1, page_cnt):
        url = baseurl+ str(i)
        request = urllib.request.Request(url, headers=headers)
        html = urlopen(request)
        bs_obj = BeautifulSoup(html)
        get_page2(bs_obj)
