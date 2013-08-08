#a flash and test tool for sony xarina
#20130626. fantao

import wx
import sys

###colum, row
#pan1
PAN1_LOCAT = (10, 35)
PAN1_SIZE  = (100, 400)
#pan2
#WORK_LOCAT = (130, 35)
WORK_LOCAT = (130, 10)
WORK_SIZE  = (350, 300)
#pan3
INFO_LOCAT = (130, 370)
INFO_SIZE  = (350, 100)

class Frame(wx.Frame):
    def __init__(self, parent = None, title = "menu"):
        wx.Frame.__init__(self, parent = None, title = "menu",
                          size = (500, 550))
        
        '''set menubar and status bar'''
        self.InitBar()
        font = wx.SystemSettings_GetFont(wx.SYS_SYSTEM_FONT)
        font.SetPointSize(10)
        
        pan = wx.Panel(self)
      
        pan1 = wx.Panel(pan, pos = PAN1_LOCAT, size = PAN1_SIZE)
        pan1.SetBackgroundColour(wx.Colour(255, 255, 255))
        title1 = wx.StaticText(pan1, label='Functions')
        title1.SetFont(font)
        #pan1.Add(st1, flag=wx.TOP, border=8)
        
        
        pan2 = wx.Panel(pan, pos = WORK_LOCAT, size = WORK_SIZE)
        #pan2.SetBackgroundColour(wx.Colour(255,255,255))
        self.SetPan2(pan2)
        
        pan3 = wx.Panel(pan, pos = INFO_LOCAT, size = INFO_SIZE)
        title3 = wx.StaticText(pan3, label='Infomation')
        wx.TextCtrl(pan3, size = (INFO_SIZE))
        #title3.SetFont(font)

    def SetPan2(self, panel):
        sizer = wx.GridBagSizer(5, 5)

        text1 = wx.StaticText(panel, label="Java Class")
        sizer.Add(text1, pos=(0, 0), flag=wx.TOP|wx.LEFT|wx.BOTTOM, 
            border=15)
        
        #icon = wx.StaticBitmap(panel, bitmap=wx.Bitmap('exec.png'))
        #sizer.Add(icon, pos=(0, 4), flag=wx.TOP|wx.RIGHT|wx.ALIGN_RIGHT, 
        #    border=5)
        
        line = wx.StaticLine(panel)
        sizer.Add(line, pos=(1, 0), span=(1, 5), 
            flag=wx.EXPAND|wx.BOTTOM, border=10)
        
        text2 = wx.StaticText(panel, label="Name")
        sizer.Add(text2, pos=(2, 0), flag=wx.LEFT, border=10)
        
        tc1 = wx.TextCtrl(panel)
        sizer.Add(tc1, pos=(2, 1), span=(1, 3), flag=wx.TOP|wx.EXPAND)
        
        text3 = wx.StaticText(panel, label="Package")
        sizer.Add(text3, pos=(3, 0), flag=wx.LEFT|wx.TOP, border=10)
        
        tc2 = wx.TextCtrl(panel)
        sizer.Add(tc2, pos=(3, 1), span=(1, 3), flag=wx.TOP|wx.EXPAND, 
            border=5)
        button1 = wx.Button(panel, label="Browse...")
        sizer.Add(button1, pos=(3, 4), flag=wx.TOP|wx.RIGHT, border=5)

        text4 = wx.StaticText(panel, label="Extends")
        sizer.Add(text4, pos=(4, 0), flag=wx.TOP|wx.LEFT, border=10)
        '''
        pan2_sizer = wx.GridBagSizer(7, 7)
        text1 = wx.StaticText(pan2, label="Workstation")
        pan2_sizer.Add(text1, pos=(3, 0), span = (7, 1), flag=wx.TOP | wx.LEFT, 
            border=5)
        '''
        #text2 = wx.StaticText(pan2, label="Choose the file:")
        #pan2_sizer.Add(text2, pos=(5, 10), flag=wx.LEFT, border=10)
        #pan2_ti1 = wx.StaticText(pan2, label='Choose the file:')
        #wx.ComboBox(pan2, pos = (2, 20))
        '''
        wx.Button(pan2, label = 'Broswer', pos = (270, 20))
        
        pan2_ti2 = wx.StaticText(pan2, label='Choose the file:')
        
        self.rb1 = wx.RadioButton(pan2, label='SCRIPT', pos=(10, 80))
        self.rb2 = wx.RadioButton(pan2, label='S P L', pos=(70, 80))
        self.rb3 = wx.RadioButton(pan2, label='UBOOT', pos=(130, 80))
        self.rb3 = wx.RadioButton(pan2, label='F W', pos=(190, 80))
        self.rb3 = wx.RadioButton(pan2, label='ROOTFS', pos=(250, 80))
        '''
    def InitBar(self):
        
#TODO: bind some event!!!
        menubar = wx.MenuBar()
        filemenu = wx.Menu()
        confmenu = wx.Menu()
        helpmenu = wx.Menu()
        
        filemenu.Append(wx.ID_FILE, 'Connect')
        filemenu.AppendSeparator()
        WinClose = filemenu.Append(wx.ID_EXIT, 'Quit')
        self.Bind(wx.EVT_MENU, self.OnQuit, WinClose)
        
        helpmenu.Append(wx.ID_HELP, 'Help')
        
        menubar.Append(filemenu, "&File")
        menubar.Append(confmenu, "&Configure")
        menubar.Append(helpmenu, "&Help")
        self.SetMenuBar(menubar)

#JUST SET IT, WON'T ANYTHING!!!
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
