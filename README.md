# project-acid
CS16 NonSteam Hallucinogen -- a radar FarESP NonSteam CS 1.6 PoC.  
For educational purposes **only**.  
这是一个 Ｃｏｕｎｔｅｒ－Ｓｔｒｉｋｅ　１.６　ｈｏｏｋ　—　雷达ＦａｒＥＳＰ　ＮｏｎＳｔｅａｍ　概念验证。  
仅用于教育目的。

## Implementation
Hooked `PreS_DynamicSound` allows a FarESP implementation.  
The client uses a [UDP WinSock](https://en.wikipedia.org/wiki/Winsock) socket which connects to the python UDP server. The python server also has a an http handler, to serve the radar to any html5 client.  
`PreS_DynamicSound` 是用于ＦａｒＥＳＰ． 
客户有[UDP WinSock](https://en.wikipedia.org/wiki/Winsock)。Ｗｉｎｓｏｃｋ连接到ｐｙｔｈｏｎＵＤＰ服务器。Ｐｙｔｈｏｎ也有一个ＨＴＴＰｈａｎｄｌｅｒ. 

## Usage
`python server.py` & inject the DLL into `hl.exe`. Enable debugging definitions if needed.

## Requirements
* Bring your own offsets (included exclusively for **interoperability purposes**)
* Microsoft Detours
* HLSDK

Tested with Windows 7 SP 1 x64, 32-bit DLL injected into a 32-bit executable. 

## PoC
https://youtu.be/Efo0qONJIC4
