import wx
        
class Frame(wx.Frame):
    def __init__(self, parent = None, title = "menu"):
        wx.Frame.__init__(self, parent = None, title = "menu")
        self.InitUi()
    
    def InitUi(self):
        wx.FutureCall(1000, self.ShowMessage)

        self.SetSize((300, 200))
        self.SetTitle('Message box')

    def ShowMessage(self):
        wx.MessageBox('Download completed', 'Info', 
            wx.OK | wx.ICON_INFORMATION)



class App(wx.App):
    def OnInit(self):
        self.frame = Frame(parent = None, title = "hello")
        self.frame.Show()
        return True
    
if __name__ == "__main__":
    app = App()
    app.MainLoop()
