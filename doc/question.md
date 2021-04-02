# Q & A 

## Socket Send 
if socket.send always send out buffer given 
or may possibly send partially ? 
if send partially, how to handle?

-> The packet buffer will fully send 
    or else the network should have some problems

## How to organise the buffer better?
```cpp
buf[nRead] = '\0';
    
std::vector<char> cleanBuffer = std::vector<char>(buf.begin(), buf.begin()+nRead);  
            // ken: need to copy to make the buf.end() correct?
```

## How to handle exception properly?


## How to close the socket clearly? and able to bind again
Use socket reuse ?? 


## What's `#pragma once` ? 



## When to use fmt-header-only vs fmt::fmt?
#target_link_libraries(app1 PRIVATE fmt::fmt-header-only) # ken: when to use this?
target_link_libraries(app1 PRIVATE fmt::fmt)
