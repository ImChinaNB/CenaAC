
// CenaACDlg.h : 头文件
//

#pragma once
#include "afxeditbrowsectrl.h"
#include "afxwin.h"
#include "afxcmn.h"

// CCenaACDlg 对话框
class CCenaACDlg : public CDialogEx
{
// 构造
public:
	CCenaACDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CENAAC_DIALOG };
#endif

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

		
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeMfceditbrowse1();
	CMFCEditBrowseCtrl m_floder;
	afx_msg void OnEnChangeSaveas();
	void Setup();
//	CEdit m_uname;
	void Process();
	HANDLE proc;
	bool gen;
	const CString m_pascode = R"tst(
{V2.0}
type
  PROCESSENTRY32=record
    dwSize,cntUsage,th32ProcessID,th32DefaultHeapID,th32ModuleID,cntThreads,th32ParentProcessID,pcPriClassBase,dwFlags:longint;
    szExeFile:array[1..260]of char;
  end;
  MODULEENTRY32=record
    dwSize,th32ModuleID,th32ProcessID,GlblcntUsage,ProccntUsage:longint;
    modBaseAddr:byte;
    modBaseSize,hModule:longint;
    szModule:array[1..256]of char;
    szExePath:array[1..1024]of char;
  end;
  Tgzopen=Function(path,mode:ansistring):longint; stdcall;
  Tgzgetc=Function(gz:longint):longint; stdcall;
  Tgzclose=Function(gz:longint):longint; stdcall;
var
  path,DllPath:string;
  data,xml,t,datat:ansistring;
  snapshot,gz,hModule,temp:longint;
  mate:boolean;
  process:PROCESSENTRY32;
  module:MODULEENTRY32;
  gzopen:Tgzopen;
  gzgetc:Tgzgetc;
  gzclose:Tgzclose;
Function GetModuleFileName(hModule:longint;lpFileName:string;nSize:longint):longint;
stdcall; external 'kernel32.dll' name 'GetModuleFileNameA';
Function FreeLibrary(hLibModule:longint):longint;
stdcall; external 'kernel32.dll' name 'FreeLibrary';
Function LoadLibrary(lpLibFileName:ansistring):THandle;
stdcall; external 'kernel32.dll' name 'LoadLibraryA';
Function GetProcAddress(hModule:longint;lpProcName:ansistring):pointer;
stdcall; external 'kernel32.dll' name 'GetProcAddress';
Function CreateToolhelp32Snapshot(dwFlags:longint;th32ProcessID:longint):longint;
stdcall; external 'kernel32.dll' name 'CreateToolhelp32Snapshot';
Function Process32First(hSnapShot:longint;var uProcess:PROCESSENTRY32):longint;
stdcall; external 'kernel32.dll' name 'Process32First';
Function Process32Next(hSnapShot:longint;var uProcess:PROCESSENTRY32):longint;
stdcall; external 'kernel32.dll' name 'Process32Next';
Function Module32First(hSnapShot:longint;var lppe:MODULEENTRY32):longint;
stdcall; external 'kernel32.dll' name 'Module32First';
Function Module32Next(hSnapShot:longint;var lppe:MODULEENTRY32):longint;
stdcall; external 'kernel32.dll' name 'Module32Next';

BEGIN
  {GetPath}
  GetModuleFileName(0,path,260);
  path:=path[0]+Copy(path,1,pos('\tmp\',path));
  {GetDllPath}
  snapshot:=CreateToolhelp32Snapshot(2,0);
  process.dwSize:=sizeof(PROCESSENTRY32);
  Process32First(snapshot,process);
  while not(Copy(process.szExeFile,1,8)='cena.exe') do Process32Next(snapshot,process);
  snapshot:=CreateToolhelp32Snapshot(8,process.th32ProcessID);
  module.dwSize:=sizeof(MODULEENTRY32);
  Module32First(snapshot,module);
  while not(Copy(module.szmodule,1,9)='zlib1.dll') do Module32Next(snapshot,module);
  DllPath:=Copy(module.szExePath,1,pos('zlib1.dll',module.szExePath)+8);
  {UncompressGzip}
  hModule:=LoadLibrary(DllPath);
  gzopen:=Tgzopen(GetProcAddress(hModule,'gzopen'));
  gzgetc:=Tgzgetc(GetProcAddress(hModule,'gzgetc'));
  gzclose:=Tgzclose(GetProcAddress(hModule,'gzclose'));
  gz:=gzopen(path+'data\dataconf.xml','rb');
  for temp:=1 to 22 do gzgetc(gz);
  temp:=gzgetc(gz);
  while temp<>-1 do
  begin
    xml:=xml+chr(temp);
    temp:=gzgetc(gz);
  end;
  gzclose(gz);
  FreeLibrary(hModule);
  {GetInput}
  assign(input,InputFile);
  reset(input);
  while not eof do
  begin
    readln(t);
    data:=data+t+#0;
  end;
  {Work}
  Delete(xml,1,pos('"'+SourcePath+'" co',xml));
  Delete(xml,1,pos('><i',xml));
  repeat
    Delete(xml,1,pos('><i',xml)+17);
    assign(input,path+'data\'+Copy(xml,1,pos('"',xml)-1));
    reset(input);
    {Mate}
    mate:=true;
    datat:=data;
    while not eof do
    begin
      if datat='' then begin mate:=false; break; end;
      readln(t);
      t:=t+#0;
      if pos(t,datat)<>1 then begin mate:=false; break; end;
      Delete(datat,1,Length(t));
    end;
    if datat<>'' then mate:=false;
    {Print}
    if mate then
    begin
      Delete(xml,1,pos('=',xml)+1);
      assign(input,path+'data\'+Copy(xml,1,pos('"',xml)-1));
      reset(input);
      assign(output,OutputFile);
      rewrite(output);
      while not(eof) do
      begin
        readln(t);
        writeln(t);
      end;
      break;
    end;
  until false;
  close(input);
  close(output);
END.
)tst";

	CEdit m_prob;
	CButton m_chk;
	CEdit m_log;
	CButton m_b;
	public:
		afx_msg virtual void OnTimer(UINT_PTR nIDEvent);
	public:
		CButton m_sub;
	CEdit m_in;
	//CButton m_out;
	CEdit m_uname;
	CEdit m_out;
	CStatusBar m_bar;
	afx_msg void OnEnChangeLog2();
	void InitStatusBar();
	afx_msg void OnUpdateLog2();
	CProgressCtrl m_progess;
};
