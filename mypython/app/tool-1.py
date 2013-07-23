#A flash and test tool for sony xarina
#20130626. fantao

import wx

#location
CHOOSE_LOC  = (0, 0)
COMBO_LOC   = (0, 1)
BROSWER_LOC = (0, 4)
TYPE_LOC    = (1, 0)

SCRIPT_LOC = (80, 50)
SPL_LOC    = (145, 50)
UBOOT_LOC  = (200, 50)
FW_LOC     = (270, 50)
ROOTFS_LOC = (320, 50)
        
class Frame(wx.Frame):
    def __init__(self, parent = None, title = "menu"):
        wx.Frame.__init__(self, parent = None, title = "menu",
                          size = (500, 450), pos = (0, 0))
        self.InitUi()
        self.Centre()
        
    def InitUi(self):

        #set menubar and statusbar
        self.InitBar()

        panel = wx.Panel(self)

        #set the whole panel into 8 rows and 5 colums
        sizer = wx.GridBagSizer(8, 5)
  
        self.FlashFunction(panel, sizer)
        self.TestFunction(panel, sizer)
        
    def FlashFunction(self, panel, sizer):
        '''
            pain the pannel of Flash Function
        '''
        text2 = wx.StaticText(panel, label="Choose File:")
        sizer.Add(text2, pos=CHOOSE_LOC, flag=wx.LEFT | wx.TOP, border=10)
        
        tc1 = wx.ComboBox(panel)
        sizer.Add(tc1, pos = COMBO_LOC, span=(1, 3),
                  flag=wx.TOP|wx.EXPAND, border = 10)
        
        button0 = wx.Button(panel, label="Browse...")
        sizer.Add(button0, pos=BROSWER_LOC, flag=wx.TOP|wx.RIGHT, border=10)

        text2 = wx.StaticText(panel, label="File Type:")
        sizer.Add(text2, pos=TYPE_LOC, flag=wx.LEFT | wx.TOP, border=15)

        self.ty1 = wx.RadioButton(panel, label='SCRIPT', pos=SCRIPT_LOC)
        self.ty2 = wx.RadioButton(panel, label='S P L', pos=SPL_LOC)
        self.ty3 = wx.RadioButton(panel, label='UBOOT', pos=UBOOT_LOC)
        self.ty4 = wx.RadioButton(panel, label='F W', pos=FW_LOC)
        self.ty5 = wx.RadioButton(panel, label='ROOTFS', pos=ROOTFS_LOC)
        
        text3 = wx.StaticText(panel, label="Address:")
        sizer.Add(text3, pos=(3, 0), flag=wx.LEFT|wx.TOP, border=10)
        
        tc2 = wx.TextCtrl(panel)
        sizer.Add(tc2, pos=(3, 1), span=(1, 3), flag=wx.TOP|wx.EXPAND, 
            border=5)

        text4 = wx.StaticText(panel, label="Size:")
        sizer.Add(text4, pos=(4, 0), flag=wx.TOP|wx.LEFT, border=10)
        
        combo = wx.TextCtrl(panel)
        sizer.Add(combo, pos=(4, 1), span=(1, 3), 
            flag=wx.TOP|wx.EXPAND, border=5)

        flash_button = wx.Button(panel, label="FLASH")
        sizer.Add(flash_button, pos=(5, 4))

        line = wx.StaticLine(panel)
        sizer.Add(line, pos=(6, 0), span=(1, 5), 
            flag=wx.EXPAND|wx.BOTTOM, border=5)

        return True
    
    def TestFunction(self, panel, sizer):
        '''
            pain the panel of test function
        '''
        sb = wx.StaticBox(panel, label="Test")

        boxsizer = wx.StaticBoxSizer(sb, wx.VERTICAL)
        boxsizer.Add(wx.CheckBox(panel, label="CPU"), 
            flag=wx.LEFT|wx.TOP|wx.BOTTOM, border=5)
        boxsizer.Add(wx.CheckBox(panel, label="DDR"),
            flag=wx.LEFT|wx.BOTTOM, border=5)
        boxsizer.Add(wx.CheckBox(panel, label="Flash"), 
            flag=wx.LEFT|wx.BOTTOM, border=5)
        boxsizer.Add(wx.CheckBox(panel, label="test1"),
            flag=wx.LEFT|wx.BOTTOM, border=5)
        sizer.Add(boxsizer, pos=(7, 0), span=(1, 4), 
            flag=wx.EXPAND|wx.TOP|wx.LEFT|wx.RIGHT , border=10)

        button4 = wx.Button(panel, label="START")
        sizer.Add(button4, pos=(7, 4), flag=wx.TOP, border=85)

        sizer.AddGrowableCol(2)
        panel.SetSizer(sizer)

        return True
    
    def InitBar(self):
        '''
            init the menubar and statusbar
        '''      
#TODO: bind some event!!!
        menubar = wx.MenuBar()
        filemenu = wx.Menu()
        confmenu = wx.Menu()
        helpmenu = wx.Menu()
        
        con = wx.Menu()
        con.Append(wx.ID_ANY, 'Serial Port')
        con.Append(wx.ID_ANY, 'TCP/IP')
        filemenu.AppendMenu(wx.ID_ANY, '&Connect', con)
        filemenu.AppendSeparator()
        WinClose = filemenu.Append(wx.ID_EXIT, 'Quit')
        self.Bind(wx.EVT_MENU, self.OnQuit, WinClose)
        
        helpmenu.Append(wx.ID_HELP, 'Help')
        
        menubar.Append(filemenu, "&File")
        menubar.Append(confmenu, "&Configure")
        menubar.Append(helpmenu, "&Help")
        self.SetMenuBar(menubar)

#JUST SET IT, WON'T DO ANYTHING!!!
#!!!TODO: bind some event to me!!!
        statusbar = self.CreateStatusBar()
        statusbar.SetStatusText('Ready')

        return True
    
    def OnQuit(self, a):
        self.Close()
    
class App(wx.App):
    def OnInit(self):
        self.frame = Frame(parent = None, title = "hello")
        self.frame.Show()
        return True
    
if __name__ == "__main__":
    app = App()
    app.MainLoop()
