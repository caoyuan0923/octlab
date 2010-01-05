ATTENTION:
Use of this source code is governed by a Clear BSD-style license that can be
found on the http://octlab.googlecode.com/svn/trunk/COPYRIGHT.TXT web-page or in
the COPYRIGHT.TXT file

To use this LabView applications (VIs):
1) first, copy DLLs from folder
http://octlab.googlecode.com/svn/trunk/subVIs/dll/ into System32 folder for
Windows 32-bit editions (C:\WINDOWS\System32) or into SysWOW64 folder for
Windows 64-bit editions (C:\WINDOWS\SysWOW64);
2) second, use LabView 2009 or above 32-bit edition;
3) third, install "Microsoft Visual C++ 2008 SP1 Redistributable Package (x86)"
from Microsoft web-site if after running LabView asks for OpenMP DLL;
4) forth, copy OCTLab sub-VIs from folder
http://octlab.googlecode.com/svn/trunk/subVIs/LabView2009-32bits/ into
"user.lib\OCTLab" folder (you should create sub-folder OCTLab if there is no
such folder in folder user.lib): in case of Windows 32-bit editions it is
located in "Program Files\National Instruments\LabVIEW 2009" folder; in case of
Windows 64-bit editions it is located in
"Program Files (x86)\National Instruments\LabVIEW 2009" folder

NOTE! This sub-VIs and DLLs are NOT for 64-bit edition of LabView, but you can
use LabView 32-bit edition without any problems with Windows 64-bit editions.