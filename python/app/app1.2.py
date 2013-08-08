import wx
import test

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

class Frame(wx.Frame):
    def __init__(self, parent = None, title = "Tool"):
        wx.Frame.__init__(self, parent = None, title = "Flash Tool",
                          size = WHOLE_SIZE)
        self.InitUi()
        self.Centre()
        
    def InitUi(self):
        panel = wx.Panel(self)
        sizer = wx.GridBagSizer(ROW, COLUM)
  
        self.FlashFunction(panel, sizer)
        
    def FlashFunction(self, panel, sizer):
        text3 = wx.StaticText(panel, label="ºº×Ö:")
        sizer.Add(text3, pos=ADDR_LOC, flag=wx.LEFT|wx.TOP, border=10)
        
        self.tc2 = wx.TextCtrl(panel)
        sizer.Add(self.tc2, pos=ADDR_TEXT_LOC, span=(1, 3), flag=wx.TOP|wx.EXPAND, 
            border=5)

        text4 = wx.StaticText(panel, label="±àÂë:")
        sizer.Add(text4, pos=SIZE_LOC, flag=wx.TOP|wx.LEFT, border=10)
    
        self.tc3 = wx.TextCtrl(panel)
        sizer.Add(self.tc3, pos=SIZE_TEXT_LOC, span=(1, 3), 
            flag=wx.TOP|wx.EXPAND, border=5)
        
        flash_button = wx.Button(panel, label="×ª»»")
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
            k = test.mydict.get(j.encode('gb2312'))
            if k == None:
                k = 'None'
            val = val + k + ','

        val = val + '0xffaa'
        self.tc3.SetLabel(val)
    
class App(wx.App):
    def OnInit(self):
        self.frame = Frame(parent = None, title = "tool")
        self.frame.Show()
        return True
    
if __name__ == "__main__":
    app = App()
    app.MainLoop()
