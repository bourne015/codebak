import wx
        
class Frame(wx.Frame):
    def __init__(self, parent = None, title = "menu"):
        wx.Frame.__init__(self, parent = None, title = "menu",
                          size = (400, 400))
        self.InitUi()
    
    def InitUi(self):
        pnl = wx.Panel(self)
        
        self.col = wx.Colour(0, 0, 0)

        rtb = wx.ToggleButton(pnl, label='red', pos=(20, 25))
        gtb = wx.ToggleButton(pnl, label='green', pos=(20, 60))
        btb = wx.ToggleButton(pnl, label='blue', pos=(20, 100))

        self.cpnl  = wx.Panel(pnl, pos=(150, 20), size=(110, 110))
        self.cpnl.SetBackgroundColour(self.col)

        rtb.Bind(wx.EVT_TOGGLEBUTTON, self.ToggleRed)
        gtb.Bind(wx.EVT_TOGGLEBUTTON, self.ToggleGreen)
        btb.Bind(wx.EVT_TOGGLEBUTTON, self.ToggleBlue)

    def ToggleRed(self, e):
        
        obj = e.GetEventObject()
        isPressed = obj.GetValue()
        
        green = self.col.Green()
        blue = self.col.Blue()
        
        if isPressed:
            self.col.Set(255, green, blue)
        else:
            self.col.Set(0, green, blue)
            
        self.cpnl.SetBackgroundColour(self.col)

    def ToggleGreen(self, e):
        
        obj = e.GetEventObject()
        isPressed = obj.GetValue()
        
        red = self.col.Red()
        blue = self.col.Blue()        
        
        if isPressed:
            self.col.Set(red, 255, blue)
        else:
            self.col.Set(red, 0, blue)
            
        self.cpnl.SetBackgroundColour(self.col)

    def ToggleBlue(self, e):
        
        obj = e.GetEventObject()
        isPressed = obj.GetValue()
        
        red = self.col.Red()
        green = self.col.Green()        
        
        if isPressed:
            self.col.Set(red, green, 255)
        else:
            self.col.Set(red, green, 0)
            
        self.cpnl.SetBackgroundColour(self.col) 



class App(wx.App):
    def OnInit(self):
        self.frame = Frame(parent = None, title = "hello")
        self.frame.Show()
        return True
    
if __name__ == "__main__":
    app = App()
    app.MainLoop()
