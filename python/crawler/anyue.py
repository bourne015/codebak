import urllib
from urllib.request import urlopen
from bs4 import BeautifulSoup
import re

#url = "http://www.gushiwen.org/default_1.aspx"
baseurl = "http://www.gushiwen.org/default_"
user_agent = 'Mozilla/4.0 (compatible; MSIE 5.5; Windows NT)'
headers = { 'User-Agent' : user_agent }
page_cnt = 10

def output_all(title, author, content, len):
    for i in range(0,len):
        print("--------------------------------------")
        print(title[i].get_text())
        print(author[i].get_text())
        print(content[i].get_text())
        #print(len(title))

def output_an(title, author, content, len):
    for i in range(0,len):
        if re.search(r'月', content[i].get_text()):
            k=re.search(r'月', content[i].get_text()).span()[0]
            print("--------------------------------------")
            print(title[i].get_text())
            print(author[i].get_text())
            #print(content[i].get_text())
            #print('%s' %(title[i].get_text()[0:k]))
            print('%s\033[1;35m%s\033[0m%s' %(content[i].get_text()[0:k],
                                            '月',content[i].get_text()[k+1:]))

def get_page(bsObj):
    i = 0
    title = bsObj.findAll("a",{"style":{"font-size:18px; line-height:22px; height:22px;"}} )
    author = bsObj.findAll("p", {"class":{"source"}})
    content = bsObj.findAll("div", {"class":{"contson"}})
    #output_all(title, author, content, len(title))
    output_an(title, author, content, len(title))

if __name__ == "__main__":
    for i in range(1,page_cnt):
        url = baseurl+ str(i) + ".aspx"
        request = urllib.request.Request(url, headers=headers)
        html = urlopen(request)
        bsObj = BeautifulSoup(html)
        get_page(bsObj)


