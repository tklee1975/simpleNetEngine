# Fix 


## Color Definition
`#define SN_GREEN            ImColor(0, 255, 0)`
-> Use const 

## enum class
```
+enum SNSocketAcceptStatus { // Jason - enum class
```



### emplace_back rather push_back()

this help to save one copy action 

### Exception 
- 

User Trigger -> Try & Catch 

Fail to recover 

### 
Use auto  

### pragma once 

#ifndef _XXXX 
#define _XXXX


### 
Use String_view 
-> Help no allocation 


### 
SNSession *xxx 
-> unique_ptr<SNSession>

## Google 
Prefer int over u_int   -> 

Take care of u_int 

## Resize 
- Resize to smaller, no cost at all 


## Override 
add override to prevent mismatch method 

## Last Error
```

```

not NULL -> nullptr

+    using NativeFD = int;

## Network 
`size_t sendData(const std::vector<char> &dataBuf);`
-> `std::span<u8> ?`

-    int ret = ::send(_sock, data, (int)dataSize, 0);
+    int ret = ::send(_sock, data, static_cast<int>(dataSize), 0);


```
+void SNSocket::platformInit() {
+    static SNSocketInit s;
+}
```

```
-int SNSocket::getSockFd()
+SNSocket::NativeFD SNSocket::getSockFd()
 {
     return _sock;
 }
 ```

```

 #include "SNSocket.h"
 #include <iostream>
-#include <unistd.h>
+
+#if _WIN32
+
+#else
+    #include <unistd.h>
+#endif
```

## IMGUI 
```
+#define SDL_MAIN_HANDLED // Jason - add this on Windows
 #include <SDL.h>
 #include "imgui.h"
```


## Wrap for String
 using MyString = std::string; C++;

`std::string SNString::str()`
-> `const std::string& SNString::str() const {`

`const char * SNString::c_str()`
-> `const char * SNString::c_str() const`

// Jason - inplace trim is slow !!
+    std::vector<SNString> split(const char *delimiter); // Jason - std::fixed_vector<std::str_view>


## Multi-Platform 

1. WinSock 
_WIN32: 
#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")
#include <Windows.h>
OTHERS:
n/a

2. Strcmp 
WIN:    
inline 
int my_strcasecmp(const char* a, const char* b) { return _stricmp(a,b); }
OTHER: 
int my_strcasecmp(const char* a, const char* b) { return strcasecmp(a,b); }
