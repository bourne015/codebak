import urllib
from urllib.request import urlopen
from bs4 import BeautifulSoup
import re

baseurl = "http://www.yingjiesheng.com/commend-parttime-"
user_agent = 'Mozilla/4.0 (compatible; MSIE 5.5; Windows NT)'
headers = { 'User-Agent' : user_agent }
page_cnt = 20

def get_page2(bs_obj):
    target = ""
    for tr in bs_obj.find_all('tr'):
        tds = tr.find_all('td')
        try:
            emphasis = ""
            company  = tds[0].contents[1].contents[-1].strip()
            addr     = tds[0].contents[1].contents[-2].text.strip()
            suburl   = tds[0].find('a')['href']
            dsdate   = tds[1].contents[0]
            if "http" not in suburl:
                suburl = "http://www.yingjiesheng.com" + suburl
            if len(tds[0].contents[1].contents) > 2:
                emphasis = tds[0].contents[1].contents[-4].text.strip()

            if "平安" in company:
                print(emphasis, addr, company, dsdate, "\n", suburl, "\n")
        except:
            pass

if __name__ == "__main__":
    for i in range(1, page_cnt):
        url = baseurl+ str(i) + ".html"
        request = urllib.request.Request(url, headers=headers)
        html = urlopen(request)
        bs_obj = BeautifulSoup(html)
        get_page2(bs_obj)
