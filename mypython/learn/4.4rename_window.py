import wx
        
class Frame(wx.Frame):
    def __init__(self, parent = None, title = "menu"):
        wx.Frame.__init__(self, parent = None, title = "menu",
                          size = (500, 500), pos = (0, 0))
        self.InitUi()
    
    def InitUi(self):
        panel = wx.Panel(self)
        sizer = wx.GridBagSizer(5, 4)

        text = wx.StaticText(panel, label="Rename To")
        sizer.Add(text, pos=(0, 0), flag=wx.TOP|wx.LEFT|wx.BOTTOM, border=5)

        tc = wx.TextCtrl(panel)
        sizer.Add(tc, pos=(1, 0), span=(1, 5), 
                flag=wx.EXPAND|wx.LEFT|wx.RIGHT, border=5)

        text2 = wx.StaticText(panel, label = 'test')
        sizer.Add(text2, pos = (2, 0), flag = wx.RIGHT, border = 5)
        tc2 = wx.TextCtrl(panel)
        sizer.Add(tc2, pos=(2, 1), span=(1, 5), 
                flag=wx.EXPAND|wx.LEFT|wx.RIGHT, border=5)
        
        buttonOk = wx.Button(panel, label="Ok", size=(90, 28))
        buttonClose = wx.Button(panel, label="Close", size=(90, 28))
        sizer.Add(buttonOk, pos=(4, 3))
        sizer.Add(buttonClose, pos=(4, 4), flag=wx.RIGHT|wx.BOTTOM, border=5)

        sizer.AddGrowableCol(1)
        sizer.AddGrowableRow(2)
        panel.SetSizerAndFit(sizer)

class App(wx.App):
    def OnInit(self):
        self.frame = Frame(parent = None, title = "hello")
        self.frame.Show()
        return True
    
if __name__ == "__main__":
    app = App()
    app.MainLoop()
