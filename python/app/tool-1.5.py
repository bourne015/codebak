#A flash and test tool for sony xarina
#20130626. fantao
import wx
import os
import socket

TASK_RANGE = 10 # used in gague, shoule find new workround

#the whole panel set into
#   8 rows and 5 colums
ROW   = 9
COLUM = 5
WHOLE_SIZE  = (520, 415)

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
                          size = WHOLE_SIZE)
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
        text1 = wx.StaticText(panel, label="Choose File:")
        sizer.Add(text1, pos=CHOOSE_LOC, flag=wx.LEFT | wx.TOP, border=10)
        
        self.tc1 = wx.ComboBox(panel)
        sizer.Add(self.tc1, pos = COMBO_LOC, span=(1, 3),
                  flag=wx.TOP|wx.EXPAND, border = 10)
        
        button0 = wx.Button(panel, label="Browse")
        sizer.Add(button0, pos=BROSWER_LOC, flag=wx.TOP|wx.RIGHT, border=10)
        self.Bind(wx.EVT_BUTTON, self.ChoosFile, button0)

        text2 = wx.StaticText(panel, label="File Type:")
        sizer.Add(text2, pos=TYPE_LOC, flag=wx.LEFT | wx.TOP, border=10)
        
        self.Butn_Scr = wx.RadioButton(panel, label='SCRIPT', pos=SCRIPT_LOC)  
        self.Butn_Spl = wx.RadioButton(panel, label='S P L', pos=SPL_LOC)
        self.Butn_Ubt = wx.RadioButton(panel, label='UBOOT', pos=UBOOT_LOC)
        self.Butn_Fw  = wx.RadioButton(panel, label='F W', pos=FW_LOC)
        self.Butn_Fs  = wx.RadioButton(panel, label='ROOTFS', pos=ROOTFS_LOC)
        self.Bind(wx.EVT_RADIOBUTTON, self.Addr_Src, self.Butn_Scr)
        self.Bind(wx.EVT_RADIOBUTTON, self.Addr_Spl, self.Butn_Spl)
        self.Bind(wx.EVT_RADIOBUTTON, self.Addr_Uboot, self.Butn_Ubt)
        self.Bind(wx.EVT_RADIOBUTTON, self.Addr_Fw, self.Butn_Fw)
        self.Bind(wx.EVT_RADIOBUTTON, self.Addr_Fs, self.Butn_Fs)
        
        text3 = wx.StaticText(panel, label="Address:")
        sizer.Add(text3, pos=ADDR_LOC, flag=wx.LEFT|wx.TOP, border=10)
        
        self.tc2 = wx.TextCtrl(panel)
        sizer.Add(self.tc2, pos=ADDR_TEXT_LOC, span=(1, 3),
			flag=wx.TOP|wx.EXPAND, border=5)

        text4 = wx.StaticText(panel, label="Size:")
        sizer.Add(text4, pos=SIZE_LOC, flag=wx.TOP|wx.LEFT, border=10)
    
        self.tc3 = wx.TextCtrl(panel)
        sizer.Add(self.tc3, pos=SIZE_TEXT_LOC, span=(1, 3), 
            flag=wx.TOP|wx.EXPAND, border=5)

        flash_button = wx.Button(panel, label="FLASH")
        sizer.Add(flash_button, pos=BUTT_FLASH_LOC)
        self.Bind(wx.EVT_BUTTON, self.StartFlash, flash_button)
        ##this button just for test whether the board is connected
        ##and test if our commands can send out to the board
        ##the test command is 'printenv'
        flash_test = wx.Button(panel, label="printenv")
        sizer.Add(flash_test, pos=(5, 4-1))
        self.Bind(wx.EVT_BUTTON, self.printenv, flash_test)
        ###
        
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
        connect  = wx.Menu()
        
        menubar.Append(filemenu, "&File")
        menubar.Append(confmenu, "&Configure")
        menubar.Append(helpmenu, "&Help")
        
        filemenu.AppendMenu(wx.ID_ANY, '&Connect', connect)
        filemenu.AppendSeparator()
        ConnectUart = connect.Append(wx.ID_ANY, 'Serial Port')
        ConnectTcp = connect.Append(wx.ID_ANY, 'TCP/IP') 
        WinClose = filemenu.Append(wx.ID_EXIT, 'Quit')
        
        conf_uart = confmenu.Append(wx.ID_ANY, 'Serial Port')
        conf_tcp  = confmenu.Append(wx.ID_ANY, 'TCP/IP')
        help_help = helpmenu.Append(wx.ID_ANY, 'Help')
        Help_About = helpmenu.Append(wx.ID_ANY, 'About')
        
        self.Bind(wx.EVT_MENU, self.BuildTcp, ConnectTcp) 
        self.Bind(wx.EVT_MENU, self.ConfUart, conf_uart)
        self.Bind(wx.EVT_MENU, self.ConfTcp, conf_tcp)
        self.Bind(wx.EVT_MENU, self.About, Help_About)
        self.Bind(wx.EVT_MENU, self.Help, help_help)
        self.Bind(wx.EVT_MENU, self.OnQuit, WinClose)
        
        self.SetMenuBar(menubar)
        
#JUST SET IT, WON'T DO ANYTHING!!!
#!!!TODO: bind some event to me!!!
        statusbar = self.CreateStatusBar()
        statusbar.SetStatusText('status: Unconnect')

        return True

    def BuildTcp(self, e):
#bad workround
        '''
        s=socket.socket()
        s.connect(('192.168.1.98',8080))   
        data=s.recv(512)
        print 'the data received is\n ',data
        
        s=socket.socket()
        s.bind(('192.168.1.98',8080))
        #s.listen(5)
        #cs,address = s.accept()
        #print 'got connected from',address
        #ra=cs.recv(512)
        #print ra
        '''
        
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

    def About(sel, e):
        AboutDia = Configure(None, title = 'About this tool')
        AboutDia.Ui_About()
        AboutDia.SetSize((200, 200))
        AboutDia.ShowModal()
        AboutDia.Destroy()

    def Help(sel, e):
        HelpDia = Configure(None, title = 'Help')
        HelpDia.Ui_Help()
        HelpDia.SetSize((200, 200))
        HelpDia.ShowModal()
        HelpDia.Destroy()
        
    def OnQuit(self, e):
        self.Close()

    def ChoosFile(self, e):
        wildcard = "All files (*.*)|*.*|" \
                   "Script file (*.ush)|*.ush|" \
                   "Binary file (*.bin)|*.bin|" \
                   "FW file (*.img)|*.img"
        dialog = wx.FileDialog(None, "Choose a file", os.getcwd(),
                           "", wildcard, wx.OPEN)
        if dialog.ShowModal() == wx.ID_OK:
            self.file = dialog.GetPath()
            self.tc1.SetLabel(self.file)
            dialog.Destroy()
            return self.file
        
        dialog.Destroy()
    
    def Addr_Src(self, a):
        self.tc2.SetLabel('0x61000000')
        self.tc3.SetLabel('Default')
    def Addr_Spl(self, a):
        self.tc2.SetLabel('0x00000000')
        self.tc3.SetLabel('0x00800000')
    def Addr_Uboot(self, a):
        self.tc2.SetLabel('0x00800000')
        self.tc3.SetLabel('0x00600000')
    def Addr_Fw(self, a):
        self.tc2.SetLabel('0x01400000')
        self.tc3.SetLabel('0x02000000')
    def Addr_Fs(self, a):
        self.tc2.SetLabel('0x03400000')
        self.tc3.SetLabel('0x10000000')
        return True

    def StartFlash(self, a):
        Address = self.tc2.GetValue()
        Size = self.tc3.GetValue()
        #print "file is:%s \nAddress is %s, size is %s"\
        #     %(self.file, Address, Size)
#shoule bind the gauge with real process but not timer
#just for test
        f_start = self.tc2.GetValue()
# there we shoule check the return value before gono
#        ra=cs.recv(512)
        f_size = self.tc3.GetValue()
        s = Configure()
        sk = s.BuildTcp('null')
        s.skt.send("nand erase " + f_start + ' '+ f_size)
        s.skt.send("nand write " + f_start + ' '+ f_size)
        GaugeDia = Configure(None, title = 'Task Process')
        GaugeDia.Ui_Gauge()
        GaugeDia.SetSize((300, 130))
        GaugeDia.ShowModal()
        #GaugeDia.Destroy()

    def printenv(self, a):
        s = Configure()
        sk = s.BuildTcp('null')
        s.skt.send("printenv")
        return True
    
class Configure(wx.Dialog):
    def __init__(self, parent = None,
                 title = "Configure"):
        wx.Dialog.__init__(self, parent, title = title)   
    
    def Ui_Uart(self):
        Port_Cho   = ['COM 1', 'COM 2']
        BaudRt_Cho = ['9600', '19200', '38400', '57600', '115200']
        Data_Cho   = ['8 bit', '7 bit']
        Parity_Cho = ['None', 'Odd', 'Even', 'Space']
        Stop_Cho   = ['1 bit', '1.5 bit', '2 bit']
        Flow_Cho   = ['None', 'Xon/Xoff', 'Hardware']
        UartItems  = ["Port:", "BaudRate:", "Data:", "Parity:",
                      "Stop:", "Flow Control:"]
        pan = wx.Panel(self)
        sizer = wx.GridBagSizer(8, 8)
        
        text1 = wx.StaticText(pan, label=UartItems[0])
        sizer.Add(text1, pos=(0, 0), flag=wx.LEFT | wx.TOP, border=15)
        
        self.ch1 = wx.ComboBox(pan, choices = Port_Cho)
        self.ch1.SetValue(Port_Cho[0])
        sizer.Add(self.ch1, pos = (0, 1), span=(1, 1),
                  flag=wx.TOP|wx.EXPAND, border = 10)
            
        text2 = wx.StaticText(pan, label=UartItems[1])
        sizer.Add(text2, pos=(1, 0), flag=wx.LEFT | wx.TOP, border=15)       
        self.ch2 = wx.ComboBox(pan, choices = BaudRt_Cho)
        sizer.Add(self.ch2, pos = (1, 1), span=(1, 1),
                  flag=wx.TOP|wx.EXPAND, border = 5)
        self.ch2.SetValue(BaudRt_Cho[0])
          
        text3 = wx.StaticText(pan, label=UartItems[2])
        sizer.Add(text3, pos=(2, 0), flag=wx.LEFT | wx.TOP, border=15)       
        self.ch3 = wx.ComboBox(pan, choices = Data_Cho)
        sizer.Add(self.ch3, pos = (2, 1), span=(1, 1),
                  flag=wx.TOP|wx.EXPAND, border = 5)
        self.ch3.SetValue(Data_Cho[0])
        
        text4 = wx.StaticText(pan, label=UartItems[3])
        sizer.Add(text4, pos=(3, 0), flag=wx.LEFT | wx.TOP, border=15)       
        self.ch4 = wx.ComboBox(pan, choices = Parity_Cho)
        sizer.Add(self.ch4, pos = (3, 1), span=(1, 1),
                  flag=wx.TOP|wx.EXPAND, border = 5)
        self.ch4.SetValue(Parity_Cho[0])
        
        text5 = wx.StaticText(pan, label=UartItems[4])
        sizer.Add(text5, pos=(4, 0), flag=wx.LEFT | wx.TOP, border=15)       
        self.ch5 = wx.ComboBox(pan, choices = Stop_Cho)
        sizer.Add(self.ch5, pos = (4, 1), span=(1, 1),
                  flag=wx.TOP|wx.EXPAND, border = 5)
        self.ch5.SetValue(Stop_Cho[0])
        
        text6 = wx.StaticText(pan, label=UartItems[5])
        sizer.Add(text6, pos=(5, 0), flag=wx.LEFT | wx.TOP, border=15)       
        self.ch6 = wx.ComboBox(pan, choices = Flow_Cho)
        sizer.Add(self.ch6, pos = (5, 1), span=(1, 1),
                  flag=wx.TOP|wx.EXPAND, border = 5)
        self.ch6.SetValue(Flow_Cho[0])
        
        OkBtn = wx.Button(pan, label='Ok')
        CloBtn = wx.Button(pan, label='Close')
        sizer.Add(OkBtn, pos = (7, 0),flag=wx.LEFT, border = 45)
        sizer.Add(CloBtn, pos = (7, 1),flag=wx.RIGHT, border = 35)
        self.Bind(wx.EVT_BUTTON, self.UartOk, OkBtn)
        self.Bind(wx.EVT_BUTTON, self.OnQuit, CloBtn)
        
        sizer.AddGrowableCol(2)
        pan.SetSizer(sizer)

    def UartOk(self, a):
        #val = self.ch1.GetValue()
        #print val
        return True
        
    def Ui_Tcp(self):
        DefaultIp = '192.168.1.182'
        DefaultPoart = '8007'
        TcpItems = ["Board IP:", "TCP Port:"]
        pan = wx.Panel(self)
        sizer = wx.GridBagSizer(2, 5)

        text1 = wx.StaticText(pan, label=TcpItems[0])
        sizer.Add(text1, pos=(0, 0), flag=wx.LEFT | wx.TOP, border=15)

        self.con1 = wx.TextCtrl(pan)
        sizer.Add(self.con1, pos = (0, 1), span=(1, 5),
                  flag=wx.TOP, border = 10)
        self.con1.SetValue(DefaultIp)
      
        text2 = wx.StaticText(pan, label=TcpItems[1])
        sizer.Add(text2, pos=(1, 0), flag=wx.LEFT | wx.TOP, border=15)
        
        self.con2 = wx.TextCtrl(pan)
        sizer.Add(self.con2, pos = (1, 1), span=(1, 5),
                  flag=wx.TOP, border = 10)
        #self.con2.SetValue("8005")
        self.con2.SetLabel(DefaultPoart)
        OkBtn = wx.Button(pan, label='Ok')
        CloBtn = wx.Button(pan, label='Close')
        sizer.Add(OkBtn, pos = (3, 0),flag=wx.LEFT, border = 65)
        sizer.Add(CloBtn, pos = (3, 1),flag=wx.RIGHT, border = 75)
        self.Bind(wx.EVT_BUTTON, self.OnQuit, CloBtn)
        self.Bind(wx.EVT_BUTTON, self.BuildTcp, OkBtn)

        sizer.AddGrowableCol(2)
        pan.SetSizer(sizer)

    def BuildTcp(self, a):
###TODO: add error check!!!
        tmp = Configure()
        tmp1 = tmp.Ui_Tcp()
        self.BoardIp = tmp.con1.GetValue()
        self.TcpPort = tmp.con2.GetValue()
        
        self.skt = socket.socket()
        self.skt.connect((self.BoardIp, int(self.TcpPort)))
###shoule check the return value
        self.skt.send("found you!")
        #data=s.recv(512)
        self.Destroy()
        
    def Ui_About(self):
        pan = wx.Panel(self)
        text = wx.StaticText(pan, label = "about!!!")

    def Ui_Help(self):
        pan = wx.Panel(self)
        text = wx.StaticText(pan, label = "help!!!")

    def Ui_Gauge(self):
#bind it with real process but  not timer
        self.timer = wx.Timer(self, 1)
        self.count = 0
        self.timer.Start(100)
        self.Bind(wx.EVT_TIMER, self.OnTimer, self.timer)
        
        pan = wx.Panel(self)
        self.pan = pan
        Sizer = wx.GridBagSizer(3, 10)
        
        self.gauge = wx.Gauge(pan, range=TASK_RANGE, size=(235, 25))
        Sizer.Add(self.gauge, pos = (0, 1), span=(1, 1),
                  flag=wx.TOP|wx.EXPAND, border = 30)
        
        Sizer.AddGrowableCol(3)
        pan.SetSizer(Sizer)
        
    def OnTimer(self, e):   
        self.count = self.count + 1
        self.gauge.SetValue(self.count)
        
        if self.count == TASK_RANGE:
            self.timer.Stop()
            wx.FutureCall(5, self.ShowMessage)
 
    def ShowMessage(self):
        wx.MessageBox('Flash completed', 'Info', 
            wx.OK | wx.ICON_INFORMATION)
        self.Destroy()
        
    def OnQuit(self, e):
        self.Destroy()
        
class App(wx.App):
    def OnInit(self):
        self.frame = Frame(parent = None, title = "tool")
        self.frame.Show()
        return True
    
if __name__ == "__main__":
    app = App()
    app.MainLoop()
