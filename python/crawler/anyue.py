import urllib
from urllib.request import urlopen
from bs4 import BeautifulSoup
import re

#url = "http://www.gushiwen.org/default_1.aspx"
#baseurl = "http://www.gushiwen.org/default_"
baseurl = "https://so.gushiwen.cn/shiwen/default_0AA"
user_agent = 'Mozilla/4.0 (compatible; MSIE 5.5; Windows NT)'
headers = { 'User-Agent' : user_agent }
page_cnt = 100

def output_all(title, author, content, len):
    for i in range(0,len):
        print("--------------------------------------")
        print(title[i].get_text())
        print(author[i].get_text())
        print(content[i].get_text())
        #print(len(title))

def output_an(title, author, content, len, f):
    name1 = '铄'
    name2 = ''
    for i in range(0,len):
        if re.search(str(name1), content[i].get_text()):
            k=re.search(str(name1), content[i].get_text()).span()[0]
            print("--------------------------------------")
            tt_tex = title[i].get_text()
            at_tex = author[i].get_text()
            ct_tex = content[i].get_text()
            print(tt_tex, at_tex)
            #print('%s' %(title[i].get_text()[0:k]))
            print('%s\033[1;35m%s\033[0m%s' %(content[i].get_text()[0:k],
                                            name1,content[i].get_text()[k+1:]))
            f.write(tt_tex + at_tex + ct_tex + '\n')

def get_page(bsObj, f):
    i = 0
    title = bsObj.findAll("a",{"style":{"font-size:18px; line-height:22px; height:22px;"}} )
    author = bsObj.findAll("p", {"class":{"source"}})
    content = bsObj.findAll("div", {"class":{"contson"}})
    #output_all(title, author, content, len(title))
    output_an(title, author, content, len(title), f)

if __name__ == "__main__":
    f = open("tmpfile", "w")
    for i in range(1,page_cnt+1):
        print("page: ", i)
        url = baseurl+ str(i) + ".aspx"
        request = urllib.request.Request(url, headers=headers)
        html = urlopen(request)
        bsObj = BeautifulSoup(html)
        get_page(bsObj, f)
    if f:
        f.close()


