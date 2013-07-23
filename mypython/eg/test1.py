import wx

class Frame(wx.Frame):
    def __init__(self, parent = None, title = 'test'):
        wx.Frame.__init__(self, parent = None, title='test', 
                            size=(260, 180))   

        self.SetUi()
    #    
    def SetUi(self):
        panel = wx.Panel(self)

        vbox = wx.BoxSizer(wx.VERTICAL)

        midPan = wx.Panel(panel)
        midPan.SetBackgroundColour('red')

        vbox.Add(midPan, 1, wx.EXPAND | wx.ALL, 20)
        panel.SetSizer(vbox)

class App(wx.App):
    def OnInit(self):
        self.frame = wx.Frame(parent = None, title = "test")
        self.frame.Show()
        return True

if __name__ == '__main__':
    app = App()
    app.MainLoop()

