import wx

class Example(wx.Frame):
  
    def __init__(self, parent, title):
        super(Example, self).__init__(parent, title=title, 
            size=(460, 480))
            
        self.InitUI()
        self.Centre()
        self.Show()     
        
    def InitUI(self):
    
        pan = wx.Panel(self)
        sizer = wx.GridBagSizer(7, 7)
        text1 = wx.StaticText(pan, label="Workstation")
        sizer.Add(text1, pos=(7, 7), span = (3, 1), flag=wx.TOP | wx.LEFT| wx.EXPAND, 
            border=1)
        
        #panel.SetSizer(vbox)


if __name__ == '__main__':
  
    app = wx.App()
    Example(None, title='Border')
    app.MainLoop()
