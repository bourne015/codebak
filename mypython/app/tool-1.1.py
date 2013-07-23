#A flash and test tool for sony xarina
#20130626. fantao

import wx

#the whole panel set into
#8 rows and 5 coluns
ROW   = 8
COLUM = 5

#location, in row 1
CHOOSE_LOC  = (0, 0)
COMBO_LOC   = (0, 1)
BROSWER_LOC = (0, 4)
TYPE_LOC    = (1, 0)

#in row 2
SCRIPT_LOC = (80,  65)
SPL_LOC    = (145, 65)
UBOOT_LOC  = (200, 65)
FW_LOC     = (270, 65)
ROOTFS_LOC = (320, 65)

#int row 3-8
ADDR_LOC        = (3, 0)
ADDR_TEXT_LOC   = (3, 1)
SIZE_LOC        = (4, 0)
SIZE_TEXT_LOC   = (4, 1)
BUTT_FLASH_LOC  = (5, 4)
SEPARA_LINE_LOC = (6, 0)
BOX_TEST_LOC    = (7, 0)
TEST_ITEM_LOC   = (8, 1)
BUTT_START_LOC  = (8, 4)

class Frame(wx.Frame):
    def __init__(self, parent = None, title = "menu"):
        wx.Frame.__init__(self, parent = None, title = "Flash Tool",
                          size = (500, 450), pos = (0, 0))
        self.InitUi()
        self.Centre()
        
    def InitUi(self):

        #set menubar and statusbar
        self.InitBar()

        panel = wx.Panel(self)

        #set the whole panel into 8 rows and 5 colums
        sizer = wx.GridBagSizer(ROW, COLUM)
  
        self.FlashFunction(panel, sizer)
        self.TestFunction(panel, sizer)
        
    def FlashFunction(self, panel, sizer):
        '''
            pain the pannel of Flash Function
        '''
        text2 = wx.StaticText(panel, label="Choose File:")
        sizer.Add(text2, pos=CHOOSE_LOC, flag=wx.LEFT | wx.TOP, border=15)
        
        tc1 = wx.ComboBox(panel)
        sizer.Add(tc1, pos = COMBO_LOC, span=(1, 3),
                  flag=wx.TOP|wx.EXPAND, border = 15)
        
        button0 = wx.Button(panel, label="Browse...")
        sizer.Add(button0, pos=BROSWER_LOC, flag=wx.TOP|wx.RIGHT, border=15)

        text2 = wx.StaticText(panel, label="File Type:")
        sizer.Add(text2, pos=TYPE_LOC, flag=wx.LEFT | wx.TOP, border=15)

        wx.RadioButton(panel, label='SCRIPT', pos=SCRIPT_LOC)
        wx.RadioButton(panel, label='S P L', pos=SPL_LOC)
        wx.RadioButton(panel, label='UBOOT', pos=UBOOT_LOC)
        wx.RadioButton(panel, label='F W', pos=FW_LOC)
        wx.RadioButton(panel, label='ROOTFS', pos=ROOTFS_LOC)
        
        text3 = wx.StaticText(panel, label="Address:")
        sizer.Add(text3, pos=ADDR_LOC, flag=wx.LEFT|wx.TOP, border=10)
        
        tc2 = wx.TextCtrl(panel)
        sizer.Add(tc2, pos=ADDR_TEXT_LOC, span=(1, 3), flag=wx.TOP|wx.EXPAND, 
            border=5)

        text4 = wx.StaticText(panel, label="Size:")
        sizer.Add(text4, pos=SIZE_LOC, flag=wx.TOP|wx.LEFT, border=10)
    
        combo = wx.TextCtrl(panel)
        sizer.Add(combo, pos=SIZE_TEXT_LOC, span=(1, 3), 
            flag=wx.TOP|wx.EXPAND, border=5)

        flash_button = wx.Button(panel, label="FLASH")
        sizer.Add(flash_button, pos=BUTT_FLASH_LOC)

        line = wx.StaticLine(panel)
        sizer.Add(line, pos=SEPARA_LINE_LOC, span=(1, 5), 
            flag=wx.EXPAND|wx.BOTTOM, border=5)

        return True
    
    def TestFunction(self, panel, sizer):
        '''
            pain the panel of test function
        '''
        sb = wx.StaticBox(panel, label="Test")
        '''
        boxsizer = wx.StaticBoxSizer(sb, wx.VERTICAL)
        boxsizer.Add(wx.CheckBox(panel, label="CPU"), 
            flag=wx.LEFT|wx.TOP|wx.BOTTOM, border=5)
        boxsizer.Add(wx.CheckBox(panel, label="DDR"),
            flag=wx.LEFT|wx.BOTTOM, border=5)
        boxsizer.Add(wx.CheckBox(panel, label="Flash"), 
            flag=wx.LEFT|wx.BOTTOM, border=5)
        boxsizer.Add(wx.CheckBox(panel, label="test1"),
            flag=wx.LEFT|wx.BOTTOM, border=5)
        sizer.Add(boxsizer, pos=BOX_TEST, span=(1, 3), 
            flag=wx.EXPAND|wx.TOP|wx.LEFT|wx.RIGHT , border=10)
        '''
        item = wx.GridSizer(5, 5, 0, 0)
        item.AddMany([wx.CheckBox(panel, label="CPU"),
                      wx.CheckBox(panel, label="DDR"),
                      wx.CheckBox(panel, label="Flash"),
                      wx.CheckBox(panel, label="none"),
                      wx.CheckBox(panel, label="none"),
                      wx.CheckBox(panel, label="none")])
        sizer.Add(item, pos=TEST_ITEM_LOC, span=(1, 3), 
            flag=wx.EXPAND|wx.TOP|wx.LEFT|wx.RIGHT , border=10)
        boxsizer = wx.StaticBoxSizer(sb, wx.VERTICAL)
        sizer.Add(boxsizer, pos=BOX_TEST_LOC, span=(1, 4), 
            flag=wx.EXPAND|wx.TOP|wx.LEFT|wx.RIGHT , border=10)
        
        button4 = wx.Button(panel, label="START")
        sizer.Add(button4, pos=BUTT_START_LOC, flag=wx.TOP, border=85)

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
        
        connect = wx.Menu()
        connect.Append(wx.ID_ANY, 'Serial Port')
        connect.Append(wx.ID_ANY, 'TCP/IP')
        filemenu.AppendMenu(wx.ID_ANY, '&Connect', connect)
        filemenu.AppendSeparator()
        
        WinClose = filemenu.Append(wx.ID_EXIT, 'Quit')
        self.Bind(wx.EVT_MENU, self.OnQuit, WinClose)

        confmenu.Append(wx.ID_ANY, 'Serial Port')
        confmenu.Append(wx.ID_ANY, 'TCP/IP')

        helpmenu.Append(wx.ID_ANY, 'Help')
        helpmenu.Append(wx.ID_ANY, 'About')
        
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
