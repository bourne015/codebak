import wx

#the whole panel set into
#   8 rows and 5 colums
ROW   = 9
COLUM = 5
WHOLE_SIZE  = (400, 200)

#int row 3-8
ADDR_LOC        = (1, 0)
ADDR_TEXT_LOC   = (1, 1)
SIZE_LOC        = (2, 0)
SIZE_TEXT_LOC   = (2, 1)

BUTT_FLASH_LOC  = (3, 3)

mydict = {
        '你':'0x100', '好':'0x015','你好':'12',
        '我':'0x200', '他':'0x300',
        '版':'0x065', '本':'0x06a'
        }

class Frame(wx.Frame):
    def __init__(self, parent = None, title = "Tool"):
        wx.Frame.__init__(self, parent = None, title = title,
                          size = WHOLE_SIZE)
        self.InitUi()
        self.Centre()
        
    def InitUi(self):
        panel = wx.Panel(self)
        sizer = wx.GridBagSizer(ROW, COLUM)
  
        self.FlashFunction(panel, sizer)
        
    def FlashFunction(self, panel, sizer):
        text3 = wx.StaticText(panel, label=":")
        sizer.Add(text3, pos=ADDR_LOC, flag=wx.LEFT|wx.TOP, border=10)
        
        self.tc2 = wx.TextCtrl(panel)
        sizer.Add(self.tc2, pos=ADDR_TEXT_LOC, span=(1, 2), flag=wx.TOP|wx.EXPAND, 
            border=5)

        text4 = wx.StaticText(panel, label=":")
        sizer.Add(text4, pos=SIZE_LOC, flag=wx.TOP|wx.LEFT, border=10)
    
        self.tc3 = wx.TextCtrl(panel)
        sizer.Add(self.tc3, pos=SIZE_TEXT_LOC, span=(1, 2), 
            flag=wx.TOP|wx.EXPAND, border=5)
        
        flash_button = wx.Button(panel, label="")
        sizer.Add(flash_button, pos=BUTT_FLASH_LOC)
        self.Bind(wx.EVT_BUTTON, self.StartFlash, flash_button)
        sizer.AddGrowableCol(2)
        panel.SetSizer(sizer)

    def StartFlash(self, a):
        text = self.tc2.GetValue()
        if text == '':
            return False
        
        l = []

        for i in text:
            l.append(i)

        val = ''
        for j in l:
            k = mydict.get(j.encode('gb2312'))
            if k == None:
                k = 'none'
            val = val + k + ','

        val = val + '0xfaa'
        self.tc3.SetLabel(val)
    
class App(wx.App):
    def OnInit(self):
        self.frame = Frame(parent = None, title = "tool")
        self.frame.Show()
        return True
    
if __name__ == "__main__":
    app = App()
    app.MainLoop()
