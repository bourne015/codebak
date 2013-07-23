import wx

TASK_RANGE = 50
       
class Frame(wx.Frame):
    def __init__(self, parent = None, title = "menu"):
        wx.Frame.__init__(self, parent = None, title = "menu",
                          size = (400, 400))
        self.InitUi()
    
    def InitUi(self):
        pnl = wx.Panel(self)

        sld = wx.Slider(pnl, value=200, minValue=150, maxValue=500, pos=(20, 20), 
            size=(250, -1), style=wx.SL_HORIZONTAL)
        
        sld.Bind(wx.EVT_SCROLL, self.OnSliderScroll)
        
        self.txt = wx.StaticText(pnl, label='200', pos=(20, 90))
        
    def OnSliderScroll(self, e):
        
        obj = e.GetEventObject()
        val = obj.GetValue()
        
        self.txt.SetLabel(str(val)) 
 
        
class App(wx.App):
    def OnInit(self):
        self.frame = Frame(parent = None, title = "hello")
        self.frame.Show()
        return True
    
if __name__ == "__main__":
    app = App()
    app.MainLoop()
