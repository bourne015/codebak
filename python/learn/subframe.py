import wx

class Frame(wx.Frame):
    def __init__(self, parent = None, title = "he"):
        print title
        wx.Frame.__init__(self, parent = None, title = "hel")
        
class App(wx.App):
        
    def OnInit(self):
        frame = Frame(parent = None, title = "hello")
        frame.Show()
        return True
    
if __name__ == "__main__":
    app = App()
    app.MainLoop()
