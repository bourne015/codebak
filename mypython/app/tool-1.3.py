#A flash and test tool for sony xarina
#20130626. fantao
import wx
import os

#the whole panel set into
#   8 rows and 5 colums
ROW   = 8
COLUM = 5

#location, in row 1
CHOOSE_LOC  = (0, 0)
COMBO_LOC   = (0, 1)
BROSWER_LOC = (0, 4)
TYPE_LOC    = (1, 0)

#in row 2
SCRIPT_LOC = (85,  60)
SPL_LOC    = (150, 60)
UBOOT_LOC  = (205, 60)
FW_LOC     = (275, 60)
ROOTFS_LOC = (325, 60)

#int row 3-8
ADDR_LOC        = (3, 0)
ADDR_TEXT_LOC   = (3, 1)
SIZE_LOC        = (4, 0)
SIZE_TEXT_LOC   = (4, 1)
BUTT_FLASH_LOC  = (5, 4)
SEPARA_LINE_LOC = (6, 0)
BOX_TEST_LOC    = (7, 0)
TEST_ITEM_LOC   = (7, 1)
BUTT_START_LOC  = (7, 4)

class Frame(wx.Frame):
    def __init__(self, parent = None, title = "Tool"):
        wx.Frame.__init__(self, parent = None, title = "Flash Tool",
                          size = (520, 410))
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
        sizer.Add(text2, pos=CHOOSE_LOC, flag=wx.LEFT | wx.TOP, border=10)
        
        self.tc1 = wx.ComboBox(panel)
        sizer.Add(self.tc1, pos = COMBO_LOC, span=(1, 3),
                  flag=wx.TOP|wx.EXPAND, border = 10)
        
        button0 = wx.Button(panel, label="Browse")
        sizer.Add(button0, pos=BROSWER_LOC, flag=wx.TOP|wx.RIGHT, border=10)
        self.Bind(wx.EVT_BUTTON, self.ChoosFile, button0)

        text2 = wx.StaticText(panel, label="File Type:")
        sizer.Add(text2, pos=TYPE_LOC, flag=wx.LEFT | wx.TOP, border=10)
        
        self.Butn_Scr = wx.RadioButton(panel, label='SCRIPT', pos=SCRIPT_LOC)
        self.Bind(wx.EVT_RADIOBUTTON, self.Set_Addr, self.Butn_Scr)
        self.Butn_Spl = wx.RadioButton(panel, label='S P L', pos=SPL_LOC)
        self.Bind(wx.EVT_RADIOBUTTON, self.Set_Addr, self.Butn_Spl)
        Butn_Ubt = wx.RadioButton(panel, label='UBOOT', pos=UBOOT_LOC)
        Butn_Fw  = wx.RadioButton(panel, label='F W', pos=FW_LOC)
        Butn_Fs  = wx.RadioButton(panel, label='ROOTFS', pos=ROOTFS_LOC)
        
        text3 = wx.StaticText(panel, label="Address:")
        sizer.Add(text3, pos=ADDR_LOC, flag=wx.LEFT|wx.TOP, border=10)
        
        self.tc2 = wx.TextCtrl(panel)
        sizer.Add(self.tc2, pos=ADDR_TEXT_LOC, span=(1, 3), flag=wx.TOP|wx.EXPAND, 
            border=5)

        text4 = wx.StaticText(panel, label="Size:")
        sizer.Add(text4, pos=SIZE_LOC, flag=wx.TOP|wx.LEFT, border=10)
    
        self.tc3 = wx.TextCtrl(panel)
        sizer.Add(self.tc3, pos=SIZE_TEXT_LOC, span=(1, 3), 
            flag=wx.TOP|wx.EXPAND, border=5)

        flash_button = wx.Button(panel, label="FLASH")
        sizer.Add(flash_button, pos=BUTT_FLASH_LOC)

        line = wx.StaticLine(panel)
        sizer.Add(line, pos=SEPARA_LINE_LOC, span=(1, 5), 
            flag=wx.EXPAND|wx.BOTTOM, border=0)

        return True
    
    def TestFunction(self, panel, sizer):
        '''
            pain the panel of test function
        '''
        text5 = wx.StaticText(panel, label="Test Items:")
        sizer.Add(text5, pos=BOX_TEST_LOC, flag=wx.LEFT|wx.TOP, border=10)

        item = wx.GridSizer(7, 6, 0, 0)
        item.AddMany([wx.CheckBox(panel, label="CPU"),
                      wx.CheckBox(panel, label="DDR"),
                      wx.CheckBox(panel, label="Flash"),
                      wx.CheckBox(panel, label="none"),
                      wx.CheckBox(panel, label="none"),
                      wx.CheckBox(panel, label="none"),
                      wx.CheckBox(panel, label="none"),
                      wx.CheckBox(panel, label="none")])
        sizer.Add(item, pos=TEST_ITEM_LOC, span=(1, 3), 
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
        menubar  = wx.MenuBar()
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

        conf_uart = confmenu.Append(wx.ID_ANY, 'Serial Port')
        self.Bind(wx.EVT_TOOL, self.ConfUart, conf_uart)
        
        conf_tcp = confmenu.Append(wx.ID_ANY, 'TCP/IP')
        self.Bind(wx.EVT_TOOL, self.ConfTcp, conf_tcp)

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
    
    def ConfUart(self, e):    
        serial = Configure(None, title='Configure the serial port')
        serial.Ui_Uart()
        serial.SetSize((270, 320))
        serial.ShowModal()
        serial.Destroy()
        
    def ConfTcp(self, e):
        Tcp = Configure(None, title='Configure TCP/IP')
        Tcp.Ui_Tcp()
        Tcp.SetSize((300, 160))
        Tcp.ShowModal()
        Tcp.Destroy()
        
    def OnQuit(self, a):
        self.Close()

    def ChoosFile(self, a):
        wildcard = "All files (*.*)|*.*|" \
                   "Script file (*.ush)|*.ush|" \
                   "Binary file (*.bin)|*.bin|" \
                   "FW file (*.img)|*.img"
        dialog = wx.FileDialog(None, "Choose a file", os.getcwd(),
                           "", wildcard, wx.OPEN)
        if dialog.ShowModal() == wx.ID_OK:
            file = dialog.GetPath()

        dialog.Destroy()
        self.tc1.SetLabel(file)

        return file
    
    def Set_Addr(self, a):
        self.tc2.SetLabel('0x61000000')
        self.tc3.SetLabel('0x10000')

        return True
    
class Configure(wx.Dialog):
    def __init__(self, parent = None,
                 title = "Configure the Serial Port"):
        wx.Dialog.__init__(self, parent, title = title)   
        #self.Ui_Uart()
        #self.SetSize((270, 320))
    
    def Ui_Uart(self):
        pan = wx.Panel(self)
        sizer = wx.GridBagSizer(8, 8)

        Port_Cho = ['Port 1', 'Port 2']
        text1 = wx.StaticText(pan, label="Port:")
        sizer.Add(text1, pos=(0, 0), flag=wx.LEFT | wx.TOP, border=15)
        
        #self.con1 = wx.ComboBox(pan, choices = Port_Cho)
        self.con1 = wx.Choice(pan, -1, choices=Port_Cho, validator = Port_Cho[1])
        sizer.Add(self.con1, pos = (0, 1), span=(1, 1),
                  flag=wx.TOP|wx.EXPAND, border = 10)

        BaudRt_Cho = ['9600', '38400', '115200']       
        text2 = wx.StaticText(pan, label="BaudRate:")
        sizer.Add(text2, pos=(1, 0), flag=wx.LEFT | wx.TOP, border=15)       
        self.tc2 = wx.ComboBox(pan, choices = BaudRt_Cho)
        sizer.Add(self.tc2, pos = (1, 1), span=(1, 1),
                  flag=wx.TOP|wx.EXPAND, border = 5)

        Data_Cho = ['8 bit', '7 bit']
        text2 = wx.StaticText(pan, label="Data:")
        sizer.Add(text2, pos=(2, 0), flag=wx.LEFT | wx.TOP, border=15)       
        self.tc2 = wx.ComboBox(pan, choices = Data_Cho)
        sizer.Add(self.tc2, pos = (2, 1), span=(1, 1),
                  flag=wx.TOP|wx.EXPAND, border = 5)

        Parity_Cho = ['none', 'odd', 'even', 'space']
        text2 = wx.StaticText(pan, label="Parity:")
        sizer.Add(text2, pos=(3, 0), flag=wx.LEFT | wx.TOP, border=15)       
        self.tc2 = wx.ComboBox(pan, choices = Parity_Cho)
        sizer.Add(self.tc2, pos = (3, 1), span=(1, 1),
                  flag=wx.TOP|wx.EXPAND, border = 5)
        
        Stop_Cho = ['1 bit', '1.5 bit', '2 bit']
        text2 = wx.StaticText(pan, label="Stop:")
        sizer.Add(text2, pos=(4, 0), flag=wx.LEFT | wx.TOP, border=15)       
        self.tc2 = wx.ComboBox(pan, choices = Stop_Cho)
        sizer.Add(self.tc2, pos = (4, 1), span=(1, 1),
                  flag=wx.TOP|wx.EXPAND, border = 5)

        Flow_Cho = ['none', 'Xon/Xoff', 'hardware']
        text2 = wx.StaticText(pan, label="Flow Control:")
        sizer.Add(text2, pos=(5, 0), flag=wx.LEFT | wx.TOP, border=15)       
        self.tc2 = wx.ComboBox(pan, choices = Flow_Cho)
        sizer.Add(self.tc2, pos = (5, 1), span=(1, 1),
                  flag=wx.TOP|wx.EXPAND, border = 5)
                
        OkBtn = wx.Button(pan, label='Ok')
        CloBtn = wx.Button(pan, label='Close')
        sizer.Add(OkBtn, pos = (7, 0),flag=wx.LEFT, border = 45)
        sizer.Add(CloBtn, pos = (7, 1),flag=wx.RIGHT, border = 35)
        self.Bind(wx.EVT_BUTTON, self.OnClose, CloBtn)
        sizer.AddGrowableCol(2)
        pan.SetSizer(sizer)

    def Ui_Tcp(self):
        pan = wx.Panel(self)
        sizer = wx.GridBagSizer(2, 5)

        text1 = wx.StaticText(pan, label="Board IP:")
        sizer.Add(text1, pos=(0, 0), flag=wx.LEFT | wx.TOP, border=15)
        
        self.con1 = wx.TextCtrl(pan)
        sizer.Add(self.con1, pos = (0, 1), span=(1, 5),
                  flag=wx.TOP, border = 10)

        OkBtn = wx.Button(pan, label='Ok')
        CloBtn = wx.Button(pan, label='Close')
        sizer.Add(OkBtn, pos = (3, 0),flag=wx.LEFT, border = 65)
        sizer.Add(CloBtn, pos = (3, 1),flag=wx.RIGHT, border = 75)
        self.Bind(wx.EVT_BUTTON, self.OnClose, CloBtn)

        sizer.AddGrowableCol(2)
        pan.SetSizer(sizer)
        
    def OnClose(self, e):
        self.Destroy()
        
class App(wx.App):
    def OnInit(self):
        self.frame = Frame(parent = None, title = "tool")
        self.frame.Show()
        return True
    
if __name__ == "__main__":
    app = App()
    app.MainLoop()
