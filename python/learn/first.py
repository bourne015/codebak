import wx
class App(wx.App):
    def OnInit(self):
        Frame = wx.Frame(parent = None, title = "hello")
        Frame.Show()
        return True
    
if __name__ == "__main__":
    app = App()
    app.MainLoop()
