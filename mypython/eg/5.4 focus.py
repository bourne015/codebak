import wx
        
class Frame(wx.Frame):
    def __init__(self, parent = None, title = "menu"):
        wx.Frame.__init__(self, parent = None, title = "menu")
        self.InitUi()
    
    def InitUi(self):

        self.color = '#b3b3b3'

        self.Bind(wx.EVT_PAINT, self.OnPaint)
        self.Bind(wx.EVT_SIZE, self.OnSize)
        self.Bind(wx.EVT_SET_FOCUS, self.OnSetFocus)
        self.Bind(wx.EVT_KILL_FOCUS, self.OnKillFocus)

    def OnPaint(self, e):
        
        dc = wx.PaintDC(self)

        dc.SetPen(wx.Pen(self.color))
        x, y = self.GetSize()
        dc.DrawRectangle(0, 0, x, y)

    def OnSize(self, e):
        
        self.Refresh()

    def OnSetFocus(self, e):
        
        self.color = '#0099f7'
        self.Refresh()

    def OnKillFocus(self, e):
        
        self.color = '#b3b3b3'
        self.Refresh()    

        grid = wx.GridSizer(2, 2, 10, 10)
        grid.AddMany([(MyWindow(self), 0, wx.EXPAND|wx.TOP|wx.LEFT, 9),
            (MyWindow(self), 0, wx.EXPAND|wx.TOP|wx.RIGHT, 9), 
            (MyWindow(self), 0, wx.EXPAND|wx.BOTTOM|wx.LEFT, 9), 
            (MyWindow(self), 0, wx.EXPAND|wx.BOTTOM|wx.RIGHT, 9)])

        self.SetSizer(grid)
 

    def OnMove(self, e):
        print e.GetEventObject()
        x, y = e.GetPosition()
        self.st1.SetLabel(str(x))
        self.st2.SetLabel(str(y))


class App(wx.App):
    def OnInit(self):
        self.frame = Frame(parent = None, title = "hello")
        self.frame.Show()
        return True
    
if __name__ == "__main__":
    app = App()
    app.MainLoop()
