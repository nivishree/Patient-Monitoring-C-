@Echo OFF
Echo "Building solution/project file using batch file"
SET SolutionPath=./monitors.sln
call %windir%\Microsoft.NET\Framework\v4.0.30319\msbuild.exe %SolutionPath%
SET EXEPath=.\Debug\monitors.exe
call %EXEPath%
Echo End Time -%Time%
Set /p Wait=Build and Run Process Completed...

