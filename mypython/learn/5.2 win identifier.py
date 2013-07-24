import wx
        
class Frame(wx.Frame):
    def __init__(self, parent = None, title = "menu"):
        wx.Frame.__init__(self, parent = None, title = "menu",
                          size = (500, 400), pos = (0, 0))
        self.InitUi()

    
    def InitUi(self):

        pnl = wx.Panel(self)
        exitButton = wx.Button(pnl, wx.ID_ANY, 'Exit', (10, 10))

        self.Bind(wx.EVT_BUTTON,  self.OnExit, exitButton)

        self.SetTitle("Automatic id")
        self.Centre()
        self.Show(True)

    def OnExit(self, event):
        self.Close()

class App(wx.App):
    def OnInit(self):
        self.frame = Frame(parent = None, title = "hello")
        self.frame.Show()
        return True
    
if __name__ == "__main__":
    app = App()
    app.MainLoop()
