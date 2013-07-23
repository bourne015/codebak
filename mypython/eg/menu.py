import wx
class Frame(wx.Frame):
    def __init__(self, parent = None, title = "menu"):
        wx.Frame.__init__(self, parent = None, title = "menu",
                          size = (500, 500), pos = (0, 0))
        self.InitUi()
        
    def InitUi(self):
        menubar1 = wx.MenuBar()
        fileMenu = wx.Menu()
        fileMenu.Append(wx.ID_NEW, '&new')
        fileMenu.Append(wx.ID_OPEN, '&Quit')
        fileMenu.Append(wx.ID_SAVE, '&Save')
        fileMenu.AppendSeparator()

        imp = wx.Menu()
        imp.Append(wx.ID_ANY, 'Import newsfeed list...')
        imp.Append(wx.ID_ANY, 'Import bookmarks...')
        imp.Append(wx.ID_ANY, 'Import mail...')

        fileMenu.AppendMenu(wx.ID_ANY, 'I&mport', imp)

        qmi = wx.MenuItem(fileMenu, wx.ID_EXIT, '&Quit\tCtrl+W')
        fileMenu.AppendItem(qmi)

        self.Bind(wx.EVT_MENU, self.OnQuit, qmi)

        menubar1.Append(fileMenu, '&File1')
        self.SetMenuBar(menubar1)
        
        self.Bind(wx.EVT_MENU, self.OnQuit, qmi)
        
    def OnQuit(self, e):
        self.Close()

    
class App(wx.App):
    def OnInit(self):
        self.frame = Frame(parent = None, title = "hello")
        self.frame.Show()
        return True
    
if __name__ == "__main__":
    app = App()
    app.MainLoop()
